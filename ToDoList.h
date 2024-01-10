#pragma once

#include "resource.h"
#include <Windows.h>
#include <CommCtrl.h>
#include <string>
#include <list>

#define IDC_BUTTON_SAVE  101
#define IDC_EDIT         102
#define IDC_STATIC_TEXT  103
#define IDC_LISTVIEW	 104

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// Yeni eklenen fonksiyon bildirimi
void SaveText(HWND hEdit, HWND hStaticText, HWND hListView);

class ToDoList {
public:
	ToDoList(); //Constructor

	//Add item to the list
	void AddItem(const std::wstring& item);

	//Get List
	const std::list<std::wstring>& GetList() const;

private:
	std::list<std::wstring> itemList;
};