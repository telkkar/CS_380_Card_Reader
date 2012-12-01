/**
 *	Course:					CS 380
 *	Group:					Group 2 - Card Reader Application Group
 *	Group Members:			Dylan, John, William
 *	Description of Project:
 *		This is a card scanning program that accepts input in the form of card
 *		numbers. When a user scans his/her card, the program will record his/
 *		her attendance. If the program doesn't know who the user is, the user
 *		is prompted for his/her information.
 */

/**
 *	Header Block: GUI Module
 *	Module Name: 
 *		GUI Module
 *	Authors:
 *		Dylan, John, William
 *	Where it fits:
 *		This module houses the main control of the program. All main logic is
 *		in this module.
 *	When it was written, and revised:
 *		Continuous revision, and revisement (see github commit history)
 *	Why it exists:
 *		This is the module that handles the GUI. We decided we wanted a GUI,
 *		therefore we have this module.
 *	How it uses datastructures, algorithms, and control:
 *		Everything is still messy, so everything is unpolished. See the state
 *		diagrams if you you want to know.
 */

/**
 *	NOTES/TODO: 
 *		-Function: EditMemberDlgProc, under case: IDOK
 *			- Follow steps outlined right under IDOK case statement
 *		-If you want to add enter functionality in dialog box, you'll have to subclass boxes in dialog box
 */


// Includes
#include "defines.h"
#include "Database.h"
#include "PrintFile.h"

#include <Windows.h>
#include <CommCtrl.h>
#include <cstring>

// Callback function prototypes
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CardNumberEditBox (HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);

BOOL CALLBACK AddMemberDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EditMemberDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

// Global Variables
char szClassName[] = "Scanner Window";
Database db;

