
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif

#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <d3dx9.h>
#include <vector>
#include <process.h>
#include <aclapi.h>
#include <windowsx.h>
//#include <thread>
//#include "cuda_runtime.h"
//#include "device_launch_parameters.h"
//#include <cuda_d3d9_interop.h>
//#include <helper_cuda.h>         // CUDA Helper Functions for initialization
#include "Globals.h"

//#include "CudaHostJoint.h"
using namespace System;
using namespace System::Threading;
using namespace System::Threading::Tasks;



//ThreadStart MoveBirdThread;
Globs Glbs;
Globs *pGlbs;

//#include "Pickcuda.cu"


IDirect3D9 *d3d9Obj; //Direct3
//unsigned int g_iAdapter = NULL; // Our adapter

D3DADAPTER_IDENTIFIER9 adapterId;
//int CUDAdev;


#include ".\Pick\Stats.h"
D3DDISPLAYMODE cDisplayModeData = {1024,768,D3DPRESENT_RATE_DEFAULT,D3DFMT_X8R8G8B8};
D3DDISPLAYMODE *DisplayMde = 0;
HWND myAppHWND;


#include "camera.h"
#include "LowestStack.h"
#include "Mob.h"
#include "d3dUtility.h"
#include "FlockHeaders.h"

using namespace Pick;

//
// Functions
//

void SetUpBirds(void);
//void MoveBird();
bool AnalisewParam(WPARAM wParam);
void InitBird(Mob* pB);
bool WriteVars(void);
bool ReadVars(void);
bool Display(void);

