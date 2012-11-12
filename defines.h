#ifndef CPP_DEFINES
#define CPP_DEFINES

// X and Y coordinates for text boxes
#define X_CARD					10
#define Y_CARD					10
#define X_NAME					10
#define Y_NAME					50
#define X_IDNUMBER				10
#define Y_IDNUMBER				75
#define X_COURSES				10
#define Y_COURSES				100

// Defines for various flags
#define ID_EDIT					101
#define ID_MENU_FILE_EXIT		500
#define ID_MENU_MODE_OPERATOR	9000
#define ID_MENU_MODE_ATTENDANCE 9001
#define IDD_DLG_ADD_MEMBER		102

#ifndef IDC_STATIC
#define IDC_STATIC				(-1)
#endif
#define IDD_DIALOG1             100
//#define IDOK                    1000
#define IDC_EDIT_CARD_NUMBER	1002
#define IDC_EDIT_NAME           1003
#define IDC_EDIT_ID_NUMBER      1004
#define IDC_EDIT_COURSES        1005

// Length of strings accepted by edit boxes
#define LENGTH_CARD_NUMBER		16
#define LENGTH_NAME				30
#define LENGTH_MSU_ID			8
#define LENGTH_COURSES			80

#endif // CPP_DEFINES
