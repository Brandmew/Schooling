#include "Mob.h"
//#include "C:\Users\Brum\Documents\Visual Studio 2012\Projects\Intro 3D Game\Mine\Pick\d3dUtility.h"

Mob StandardMob(void)
{
	return Mob();
}

float randf(void)
	{
		return rand()/32767.0f;
	}

Mob::Mob()
{
	Pos.x = 0.0f;
	Pos.y = 0.0f;
	Pos.z = 16.0f;

	Vel.x = 0.0001f;
	Vel.y = 0.0001f;
	Vel.z = -0.0001f;

	Acc.x = 0.0f;
	Acc.y = 0.0f;
	Acc.z = 0.0f;

	NoOtherMobs = 0;
	Next = 0;
	Prev = 0;
}


Mob::Mob(float x, float y, float z)
{
	Pos.x = x;
	Pos.y = y;
	Pos.z = z;

	Vel.x = 0.0001f;
	Vel.y = 0.0001f;
	Vel.z = -0.0001f;

	Acc.x=0.0f;
	Acc.y=0.0f;
	Acc.z=0.0f;

	NoOtherMobs = 0;
	Next=0;
	Prev=0;
}

Mob::Mob(float x, float y, float z, float maxvel)
{
	Pos.x = x;
	Pos.y = y;
	Pos.z = z;

	Vel.x = (randf()-0.5f)*maxvel*2;
	Vel.y = (randf()-0.5f)*maxvel*2;
	Vel.z = (randf()-0.5f)*maxvel*2;

	Acc.x=0.0f;
	Acc.y=0.0f;
	Acc.z=0.0f;

	NoOtherMobs = 0;
	Next=0;
	Prev=0;
}

Mob::~Mob(void)
{
}

// Returns the Normal of Velocity.
D3DXVECTOR3 Mob::NormVel()
{
	if (Vel == D3DXVECTOR3(0.0f,0.0f,0.0f))
	{
		return D3DXVECTOR3(0.0f,0.0f,-1.0f);
	}
	else
	{
		D3DXVECTOR3 Temp;
		D3DXVec3Normalize(&Temp,&Vel);
		return Temp;
	}
}
void Mob::Animate(float timedelta)
{
	Vel += (Acc * timedelta);
	Pos += (Vel * timedelta);
}

void Mob::CapVel(const float BirdMaxV)
{
	if(D3DXVec3Length(&Vel) > BirdMaxV )
	{
		D3DXVec3Normalize(&Vel,&Vel);
		Vel *= BirdMaxV;
	}
}

void Mob::DampenVel(const float BirdAvgV)
{
	Vel += ((BirdAvgV - D3DXVec3Length(&Vel) )*0.001F)*Vel;
}

void Mob::CollarVel(const float BirdMinV)
{
	if(D3DXVec3Length(&Vel) < BirdMinV )
	{
		D3DXVec3Normalize(&Vel,&Vel);
		Vel *= BirdMinV;
	}
}
// Transform (move from local space to World)
D3DXMATRIX* Mob::GetTransform()
{
		//Rotate bird
		//To produce a rotation between two vectors (To rotate from direction A to
		//direction B), I do the following:
		//Get the angle between the two normal vectors (dot product).
		//Get a vector perpendicular to the two normal vectors (cross product)
		//Then use angle axis rotation, and this works in most cases
		D3DXVECTOR3 RotAxis;
		D3DXMATRIX Rot;
		D3DXVECTOR3 VelN;
		float angle;

		// Calculate axis of rotation
		VelN = NormVel();
	//Note that performing dot or cross products against standard basis vectors 
	//(such as 0,0,1) really end up being equivalent to trivial assignment 
	//operations, and as such you can optimize the code by simplification.  The 
	//result of the code above could as easily be accomplished by:
	//
	//// dot((0,0,1),v) will simply return v.z
	//ret.vRotation.y = acosf(temporary.z);
	//// cross((0,0,1),v) will simply return (-v.y,v.x,0)
	//// thus crossproduct.y is simply temporary.x
	//if (temporary.x<0.0f)
	//    ret.vRotation.y=-ret.vRotation.y;
	//D3DXINLINE FLOAT D3DXVec3Dot
	//    ( CONST D3DXVECTOR3 *pV1, CONST D3DXVECTOR3 *pV2 )
	//    return pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z;
	//						0										0								-1


				//angle = acosf(D3DXVec3Dot(pStandardBasis,&VelN));
		angle = acosf(-(VelN.z));
	//D3DXINLINE D3DXVECTOR3* D3DXVec3Cross
	//    ( D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV1, CONST D3DXVECTOR3 *pV2 )
	//{
	//    D3DXVECTOR3 v;
	//    v.x = pV1->y * pV2->z - pV1->z * pV2->y;
				//		0									-1
	//    v.y = pV1->z * pV2->x - pV1->x * pV2->z;
				//		-1								0
	//    v.z = pV1->x * pV2->y - pV1->y * pV2->x;
				//		0									0
	//
	//    *pOut = v;
	//    return pOut;
	//}
				//D3DXVec3Cross(&RotAxis,pStandardBasis,&VelN);
		RotAxis = D3DXVECTOR3(VelN.y,-VelN.x,0);

		//D3DXVec3Normalize(&RotAxis,&RotAxis);
		D3DXMatrixRotationAxis(&Rot,&RotAxis,angle);
		// Move from origin (local space) to World space
		D3DXMatrixTranslation(&WorldTrans, Pos.x, Pos.y, Pos.z);
		D3DXMatrixMultiply(&WorldTrans,&Rot,&WorldTrans);
		return &WorldTrans;
}