bool ClosingDouwn = false;
//
// Framework functions
//
bool Setup()
{
	//pointer to globals
	pGlbs = &Glbs;
	pGlbs->ThreadStackHold = 0;
	//read .ini file from last time
	ReadVars();
	// time delta for calcs
	QueryPerformanceCounter(&lastTime);
	//Check to see if we have high res counter.
	// get the high resolution counter's accuracy
	QueryPerformanceFrequency(&ticksPerMicroSecondhr);
	ticksPerMicroSecondhr.QuadPart /= 1000000;
	// SetUpBirds
	pGlbs->RoostSphere._center = D3DXVECTOR3(0, 0, 0);
	pGlbs->RoostSphere._radius = 180;
	pGlbs->RoostSphere._radiusSqr = pGlbs->RoostSphere._radius * pGlbs->RoostSphere._radius;

	D3DXCreateCylinder(D3DDevice, 0, 4, 10, 3, 1, &Cylinder, 0);


	// Set up Font
	D3DXFONT_DESC lf;
	D3DXFONT_DESC* plf = &lf;
	ZeroMemory(&lf, sizeof(D3DXFONT_DESC));
	lf.Height = 12;    // in logical units
	lf.Width = 6;    // in logical units
	lf.Weight = 500;   // boldness, range 0(light) - 1000(bold)
	lf.Italic = false;
	lf.CharSet = DEFAULT_CHARSET;
	lf.OutputPrecision = 0;
	lf.Quality = 0;
	lf.PitchAndFamily = 0;
	lf.MipLevels = 0;
	strcpy_s(lf.FaceName, "Courier\0"); // font style

	if (FAILED(D3DXCreateFontIndirect(D3DDevice, plf, &::Font)))
	{
		ErrorExit(TEXT("D3DXCreateFontIndirect() - FAILED"));		return false;
	}

	if (S_OK != (::Font->PreloadCharacters('A', 'Z')))
	{
		ErrorExit(TEXT("PreloadCharacters() - FAILED"));		return false;
	}
	if (S_OK != (::Font->PreloadCharacters('a', 'z')))
	{
		ErrorExit(TEXT("PreloadCharacters() - FAILED"));		return false;
	}
	if (S_OK != (::Font->PreloadCharacters('0', '9')))
	{
		ErrorExit(TEXT("PreloadCharacters() - FAILED"));		return false;
	}
	// Load the XFile data.
	HRESULT hr = 0;
	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD        numMtrls = 0;


	hr = D3DXLoadMeshFromX(
		"bigship1.x",

		D3DXMESH_MANAGED,
		D3DDevice,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&Spccrft);

	if (FAILED(hr))
	{
		ErrorExit(TEXT("D3DXLoadMeshFromX"));		return false;
	}

	//
	// Extract the materials, and load textures.
	//

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for (DWORD i = 0; i < numMtrls; i++)
		{
			// the MatD3D property doesn't have an ambient value set
			// when its loaded, so set it now:
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			// save the ith material
			Mtrls.push_back(mtrls[i].MatD3D);

			// check if the ith material has an associative texture
			if (mtrls[i].pTextureFilename != 0)
			{
				// yes, load the texture for the ith subset
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFile(D3DDevice, mtrls[i].pTextureFilename, &tex);

				// save the loaded texture
				myTextures.push_back(tex);
			}
			else
			{
				// no texture for the ith subset
				myTextures.push_back(0);
			}
		}
	}
	d3d::Release<ID3DXBuffer*>(mtrlBuffer);

	hr = Spccrft->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjBuffer->GetBufferPointer(), 0, 0, 0);
	d3d::Release<ID3DXBuffer*>(adjBuffer);
	if (FAILED(hr))
	{
		::MessageBox(0, "OptimizeInplace() - FAILED", 0, 0);
		return false;
	}

	HRD(D3DDevice->CreateVertexBuffer(sizeof(LineBuff), D3DUSAGE_DONOTCLIP, LineVertexFVF, D3DPOOL_MANAGED, &v_buffer, NULL));
	//HRD(D3DDevice->CreateVertexBuffer(sizeof(LineBuff), D3DUSAGE_DYNAMIC | D3DUSAGE_DONOTCLIP, LineVertexFVF, D3DPOOL_SYSTEMMEM, &v_buffer, NULL));

	// Set indecies for lines between birds - this is effectivly a const.
	HRD(D3DDevice->CreateIndexBuffer(sizeof(IndexBuf), D3DUSAGE_DONOTCLIP | D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &i_buffer, NULL));
	ZeroMemory(IndexBuf, sizeof(IndexBuf));
	for (WORD i = 0; i < NearestMobStackSize; i++)
	{
		//IndexBuf[i*2] = 0;
		IndexBuf[i*2 + 1] = i+1;
	}
	void* pVideoRam;
	HRD(i_buffer->Lock(0, sizeof(IndexBuf), (void**)&pVideoRam, 0/*D3DLOCK_DISCARD*/));    // lock the buffer
	memcpy(pVideoRam, IndexBuf, sizeof(WORD) * NearestMobStackSize * 2);    // copy the indecies to the locked buffer
	HRD(i_buffer->Unlock());    // unlock the buffer

	SetUpBirds();
	// Sort Birds Linked list
	pGlbs->BirdsLLTail = Mob::Sort(&Bird[0],pGlbs->BirdsCount);
	//InitBird(&Pred[0]);
	//Pred[0].mtrlCol = d3d::WHITE_MTRL; 

	// Set light.
	D3DXVECTOR3 dir(0.707f, -0.0f, 0.707f);
	D3DXCOLOR col(1.0f, 1.0f, 1.0f, 1.0f);
	D3DLIGHT9 light = d3d::InitDirectionalLight(&dir, &col);

	D3DDevice->SetLight(0, &light);
	D3DDevice->LightEnable(0, true);
	D3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, false);
	D3DDevice->SetRenderState(D3DRS_SPECULARENABLE, false);

	TheCamera.setPosition(&D3DXVECTOR3(0.0f, 0.0f, -2000.0f));

	TheCamera.strafe(0.0f);
	TheCamera.fly(0.0f);
	TheCamera.getViewMatrix(&::View);
	D3DDevice->SetTransform(D3DTS_VIEW, &::View);

	// Set projection matrix.
	D3DXMatrixPerspectiveFovLH(
			&proj,
			D3DX_PI * 0.25f, // 45 - degree
			(float)Width / (float)Height,
			1.0f,
			10000.0f);
	D3DDevice->SetTransform(D3DTS_PROJECTION, &proj);

	//Setup threads
	_SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	for (int i = 0;i < NumberOfThreads;i++)
	{
		thisThread[i].PrefferedProc = i % sysInfo.dwNumberOfProcessors;
	}
	/////////////////////////////////////////////////////////
	//DWORD dwRes, dwDisposition;
	//PSID pAdminSID = NULL;
	//PACL pACL = NULL;
	//PSECURITY_DESCRIPTOR pSD = NULL;
	//EXPLICIT_ACCESS ea[1];
	//SID_IDENTIFIER_AUTHORITY SIDAuthWorld =
	//	SECURITY_WORLD_SID_AUTHORITY;
	//SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
	//SECURITY_ATTRIBUTES sa;
	//LONG lRes;
	//HKEY hkSub = NULL;

	//// Create a SID for the BUILTIN\Administrators group.
	//if (!AllocateAndInitializeSid(&SIDAuthNT, 2,
	//	SECURITY_BUILTIN_DOMAIN_RID,
	//	DOMAIN_ALIAS_RID_ADMINS,
	//	0, 0, 0, 0, 0, 0,
	//	&pAdminSID))
	//{
	//	ErrorExit(TEXT("AllocateAndInitializeSid Error "));
	//}

	//// Initialize an EXPLICIT_ACCESS structure for an ACE.
	//// The ACE will allow the Administrators group full access to
	//// the key.
	//ea[0].grfAccessPermissions = THREAD_ALL_ACCESS;
	//ea[0].grfAccessMode = SET_ACCESS;
	//ea[0].grfInheritance = NO_INHERITANCE;
	//ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	//ea[0].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
	//ea[0].Trustee.ptstrName = (LPTSTR)pAdminSID;

	//// Create a new ACL that contains the new ACEs.
	//dwRes = SetEntriesInAcl(1, ea, NULL, &pACL);
	//if (ERROR_SUCCESS != dwRes)
	//{
	//	ErrorExit(TEXT("SetEntriesInAcl Error "));
	//}

	//// Initialize a security descriptor.  
	//pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
	//if (NULL == pSD)
	//{
	//	ErrorExit(TEXT("LocalAlloc Error "));
	//}

	//if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION))
	//{
	//	ErrorExit(TEXT("InitializeSecurityDescriptor Error"));
	//}

	//// Add the ACL to the security descriptor. 
	//if (!SetSecurityDescriptorDacl(pSD,
	//	TRUE,     // bDaclPresent flag   
	//	pACL,
	//	FALSE))   // not a default DACL 
	//{
	//	ErrorExit(TEXT("SetSecurityDescriptorDacl Error %u\n"));
	//}

	//// Initialize a security attributes structure.
	//sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	//sa.lpSecurityDescriptor = pSD;
	//sa.bInheritHandle = FALSE;
	///////////////////////////////////////////////////////////

	for (int i = 0;i < NumberOfThreads;i++)
	{
		thisThread[i].Busy = FALSE;
		thisThread[i].ThisBird = 0;
		thisThread[i].WaitSignal = 0;
		ThreadParam[i] = i;
		thisThread[i].ThreadPtr = (HANDLE)_beginthreadex(0, 1 << 16 , MBThreadWrap, &ThreadParam[i],0, &thisThread[i].ID);
		thisThread[i].PreviousProc = SetThreadIdealProcessor(&thisThread[i].ThreadPtr, thisThread[i].PrefferedProc);
		
		
		//HRD(D3DDevice->CreateVertexBuffer(sizeof(LineBuff), D3DUSAGE_DONOTCLIP, LineVertexFVF, D3DPOOL_MANAGED, &v_buffer, NULL));

		//if (thisThread[ThisThreadNumber].PreviousProc == (DWORD)-1)
		//{
		//	ErrorExit(TEXT("SetThreadIdealProcessor"));
		//}
		//DWORD rv;
		//rv = GetSecurityInfo(thisThread[i].ThreadPtr, SE_KERNEL_OBJECT, thisThread[i].Security, 0, 0, 0, 0, 0);
		//if (rv != ERROR_SUCCESS)
		//{
		//	Beep(1500, 100);
		//}
	}
	return true;
}