/*
 * Function: WinMain
 * Description: This is the function that replaces main() in a terminal application.
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


/*
 * Function: WindowProcedure
 * Description: This function is called by the Windows function DispatchMessage(). It
 *   processes the messages sent to it by the OS.
 *   Here is where we create most of the controls in the main window.
 */
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
		HWND hwnd_CardNumberEditBox = CreateWindow(
			TEXT("Edit"),
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			100,     // X from top left
			Y_CARD,  // Y from top left
			135,     // Width
			20,		 // Height
			hwnd,
			(HMENU) IDC_EDIT_CARDNUMBER,
			((LPCREATESTRUCT) lParam)->hInstance,
			NULL);


		HWND hwnd_NameEditBox = CreateWindow(
			TEXT("Edit"),
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
			100,     // X from top left
			Y_NAME,  // Y from top left
			200,     // Width
			20,      // Height
			hwnd,
			(HMENU) IDC_EDIT_NAME,
			((LPCREATESTRUCT) lParam)->hInstance,
			NULL);

		HWND hwnd_IDNumberEditBox = CreateWindow(
			TEXT("Edit"),
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
			100,		 // X from top left
			Y_IDNUMBER,  // Y from top left
			200,		 // Width
			20,			 // Height
			hwnd,
			(HMENU) IDC_EDIT_IDNUMBER,
			((LPCREATESTRUCT) lParam)->hInstance,
			NULL);

		HWND hwnd_CoursesEditBox = CreateWindow(
			TEXT("Edit"),
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
			100,		// X from top left
			Y_COURSES,  // Y from top left
			200,		// Width
			20,			// Height
			hwnd,
			(HMENU) IDC_EDIT_COURSES,
			((LPCREATESTRUCT) lParam)->hInstance,
			NULL);

		HWND hwnd_AttendanceCountBox = CreateWindow(
			TEXT("Edit"),
			"0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
			X_ATTENDANCE_COUNT,		// X from top left
			Y_ATTENDANCE_COUNT,  // Y from top left
			20,		// Width
			20,			// Height
			hwnd,
			(HMENU) IDC_ATTENDANCE_COUNTER,
			((LPCREATESTRUCT) lParam)->hInstance,
			NULL);

		// Create some buttons
		HWND hwnd_EditButton = CreateWindow(
			TEXT("Button"),
			"Edit Selected Member",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
			350,		// X from top left
			100,  // Y from top left
			200,		// Width
			23,			// Height
			hwnd,
			(HMENU) IDC_BUTTON_EDITMEMBER,
			((LPCREATESTRUCT) lParam)->hInstance,
			NULL);


		// *****************************************
		// ***** This starts list box creation *****
		// *****************************************
		HWND hwnd_AttendanceListBox = CreateWindow(
			WC_LISTVIEW,
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
			0,		// X from top left
			150,			// Y from top left
			785,		// Width
			410,		// Height
			hwnd,
			(HMENU) IDC_LISTBOX,
			((LPCREATESTRUCT) lParam)->hInstance,
			NULL);

		// Add extended view styles to the list box
		ListView_SetExtendedListViewStyle(hwnd_AttendanceListBox, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		LVCOLUMN lvc = { 0 };

		lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH  | LVCF_FMT;
        lvc.fmt  = LVCFMT_LEFT;

        lvc.iSubItem = 0;					// Hidden Column
        lvc.cx       = 0;					//
        lvc.pszText  = TEXT("CardNumber");	//
		ListView_InsertColumn(hwnd_AttendanceListBox, 0, &lvc);

        lvc.iSubItem = 1;
        lvc.cx       = 150;
        lvc.pszText  = TEXT("Name");
        ListView_InsertColumn(hwnd_AttendanceListBox, 1, &lvc);
 
        lvc.iSubItem = 2;
        lvc.cx       = 75;
        lvc.pszText  = TEXT("ID Number");
        ListView_InsertColumn(hwnd_AttendanceListBox, 2, &lvc);
 
        lvc.iSubItem = 3;
        lvc.cx       = 575;
        lvc.pszText  = TEXT("Courses");
        ListView_InsertColumn(hwnd_AttendanceListBox, 3, &lvc);

		// ***************************************
		// ***** This ends list box creation *****
		// ***************************************

		// Start the menu creation
		hMenu = CreateMenu();

		hSubMenu = CreatePopupMenu();
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, (LPCSTR)"Program");
		AppendMenu(hSubMenu, MF_STRING, IDM_MENU_FILE_EXIT, (LPCSTR)"Exit");

		hSubMenu = CreatePopupMenu();
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, (LPCSTR)"Print");
		AppendMenu(hSubMenu, MF_STRING, IDM_MENU_PRINT_HUMANREADABLE, (LPCSTR)"Human Readable");
		AppendMenu(hSubMenu, MF_STRING, IDM_MENU_PRINT_CSV, (LPCSTR)"CSV");

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
		char attendanceCount[] = "Attendance Count:";

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

		// Attendance Count text
		TextOut(hdc,
		        X_ATTENDANCE_COUNT - 120,        /* X */
		        Y_ATTENDANCE_COUNT + 2,          /* Y */
		        (LPCSTR)attendanceCount,
		        strlen(attendanceCount) /* Number of chars */);


		EndPaint(hwnd, &ps);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_MENU_FILE_EXIT:
		{
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		}
		case IDM_MENU_PRINT_HUMANREADABLE:
		{
			PrintFile printFile;
			printFile.printToHumanFormatted(db.getAttendanceTable(), db.getAttendanceCount());
			break;
		}
		case IDM_MENU_PRINT_CSV:
		{
			PrintFile printFile;
			printFile.printToCSV(db.getAttendanceTable(), db.getAttendanceCount());
			break;
		}
		case IDC_BUTTON_EDITMEMBER:
		{
			DialogBox(GetModuleHandle(NULL),
						MAKEINTRESOURCE(IDD_DLG_EDITMEMBER),
						hwnd,
						EditMemberDlgProc);
			break;
		}
		default:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
		
		// Line for cleaning up attendance on program exit
		db.clearAttendance();

		break;
	default:                      /* for messages that we don't deal with */
		return DefWindowProc (hwnd, message, wParam, lParam);
	}

	return 0;
}


