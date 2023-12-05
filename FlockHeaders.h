#ifndef __FlockHeaders__
#define __FlockHeaders__


IDirect3DDevice9* D3DDevice = 0; 
Camera TheCamera(Camera::AIRCRAFT);

int Width  = 1024;
int Height = 768;

D3DXMATRIX View; //Look at matrix
D3DXMATRIX proj; //Projection Matrix
D3DVIEWPORT9 vp;
D3DVIEWPORT9* pvp = &vp;

const char HelpStr1[] = "Birds V0.20 Beta - Help\n\n\
n Toggle bird (N)umbers   e Toggle show (E)nvironment(slow)\n\
p Toggle (P)ause          h Toggle this (H)elp\n\
t (T)oggle Frames/Sec     v Toggle en(v)ronment Numbers \n\
q Snap shot to Pickture.bmp\n\n\
Environment Controls:\n";
const char HelpStr2[] = "Reduce              Increase | Reduce Influence Increase\n\
1  Bird  Count (2000 max) 2  | N/A              N/A\n\
3      Visual Angle       4  | N/A              N/A\n\
5      Roost Sphere       6  | F5               F6\n\
7    Attract Distance     8  | F7               F8\n\
9   Collision Distance    0  | F3               F4\n\
z  Head-on evade angle    x  |\n\
i     Top Velocity        o  |\n\
j   Bottom Velocity       k  |";

const char HelpStr3[] = "Camera control keys: (Not the screen!)\n\
a Left (x-)               d Right (x+)\n\
r Up (y+)                 f Down (y-)\n\
w In (z+)                 s Out (z-)\n\
Left Rotate left          Right Rotate Right\n\
Up Rotate up              Down Rotate Down\n\
< , Rotate Anticlockwise  > . Rotate Clockwise\n\
b Be a (B)ird\n\
c Circle around centre";

const char Nag[] ="Flocking Off \xA9 2011 \nPress H for Help & keys.\n\
Hiring, bugs & suggestions to: bradders12345@gmail.com\n\
(This message will self destruct)";

ID3DXMesh* Cylinder = 0;
ID3DXMesh*                      Spccrft = 0;
std::vector<D3DMATERIAL9>       Mtrls(0);
std::vector<IDirect3DTexture9*> myTextures(0);

#define LineVertexFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
struct LineVertex
{
	float x, y, z;
	float rhw;
	DWORD col;
};
LineVertex LineBuff[NearestMobStackSize +1];
WORD IndexBuf[NearestMobStackSize *2];
LPDIRECT3DVERTEXBUFFER9 v_buffer;
LPDIRECT3DINDEXBUFFER9 i_buffer;

//Offset from start of Mob structure to mob.pos.x for sorting
long MobOffsetx;
//Mob Pred[5];

d3d::BoundingBox RoostBox;

ID3DXFont* Font   = 0;
//ID3DXLine*	Line	= 0;
DWORD FrameCnt    = 0;
DWORD TotalFrameCnt = 0;



//debug timers
LARGE_INTEGER ticksPerMicroSecondhr; //Highres for performence checks
float microsecondspersechr; //Highres for performence checks
float microsecondshr = 0;
LARGE_INTEGER DebugLoopCounter;
float TimeElapsed = 0; // Amimation timer
LARGE_INTEGER lastTime; // for delta times
LARGE_INTEGER timeDelta;
float TimeDeltaAnim = 0;
float timetotal = 0;
float FPS = 0;
float AvgFPS =0;

char FPSString[100];
char MobString[12];

void ShowEvVars(void);
void DumpLL(void);
void dump_buffer();
void VarStr(char *szOutStr, char *szInStr ,float var);

void InitBird(Mob* pB)
{
		*pB = Mob( (d3d::randf()-0.5f)*pGlbs->RoostSphere._radius*4
			,(d3d::randf()-0.5f)*pGlbs->RoostSphere._radius*4
			,(d3d::randf()-0.5f)*pGlbs->RoostSphere._radius*4
			,(float)MAXBIRDVEL );
		D3DXCOLOR TempCol = D3DXCOLOR((d3d::randf()/2)+0.1f,(d3d::randf()/2)+0.1f,(d3d::randf()/2)+0.1f,1);
		pB->mtrlCol = d3d::InitMtrl(TempCol,TempCol,TempCol,TempCol,2.0f);

		pB->GetTransform();
}


