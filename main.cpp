// ForDZ2.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ ïðèëîæåíèÿ.
//

#include "stdafx.h"
#include "ForDZ2.h"

#define MAX_LOADSTRING 100

// Ãëîáàëüíûå ïåðåìåííûå:
HINSTANCE hInst;								// òåêóùèé ýêçåìïëÿð
TCHAR szTitle[MAX_LOADSTRING];					// Òåêñò ñòðîêè çàãîëîâêà
TCHAR szWindowClass[MAX_LOADSTRING];			// èìÿ êëàññà ãëàâíîãî îêíà

// Îòïðàâèòü îáúÿâëåíèÿ ôóíêöèé, âêëþ÷åííûõ â ýòîò ìîäóëü êîäà:
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

 	// TODO: ðàçìåñòèòå êîä çäåñü.
	MSG msg;
	HACCEL hAccelTable;

	// Èíèöèàëèçàöèÿ ãëîáàëüíûõ ñòðîê
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FORDZ2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Âûïîëíèòü èíèöèàëèçàöèþ ïðèëîæåíèÿ:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FORDZ2));

	// Öèêë îñíîâíîãî ñîîáùåíèÿ:
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
//  ÔÓÍÊÖÈß: MyRegisterClass()
//
//  ÍÀÇÍÀ×ÅÍÈÅ: ðåãèñòðèðóåò êëàññ îêíà.
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
//   ÔÓÍÊÖÈß: InitInstance(HINSTANCE, int)
//
//   ÍÀÇÍÀ×ÅÍÈÅ: ñîõðàíÿåò îáðàáîòêó ýêçåìïëÿðà è ñîçäàåò ãëàâíîå îêíî.
//
//   ÊÎÌÌÅÍÒÀÐÈÈ:
//
//        Â äàííîé ôóíêöèè äåñêðèïòîð ýêçåìïëÿðà ñîõðàíÿåòñÿ â ãëîáàëüíîé ïåðåìåííîé, à òàêæå
//        ñîçäàåòñÿ è âûâîäèòñÿ íà ýêðàí ãëàâíîå îêíî ïðîãðàììû.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Ñîõðàíèòü äåñêðèïòîð ýêçåìïëÿðà â ãëîáàëüíîé ïåðåìåííîé

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
int key; // Ñóäà çàïèøåì çíà÷åíèå ñåêðåòíîãî êëþ÷à

OPENFILENAME ofn; // Ñòðóêòóðà äëÿ ñòàíäàðòíûõ îêîí "Îòêðûòü ôàéë" è "Ñîõðàíèòü"
TCHAR NameFile[256] = "MyFile.shf"; // Ñþäà áóäåò çàïèñàíî èìÿ ôàéëà