/*
 *  Function: CardNumberEditBox
 *  Description: Our CardNumberEditBox control gets subclassed into this function.
 */
LRESULT CALLBACK CardNumberEditBox(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		if(wParam == VK_RETURN && GetWindowTextLength(hwnd) != 0)
		{
			char cardNumber[LENGTH_CARD_NUMBER + 1] = "";
			char name[LENGTH_NAME + 1] = "";
			char idNumber[LENGTH_MSU_ID + 1] = "";
			char courses[LENGTH_COURSES + 1] = "";

			GetWindowText(hwnd, (LPSTR)cardNumber, LENGTH_CARD_NUMBER + 1); // This puts a null terminating character on the end of string
																		// This is the reason for the + 1's at end of cardNumber cstring

			if(db.isMember(cardNumber))
			{
				if(!db.isAttending(cardNumber))
				{
					db.getMemberInfo(cardNumber, name, idNumber, courses);
					db.addAttendance(cardNumber, name, idNumber, courses);

					SetWindowText(GetDlgItem(FindWindow(szClassName, NULL), IDC_EDIT_NAME), (LPCSTR)name);
					SetWindowText(GetDlgItem(FindWindow(szClassName, NULL), IDC_EDIT_IDNUMBER), (LPCSTR)idNumber);
					SetWindowText(GetDlgItem(FindWindow(szClassName, NULL), IDC_EDIT_COURSES), (LPCSTR)courses);

					// Handle to List box found
					HWND hwnd_AttendanceListBox = GetDlgItem(FindWindow(szClassName, NULL), IDC_LISTBOX);

					LVITEM   lv  = { 0 };  // No idea what this does, but works

					// Add new entry to the AttendanceListBox
					ListView_InsertItem(hwnd_AttendanceListBox, &lv);
					ListView_SetItemText(hwnd_AttendanceListBox, 0, 0, (LPSTR)cardNumber);
					ListView_SetItemText(hwnd_AttendanceListBox, 0, 1, (LPSTR)name);
					ListView_SetItemText(hwnd_AttendanceListBox, 0, 2, (LPSTR)idNumber);
					ListView_SetItemText(hwnd_AttendanceListBox, 0, 3, (LPSTR)courses);
					ListView_SetCheckState(hwnd_AttendanceListBox, 0, TRUE);

					ListView_SetItemState(hwnd_AttendanceListBox, -1, 0, LVIS_SELECTED); // deselect all items
					SendMessage(hwnd_AttendanceListBox, LVM_ENSUREVISIBLE, (WPARAM)0, FALSE); // if item is far, scroll to it
					ListView_SetItemState(hwnd_AttendanceListBox, 0, LVIS_SELECTED, LVIS_SELECTED); // select item
					
					/* Needs to check for ints over 99 (any more than two digits) */
					int count = db.getAttendanceCount();
					char countText[3];
					
					_itoa(db.getAttendanceCount(), countText, 10); 

					SetWindowText(GetDlgItem(FindWindow(szClassName, NULL), IDC_ATTENDANCE_COUNTER), (LPCTSTR)countText);


				}
				else /* If the person is attending */
				{
					HWND hwnd_AttendanceListBox = GetDlgItem(FindWindow(szClassName, NULL), IDC_LISTBOX);

					int int_cardNumber = atoi(cardNumber);

					LVFINDINFO *lv = new LVFINDINFO;
					lv->flags = LVFI_STRING;
					lv->psz = cardNumber;

					int position = ListView_FindItem(hwnd_AttendanceListBox, -1, lv);

					// Select them in the list box? That'd be neat
					ListView_SetItemState(hwnd_AttendanceListBox, -1, 0, LVIS_SELECTED); // deselect all items
					SendMessage(hwnd_AttendanceListBox, LVM_ENSUREVISIBLE, (WPARAM)position, FALSE); // if item is far, scroll to it
					ListView_SetItemState(hwnd_AttendanceListBox, position, LVIS_SELECTED, LVIS_SELECTED); // select item
					//ListView_SetItemState(hwnd_AttendanceListBox, position, LVIS_FOCUSED, LVIS_FOCUSED); // optional
				}
			}
			else
			{	// ADD missing information into the database (members table)
				DialogBox(GetModuleHandle(NULL),
						  MAKEINTRESOURCE(IDD_DLG_ADDMEMBER),
						  hwnd,
						  AddMemberDlgProc);
			}

			SendMessage(GetDlgItem(FindWindow(szClassName, NULL), IDC_EDIT_CARDNUMBER), EM_SETSEL, 0, -1);
			SetFocus(GetDlgItem(FindWindow(szClassName, NULL), IDC_EDIT_CARDNUMBER));
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

	return DefSubclassProc(hwnd, message, wParam, lParam);
}

/*
 *  Function: AddMemberDlgProc
 *  Description: This is the function that handles the messages for the dialog box
 *    that prompts the user for information before adding that user to the database.
 */
BOOL CALLBACK AddMemberDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
		{
			// Get the cardNumber
			char cardNumber[LENGTH_CARD_NUMBER + 1] = "";
			GetWindowText(GetDlgItem(FindWindow(szClassName, NULL), IDC_EDIT_CARDNUMBER), (LPSTR)cardNumber, LENGTH_CARD_NUMBER + 1);

			// Place it in the first edit control in the dialog box
			SetWindowText(GetDlgItem(hwnd, IDC_EDIT_CARDNUMBER), (LPCSTR)cardNumber);

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

					// Get the info from the dialog edit controls in the dialog box
					GetWindowText(GetDlgItem(hwnd, IDC_EDIT_CARDNUMBER), (LPSTR)cardNumber, LENGTH_CARD_NUMBER + 1);
					GetWindowText(GetDlgItem(hwnd, IDC_EDIT_NAME), (LPSTR)name, LENGTH_NAME + 1);
					GetWindowText(GetDlgItem(hwnd, IDC_EDIT_IDNUMBER), (LPSTR)idNumber, LENGTH_MSU_ID + 1);
					GetWindowText(GetDlgItem(hwnd, IDC_EDIT_COURSES), (LPSTR)courses, LENGTH_COURSES + 1);
					
					// Add them to the members table, and the attendance table
					db.addMember(cardNumber, name, idNumber, courses);
					db.addAttendance(cardNumber, name, idNumber, courses);

					// Handle to List box found
					HWND hwnd_AttendanceListBox = GetDlgItem(FindWindow(szClassName, NULL), IDC_LISTBOX);
					LVITEM   lv  = { 0 };

					// Add user to AttendanceListBox in main window
					ListView_InsertItem(hwnd_AttendanceListBox, &lv);
					ListView_SetItemText(hwnd_AttendanceListBox, 0, 0, (LPSTR)cardNumber);
					ListView_SetItemText(hwnd_AttendanceListBox, 0, 1, (LPSTR)name);
					ListView_SetItemText(hwnd_AttendanceListBox, 0, 2, (LPSTR)idNumber);
					ListView_SetItemText(hwnd_AttendanceListBox, 0, 3, (LPSTR)courses);
					ListView_SetCheckState(hwnd_AttendanceListBox, 0, TRUE);

					// Change the information of the edit boxes in main window
					SetWindowText(GetDlgItem(FindWindow(szClassName, NULL), IDC_EDIT_CARDNUMBER), (LPCSTR)cardNumber);
					SetWindowText(GetDlgItem(FindWindow(szClassName, NULL), IDC_EDIT_NAME), (LPCSTR)name);
					SetWindowText(GetDlgItem(FindWindow(szClassName, NULL), IDC_EDIT_IDNUMBER), (LPCSTR)idNumber);
					SetWindowText(GetDlgItem(FindWindow(szClassName, NULL), IDC_EDIT_COURSES), (LPCSTR)courses);

                    EndDialog(hwnd, IDOK);
				}
                break;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                break;
            }
		break;
        default:
            return FALSE;
    }
    return TRUE;
}

