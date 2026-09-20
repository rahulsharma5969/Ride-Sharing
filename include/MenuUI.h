#ifndef MENU_UI_H
#define MENU_UI_H

#include "RideManager.h"
#include <iostream>
#include <limits>

/**
 * @brief Menu-driven Console UI for interacting with the Ride Sharing Platform.
 */
class MenuUI {
private:
    RideManager manager;

    // Helper functions for user input
    int getIntInput(const std::string& prompt);
    double getDoubleInput(const std::string& prompt);
    std::string getStringInput(const std::string& prompt);

    // Sub-menus
    void riderMenu();
    void driverMenu();
    void adminMenu();
    void runAutomatedDemo();

public:
    MenuUI();
    void start();
};

#endif // MENU_UI_H
