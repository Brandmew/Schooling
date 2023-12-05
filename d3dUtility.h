

#ifndef __d3dUtilityH__
#define __d3dUtilityH__

#include <d3dx9.h>
#include <string>
#include <limits>
#include <D3D9Types.h>

#ifdef NDEBUG
#define HRD(x) (x)
#else
#define HRD(x) if(FAILED(x)) DebugBreak()
#endif // DEBUG

LRESULT CALLBACK WndProc(HINSTANCE hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int EnterMsgLoop();
bool InitD3D(D3DDEVTYPE ,	IDirect3DDevice9** , bool , HWND AppHnd, D3DDISPLAYMODE *DispMode, IDirect3D9* d3d9Ob);


namespace d3d
{
	bool InitWin(HINSTANCE hwnd, int width, int height, bool windowed, HWND& AppHnd);

	template<class T> void Release(T t)
	{
		if( t )
		{
			t->Release();
			t = 0;
		}
	}
		
	template<class T> void Delete(T t)
	{
		if( t )
		{
			delete t;
			t = 0;
		}
	}

	// Random Flaot
	float randf(void);

	//
	// Colors
	//
	const D3DXCOLOR      WHITE( D3DCOLOR_XRGB(255, 255, 255) );
	const D3DXCOLOR      BLACK( D3DCOLOR_XRGB(  0,   0,   0) );
	const D3DXCOLOR        RED( D3DCOLOR_XRGB(255,   0,   0) );
	const D3DXCOLOR      GREEN( D3DCOLOR_XRGB(  0, 255,   0) );
	const D3DXCOLOR       BLUE( D3DCOLOR_XRGB(  0,   0, 255) );
	const D3DXCOLOR     YELLOW( D3DCOLOR_XRGB(255, 255,   0) );
	const D3DXCOLOR       CYAN( D3DCOLOR_XRGB(  0, 255, 255) );
	const D3DXCOLOR    MAGENTA( D3DCOLOR_XRGB(255,   0, 255) );

	//
	// Lights
	//

	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
	D3DLIGHT9 InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color);
	
	
	//
	// Materials
	//

	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

	const D3DMATERIAL9 WHITE_MTRL  = InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);
	const D3DMATERIAL9 RED_MTRL    = InitMtrl(RED, RED, RED, BLACK, 2.0f);
	const D3DMATERIAL9 GREEN_MTRL  = InitMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f);
	const D3DMATERIAL9 BLUE_MTRL   = InitMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);
	const D3DMATERIAL9 CYAN_MTRL = InitMtrl(CYAN, CYAN, CYAN, BLACK, 2.0f);
	const D3DMATERIAL9 MAGENTA_MTRL = InitMtrl(MAGENTA, MAGENTA, MAGENTA, BLACK, 2.0f);

	//
	// Bounding Objects / Math Objects
	//

	struct BoundingBox
	{
		BoundingBox();

		bool isPointInside(D3DXVECTOR3& p);

		D3DXVECTOR3 _min;
		D3DXVECTOR3 _max;
	};

	struct BoundingSphere
	{
		BoundingSphere();
		D3DXVECTOR3 _center;
		float       _radius;
		float _radiusSqr;
	};

	struct Ray
	{
		D3DXVECTOR3 _origin;
		D3DXVECTOR3 _direction;
	};

	//
	// Constants
	//

	const float EPSILON  = 0.001f;

	//
	// Drawing
	//

	bool DrawBasicScene(
		IDirect3DDevice9* device,// Pass in 0 for cleanup.
		float scale);            // uniform scale 

	// x,y,z - Position in world co-ord.
	bool DrawSphere(IDirect3DDevice9* Device, const D3DXVECTOR3 Vec,
		const float radius, const float Tranparency, const D3DMATERIAL9 Col);
	//
	// Vertex Structures
	//

	struct Vertex
	{
		Vertex(){}
		Vertex(float x, float y, float z, 
			float nx, float ny, float nz,
			float u, float v)
		{
			_x  = x;  _y  = y;  _z  = z;
			_nx = nx; _ny = ny; _nz = nz;
			_u  = u;  _v  = v;
		}
		float _x, _y, _z;
		float _nx, _ny, _nz;
		float _u, _v;

		static const DWORD FVF;
	};

}

#endif // __d3dUtilityH__
