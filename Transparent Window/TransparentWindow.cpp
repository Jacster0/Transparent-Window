#include "TransparentWindow.h"

#define COLOR_RED     FOREGROUND_RED   |  FOREGROUND_INTENSITY                            
#define COLOR_GREEN   FOREGROUND_GREEN |  FOREGROUND_INTENSITY                            
#define COLOR_BLUE    FOREGROUND_BLUE  |  FOREGROUND_INTENSITY                            
#define COLOR_WHITE   FOREGROUND_RED   |  FOREGROUND_GREEN        | FOREGROUND_BLUE        

HWND TransparentWindow::m_hWnd = nullptr;

auto TransparentWindow::SetWindowTransparency(const std::wstring& processName) -> void {
    const DWORD id = FindProcessId(processName);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (id != 0) {
        EnumWindows(EnumWindowCallback, id);

        if (m_hWnd) {
            if (SetTransparency(m_hWnd, m_transparency)) {
                SetConsoleTextAttribute(hConsole, COLOR_GREEN);
                std::cout << "Window transparency successfully set" << std::endl;
            }

            else {
                SetConsoleTextAttribute(hConsole, COLOR_RED);
                std::cout << "Error: Could not set Window transparency. Errorcode: " << GetLastError() << std::endl;
            }
        }
        else {
            SetConsoleTextAttribute(hConsole, COLOR_RED);
            std::cout << "Error: Could not attach process to handle because handle is null" << std::endl;
        }
    }

    else {
        SetConsoleTextAttribute(hConsole, COLOR_RED);
        std::cout << "Error: Could not find an ID of the process" << std::endl;

    }

    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
}

auto TransparentWindow::FindProcessId(const std::wstring& processName) -> DWORD {
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile)) {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo)) {
        if (!processName.compare(processInfo.szExeFile)) {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}

auto TransparentWindow::EnumWindowCallback(HWND hWnd, LPARAM lParam) -> BOOL {
    DWORD lpdwProcessId;
    GetWindowThreadProcessId(hWnd, &lpdwProcessId);

    if (lpdwProcessId == lParam) {
        std::cout << "Process ID found" << std::endl;
        m_hWnd = hWnd;
        return FALSE;
    }
    return TRUE;
}

auto TransparentWindow::SetTransparency(HWND hWnd, std::uint8_t transparency) -> BOOL {
    long wAttr = GetWindowLong(hWnd, GWL_EXSTYLE);
    SetWindowLong(hWnd, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);

    return SetLayeredWindowAttributes(hWnd, 0, transparency, 0x02);
}