#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <Windowsx.h>
#include <iostream>
#include <conio.h>
#include "Model.h"

HBITMAP hBitmap = NULL;

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Flappy Bird group 5441 Sazonov Anton Borisovich");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global variables
#define G 250;
#define TUBE_COUNT 3///<Number of simultaneously generating tubes 
#define WINDOW_WIDTH 800///< width window
#define WINDOW_HEIGHT 600///< heigt window
int GameOver = 0;
bool pause = false;
int p = 0;
int Score = 0;
int score;
int tmpX = 0, tmpY = 0,tmpV = 0,tmpScore = 0;
int tmpTX[TUBE_COUNT];
int tmpTY[TUBE_COUNT];
//TBird bird;
TTube tubes[TUBE_COUNT];

void DoPhysics(ULONGLONG dT);
void StartGame();


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{ 
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	ULONGLONG prevTime = -1, curTime, deltaT;

	
	StartGame();
	while (TRUE)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
			break;

		curTime = GetTickCount64();
		if (prevTime == -1)
			deltaT = 0;
		else deltaT = curTime - prevTime;
		prevTime = curTime;

		if (!pause&&GameOver==0)
		{
			DoPhysics(deltaT);
		}
		InvalidateRect(hWnd, NULL, 1);
	}

	if (GameOver)
	{	FILE *F;
		char fn[] = "records.txt";
		F = fopen(fn, "a");
		fprintf(F, "%d\n", score);
		fclose(F);
		GameOver = 0;
	}

	return (int)msg.wParam;
}

/*!
\brief  function void StartGame () is designed for the beginning of the start of the game. This function is implemented in the field of generation of pipes
through certain period of time
The function code is as follows:
\code
void StartGame ()
{

srand (GetTickCount ());

for (int i = 0; i <TUBE_COUNT; i ++)
{

tubes [i] = CreateTube (i * (WINDOW_WIDTH / TUBE_COUNT) + WINDOW_WIDTH);
}

}
\endcode
*/
void StartGame()
{

	srand(GetTickCount());

	for (int i = 0; i<TUBE_COUNT; i++)
	{
		
		tubes[i] = CreateTube(i*(WINDOW_WIDTH / TUBE_COUNT) + WINDOW_WIDTH);
	}

}
/*!
\brief 
Function void DoPhysics responsible for all of physics in the game. In this function implements the birds position on the playing field,
check with birds touch the pipe, restart the game, adding points with the passage of a bird pipes.


While the bird touched the brink condition adds to the points each time another point, the condition is satisfied until the end of the game lies,
that is, until the bird has not touched one of the faces.
   \code

    if (GameOver == 0) 
	{Score ++;}

	 \endcode

	 The condition is responsible for checking touch bird horizontal edge. If the bird has touched the brink of the condition is that
	 game over. The process of the game is stopped.
	 \code

	 if (((BIRD_SPOS - BIRD_SIZE) <(tubes [i] .X + tubes [i] .r)) && ((BIRD_SPOS + BIRD_SIZE)> (tubes [i] .X - tubes [i] .r)))
	 {
	 if (((tubes [i] .Y + tubes [i] .r! <ch.y - BIRD_SIZE) && (tubes [i] .Y - tubes [i] .r + GAP_SIZE> ch.y + BIRD_SIZE)) )
	 {
	 GameOver = 1;
	 }
	 }
	 if ((tubes [i] .X <0))
	 {
	 tubes [i] = CreateTube (WINDOW_WIDTH);
	 }
	 \endcode
	 The condition is responsible for checking touch bird vertical face. If the bird has touched the brink of the condition is that
	 game over. The process of the game is stopped.
	 \code

	 if ((WINDOW_HEIGHT - 5 < ch.y - BIRD_SIZE) && (ch.y - BIRD_SIZE < WINDOW_HEIGHT))
	 {
	 if ((tubes[i].X < ch.x) && (ch.x < tubes[i].X))
	 {
	 GameOver = 1;
	 }
	 }
	 \endcode
	 */
