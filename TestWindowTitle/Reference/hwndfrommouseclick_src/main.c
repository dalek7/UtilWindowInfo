/******************************************************************************************/
/*																						  */
/*            Simple example to show how to get window handles from mouse clicks          */
/*											by 											  */
/*									recoup_this@yahoo.com								  */
/*																						  */
/******************************************************************************************/
#include <windows.h>

BOOL g_bCaptureSet = FALSE;							// Flag to indicate if window has called SetCapture()

BOOL CALLBACK MainDlgProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uiMsg)
		{
		case WM_LBUTTONDOWN:
			{
			if(g_bCaptureSet == TRUE) 				//Checks if the window has captured the mouse
				{
				POINT p;
				HWND hWndGet;
				char szTitle[256];
				DWORD dwPoint = GetMessagePos(); 	// Get the screen co-ords at the time
								 					// GetMessage was last called
				
				p.x = LOWORD(dwPoint);		 		// Convert it to a points struct
				p.y = HIWORD(dwPoint);
				
				memset(szTitle, 0, 256);	 		// Empty szTitle, just incase !!
				hWndGet = WindowFromPoint(p);	 	// This gets the HWND of the window 
								 					// at point p
								 
				if(hWndGet == NULL)					// Also it returns null if no window is 
								 					// there, so format an error message and
								 					// Display it, then release capture of 
								 					// the mouse, and set g_bCaptureSet to 
								 					// reflect this
					{
					wsprintf(szTitle, "No window at selected point (%d, %d)", p.x, p.y);
					MessageBox(hWnd, szTitle, "Error", MB_OK);
					ReleaseCapture();		
					g_bCaptureSet = FALSE;
					return TRUE;
					}
													// Otherwise get the found window's
													// text, and display it, then
													// release capture, and update
													// g_bCaptureSet
				GetWindowText(hWndGet, szTitle, 256);	
				MessageBox(hWnd, szTitle, "Window selected", MB_OK);
				ReleaseCapture();
				g_bCaptureSet = FALSE;
				}
			return TRUE;
			}
		case WM_COMMAND:
			{
			switch(LOWORD(wParam))
				{
				case IDCANCEL:
					{
					EndDialog(hWnd, 0);
					return TRUE;
					}
				case IDOK:
					{
					if(g_bCaptureSet == TRUE)		// Ignore the click if window already 
													// has capture
						{
						return TRUE;	
						}
					SetCapture(hWnd);				// Set the mouse capture to the window
					g_bCaptureSet = TRUE;			// and update g_bCaptureSet
					return TRUE;
					}
				}
			return FALSE;
			}
		}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int iCmdShow)
{
	DialogBox(hInst, "MAINDIALOG", NULL, MainDlgProc);
	return 0;
}