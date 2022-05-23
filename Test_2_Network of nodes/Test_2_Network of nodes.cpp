#include <iostream>
#include <functional>
#include "Notework_manager.h"
#include <windows.h>

using namespace std;

int main()
{
    //setlocale(LC_ALL, "ru");
	srand(time(NULL));
	
	Notework_manager manager;

    manager.StartSimulator(5);


	for (int i = 0; i <= 5; ++i)
	{
        manager.Tick();
        Sleep(1000);
	}

}
