#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdio>

using namespace std;

struct Uzytkownik {
    int idUzytkownika;
    string loginUzytkownika;
    string hasloUzytkownika;
};

struct Znajomy {
    int id;
    int idUzytkownika;
    string imie;
    string nazwisko;
    string telefon;
    string email;
    string adres;
};

string wczytajLinie ();
char wczytajZnak ();
int wczytajLiczbe ();

int odczytajZnajomychZPliku (vector <Znajomy>& znajomi, int idZalogowanegoUzytkownika);
void zapiszZnajomegoDoPliku (Znajomy znajomyDoZapisania);
void zaktualizujZnajomegoWPliku (vector <Znajomy>& znajomi, int indeksModyfikowanegoAdresata);
int utworzIDodajNowegoZnajomego (vector <Znajomy>& znajomi, int idZalogowanegoUzytkownika, int idOstatniegoZnajomego);
void szukajZnajomychPoImieniu (vector <Znajomy>& znajomi);
void szukajZnajomychPoNazwisku (vector <Znajomy>& znajomi);
void wyswietlWszystkichZnajomych (vector <Znajomy>& znajomi);
void usunZnajomego (vector <Znajomy>& znajomi);
void edytujZnajomego (vector <Znajomy>& znajomi);
void wypiszNaEkranBrakKontaktow ();
void wrocDoMenuGlownego ();
void wypiszMenuZmianyDanych ();
void odczytajUzytkownikowZPliku (vector <Uzytkownik>& uzytkownicy);
int zalogujUzytkownika (vector <Uzytkownik>& uzytkownicy);
void zapiszUzytkownikaDoPliku (Uzytkownik uzytkownikDoZapisania);
void zarejestrujUzytkownika (vector <Uzytkownik>& uzytkownicy);
void zmienHaslo (vector <Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika);
void zaktualizujUzytkownikowWPliku (vector <Uzytkownik>& uzytkownicy);
void usunZnajomegoZPliku (vector <Znajomy>& znajomi, vector<Znajomy>::iterator itr);

int main() {
    vector <Uzytkownik> uzytkownicy;
    vector <Znajomy> znajomi;
    int wybranaOpcjaWMenuGlownym = 0;
    int idZalogowanegoUzytkownika = 0;
    int idOstatniegoZnajomego = 0;

    odczytajUzytkownikowZPliku (uzytkownicy);


    while (1) {
        if (idZalogowanegoUzytkownika == 0) {
            system ("cls");
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "3. Zamknij program" << endl;

            wybranaOpcjaWMenuGlownym = wczytajLiczbe ();
            switch (wybranaOpcjaWMenuGlownym) {
            case 1:
                idZalogowanegoUzytkownika = zalogujUzytkownika (uzytkownicy);
                idOstatniegoZnajomego = odczytajZnajomychZPliku (znajomi, idZalogowanegoUzytkownika);
                break;
            case 2:
                zarejestrujUzytkownika (uzytkownicy);
                break;
            case 3:
                cout << "Zamykanie programu";
                exit(0);
            default:
                cout << "Wpisano niepoprawny znak, prosze wybrac opcje" << endl;
                Sleep (2000);
            }
        } else {
            system ("cls");
            cout << "MENU GLOWNE" << endl;
            cout << "Zalogowano jako " << uzytkownicy[idZalogowanegoUzytkownika - 1].loginUzytkownika << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl;

            wybranaOpcjaWMenuGlownym = wczytajLiczbe ();
            switch (wybranaOpcjaWMenuGlownym) {
            case 1:
                idOstatniegoZnajomego = utworzIDodajNowegoZnajomego (znajomi, idZalogowanegoUzytkownika, idOstatniegoZnajomego);
                break;
            case 2:
                szukajZnajomychPoImieniu (znajomi);
                break;
            case 3:
                szukajZnajomychPoNazwisku (znajomi);
                break;
            case 4:
                wyswietlWszystkichZnajomych (znajomi);
                break;
            case 5:
                usunZnajomego (znajomi);
                break;
            case 6:
                edytujZnajomego (znajomi);
                break;
            case 7:
                zmienHaslo (uzytkownicy, idZalogowanegoUzytkownika);
                break;
            case 8:
                Sleep (200);
                znajomi.clear();
                idZalogowanegoUzytkownika = 0;
                cout << "Wylogowano" << endl;
                Sleep (500);
                break;
            default:
                cout << "Wpisano niepoprawny znak, prosze wybrac opcje" << endl;
                Sleep (2000);
            }
        }
    }
    return 0;
}

