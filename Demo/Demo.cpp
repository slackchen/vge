// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define VGE_USE_MEMORY_MANAGE
#include <Vge.h>

using namespace Vge;

template <class T>
T* New()
{
	string name = typeid(T).name();
	return new T;
}

template <class T>
T* NewZero()
{
	string name = typeid(T).name();
	void* p = malloc(sizeof(T));
	memset(p, 0, sizeof(T));
	new(p)T;
	return (T*)p;
}


class TestObj : public Object
{
public:

	TestObj()
	{
		int a = 1;
	}
	~TestObj()
	{

	}

	void DoTest()
	{

	}

	void DoTest2(int i)
	{

	}

	int a;
};

typedef SharedPtr<TestObj> TestObjPtr;

class BBB : public TestObj
{
public:
	BBB()
	{

	}
};
class DemoWindow : public Window
{
public:
	Font* mFont;
	Font* mFont24;
	FPSCounter fps;

	DemoWindow(Frame* frame)
		: Window(frame)
	{
		SetClientSize(Size(800, 600));
		SetFullScreen(false);
		SetVsync(false);
	}

	virtual void OnCreated()
	{
		SetWindowText(VT("Vge Demo"));

		Graphics* g = GetGraphics();

		mFont = g->CreateFont(VT(""), 20);
		mFont24 = g->CreateFont(VT("黑体"), 24);

		Array<int> intArray;
		//intArray.Resize(6);
		intArray.Add(1);
		intArray.Add(2);
		intArray.Add(3);

		for (Array<int>::Iterator i = intArray.First() ; i != intArray.Last(); ++i)
			Console::PrintLine(StringUtil::ToString(*i));

		Console::PrintLine(VT(""));

		intArray.Remove(2);
		intArray.Remove(1);
		intArray.Remove(0);

		for (dword i = 0 ; i < intArray.Length(); ++i)
			Console::PrintLine(StringUtil::ToString(intArray[i]));

		Console::PrintLine(VT(""));

		intArray.Add(3);

		intArray.Clear();

		List<int> intList;
		intList.Add(1);
		intList.Add(2);
		intList.Add(3);

		List<int>::Iterator it = intList.First();
		while (it != intList.Last())
		{
			Console::PrintLine(StringUtil::ToString(*it));
			it++;
		}

		intList.Remove(2);
		intList.Remove(1);
		intList.Remove(0);

		intList.Add(3);

		it = intList.First();
		while (it != intList.Last())
		{
			Console::PrintLine(StringUtil::ToString(*it));
			it++;
		}

		Map<int, int> mapList;
		mapList[1] = 1;

		Map<int, int>::Iterator itMap = mapList.Find(7);
		mapList[2] = 2;
		mapList[5] = 5;
		mapList[7] = 7;

		itMap = mapList.Find(7);

		mapList[3] = 3;
		mapList[6] = 6;
		mapList[4] = 4;

		itMap = mapList.Find(7);

		for (Map<int, int>::Iterator it = mapList.First();
			it != mapList.Last(); it++)
		{
			Console::PrintLine(StringUtil::ToString((*it).mValue));
		}

		Map<string, int> names;
		names.Add("name", 1);


		String str1 = VT("1231.245");

		bool ret1 = StringUtil::CompareWildcard(str1, VT("*.???"));

		bool ret2 = StringUtil::CompareWildcard(str1, VT("abd12355"));

/*		BigNumber a(VT("23234234234234242342432342344"));
		BigNumber b(VT("11111111111111111111111111111"));

		BigNumber c = a + b;

		Console::PrintLine(c.ToString());
*/

//		String str(_T("你看到我了吗？"));
//		FileStream file(_T("c:\\1.txt") );
//#ifdef VGE_UNICODE
//		file.WriteUnicodeFlag();
//#endif
//		file.Write( (Vge::byte*)str.c_str(), ( str.length() + 1 ) * sizeof(vchar));

		Name name(VT("abc"));
		Name name2;
		Name name3(VT("abc"));

		Console::PrintLine(name.GetString());

		//delete new ReferenceObject;

		//class TestThread : public Runable
		//{
		//public:
		//	virtual int Run()
		//	{
		//		for ( int i = 0; i < 100; ++i )
		//		{
		//			Console::PrintLine(VT("Test Thread"));
		//			System::Sleep(300);
		//		}
		//		return 0;
		//	}
		//};

		//TestThread* test = new TestThread;
		//Thread* thread = new Thread( test );

		//for ( int i = 0; i < 100; ++i )
		//{
		//	Console::PrintLine(VT("Main Thread"));
		//	System::Sleep(500);
		//}

		//thread->Terminate();

		//delete thread;
		//delete test;

		class Test
		{
		public:
			Property<Name> Name;

			Property<int> Age;

			VGE_SYNTHESIZE(int, mHeight, Height)

			VGE_SYNTHESIZE_REF(String, mSchool, School)

			typedef int (Test::*Func)(void);

			//Func mFunc;
		};

		Test test;
		test.Name = VT("Adrian");
		test.Age = 30;

		test.Name = String();

		String str = test.Name;

		test.SetSchool(VT("Small four"));
		test.GetSchool();

		str.Format("%d %d %d", 1, 2, 3);


		//----------------------------------------------------

		TestObjPtr p1 = new TestObj;
		TestObjPtr p2 = p1;
		p2->a;
		p1 = p2;
		p1 = p1;
//		p1 = null;
		if (p1 != null)
			int A = 1;
		else
			int b = 1;

		//-----------------------------------------------------

		{
			typedef MultiCall<TestObj, void (TestObj::*)()> TestObjEvent;
			TestObjEvent testEvent;
			testEvent += NewDelegate(p1, &TestObj::DoTest);
			testEvent();
		}

		{
			typedef MultiCall1<TestObj, void (TestObj::*)(int), int> TestObjEvent;
			TestObjEvent testEvent;
			testEvent += NewDelegate(p1, &TestObj::DoTest2);
			testEvent(8);
		}
	}

