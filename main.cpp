/**
 *  Course: CS 380
 *  Description of program: This is the prototype GUI for Group 2's CS 380 Card Scanning Project
 *    It is intended to be a evolutionary prototype.
 *
 */


// Includes
#include <Windows.h>
#include <CommCtrl.h>
#include "defines.cpp"
#include "Database.h"


// Callback function prototypes
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CardNumberEditBox (HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);
/* Don't need these just yet
LRESULT CALLBACK NameEditBox (HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);
LRESULT CALLBACK IDNumberEditBox (HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);
LRESULT CALLBACK CoursesEditBox (HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);
*/

// Global Variables
char szClassName[] = "Scanner Window";
HWND hwnd_CardNumberEditBox;
HWND hwnd_NameEditBox;
HWND hwnd_IDNumberEditBox;
HWND hwnd_CoursesEditBox;
// Database Object
Database db;

/**
 *  MAIN FUNCTION BEGINS HERE
 *  This is where the magic starts!
 */
int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "CS 380 - Card Reader Application - Group 2",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                 /* The programs width */
           600,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	HMENU hMenu;
	HMENU hSubMenu;

    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
			{
            // Create items on the window
            hwnd_CardNumberEditBox = CreateWindow(
									 TEXT("Edit"),
									 NULL,
                                     WS_CHILD | WS_VISIBLE | WS_BORDER,
                                     100,  // X from top left
                                     Y_CARD,  // Y from top left
                                     135,  //Width
                                     20,
                                     hwnd,
                                     (HMENU) ID_EDIT,
                                     ((LPCREATESTRUCT) lParam)->hInstance,
                                     NULL);


            hwnd_NameEditBox = CreateWindow(
									 TEXT("Edit"),
									 NULL,
                                     WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                                     100,  // X from top left
                                     Y_NAME,  // Y from top left
                                     200,  // Width
                                     20,   // Height
                                     hwnd,
                                     (HMENU) ID_EDIT,
                                     ((LPCREATESTRUCT) lParam)->hInstance,
                                     NULL);

            hwnd_IDNumberEditBox = CreateWindow(
									 TEXT("Edit"),
									 NULL,
                                     WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                                     100,  // X from top left
                                     Y_IDNUMBER,  // Y from top left
                                     200,  // Width
                                     20,   // Height
                                     hwnd,
                                     (HMENU) ID_EDIT,
                                     ((LPCREATESTRUCT) lParam)->hInstance,
                                     NULL);

            hwnd_CoursesEditBox = CreateWindow(
									 TEXT("Edit"),
									 NULL,
                                     WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                                     100,  // X from top left
                                     Y_COURSES,  // Y from top left
                                     200,  // Width
                                     20,   // Height
                                     hwnd,
                                     (HMENU) ID_EDIT,
                                     ((LPCREATESTRUCT) lParam)->hInstance,
                                     NULL);


			// Start the menu creation
			hMenu = CreateMenu();

			hSubMenu = CreatePopupMenu();
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "Program");
			AppendMenu(hSubMenu, MF_STRING, ID_MENU_FILE_EXIT, "Exit");

			hSubMenu = CreatePopupMenu();
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "Mode");
			AppendMenu(hSubMenu, MF_STRING, ID_MENU_MODE_ATTENDANCE, "Attendance");
			AppendMenu(hSubMenu, MF_STRING, ID_MENU_MODE_OPERATOR, "Operator");

			SetMenu(hwnd, hMenu);
			// End menu creation


            // Subclass declarations
            SetWindowSubclass(hwnd_CardNumberEditBox, CardNumberEditBox, 0, 0);
			/* Don't need these just yet
			 *
            SetWindowSubclass(hwnd_NameEditBox, NameEditBox, 0, 0);
            SetWindowSubclass(hwnd_IDNumberEditBox, IDNumberEditBox, 0, 0);
            SetWindowSubclass(hwnd_CoursesEditBox, CoursesEditBox, 0, 0);
			 *
			**/
			// End subclass declarations

			// Set focus to Card ID box
			SetFocus(hwnd_CardNumberEditBox);
			}
            break;
		case WM_PAINT:
			{
				// Make some pretty text
				char cardID[] = "Card ID:";
				char name[] = "Name:";
				char idNumber[] = "ID Number:";
				char courses[] = "Courses:";

				HDC hdc = BeginPaint(hwnd, &ps);

				// Card ID text
				TextOut(hdc,
						X_CARD,          /* X */
						Y_CARD,          /* Y */
						cardID,
						strlen(cardID) /* Number of chars */);

				// Name text
				TextOut(hdc,
						X_NAME,          /* X */
						Y_NAME,          /* Y */
						name,
						strlen(name) /* Number of chars */);

				// ID number text
				TextOut(hdc,
						X_IDNUMBER,          /* X */
						Y_IDNUMBER,          /* Y */
						idNumber,
						strlen(idNumber) /* Number of chars */);

				// Courses text
				TextOut(hdc,
						X_COURSES,          /* X */
						Y_COURSES,          /* Y */
						courses,
						strlen(courses) /* Number of chars */);

				EndPaint(hwnd, &ps);
			}
			break;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case ID_MENU_FILE_EXIT:
				{
					PostMessage(hwnd, WM_CLOSE, 0, 0);
					break;
				}
				default:
					break;
			}
			break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}


