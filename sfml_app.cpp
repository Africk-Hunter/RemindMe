#include "universalClass.hpp"


/* Notes */
// Name: RemindMe!
// - Reminder Sounds
//      - Roblox Badge, You got mail
// 400% Increase Size
// Stack of Task objects

/* Dimensions Relative to Screen Size */
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
        - Setting Cog Size:
            - X: 0.052083
            - Y: 0.0925925
        - Setting Cog Pos:
            - X: 0.9375
            - Y: 0.8888
*/
int main() {

    UniversalClass mainSoft;

    mainSoft.mainLoop();
    return 0;

}















/*
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
    std::stack<int> stateStack;
    HINSTANCE hInstance = GetModuleHandle(nullptr);
    WNDCLASS wc;
    HWND hWnd;
    MSG msg;


   

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

   

    loadTextures(txtManager);
    loadAssets(butManager, txtManager);
    stateStack.push(1); // Make the default state the main menu

    while (window.isOpen())
    {
        background.setTexture(txtManager.getRef("mainMenu"));
        
        while (IsIconic(window.getSystemHandle())) { // If window is minimzed wait for icon input
            if (MsgWaitForMultipleObjects(0, NULL, FALSE, 5000, QS_ALLINPUT) == WAIT_OBJECT_0)
            {
                while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
                {
                    DispatchMessage(&msg);
                }
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
          if (event.type == sf::Event::MouseButtonPressed) {

              if (event.mouseButton.button == sf::Mouse::Left) {

                  switch(stateStack.top()) // Psuedo State Machine
                      case 1: {
                            if (butManager.getRef("newTaskButton").isHovered(window)) {
                            stateStack.push(2);
                            }
                            if (butManager.getRef("currentTaskButton").isHovered(window)) {
                                stateStack.push(3);
                            }
                            if (butManager.getRef("completedTaskButton").isHovered(window)) {
                                stateStack.push(4);
                            }
                            if (butManager.getRef("exitMainMenuButton").isHovered(window)) {
                                window.close();
                            }
                      }
                  
              }
          }
        }



        window.clear();
        window.draw(background);
        if (stateStack.top() == 1) { // If Main Menu state, draw these elements
            butManager.getRef("newTaskButton").drawTo(window);
            butManager.getRef("currentTaskButton").drawTo(window);
            butManager.getRef("completedTaskButton").drawTo(window);
            butManager.getRef("exitMainMenuButton").drawTo(window);
        }
        butManager.getRef("settingsCogButton").drawTo(window);
        window.display();
    }

   // return static_cast<int>(msg.wParam);
    return 0;
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
    txtManager.loadTexture("settingsCog", "media/textures/settingsCog.png");
    
}

void loadAssets(ResourceManager<Button>& butManager, TextureManager& txtManager) {

   
    Button newTask({ static_cast<float>(window.getView().getSize().x * 0.104166), static_cast<float>(window.getView().getSize().y * 0.3796) }, { static_cast<float>(window.getView().getSize().x * 0.4322), static_cast<float>(window.getView().getSize().y * 0.07407) });
    Button currentTask({ static_cast<float>(window.getView().getSize().x * 0.104166), static_cast<float>(window.getView().getSize().y * .5) }, { static_cast<float>(window.getView().getSize().x * 0.5364), static_cast<float>(window.getView().getSize().y * 0.07407) });
    Button completedTask({ static_cast<float>(window.getView().getSize().x * 0.104166), static_cast<float>(window.getView().getSize().y * 0.62037) }, { static_cast<float>(window.getView().getSize().x * 0.5885416), static_cast<float>(window.getView().getSize().y * 0.07407) });
    Button exitMainMenu({ static_cast<float>(window.getView().getSize().x * 0.104166), static_cast<float>(window.getView().getSize().y * 0.74074) }, { static_cast<float>(window.getView().getSize().x * 0.14583), static_cast<float>(window.getView().getSize().y * 0.07407) });
    Button settingsCog({ static_cast<float>(window.getView().getSize().x * 0.9375), static_cast<float>(window.getView().getSize().y * 0.8888) }, { static_cast<float>(window.getView().getSize().x * 0.052083), static_cast<float>(window.getView().getSize().y * 0.0925925) });

 
    butManager.loadResource("newTaskButton", newTask);
    butManager.loadResource("currentTaskButton", currentTask);
    butManager.loadResource("completedTaskButton", completedTask);
    butManager.loadResource("exitMainMenuButton", exitMainMenu);
    butManager.loadResource("settingsCogButton", settingsCog);

  
    butManager.getRef("newTaskButton").setTexture(txtManager.getRef("mainMenu_newTask"));
    butManager.getRef("currentTaskButton").setTexture(txtManager.getRef("mainMenu_currentTask"));
    butManager.getRef("completedTaskButton").setTexture(txtManager.getRef("mainMenu_completedTask"));
    butManager.getRef("exitMainMenuButton").setTexture(txtManager.getRef("mainMenu_exit"));
    butManager.getRef("settingsCogButton").setTexture(txtManager.getRef("settingsCog"));

    */