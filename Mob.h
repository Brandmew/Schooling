#ifndef __Mob_H__
#define __Mob_H__

#include <d3dx9.h>

#define NearestMobStackSize (8)

class Mob
{
public:
	// contructors
	Mob();
	~Mob(void);
	Mob(float x, float y, float z);
	Mob(float x, float y, float z, float maxvel);

	// Methods (Member functions)
	
	// Returns the Normal of Velocity.
	D3DXVECTOR3 NormVel();
	// Animate
	void Animate(float timedelta);
	// Cap Max Velocity
	void CapVel(float BirdMaxVel);
	// Dampen Velocity
	void DampenVel(float BirdMaxVel);
	// Collar Min Velocity
	void CollarVel(const float BirdMinV);
	// Transform (move from local space to World)
	D3DXMATRIX* GetTransform();
	//Get Current XY Screen position from CURRENT Transform Matrix
	void CalcScrXY(const D3DVIEWPORT9 *pViewport, const D3DXMATRIX *pProjection, const D3DXMATRIX *pView);
	//sawp positions on linked list (Cur <-> Next)
	bool SwapNext(void);
	//sawp positions on linked list (Cur <-> Prev)
	bool SwapPrev(void);

	// Mob Acceleration
	D3DXVECTOR3 Acc;
	// Mob Velocity
	D3DXVECTOR3 Vel;
	// Mob Posotion
	D3DXVECTOR3 Pos;
	// Transformation Matrix
	D3DXMATRIX WorldTrans;
	// Screen Position after Transformation.
	D3DXVECTOR3 ScrPos;
	BOOL OnCreen;
	D3DMATERIAL9 mtrlCol;
	int UtilityNo;
	
	//Linked list 
private:
	// Swap positions on a linked list
	bool SwapLL( Mob* A, Mob* B);
public:
	//Sort linked list in X order. Returns Tail Addr of Linked list
	static Mob* Sort(Mob* pFirstMob, const int Count);
	//Single pass through list moving a Mob up or down. Returns Tail Addr of Linked list
	static Mob* DynamicSort(Mob* Start, int Count);
	// set up poineter on the list & sort. Returns Tail Addr of Linked list
	static Mob* InitaliseLinked(Mob* start,int count);
	//Linked List
	Mob* Next;
	Mob* Prev;
	Mob* ClosestMob[NearestMobStackSize];
	D3DXCOLOR ClosestCol[NearestMobStackSize];
	int NoOtherMobs;
	void MoveBird();
};


#endif // __Mob_H__