#include "TransparentWindowApi.h"
#include "TransparentWindowApi.h"

auto TransparentWindowApi::Execute(const std::wstring& processName) -> void {
	m_tWnd.m_transparency = m_transparency;
	m_tWnd.SetWindowTransparency(processName);
}