void DoPhysics(ULONGLONG dT)
{
	ch.y += ((double)dT / 1000)*ch.vy;
	ch.vy += ((double)dT / 1000) * 2 * G;

	if (ch.y - BIRD_SIZE < 0)
	{
		ch.y = BIRD_SPOS;
	}

	if ((ch.y - BIRD_SIZE) >= WINDOW_HEIGHT)
	{
		GameOver = 1;
	}

	if (GameOver == 1)
	{
		ch.y = WINDOW_HEIGHT - BIRD_SIZE;
		dX = 0;
		score=0;
	}

	if (GameOver == 0){
     
		Score++;
	}
	
		for (int i = 0; i < TUBE_COUNT; i++)
		{
			tubes[i].X += ((double)dT / 1000)*dX;

			if (((BIRD_SPOS - BIRD_SIZE) < (tubes[i].X + tubes[i].r)) && ((BIRD_SPOS + BIRD_SIZE) > (tubes[i].X - tubes[i].r)))
			{
				if (!((tubes[i].Y + tubes[i].r < ch.y - BIRD_SIZE) && (tubes[i].Y - tubes[i].r + GAP_SIZE > ch.y + BIRD_SIZE)))
				{
					GameOver = 1;
				}
			}
			if ((tubes[i].X < 0))
			{
				tubes[i] = CreateTube(WINDOW_WIDTH);
			}
	
			if ((WINDOW_HEIGHT - 5 < ch.y - BIRD_SIZE) && (ch.y - BIRD_SIZE < WINDOW_HEIGHT))
			{
				if ((tubes[i].X < ch.x) && (ch.x < tubes[i].X))
				{
					GameOver = 1;
				}
			}
		}
	}



