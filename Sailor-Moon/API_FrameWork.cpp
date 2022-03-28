// API_FrameWork.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "API_FrameWork.h"
#include"mainGame.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

/*
#include <shlwapi.h>
#include <objidl.h>
#include <GdiPlus.h>
#include <gdiplusimaging.h>
using namespace std;
using namespace Gdiplus;
#pragma comment (lib, "gdiplus.lib")
#pragma comment (lib, "shlwapi.lib")
*/
HINSTANCE m_hInstance;
HWND m_hWnd;
POINT m_ptMouse = { 0,0 };
int zDelta = 0;
bool mouseMove = false;
bool invenPos1_move = false;
bool invenPos2_move = false;
bool invenPos3_move = false;
bool invenPos4_move = false;
bool invenPos5_move = false;
bool invenPos6_move = false;
bool invenPos7_move = false;
bool invenPos8_move = false;
bool invenPos9_move = false;

/*
RECT iwItemList1_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 35, 50, 50);
RECT iwItemList2_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 35, 50, 50);
RECT iwItemList3_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 35, 50, 50);
RECT iwItemList4_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 95, 50, 50);
RECT iwItemList5_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 95, 50, 50);
RECT iwItemList6_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 95, 50, 50);
RECT iwItemList7_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 155, 50, 50);
RECT iwItemList8_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 155, 50, 50);
RECT iwItemList9_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 155, 50, 50);
*/

RECT Menu_RC = RectMake(600, 140, 200, 250);
RECT invenPos1_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 35, 50, 50);
RECT invenPos2_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 35, 50, 50);
RECT invenPos3_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 35, 50, 50);
RECT invenPos4_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 95, 50, 50);
RECT invenPos5_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 95, 50, 50);
RECT invenPos6_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 95, 50, 50);
RECT invenPos7_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 155, 50, 50);
RECT invenPos8_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 155, 50, 50);
RECT invenPos9_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 155, 50, 50);




//메인게임
mainGame mg;



LPTSTR m_lpszClass = TEXT("세일러문");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	m_hInstance = hInstance;

	WNDCLASS wndClass;


	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);


	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = m_lpszClass;
	wndClass.lpszMenuName = NULL;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);


	m_hWnd = CreateWindow(
		WINNAME,		
		WINNAME,			
		WS_OVERLAPPEDWINDOW,	
		WINSTARTX,				
		WINSTARTY,				
		WINSIZEX,				
		WINSIZEY,					
		NULL,					
		(HMENU)NULL,			
		hInstance,			
		NULL);



	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	ShowWindow(m_hWnd, nCmdShow);

	//메인게임 초기화 실패하면 종료
	if (FAILED(mg.init()))
	{
		return 0;
	}




	MSG message;




	//게임용 루프
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{

			if (message.message == WM_QUIT)break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIME->update(60.0f);
			mg.update();
			mg.render();
		}
	}

	//MSG : 운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체
	//TranslateMessage : 키보드 입력 메세지 처리 담당
	//DispatchMessage : 윈ㄷ도우 프로시져에 전달된 메세지를 실제 윈도우에 전달
	//getMessage : 대기상태
	/*while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}*/


	//메시지 루프를 다돌면 해제하자.
	mg.release();

	return message.wParam;

}

