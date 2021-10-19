#include "d3dUtility.h"
#ifndef __d3dUtilityC__
#define __d3dUtilityC__
#include <D3D9Types.h>

// vertex formats
const DWORD d3d::Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

bool d3d::InitWin(HINSTANCE hInstance, int width,  int height,
						bool windowed, HWND& AppHnd)
{
	//
	// Create the main application window.
	//
	if (AppHnd) return true;

	HICON myIcon;
	myIcon  = static_cast<HICON>(LoadImage(0,
		//"C:\\Users\\User\\Documents\\Visual Studio 2012\\Projects\\Intro 3D Game\\Mine\\Pick\\bird-icon5.ico",
		"Pick.ico",
		IMAGE_ICON, 48, 48, LR_LOADFROMFILE | LR_LOADTRANSPARENT ));

	WNDCLASS wc;

 	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	wc.lpfnWndProc   = (WNDPROC)WndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = myIcon; //LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = "XFlockings";

	if( !RegisterClass(&wc) ) 
	{
#ifdef _DEBUG
		DWORD werr;
		werr = GetLastError();
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);

#endif //_DEBUG
		return false;
	}
		
	//Now sends a WM_CREATE
	HWND tHwnd;
	tHwnd = CreateWindow("XFlockings", "Flocking Off", 
		( WS_OVERLAPPEDWINDOW),
		10, 10, width, height,
		0 /*parent hwnd*/, 0 /* menu */, hInstance, 0 /*extra*/); 
	 AppHnd = tHwnd;
	if( !&AppHnd )
	{

#ifdef _DEBUG
		DWORD werr;
		werr = GetLastError();

		::MessageBox(NULL, "CreateWindow() - FAILED", 0, 0);

#endif //_DEBUG
		return false;
	}
	return true;
}

	//
	// Init D3D: 
	//


bool  InitD3D(D3DDEVTYPE deviceType, IDirect3DDevice9** device, bool windowed, HWND AppHnd, D3DDISPLAYMODE *DispMode, IDirect3D9* d3d9)
{
	HRESULT hr = 0;
	
	// Step 1: Create the IDirect3D9 object.
	if  (!D3DXCheckVersion(D3D_SDK_VERSION, D3DX_SDK_VERSION))//(D3DXGetDriverLevel(device)<900)
	{

		int mbRetVal;
		mbRetVal = ::MessageBox(0, "The correct version of DirectX9.0c is missing. \n Would you like to go to the update site? \n (DirectX End-User Runtime)", "Graphics Issue", MB_OKCANCEL);
		if (mbRetVal == IDOK)
		{
				ShellExecute(0, "open","https://www.microsoft.com/en-GB/download/details.aspx?id=34429", 0, 0, SW_SHOWNORMAL);
		}
		//return false;
	}



    if( d3d9 == NULL)
	{
		::MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}


	// Step 2: Check for hardware vp.

	D3DCAPS9 caps;
	hr = d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	int vp = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// Step 3: Fill out the D3DPRESENT_PARAMETERS structure.
	hr = d3d9->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, DispMode );
	DWORD QualityLevels = 0;
	hr = d3d9->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, deviceType, DispMode->Format, windowed, D3DMULTISAMPLE_8_SAMPLES, &QualityLevels);

	if (hr != S_OK)
	{
		::MessageBox(0, "GetAdapterDisplayMode() - FAILED", 0, 0);
		return false;
	}
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = 0;//DispMode->Width;
	d3dpp.BackBufferHeight = 0;//DispMode->Height;
	d3dpp.BackBufferFormat           = DispMode->Format;
	d3dpp.BackBufferCount            = 1;
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_8_SAMPLES;
	d3dpp.MultiSampleQuality         = QualityLevels - 1;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	d3dpp.hDeviceWindow              = AppHnd;
	d3dpp.Windowed                   = windowed;
	d3dpp.EnableAutoDepthStencil     = true; 
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
	d3dpp.Flags                      = 0;
	if (windowed)
	{ 	d3dpp.FullScreen_RefreshRateInHz = 0; }
	else
	{	d3dpp.FullScreen_RefreshRateInHz = DispMode->RefreshRate; }
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;

	
	// Step 4: Create the device.

	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		deviceType,         // device type
		 AppHnd,       // window associated with device
		vp,                 // vertex processing
	    &d3dpp,             // present parameters
	    device);            // return created device

	if( FAILED(hr) )
	{
		// try again using a 16-bit depth buffer
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		
		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			deviceType,
			 AppHnd,
			vp,
			&d3dpp,
			device);

		if( FAILED(hr) )
		{
			d3d9->Release(); // done with d3d9 object

#ifdef _DEBUG
			::MessageBox(0, "CreateDevice() - FAILED", 0, 0);

#endif //_DEBUG
			return false;
		}
	}
	return true;
}



D3DLIGHT9 d3d::InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_DIRECTIONAL;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Direction = *direction;

	return light;
}

D3DLIGHT9 d3d::InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_POINT;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}

D3DLIGHT9 d3d::InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_SPOT;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Direction = *direction;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta        = 0.5f;
	light.Phi          = 0.7f;

	return light;
}

D3DMATERIAL9 d3d::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient  = a;
	mtrl.Diffuse  = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power    = p;
	return mtrl;
}

float d3d::randf(void)
	{
		return rand()/32767.0f;
	}

