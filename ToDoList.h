#pragma once

#include "resource.h"
#include <Windows.h>
#include <string>
#define IDC_BUTTON_SAVE  101
#define IDC_EDIT         102
#define IDC_STATIC_TEXT  103

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// Yeni eklenen fonksiyon bildirimi
void SaveText(HWND hEdit, HWND hStaticText);