#pragma once

#include <windows.h>
#include <string>

class NativeWindow {
public:
    bool Create(HINSTANCE instance, const std::wstring& title);
    int Run();

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    static constexpr wchar_t kClassName[] = L"PuterForgeNativeWindow";

    HWND hwnd_ = nullptr;
};