d3d::BoundingBox::BoundingBox()
{
	// infinite small 
	_min.x = -200; //d3d::INFINITY;
	_min.y = -200; //d3d::INFINITY;
	_min.z = -150; //d3d::INFINITY;

	_max.x = 200; //d3d::INFINITY;
	_max.y = 200; //d3d::INFINITY;
	_max.z = 250; //d3d::INFINITY;
}

bool d3d::BoundingBox::isPointInside(D3DXVECTOR3& p)
{
	if( p.x >= _min.x && p.y >= _min.y && p.z >= _min.z &&
		p.x <= _max.x && p.y <= _max.y && p.z <= _max.z )
	{
		return true;
	}
	else
	{
		return false;
	}
}

d3d::BoundingSphere::BoundingSphere()
{
	_radius = 0.0f;
}

bool d3d::DrawSphere(IDirect3DDevice9* Device, const D3DXVECTOR3 Vec, const float radius, const float Tranparency, const D3DMATERIAL9 Col)
{
	static ID3DXMesh* SphereMesh = 0;

	if( Device != 0 )
	{

		D3DXMATRIX SphereTransform;
		D3DXMATRIX TempMatrix;

		if (SphereMesh == 0)
			D3DXCreateSphere(Device, 1, 10, 10, &SphereMesh, 0);

		D3DXMatrixIdentity(&SphereTransform);
		D3DXMatrixScaling(&SphereTransform, radius, radius, radius);
		D3DXMatrixTranslation(&TempMatrix, Vec.x, Vec.y, Vec.z);
		D3DXMatrixMultiply(&SphereTransform,&SphereTransform,&TempMatrix);
		Device->SetTransform(D3DTS_WORLD, &SphereTransform);

		D3DMATERIAL9 ColTemp = Col;
		ColTemp.Diffuse.a = Tranparency; 
		Device->SetMaterial(&ColTemp);
		if (SphereMesh)		SphereMesh->DrawSubset(0);
	}
	else
	{
		// destroy sphere mesh
		if (SphereMesh)
			d3d::Release<ID3DXMesh*>(SphereMesh);
	}
	return true;
}

bool d3d::DrawBasicScene(IDirect3DDevice9* device, float scale)
{
	static IDirect3DVertexBuffer9* floor  = 0;
	static IDirect3DTexture9*      tex    = 0;
	static ID3DXMesh*              pillar = 0;

	HRESULT hr = 0;

	if( device == 0 )
	{
		if( floor && tex && pillar )
		{
			// they already exist, destroy them
			d3d::Release<IDirect3DVertexBuffer9*>(floor);
			d3d::Release<IDirect3DTexture9*>(tex);
			d3d::Release<ID3DXMesh*>(pillar);
		}
	}
	else if( !floor && !tex && !pillar )
	{
		// they don't exist, create them
		device->CreateVertexBuffer(
			6 * sizeof(d3d::Vertex),
			0, 
			d3d::Vertex::FVF,
			D3DPOOL_MANAGED,
			&floor,
			0);

		Vertex* v = 0;
		floor->Lock(0, 0, (void**)&v, 0);

		v[0] = Vertex(-20.0f, -2.5f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v[1] = Vertex(-20.0f, -2.5f,  20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v[2] = Vertex( 20.0f, -2.5f,  20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		v[3] = Vertex(-20.0f, -2.5f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v[4] = Vertex( 20.0f, -2.5f,  20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v[5] = Vertex( 20.0f, -2.5f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

		floor->Unlock();

		D3DXCreateCylinder(device, 0.5f, 0.5f, 5.0f, 20, 20, &pillar, 0);

		D3DXCreateTextureFromFileA(
			device,
			"desert.bmp",
			&tex);
	}
	else
	{
		//
		// Pre-Render Setup
		//
		device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		D3DXVECTOR3 dir(0.707f, -0.707f, 0.707f);
		D3DXCOLOR col(1.0f, 1.0f, 1.0f, 1.0f);
		D3DLIGHT9 light = d3d::InitDirectionalLight(&dir, &col);

		device->SetLight(0, &light);
		device->LightEnable(0, true);
		device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		device->SetRenderState(D3DRS_SPECULARENABLE, true);

		//
		// Render
		//

		D3DXMATRIX T, R, P, S;

		D3DXMatrixScaling(&S, scale, scale, scale);

		// used to rotate cylinders to be parallel with world's y-axis
		D3DXMatrixRotationX(&R, -D3DX_PI * 0.5f);

		// draw floor
		D3DXMatrixIdentity(&T);
		T = T * S;
		device->SetTransform(D3DTS_WORLD, &T);
		device->SetMaterial(&d3d::WHITE_MTRL);
		device->SetTexture(0, tex);
		device->SetStreamSource(0, floor, 0, sizeof(Vertex));
		device->SetFVF(Vertex::FVF);
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
		
		// draw pillars
		device->SetMaterial(&d3d::BLUE_MTRL);
		device->SetTexture(0, 0);
		for(int i = 0; i < 5; i++)
		{
			D3DXMatrixTranslation(&T, -5.0f, 0.0f, -15.0f + (i * 7.5f));
			P = R * T * S;
			device->SetTransform(D3DTS_WORLD, &P);
			pillar->DrawSubset(0);

			D3DXMatrixTranslation(&T, 5.0f, 0.0f, -15.0f + (i * 7.5f));
			P = R * T * S;
			device->SetTransform(D3DTS_WORLD, &P);
			pillar->DrawSubset(0);
		}
	}
	return true;
}
 #endif // __d3dUtilityC__