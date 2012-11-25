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
 *	Header Block: defines Header
 *	Module Name: 
 *		defines Header
 *	Authors:
 *		Dylan, John, William
 *	Where it fits:
 *		This file has the defines for values used elsewhere in the program.
 *	When it was written, and revised:
 *		Continuous revision, and revisement (see github commit history)
 *	Why it exists:
 *		Collective place for the defines.
 *	How it uses datastructures, algorithms, and control:
 *		N/A
 */

/**
 *	NOTES/TODO: 
 *
 */

#ifndef H_DEFINES
#define H_DEFINES

// X and Y coordinates for text boxes
#define X_CARD					10
#define Y_CARD					10
#define X_NAME					10
#define Y_NAME					50
#define X_IDNUMBER				10
#define Y_IDNUMBER				75
#define X_COURSES				10
#define Y_COURSES				100


/*******************************************
 * Defines for flags/messages
 * Each section increases X by 1, where 1X00
 *******************************************/
// ID for Controls (IDC)
#define IDC_EDIT_CARDNUMBER		1000
#define IDC_EDIT_NAME			1001
#define IDC_EDIT_IDNUMBER		1002
#define IDC_EDIT_COURSES		1003
#define IDC_LISTBOX				1004
#define	IDC_BUTTON_EDITMEMBER	1005
#define IDC_STATIC				(-1)

// ID for Menus (IDM)
#define IDM_MENU_FILE_EXIT		1100
#define IDM_MENU_MODE_OPERATOR	1101
#define IDM_MENU_MODE_ATTENDANCE 1102

// ID For Dialog Boxes
#define IDD_DLG_ADDMEMBER		1200
#define IDD_DLG_EDITMEMBER		1201

/*******************************************
 * End defines for flags/messages
 *******************************************/


// Length of strings accepted by edit boxes
#define LENGTH_CARD_NUMBER		16
#define LENGTH_NAME				30
#define LENGTH_MSU_ID			8
#define LENGTH_COURSES			80

#endif // H_DEFINES
