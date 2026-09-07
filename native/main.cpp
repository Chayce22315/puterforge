#include <windows.h>

namespace {

constexpr wchar_t kClassName[] = L"PuterForgeWindow";
constexpr wchar_t kTitle[] = L"puterforge";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT: {
        PAINTSTRUCT paint{};
        HDC dc = BeginPaint(hwnd, &paint);

        RECT client{};
        GetClientRect(hwnd, &client);

        SetBkMode(dc, TRANSPARENT);
        SetTextColor(dc, RGB(230, 230, 230));

        HFONT titleFont = CreateFontW(
            36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");

        HFONT bodyFont = CreateFontW(
            18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");

        HFONT previous = static_cast<HFONT>(SelectObject(dc, titleFont));
        TextOutW(dc, 32, 28, L"puterforge", 9);

        SelectObject(dc, bodyFont);
        TextOutW(dc, 32, 84, L"native shell initialized", 23);
        TextOutW(dc, 32, 116, L"c++ / windows / cmake", 22);

        SelectObject(dc, previous);
        DeleteObject(titleFont);
        DeleteObject(bodyFont);

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

} // namespace

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int showCommand) {
    WNDCLASSW windowClass{};
    windowClass.hInstance = instance;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.lpszClassName = kClassName;
    windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);

    if (!RegisterClassW(&windowClass)) {
        return 1;
    }

    HWND hwnd = CreateWindowExW(
        0,
        kClassName,
        kTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        900,
        600,
        nullptr,
        nullptr,
        instance,
        nullptr);

    if (!hwnd) {
        return 1;
    }

    ShowWindow(hwnd, showCommand);
    UpdateWindow(hwnd);

    MSG message{};
    while (GetMessageW(&message, nullptr, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }

    return static_cast<int>(message.wParam);
}