void CALLBACK zDeltaReset(HWND hWnd, UINT iMessage, UINT_PTR nIDEvent, DWORD dwTime)
{
	zDelta = 0;
	
	
}
/*
#define DRAW_ANIM   1
static HWND hWnd;
static HDC hMWDC;
static Graphics* pGphcs = NULL;
static Image* pImg = NULL;
static unsigned int nFrm = 0, nFrmCnt = 0;
*/
//윈도우 프로시져 : 메세지를 운영체제에 전달한다. 강제로 운영체제가 호출
//hWnd : 윈도우가 발생한 메세지인지 구분
//imessage : 메세지 구분번호
//wParam : 마우스 버튼의 상태, 키보드 조합키의 상태를 전달한다.
//lParam :  마우스 클릭 좌표를 전달
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//inventoryWindow_RC = RectMakeCenter(700, 265, 200, 250);
	static int x = 600; //프로그램이 시작 되었을때 존재하는 사각형의 x좌표
	static int y = 140; //프로그램이 시작 되었을때 존재하는 사격형의 y좌표
	static int temp_x; //마우스로 사각형을 찍었을때 원래 사각형 시작점의 x좌표와 클릭한부분의 x좌표간의 차이를 저장하는 변수
	static int temp_y; //마우스로 사각형을 찍었을때 원래 사각형 시작점의 y좌표와 클릭한부분의 y좌표간의 차이를 저장하는 변수


	/*RECT invenPos1_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 35, 50, 50);
	RECT invenPos2_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 35, 50, 50);
	RECT invenPos3_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 35, 50, 50);
	RECT invenPos4_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 95, 50, 50);
	RECT invenPos5_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 95, 50, 50);
	RECT invenPos6_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 95, 50, 50);
	RECT invenPos7_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 155, 50, 50);
	RECT invenPos8_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 155, 50, 50);
	RECT invenPos9_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 155, 50, 50);
	*/

	static int invenPos1_x = invenPos1_RC.left;
	static int invenPos1_y = invenPos1_RC.top;
	static int tempInven1_x;
	static int tempInven1_y;

	static int invenPos2_x = invenPos2_RC.left;
	static int invenPos2_y = invenPos2_RC.top;
	static int tempInven2_x;
	static int tempInven2_y;

	static int invenPos3_x = invenPos3_RC.left;
	static int invenPos3_y = invenPos3_RC.top;
	static int tempInven3_x;
	static int tempInven3_y;

	static int invenPos4_x = invenPos4_RC.left;
	static int invenPos4_y = invenPos4_RC.top;
	static int tempInven4_x;
	static int tempInven4_y;

	static int invenPos5_x = invenPos5_RC.left;
	static int invenPos5_y = invenPos5_RC.top;
	static int tempInven5_x;
	static int tempInven5_y;

	static int invenPos6_x = invenPos6_RC.left;
	static int invenPos6_y = invenPos6_RC.top;
	static int tempInven6_x;
	static int tempInven6_y;

	static int invenPos7_x = invenPos7_RC.left;
	static int invenPos7_y = invenPos7_RC.top;
	static int tempInven7_x;
	static int tempInven7_y;


	static int invenPos8_x = invenPos8_RC.left;
	static int invenPos8_y = invenPos8_RC.top;
	static int tempInven8_x;
	static int tempInven8_y;

	static int invenPos9_x = invenPos9_RC.left;
	static int invenPos9_y = invenPos9_RC.top;
	static int tempInven9_x;
	static int tempInven9_y;

	

	static BOOL bMove = FALSE; //마우스의 상태 저장
	switch (iMessage)
	{
	case WM_CREATE:
		//PlaySoundA((LPCSTR)"images/세일러문", NULL, SND_FILENAME | SND_ASYNC);
		//PlaySoundA((LPCSTR)"images/정의", NULL, SND_FILENAME | SND_ASYNC);
		PlaySoundA((LPCSTR)"images/music", NULL, SND_FILENAME | SND_ASYNC);

		/*hMWDC = GetDC(hWnd);
		pGphcs = new Graphics(hMWDC);
		WCHAR path[MAX_PATH];
		GetModuleFileNameW(NULL, path, MAX_PATH);
		PathRemoveFileSpecW(path);
		PathAppendW(path, L"images\\img.gif");
		pImg = new Image(path);
		if (pImg) 
		{
			nFrmCnt = pImg->GetFrameCount(&FrameDimensionTime);
			SetTimer(hWnd, DRAW_ANIM, 100, NULL);
		}*/

		break;
	case WM_MOUSEWHEEL:
		zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		break;
	case WM_MOUSEMOVE:
		if (bMove)
		{
			x = LOWORD(lParam) - temp_x; //마우스가 움직이면서 갱신되는 x좌표에 temp_x를 뺌
			y = HIWORD(lParam) - temp_y; //이부분이 이해가 안가면 주석처리 해서 확인하세요.(-_-; 설명을 잘 못하겠음)

			Menu_RC = RectMake(x, y, 200, 250);
		}

		else if (invenPos1_move)
		{
			invenPos1_x = LOWORD(lParam) - tempInven1_x; //마우스가 움직이면서 갱신되는 x좌표에 temp_x를 뺌
			invenPos1_y = HIWORD(lParam) - tempInven1_y; //이부분이 이해가 안가면 주석처리 해서 확인하세요.(-_-; 설명을 잘 못하겠음)

			invenPos1_RC = RectMake(invenPos1_x, invenPos1_y, 50, 50);
		}

		else if (invenPos2_move)
		{
			invenPos2_x = LOWORD(lParam) - tempInven2_x; //마우스가 움직이면서 갱신되는 x좌표에 temp_x를 뺌
			invenPos2_y = HIWORD(lParam) - tempInven2_y; //이부분이 이해가 안가면 주석처리 해서 확인하세요.(-_-; 설명을 잘 못하겠음)

			invenPos2_RC = RectMake(invenPos2_x, invenPos2_y, 50, 50);
		}

		else if (invenPos3_move)
		{
			invenPos3_x = LOWORD(lParam) - tempInven3_x; //마우스가 움직이면서 갱신되는 x좌표에 temp_x를 뺌
			invenPos3_y = HIWORD(lParam) - tempInven3_y; //이부분이 이해가 안가면 주석처리 해서 확인하세요.(-_-; 설명을 잘 못하겠음)

			invenPos3_RC = RectMake(invenPos3_x, invenPos3_y, 50, 50);
		}

		else if (invenPos4_move)
		{
			invenPos4_x = LOWORD(lParam) - tempInven4_x; //마우스가 움직이면서 갱신되는 x좌표에 temp_x를 뺌
			invenPos4_y = HIWORD(lParam) - tempInven4_y; //이부분이 이해가 안가면 주석처리 해서 확인하세요.(-_-; 설명을 잘 못하겠음)

			invenPos4_RC = RectMake(invenPos4_x, invenPos4_y, 50, 50);
		}

		else if (invenPos5_move)
		{
			invenPos5_x = LOWORD(lParam) - tempInven5_x; //마우스가 움직이면서 갱신되는 x좌표에 temp_x를 뺌
			invenPos5_y = HIWORD(lParam) - tempInven5_y; //이부분이 이해가 안가면 주석처리 해서 확인하세요.(-_-; 설명을 잘 못하겠음)

			invenPos5_RC = RectMake(invenPos5_x, invenPos5_y, 50, 50);
		}

		else if (invenPos6_move)
		{
			invenPos6_x = LOWORD(lParam) - tempInven6_x; //마우스가 움직이면서 갱신되는 x좌표에 temp_x를 뺌
			invenPos6_y = HIWORD(lParam) - tempInven6_y; //이부분이 이해가 안가면 주석처리 해서 확인하세요.(-_-; 설명을 잘 못하겠음)

			invenPos6_RC = RectMake(invenPos6_x, invenPos6_y, 50, 50);
		}

		else if (invenPos7_move)
		{
			invenPos7_x = LOWORD(lParam) - tempInven7_x; //마우스가 움직이면서 갱신되는 x좌표에 temp_x를 뺌
			invenPos7_y = HIWORD(lParam) - tempInven7_y; //이부분이 이해가 안가면 주석처리 해서 확인하세요.(-_-; 설명을 잘 못하겠음)

			invenPos7_RC = RectMake(invenPos7_x, invenPos7_y, 50, 50);
		}

		else if (invenPos8_move)
		{
			invenPos8_x = LOWORD(lParam) - tempInven8_x; //마우스가 움직이면서 갱신되는 x좌표에 temp_x를 뺌
			invenPos8_y = HIWORD(lParam) - tempInven8_y; //이부분이 이해가 안가면 주석처리 해서 확인하세요.(-_-; 설명을 잘 못하겠음)

			invenPos8_RC = RectMake(invenPos8_x, invenPos8_y, 50, 50);
		}

		else if (invenPos9_move)
		{
			invenPos9_x = LOWORD(lParam) - tempInven9_x; //마우스가 움직이면서 갱신되는 x좌표에 temp_x를 뺌
			invenPos9_y = HIWORD(lParam) - tempInven9_y; //이부분이 이해가 안가면 주석처리 해서 확인하세요.(-_-; 설명을 잘 못하겠음)

			invenPos9_RC = RectMake(invenPos9_x, invenPos9_y, 50, 50);
		}

		break;
	case WM_LBUTTONDOWN: //마우스의 왼쪽버튼이 눌렸을때
		int x1, y1;

		x1 = LOWORD(lParam); //마우스의 왼쪽버튼이 눌린 좌표를 저장
		y1 = HIWORD(lParam);
		
		invenPos1_x = invenPos1_RC.left;
		invenPos1_y = invenPos1_RC.top;
		invenPos2_x = invenPos2_RC.left;
		invenPos2_y = invenPos2_RC.top;
		invenPos3_x = invenPos3_RC.left;
		invenPos3_y = invenPos3_RC.top;
		invenPos4_x = invenPos4_RC.left;
		invenPos4_y = invenPos4_RC.top;
		invenPos5_x = invenPos5_RC.left;
		invenPos5_y = invenPos5_RC.top;
		invenPos6_x = invenPos6_RC.left;
		invenPos6_y = invenPos6_RC.top;
		invenPos7_x = invenPos7_RC.left;
		invenPos7_y = invenPos7_RC.top;
		invenPos8_x = invenPos8_RC.left;
		invenPos8_y = invenPos8_RC.top;
		invenPos9_x = invenPos9_RC.left;
		invenPos9_y = invenPos9_RC.top;

		if ((x<x1 && (x + 200)>x1) && (y<y1 && (y + 25)>y1)) //사각형 안에서 마우스의 왼쪽버튼이 클릭되었다면 아래의 명령수행
		{
			temp_x = x1 - x; //사각형 시작부분의 x좌표와 마우스가 클릭된 좌표의 차를 저장함
			temp_y = y1 - y; //사각형 시작부분의 y좌표와 마우스가 클릭된 좌표의 차를 저장함

			bMove = TRUE;
		}

		
		else if ((invenPos1_x<x1 && (invenPos1_x + 50)>x1) && (invenPos1_y<y1 && (invenPos1_y + 50)>y1)) //사각형 안에서 마우스의 왼쪽버튼이 클릭되었다면 아래의 명령수행
		{
			tempInven1_x = x1 - invenPos1_x; //사각형 시작부분의 x좌표와 마우스가 클릭된 좌표의 차를 저장함
			tempInven1_y = y1 - invenPos1_y; //사각형 시작부분의 y좌표와 마우스가 클릭된 좌표의 차를 저장함

			invenPos1_move = TRUE;
		}

		else if ((invenPos2_x<x1 && (invenPos2_x + 50)>x1) && (invenPos2_y<y1 && (invenPos2_y + 50)>y1)) //사각형 안에서 마우스의 왼쪽버튼이 클릭되었다면 아래의 명령수행
		{
			tempInven2_x = x1 - invenPos2_x; //사각형 시작부분의 x좌표와 마우스가 클릭된 좌표의 차를 저장함
			tempInven2_y = y1 - invenPos2_y; //사각형 시작부분의 y좌표와 마우스가 클릭된 좌표의 차를 저장함

			invenPos2_move = TRUE;
		}

		else if ((invenPos3_x<x1 && (invenPos3_x + 50)>x1) && (invenPos3_y<y1 && (invenPos3_y + 50)>y1)) //사각형 안에서 마우스의 왼쪽버튼이 클릭되었다면 아래의 명령수행
		{
			tempInven3_x = x1 - invenPos3_x; //사각형 시작부분의 x좌표와 마우스가 클릭된 좌표의 차를 저장함
			tempInven3_y = y1 - invenPos3_y; //사각형 시작부분의 y좌표와 마우스가 클릭된 좌표의 차를 저장함

			invenPos3_move = TRUE;
		}

		else if ((invenPos4_x<x1 && (invenPos4_x + 50)>x1) && (invenPos4_y<y1 && (invenPos4_y + 50)>y1)) //사각형 안에서 마우스의 왼쪽버튼이 클릭되었다면 아래의 명령수행
		{
			tempInven4_x = x1 - invenPos4_x; //사각형 시작부분의 x좌표와 마우스가 클릭된 좌표의 차를 저장함
			tempInven4_y = y1 - invenPos4_y; //사각형 시작부분의 y좌표와 마우스가 클릭된 좌표의 차를 저장함

			invenPos4_move = TRUE;
		}

		else if ((invenPos5_x<x1 && (invenPos5_x + 50)>x1) && (invenPos5_y<y1 && (invenPos5_y + 50)>y1)) //사각형 안에서 마우스의 왼쪽버튼이 클릭되었다면 아래의 명령수행
		{
			tempInven5_x = x1 - invenPos5_x; //사각형 시작부분의 x좌표와 마우스가 클릭된 좌표의 차를 저장함
			tempInven5_y = y1 - invenPos5_y; //사각형 시작부분의 y좌표와 마우스가 클릭된 좌표의 차를 저장함

			invenPos5_move = TRUE;
		}

		else if ((invenPos6_x<x1 && (invenPos6_x + 50)>x1) && (invenPos6_y<y1 && (invenPos6_y + 50)>y1)) //사각형 안에서 마우스의 왼쪽버튼이 클릭되었다면 아래의 명령수행
		{
			tempInven6_x = x1 - invenPos6_x; //사각형 시작부분의 x좌표와 마우스가 클릭된 좌표의 차를 저장함
			tempInven6_y = y1 - invenPos6_y; //사각형 시작부분의 y좌표와 마우스가 클릭된 좌표의 차를 저장함

			invenPos6_move = TRUE;
		}

		else if ((invenPos7_x<x1 && (invenPos7_x + 50)>x1) && (invenPos7_y<y1 && (invenPos7_y + 50)>y1)) //사각형 안에서 마우스의 왼쪽버튼이 클릭되었다면 아래의 명령수행
		{
			tempInven7_x = x1 - invenPos7_x; //사각형 시작부분의 x좌표와 마우스가 클릭된 좌표의 차를 저장함
			tempInven7_y = y1 - invenPos7_y; //사각형 시작부분의 y좌표와 마우스가 클릭된 좌표의 차를 저장함

			invenPos7_move = TRUE;
		}

		else if ((invenPos8_x<x1 && (invenPos8_x + 50)>x1) && (invenPos8_y<y1 && (invenPos8_y + 50)>y1)) //사각형 안에서 마우스의 왼쪽버튼이 클릭되었다면 아래의 명령수행
		{
			tempInven8_x = x1 - invenPos8_x; //사각형 시작부분의 x좌표와 마우스가 클릭된 좌표의 차를 저장함
			tempInven8_y = y1 - invenPos8_y; //사각형 시작부분의 y좌표와 마우스가 클릭된 좌표의 차를 저장함

			invenPos8_move = TRUE;
		}

		else if ((invenPos9_x<x1 && (invenPos9_x + 50)>x1) && (invenPos9_y<y1 && (invenPos9_y + 50)>y1)) //사각형 안에서 마우스의 왼쪽버튼이 클릭되었다면 아래의 명령수행
		{
			tempInven9_x = x1 - invenPos9_x; //사각형 시작부분의 x좌표와 마우스가 클릭된 좌표의 차를 저장함
			tempInven9_y = y1 - invenPos9_y; //사각형 시작부분의 y좌표와 마우스가 클릭된 좌표의 차를 저장함

			invenPos9_move = TRUE;
		}
		
		break;
	case WM_LBUTTONUP:
		bMove = FALSE;
		invenPos1_move = false;
		invenPos2_move = false;
		invenPos3_move = false;
		invenPos4_move = false;
		invenPos5_move = false;
		invenPos6_move = false;
		invenPos7_move = false;
		invenPos8_move = false;
		invenPos9_move = false;

		break;
		
	case WM_TIMER:
		SetTimer(hWnd, 1, 25, zDeltaReset);

		/*if (wParam == DRAW_ANIM)
		{
			pImg->SelectActiveFrame(&FrameDimensionTime, nFrm);
			Rect DRC(0, 0, pImg->GetWidth(), pImg->GetHeight());
			pGphcs->Clear(Color(128, 128, 128));
			pGphcs->DrawImage(pImg, DRC);
			if (nFrm < (nFrmCnt - 1)) nFrm++; else nFrm = 0;
		}*/

		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		/*
		delete pGphcs;
		delete pImg;
		ReleaseDC(hWnd, hMWDC);
		KillTimer(hWnd, DRAW_ANIM);
		*/
		break;
	}
	return mg.MainProc(hWnd, iMessage, wParam, lParam);
}



//위도우 크기조정 
//클라이언트 영역 사이즈 잡자
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//위 RECT정보로 윈도우 사이즈 셋팅
	SetWindowPos(m_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}