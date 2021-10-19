#pragma once

#ifndef __LinkedList_H__
#define __LinkedList_H__

// only to be used on homoginous data blocks as sort uses an
// offset = &(Obj.Element) - &(Obj)

template <class T> class LinkedList
{
//Properties
public:
	struct Node
	{
		T* Obj;
		Node* Next;
		Node* Prev;
		Node(T* t, Node* p, Node* n)
		{
			Obj = t;
			Prev = p;
			Next = n;
		}

		bool SwapLL( Node* A,  Node* B)
		{
			Node* Apn= A->Prev->Next; 
			Node* Ap = A->Prev;
			//Node* An = A->Next;
			//Node* Bp = B->Prev;
			Node* Bn = B->Next;
			Node* Bnp = B->Next->Prev;

			A->Prev->Next = B; //An or B
			B->Next->Prev = A; //Bp or A
			A->Next = Bn;
			B->Next = Apn;
			B->Prev = Ap;
			A->Prev = Bnp;
			return true;
		}

		bool SwapNext(void)
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
				//Penultimate in list - special swap
				Node TNext = *Next;
				Node Tthis = *this;
				*Next = Tthis;
				*this = TNext;
				Tthis.Next->Next = TNext.Next; //0
				Tthis.Next->Prev = TNext.Prev;
				TNext.Prev->Next = Tthis.Next;
				TNext.Prev->Prev = Tthis.Prev;
				return true;
			}
			//Not insaine lets swap!
			return SwapLL(this, Next);
		}
	};
	Node* Head;
	Node* Tail;
private:
	int arrMaxSize;
	int Count;
	Node* Marker;
	int MarkerPos;
private:
	// Swap positions on a linked list
	bool SwapLL( Node* A,  Node* B);
	bool SwapPrev(void);
	bool empty() const { return ( !Head || !Tail ); }
  operator bool() const { return !empty(); }
public:
	void AddHead(T* ptr)
	{
		Head = new Node(ptr, 0 , Head);
		if( Head->Next )
			Head->Next->Prev = Head;
		if( empty() )
			Tail = Head;
		Count++;
	}

	void AddTail(T* ptr)
	{
		Tail = new Node(ptr, Tail, 0);
		if( Tail->Prev )
			Tail->Prev->Next = Tail;
		if( empty() )
			Head = Tail;
		Count++;
	}

	bool SetMarker(int markin)
	{
		if (empty())
			return false;
		Marker = Head;
		MarkerPos = 0;
		int cnt = 0;
		while (cnt<markin)
		{
			Marker = Marker->Next;
			cnt++;
			MarkerPos++;
			if (!Marker)
				return false;
		}
		
		return true;
	}

	T* GetObjMarker()
	{
		return Marker->Obj;
	}
	T* GetNextObjMarker()
	{
		Marker = Marker->Next;
		if (Marker)
		{
			MarkerPos++;
			return Marker->Obj;
		}
		return 0;
	}
	bool Remove(T* ptr);
	bool RemoveTail(void)
	{
		if (!Tail)
			return false;
		Node* Temp = Tail;
		Tail = Tail->Prev;
		if (Tail)
		{
			Tail->Next =0;
			Count--;
			delete Temp;
			return true;
		}
		else
		{
			Head = 0;//last on list
			delete Temp;
			return false;
		}
	}

	bool RemoveHead(void)
	{
		if (!Head)
			return false;
		Node* Temp = Head;
		Head = Head->Next;
		if (Head)
		{
			Head->Prev =0;
			Count--;
		}
		else
			Tail = 0; //last on list
		
			delete Temp;
			return true;
	}
	//Node* Seek(T* ptr);
	LinkedList() { Head = 0; Tail = 0; Marker = 0; }

	~LinkedList(void)
	{
		while (Head)
			RemoveHead();
	}

	//Sort linked list in X order. Returns Tail Addr of Linked list
	//void Sort(); 
	//Single pass through list moving a Node up or down. Returns Tail Addr of Linked list
	void DynamicSort(long Indx);
	// set up poineter on the list & sort. Returns Tail Addr of Linked list

Node* Seek(T* ptr)
{
	Node* Found = Head;
	while (Found->Obj != ptr && Found)
		Found = Found->Next;
	return Found;
}


//Indx = offset = &(Obj.Element) - &(Obj)
template <typename P >
void DynamicSort(long Indx)
{
	Node* pCurNode = Head;
	Node* NodeTail = 0;
	P* pThisObj;
	P* pThatObj;
	while (pCurNode->Next)
	{
		pThisObj = (P*)((long)(pCurNode->Obj)+Indx);
		pThatObj = (P*)((long)(pCurNode->Next->Obj)+Indx);
		if ( (*pThisObj) > (*pThatObj) )
		{
			pCurNode->SwapNext();
		}
		else
		{
			pCurNode = pCurNode->Next;
		}// if Sort
	}//if not EOL
}

//****************This will not work!!
template <typename P > void Sort(long Indx)
{
	int OLPcnt, ILPcnt;
	Node* Cur;
	Node* TempPrev;
	Node* CurNext;
	P* pThisObj;
	P* pThatObj;
	OLPcnt = Count;
	while(OLPcnt > 0)
	{
		ILPcnt = OLPcnt;
		// element 0 has to be done manually or put another "if" in ILP
		// or just ignore it!

		//Set current pointers to bottom of array.
		Cur = Head->Next;
		TempPrev = Head;
		while (ILPcnt > 0)
		{
			//Record tempory Linked List pointers
			CurNext = Cur->Next;
			if (CurNext == 0)
				break;
			pThisObj = (P*)((long)(Cur->Obj)+Indx);
			pThatObj = (P*)((long)(Cur->Next->Obj)+Indx);
			if ( (*pThisObj) > (*pThatObj) )
			{
				TempPrev->Next = CurNext;
				Cur->Next = CurNext->Next;
				CurNext->Next = Cur;
				//Cur remains the same as the data hasn't moved but the position on the linked list has
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
	Cur = Head;
	(Cur->Next)->Prev = Head;
	OLPcnt=0;
	while (OLPcnt < Count)
	{
		Cur = Cur->Next;
		if(Cur->Next !=0)
			(Cur->Next)->Prev = Cur;
		OLPcnt++;
	}
	return ;
}

};

#endif //__LinkedList_H__