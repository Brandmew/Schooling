#include "LinkedList.h"


template <class T>
bool LinkedList<T>::Remove(T* ptr)
{
	Node* remove = Seek(T* ptr);
	if (!remove)
		//couldn't find
		return false;
	if (!remove->Prev)
	{
		// we hit the head.
		Head = remove->Next;
		if (Head)
		{
			delete remove;
			Head->Prev = 0;
			Count--;
			return true;
		}
		else
			return false;
	}

	if (!remove->Next)
	{
		// we hit the Tail
		Tail = remove->Prev;
		if (Tail)
		{
			delete remove;
			Tail->Next =0;
			Count--;
			return true;
		}
		else
			return false;
	}
	//sanity complete- Now go insaine
	remove->Prev->Next = remove->Next;
	remove->Next->Prev = remove->Prev;
	delete remove;
	Count--;
	return true;
}


 template <class T >bool LinkedList<T>::SwapPrev(void)
{
	// sanity checks
	if (Node::Prev == 0)
	{
		// Already at bottom of list do nothing.
		return false;
	}
	if (Node::Prev->Prev == 0)
	{
		//return false;
		//2nd in list - special swap down
		//as head of list is static - ie Node[0] points to head
		//swap actual values (yes I know, slow big copy)
		Node TPrev = *Node::Prev;
		Node Tthis = *this;
		*Node::Prev = Tthis;
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
