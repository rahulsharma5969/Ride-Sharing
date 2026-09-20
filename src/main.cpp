#include "../include/MenuUI.h"
#include <iostream>

int main() {
    try {
        MenuUI ui;
        ui.start();
    } catch (const std::exception& e) {
        std::cerr << "[Fatal Error] Exception caught in main: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "[Fatal Error] Unknown error occurred." << std::endl;
        return 1;
    }
    return 0;
}
