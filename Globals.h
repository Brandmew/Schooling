#pragma once
#include "d3dUtility.h"
#include "Mob.h"

#define MAXROOSTSIZE ((float) 200)
#define MINBIRDVEL ((int) 5)

const int MAXBIRDVEL = (int)800;

const int MAXBIRDS = (int)10000;

const ULONG EXIT_CUST_THREAD  = 6666;
const int NumberOfThreads = (int)16;
POINT MousePosition;
POINT LastMousePosition;

UINT SelectedBird;
UINT MouseBird;

//int ThdsPerBlk = 256;

//Current Bird Buffer
//static int CurrBB;
////New Bird Buffer
//static int NewBB;

static Mob Bird[MAXBIRDS + 1];

union shareCB 
{
	bool bval;
	char cval;
};

shareCB NumberTog = {false};
shareCB PauseTog = {false};
shareCB HelpTog = {false};

struct myThread
{
	bool Busy;
	Mob* ThisBird;
	int ThisBirdNumner;
	ULONG WaitSignal;
	HANDLE ThreadPtr;
	unsigned int ID;
	SECURITY_INFORMATION Security;
	int me;
	DWORD PrefferedProc;
	DWORD ActualProc;
	DWORD PreviousProc;
};
static myThread thisThread[NumberOfThreads];
static int ThreadParam[NumberOfThreads];

namespace Globals
	
{
	 class Globs {
	public:
		Globs(void);
		~Globs(void);
		int BirdsCount;
		float BirdTopVel;
		float BirdBottomVel;
		float AttractDist;
		float AttractDistMax;
		float CollDist;
		float RoostInf;
		float VisualAngle;
		float AttractInf;
		float CollInf;
		float HeadOnEvation;
		shareCB EnvTog;
		shareCB FPSTog;
		shareCB EnvNumTog;
		shareCB Showballs;
		shareCB BeABirdTog;
		shareCB CameraCircleTog;
		shareCB Snapshot;
		shareCB ShowShip;
		bool DlgOpen;
		d3d::BoundingSphere RoostSphere;
		Mob* BirdsLLTail;
		int ThreadCount;
		ULONG ThreadStackHold;
	};

}
using namespace Globals;
Globs::Globs()
{
	BirdsCount = 60;
	BirdTopVel = 50;
	BirdBottomVel = 20;
	AttractDist = 150;
	AttractDistMax = 1000;
	CollDist = 60;
	RoostInf = 20;
	VisualAngle = D3DX_PI/2;
	AttractInf = 1.5f;
	CollInf = 3.2f;
	HeadOnEvation = D3DX_PI/2;
	EnvTog.bval = false;
	FPSTog.bval = false;
	EnvNumTog.bval = false;
	BeABirdTog.bval = false;
	CameraCircleTog.bval = false;
	Snapshot.bval = false;
	ShowShip.bval = true;
	DlgOpen = false;
	RoostSphere._radius = MAXROOSTSIZE / 2;
	ThreadCount = 0;
}

Globs::~Globs(void)
{
}