void Cleanup()
{
	//release threads
	for (int i = 0;i < NumberOfThreads;i++)
	{
		thisThread[i].WaitSignal = EXIT_CUST_THREAD;
		WakeByAddressSingle(&thisThread[i].WaitSignal);
		WaitForSingleObject( thisThread[i].ThreadPtr, INFINITE);
		CloseHandle(thisThread[i].ThreadPtr);
	}
	for(UINT i = 0; i < myTextures.size(); i++) d3d::Release<IDirect3DTexture9*>( myTextures[i] );
	d3d::Release<IDirect3DVertexBuffer9*>(v_buffer);
	d3d::Release<IDirect3DIndexBuffer9*>(i_buffer);
	d3d::Release<ID3DXMesh*>(Cylinder);
	d3d::Release<ID3DXFont*>(::Font);
	d3d::Release<ID3DXMesh*>(Spccrft);
	d3d::DrawSphere(0,D3DXVECTOR3(0,0,0),0,0,D3DMATERIAL9());
	d3d::Release<IDirect3D9*>(d3d9Obj); // done with d3d9 object
}

static bool Display(void)
{
	pGlbs = &Glbs;
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 centre(0.0f, 1.0f, 0.0f);
	static float CameraCircle = 0;

	if (D3DDevice)
	{

		LARGE_INTEGER currTime;
		QueryPerformanceCounter(&currTime);
		timeDelta.QuadPart = (currTime.QuadPart - lastTime.QuadPart);
		TimeDeltaAnim = (float)(timeDelta.QuadPart / ticksPerMicroSecondhr.QuadPart) / 1000000;


		if (timeDelta.QuadPart > 1000000 || timeDelta.QuadPart == 0)
		{
			timeDelta.QuadPart = 1000000;
		}

		Mob* pBird = 0;

		// move the camera
		if (pGlbs->BeABirdTog.bval)
		{
			D3DXVECTOR3 eye = Bird[1].Pos - (Bird[1].NormVel() * 150.0f);
			D3DXMatrixLookAtLH(&::View, &eye, &(Bird[1].Pos), &up);
		}
		else
		{
			if (pGlbs->CameraCircleTog.bval)
			{
				CameraCircle += 0.005f;
				if (CameraCircle > 2 * D3DX_PI) CameraCircle = 0;
				D3DXVECTOR3 TempPos(-sin(CameraCircle) * 2000, 0, cos(CameraCircle) * 2000);
				D3DXMatrixLookAtLH(&::View, &TempPos, &centre, &up);
			}
			else
			{
				//TheCamera.getViewMatrix(&::View);
				D3DXVECTOR3 eye;
				TheCamera.getPosition(&eye);
				D3DXMatrixLookAtLH(&::View, &eye, &centre, &up);
			}
		}

		D3DDevice->SetTransform(D3DTS_VIEW, &::View);
		D3DDevice->GetViewport(pvp);
		// now have a view we can calculate x,y screen pos
		pBird = &Bird[0];
		int freeThread = -1;
		int chkThread = 0;
		ULONG ThreadComparisonValue = 0;
		pGlbs->ThreadCount = 0;
		CurrentClosestDist = (FLOAT)INFINITE;

		while (true)
		{

			freeThread = -1;
			chkThread = 0;
			DWORD dwCreateFlags = 0;
			while (freeThread == -1 && pBird != 0)
			{
				if (thisThread[chkThread].Busy == FALSE)
				{
					freeThread = chkThread;
					thisThread[freeThread].Busy = TRUE;
					thisThread[freeThread].ThisBird = pBird;
					thisThread[freeThread].WaitSignal = CUST_THREAD_DISPLAY;//non zero to fire
					WakeByAddressSingle(&thisThread[freeThread].WaitSignal);
				}
				chkThread++;
				if (chkThread >= NumberOfThreads && freeThread == -1)
				{
					WaitOnAddress(&pGlbs->ThreadStackHold, &ThreadComparisonValue, sizeof(ULONG), 5);
					pGlbs->ThreadStackHold = 0;
					chkThread = 0;
				}
			}

			if (pBird->Next == 0)
				break;
			pBird = pBird->Next;
		}

// Render the birds
		D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		D3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		D3DDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, true);
		D3DDevice->BeginScene();
		int cnt = 0;

		pBird = &Bird[0];
		/// This is just unsafe to ask DX to go MT



		//freeThread = -1;
		//chkThread = 0;
		//ThreadComparisonValue = 0;
		//pGlbs->ThreadCount = 0;
		//while (true)
		//{
		//	if (pBird->OnCreen)
		//	{

		//		freeThread = -1;
		//		chkThread = 0;
		//		DWORD dwCreateFlags = 0;
		//		while (freeThread == -1 && pBird != 0)
		//		{
		//			if (thisThread[chkThread].Busy == FALSE)
		//			{
		//				freeThread = chkThread;
		//				thisThread[freeThread].Busy = TRUE;
		//				thisThread[freeThread].ThisBird = pBird;
		//				thisThread[freeThread].WaitSignal = CUST_THREAD_RENDER;//non zero to fire
		//				WakeByAddressSingle(&thisThread[freeThread].WaitSignal);
		//			}
		//			chkThread++;
		//			//wait if no threads free
		//			if (chkThread >= NumberOfThreads && freeThread == -1)
		//			{
		//				WaitOnAddress(&pGlbs->ThreadStackHold, &ThreadComparisonValue, sizeof(ULONG), 5);
		//				pGlbs->ThreadStackHold = 0;
		//				chkThread = 0;
		//			}
		//		}
		//	}
		//	cnt++;

		//	if ( (pBird->Next == 0) || (cnt >= pGlbs->BirdsCount) )
		//		break;
		//	pBird = pBird->Next;
		//}



		while (cnt <= pGlbs->BirdsCount)
		{
			if (pBird->OnCreen)
			{
				D3DDevice->SetTransform(D3DTS_WORLD, &(pBird->WorldTrans));
				D3DDevice->SetMaterial(&pBird->mtrlCol);

				if (pGlbs->ShowShip.bval)
				{
					for (UINT i = 0; i < Mtrls.size(); i++)
					{
						D3DDevice->SetMaterial(&Mtrls[i]);
						D3DDevice->SetTexture(0, myTextures[i]);
						if (i == 0)
						{
							Mtrls[i].Ambient = pBird->mtrlCol.Ambient;
							Mtrls[i].Power = pBird->mtrlCol.Power;
						}
						Spccrft->DrawSubset(i);
					}
				}
				else
				{
					Cylinder->DrawSubset(0);
				}

				if ( (NumberTog.bval) || (pBird->ID == MouseBird) )
				{
					ZeroMemory(&MobString, sizeof(MobString));
					sprintf_s(MobString, "%u", pBird->ID);
					RECT rect = { (LONG)pBird->ScrPos.x, (LONG)pBird->ScrPos.y, Width, Height };
					::Font->DrawText(0, MobString, -1, &rect, DT_TOP | DT_LEFT, 0xffffffff);
				} //(NumberTog)

				if (pGlbs->EnvTog.bval && pBird->NoOtherMobs)
				{
					Mob* OB = 0;
					int OtherBirdCnt = 0;
					int Linecount = 0;
					ZeroMemory(LineBuff, sizeof(LineBuff));
					LineBuff[0].x = pBird->ScrPos.x;
					LineBuff[0].y = pBird->ScrPos.y;
					LineBuff[0].z = pBird->ScrPos.z;
					LineBuff[0].col = d3d::BLACK;
					while (OtherBirdCnt < pBird->NoOtherMobs)
					{
						OB = pBird->ClosestMob[OtherBirdCnt];
						if (OB)
						{
							if (OB->OnCreen)
							{
								Linecount++;
								LineBuff[Linecount].x = (OB->ScrPos.x + pBird->ScrPos.x)/2;
								LineBuff[Linecount].y = (OB->ScrPos.y + pBird->ScrPos.y)/2;
								LineBuff[Linecount].z = (OB->ScrPos.z + pBird->ScrPos.z)/2;
								LineBuff[Linecount].col = pBird->ClosestCol[OtherBirdCnt];
							}
						}
						OtherBirdCnt++;
					}
					if (Linecount)
					{
						DWORD TFVF;
						void* pVideoRam;
						HRD(v_buffer->Lock(0, 0, (void**)&pVideoRam, D3DLOCK_DISCARD));    // lock the vertex buffer
						memcpy(pVideoRam, LineBuff, sizeof(LineVertex) * (Linecount + 1));    // copy the vertices to the locked buffer
						HRD(v_buffer->Unlock());    // unlock the vertex buffer

						//D3DINDEXBUFFER_DESC indBufDesc;
						HRD(D3DDevice->GetFVF(&TFVF));
						//D3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
						HRD(D3DDevice->SetFVF(LineVertexFVF));
						HRD(D3DDevice->SetStreamSource(0, v_buffer, 0, sizeof(LineVertex)));
						HRD(D3DDevice->SetIndices(i_buffer));
						//i_buffer->GetDesc(&indBufDesc);
						HRD(D3DDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, Linecount * 2, 0, Linecount));
						HRD(D3DDevice->SetFVF(TFVF));
					}
				}
			}


			cnt++;
			pBird = &Bird[cnt];
			if (cnt > pGlbs->BirdsCount)
				break;
		}//while (cnt < BirdsCount)
		
		 
		// Render predior
		//pBird= &Pred[0];
		//Device->SetTransform(D3DTS_WORLD, &(pBird->WorldTrans));
		//Device->SetMaterial(&pBird->mtrlCol);
		//Cylinder->DrawSubset(0);
		//Device->EndScene();


		ShowEvVars();
		//DumpLL();
		Show_FramesPS();
		D3DDevice->EndScene();
		D3DDevice->Present(0, 0, 0, 0);
		D3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, d3d::BLACK, 1.0f, 0);


