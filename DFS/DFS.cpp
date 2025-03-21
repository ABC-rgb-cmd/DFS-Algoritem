#include <iostream>
#include <fstream>
using namespace std;
void readGraph(int& stevilo_vozlisc, int**& C)
{
    ifstream f("graf.txt");
    if (!f) {
        cerr << "Napaka pri odpiranju datoteke!" << endl;
        exit(1);
    }

    int stevilo_povezav;
    f >> stevilo_vozlisc >> stevilo_povezav;
    C = new int* [stevilo_vozlisc];
    for (int i = 0; i < stevilo_vozlisc; i++) {
        C[i] = new int[stevilo_vozlisc] {0};
    }

    int v1, v2, cena;
    for (int i = 0; i < stevilo_povezav; i++) {
        f >> v1 >> v2 >> cena;
        if (v1 < 1 || v1 > stevilo_vozlisc || v2 < 1 || v2 > stevilo_vozlisc) {
            cerr << "Napaka: Indeksi vozlišè (" << v1 << ", " << v2 << ") so izven dovoljenega obsega!" << endl;
            exit(1);
        }
        v1--;
        v2--;

        C[v1][v2] = cena;
        C[v2][v1] = cena;
    }
}
int main()
{
    int stevilo_vozlisc;
    int** C;
    bool enabled = true;
    int choice;
    while (enabled)
    {
        cout << "Iskanje v Globino - Izbira \n1 Preberi graf iz datoteke\n2 Pozeni iskanje iz vozlisca s\n"
            <<"3 Izpis seznama vozlisc in njihovih podaktov\n4 Izpis poti med vozliscema s in d\n5 Konec\n\n"
            <<"Vasa Izbira: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            //Read Graph
            readGraph(stevilo_vozlisc, C);
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

