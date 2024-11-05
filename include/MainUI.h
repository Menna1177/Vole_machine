#ifndef MAINUI_H
#define MAINUI_H

#include "Machine.h"
#include <string>

class MainUI
{
    public:
        string inputFileName();
        void displayMenu();
        void inputChoice();
        void run();
};

#endif // MAINUI_H
