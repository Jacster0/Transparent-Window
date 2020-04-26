#pragma once
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>

class TransparentWindow {
private:
	auto SetWindowTransparency(const std::wstring& processName)			-> void;
	auto FindProcessId(const std::wstring& processName)					-> DWORD;
	static auto CALLBACK EnumWindowCallback(HWND hWnd, LPARAM lParam)	-> BOOL;
	auto SetTransparency(HWND hWnd, std::uint8_t transparency)			-> BOOL;
private:
	static HWND m_hWnd;
	std::uint8_t m_transparency;
	friend class TransparentWindowApi;
};

