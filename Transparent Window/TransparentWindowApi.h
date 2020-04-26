#pragma once
#include "TransparentWindow.h"

class TransparentWindowApi {
public:
	auto Execute(const std::wstring& processName)	-> void;
	auto Transparency()								-> uint8_t& { return m_transparency; }
private:
	std::uint8_t m_transparency = 0xFF;
	TransparentWindow m_tWnd;
};

