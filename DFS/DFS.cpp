#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
using namespace std;
struct Vozlisce {
    int predhodnik;
    int dolzina;
    int status; // 0 = nepregledano, 1 = v obdelavi, 2 = razvito
    int indeks;
    string ime;
};
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
void depthSearch(int** C, int s, int stevilo_vozlisc) {
    if (s < 0 || s >= stevilo_vozlisc) {
        cout << "Invalid starting vertex!" << endl;
        return;
    }

    vector<Vozlisce> vozlisca(stevilo_vozlisc);

    // Inicializacija vseh vozlišè
    for (int i = 0; i < stevilo_vozlisc; i++) {
        vozlisca[i].status = 0;  // nepregledano
        vozlisca[i].dolzina = -1;
        vozlisca[i].predhodnik = -1;
        vozlisca[i].indeks = i;
        vozlisca[i].ime = "V" + to_string(i);
    }

    // Inicializacija zaèetnega vozlišèa
    vozlisca[s].status = 1; // v obdelavi
    vozlisca[s].dolzina = 0;
    vozlisca[s].predhodnik = -1;

    stack<int> sklad;
    sklad.push(s);

    while (!sklad.empty()) {
        int v = sklad.top();
        sklad.pop();

        // Oznaèimo vozlišèe kot razvito
        vozlisca[v].status = 2;

        // Pregledamo vse sosede vozlišèa v
        for (int u = 0; u < stevilo_vozlisc; u++) {
            if (C[v][u] != 0 && vozlisca[u].status == 0) { // Èe obstaja povezava in ni obiskan
                vozlisca[u].status = 1; // v obdelavi
                vozlisca[u].dolzina = vozlisca[v].dolzina + 1;
                vozlisca[u].predhodnik = v;
                sklad.push(u);
            }
        }
    }

}

int main()
{
    int stevilo_vozlisc;
    int** C = nullptr;
    bool enabled = true;
    int choice;
    int s;
    while (enabled)
    {
        cout << "\nIskanje v Globino - Izbira \n1 Preberi graf iz datoteke\n2 Pozeni iskanje iz vozlisca s\n"
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
            cout << "\nVpisite vozlisce s: ";
            cin >> s;
            if (C != nullptr)
            {
                depthSearch(C, s, stevilo_vozlisc);
            }
            else
            {

            }
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

