/**
 * Agenda de Contacte — C++ Console Application
 * =============================================
 * Aplicatie de gestiune a contactelor care ruleaza in linia de comanda.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include <algorithm>
using namespace std;

struct Contact {
    string Nume, Prenume, adresa, judet, oras, tara, telefon, email;
    time_t momentAdaugare;
};

void afiseazaMeniu();
void adaugaContact(vector<Contact>& agenda);
void afisareAgenda(vector<Contact>& agenda);
void cautaContact(const vector<Contact>& agenda);
void modificaContact(vector<Contact>& agenda);
void stergereContact(vector<Contact>& agenda);
void exportaCSV(const vector<Contact>& agenda);
void salveazaInFisier(vector<Contact>& agenda);
void incarcaDinFisier(vector<Contact>& agenda);
bool telefonExista(const vector<Contact>& agenda, const string& tel);
bool emailExista(const vector<Contact>& agenda, const string& email);

bool ordoneazaCeleMaiNoiPrimele(const Contact& a, const Contact& b) { return a.momentAdaugare > b.momentAdaugare; }

int main() {
    vector<Contact> agenda;
    incarcaDinFisier(agenda);
    bool ruleaza = true;
    int optiune;
    cout << "Bun venit in agenda!\n";
    while (ruleaza) {
        afiseazaMeniu();
        cout << "\nAlege o optiune: ";
        cin >> optiune;
        cin.ignore();
        switch (optiune) {
            case 1: adaugaContact(agenda); break;
            case 2: afisareAgenda(agenda); break;
            case 3: cautaContact(agenda); break;
            case 4: modificaContact(agenda); break;
            case 5: stergereContact(agenda); break;
            case 6: exportaCSV(agenda); break;
            case 7: salveazaInFisier(agenda); ruleaza = false; cout << "\nDatele au fost salvate. La revedere!\n"; break;
            default: cout << "\nOptiune invalida! Incercati alta optiune!\n";
        }
    }
    return 0;
}

void afiseazaMeniu() {
    cout << "\n--- Meniu ---\n1. Adauga contact\n2. Afisare agenda\n3. Cauta contact\n4. Modifica contact\n5. Stergere contact\n6. Exporta in CSV\n7. Iesire\n";
}

bool telefonExista(const vector<Contact>& agenda, const string& tel) { for (const auto& c : agenda) if (c.telefon == tel) return true; return false; }
bool emailExista(const vector<Contact>& agenda, const string& email) { for (const auto& c : agenda) if (c.email == email) return true; return false; }

string citesteNumeValid(string mesaj) {
    string input;
    do {
        cout << mesaj; getline(cin, input);
        if (input.empty()) { cout << "Eroare: Nu ati introdus nimic!\n"; continue; }
        bool valid = true; for (char c : input) if (!isalpha(c) && !isspace(c)) valid = false;
        if (!valid) { cout << "Eroare: Valoare invalida!\n"; input.clear(); continue; }
        bool cuvantNou = true;
        for (char& c : input) { if (isalpha(c)) { c = cuvantNou ? toupper(c) : tolower(c); cuvantNou = false; } else if (isspace(c)) cuvantNou = true; }
        return input;
    } while (true);
}

string citesteTelefonValid(string mesaj) {
    string input;
    do {
        cout << mesaj; getline(cin, input); bool valid = !input.empty() && input.length() >= 10;
        for (size_t i = 0; valid && i < input.length(); ++i) if (!((i == 0 && input[i] == '+') || isdigit(input[i]))) valid = false;
        if (valid) return input; cout << "Eroare: Telefon invalid!\n";
    } while (true);
}

string citesteEmailValid(string mesaj) {
    string input;
    do {
        cout << mesaj; getline(cin, input); size_t at = input.find('@'), dot = input.find('.', at);
        if (!input.empty() && input.find(' ') == string::npos && at != string::npos && at > 0 && at < input.length()-1 && dot != string::npos && dot > at+1 && dot < input.length()-1) { for (char& c : input) c = tolower(c); return input; }
        cout << "Eroare: Email invalid!\n";
    } while (true);
}

string citesteJudetValid(string mesaj) { return citesteNumeValid(mesaj); }
string citesteOrasValid(string mesaj) { return citesteJudetValid(mesaj); }
string citesteTaraValid(string mesaj) { return citesteJudetValid(mesaj); }

void adaugaContact(vector<Contact>& agenda) {
    Contact c;
    c.Nume = citesteNumeValid("Introduceti Nume: "); c.Prenume = citesteNumeValid("Introduceti Prenume: ");
    cout << "Introduceti adresa: "; getline(cin, c.adresa);
    c.judet = citesteJudetValid("Introduceti judet: "); c.oras = citesteOrasValid("Introduceti oras: "); c.tara = citesteTaraValid("Introduceti tara: ");
    do { c.telefon = citesteTelefonValid("Introduceti telefon: "); if (telefonExista(agenda, c.telefon)) cout << "Eroare: Telefon duplicat!\n"; else break; } while (true);
    do { c.email = citesteEmailValid("Introduceti e-mail: "); if (emailExista(agenda, c.email)) cout << "Eroare: Email duplicat!\n"; else break; } while (true);
    c.momentAdaugare = time(nullptr); agenda.push_back(c); cout << "Contact adaugat cu succes!\n";
}

void afisareAgenda(vector<Contact>& agenda) {
    if (agenda.empty()) { cout << "\nAgenda este goala.\n"; return; }
    sort(agenda.begin(), agenda.end(), ordoneazaCeleMaiNoiPrimele);
    for (size_t i = 0; i < agenda.size(); ++i) cout << agenda[i].Nume << " " << agenda[i].Prenume << " - " << agenda[i].telefon << " - " << agenda[i].email << "\n";
}

void cautaContact(const vector<Contact>& agenda) {
    string termen; cout << "Introduceti termenul: "; getline(cin, termen); bool gasit = false;
    for (const auto& c : agenda) if (c.Nume.find(termen) != string::npos || c.Prenume.find(termen) != string::npos || c.telefon.find(termen) != string::npos) { cout << c.Nume << " " << c.Prenume << " - " << c.telefon << "\n"; gasit = true; }
    if (!gasit) cout << "Niciun contact nu a fost gasit.\n";
}

void modificaContact(vector<Contact>& agenda) { cout << "Modificarea contactelor este disponibila in versiunea originala.\n"; }
void stergereContact(vector<Contact>& agenda) { cout << "Stergerea contactelor este disponibila in versiunea originala.\n"; }

void exportaCSV(const vector<Contact>& agenda) {
    ofstream f("contacte_export.csv"); f << "Nume,Prenume,Telefon,Email,Adresa_Strada,Oras,Judet,Tara,Timestamp_Adaugare\n";
    for (const auto& c : agenda) f << c.Nume << "," << c.Prenume << "," << c.telefon << "," << c.email << "," << c.adresa << "," << c.oras << "," << c.judet << "," << c.tara << "," << c.momentAdaugare << "\n";
}

void salveazaInFisier(vector<Contact>& agenda) {
    ofstream f("contacte.txt"); for (const auto& c : agenda) f << c.Nume << "\n" << c.Prenume << "\n" << c.adresa << "\n" << c.judet << "\n" << c.oras << "\n" << c.tara << "\n" << c.telefon << "\n" << c.email << "\n" << c.momentAdaugare << "\n";
}

void incarcaDinFisier(vector<Contact>& agenda) {
    ifstream f("contacte.txt"); Contact c; string t;
    while (getline(f, c.Nume) && getline(f, c.Prenume) && getline(f, c.adresa) && getline(f, c.judet) && getline(f, c.oras) && getline(f, c.tara) && getline(f, c.telefon) && getline(f, c.email) && getline(f, t)) { try { c.momentAdaugare = stoll(t); } catch (...) { c.momentAdaugare = time(nullptr); } agenda.push_back(c); }
}