//
//  ÔÓÍÊÖÈß: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ÍÀÇÍÀ×ÅÍÈÅ:  îáðàáàòûâàåò ñîîáùåíèÿ â ãëàâíîì îêíå.
//
//  WM_COMMAND	- îáðàáîòêà ìåíþ ïðèëîæåíèÿ
//  WM_PAINT	-Çàêðàñèòü ãëàâíîå îêíî
//  WM_DESTROY	 - ââåñòè ñîîáùåíèå î âûõîäå è âåðíóòüñÿ.
//
//


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message)
	{
	case WM_CHAR: // Ñîîáùåíèå ââîä ñèìâîëà
		// Çàïèñûâàåì ñèìâîë â ñòðîêó
		Str[len] = wParam;
		len++; // Äëèíà ñòðîêè óâåëè÷èâàåòñÿ íà 1
		Str[len] = 0; // Ñòðîêà çàêàí÷èâàåòñÿ ñèìâîëîì ñ êîäîì 0
		// Âûâîä ñòðîêè íà ýêðàí
		hdc = GetDC(hWnd); // Ïîëó÷àåì êîíòåêñò óñòðîéñòâà
		SetTextColor(hdc, RGB(0, 0, 255));
		TextOut(hdc, 40, 40, Str, len); // Âûâîä ñòðîêè
		ReleaseDC(hWnd, hdc); // Îñâîáîæäàåì êîíòåêñò óñòðîéñòâà
		break;
	case WM_COMMAND: // Ñîîáùåíèå îò âûáîðà ýëåìåíòà ìåíþ
		wmId    = LOWORD(wParam); // Ïîëó÷àåì èäåíòèôèêàòîð (íîìåð) ýëåìåíòà ìåíþ
		wmEvent = HIWORD(wParam);
		// Ðàçîáðàòü âûáîð â ìåíþ:
		switch (wmId) // Îáðàáîòêà îòäåëüíûõ ýëåìåíòîâ ìåíþ
		{
		case IDM_ABOUT: // Î ïðîãðàììå 
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT: // Âûõîä
			DestroyWindow(hWnd);
			break;
		case ID_32771: // Îòêðûòü ôàéë
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = NameFile; // Ñþäà áóäåò çàïèñàíî èìÿ ôàéëà
			// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
			// use the contents of szFile to initialize itself.
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = 255;
			ofn.lpstrFilter = "Øèôðîâàííûå ôàéëû (*.shf)\0*.shf\0Âñå ôàéëû\0*.*\0"; // Ôèëüòð äëÿ îòîáðàæåíèÿ ôàéëîâ
			ofn.nFilterIndex = 0;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.lpstrDefExt = "shf"; // Ñòðîêà ðàñøèðåíèå ïî óìîë÷àíèþ

			if (GetOpenFileName(&ofn)) // Ïîÿâëÿåòñÿ îêíî "Îòêðûòü", ôóíêöèÿ âîçâðàùàåò èñòèííî, åñëè íàæàòà êíîïêà Îòêðûòü
			{
				// Îòîáðàæàåì îêíî äëÿ ââîäà êëþ÷à
				if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDialog) == IDOK)
				{
					FILE *pF1;
					char Shifr[512]; // Çàøèôðîâàííûé òåêñò
					pF1 = fopen(NameFile, "rb"); // Îòêðûâàåì ôàéë äëÿ ÷òåíèÿ â äâîè÷íîì ðåæèìå
					if (pF1 == 0)
					{
						MessageBox(hWnd, "Îøèáêà îòêðûòèÿ ôàéëà. Âîçìîæíî ôàéë íå ñóùåñòâóåò", "Ñîîáùåíèå îá îøèáêå", MB_OK | MB_ICONHAND);
						return TRUE;
					}
					fread(&len, sizeof(int), 1, pF1); // ×èòàåì Ðàçìåð äàííûõ â áàéòàõ
					fread(Shifr, sizeof(char), len, pF1); // ×èòàåì äàííûå èç ôàéë
					fclose(pF1);
					Gammirovanie(Shifr, Str, len, key, 2); // Ðàñøèôðîâûâàåì
					Str[len] = 0; // Ñòðîêà çàêàí÷èâàåòñÿ 0
					InvalidateRect(hWnd, 0, TRUE); // Ïåðåðèñîâêà îêíà
				}
				else MessageBox(hWnd, "Äàííûå íå ïðî÷èòàíû. Êëþ÷ íå ââåäåí!!", "Ñîîáùåíèå", MB_OK | MB_ICONHAND);
			}


			break;
		case ID_32772: // Ñîõðàíèòü ôàéë
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hWnd; // ðîäèòåëüñêîå îêíî 
			ofn.lpstrFilter = "Øèôðîâàííûå ôàéëû (*.shf)\0*.shf\0Âñå ôàéëû\0*.*\0"; // Ìàñêà (ôèëüòð) äëÿ îòîáðàæàåìûõ ôàéëîâ
			ofn.lpstrFile = NameFile;  // Ñþäà áóäåò çàïèñàíî ïîëíîå èìÿ ôàéëà
			ofn.nMaxFile = 255;
			ofn.lpstrFileTitle = NULL;//
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
			ofn.lpstrTitle = NULL;
			ofn.lpstrDefExt = "shf"; // Ñòðîêà ðàñøèðåíèå ïî óìîë÷àíèþ
			if (GetSaveFileName(&ofn)) // Ïîÿâëÿåòñÿ îêíî "Ñîõðàíèòü", ôóíêöèÿ âîçâðàùàåò èñòèííî, åñëè íàæàòà êíîïêà Ok
			{
				// Îòîáðàæàåì îêíî äëÿ ââîäà êëþ÷à
				if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDialog) == IDOK)
				{
					char Shifr[512]; // Çàøèôðîâàííûé òåêñò
					Gammirovanie(Str, Shifr, len, key, 1); // Øèôðîâàíèå äàííûõ

					FILE *pF1;  // Ôàéë äëÿ ñîõðàíåíèÿ
					pF1 = fopen(NameFile, "wb"); // Äëÿ çàøèôðîâàííûõ äàííûõ ôàéë â äâîè÷íîì ðåæèìå
					if (pF1 == 0)
					{
						MessageBox(hWnd, "Îøèáêà îòêðûòèÿ ôàéëà.", "Ñîîáùåíèå îá îøèáêå", MB_OK | MB_ICONHAND);
						return TRUE;
					}
					fwrite(&len, sizeof(int), 1, pF1); // Ðàçìåð äàííûõ â áàéòàõ
					fwrite(Shifr, sizeof(char), len, pF1); // Çàïèñûâàåì äàííûå â ôàéë
					fclose(pF1);
					MessageBox(hWnd, "Äàííûå óñïåøíî ñîõðàíåíû.", "Ñîîáùåíèå", MB_OK | MB_ICONINFORMATION);
				}
				else MessageBox(hWnd, "Äàííûå íå ñîõðàíåíû. Êëþ÷ íå ââåäåí!!", "Ñîîáùåíèå", MB_OK | MB_ICONHAND);
			}

			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT: // Ïåðåðèñîâêà îêíà
		hdc = BeginPaint(hWnd, &ps);
		// TODO: äîáàâüòå ëþáîé êîä îòðèñîâêè...
		SetTextColor(hdc, RGB(0, 0, 255));
		TextOut(hdc, 40, 40, Str, len); // Âûâîä ñòðîêè
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