//Bird Movement
		
		LARGE_INTEGER tickStarthr;   // Hires point in time
		LARGE_INTEGER tickFinishhr;   // Hires point in time
		QueryPerformanceCounter(&tickStarthr);
		MouseBird = 0;
		// dont scan z list use counter to reduce ailseing
		pBird = &Bird[0];
		ThreadComparisonValue =0;
		pGlbs->ThreadCount = 0;
		freeThread = -1;
		chkThread = 0;
		while (!PauseTog.bval)
		{
			
			freeThread = -1;
			chkThread = 0;
			DWORD dwCreateFlags = 0;
			while (freeThread == -1 && pBird != 0)
			{
				if (thisThread[chkThread].Busy == FALSE)
				{
					freeThread = chkThread;
					thisThread[freeThread].Busy = TRUE;
					thisThread[freeThread].ThisBird = pBird;
					thisThread[freeThread].WaitSignal = CUST_THREAD_MOVEMENT;//non zero to fire
					WakeByAddressSingle(&thisThread[freeThread].WaitSignal);
				}
				chkThread++;
				if (chkThread >= NumberOfThreads && freeThread == -1)
				{
					WaitOnAddress(&pGlbs->ThreadStackHold, &ThreadComparisonValue, sizeof(ULONG), 5);
					pGlbs->ThreadStackHold = 0;
					chkThread = 0;
				}
			}

			if (pBird->Next == 0)
				break;
			pBird = pBird->Next;
		}
		//CudaAnimate(&Glbs, timeDelta);

		freeThread = -1;
		chkThread = 0;
		while (freeThread == -1)
		{
			freeThread = 0;
			for (int i = 0; i < NumberOfThreads; i++)
			{
				if (thisThread[i].Busy == TRUE)
				{
					freeThread = -1;
					break;
				}
			}
		}

		pGlbs->BirdsLLTail = Mob::DynamicSort(&Bird[0],pGlbs->BirdsCount);
		//pGlbs->BirdsLLTail = Mob::Sort(&Bird[0], pGlbs->BirdsCount);
		QueryPerformanceCounter(&tickFinishhr);

		microsecondshr = (float)(tickFinishhr.QuadPart  - tickStarthr.QuadPart )/ticksPerMicroSecondhr.QuadPart;

		if (pGlbs->Snapshot.bval)
		{
			dump_buffer();
			pGlbs->Snapshot.bval = false;
		}

		lastTime = currTime;
		return true;
	}
	else //if device
	{
		return false;
	} //if device

}