int utworzIDodajNowegoZnajomego (vector <Znajomy>& znajomi, int idZalogowanegoUzytkownika, int idOstatniegoZnajomego) {
    system ("cls");
    cout << "1. Dodaj adresata" << endl;

    Znajomy tymczasowy;

    cout << "Imie: ";
    tymczasowy.imie = wczytajLinie ();
    cout << "Nazwisko: ";
    tymczasowy.nazwisko = wczytajLinie ();
    cout << "Numer telefonu: ";
    tymczasowy.telefon = wczytajLinie ();
    cout << "Adres e-mail: ";
    tymczasowy.email = wczytajLinie ();
    cout << "Adres: ";
    tymczasowy.adres = wczytajLinie ();

    if (idOstatniegoZnajomego == 0) {
        tymczasowy.id = 1;
    } else {
        tymczasowy.id = idOstatniegoZnajomego + 1;
    }

    tymczasowy.idUzytkownika = idZalogowanegoUzytkownika;

    znajomi.push_back(tymczasowy);
    zapiszZnajomegoDoPliku (tymczasowy);

    idOstatniegoZnajomego = tymczasowy.id;

    Sleep (200);
    cout << "Dodano znajomego!" << endl;
    Sleep (500);

    return idOstatniegoZnajomego;
}

void usunZnajomego (vector <Znajomy>& znajomi) {
    int idUsuwanegoAdresata = 0;
    char potwierdzenieUsuniecia;
    int liczbaZnajomych = znajomi.size();
    bool znalezionoIdWZnajomych = false;

    system ("cls");
    cout << "5. Usun adresata" << endl;

    cout << "Wpisz ID adresata ktorego chcesz usunac" << endl;
    idUsuwanegoAdresata = wczytajLiczbe ();

    for (int i = 0; i < liczbaZnajomych; i++)
    {
        if (idUsuwanegoAdresata == znajomi[i].id)
        {
            znalezionoIdWZnajomych = true;
            break;
        }
    }

    if (znalezionoIdWZnajomych == false)
    {
        Sleep (200);
        cout << "Nie znaleziono adresata o podanym ID" << endl;
        wrocDoMenuGlownego ();
        return;
    }

    cout << "Potwierdz naciskajac klawisz 't'" << endl;
    potwierdzenieUsuniecia = wczytajZnak ();

    if (znalezionoIdWZnajomych == true && potwierdzenieUsuniecia == 't') {
        for (vector<Znajomy>::iterator itr = znajomi.begin(), koniec = znajomi.end(); itr != koniec; itr++) {
            if (itr->id == idUsuwanegoAdresata) {
                usunZnajomegoZPliku (znajomi, itr);
                znajomi.erase(itr);
                Sleep (200);
                cout << "Usunieto znajomego!" << endl;
                Sleep (500);
                break;
            }
        }
    }
}

void usunZnajomegoZPliku (vector <Znajomy>& znajomi, vector<Znajomy>::iterator itr)
{
    int idUsuwanegoAdresata = itr->id;
    fstream plik1, plik2;
    plik1.open ("Adresaci.txt", ios::in);
    plik2.open ("Adresaci_tymczasowy.txt", ios::out | ios::app);
    if (plik1.good()) {
        string liniaWPliku = "";
        while (getline(plik1, liniaWPliku)) {
            int id = 0;
            size_t rozdzielenieWyrazow = liniaWPliku.find('|');
            id = atoi(liniaWPliku.substr(0, rozdzielenieWyrazow).c_str());
            if (id != idUsuwanegoAdresata)
            {
                plik2 << liniaWPliku << endl;
            }
        }
    } else {
        cout << "nie udalo sie otwozyc pliku" << endl;
    }
    plik1.close();
    plik2.close();

    remove("Adresaci.txt");
    rename( "Adresaci_tymczasowy.txt", "Adresaci.txt" );
}

