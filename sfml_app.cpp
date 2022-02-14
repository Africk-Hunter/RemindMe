#include <SFML/Graphics.hpp>

#include <windows.h>
#include <shellapi.h>
#include <iostream>
#include "resource.h"

/* Notes */
// Name: RemindMe!
// - Reminder Sounds
//      - Roblox Badge, You got mail




#define TRAY_ICON_ID (WM_USER + 2)
#define WM_MESSAGE (WM_USER + 1)

sf::RenderWindow window(sf::VideoMode(850, 478), L"Hunter's_Reminder_Program");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LPCWSTR lpszClass = L"__hidden__";

int main()
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    WNDCLASS wc;
    HWND hWnd;
    MSG msg;
    bool minimized = 0;

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = nullptr;
    wc.hCursor = nullptr;
    wc.hIcon = nullptr;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = lpszClass;
    wc.lpszMenuName = nullptr;
    wc.style = 0;
    RegisterClass(&wc);

    hWnd = CreateWindowEx( 0, lpszClass, L" ", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL );
    ShowWindow(hWnd, SW_HIDE);

    sf::RectangleShape background;
    background.setSize({ (float)window.getSize().x, (float)window.getSize().y });


    while (window.isOpen())
    {
        
        if (IsIconic(window.getSystemHandle())) {
            minimized = 1;
            while (GetMessage(&msg, nullptr, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
   
        sf::Event event;
        while (window.pollEvent(event))
        {
          if (event.type == sf::Event::Closed) {
            window.close();
            }
          if (event.type == sf::Event::Resized) {

           }


        }

    }

        
        window.clear();
        window.draw(background);
        window.display();
    
    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static NOTIFYICONDATA systemTray;

    switch (msg)
    {
    case WM_CREATE:
        std::memset(&systemTray, 0, sizeof(systemTray));
        systemTray.cbSize = sizeof(systemTray);
        systemTray.hWnd = hWnd;
        systemTray.uID = 0;
        systemTray.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
        systemTray.uCallbackMessage = WM_APP + 1;
        systemTray.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
        lstrcpy(systemTray.szTip, L"RemindMe!");
        Shell_NotifyIcon(NIM_ADD, &systemTray);
        Shell_NotifyIcon(NIM_SETVERSION, &systemTray);
        return 0;
    case WM_APP + 1:
        switch (lParam)
        {
        case WM_LBUTTONDBLCLK:
            window.setVisible(true);
            ShowWindow(window.getSystemHandle(), SW_SHOWNORMAL | SW_NORMAL);
            break;
        }
        break;
    case WM_DESTROY:
        Shell_NotifyIcon(NIM_DELETE, &systemTray);
        MessageBox(nullptr, L" ", L" ", MB_OK);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}




/*




int main()
{

    // RemindMe!

   
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    NOTIFYICONDATA systemTray;
    HWND hwnd;
    MSG msg;
    hwnd = FindWindow(NULL, L"Hunter's_Reminder_Program");

    systemTray.cbSize = sizeof(systemTray);
    systemTray.hWnd = hwnd;
    systemTray.uID = TRAY_ICON_ID;
    systemTray.uVersion = NOTIFYICON_VERSION;
    systemTray.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE( IDI_ICON1 ));
    systemTray.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    systemTray.uCallbackMessage = WM_MESSAGE;
    //systemTray.szTip = Double Click Me!;
    Shell_NotifyIcon(NIM_ADD, &systemTray);


  
   // ShowWindow(hwnd, SW_MINIMIZE);
   
   // strcpy(systemTray.szTip, "My Application");
    //systemTray.uCallbackMessage = WM_LBUTTONDOWN;
    
   

    window.setVisible(false);
    while (GetMessage(&msg, nullptr, 0, 0)) {
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
           // if (event.type == sf::Event::Resized) {
                
           // }
            
            
        }
        DispatchMessage(&msg);
    }
           // TranslateMessage(&msg);
            
        
        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HMENU popMenu = CreatePopupMenu();
    switch (msg)
    {
    case WM_MESSAGE:
            switch (lParam)
            {
                case WM_LBUTTONDOWN:
                    window.setVisible(false);
                    std::cout << "Hello" << std::endl;
                    break;
                case WM_RBUTTONDOWN:
                    
                    AppendMenu(popMenu, MF_STRING, ID_MENU_SHOW, L"Show");
                    AppendMenu(popMenu, MF_STRING, This should be a ID to handle the menu itemID_MENU_EXIT, L"Exit");
                    POINT pCursor;
                    GetCursorPos(&pCursor);
                    TrackPopupMenu(popMenu, TPM_LEFTBUTTON | TPM_RIGHTALIGN, pCursor.x, pCursor.y, 0, hWnd, NULL);
                    break;
                case WM_LBUTTONDBLCLK:
                    window.setVisible(false);
                    std::cout << "Hello" << std::endl;
                    break;
                case WM_CONTEXTMENU:
                    break;
              
            }
            break;
    }
    return DefWindowProc(hWnd,msg,wParam,lParam);
}
*/