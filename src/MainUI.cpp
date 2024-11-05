#include "MainUI.h"
#include <iostream>

using namespace std;


void MainUI::run()
{
    Machine machine;
    string filename;

    cout << "Enter the filename with Vole program: ";
    cin >> filename;

    try {
        machine.loadProgramFile(filename);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return;
    }

    int choice;
    cout << "Choose an option:\n";
    cout << "1. Run program as a whole\n";
    cout << "2. Run program step by step\n";
    cin >> choice;

    if (choice == 1) {
        machine.run();
        machine.OutputState();
    } else if (choice == 2) {
        machine.runStepByStep();
    } else {
        cout << "Invalid choice.\n";
    }
}