void Show_FramesPS()
{
	pGlbs = &Glbs;
	FrameCnt++;
	TimeElapsed += TimeDeltaAnim;
	microsecondspersechr += microsecondshr;
	if(TimeElapsed >= 1.0f)
	{
		char temp[20];
		FPS = (float)FrameCnt / TimeElapsed;
		TotalFrameCnt += FrameCnt;
		timetotal += TimeElapsed;
		AvgFPS = TotalFrameCnt / timetotal;
		ZeroMemory(&FPSString, sizeof(FPSString));
		lstrcat(FPSString,"FPS:");
		ZeroMemory(&temp, sizeof(temp));
		sprintf_s(temp, "%.1f", FPS);
		lstrcat(FPSString,temp);
		lstrcat(FPSString," Avg:");
		ZeroMemory(&temp, sizeof(temp));
		sprintf_s(temp, "%.1f", AvgFPS);
		lstrcat(FPSString,temp);
		lstrcat(FPSString," Math MicroSec:");
		ZeroMemory(&temp, sizeof(temp));
		sprintf_s(temp, "%.0f", microsecondspersechr/TotalFrameCnt);
		lstrcat(FPSString,temp);
		lstrcat(FPSString," DebugLoopCnt:");
		ZeroMemory(&temp, sizeof(temp));
		sprintf_s(temp, "%.2f", (float)DebugLoopCounter.QuadPart/TotalFrameCnt);
		lstrcat(FPSString,temp);
		TimeElapsed = 0.0f;
		FrameCnt    = 0;
	}
	if (pGlbs->FPSTog.bval)
	{
		RECT rect = {1, 1, Width, Height};
		::Font->DrawText(0, FPSString, -1, &rect, DT_TOP | DT_LEFT, 0xffffffff);
	}
	//if (timetotal < 10)
	//{
	//	RECT rect = {0, (int)(Height/2), Width, Height};
	//	::Font->DrawText(0, Nag, -1, &rect, DT_TOP | DT_CENTER, d3d::WHITE);
	//}

}

void ShowEvVars(void)
{
	 //Render environment 
	if (pGlbs->Showballs.bval)
	{
		D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		D3DDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_FALSE);
		d3d::DrawSphere(D3DDevice, D3DXVECTOR3(0,0,0), pGlbs->RoostSphere._radius, 0.5f,d3d::BLUE_MTRL );
		d3d::DrawSphere(D3DDevice, Bird[SelectedBird].Pos, pGlbs->AttractDist, 0.3f,d3d::GREEN_MTRL);
		d3d::DrawSphere(D3DDevice, Bird[SelectedBird].Pos, pGlbs->CollDist, 0.3f,d3d::RED_MTRL);
		D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		D3DDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	}

	if (HelpTog.bval)
	{
		RECT rect = {0, 25, Width, Height};
		::Font->DrawText(0, HelpStr1, -1, &rect, DT_TOP | DT_LEFT, d3d::WHITE);
		rect.top = 127;
		::Font->DrawText(0, HelpStr2, -1, &rect, DT_TOP | DT_LEFT, d3d::WHITE);
		rect.top = 247;
		::Font->DrawText(0, HelpStr3, -1, &rect, DT_TOP | DT_LEFT, d3d::WHITE);
	}

	if (pGlbs->EnvNumTog.bval)
	{
		char szOut[254];
		ZeroMemory(&szOut, sizeof(szOut));
		VarStr(szOut, "Bird Count 1&2:", (float)pGlbs->BirdsCount);
		VarStr(szOut, "\nVisual Angle 3&4:", (pGlbs->VisualAngle / D3DX_PI)*360 );
		VarStr(szOut, "\nRoost Size 5&6:", pGlbs->RoostSphere._radius);
		VarStr(szOut, "\nAttract Dist 7&8:", pGlbs->AttractDist);
		VarStr(szOut, "\nCollision Dist 9&0:", pGlbs->CollDist);
		VarStr(szOut, "\nRoost Influence F5&F6:", pGlbs->RoostInf);
		VarStr(szOut, "\nAttract Influence F7&F8:", pGlbs->AttractInf);
		RECT rect = {1, 1, Width, Height};
		::Font->DrawText(0, szOut, -1, &rect, DT_TOP | DT_RIGHT, d3d::WHITE);
		ZeroMemory(&szOut, sizeof(szOut));
		VarStr(szOut, "\nCollision Influence F3&F4:", pGlbs->CollInf);
		VarStr(szOut, "\nHead-on evade angle Z&X:", (pGlbs->HeadOnEvation / D3DX_PI)*360 );
		VarStr(szOut, "\nTop Velocity I&O:", pGlbs->BirdTopVel );
		VarStr(szOut, "\nBottom Velocity J&K:", pGlbs->BirdBottomVel);
		
		rect.top = 80;
		::Font->DrawText(0, szOut, -1, &rect, DT_TOP | DT_RIGHT, d3d::WHITE);
	}
}