void SetUpBirds(void)
{
	for(int t = 0; t<=MAXBIRDS; t++)
	{
		InitBird(&Bird[t]);
		Bird[t].ID = t;
	}
	Mob::InitaliseLinked(&Bird[0], MAXBIRDS);
}

int EnterMsgLoop(  )
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	while(msg.message != WM_QUIT)
	{
		if (!ClosingDouwn) Display();
		if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		} 
	} 

  return true;//msg.wParam;
}

LRESULT CALLBACK WndProc(HINSTANCE hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//static UINT		uTimer = 0;		// Timer for the screen saver
	bool UserKeyUsed = false;
	switch( msg )
	{
		
	case WM_KEYDOWN:
		//since there's boat load of different keys farm em' out
		UserKeyUsed  = (AnalisewParam(wParam)) || (Camera::ProcessKeyInput(wParam, &TheCamera, TimeDeltaAnim));
		if( wParam == VK_ESCAPE ) // escape will always kill
			DestroyWindow(HWND(hwnd));
		break;
	case WM_MOUSEMOVE:
		LastMousePosition = MousePosition;
		MousePosition.x = GET_X_LPARAM(lParam);
		MousePosition.y = GET_Y_LPARAM(lParam);
		PhysicalToLogicalPoint(myAppHWND, &MousePosition);
		switch (wParam)
		{
		case MK_LBUTTON:
			SelectedBird = MouseBird;
			break;
		case MK_RBUTTON:
			LONG dx, dy;
			dx = MousePosition.x - LastMousePosition.x;
			dy = MousePosition.y - LastMousePosition.y;
			TheCamera.strafe((float)dx * 2);
			TheCamera.fly((float)dy * 2);
			break;
		}
		break;
	case WM_LBUTTONDBLCLK:
		pGlbs->BeABirdTog.bval = true;
		break;
	case WM_MOUSEWHEEL:
		TheCamera.walk(GET_WHEEL_DELTA_WPARAM(wParam));
		break;
	case WM_CREATE:				// Creation of window
			DisplayMde = &cDisplayModeData;
		break;
	case WM_DESTROY:			// Cleans up the screen saver window
			ClosingDouwn = true;
			WriteVars();
			Cleanup();
			if(D3DDevice) D3DDevice->Release();
			PostQuitMessage(0);
		break;
	default:
		{
			return DefWindowProc(HWND(hwnd), msg, wParam, lParam);
		}
		break;
	}

	if(!UserKeyUsed)
	{
			return DefWindowProc(HWND(hwnd), msg, wParam, lParam);
	}
	return 0; // consumed?
}

