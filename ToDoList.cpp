// ToDoList.cpp : Uygulamanın giriş noktasını tanımlar.
//

#include "framework.h"
#include "ToDoList.h"

#define MAX_LOADSTRING 100

// Genel Değişkenler:
HINSTANCE hInst;                                // geçerli örnek
WCHAR szTitle[MAX_LOADSTRING];                  // Başlık çubuğu metni
WCHAR szWindowClass[MAX_LOADSTRING];            // ana pencere sınıfı adı

// Bu kod modülündeki işlevlerin bildirimlerini ilet:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Kodu buraya yerleştirin.

	// Genel dizeleri başlat
	wcscpy_s(szTitle, MAX_LOADSTRING, L"CloudList - An App for To-Do List");
	//LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	//LoadStringW(hInstance, IDC_TODOLIST, szWindowClass, MAX_LOADSTRING);
	wcscpy_s(szWindowClass, MAX_LOADSTRING, L"MainScreen");
	MyRegisterClass(hInstance);

	// Uygulama başlatması gerçekleştir:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TODOLIST));

	MSG msg;

	// Ana ileti döngüsü:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  İŞLEV: MyRegisterClass()
//
//  AMAÇ: Pencere sınıfını kaydeder.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TODOLIST));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TODOLIST);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   İŞLEV: InitInstance(HINSTANCE, int)
//
//   AMAÇ: Örnek tanıtıcısını kaydeder ve ana pencereyi oluşturur
//
//   AÇIKLAMALAR:
//
//        Bu işlevde, örnek tanıtıcısını genel değişkene kaydederiz ve
//        ana program penceresini oluşturur ve görüntüleriz.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Örnek tanıtıcısını genel değişkenimizde depola

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  İŞLEV: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  AMAÇ: Ana pencere için iletileri işler.
//
//  WM_COMMAND  - uygulama menüsünü işle
//  WM_PAINT    - Ana pencereyi boya
//  WM_DESTROY  - bir çıkış iletisi gönder ve dön
//
//

void SaveText(HWND hEdit, HWND hStaticText)
{
	int textLength = GetWindowTextLengthW(hEdit);
	if (textLength > 0)
	{
		// Metin alanından metni al
		std::wstring textBuffer(textLength + 1, L'\0');
		GetWindowTextW(hEdit, &textBuffer[0], textLength + 1);

		SetWindowTextW(hStaticText, textBuffer.c_str());
		// Burada textBuffer içindeki metni başka bir yere kaydedebilirsiniz.
		// Örneğin, bir dosyaya yazabilirsiniz.
		// Şu an sadece bir mesaj kutusuna yazdırıyoruz:
		MessageBox(NULL, textBuffer.c_str(), L"Kaydedilen Metin", MB_OK);
		SetWindowTextW(hStaticText, textBuffer.c_str());
	}
	else
	{
		MessageBox(NULL, L"Metin alanı boş!", L"Uyarı", MB_OK | MB_ICONHAND);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;
	static HWND hStaticText;
	static HWND hButton;
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Menü seçimlerini ayrıştır:
		switch (wmId)
		{
		case IDC_BUTTON_SAVE:
		{
			MessageBox(NULL, L"Butona Tıklandı!", L"Bilgi", MB_OK);
			// SaveText fonksiyonunu çağır
			SaveText(hEdit, hStaticText);
		}
		break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Buraya hdc kullanan herhangi bir çizim kodu ekleyin...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CREATE:
	{
		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT",
			L"",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10,
			10,
			200,
			20,
			hWnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL);

		if (hEdit == NULL)
		{
			MessageBox(hWnd, L"Metin alanı oluşturulamadı!", L"Hata", MB_OK | MB_ICONHAND);
		}

		hButton = CreateWindow(
			L"BUTTON",
			L"Kaydet",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			250,
			10,
			120,
			25,
			hWnd,
			(HMENU)IDC_BUTTON_SAVE,
			hInst,
			NULL);

		hStaticText = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 10, 50, 200, 20, hWnd, (HMENU)IDC_STATIC_TEXT, GetModuleHandle(NULL), NULL);
	}
	break;

	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// Hakkında kutusu için ileti işleyicisi.
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