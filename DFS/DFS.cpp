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
vector<Vozlisce> initializeGraph(int stevilo_vozlisc)
{
    vector<Vozlisce> vozlisca(stevilo_vozlisc);

    // Inicializacija vseh vozlišè
    for (int i = 0; i < stevilo_vozlisc; i++) {
        vozlisca[i].status = 0;  // nepregledano
        vozlisca[i].dolzina = -1;
        vozlisca[i].predhodnik = -1;
        vozlisca[i].indeks = i;
        vozlisca[i].ime = "V" + to_string(i);
    }
    return vozlisca;
}
void depthSearch(int** C, int s, vector<Vozlisce>& vozlisca) {
    if (s < 0 || s >= vozlisca.size()) {
        cout << "Invalid starting vertex!" << endl;
        return;
    }
    vozlisca = initializeGraph(vozlisca.size());
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
        for (int u = 0; u < vozlisca.size(); u++) {
            if (C[v][u] != 0 && vozlisca[u].status == 0) { // Èe obstaja povezava in ni obiskan
                vozlisca[u].status = 1; // v obdelavi
                vozlisca[u].dolzina = vozlisca[v].dolzina + 1;
                vozlisca[u].predhodnik = v;
                sklad.push(u);
            }
        }
    }

}
void outputGraph(vector<Vozlisce> vozlisca)
{
    cout << "Rezultati iskanja v globino (DFS):\n";
    for (int i = 0; i < vozlisca.size(); i++) {
        cout << "Vozlisce " << i << " - "
            << "Indeks: " << vozlisca[i].indeks << ", "
            << "Status: " << vozlisca[i].status << ", "
            << "Predhodnik: " << vozlisca[i].predhodnik << ", "
            << "Dolzina od vozlisca s: " << vozlisca[i].dolzina
            << endl;
    }
}
void outputPath(vector<Vozlisce> vozlisca, int s, int v)
{
    if (v == s)
    {
        cout << "Pot je: " << vozlisca[v].ime + " ";
        return;
    }
    else if (vozlisca[v].predhodnik == -1)
    {
        cout << "Med " << vozlisca[s].ime << " in " << vozlisca[v].ime << " ni poti" << endl;
    }
    else
    {
        outputPath(vozlisca, s, vozlisca[v].predhodnik);
        cout << vozlisca[v].ime + " ";
    }
}
int main()
{
    int stevilo_vozlisc;
    int** C = nullptr;
    bool enabled = true;
    int choice;
    int s;
    int v;
    vector<Vozlisce> vozlisca;
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
            vozlisca = initializeGraph(stevilo_vozlisc);
            break;
        case 2:
            //Search
            cout << "\nVpisite vozlisce s: ";
            cin >> s;
            if (C != nullptr)
            {
                depthSearch(C, s, vozlisca);
            }
            else
            {

            }
            break;
        case 3:
            //info dump
            if (C != nullptr)
            {
                outputGraph(vozlisca);
            }
            break;
        case 4:
            //path output
            if(s>-1 && s<stevilo_vozlisc)
            {
                cout << "\nVpisite vozlisce v: ";
                cin >> v;
                outputPath(vozlisca, s, v);
            }
            break;
        case 5:
            enabled = false;
            break;
        default:
            break;
        }
    }
}