/**
 *  Callback function for CardNumberEditBox
 */
LRESULT CALLBACK CardNumberEditBox(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (message)
    {
        case WM_KEYDOWN:
        {
            if(wParam == VK_RETURN && GetWindowTextLength(hWnd) != 0)
            {
				char cardNumber[LENGTH_CARD_NUMBER + 1] = "";
				char name[LENGTH_NAME + 1] = "";
				char idNumber[LENGTH_MSU_ID + 1] = "";
				char courses[LENGTH_COURSES + 1] = "";

				GetWindowText(hWnd, cardNumber, LENGTH_CARD_NUMBER); // This puts a null terminating character on the end of string
																	 // This is the reason for the + 1's at end of cardNumber cstring

				if(db.isMember(cardNumber))
				{
					db.getMemberInfo(cardNumber, name, idNumber, courses);
					SetWindowText(hwnd_NameEditBox, name);
					SetWindowText(hwnd_IDNumberEditBox, idNumber);
					SetWindowText(hwnd_CoursesEditBox, courses);
				}
				else
				{
					// ADD missing information into the database (members table)
				}
				
				SendMessage(hwnd_CardNumberEditBox, EM_SETSEL, 0, -1);
				SetFocus(hwnd_CardNumberEditBox);
            }

            return true;
        }
		case WM_CHAR:
		{
			if(wParam == VK_RETURN || wParam == VK_TAB)
			{
				return false;
			}
		}
        default:
            break;
    }

    return DefSubclassProc(hWnd, message, wParam, lParam);
}


/** THESE FOLLOWING FUNCTIONS ARE CURRENTLY UNNEEDED
 *
 *
 *
// Callback function for NameEditBox

LRESULT CALLBACK NameEditBox(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (message)
    {
        case WM_KEYDOWN:
        {
            if(wParam == VK_RETURN || wParam == VK_TAB)
            {
				SetFocus(hwnd_IDNumberEditBox);
				return false;
            }
            return true;
        }
		case WM_CHAR:
		{
			if(wParam == VK_RETURN || wParam == VK_TAB)
			{
				return false;
			}
		}

        default:
            break;
    }

    return DefSubclassProc(hWnd, message, wParam, lParam);
}


// Callback function for IDNumberEditBox

LRESULT CALLBACK IDNumberEditBox(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (message)
    {
        case WM_KEYDOWN:
        {
            if(wParam == VK_RETURN || wParam == VK_TAB)
            {
				SetFocus(hwnd_CoursesEditBox);
				return false;
            }
            return true;
        }
		case WM_CHAR:
		{
			if(wParam == VK_RETURN || wParam == VK_TAB)
			{
				return false;
			}
		}

        default:
            break;
    }

    return DefSubclassProc(hWnd, message, wParam, lParam);
}


// Callback function for CoursesEditBox

LRESULT CALLBACK CoursesEditBox(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (message)
    {
        case WM_KEYDOWN:
        {
            if(wParam == VK_RETURN || wParam == VK_TAB)
            {
				SetFocus(hwnd_IDNumberEditBox);
				return false;
            }
            return true;
        }
		case WM_CHAR:
		{
			if(wParam == VK_RETURN || wParam == VK_TAB)
			{
				return false;
			}
		}
		

        default:
            break;
    }

    return DefSubclassProc(hWnd, message, wParam, lParam);
}
 *
 *
 * END UNNEEDED FUNCTION COMMENT OUT
 */