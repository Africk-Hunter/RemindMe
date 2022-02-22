#include "universalClass.hpp"
#include <filesystem>

int UniversalClass::mainLoop() {

    stateStack.push(1);

    while (window.isOpen())
    {
        switch (stateStack.top()) {

        case 1:
            mainMenuState();
            break;

        }
        while (IsIconic(window.getSystemHandle())) { // If window is minimized wait for icon input
            if (MsgWaitForMultipleObjects(0, NULL, FALSE, 5000, QS_ALLINPUT) == WAIT_OBJECT_0)
            {
                while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
                {
                    DispatchMessage(&msg);
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


void UniversalClass::dummyWindowSetup() {

    /* Dummy Window & Icon Setup*/

    wc.cbWndExtra = sizeof(LONG_PTR);
    hWnd = CreateWindowEx(0, lpszClass, L" ", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, this);

    wc.cbClsExtra = 0;
    
    wc.hbrBackground = nullptr;
    wc.hCursor = nullptr;
    wc.hIcon = nullptr;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = lpszClass;
    wc.lpszMenuName = nullptr;
    wc.style = 0;
    RegisterClass(&wc);
    
    ShowWindow(hWnd, SW_HIDE);

    /*---------------------------*/
}

LRESULT CALLBACK UniversalClass::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static NOTIFYICONDATA systemTray;

    //UniversalClass *UniversalClass = (UniversalClass *);
  //  GetWindowLongPtr(hWnd, 0);
    CREATESTRUCT* cs;
    switch (msg)
    {
    case WM_CREATE:

        cs = (CREATESTRUCT*)lParam;
        ::SetWindowLongPtr(hWnd, 0, (LONG_PTR)cs->lpCreateParams);
        break;

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
          //  window.setVisible(true);
         //   ShowWindow(window.getSystemHandle(), SW_SHOWNORMAL | SW_NORMAL);
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

UniversalClass::UniversalClass() {

    window.create(sf::VideoMode(768, 432), L"Hunter's_Reminder_Program");
    window.setFramerateLimit(60);
    loadTextures();
    loadAssets();
    background.setTexture(txtManager.getRef("mainMenu"));
}

void UniversalClass::loadTextures() {

    txtManager.loadTexture("mainMenu", "media/textures/RemindMe_MainMenu.png");
    txtManager.loadTexture("newTask", "media/textures/RemindMe_newTaskMenu.png");
    txtManager.loadTexture("mainMenu_newTask", "media/textures/mainMenu_newTask.png");
    txtManager.loadTexture("mainMenu_currentTask", "media/textures/mainMenu_currentTasks.png");
    txtManager.loadTexture("mainMenu_completedTask", "media/textures/mainMenu_completedtTasks.png");
    txtManager.loadTexture("mainMenu_exit", "media/textures/mainMenu_Exit.png");
    txtManager.loadTexture("settingsCog", "media/textures/settingsCog.png");
    txtManager.loadTexture("blank_image", "media/textures/blank_image.png");

}

void UniversalClass::loadAssets() {

    sf::Font simplePixels;
    simplePixels.loadFromFile("media/fonts/SimplePixels.ttf");
    fontManager.loadResource("simplePixels", simplePixels);

    /* Initialize Resources*/
    Button newTask({ static_cast<float>(window.getView().getSize().x * 0.104166), static_cast<float>(window.getView().getSize().y * 0.3796) }, { static_cast<float>(window.getView().getSize().x * 0.4322), static_cast<float>(window.getView().getSize().y * 0.07407) });
    Button currentTask({ static_cast<float>(window.getView().getSize().x * 0.104166), static_cast<float>(window.getView().getSize().y * .5) }, { static_cast<float>(window.getView().getSize().x * 0.5364), static_cast<float>(window.getView().getSize().y * 0.07407) });
    Button completedTask({ static_cast<float>(window.getView().getSize().x * 0.104166), static_cast<float>(window.getView().getSize().y * 0.62037) }, { static_cast<float>(window.getView().getSize().x * 0.5885416), static_cast<float>(window.getView().getSize().y * 0.07407) });
    Button exitMainMenu({ static_cast<float>(window.getView().getSize().x * 0.104166), static_cast<float>(window.getView().getSize().y * 0.74074) }, { static_cast<float>(window.getView().getSize().x * 0.14583), static_cast<float>(window.getView().getSize().y * 0.07407) });
    Button settingsCog({ static_cast<float>(window.getView().getSize().x * 0.9375), static_cast<float>(window.getView().getSize().y * 0.8888) }, { static_cast<float>(window.getView().getSize().x * 0.052083), static_cast<float>(window.getView().getSize().y * 0.0925925) });
    Button taskNameButton({ static_cast<float>(window.getView().getSize().x * 0.09375), static_cast<float>(window.getView().getSize().y * 0.194444) }, { static_cast<float>(window.getView().getSize().x * 0.802083), static_cast<float>(window.getView().getSize().y * 0.11111) });
    Button taskNotesButton({ static_cast<float>(window.getView().getSize().x * 0.09375), static_cast<float>(window.getView().getSize().y * 0.33101) }, { static_cast<float>(window.getView().getSize().x * 0.802083), static_cast<float>(window.getView().getSize().y * .25) });
    Button dueDateButton({ static_cast<float>(window.getView().getSize().x * 0.09375), static_cast<float>(window.getView().getSize().y * 0.606481) }, { static_cast<float>(window.getView().getSize().x * 0.52083), static_cast<float>(window.getView().getSize().y * 0.0625) });
    Button timeDueButton({ static_cast<float>(window.getView().getSize().x * 0.09375), static_cast<float>(window.getView().getSize().y * 0.694444) }, { static_cast<float>(window.getView().getSize().x * 0.52083), static_cast<float>(window.getView().getSize().y * 0.0625) });
    Button saveTaskButton({ static_cast<float>(window.getView().getSize().x * 0.31770833), static_cast<float>(window.getView().getSize().y * 0.787037) }, { static_cast<float>(window.getView().getSize().x * 0.15625), static_cast<float>(window.getView().getSize().y * 0.0555555) });
    Button discardTaskButt({ static_cast<float>(window.getView().getSize().x * 0.53125), static_cast<float>(window.getView().getSize().y * 0.787037) }, { static_cast<float>(window.getView().getSize().x * 0.15625), static_cast<float>(window.getView().getSize().y * 0.0555555) });

    /* Add resources to their respective resource managers*/
    butManager.loadResource("newTaskButton", newTask);
    butManager.loadResource("currentTaskButton", currentTask);
    butManager.loadResource("completedTaskButton", completedTask);
    butManager.loadResource("exitMainMenuButton", exitMainMenu);
    butManager.loadResource("settingsCogButton", settingsCog);
    butManager.loadResource("taskNameButton", taskNameButton);
    butManager.loadResource("taskNotesButton", taskNotesButton);
    butManager.loadResource("dueDateButton", dueDateButton);
    butManager.loadResource("timeDueButton", timeDueButton);
    butManager.loadResource("saveTaskButton", saveTaskButton);
    butManager.loadResource("discardTaskButt", discardTaskButt);

   // textboxManager.loadResource("taskNameText", taskNameText);
  //  textboxManager.loadResource("taskNotesText", taskNotesText);
   // textboxManager.loadResource("dueDateText", dueDateText);
   // textboxManager.loadResource("timeDueText", timeDueText);

    /* Assign textures to resources if needed */
    butManager.getRef("newTaskButton").setTexture(txtManager.getRef("mainMenu_newTask"));
    butManager.getRef("currentTaskButton").setTexture(txtManager.getRef("mainMenu_currentTask"));
    butManager.getRef("completedTaskButton").setTexture(txtManager.getRef("mainMenu_completedTask"));
    butManager.getRef("exitMainMenuButton").setTexture(txtManager.getRef("mainMenu_exit"));
    butManager.getRef("settingsCogButton").setTexture(txtManager.getRef("settingsCog"));
    butManager.getRef("taskNameButton").setTexture(txtManager.getRef("blank_image"));
    butManager.getRef("taskNotesButton").setTexture(txtManager.getRef("blank_image"));
    butManager.getRef("dueDateButton").setTexture(txtManager.getRef("blank_image"));
    butManager.getRef("timeDueButton").setTexture(txtManager.getRef("blank_image"));
    butManager.getRef("saveTaskButton").setTexture(txtManager.getRef("blank_image"));
    butManager.getRef("discardTaskButt").setTexture(txtManager.getRef("blank_image"));

}

void UniversalClass::deserializeTasks() {

    std::string dirPath = "jsonData/";

	for (auto const& dir_entry : std::filesystem::directory_iterator(dirPath))
	{
        Task loadedTask;

        std::string nDirPath;
        nDirPath = dir_entry.path().string();

		std::ifstream jsonFileReader; // Create the stream
        //std::stringstream jsonString;

        
        jsonFileReader.open(nDirPath, std::ofstream::in); 
		{
			cereal::JSONInputArchive ar_in(jsonFileReader);
            //ar_in(loadedTask);
            loadedTask.serialize(ar_in);
			//editTask.serialize(ar); // Adding contents to stream / making them suitable for JSON
		}
        jsonFileReader.close(); // Close the stream when done

       // taskQueue.push(loadedTask);
        //std::cout << taskQueue.top().getTaskName();
       
	}

}

void UniversalClass::mainMenuState() {

    deserializeTasks();
    
    while (stateStack.top() == 1) {
        
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

                    if (butManager.getRef("newTaskButton").isHovered(window)) {
                        Task newTask;

                        stateStack.push(2);
                        editTaskState(newTask);
                    }
                    if (butManager.getRef("currentTaskButton").isHovered(window)) {
                        //stateStack.push(3);
                       
                    }
                    if (butManager.getRef("completedTaskButton").isHovered(window)) {
                        stateStack.push(4);
                    }
                    if (butManager.getRef("exitMainMenuButton").isHovered(window)) {
                        window.close();
                    }
                }
            }
           
            background.setTexture(txtManager.getRef("mainMenu"));
            window.clear();
            window.draw(background);
            
            butManager.getRef("newTaskButton").drawTo(window);
            butManager.getRef("currentTaskButton").drawTo(window);
            butManager.getRef("completedTaskButton").drawTo(window);
            butManager.getRef("exitMainMenuButton").drawTo(window);
            butManager.getRef("settingsCogButton").drawTo(window);
            window.display();
        }
    }
}

void UniversalClass::editTaskState(Task& editTask) {

	Textbox taskNameText(24, 23, { static_cast<float>(window.getView().getSize().x * 0.59244), static_cast<float>(window.getView().getSize().y * 0.09722) }, { static_cast<float>(window.getView().getSize().x * 0.315104), static_cast<float>(window.getView().getSize().y * 0.226851) }, sf::Color::White, fontManager.getRef("simplePixels"));
	Textbox taskNotesText(24, 101, { static_cast<float>(window.getView().getSize().x * 0.578125), static_cast<float>(window.getView().getSize().y * 0.22453) }, { static_cast<float>(window.getView().getSize().x * 0.329425), static_cast<float>(window.getView().getSize().y * 0.34722222) }, sf::Color::White, fontManager.getRef("simplePixels"));
	Textbox dueDateText(24, 10, { static_cast<float>(window.getView().getSize().x * 0.34375), static_cast<float>(window.getView().getSize().y * 0.0462962) }, { static_cast<float>(window.getView().getSize().x * 0.286458), static_cast<float>(window.getView().getSize().y * 0.6157) }, sf::Color::White, fontManager.getRef("simplePixels"));
	Textbox timeDueText(24, 7, { static_cast<float>(window.getView().getSize().x * 0.34375), static_cast<float>(window.getView().getSize().y * 0.0462962) }, { static_cast<float>(window.getView().getSize().x * 0.286458), static_cast<float>(window.getView().getSize().y * 0.7037037) }, sf::Color::White, fontManager.getRef("simplePixels"));

    background.setTexture(txtManager.getRef("newTask"));

    while (stateStack.top() == 2) {
        sf::Event event;
        while (window.pollEvent(event) && stateStack.top() == 2)
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {

            }
            if (event.type == sf::Event::MouseButtonPressed) {

                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (butManager.getRef("taskNameButton").isHovered(window)) {
                        timeDueText.turnOffSelection();
                        taskNotesText.turnOffSelection();
                        dueDateText.turnOffSelection();
                        taskNameText.reverseSelectState();
                    }
                    else if (butManager.getRef("taskNotesButton").isHovered(window)) {
                        taskNameText.turnOffSelection();
                        dueDateText.turnOffSelection();
                        timeDueText.turnOffSelection();
                        taskNotesText.reverseSelectState();
                    }
                    else if (butManager.getRef("dueDateButton").isHovered(window)) {
                        taskNameText.turnOffSelection();
                        taskNotesText.turnOffSelection();
                        timeDueText.turnOffSelection();
                        dueDateText.reverseSelectState();
                    }
                    else if (butManager.getRef("timeDueButton").isHovered(window)) {
                        taskNameText.turnOffSelection();
                        taskNotesText.turnOffSelection();
                        dueDateText.turnOffSelection();
                        timeDueText.reverseSelectState();
                    }
                    else if (butManager.getRef("saveTaskButton").isHovered(window)) {
                        editTask.saveEnteredData(taskNameText.getTextbox(),
                                                taskNotesText.getTextbox(),
                                                dueDateText.getTextbox(),
                                                timeDueText.getTextbox()); // Saves user entered data to task.

						std::ofstream jsonFile; // Create the stream
                        std::string pathDir = "jsonData/";
						std::string jsonFileName = editTask.getTaskName();
						pathDir += jsonFileName += ".json"; // Create a new file named the Task Name and put it in the jsonData folder

						jsonFile.open(pathDir, std::ofstream::out ); // Open the file for appending
						{
							cereal::JSONOutputArchive ar(jsonFile);
                            ar(CEREAL_NVP(editTask)); // Adding contents to stream / making them suitable for JSON
						}
						jsonFile.close(); // Close the stream when done
                        
                        stateStack.pop();
                    }
                    else if (butManager.getRef("discardTaskButt").isHovered(window)) {
                        stateStack.pop();
                    }
                }
            }
            if (event.type == sf::Event::TextEntered) {
                if (taskNameText.getSelectionState()) {
                    taskNameText.verifyValidInput(event);
                }
                else if (taskNotesText.getSelectionState()) {
                    taskNotesText.verifyValidInput(event);
                }
                else if (dueDateText.getSelectionState()) {
                    dueDateText.verifyValidInput(event);
                }
                else if (timeDueText.getSelectionState()) {
                    timeDueText.verifyValidInput(event);
                }
            }

            window.clear();
            window.draw(background);
            taskNameText.drawTo(window);
            taskNotesText.drawTo(window);
            dueDateText.drawTo(window);
            timeDueText.drawTo(window);
            window.display();
        }
    }

}