//Get Current XY Screen position from CURRENT Transform Matrix
void Mob::CalcScrXY(CONST D3DVIEWPORT9 *pViewport, CONST D3DXMATRIX *pProjection, CONST D3DXMATRIX *pView)
{
	D3DXVec3Project(&ScrPos,&D3DXVECTOR3(0, 0, 0),pViewport,pProjection,pView,&WorldTrans);
}

//Linked list sort.
Mob* Mob::Sort( Mob* pFirstMob,const int Count)
{
	int OLPcnt, ILPcnt;
	Mob* Cur;
	Mob* TempPrev;
	Mob* CurNext;
	
	OLPcnt = Count;
	while(OLPcnt > 0)
	{
		ILPcnt = OLPcnt;

		//Set current pointers to bottom of array.
		Cur = pFirstMob->Next;
		TempPrev = pFirstMob;
		while (ILPcnt > 0)
		{
			//Record tempory Linked List pointers
			CurNext = Cur->Next;
			if (CurNext == 0)
				break;
			if ( (Cur->Pos.z) > (CurNext->Pos.z) )
			{
				TempPrev->Next = CurNext;
				Cur->Next = CurNext->Next;
				CurNext->Next = Cur;
				//Cur remains the same 
				TempPrev = CurNext;
			}
			else
			{
				TempPrev = Cur;
				Cur = Cur->Next;
			} // end if
			ILPcnt--;
		}// while ILPCnt > 0
		OLPcnt--;
	}//while OLPCnt >0
	// Build Prev pointers
	Cur = pFirstMob;
	(Cur->Next)->Prev = pFirstMob;
	OLPcnt=0;
	while (OLPcnt < Count)
	{
		Cur = Cur->Next;
		if(Cur->Next != 0)
			(Cur->Next)->Prev = Cur;
		OLPcnt++;
	}
	return Cur;
}

//dynamic sort - as pos.x is a float the likelyhood of passing two other mobs is small
//if a mob does, it will get moved on the next pass and so on until it is in order.
Mob* Mob::DynamicSort(Mob* Start, int Count)
{
		int cnt = 0,tcnt = 0;
		Mob* pMob = Start;
		Mob* mobTail = 0;
		while (cnt < Count)
		{
			tcnt = cnt;
			while (tcnt == cnt && pMob)
			{
				if (pMob->Next == 0)
				{
					mobTail = pMob;
					cnt++;
				}
				else
				{
					if (pMob->Pos.z > (pMob->Next)->Pos.z)
					{
						if (!(pMob->SwapNext())) cnt++;
					}
					else
					{
						if (pMob->Prev != 0)
						{
							if (pMob->Pos.z < (pMob->Prev)->Pos.z)
							{
								if (!(pMob->SwapPrev())) cnt++;
							}
							else cnt++;
						}
						else
						{
							cnt++;
						}
					}
				}
			}
			
			pMob++;
		}
		if (mobTail)
			return mobTail;
		else
			return pMob;
}

bool Mob::SwapPrev(void)
{
	// sanity checks
	if (Prev == 0)
	{
		// Already at bottom of list do nothing.
		return false;
	}
	if (Prev->Prev == 0)
	{
		//return false;
		//2nd in list - special swap down
		//as head of list is static - ie Mob[0] points to head
		//swap actual values 
		Mob TPrev = *Prev;
		Mob Tthis = *this;
		*Prev = Tthis;
		*this = TPrev;
		Tthis.Prev->Next = TPrev.Next;
		Tthis.Prev->Prev = TPrev.Prev; //0
		TPrev.Next->Next = Tthis.Next;
		TPrev.Next->Prev = Tthis.Prev;
		return true;
	}
	// sane so... Boooyaaa
	if(!(Prev->SwapNext()))
		return false;
	return true;
}


bool Mob::SwapNext(void)
{
	// sanity checks
	if (Next == 0)
	{
		// Already at top or bottom of list do nothing.
		return false;
	}
	if (Next->Next == 0 || Prev == 0)
	{
		//return false;
		//last in list - special swap
		Mob TNext = *Next;
		Mob Tthis = *this;
		*Next = Tthis;
		*this = TNext;
		Tthis.Next->Next = TNext.Next; //0
		Tthis.Next->Prev = TNext.Prev;
		TNext.Prev->Next = Tthis.Next;
		TNext.Prev->Prev = Tthis.Prev;
		return true;
	}
	//Not insaine lets swap!
	if (!SwapLL(this, Next))
		return false;
	return true;
}


bool Mob::SwapLL( Mob* A,  Mob* B)
{
	Mob* Apn= A->Prev->Next; 
	Mob* Ap = A->Prev;
	Mob* Bn = B->Next;
	Mob* Bnp = B->Next->Prev;

	A->Prev->Next = B; //An or B
	B->Next->Prev = A; //Bp or A
	A->Next = Bn;
	B->Next = Apn;
	B->Prev = Ap;
	A->Prev = Bnp;
	return true;
}



Mob* Mob::InitaliseLinked(Mob* start,int count)
{
	Mob* pMb = start;
	pMb->Prev = 0;
	pMb->Next = (pMb +1);
	for(int t = 1; t<=count; t++)
	{
		pMb++;
		pMb->Prev = (pMb -1);
		pMb->Next = (pMb +1);
	}

	(start + count)->Prev=(start + count-1);
	(start + count)->Next=0;
	return (start + count);	
}