void szukajZnajomychPoImieniu (vector <Znajomy>& znajomi) {
    int liczbaZapisanychZnajomych = znajomi.size();

    system ("cls");
    cout << "2. Wyszukaj po imieniu" << endl;

    if (liczbaZapisanychZnajomych < 1) {
        wypiszNaEkranBrakKontaktow ();
    } else {
        bool czyZnalezionoZnajomego = false;
        string szukaneImie = "";

        cout << "Wpisz imie:";
        szukaneImie = wczytajLinie ();

        for (int i = 0; i < liczbaZapisanychZnajomych; i++) {
            if (znajomi[i].imie == szukaneImie) {
                cout << endl;
                cout << "id: " << znajomi[i].id << endl;
                cout << "imie: " << znajomi[i].imie << endl;
                cout << "nazwisko: " << znajomi[i].nazwisko << endl;
                cout << "numer telefonu: " << znajomi[i].telefon << endl;
                cout << "adres e-mail: " << znajomi[i].email << endl;
                cout << "adres: " << znajomi[i].adres << endl;
                czyZnalezionoZnajomego = true;
            }
        }
        if (!czyZnalezionoZnajomego) {
            wypiszNaEkranBrakKontaktow ();
        } else {
            wrocDoMenuGlownego ();
        }
    }
}

void szukajZnajomychPoNazwisku (vector <Znajomy>& znajomi) {
    int liczbaZapisanychZnajomych = znajomi.size();

    system ("cls");
    cout << "3. Wyszukaj po nazwisku" << endl;

    if (liczbaZapisanychZnajomych < 1) {
        wypiszNaEkranBrakKontaktow ();
    } else {
        bool czyZnalezionoZnajomego = false;
        string szukaneNazwisko = "";

        cout << "Wpisz nazwisko:";
        szukaneNazwisko = wczytajLinie ();

        for (int i = 0; i < liczbaZapisanychZnajomych; i++) {
            if (znajomi[i].nazwisko == szukaneNazwisko) {
                cout << endl;
                cout << "id: " << znajomi[i].id << endl;
                cout << "imie: " << znajomi[i].imie << endl;
                cout << "nazwisko: " << znajomi[i].nazwisko << endl;
                cout << "numer telefonu: " << znajomi[i].telefon << endl;
                cout << "adres e-mail: " << znajomi[i].email << endl;
                cout << "adres: " << znajomi[i].adres << endl;
                czyZnalezionoZnajomego = true;
            }
        }
        if (!czyZnalezionoZnajomego) {
            wypiszNaEkranBrakKontaktow ();
        } else {
            wrocDoMenuGlownego ();
        }
    }
}

void wyswietlWszystkichZnajomych (vector <Znajomy>& znajomi) {
    int liczbaZapisanychZnajomych = znajomi.size();

    system ("cls");

    cout << "4. Wyswietl wszystkich adresatow" << endl;
    if (liczbaZapisanychZnajomych > 0) {
        for (int i = 0; i < liczbaZapisanychZnajomych; i++) {
            cout << endl;
            cout << "id: " << znajomi[i].id << endl;
            cout << "imie: " << znajomi[i].imie << endl;
            cout << "nazwisko: " << znajomi[i].nazwisko << endl;
            cout << "numer telefonu: " << znajomi[i].telefon << endl;
            cout << "adres e-mail: " << znajomi[i].email << endl;
            cout << "adres: " << znajomi[i].adres << endl;
        }
        wrocDoMenuGlownego ();
    } else {
        wypiszNaEkranBrakKontaktow ();
    }
}

void wypiszNaEkranBrakKontaktow () {
    cout << "Brak kontaktow do wyswietlenia" << endl;
    Sleep (2000);
}

void wrocDoMenuGlownego () {
    cout << endl << "Wcisnij dowolny klawisz zeby wrocic do menu glownego";
    cin.get();
    Sleep (500);
}