//
// WinMain
//

int WINAPI WinMain(HINSTANCE hinstance,  HINSTANCE prevInstance,  PSTR cmdLine,  int showCmd)
{
	myAppHWND =0;

	if(!d3d::InitWin(hinstance, Width, Height, true, myAppHWND))
	{
 		::MessageBox(0, "InitWin() - FAILED", 0, 0);
 		return -1;
	}
 	ShowWindow(myAppHWND, SW_SHOWMAXIMIZED);

	WINDOWINFO wi;
	//Testline
	GetWindowInfo(myAppHWND , &wi);

	Width = wi.rcClient.right - wi.rcClient.left;
	Height = wi.rcClient.bottom - wi.rcClient.top;
	cDisplayModeData.Height = Height;
	cDisplayModeData.Width = Width;

	UpdateWindow(myAppHWND);

	d3d9Obj = Direct3DCreate9(D3D_SDK_VERSION);

	if( !InitD3D( D3DDEVTYPE_HAL, &D3DDevice, true, myAppHWND, &cDisplayModeData, d3d9Obj) )
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		DestroyWindow(myAppHWND);
	}
	UpdateWindow(myAppHWND);
	
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		DestroyWindow(myAppHWND);
		return -1;
	}

	//////  CUDA
	//cudaError cuStatus;

	//d3d9Obj->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &adapterId);
	//cuStatus = cudaD3D9GetDevice(&CUDAdev, adapterId.DeviceName);
	//if (cuStatus != cudaSuccess) ::MessageBox(0, "CUDA adapterId - FAILED", 0, 0);
	//cudaD3D9SetDirect3DDevice(Device);
	//if (cuStatus != cudaSuccess) ::MessageBox(0, "CUDA Devive reg - FAILED", 0, 0);

	int _set_printf_count_output(
		int enable
	);

	Pick::Stats^ StatsDiag = gcnew Pick::Stats ;
	StatsDiag->Show();
	pGlbs->DlgOpen = true;
	EnterMsgLoop();
#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
#endif

	return 0;

}


