/**************************
 * Includes
 *
 **************************/
 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


#include <windows.h>
#include <gl/gl.h>
#include "c/matrix.h"
#include "main.h"


/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    
	int n, k, c;
    int **Matrix;
    int **bNear;
    int **bFar;
       
    Matrix = (int**)malloc(3 * sizeof(int*));
    bNear = (int**)malloc(3 * sizeof(int*));
    bFar = (int**)malloc(3 * sizeof(int*));
  
	for(n=0; n<3; n++)
	{
		Matrix[n] = (int*)malloc(K_max * sizeof(int));
		bNear[n] = (int*)malloc(K_max-1 * sizeof(int));
		bFar[n] = (int*)malloc(K_max-1 * sizeof(int));
		Matrix[n][0] = M[n][0];
		for(k=0; k<K_max-1; k++)
		{
			Matrix[n][k+1] = M[n][k+1];
			bNear[n][k] = Gr_blizn[n][k];
			bFar[n][k] = Gr_daln[n][k];
		}
	}
	
	combAlg(Matrix, bNear, bFar, K_max);
		
    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "Алгоритм объединения областей", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      SCREEN_WIDTH/2.f - WINDOW_WIDTH/2.f,
	  SCREEN_HEIDHT/2.f - WINDOW_HEIDHT/2.f,
	  WINDOW_WIDTH, WINDOW_HEIDHT,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);
    
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
    glOrtho(VIEW_OFFSET_X,VIEW_WIDTH,
			VIEW_HEIDHT,VIEW_OFFSET_Y,0,1);
    glMatrixMode(GL_MODELVIEW);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClear (GL_COLOR_BUFFER_BIT);

			//in_line();
			//blend();

			for(n=0; n<3; n++)
			{
				if(n == 0)
		          	glColor3f(1.0f, 0.0f, 0.0f);
				if(n == 1)
		          	glColor3f(0.0f, 1.0f, 0.0f);
				if(n == 2)
		          	glColor3f(0.0f, 0.0f, 1.0f);
					for(k=0; k<M[n][0]; k++)
					{
						glRecti(Gr_blizn[n][k]-1, n,
								Gr_daln [n][k], n + 1);
					}
					for(k=0; k<Matrix[n][0]; k++)
					{
						glRecti(bNear[n][k]-1, n + 4,
								bFar [n][k], n + 5);
					}
			}
			
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_LINES);
			for(n=VIEW_OFFSET_X+1;n<VIEW_WIDTH;n++)
			{
				glVertex2f(n, VIEW_OFFSET_Y);
				glVertex2f(n, VIEW_HEIDHT);
			}
			for(k=VIEW_OFFSET_Y+1;k<VIEW_HEIDHT;k++)
			{
				glVertex2f(VIEW_OFFSET_X,k);
				glVertex2f(VIEW_WIDTH,k);
			}
			glEnd();
            SwapBuffers (hDC);
        }
    }
    
    for(n=0; n<3; n++)
	{
		free(Matrix[n]);
		free(bNear[n]);
		free(bFar[n]);
	}
	free(Matrix);
	free(bNear);
	free(bFar);


    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}