int odczytajZnajomychZPliku (vector <Znajomy>& znajomi, int idZalogowanegoUzytkownika) {
    fstream plik;
    Znajomy tymczasowy;
    int idOstatniegoZnajomego = 0;

    plik.open ("Adresaci.txt", ios::in);
    if (plik.good()) {
        string liniaWPliku = "";
        while (getline(plik, liniaWPliku)) {
            string id = "";
            size_t rozdzielenieWyrazow = liniaWPliku.find('|');
            size_t poprzednieRozdzielenieWyrazow = 0;
            int numerWyrazu = 1;
            while (numerWyrazu <= 7) {
                switch (numerWyrazu) {
                case 1:
                    id = liniaWPliku.substr(poprzednieRozdzielenieWyrazow, rozdzielenieWyrazow);
                    tymczasowy.id = atoi(id.c_str());
                    break;
                case 2:
                    id = liniaWPliku.substr(poprzednieRozdzielenieWyrazow + 1, rozdzielenieWyrazow - poprzednieRozdzielenieWyrazow - 1);
                    tymczasowy.idUzytkownika = atoi(id.c_str());
                    break;
                case 3:
                    tymczasowy.imie = liniaWPliku.substr(poprzednieRozdzielenieWyrazow + 1, rozdzielenieWyrazow - poprzednieRozdzielenieWyrazow - 1);
                    break;
                case 4:
                    tymczasowy.nazwisko = liniaWPliku.substr(poprzednieRozdzielenieWyrazow + 1, rozdzielenieWyrazow - poprzednieRozdzielenieWyrazow - 1);
                    break;
                case 5:
                    tymczasowy.telefon = liniaWPliku.substr(poprzednieRozdzielenieWyrazow + 1, rozdzielenieWyrazow - poprzednieRozdzielenieWyrazow - 1);
                    break;
                case 6:
                    tymczasowy.email = liniaWPliku.substr(poprzednieRozdzielenieWyrazow + 1, rozdzielenieWyrazow - poprzednieRozdzielenieWyrazow - 1);
                    break;
                case 7:
                    tymczasowy.adres = liniaWPliku.substr(poprzednieRozdzielenieWyrazow + 1, rozdzielenieWyrazow - poprzednieRozdzielenieWyrazow - 1);
                    break;
                }
                poprzednieRozdzielenieWyrazow = rozdzielenieWyrazow;
                rozdzielenieWyrazow = liniaWPliku.find('|', rozdzielenieWyrazow + 1);
                numerWyrazu ++;
            }
            if (tymczasowy.idUzytkownika == idZalogowanegoUzytkownika) {
                znajomi.push_back(tymczasowy);
            }
        }
        idOstatniegoZnajomego = tymczasowy.id;
    } else {
        cout << "nie udalo sie otwozyc pliku" << endl;
    }
    plik.close();
    return idOstatniegoZnajomego;
}

void zapiszZnajomegoDoPliku (Znajomy znajomyDoZapisania) {
    fstream plik;
    plik.open ("Adresaci.txt", ios::out | ios::app);
    plik << znajomyDoZapisania.id << "|";
    plik << znajomyDoZapisania.idUzytkownika << "|";
    plik << znajomyDoZapisania.imie << "|";
    plik << znajomyDoZapisania.nazwisko << "|";
    plik << znajomyDoZapisania.telefon << "|";
    plik << znajomyDoZapisania.email << "|";
    plik << znajomyDoZapisania.adres << "|";
    plik << endl;
    plik.close();
}

void zaktualizujZnajomegoWPliku (vector <Znajomy>& znajomi, int indeksModyfikowanegoAdresata) {
    int idModyfikowanegoAdresata = znajomi[indeksModyfikowanegoAdresata].id;
    fstream plik1, plik2;
    plik1.open ("Adresaci.txt", ios::in);
    plik2.open ("Adresaci_tymczasowy.txt", ios::out | ios::app);
    if (plik1.good()) {
        string liniaWPliku = "";
        while (getline(plik1, liniaWPliku)) {
            int id = 0;
            size_t rozdzielenieWyrazow = liniaWPliku.find('|');
            id = atoi(liniaWPliku.substr(0, rozdzielenieWyrazow).c_str());
            if (id != idModyfikowanegoAdresata)
            {
                plik2 << liniaWPliku << endl;
            }
            else
            {
                plik2 << idModyfikowanegoAdresata << "|";
                plik2 << znajomi[indeksModyfikowanegoAdresata].idUzytkownika << "|";
                plik2 << znajomi[indeksModyfikowanegoAdresata].imie << "|";
                plik2 << znajomi[indeksModyfikowanegoAdresata].nazwisko << "|";
                plik2 << znajomi[indeksModyfikowanegoAdresata].telefon << "|";
                plik2 << znajomi[indeksModyfikowanegoAdresata].email << "|";
                plik2 << znajomi[indeksModyfikowanegoAdresata].adres << "|";
                plik2 << endl;
            }
        }
    } else {
        cout << "nie udalo sie otwozyc pliku" << endl;
    }
    plik1.close();
    plik2.close();

    remove("Adresaci.txt");
    rename( "Adresaci_tymczasowy.txt", "Adresaci.txt" );
}

void wypiszMenuZmianyDanych () {
    system ("cls");
    cout << "wybierz opcje:" << endl;
    cout << "1 - zmien imie" << endl;
    cout << "2 - zmien nazwisko" << endl;
    cout << "3 - zmien numer telefonu" << endl;
    cout << "4 - zmien adres e-mail" << endl;
    cout << "5 - zmien adres" << endl;
    cout << "6 - powrot do menu glownego" << endl;
}

string wczytajLinie () {
    string linia = "";
    cin.sync();
    getline(cin, linia);
    return linia;
}