/*!
\brief This function is responsible for drawing birds, pipes, background playing field and shows all the text in the game.
As it prescribe management in our game.
For control of the game and drawing the background playing field meets the code.
 \code
 switch (message)
	{
	case WM_CREATE: //load picture on background 
		hBitmap = (HBITMAP)LoadImage(hInst, L"1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'R': //Restart game
	    ch.y=100;
		dX=-150;
       for (int i = 0; i<TUBE_COUNT; i++)
	    {tubes[i] = CreateTube(i*(WINDOW_WIDTH / TUBE_COUNT) + WINDOW_WIDTH);}
	    Score=0;
		GameOver=0;
		break;
		case ' ': //Jump birds
			ch.vy = -300;
			break;
		case 'P':  //Pause game
			pause = !(pause);
			break;
		case VK_F5: case 'S': //Save coordinate bird and tube
			tmpX = ch.X;
			tmpY = ch.y;
			tmpV = ch.vy;
			tmpScore = Score;
			//
			for (int i(0); i < TUBE_COUNT;i++)
			{ 
				tmpTX[i] = tubes[i].X;
				tmpTY[i] = tubes[i].Y;
			}			
			break;
		case VK_F8: case 'L': //Load coordinate bird and tube
			ch.X = tmpX;
			ch.y = tmpY;
			ch.vy = tmpV;
			Score = tmpScore;
			//
			for (int i(0); i < TUBE_COUNT; i++)
			{
				tubes[i].X = tmpTX[i];
				tubes[i].Y = tmpTY[i];
			}
			break;

		}
\endcode
This part of the code responsible for drawing tubes and birds. Drawing in WinApi performed using brushes and pens. With feathers, we draw the contours of our
pipes and birds. With a brush paints we figure our color.
 \code
case WM_PAINT:
		//Рисуем здесь 
		RECT rect;
		BITMAP bitmap;
		HDC hdcMem;
		HGDIOBJ oldBitmap;
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		width = rect.right;
		height = rect.bottom;
		backbuffDC = CreateCompatibleDC(hdc);
		backbuffer = CreateCompatibleBitmap(hdc, width, height);
		savedDC = SaveDC(backbuffDC);
		SelectObject(backbuffDC, backbuffer);


		//clear window 
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(backbuffDC, &rect, hBrush);
		DeleteObject(hBrush);
		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		//Рисуем background 
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt(backbuffDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

		//draw tubes
			for (int i = 0; i < TUBE_COUNT; i++)
			{
				hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
				hOldPen = (HPEN)SelectObject(backbuffDC, hPen);
				Rectangle(backbuffDC, tubes[i].X - tubes[i].r, -1, tubes[i].X + tubes[i].r, tubes[i].Y + tubes[i].r);
				Rectangle(backbuffDC, tubes[i].X - tubes[i].r, tubes[i].Y - tubes[i].r + GAP_SIZE, tubes[i].X + tubes[i].r, WINDOW_HEIGHT);
				SelectObject(backbuffDC, hOldPen);
				DeleteObject(hPen);
				hPen = CreatePen(PS_SOLID, tubes[i].r, RGB(0, 255, 0));
				hOldPen = (HPEN)SelectObject(backbuffDC, hPen);
				Rectangle(backbuffDC, tubes[i].X - (tubes[i].r / 2), -1, tubes[i].X + (tubes[i].r / 2), tubes[i].Y + (tubes[i].r / 2));
				Rectangle(backbuffDC, tubes[i].X - (tubes[i].r / 2), tubes[i].Y - (tubes[i].r / 2) + GAP_SIZE, tubes[i].X + (tubes[i].r / 2), WINDOW_HEIGHT);
				SelectObject(backbuffDC, hOldPen);
				DeleteObject(hPen);
			}
		//draw bird
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hOldPen = (HPEN)SelectObject(backbuffDC, hPen);
		Ellipse(backbuffDC, BIRD_SPOS - BIRD_SIZE, ch.y - BIRD_SIZE, BIRD_SPOS + (BIRD_SIZE), ch.y + BIRD_SIZE);
		SelectObject(backbuffDC, hOldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, BIRD_SIZE, RGB(255, 0, 0));
		hOldPen = (HPEN)SelectObject(backbuffDC, hPen);

		Ellipse(backbuffDC, BIRD_SPOS - (BIRD_SIZE / 2), ch.y - (BIRD_SIZE / 2), BIRD_SPOS + (BIRD_SIZE / 2), ch.y + (BIRD_SIZE / 2));

		SelectObject(backbuffDC, hOldPen);
		DeleteObject(hPen);
\endcode
This part of the code responsible for entering text on a screen. To enter text on the screen creates an array of characters. Using this array, we can create the text. If the number of characters exceeds the specified number of the program will display an error. The text displayed on the screen at a certain place and under certain conditions. The implementation is shown below
 \code
WCHAR s[100];
		    
		    wsprintf(s, _T("Press P to get detailed instructions"));
			TextOut(backbuffDC, 10, 10, s, wcslen(s));

		if (pause){
			wsprintf(s, _T("Pause"));
			TextOut(backbuffDC, 350, 250, s, wcslen(s));
			wsprintf(s, _T("R - restart the game   "));
			TextOut(backbuffDC, 20, 440, s, wcslen(s));
			  wsprintf(s, _T("Spacebar - jerk birds"));
			TextOut(backbuffDC, 25, 460, s, wcslen(s));
			  wsprintf(s, _T("S/ L - save / load the coordinates"));
			TextOut(backbuffDC, 30, 480, s, wcslen(s));
			  wsprintf(s, _T("P - pause"));
			TextOut(backbuffDC, 35, 500, s, wcslen(s));
		}
		if (GameOver == 1)
		{
			wsprintf(s, _T("Game over! Restart game"));
			TextOut(backbuffDC, 350, 250, s, wcslen(s));
			wsprintf(s, _T("Press R"));
			TextOut(backbuffDC, 400, 350, s, wcslen(s));
		}
		if (Score / WINDOW_HEIGHT >= 2)
		{
			score = ((Score - 25) / 400) - 2;
			wsprintf(s, _T("Score = %d"),((Score - 20) / 400) - 2);
			TextOut(backbuffDC, 350, 200, s, wcslen(s));
		}
		\endcode
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int savedDC;
	HDC backbuffDC;
	int width, height;
	HBITMAP backbuffer;
	HBRUSH hBrush;
	int xPos, yPos;
	double dx, dy;
	HPEN hPen, hOldPen;
	double alpha, pieX, pieY;
	int r;

	switch (message)
	{
	case WM_CREATE: // load picture on background 
		hBitmap = (HBITMAP)LoadImage(hInst, L"1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'R':
	    ch.y=100;
		dX=-150;
       for (int i = 0; i<TUBE_COUNT; i++)
	    {tubes[i] = CreateTube(i*(WINDOW_WIDTH / TUBE_COUNT) + WINDOW_WIDTH);}
	    Score=0;
		GameOver=0;
		break;
		case ' ':
			ch.vy = -300;
			break;
		case 'P':
			pause = !(pause);
			break;
		case VK_F5: case 'S':
			tmpX = ch.X;
			tmpY = ch.y;
			tmpV = ch.vy;
			tmpScore = Score;
			//
			for (int i(0); i < TUBE_COUNT;i++)
			{ 
				tmpTX[i] = tubes[i].X;
				tmpTY[i] = tubes[i].Y;
			}			
			break;
		case VK_F8: case 'L':
			ch.X = tmpX;
			ch.y = tmpY;
			ch.vy = tmpV;
			Score = tmpScore;
			//
			for (int i(0); i < TUBE_COUNT; i++)
			{
				tubes[i].X = tmpTX[i];
				tubes[i].Y = tmpTY[i];
			}
			break;

		}

		InvalidateRect(hWnd, NULL, 1);
		break;
	case WM_PAINT:
		RECT rect;
		BITMAP bitmap;
		HDC hdcMem;
		HGDIOBJ oldBitmap;
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		width = rect.right;
		height = rect.bottom;
		backbuffDC = CreateCompatibleDC(hdc);
		backbuffer = CreateCompatibleBitmap(hdc, width, height);
		savedDC = SaveDC(backbuffDC);
		SelectObject(backbuffDC, backbuffer);


		//clear window 
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(backbuffDC, &rect, hBrush);
		DeleteObject(hBrush);
		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		//Drawling background 
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt(backbuffDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

		//draw tubes
			for (int i = 0; i < TUBE_COUNT; i++)
			{
				hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
				hOldPen = (HPEN)SelectObject(backbuffDC, hPen);
				Rectangle(backbuffDC, tubes[i].X - tubes[i].r, -1, tubes[i].X + tubes[i].r, tubes[i].Y + tubes[i].r);
				Rectangle(backbuffDC, tubes[i].X - tubes[i].r, tubes[i].Y - tubes[i].r + GAP_SIZE, tubes[i].X + tubes[i].r, WINDOW_HEIGHT);
				SelectObject(backbuffDC, hOldPen);
				DeleteObject(hPen);
				hPen = CreatePen(PS_SOLID, tubes[i].r, RGB(0, 255, 0));
				hOldPen = (HPEN)SelectObject(backbuffDC, hPen);
				Rectangle(backbuffDC, tubes[i].X - (tubes[i].r / 2), -1, tubes[i].X + (tubes[i].r / 2), tubes[i].Y + (tubes[i].r / 2));
				Rectangle(backbuffDC, tubes[i].X - (tubes[i].r / 2), tubes[i].Y - (tubes[i].r / 2) + GAP_SIZE, tubes[i].X + (tubes[i].r / 2), WINDOW_HEIGHT);
				SelectObject(backbuffDC, hOldPen);
				DeleteObject(hPen);
			}
		//draw bird
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hOldPen = (HPEN)SelectObject(backbuffDC, hPen);
		Ellipse(backbuffDC, BIRD_SPOS - BIRD_SIZE, ch.y - BIRD_SIZE, BIRD_SPOS + (BIRD_SIZE), ch.y + BIRD_SIZE);
		SelectObject(backbuffDC, hOldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, BIRD_SIZE, RGB(255, 0, 0));
		hOldPen = (HPEN)SelectObject(backbuffDC, hPen);

		Ellipse(backbuffDC, BIRD_SPOS - (BIRD_SIZE / 2), ch.y - (BIRD_SIZE / 2), BIRD_SPOS + (BIRD_SIZE / 2), ch.y + (BIRD_SIZE / 2));

		SelectObject(backbuffDC, hOldPen);
		DeleteObject(hPen);
		//print text
		WCHAR s[100];
		    
		    wsprintf(s, _T("Press P to get detailed instructions"));
			TextOut(backbuffDC, 10, 10, s, wcslen(s));

		if (pause){
			wsprintf(s, _T("Pause"));
			TextOut(backbuffDC, 350, 250, s, wcslen(s));
			wsprintf(s, _T("R - restart the game   "));
			TextOut(backbuffDC, 20, 440, s, wcslen(s));
			  wsprintf(s, _T("Spacebar - jerk birds"));
			TextOut(backbuffDC, 25, 460, s, wcslen(s));
			  wsprintf(s, _T("S/ L - save / load the coordinates"));
			TextOut(backbuffDC, 30, 480, s, wcslen(s));
			  wsprintf(s, _T("P - pause"));
			TextOut(backbuffDC, 35, 500, s, wcslen(s));
		}
		if (GameOver == 1)
		{
			wsprintf(s, _T("Game over! Restart game"));
			TextOut(backbuffDC, 350, 250, s, wcslen(s));
			wsprintf(s, _T("Press R"));
			TextOut(backbuffDC, 400, 350, s, wcslen(s));
		}
		if (Score / WINDOW_HEIGHT >= 2)
		{
			score = ((Score - 25) / 400) - 2;
			wsprintf(s, _T("Score = %d"),((Score - 20) / 400) - 2);
			TextOut(backbuffDC, 350, 200, s, wcslen(s));
		}
		// End application-specific layout section.
		BitBlt(hdc, 0, 0, width, height, backbuffDC, 0, 0, SRCCOPY);
		RestoreDC(backbuffDC, savedDC);
		
		DeleteObject(backbuffer);
		DeleteDC(backbuffDC);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
		

		EndPaint(hWnd, &ps);
		break;
	case WM_ERASEBKGND:
		return 1;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}