#include <windows.h>
#include <conio.h>
#include "main.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int move(int xfact, int yfact){
    GetWindowRect(handle, &rect);
    MoveWindow(handle, rect.left + xfact * STEP_LEN, rect.top + yfact * STEP_LEN, rect.right-rect.left, rect.bottom-rect.top, FALSE);
    Sleep(TIME_SLEEP);
}
void Wineventproc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD idEventThread, DWORD dwmsEventTime)
{
    handle = GetForegroundWindow();
}
void* keyboard(void* arg){
    SetWinEventHook(
    EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND,
    NULL, Wineventproc,
    0, 0,
    WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
    RegisterHotKey(NULL, VK_LEFT, MOD_SHIFT | MOD_NOREPEAT, VK_LEFT);
    RegisterHotKey(NULL, VK_UP, MOD_SHIFT | MOD_NOREPEAT, VK_UP);
    RegisterHotKey(NULL, VK_RIGHT, MOD_SHIFT | MOD_NOREPEAT, VK_RIGHT);
    RegisterHotKey(NULL, VK_DOWN, MOD_SHIFT | MOD_NOREPEAT, VK_DOWN);
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0){
        if(msg.message == WM_HOTKEY)
        {
            while(GetKeyState(VK_SHIFT)&0x80 && GetKeyState(msg.wParam)&0x80)
            {
                switch (msg.wParam)
                {
                case VK_UP:
                    move(0, -1);
                    break;
                case VK_DOWN:
                    move(0, 1);
                    break;
                case VK_LEFT:
                    move(-1, 0);
                    break;
                case VK_RIGHT:
                    move(1, 0);
                    break;
                }
            }
        }
    }
}
int main(){
    handle = GetForegroundWindow();
    pthread_t thread;
    int status = pthread_create(&thread, NULL, keyboard, &rect);
    pthread_join(thread, NULL);
    if (status != 0) {
        printf("error %d\n",status);
        exit(-1);
    }
    exit(0);
}