char wczytajZnak() {
    string linia = "";
    char znak = (0);

    while (1) {
        cin.sync();
        getline (cin, linia);

        if (linia.length() == 1) {
            znak = linia[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz pojedynczy znak" << endl;
    }
    return znak;
}

int wczytajLiczbe () {
    string linia = "";
    int liczba = 0;

    while (1) {
        cin.sync();
        getline (cin, linia);

        stringstream ss(linia);
        if (ss >> liczba) {
            break;
        }
        cout << "To nie jest liczba. Wpisz liczbe" << endl;
    }
    return liczba;
}

void edytujZnajomego (vector <Znajomy>& znajomi) {
    int liczbaZapisanychZnajomych = znajomi.size();
    int idEdytowanegoAdresata = 0;
    bool czyZnalezionoAdresata = false;
    int wybranaOpcjaZmianyDanych = 0;

    system ("cls");
    cout << "6. Edytuj adresata" << endl;

    if (liczbaZapisanychZnajomych < 1) {
        wypiszNaEkranBrakKontaktow ();
    } else {
        cout << "Wpisz ID adresata ktorego dane chcesz zmienic" << endl;
        idEdytowanegoAdresata = wczytajLiczbe ();

        for (int i = 0; i < liczbaZapisanychZnajomych; i++) {
            if (znajomi[i].id == idEdytowanegoAdresata) {
                czyZnalezionoAdresata = true;
                wypiszMenuZmianyDanych ();
                wybranaOpcjaZmianyDanych = wczytajLiczbe ();
                cin.sync();

                switch (wybranaOpcjaZmianyDanych) {
                case 1:
                    cout << "wpisz imie: " ;
                    znajomi[i].imie = wczytajLinie ();
                    break;
                case 2:
                    cout << "wpisz nazwisko: " ;
                    znajomi[i].nazwisko = wczytajLinie ();
                    break;
                case 3:
                    cout << "wpisz nr telefonu: " ;
                    znajomi[i].telefon = wczytajLinie ();
                    break;
                case 4:
                    cout << "wpisz adres e-mail: " ;
                    znajomi[i].email = wczytajLinie ();
                    break;
                case 5:
                    cout << "wpisz adres: " ;
                    znajomi[i].adres = wczytajLinie ();
                    break;
                case 6:
                    wrocDoMenuGlownego ();
                    break;
                }
                zaktualizujZnajomegoWPliku (znajomi, i);

                Sleep (200);
                cout << "Zaktualizowano znajomego!" << endl;
                Sleep (500);
                break;
            }
        }
        if (!czyZnalezionoAdresata) {
            wypiszNaEkranBrakKontaktow ();
        }
    }
}

void odczytajUzytkownikowZPliku (vector <Uzytkownik>& uzytkownicy) {
    fstream plik;
    string liniaWPliku = "";
    plik.open ("Uzytkownicy.txt", ios::in);
    if (plik.good()) {
        while (getline(plik, liniaWPliku)) {
            Uzytkownik tymczasowy;
            string idUzytkownika = "";
            size_t rozdzielenieWyrazow = liniaWPliku.find('|');
            size_t poprzednieRozdzielenieWyrazow = 0;
            int numerWyrazu = 1;
            while (numerWyrazu <= 3) {
                switch (numerWyrazu) {
                case 1:
                    idUzytkownika = liniaWPliku.substr(poprzednieRozdzielenieWyrazow, rozdzielenieWyrazow);
                    tymczasowy.idUzytkownika = atoi(liniaWPliku.c_str());
                    break;
                case 2:
                    tymczasowy.loginUzytkownika = liniaWPliku.substr(poprzednieRozdzielenieWyrazow + 1, rozdzielenieWyrazow - poprzednieRozdzielenieWyrazow - 1);
                    break;
                case 3:
                    tymczasowy.hasloUzytkownika = liniaWPliku.substr(poprzednieRozdzielenieWyrazow + 1, rozdzielenieWyrazow - poprzednieRozdzielenieWyrazow - 1);
                    break;

                }
                poprzednieRozdzielenieWyrazow = rozdzielenieWyrazow;
                rozdzielenieWyrazow = liniaWPliku.find('|', rozdzielenieWyrazow + 1);
                numerWyrazu ++;
            }
            uzytkownicy.push_back(tymczasowy);
        }
    } else {
        cout << "Nie udalo sie otwozyc pliku z uzytkownikami" << endl;
    }
}

int zalogujUzytkownika (vector <Uzytkownik>& uzytkownicy) {
    int liczbaZapisanychUzytkownikow = uzytkownicy.size();
    string login = "";
    string haslo = "";

    system ("cls");
    cout << "1. Logowanie" << endl;

    if (uzytkownicy.size() > 0) {
        cout << "Wpisz login" << endl;
        login = wczytajLinie();
        for (int i = 0; i < liczbaZapisanychUzytkownikow; i++) {
            if (uzytkownicy[i].loginUzytkownika == login) {
                cout << "Wpisz haslo" << endl;
                for (int proby = 0; proby < 3; proby++) {
                    cout << "Pozostalo prob: " << 3-proby << endl;
                    haslo = wczytajLinie();
                    if (uzytkownicy[i].hasloUzytkownika == haslo) {
                        Sleep (200);
                        cout << "Zalogowano" << endl;
                        Sleep (500);
                        return uzytkownicy[i].idUzytkownika;
                    }
                }
                Sleep (200);
                cout << "Wpisano bledne haslo 3 razy";
                wrocDoMenuGlownego();
                return 0;
            }
        }
        Sleep (200);
        cout << "Nie ma takiego uzytkownika";
        wrocDoMenuGlownego();
        return 0;

    } else {
        Sleep (200);
        cout << "Brak zarejestrowanych uzytkownikow";
        wrocDoMenuGlownego();
        return 0;

    }
}

void zarejestrujUzytkownika (vector <Uzytkownik>& uzytkownicy) {
    int liczbaUzytkownikow = uzytkownicy.size();
    Uzytkownik tymczasowy;

    system ("cls");
    cout << "2. Rejestracja" << endl;
    cout << "Wpisz login" << endl;
    tymczasowy.loginUzytkownika = wczytajLinie ();
    int licznik = 0;
    while (licznik < liczbaUzytkownikow) {
        if (uzytkownicy[licznik].loginUzytkownika == tymczasowy.loginUzytkownika) {
            cout << "Taki uzytkownik juz istnieje, wpisz inny login" << endl;
            tymczasowy.loginUzytkownika = wczytajLinie();
            licznik = 0;
        } else {
            licznik++;
        }
    }

    cout << "Wpisz haslo" << endl;
    tymczasowy.hasloUzytkownika = wczytajLinie ();

    if (liczbaUzytkownikow == 0) {
        tymczasowy.idUzytkownika = 1;
    } else {
        tymczasowy.idUzytkownika = uzytkownicy[liczbaUzytkownikow - 1].idUzytkownika + 1;
    }

    uzytkownicy.push_back(tymczasowy);
    zapiszUzytkownikaDoPliku (tymczasowy);

    Sleep (200);
    cout << "Dodano znajomego" << endl;
    Sleep (500);
}

void zapiszUzytkownikaDoPliku (Uzytkownik uzytkownikDoZapisania) {
    fstream plik;
    plik.open ("Uzytkownicy.txt", ios::out | ios::app);
    plik << uzytkownikDoZapisania.idUzytkownika << "|";
    plik << uzytkownikDoZapisania.loginUzytkownika << "|";
    plik << uzytkownikDoZapisania.hasloUzytkownika << "|";
    plik << endl;
    plik.close();
}

void zmienHaslo (vector <Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika) {
    int liczbaZapisanychUzytkownikow = uzytkownicy.size();
    system ("cls");
    cout << "7. Zmien haslo" << endl;

    for (int i = 0; i < liczbaZapisanychUzytkownikow; i++) {
        if (idZalogowanegoUzytkownika == uzytkownicy[i].idUzytkownika) {
            cout << "Wpisz nowe haslo" << endl;
            uzytkownicy[i].hasloUzytkownika = wczytajLinie();
        }
    }
    zaktualizujUzytkownikowWPliku (uzytkownicy);
    Sleep (200);
    cout << "Zmieniono haslo" << endl;
    Sleep (500);
}

void zaktualizujUzytkownikowWPliku (vector <Uzytkownik>& uzytkownicy) {
    int liczbaZapisanychUzytkownikow = uzytkownicy.size();
    fstream plik;
    plik.open ("Uzytkownicy.txt", ios::out);
    for (int i = 0; i < liczbaZapisanychUzytkownikow; i++) {
        plik << uzytkownicy[i].idUzytkownika << "|";
        plik << uzytkownicy[i].loginUzytkownika << "|";
        plik << uzytkownicy[i].hasloUzytkownika << "|";
        plik << endl;
    }
    plik.close();
}