/*
 *  Function: EditMemberDlgProc
 *  Description: This is the function that handles the messages for the dialog box
 *    that prompts the user to edit a user's information.
 */
BOOL CALLBACK EditMemberDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
		{
			char cardNumber[LENGTH_CARD_NUMBER + 1] = "";
			char name[LENGTH_NAME + 1] = "";
			char idNumber[LENGTH_MSU_ID + 1] = "";
			char courses[LENGTH_COURSES + 1] = "";

			HWND hwnd_AttendanceListBox = GetDlgItem(FindWindow(szClassName, NULL), IDC_LISTBOX);

			int selectedIndex = ListView_GetNextItem(hwnd_AttendanceListBox, -1, LVNI_SELECTED);

			ListView_GetItemText(hwnd_AttendanceListBox, selectedIndex, 0, (LPSTR)cardNumber, LENGTH_CARD_NUMBER + 1);
			ListView_GetItemText(hwnd_AttendanceListBox, selectedIndex, 1, (LPSTR)name, LENGTH_NAME + 1);
			ListView_GetItemText(hwnd_AttendanceListBox, selectedIndex, 2, (LPSTR)idNumber, LENGTH_MSU_ID + 1); // Not sure why we need +1, but we do
			ListView_GetItemText(hwnd_AttendanceListBox, selectedIndex, 3, (LPSTR)courses, LENGTH_COURSES + 1);

			// Display in the dialog box
			SetWindowText(GetDlgItem(hwnd, IDC_EDIT_CARDNUMBER), (LPCSTR)cardNumber);
			SetWindowText(GetDlgItem(hwnd, IDC_EDIT_NAME), (LPCSTR)name);
			SetWindowText(GetDlgItem(hwnd, IDC_EDIT_IDNUMBER), (LPCSTR)idNumber);
			SetWindowText(GetDlgItem(hwnd, IDC_EDIT_COURSES), (LPCSTR)courses);

			// Set focus to the name box
			PostMessage(hwnd, WM_NEXTDLGCTL, FALSE, FALSE);
		}
        return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
				{
					/* Here's what do:
					 *	Read info from the edit controls
					 *	Call the edit information function from database with new edit information
					 *	Show the new information in the edit box
					 */

					char cardNumber[LENGTH_CARD_NUMBER + 1] = "";
					char name[LENGTH_NAME + 1] = "";
					char idNumber[LENGTH_MSU_ID + 1] = "";
					char courses[LENGTH_COURSES + 1] = "";

					GetWindowText(GetDlgItem(hwnd, IDC_EDIT_CARDNUMBER), (LPSTR)cardNumber, LENGTH_CARD_NUMBER + 1);
					GetWindowText(GetDlgItem(hwnd, IDC_EDIT_NAME), (LPSTR)name, LENGTH_NAME + 1);
					GetWindowText(GetDlgItem(hwnd, IDC_EDIT_IDNUMBER), (LPSTR)idNumber, LENGTH_MSU_ID + 1);
					GetWindowText(GetDlgItem(hwnd, IDC_EDIT_COURSES), (LPSTR)courses, LENGTH_COURSES + 1);

					db.editInformation(cardNumber, name, idNumber, courses);

					HWND hwnd_AttendanceListBox = GetDlgItem(FindWindow(szClassName, NULL), IDC_LISTBOX);

					int selectedIndex = ListView_GetNextItem(hwnd_AttendanceListBox, -1, LVNI_SELECTED);

					ListView_SetItemText(hwnd_AttendanceListBox, selectedIndex, 0, (LPSTR)cardNumber);
					ListView_SetItemText(hwnd_AttendanceListBox, selectedIndex, 1, (LPSTR)name);
					ListView_SetItemText(hwnd_AttendanceListBox, selectedIndex, 2, (LPSTR)idNumber);
					ListView_SetItemText(hwnd_AttendanceListBox, selectedIndex, 3, (LPSTR)courses);


                    EndDialog(hwnd, IDOK);
				}
                break;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                break;
            }
		break;
		default:
            return FALSE;
    }
    return TRUE;
}