	virtual void OnDestroy()
	{
		Graphics* g = GetGraphics();

		g->ReleaseFont(mFont);
		g->ReleaseFont(mFont24);
	}

	virtual void Paint(Graphics* g)
	{
		Size clientsize = GetClientSize();

		g->DrawText(mFont, VT("Press Alt+Enter to toggle full screen"), 20+100, 20, Color::Yellow);
		g->DrawText(mFont, VT("Press F6 to switch pixel resolution"), 20+100, 20+30, Color::Yellow);

		StrStream str;
		str << VT("FPS: ") << fps.GetFPS();
		g->DrawText(mFont, str.str().c_str(), 20, 20, Color::Yellow);

		g->DrawText(mFont, VT("class Vge {};"), 200, 200, Color::White);
		g->DrawText(mFont24, VT("if (a == b) ..."), 200, 250, Color::Magenta);

		g->DrawText(mFont, VT("欢迎！"), 200, 300, Color::Yellow);

		g->DrawText(mFont24, VT("The End"), clientsize.width, clientsize.height,
			Color(1.0f, 1.0f, 1.0f), ALIGN_Right | ALIGN_Bottom);

		fps.Update();
	}
};

#if defined _WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
int _tmain(int argc, _TCHAR* argv[])
#endif
{
	try
	{
		String str1 = VT("你好，VGE世界！\n");

		Console::PrintLine(str1);

		//////////////////////////////
		Frame frame;
		DemoWindow* window = new DemoWindow(&frame);
		frame.Run(window);
	}
	catch (VgeException& e)
	{
#ifdef _WIN32
		::MessageBox(NULL, e.What().Str(), VT("Vge Exception caught"), MB_OK | MB_ICONSTOP);
#else
		Console::PrintLine(e.What());
#endif
	}
	catch (...)
	{
		Console::PrintLine(VT("Unknown exception caught!"));
	}

	return 0;
}