void DumpLL(void)
{
	char Var[255];
	char LineOut[255];
	RECT rect = {10, 10, Width, Height};
	Mob* pB = &Bird[0];
	int cnt = 0;
	//Device->Clear(0, 0,D3DCLEAR_TARGET |  D3DCLEAR_ZBUFFER, d3d::BLACK, 1.0f, 0);
	for (;; )
	{
		ZeroMemory(&LineOut, sizeof(LineOut));
		if (pB!=0)
			sprintf_s(LineOut, "% 8n", ( int* )(pB->Prev));
		else
			sprintf_s(LineOut,10,"Start");
		ZeroMemory(&Var, sizeof(Var));
		sprintf_s(Var, "% 8n", (int*)pB );
		lstrcat(LineOut,	Var);
		ZeroMemory(&Var, sizeof(Var));
		sprintf_s(Var, "% 8n", (int*)pB->Next );
		lstrcat(LineOut,	Var);

		::Font->DrawText(0, LineOut, -1, &rect, DT_TOP | DT_LEFT, 0xffffffff);
		rect.top += 10;
		pB = pB->Next;
		if (!pB) break;
		cnt++;
	}
	ZeroMemory(&LineOut, sizeof(LineOut));
	sprintf_s(LineOut, "% 10X", cnt );
	::Font->DrawText(0, LineOut, -1, &rect, DT_TOP | DT_LEFT, 0xffffffff);
	rect.top += 10;
	//Device->Present(0,0,0,0);
}

//void DumpNewLL(void)
//{
//	char Var[255];
//	char LineOut[255];
//	RECT rect = {10, 10, Width, Height};
//	Testlist.SetMarker(0);
//	Mob* pB = Testlist.GetObjMarker();
//	int cnt = 0;
//	//Device->Clear(0, 0,D3DCLEAR_TARGET |  D3DCLEAR_ZBUFFER, d3d::BLACK, 1.0f, 0);
//	for (;; )
//	{
//		ZeroMemory(&LineOut, sizeof(LineOut));
//		sprintf_s(LineOut, "% 8X", pB );
//
//		ZeroMemory(&Var, sizeof(Var));
//		sprintf_s(Var,"% 4i ",cnt);
//		lstrcat(LineOut,Var);
//
//		ZeroMemory(&Var, sizeof(Var));
//		if (pB!=0)
//			sprintf_s(Var, "% 8f", pB->Pos.x );
//		else
//			sprintf_s(Var,10,"Start");
//		lstrcat(LineOut,Var);
//
//
//		Font->DrawText(0, LineOut, -1, &rect, DT_TOP | DT_LEFT, 0xffffffff);
//		rect.top += 10;
//		pB = Testlist.GetNextObjMarker();
//		if (!pB) break;
//		cnt++;
//	}
//	ZeroMemory(&LineOut, sizeof(LineOut));
//	sprintf_s(LineOut, "% 10X", cnt );
//	Font->DrawText(0, LineOut, -1, &rect, DT_TOP | DT_LEFT, 0xffffffff);
//	rect.top += 10;
//	//Device->Present(0,0,0,0);
//}

void dump_buffer()
{
   IDirect3DSurface9* pRenderTarget=NULL;
   IDirect3DSurface9* pDestTarget=NULL;
	 //static int ndebug;
	 const char file[] = "Pickture.bmp";
   // sanity checks.
   if (D3DDevice == NULL)
      return;

   // get the render target surface.
   HRESULT hr = D3DDevice->GetRenderTarget(0, &pRenderTarget);
   // get the current adapter display mode.
   //hr = pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddisplaymode);

   // create a destination surface.
   hr = D3DDevice->CreateOffscreenPlainSurface( DisplayMde->Width,
                         DisplayMde->Height,
                         DisplayMde->Format,
                         D3DPOOL_SYSTEMMEM,
                         &pDestTarget,
                         NULL);
   //copy the render target to the destination surface.
   hr = D3DDevice->GetRenderTargetData(pRenderTarget, pDestTarget);
   //save its contents to a bitmap file.
   hr = D3DXSaveSurfaceToFile(file,
                              D3DXIFF_BMP,
                              pDestTarget,
                              NULL,
                              NULL);

   // clean up.
   pRenderTarget->Release();
   pDestTarget->Release();
}



void VarStr(char *szOutStr, char *szInStr ,float var)
{
	char	szT[255];
	strncpy_s(szT,254,szInStr,50);
	lstrcat(szOutStr,szT);
	ZeroMemory(&szT, sizeof(szT));
	sprintf_s(szT,"% 6.1f", var);
	lstrcat(szOutStr,szT);
}

bool WriteVars(void)
{
	FILE *fileVars;
	errno_t err;
	if( (err  = fopen_s( &fileVars, "Flocking Off.ini", "w" )) !=0 )
	{
		::MessageBox(0,"Write failed All bets off","err - what!",0);
		return false;
	}
		//BirdsCount = 100;
		fprintf_s( fileVars, "%i %f %f %f %f %f %f %f %f %f",
		pGlbs->BirdsCount,
		pGlbs->VisualAngle, pGlbs->AttractDist, pGlbs->CollDist,	pGlbs->RoostInf,	pGlbs->AttractInf,
		pGlbs->CollInf, pGlbs->HeadOnEvation,	pGlbs->BirdTopVel, pGlbs->BirdBottomVel);
		fprintf_s( fileVars, "%c%c%c%c%c%c%c%c%c",
		NumberTog.cval, PauseTog.cval, pGlbs->EnvTog.cval, pGlbs->EnvNumTog.cval,	HelpTog.cval,
		pGlbs->BeABirdTog.cval, pGlbs->CameraCircleTog.cval, pGlbs->Snapshot.cval, pGlbs->FPSTog.cval);
	fclose(fileVars);
	return true;
}

