#include <windows.h>

#include "NativeWindow.h"

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int) {
    NativeWindow window;
    if (!window.Create(instance, L"puterforge")) {
        MessageBoxW(nullptr, L"failed to create the puterforge window.", L"puterforge", MB_ICONERROR | MB_OK);
        return 1;
    }

    return window.Run();
}