// Îáðàáîò÷èê ñîîáùåíèé äëÿ îêíà "Î ïðîãðàììå".
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

// Îáðàáîò÷èê ñîîáùåíèé äëÿ îêíà "Ââîä ñåêðåòíîãî êëþ÷à.
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
			if (LOWORD(wParam) == IDOK) // ×èòàåì ñåêðåòíûé êëþ÷ èç òåêñòîâîãî ïîëÿ
			{
				char Str[32];
				SendDlgItemMessage(hDlg, IDC_EDIT1, WM_GETTEXT, 31, (LPARAM)Str); // Ïðî÷èòàëè òåêñò èç òåêñòîâîãî ïîëÿ è çàïèñàëè â ñòðóêó Str
				// ×èòàåì äàííûå èç ñòðîêè
				if (sscanf(Str, "%d", &key) < 1) // Öåëîå çíà÷åíèå íå ïðî÷èòàíî èç ñòðîêè
				{
					MessageBox(hDlg, "Íåâåðíûé ôîðìàò êëþ÷à. Êëþ÷ äîëæåí áûòü öåëûì ÷èñëîì", "Ñîîáùåíèå î íåâåðíîì ôîðìàòå êëþ÷à", MB_OK | MB_ICONHAND);
					return (INT_PTR)TRUE; // Âûõîä áåç çàêðûòèÿ äèàëîãîâîãî îêíà

				}

			}
			EndDialog(hDlg, LOWORD(wParam)); // Çàêðûòèå äèàëîãîâîãî îêíà
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