bool ReadVars(void)
{

	FILE *fileVars;
	errno_t err;
  if( (err  = fopen_s( &fileVars, "Flocking Off.ini", "r" )) !=0 )
	{  
		WriteVars();
		return false;
	}
	else
	{
		int ret_val;
		ret_val = fscanf_s( fileVars, "%i %f %f %f %f %f %f %f %f %f",&pGlbs->BirdsCount,
		&pGlbs->VisualAngle, &pGlbs->AttractDist, &pGlbs->CollDist, &pGlbs->RoostInf,	&pGlbs->AttractInf,
		&pGlbs->CollInf, &pGlbs->HeadOnEvation,	&pGlbs->BirdTopVel, &pGlbs->BirdBottomVel);

		fscanf_s( fileVars, "%c%c%c%c%c%c%c%c%c",
		&NumberTog.cval, 1, &PauseTog.cval, 1, &pGlbs->EnvTog.cval, 1, &pGlbs->EnvNumTog.cval, 1,	&HelpTog.cval, 1,
		&pGlbs->BeABirdTog.cval, 1, &pGlbs->CameraCircleTog.cval, 1, &pGlbs->Snapshot.cval, 1, &pGlbs->FPSTog.cval, 1);
		fclose(fileVars);	
		return true;
	}
}

void ErrorExit(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();
	DWORD outstrlen;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);
	outstrlen = (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR);
	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, outstrlen);
	sprintf_s((LPTSTR)lpDisplayBuf, outstrlen, TEXT("%s failed with error %d: %s"), lpszFunction, dw, lpMsgBuf);
	::MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}

