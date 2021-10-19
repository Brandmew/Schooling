
#ifndef __LowestStack_H__
#define __LowestStack_H__
//Written by Andrew Sutcliffe - Use at will 2004ish


template <typename C, typename T, int Size > class LowStack
{
private:
	struct myStack
	{
		C* Obj;
		T Srt;
	};
	myStack Element[Size+1];
	int StkSize;
	int StkCnt;
public:
	int StackPeak;
	LowStack()
	{
		if (Size <= 0)
			return 0;
		StkSize = Size;
		StkCnt = 1;
		for (int c =0; c < StkSize+1; c++)
		{
			Element[c].Obj = 0;
		}
		StackPeak = 0;
	}

	int GetStackSize()
	{
		return StkCnt;
	}

	LowStack(T Value)
	{
		if (Size <= 0)
			return;
		StkSize = Size;
		StkCnt = 1;
		for (int c =0; c < StkSize+1; c++)
		{
			Element[c].Srt = Value;
			Element[c].Obj = 0;
		}
		StackPeak = 0;
	}

	~LowStack()
	{
	}

	bool Add(C* Object, T Sort)
	{
		if(Sort < Element[StkCnt].Srt)
		{
			if (StkCnt < 1)
				StkCnt =1;

			if (StkCnt != StkSize)
				StkCnt++;

			int pnt = StkCnt-1;

			while (pnt !=0 && Sort < Element[pnt].Srt)
			{
				Element[pnt+1].Srt = Element[pnt].Srt;
				Element[pnt+1].Obj = Element[pnt].Obj;
				pnt--;
			}

			pnt++;
			Element[pnt].Obj = Object;
			Element[pnt].Srt = Sort;
			if (StackPeak < StkCnt)
				StackPeak = StkCnt;
			return true;
		}
		else
		{
			return false;
		}
	}

	C* Pull()
	{
		if (StkCnt < 1)
			return 0;
		return Element[--StkCnt].Obj; 
	}

	void DumpStack(void)
	{
		char Var[255];
		char LineOut[255];
		RECT rect = {10, 10, Width, Height};
		int cnt = 0;
		//	Device->Clear(0, 0,D3DCLEAR_TARGET |  D3DCLEAR_ZBUFFER, d3d::BLACK, 1.0f, 0);
		for (int cnt = 0; cnt<= Size; cnt++ )
		{
			ZeroMemory(&LineOut, sizeof(LineOut));
			sprintf_s(LineOut, "% 8X", Element[cnt].Obj);

			ZeroMemory(&Var, sizeof(Var));
			sprintf_s(Var, "% 8X", Element[cnt].Srt);
			lstrcat(LineOut,	Var);
			ZeroMemory(&Var, sizeof(Var));

			Font->DrawText(0, LineOut, -1, &rect, DT_TOP | DT_LEFT, 0xffffffff);
			rect.top += 10;
		}
		//Device->Present(0,0,0,0);
	}
};
#endif __LowestStack_H__ 