#include <SFML/Graphics.hpp>

#include <windows.h>
#include <shellapi.h>
#include <iostream>
#include "resource.h"
#include "texture_manager.hpp"
#include "resourceManager.hpp"
#include "Button.hpp"

/* Notes */
// Name: RemindMe!
// - Reminder Sounds
//      - Roblox Badge, You got mail
// 400% Increase Size

/* Dimensions Relate to Screen Size */
/*
    Main Menu:
        - Button One Size
            - X: 0.4322
            - Y: 0.07407
        - Button One Pos:
            - X: 0.104166
            - Y: 0.3796
        - Button Two Size
            - X: 0.5364
            - Y: 0.07407
        - Button Two Pos:
            - X: 0.104166
            - Y: .5
        - Button Three Size
            - X: 0.5885416
            - Y: 0.07407
        - Button Three Pos:
            - X: 0.104166
            - Y: 0.62037
        - Button Four Size:
            - X: 0.14583
            - Y: 0.07407
        - Button Four Pos:
            - X: 0.104166
            - Y: 0.74074



*/


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void loadTextures(TextureManager&);
void loadAssets(ResourceManager<Button>&, TextureManager&);


sf::RenderWindow window(sf::VideoMode(768, 432), L"Hunter's_Reminder_Program");




LPCWSTR lpszClass = L"__hidden__";

int main()
{
    TextureManager txtManager;
    ResourceManager<Button> butManager;
    sf::Sprite background;
    HINSTANCE hInstance = GetModuleHandle(nullptr);
    WNDCLASS wc;
    HWND hWnd;
    MSG msg;


    loadTextures(txtManager);
    loadAssets(butManager, txtManager);


    /* Dummy Window & Icon Setup*/

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
    hWnd = CreateWindowEx(0, lpszClass, L" ", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);
    ShowWindow(hWnd, SW_HIDE);

    /*---------------------------*/

    while (window.isOpen())
    {
        background.setTexture(txtManager.getRef("mainMenu"));
        
        while (IsIconic(window.getSystemHandle())) { // If window is minimzed wait for icon input
            if (MsgWaitForMultipleObjects(0, NULL, FALSE, 5000, QS_ALLINPUT) == WAIT_OBJECT_0)
            {
                while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
                {
                    DispatchMessage(&msg);
                    std::cout << "why am i here";
                }
            }
           // if (GetMessage(&msg, nullptr, 0, 0)) {
             //   TranslateMessage(&msg);
             //   DispatchMessage(&msg);
                
          //  }
            std::cout << "Message Worked";
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
        window.clear();
        window.draw(background);
        butManager.getRef("newTaskButton").drawTo(window);
        butManager.getRef("currentTaskButton").drawTo(window);
        butManager.getRef("completedTaskButton").drawTo(window);
        butManager.getRef("exitMainMenuButton").drawTo(window);
        window.display();
    }

        
        
    
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


void loadTextures(TextureManager &txtManager) {

    txtManager.loadTexture("mainMenu", "media/textures/RemindMe_MainMenu.png");
    txtManager.loadTexture("mainMenu_newTask", "media/textures/mainMenu_newTask.png");
    txtManager.loadTexture("mainMenu_currentTask", "media/textures/mainMenu_currentTasks.png");
    txtManager.loadTexture("mainMenu_completedTask", "media/textures/mainMenu_completedtTasks.png");
    txtManager.loadTexture("mainMenu_exit", "media/textures/mainMenu_Exit.png");
    
}

void loadAssets(ResourceManager<Button>& butManager, TextureManager& txtManager) {

    /* Initialize Resources*/
    Button newTask({ static_cast<float>(window.getView().getSize().x * 0.104166), static_cast<float>(window.getView().getSize().y * 0.3796) }, { static_cast<float>(window.getView().getSize().x * 0.4322), static_cast<float>(window.getView().getSize().y * 0.07407) });
    Button currentTask({ static_cast<float>(window.getView().getSize().x * 0.104166), static_cast<float>(window.getView().getSize().y * .5) }, { static_cast<float>(window.getView().getSize().x * 0.5364), static_cast<float>(window.getView().getSize().y * 0.07407) });
    Button completedTask({ static_cast<float>(window.getView().getSize().x * 0.104166), static_cast<float>(window.getView().getSize().y * 0.62037) }, { static_cast<float>(window.getView().getSize().x * 0.5885416), static_cast<float>(window.getView().getSize().y * 0.07407) });
    Button exitMainMenu({ static_cast<float>(window.getView().getSize().x * 0.104166), static_cast<float>(window.getView().getSize().y * 0.74074) }, { static_cast<float>(window.getView().getSize().x * 0.14583), static_cast<float>(window.getView().getSize().y * 0.07407) });


    /* Add resources to their respective resource managers*/
    butManager.loadResource("newTaskButton", newTask);
    butManager.loadResource("currentTaskButton", currentTask);
    butManager.loadResource("completedTaskButton", completedTask);
    butManager.loadResource("exitMainMenuButton", exitMainMenu);

    /* Assign textures to resources if needed */
    butManager.getRef("newTaskButton").setTexture(txtManager.getRef("mainMenu_newTask"));
    butManager.getRef("currentTaskButton").setTexture(txtManager.getRef("mainMenu_currentTask"));
    butManager.getRef("completedTaskButton").setTexture(txtManager.getRef("mainMenu_completedTask"));
    butManager.getRef("exitMainMenuButton").setTexture(txtManager.getRef("mainMenu_exit"));
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