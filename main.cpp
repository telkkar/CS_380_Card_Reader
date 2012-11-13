/**
 *  Course: CS 380
 *  Description of program: This is the prototype GUI for Group 2's CS 380 Card Scanning Project
 *    It is intended to be a evolutionary prototype.
 *
 *	WILLIAM NOTE: Get rid of all these global handles, you fool! 
 *		Use something like this GetDlgItem(FindWindow(szClassName, NULL), ID_LISTBOX)
 *            FindWindow(className, windowName) returns handle to *WINDOW* with those names
 *            GetDlgItem(handle of parent, #id of control) returns handle to *CONTROL*
 *
 */


// Includes
#include <Windows.h>
#include <CommCtrl.h>
#include "defines.h"
#include "Database.h"


// Callback function prototypes
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CardNumberEditBox (HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);

BOOL CALLBACK AddMemberDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
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
	wincl.lpszClassName = (LPCSTR)szClassName;
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
		(LPCSTR)szClassName,         /* Classname */
		(LPCSTR)"CS 380 - Card Reader Application - Group 2",       /* Title Text */
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
			100,     // X from top left
			Y_CARD,  // Y from top left
			135,     // Width
			20,		 // Height
			hwnd,
			(HMENU) ID_EDIT,
			((LPCREATESTRUCT) lParam)->hInstance,
			NULL);


		hwnd_NameEditBox = CreateWindow(
			TEXT("Edit"),
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
			100,     // X from top left
			Y_NAME,  // Y from top left
			200,     // Width
			20,      // Height
			hwnd,
			(HMENU) ID_EDIT,
			((LPCREATESTRUCT) lParam)->hInstance,
			NULL);

		hwnd_IDNumberEditBox = CreateWindow(
			TEXT("Edit"),
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
			100,		 // X from top left
			Y_IDNUMBER,  // Y from top left
			200,		 // Width
			20,			 // Height
			hwnd,
			(HMENU) ID_EDIT,
			((LPCREATESTRUCT) lParam)->hInstance,
			NULL);

		hwnd_CoursesEditBox = CreateWindow(
			TEXT("Edit"),
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
			100,		// X from top left
			Y_COURSES,  // Y from top left
			200,		// Width
			20,			// Height
			hwnd,
			(HMENU) ID_EDIT,
			((LPCREATESTRUCT) lParam)->hInstance,
			NULL);

		// *****************************************
		// ***** This starts list box creation *****
		// *****************************************
		HWND hwnd_AttendanceListBox = CreateWindow(
			WC_LISTVIEW,
			NULL,
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | LVS_REPORT,
			380,		// X from top left
			0,			// Y from top left
			400,		// Width
			450,		// Height
			hwnd,
			(HMENU) ID_LISTBOX,
			((LPCREATESTRUCT) lParam)->hInstance,
			NULL);

		// Will this ever work?
		ShowScrollBar(hwnd_AttendanceListBox, SB_VERT, true);

		// Add extended view styles to the list box
		ListView_SetExtendedListViewStyle(hwnd_AttendanceListBox, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		LVCOLUMN lvc = { 0 };

		lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH  | LVCF_FMT;
        lvc.fmt  = LVCFMT_LEFT;

        lvc.iSubItem = 0;
        lvc.cx       = 50;
        lvc.pszText  = TEXT("Name");
        ListView_InsertColumn(hwnd_AttendanceListBox, 0, &lvc);
 
        lvc.iSubItem = 1;
        lvc.cx       = 100;
        lvc.pszText  = TEXT("ID Number");
        ListView_InsertColumn(hwnd_AttendanceListBox, 1, &lvc);
 
        lvc.iSubItem = 2;
        lvc.cx       = 230;
        lvc.pszText  = TEXT("Courses");
        ListView_InsertColumn(hwnd_AttendanceListBox, 2, &lvc);

		// ***************************************
		// ***** This ends list box creation *****
		// ***************************************

		// Start the menu creation
		hMenu = CreateMenu();

		hSubMenu = CreatePopupMenu();
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, (LPCSTR)"Program");
		AppendMenu(hSubMenu, MF_STRING, ID_MENU_FILE_EXIT, (LPCSTR)"Exit");

		hSubMenu = CreatePopupMenu();
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, (LPCSTR)"Mode");
		AppendMenu(hSubMenu, MF_STRING, ID_MENU_MODE_ATTENDANCE, (LPCSTR)"Attendance");
		AppendMenu(hSubMenu, MF_STRING, ID_MENU_MODE_OPERATOR, (LPCSTR)"Operator");

		SetMenu(hwnd, hMenu);
		// End menu creation


		/***** Subclass declarations
		 *	Subclassing our edit boxes makes it so we can incercept events
		 *	(mainly the Enter key) and do something (different) with the event
		 *	before it gets passed to the main window. This is what allows us to
		 *	accept the enter key and have it process the input instead of entering
		 *	nothing and doing nothing.
		 */
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
		// Make some text to the left side of the edit boxes
		char cardID[] = "Card ID:";
		char name[] = "Name:";
		char idNumber[] = "ID Number:";
		char courses[] = "Courses:";

		HDC hdc = BeginPaint(hwnd, &ps);

		// Card ID text
		TextOut(hdc,
		        X_CARD,          /* X */
		        Y_CARD,          /* Y */
		        (LPCSTR)cardID,
		        strlen(cardID) /* Number of chars */);

		// Name text
		TextOut(hdc,
		        X_NAME,          /* X */
		        Y_NAME,          /* Y */
		        (LPCSTR)name,
		        strlen(name) /* Number of chars */);

		// ID number text
		TextOut(hdc,
		        X_IDNUMBER,          /* X */
		        Y_IDNUMBER,          /* Y */
		        (LPCSTR)idNumber,
		        strlen(idNumber) /* Number of chars */);

		// Courses text
		TextOut(hdc,
		        X_COURSES,          /* X */
		        Y_COURSES,          /* Y */
		        (LPCSTR)courses,
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
 *  Our CardNumberEditBox gets subclassed into this function
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

			GetWindowText(hWnd, (LPSTR)cardNumber, LENGTH_CARD_NUMBER); // This puts a null terminating character on the end of string
			// This is the reason for the + 1's at end of cardNumber cstring

			if(db.isMember(cardNumber))
			{
				db.getMemberInfo(cardNumber, name, idNumber, courses);
				SetWindowText(hwnd_NameEditBox, (LPCSTR)name);
				SetWindowText(hwnd_IDNumberEditBox, (LPCSTR)idNumber);
				SetWindowText(hwnd_CoursesEditBox, (LPCSTR)courses);

				// Handle to List box found
				HWND hwnd_AttendanceListBox = GetDlgItem(FindWindow(szClassName, NULL), ID_LISTBOX);
				LVITEM   lv  = { 0 };  // No idea what this does, but works

				// Add new entry to the AttendanceListBox
				ListView_InsertItem(hwnd_AttendanceListBox, &lv);
				ListView_SetItemText(hwnd_AttendanceListBox, 0, 0, (LPSTR)name);
				ListView_SetItemText(hwnd_AttendanceListBox, 0, 1, (LPSTR)idNumber);
				ListView_SetItemText(hwnd_AttendanceListBox, 0, 2, (LPSTR)courses);
				ListView_SetCheckState(hwnd_AttendanceListBox, 0, TRUE);
			}
			else
			{	// ADD missing information into the database (members table)
				DialogBox(GetModuleHandle(NULL),
						  MAKEINTRESOURCE(IDD_DLG_ADD_MEMBER),
						  hWnd,
						  AddMemberDlgProc);
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


BOOL CALLBACK AddMemberDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
		{
			// Get the cardNumber
			char cardNumber[LENGTH_CARD_NUMBER + 1] = "";
			GetWindowText(hwnd_CardNumberEditBox, (LPSTR)cardNumber, LENGTH_CARD_NUMBER);

			// Place it in the first edit control in the dialog box
			SetWindowText(GetDlgItem(hwnd, IDC_EDIT_CARD_NUMBER), (LPCSTR)cardNumber);

			// Set focus to the name box
			PostMessage(hwnd, WM_NEXTDLGCTL, FALSE, FALSE);
		}
        return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
				{
					// Add info to database
					char cardNumber[LENGTH_CARD_NUMBER + 1] = "";
					char name[LENGTH_NAME + 1] = "";
					char idNumber[LENGTH_MSU_ID + 1] = "";
					char courses[LENGTH_COURSES + 1] = "";

					// Get the info from the dialog edit controls
					GetWindowText(hwnd_CardNumberEditBox, (LPSTR)cardNumber, LENGTH_CARD_NUMBER);
					GetWindowText(GetDlgItem(hwnd, IDC_EDIT_NAME), (LPSTR)name, LENGTH_NAME);
					GetWindowText(GetDlgItem(hwnd, IDC_EDIT_ID_NUMBER), (LPSTR)idNumber, LENGTH_MSU_ID);
					GetWindowText(GetDlgItem(hwnd, IDC_EDIT_COURSES), (LPSTR)courses, LENGTH_COURSES);
					
					// Add them to the members table, and the attendance table
					db.addMember(cardNumber, name, idNumber, courses);
					db.addAttendance(cardNumber, name, idNumber, courses);

					// Handle to List box found
					HWND hwnd_AttendanceListBox = GetDlgItem(FindWindow(szClassName, NULL), ID_LISTBOX);
					LVITEM   lv  = { 0 };

					// Add user to AttendanceListBox in main window
					ListView_InsertItem(hwnd_AttendanceListBox, &lv);
					ListView_SetItemText(hwnd_AttendanceListBox, 0, 0, (LPSTR)name);
					ListView_SetItemText(hwnd_AttendanceListBox, 0, 1, (LPSTR)idNumber);
					ListView_SetItemText(hwnd_AttendanceListBox, 0, 2, (LPSTR)courses);
					ListView_SetCheckState(hwnd_AttendanceListBox, 0, TRUE);

					// Add the information into the edit boxes in main window
					SetWindowText(hwnd_CardNumberEditBox, (LPCSTR)cardNumber);
					SetWindowText(hwnd_NameEditBox, (LPCSTR)name);
					SetWindowText(hwnd_IDNumberEditBox, (LPCSTR)idNumber);
					SetWindowText(hwnd_CoursesEditBox, (LPCSTR)courses);

                    EndDialog(hwnd, IDOK);
				}
                break;
                case IDCANCEL: // Currently not used
                    EndDialog(hwnd, IDCANCEL);
                break;
            }
		break;
        default:
            return FALSE;
    }
    return TRUE;
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
