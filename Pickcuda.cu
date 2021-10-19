//#include "Globals.h"
//#include "Pickcuda.cuh"
//__global__ void AnimateCU(float timedelta, int cnt, int MiddleSpeed)
//{
//	int i = threadIdx.x;
//	if (i < cnt)
//	{
//		//Bird[i].Vel += ((MiddleSpeed - D3DXVec3Length(&Bird[i].Vel))*0.001F)*Bird[i].Vel;
//		Bird[i].Vel += Bird[i].Acc * timedelta;
//		Bird[i].Pos += Bird[i].Vel * timedelta;
//	}
//}
//
//cudaError CudaAnimate(Globs *pGlbs, float timeDelta)
//{
//	int NoBrds = pGlbs->BirdsCount;
//	int AveSpeed = (pGlbs->BirdTopVel + pGlbs->BirdBottomVel) / 2;
//	int NBlks = NoBrds / ThdsPerBlk;
//	AnimateCU <<< NBlks, ThdsPerBlk >>> (timeDelta, NoBrds, AveSpeed);
//	return cudaGetLastError();
//}
