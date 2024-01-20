#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "SFML/Graphics.hpp"
#include <iostream>

class ScreenManager {
    public:
        sf::Window window;

        ScreenManager(int width, int height);
        ScreenManager(int width, int height, std::string windowTitle);

        void update();
        bool isRunning();
};

#endif //SCREENMANAGER_H