#include "NativeWindow.h"

#include <windows.h>

namespace {
constexpr wchar_t kWindowTitle[] = L"puterforge";
}

bool NativeWindow::Create(HINSTANCE instance, const std::wstring& title) {
    WNDCLASSW windowClass{};
    windowClass.hInstance = instance;
    windowClass.lpfnWndProc = &NativeWindow::WindowProc;
    windowClass.lpszClassName = kClassName;
    windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);

    if (!RegisterClassW(&windowClass)) {
        const DWORD error = GetLastError();
        if (error != ERROR_CLASS_ALREADY_EXISTS) {
            return false;
        }
    }

    hwnd_ = CreateWindowExW(
        0,
        kClassName,
        title.empty() ? kWindowTitle : title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1100,
        700,
        nullptr,
        nullptr,
        instance,
        this);

    if (!hwnd_) {
        return false;
    }

    ShowWindow(hwnd_, SW_SHOW);
    UpdateWindow(hwnd_);
    return true;
}

int NativeWindow::Run() {
    MSG message{};
    while (GetMessageW(&message, nullptr, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
    return static_cast<int>(message.wParam);
}

LRESULT CALLBACK NativeWindow::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    auto* self = reinterpret_cast<NativeWindow*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

    if (message == WM_NCCREATE) {
        auto* create = reinterpret_cast<CREATESTRUCTW*>(lParam);
        self = static_cast<NativeWindow*>(create->lpCreateParams);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
        self->hwnd_ = hwnd;
    }

    switch (message) {
    case WM_PAINT: {
        PAINTSTRUCT paint{};
        HDC dc = BeginPaint(hwnd, &paint);
        RECT client{};
        GetClientRect(hwnd, &client);
        SetBkMode(dc, TRANSPARENT);

        HFONT title = CreateFontW(34, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                  DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                  CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Segoe UI");
        HFONT body = CreateFontW(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                 DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                 CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Segoe UI");

        HGDIOBJ previous = SelectObject(dc, title);
        TextOutW(dc, 32, 28, L"puterforge", 9);
        SelectObject(dc, body);
        TextOutW(dc, 32, 82, L"native workspace online", 23);
        TextOutW(dc, 32, 114, L"foundation expanded", 19);

        RECT panel{32, 170, client.right - 32, client.bottom - 32};
        Rectangle(dc, panel.left, panel.top, panel.right, panel.bottom);
        TextOutW(dc, panel.left + 20, panel.top + 20, L"workspace", 9);
        TextOutW(dc, panel.left + 20, panel.top + 54, L"editor", 6);
        TextOutW(dc, panel.left + 20, panel.top + 82, L"models", 6);
        TextOutW(dc, panel.left + 20, panel.top + 110, L"agents", 6);
        TextOutW(dc, panel.left + 20, panel.top + 138, L"terminal", 8);

        SelectObject(dc, previous);
        DeleteObject(title);
        DeleteObject(body);
        EndPaint(hwnd, &paint);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProcW(hwnd, message, wParam, lParam);
    }
}
