#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "Notework_manager.h"


using namespace std;

class Class
{
public:
    int value;

    Class(int a) : value(a)
    {
        cout << value << " pricol " << endl;
    }
	~Class()
    {
        cout << value << " pizda " << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
	srand(time(NULL));

    Notework_manager manager = Notework_manager();

	

	for (int i = 0; i <= 5; ++i)
	{
        manager.Tick();
	}

    /*
	Notework_manager A();

	
    std::cout << "Hello World!\n";


    vector<Class*> a;

    Class* A1 = new Class(1);
    Class* A2 = new Class(2);
    Class* A3 = new Class(3);
    Class* A4 = new Class(4);
    Class* A5 = new Class(5);

	


	
    a.push_back((A1));
    a.push_back((A2));
    a.push_back((A3));
    a.push_back((A4));
    a.push_back((A5));

    for (int i = a.size() - 1; i > -1; --i)
    {
        cout << a[i]->value << " ";
    }

    cout << endl;
	
    for (int i = a.size() - 1; i > -1; --i)
    {
        if (a[i]->value % 2 != 0)
        {
            cout << " delete - " << a[i]->value << endl;

            //auto del = a.begin() + i;
        	
            a.erase(a.begin() + i);
        }
    }
	
    cout << endl;
	
    for (int i = a.size() - 1; i > -1; --i)
    {
        cout << a[i]->value << " ";
    }
    
    cout << endl;
        */
}
