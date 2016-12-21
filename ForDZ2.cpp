// ForDZ2.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "ForDZ2.h"

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szTitle[MAX_LOADSTRING];					// ����� ������ ���������
TCHAR szWindowClass[MAX_LOADSTRING];			// ��� ������ �������� ����

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK MyDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���������� ��� �����.
	MSG msg;
	HACCEL hAccelTable;

	// ������������� ���������� �����
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FORDZ2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FORDZ2));

	// ���� ��������� ���������:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FORDZ2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_FORDZ2);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



char Cyclicheskiy_sdvig(char a)
{
	char maska = a << 4;
	char a_ = (a >> 4) & 0b00001111;
	return a_ | maska;
}

char Obr_cyclicheskiy_sdvig(char a)
{
	char maska = (a >> 4) & 0b00001111;
	char a__ = a << 4;
	return maska | a__;
}

void Gammirovanie(char *in, char *out, int n, int reg, int key)
{
	srand(key);
	char a, b;
	for (int i = 0; i < n; i += 1) memcpy(&a, in + i, 1);
	int gamma = rand();
	if (reg == 1) char b = Cyclicheskiy_sdvig(a) ^ gamma;
	if (reg == 2) char b = Obr_cyclicheskiy_sdvig(a) ^ gamma;
}


char Str[512];
int len = 0;
int key; // ���� ������� �������� ���������� �����

OPENFILENAME ofn; // ��������� ��� ����������� ���� "������� ����" � "���������"
TCHAR NameFile[256] = "MyFile.shf"; // ���� ����� �������� ��� �����



//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND	- ��������� ���� ����������
//  WM_PAINT	-��������� ������� ����
//  WM_DESTROY	 - ������ ��������� � ������ � ���������.
//
//


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message)
	{
	case WM_CHAR: // ��������� ���� �������
		// ���������� ������ � ������
		Str[len] = wParam;
		len++; // ����� ������ ������������� �� 1
		Str[len] = 0; // ������ ������������� �������� � ����� 0
		// ����� ������ �� �����
		hdc = GetDC(hWnd); // �������� �������� ����������
		SetTextColor(hdc, RGB(0, 0, 255));
		TextOut(hdc, 40, 40, Str, len); // ����� ������
		ReleaseDC(hWnd, hdc); // ����������� �������� ����������
		break;
	case WM_COMMAND: // ��������� �� ������ �������� ����
		wmId    = LOWORD(wParam); // �������� ������������� (�����) �������� ����
		wmEvent = HIWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId) // ��������� ��������� ��������� ����
		{
		case IDM_ABOUT: // � ��������� 
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT: // �����
			DestroyWindow(hWnd);
			break;
		case ID_32771: // ������� ����
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = NameFile; // ���� ����� �������� ��� �����
			// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
			// use the contents of szFile to initialize itself.
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = 255;
			ofn.lpstrFilter = "����������� ����� (*.shf)\0*.shf\0��� �����\0*.*\0"; // ������ ��� ����������� ������
			ofn.nFilterIndex = 0;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.lpstrDefExt = "shf"; // ������ ���������� �� ���������

			if (GetOpenFileName(&ofn)) // ���������� ���� "�������", ������� ���������� �������, ���� ������ ������ �������
			{
				// ���������� ���� ��� ����� �����
				if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDialog) == IDOK)
				{
					FILE *pF1;
					char Shifr[512]; // ������������� �����
					pF1 = fopen(NameFile, "rb"); // ��������� ���� ��� ������ � �������� ������
					if (pF1 == 0)
					{
						MessageBox(hWnd, "������ �������� �����. �������� ���� �� ����������", "��������� �� ������", MB_OK | MB_ICONHAND);
						return TRUE;
					}
					fread(&len, sizeof(int), 1, pF1); // ������ ������ ������ � ������
					fread(Shifr, sizeof(char), len, pF1); // ������ ������ �� ����
					fclose(pF1);
					Gammirovanie(Shifr, Str, len, key, 2); // ��������������
					Str[len] = 0; // ������ ������������� 0
					InvalidateRect(hWnd, 0, TRUE); // ����������� ����
				}
				else MessageBox(hWnd, "������ �� ���������. ���� �� ������!!", "���������", MB_OK | MB_ICONHAND);
			}


			break;
		case ID_32772: // ��������� ����
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hWnd; // ������������ ���� 
			ofn.lpstrFilter = "����������� ����� (*.shf)\0*.shf\0��� �����\0*.*\0"; // ����� (������) ��� ������������ ������
			ofn.lpstrFile = NameFile;  // ���� ����� �������� ������ ��� �����
			ofn.nMaxFile = 255;
			ofn.lpstrFileTitle = NULL;//
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
			ofn.lpstrTitle = NULL;
			ofn.lpstrDefExt = "shf"; // ������ ���������� �� ���������
			if (GetSaveFileName(&ofn)) // ���������� ���� "���������", ������� ���������� �������, ���� ������ ������ Ok
			{
				// ���������� ���� ��� ����� �����
				if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDialog) == IDOK)
				{
					char Shifr[512]; // ������������� �����
					Gammirovanie(Str, Shifr, len, key, 1); // ���������� ������

					FILE *pF1;  // ���� ��� ����������
					pF1 = fopen(NameFile, "wb"); // ��� ������������� ������ ���� � �������� ������
					if (pF1 == 0)
					{
						MessageBox(hWnd, "������ �������� �����.", "��������� �� ������", MB_OK | MB_ICONHAND);
						return TRUE;
					}
					fwrite(&len, sizeof(int), 1, pF1); // ������ ������ � ������
					fwrite(Shifr, sizeof(char), len, pF1); // ���������� ������ � ����
					fclose(pF1);
					MessageBox(hWnd, "������ ������� ���������.", "���������", MB_OK | MB_ICONINFORMATION);
				}
				else MessageBox(hWnd, "������ �� ���������. ���� �� ������!!", "���������", MB_OK | MB_ICONHAND);
			}

			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT: // ����������� ����
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �������� ����� ��� ���������...
		SetTextColor(hdc, RGB(0, 0, 255));
		TextOut(hdc, 40, 40, Str, len); // ����� ������
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���������� ��������� ��� ���� "� ���������".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// ���������� ��������� ��� ���� "���� ���������� �����.
INT_PTR CALLBACK MyDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			if (LOWORD(wParam) == IDOK) // ������ ��������� ���� �� ���������� ����
			{
				char Str[32];
				SendDlgItemMessage(hDlg, IDC_EDIT1, WM_GETTEXT, 31, (LPARAM)Str); // ��������� ����� �� ���������� ���� � �������� � ������ Str
				// ������ ������ �� ������
				if (sscanf(Str, "%d", &key) < 1) // ����� �������� �� ��������� �� ������
				{
					MessageBox(hDlg, "�������� ������ �����. ���� ������ ���� ����� ������", "��������� � �������� ������� �����", MB_OK | MB_ICONHAND);
					return (INT_PTR)TRUE; // ����� ��� �������� ����������� ����

				}

			}
			EndDialog(hDlg, LOWORD(wParam)); // �������� ����������� ����
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