unsigned int __stdcall MBThreadWrap(LPVOID parg)
{
__declspec (thread)static ULONG ThisThreadNumber;
__declspec (thread)static Mob* mymob;
__declspec (thread)static ULONG ThreadComparisonValue = 0;
__declspec (thread)static ULONG CurrectFunction = 0;
//__declspec (thread)static LineVertex LineBuff[NearestMobStackSize + 1];

	pGlbs = &Glbs;

	ThisThreadNumber = *((ULONG*)parg);
	thisThread[ThisThreadNumber].me = ThisThreadNumber;
	if (thisThread[ThisThreadNumber].ID != GetThreadId(thisThread[ThisThreadNumber].ThreadPtr))
	{
		ErrorExit(TEXT("IDs mismatch"));

	}
	
	thisThread[ThisThreadNumber].ActualProc = GetCurrentProcessorNumber();
	++(pGlbs->ThreadCount);
	while (true)
	{
		CurrectFunction = 0;
		pGlbs = &Glbs;
		while (thisThread[ThisThreadNumber].WaitSignal == ThreadComparisonValue)
		{
			WaitOnAddress(&thisThread[ThisThreadNumber].WaitSignal, &ThreadComparisonValue, sizeof(ULONG), INFINITE);
		}
		CurrectFunction = thisThread[ThisThreadNumber].WaitSignal;
		if (CurrectFunction == EXIT_CUST_THREAD) break;
		thisThread[ThisThreadNumber].WaitSignal = 0;
		thisThread[ThisThreadNumber].Busy = TRUE;
		if (thisThread[ThisThreadNumber].ThisBird)
		{
			mymob = thisThread[ThisThreadNumber].ThisBird;
			switch (CurrectFunction)
			{
				case CUST_THREAD_INTALISE:
					//HRD(D3DDevice->CreateVertexBuffer(sizeof(LineBuff), D3DUSAGE_DONOTCLIP, LineVertexFVF, D3DPOOL_MANAGED, &v_buffer, NULL));
					break;

				case CUST_THREAD_MOVEMENT:
				{
					LowStack< Mob, float, NearestMobStackSize > ClosestMobs(FLT_MAX);

					float PosX = mymob->Pos.x;
					float PosY = mymob->Pos.y;
					float PosZ = mymob->Pos.z;
					D3DXVECTOR3 Position = mymob->Pos;

					// Reset Acc and add a Jiggle (call it air turbulance if you will!)
					mymob->Acc.x = (d3d::randf() - 0.5f) / 10;
					mymob->Acc.y = (d3d::randf() - 0.5f) / 10;
					mymob->Acc.z = (d3d::randf() - 0.5f) / 10;

					//Check bounds roost sphere
					if (D3DXVec3LengthSq(&Position) > pGlbs->RoostSphere._radiusSqr)
					{
						//Turn bird (by accellerating toward) origin.
						mymob->Acc -= (Position)*(pGlbs->RoostInf / 500);
					}

					// Create a list (user stack) of birds that can be seen.
					// Scan down & up the sorted linked list to find closest birds.
					// store pointers on the stack. 
					// Box testing is done rather than going straight for sphere
					Mob* OtherBird;
					OtherBird = mymob->Prev;

					D3DXVECTOR3 VectorToOtherBird;
					D3DXVECTOR3 NormalVectorToOtherBird;
					float AngleToOtherBird = 0;
					float LengthToOtherBird = 0;

					///
					while ((OtherBird) && (abs(PosZ - OtherBird->Pos.z) < pGlbs->AttractDist))
					{
						if (abs(PosY - OtherBird->Pos.y) < pGlbs->AttractDist)
						{
							if (abs(PosX - OtherBird->Pos.x) < pGlbs->AttractDist)
							{
								//we are inside the Attract Box, Now test the Attract Sphere.
								VectorToOtherBird = (OtherBird->Pos - Position);
								LengthToOtherBird = D3DXVec3Length(&VectorToOtherBird);
								if (LengthToOtherBird < pGlbs->AttractDist)
								{
									//Are we inside visual arc?
									D3DXVec3Normalize(&NormalVectorToOtherBird, &VectorToOtherBird);
									AngleToOtherBird = acosf(D3DXVec3Dot(&(mymob->NormVel()), &NormalVectorToOtherBird));
									if (AngleToOtherBird < pGlbs->VisualAngle)
									{
										//So Its close enough but is it the closest???
										ClosestMobs.Add(OtherBird, LengthToOtherBird);
									}//Inside Visual Arc
								}//Inside sphere
							} //z test
						} //y test
						OtherBird = OtherBird->Prev;
						DebugLoopCounter.QuadPart++;
					}//test x & Wend

					//same as above but scanning up.
					OtherBird = mymob->Next;
					while ((OtherBird) && (abs(PosZ - OtherBird->Pos.z) < pGlbs->AttractDist))
					{
						if (abs(PosY - OtherBird->Pos.y) < pGlbs->AttractDist)
						{
							if (abs(PosX - OtherBird->Pos.x) < pGlbs->AttractDist)
							{
								//we are inside the Attract Box, Now test the Attract Sphere.
								VectorToOtherBird = (OtherBird->Pos - Position);
								LengthToOtherBird = D3DXVec3Length(&VectorToOtherBird);
								if (LengthToOtherBird < pGlbs->AttractDist)
								{
									//Are we inside visual arc?
									D3DXVec3Normalize(&NormalVectorToOtherBird, &VectorToOtherBird);
									AngleToOtherBird = acosf(D3DXVec3Dot(&(mymob->NormVel()), &NormalVectorToOtherBird));
									if (AngleToOtherBird < pGlbs->VisualAngle)
									{
										//So Its close enough but is it the closest???
										ClosestMobs.Add(OtherBird, LengthToOtherBird);
									}//Inside Visual Arc
								}//Inside sphere
							} //z test
						} //y test
						OtherBird = OtherBird->Next;
						DebugLoopCounter.QuadPart++;
					}// Wend

					//Now do something with the stack.

					int cnt = 0;
					int BirdsSeen = ClosestMobs.GetStackSize();

					OtherBird = ClosestMobs.Pull();
					while (OtherBird)
					{
						D3DXVECTOR3 AccTemp;
						VectorToOtherBird = (OtherBird->Pos - Position);
						D3DXVec3Normalize(&NormalVectorToOtherBird, &VectorToOtherBird);
						AngleToOtherBird = acosf(D3DXVec3Dot(&(mymob->NormVel()), &NormalVectorToOtherBird));
						// if Velocity angle diffrence > 90deg (pi/2) then "possibly facing"...
						float AngleDifference = acosf(D3DXVec3Dot(&(mymob->NormVel()), &(OtherBird->NormVel())));
						D3DXCOLOR tempCol = d3d::CYAN;
						AccTemp = D3DXVECTOR3(0, 0, 0);
						float LengthToOtherBird = D3DXVec3Length(&VectorToOtherBird);
						mymob->UtilityNo = 0;
						if (LengthToOtherBird < pGlbs->CollDist)
							// Avoid collision with other bird
						{
							AccTemp -= ((pGlbs->CollDist - LengthToOtherBird)*pGlbs->CollInf)*NormalVectorToOtherBird;
							tempCol = d3d::RED;
						}
						else
						{
							//Attract toward Other Bird
							bool facing = (AngleDifference > (D3DX_PI / 2)) ? true : false;
							if (facing) // is other bird facing us?
							{
								float AngFacingUs = acosf(D3DXVec3Dot(&NormalVectorToOtherBird, &(OtherBird->NormVel())));
								if (AngFacingUs > (D3DX_PI - pGlbs->HeadOnEvation))
								{
									//Head On - Heading toward each other - evade
									AccTemp += ((LengthToOtherBird - pGlbs->CollDist)*pGlbs->AttractInf)*NormalVectorToOtherBird;
									tempCol = d3d::MAGENTA;
								}
								else
								{
									if (AngFacingUs > D3DX_PI / 2)
									{
										//Heading toward each other move away
										AccTemp -= (VectorToOtherBird) * (pGlbs->AttractInf);
										tempCol = d3d::YELLOW;
									}
									else
									{
										//	//Behind and heading away.
										//	AccTemp += (VectorToOtherBird) * (pGlbs->AttractInf);
										tempCol = d3d::WHITE;
									} //AngFacingUs
								}
							}
							else
								//If not facing us attract to other.
							{
								AccTemp += (VectorToOtherBird)* (pGlbs->AttractInf);
								tempCol = d3d::GREEN;
							}
						}

						mymob->Acc += (AccTemp * 10) / (FLOAT)BirdsSeen;
						mymob->ClosestMob[cnt] = OtherBird;
						tempCol.a *= 0.6f;
						mymob->ClosestCol[cnt] = tempCol;

						cnt++;
						OtherBird = ClosestMobs.Pull();
						if (!OtherBird) break;
					}
					mymob->NoOtherMobs = cnt;

					mymob->UtilityNo = cnt;
					mymob->DampenVel((pGlbs->BirdTopVel + pGlbs->BirdBottomVel) / 2);
					mymob->CapVel(pGlbs->BirdTopVel);
					mymob->CollarVel(pGlbs->BirdBottomVel);
					mymob->Animate(TimeDeltaAnim);
					mymob->GetTransform();
				}
				break;

				case CUST_THREAD_DISPLAY:
				{
					//Is it on the screen

					float X, Y, Z;
					D3DXVECTOR2 PntBird;
					D3DXVec3Project(&mymob->ScrPos, &D3DXVECTOR3(0, 0, 0), pvp, &proj, &::View, &mymob->WorldTrans);
					X = mymob->ScrPos.x;
					Y = mymob->ScrPos.y;
					Z = mymob->ScrPos.z;

					float DistamceToMouse = 0;
					if (Z > 0 && X > 0 && Y > 0 && X < Width && Y < Height)
					{
						mymob->OnCreen = TRUE;
						PntBird.x = MousePosition.x - X;
						PntBird.y = MousePosition.y - Y;
						DistamceToMouse = sqrtf(D3DXVec2LengthSq(&PntBird));
						if (DistamceToMouse < CurrentClosestDist)
						{
							CurrentClosestDist = DistamceToMouse;
							MouseBird = mymob->ID;
						}
					}
					else
						mymob->OnCreen = FALSE;
				}
				break;

				case CUST_THREAD_RENDER:
					/// Too unsafe to use!!!
				{
					D3DDevice->SetTransform(D3DTS_WORLD, &(mymob->WorldTrans));
					D3DDevice->SetMaterial(&mymob->mtrlCol);

					if (pGlbs->ShowShip.bval)
					{
						for (UINT i = 0; i < Mtrls.size(); i++)
						{
							D3DDevice->SetMaterial(&Mtrls[i]);
							D3DDevice->SetTexture(0, myTextures[i]);
							if (i == 0)
							{
								Mtrls[i].Ambient = mymob->mtrlCol.Ambient;
								Mtrls[i].Power = mymob->mtrlCol.Power;
							}
							Spccrft->DrawSubset(i);
						}
					}
					else
					{
						Cylinder->DrawSubset(0);
					}

					if ((NumberTog.bval) || (mymob->ID == MouseBird))
					{
						ZeroMemory(&MobString, sizeof(MobString));
						sprintf_s(MobString, "%u", mymob->ID);
						RECT rect = { (LONG)mymob->ScrPos.x, (LONG)mymob->ScrPos.y, Width, Height };
						::Font->DrawText(0, MobString, -1, &rect, DT_TOP | DT_LEFT, 0xffffffff);
					} //(NumberTog)

					if (pGlbs->EnvTog.bval && mymob->NoOtherMobs)
					{
						Mob* OB = 0;
						int OtherBirdCnt = 0;
						int Linecount = 0;
						ZeroMemory(LineBuff, sizeof(LineBuff));
						LineBuff[0].x = mymob->ScrPos.x;
						LineBuff[0].y = mymob->ScrPos.y;
						LineBuff[0].z = mymob->ScrPos.z;
						LineBuff[0].col = d3d::BLACK;
						while (OtherBirdCnt < mymob->NoOtherMobs)
						{
							OB = mymob->ClosestMob[OtherBirdCnt];
							if (OB)
							{
								if (OB->OnCreen)
								{
									Linecount++;
									LineBuff[Linecount].x = (OB->ScrPos.x + mymob->ScrPos.x) / 2;
									LineBuff[Linecount].y = (OB->ScrPos.y + mymob->ScrPos.y) / 2;
									LineBuff[Linecount].z = (OB->ScrPos.z + mymob->ScrPos.z) / 2;
									LineBuff[Linecount].col = mymob->ClosestCol[OtherBirdCnt];
								}
							}
							OtherBirdCnt++;
						}
						if (Linecount)
						{
							DWORD TFVF;
							mymob->pVideoRam = NULL;
							HRD(v_buffer->Lock(0, 0, (void**)&mymob->pVideoRam, D3DLOCK_DISCARD));    // lock the vertex buffer
							memcpy(mymob->pVideoRam, LineBuff, sizeof(LineVertex) * (Linecount + 1));    // copy the vertices to the locked buffer
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
				break;

			}
			/// switch CUST_THREAD_*
			thisThread[ThisThreadNumber].ThisBird = 0;
			thisThread[ThisThreadNumber].Busy = FALSE;
			pGlbs->ThreadStackHold = 1;
			WakeByAddressSingle(&pGlbs->ThreadStackHold);
		}
		else 
		{ 
			thisThread[ThisThreadNumber].Busy = FALSE;
			pGlbs->ThreadStackHold = 1;
			WakeByAddressSingle(&pGlbs->ThreadStackHold);
			Beep(1400,100);
		}
	}
	//MEMORY_BASIC_INFORMATION mbi;
	//VirtualQuery(&mbi, &mbi, sizeof(mbi));
	//// now mbi.AllocationBase = reserved stack memory base address

	//VirtualQuery(mbi.AllocationBase, &mbi, sizeof(mbi));
	//// now (mbi.BaseAddress, mbi.RegionSize) describe reserved (uncommitted) portion of the stack
	//// skip it

	//VirtualQuery((char*)mbi.BaseAddress + mbi.RegionSize, &mbi, sizeof(mbi));
	//// now (mbi.BaseAddress, mbi.RegionSize) describe the guard page
	//// skip it

	//VirtualQuery((char*)mbi.BaseAddress + mbi.RegionSize, &mbi, sizeof(mbi));
	//// now (mbi.BaseAddress, mbi.RegionSize) describe the committed (i.e. accessed) portion of the stack


	--(pGlbs->ThreadCount);
	return 0;

//movemainloop:
//	goto returnfromsubloop;
}


using namespace Pick;
bool AnalisewParam(WPARAM wParam)
{
	switch (wParam)
	{
	case 0x4E: //n
	{	NumberTog.bval = !(NumberTog.bval);	break;}
	case 'Y': 
	{pGlbs->Showballs.bval = !(pGlbs->Showballs.bval);	break;}
	case 0x50: //p
		{	PauseTog.bval = !(PauseTog.bval);	break;}
	case 0x45: //e
		{	pGlbs->EnvTog.bval = !(pGlbs->EnvTog.bval); break;}
	case 0x48://h
		{	HelpTog.bval  = !(HelpTog.bval);break;}
	case 0x54: //t
		{pGlbs->FPSTog.bval  = !(pGlbs->FPSTog.bval);	break;}
	case 0x56://V
		{pGlbs->EnvNumTog.bval  = !(pGlbs->EnvNumTog.bval);	break;}
	case 'B':
		{pGlbs->BeABirdTog.bval  = !(pGlbs->BeABirdTog.bval);	break;}
	case 'C':
		{pGlbs->CameraCircleTog.bval  = !(pGlbs->CameraCircleTog.bval);	break;}
	case 'Q':
		pGlbs->Snapshot.bval = true;	break;
	case 0x31://1
		{
			if (pGlbs->BirdsCount <= 2)
				pGlbs->BirdsCount = 2;
			else
			{	
				*pGlbs->BirdsLLTail = Bird[pGlbs->BirdsCount];
				pGlbs->BirdsCount--;
				pGlbs->BirdsLLTail = Mob::InitaliseLinked(&Bird[0], pGlbs->BirdsCount);
			}
		}
		break;
	case 0x32://2
		{
			if (pGlbs->BirdsCount >= MAXBIRDS)
				pGlbs->BirdsCount = MAXBIRDS;
			else
			{
				pGlbs->BirdsCount++;
				//InitBird(&Bird[pGlbs->BirdsCount]);
				pGlbs->BirdsLLTail = Mob::InitaliseLinked(&Bird[0], pGlbs->BirdsCount);
			}
		}
		break;
	case 0x33://3
		{
			if (pGlbs->VisualAngle <= 0)
				pGlbs->VisualAngle = 0.00001f;
			else
				pGlbs->VisualAngle -= 0.05f;
		}
		break;
	case 0x34://4
		{
			if (pGlbs->VisualAngle >= D3DX_PI)
				pGlbs->VisualAngle = D3DX_PI;
			else
				pGlbs->VisualAngle += 0.05f;
		}
		break;
	case 0x35://5
		{
			if (pGlbs->RoostSphere._radius <= 1)
			{
				pGlbs->RoostSphere._radius = 1.0f;
				pGlbs->RoostSphere._radiusSqr = 1.0f;
			}
			else
			{
				pGlbs->RoostSphere._radius -= 1.0f;
				pGlbs->RoostSphere._radiusSqr = pGlbs->RoostSphere._radius * pGlbs->RoostSphere._radius;
			}
		}
		break;
	case 0x36://6
		{
			if (pGlbs->RoostSphere._radius >= MAXROOSTSIZE)
			{
				pGlbs->RoostSphere._radius = MAXROOSTSIZE;
				pGlbs->RoostSphere._radiusSqr = pGlbs->RoostSphere._radius * pGlbs->RoostSphere._radius;
			}
			else
			{
				pGlbs->RoostSphere._radius += 1.0f;
				pGlbs->RoostSphere._radiusSqr = pGlbs->RoostSphere._radius * pGlbs->RoostSphere._radius;
			}
		}
		break;
	case 0x37://7
		{
			if (pGlbs->AttractDist <= 1)
				pGlbs->AttractDist = 1.0f;
			else
				pGlbs->AttractDist -= 1.0f;
		}
		break;
	case 0x38://8
		{
			if (pGlbs->AttractDist >= pGlbs->AttractDistMax)
				pGlbs->AttractDist = pGlbs->AttractDistMax;
			else
				pGlbs->AttractDist += 1.0f;
		}
		break;
	case 0x39://9
		{
			if (pGlbs->CollDist  <= 1)
				pGlbs->CollDist = 1.0f;
			else
				pGlbs->CollDist -= 1.0f;
		}
		break;
	case 0x30://0
		{
			if (pGlbs->CollDist >= pGlbs->AttractDist)
				pGlbs->CollDist = pGlbs->AttractDist;
			else
				pGlbs->CollDist += 1.0f;
		}
		break;
	case 0x74://F5
		{
			if (pGlbs->RoostInf <= 0)
				pGlbs->RoostInf = 0;
			else
				pGlbs->RoostInf -= 0.1f;
		}
		break;
	case 0x75://F6
		{
			if (pGlbs->RoostInf >= 100)
				pGlbs->RoostInf = 100;
			else
				pGlbs->RoostInf += 0.1f;
		}
		break;
	case 0x76://F7
		{
			if (pGlbs->AttractInf <= 0)
				pGlbs->AttractInf = 0;
			else
				pGlbs->AttractInf -= 0.1f;
		}
		break;
	case 0x77://F8
		{
			if (pGlbs->AttractInf >= 100)
				pGlbs->AttractInf = 100;
			else
				pGlbs->AttractInf += 0.1f;
		}
		break;
	case 0x72://F3
		{
			if (pGlbs->CollInf <= 0)
				pGlbs->CollInf = 0;
			else
				pGlbs->CollInf -= 0.1f;
		}
		break;
	case 0x73://F4
		{
			if (pGlbs->CollInf >= 100)
				pGlbs->CollInf = 100;
			else
				pGlbs->CollInf += 0.1f;
		}
		break;
	case 'Z':
		{
			if (pGlbs->HeadOnEvation <= 0.1f)
				pGlbs->HeadOnEvation = 0.1f;
			else
				pGlbs->HeadOnEvation -= 0.1f;
		}
		break;
	case 'X':
		{
			if (pGlbs->HeadOnEvation >= (D3DX_PI/2))
				pGlbs->HeadOnEvation = (D3DX_PI/2);
			else
				pGlbs->HeadOnEvation += 0.1f;
		}
		break;
	case 'I':
		{
			if (pGlbs->BirdTopVel <= 0.1f)
				pGlbs->BirdTopVel = 0.1f;
			else
				pGlbs->BirdTopVel -= 0.1f;
		}
		break;
	case 'O':
		{
			if (pGlbs->BirdTopVel >= MAXBIRDVEL )
				pGlbs->BirdTopVel = MAXBIRDVEL;
			else
				pGlbs->BirdTopVel += 0.1f;
		}
		break;
	case 'K':
		{
			if (pGlbs->BirdBottomVel >= pGlbs->BirdTopVel)
				pGlbs->BirdBottomVel = pGlbs->BirdTopVel;
			else
				pGlbs->BirdBottomVel += 0.1f;
		}
		break;
	case 'J':
		{
		if (pGlbs->BirdBottomVel <= MINBIRDVEL)
		{
			pGlbs->BirdBottomVel = MINBIRDVEL;
		}
			else
				pGlbs->BirdBottomVel -= 0.1f;
		}
		break;
	case 'M':
		{
			if (!pGlbs->DlgOpen)
			{
				Pick::Stats^ StatsDiag = gcnew Pick::Stats ;
				StatsDiag->Show();
				pGlbs->DlgOpen = true;
			}
		}
		break;
	default:
		return false;
	}
	return true;
}
#endif __FlockHeaders__