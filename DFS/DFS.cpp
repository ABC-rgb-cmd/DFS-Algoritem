#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    bool enabled = true;
    int choice;
    while (enabled)
    {
        cout << "Iskanje v Globino - Izbira \n1 Preberi graf iz datoteke\n2 Pozeni iskanje iz vozilisca s\n"
            <<"3 Izpis seznama vozilisc in njihovih podaktov\n4 Izpis poti med voziliscema s in d\n5 Konec";
        switch (choice)
        {
        case 1:
            //Read Graph
            break;
        case 2:
            //Search
            break;
        case 3:
            //info dump
            break;
        case 4:
            //path output
            break;
        case 5:
            enabled = false;
            break;
        default:
            break;
        }
    }
}

