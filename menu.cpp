#include "menu.h"
#include <iostream>

using namespace std;

void Menu::display_main_menu(){
    cout << "Wybor problemu\n";
    cout << "1) Wyznaczanie minimalnego drzewa rozpinajacego (MST)\n";
    cout << "2) Wyznaczanie najkrotszej sciezki\n";
    cout << "0) Wyjscie - zakoncz dzialanie programu\n";
    cin >> main_choice;
}

void Menu::display_mst_menu(){
    cout << "Problem: wyznaczanie minimalnego drzewa rozpinajacego (MST).\n";
    cout << "1) Wczytaj dane z pliku\n";
    cout << "2) Wygeneruj graf losowo\n";
    cout << "3) Wyświetl graf listowo i macierzowo\n";
    cout << "4) Algorytm 1 (Prima) wyniki\n";
    cout << "0) Wyjscie - zmiana problemu\n";
    cin >> second_choice;
}

void Menu::display_path_menu(){
    cout << "Problem: wyszukiwanie najkrotszej sciezki w grafie.\n";
    cout << "1) Wczytaj dane z pliku\n";
    cout << "2) Wygeneruj graf losowo\n";
    cout << "3) Wyswietl graf listowo i macierzowo\n";
    cout << "4) Algorytm 1 (Dijkstry) wyniki\n";
    cout << "0) Wyjscie - zmiana problemu\n";
    cin >> second_choice;
}

void Menu::run(){
    while(main_choice != '0'){
        display_main_menu();
        second_choice = '1'; // zeby weszlo w petle
        switch (main_choice)
        {
        case '0':
            return;
            break;

        case '1': // MST
            while(second_choice != '0'){
                display_mst_menu();
                switch (second_choice)
                {
                case '0': // Wyjscie
                    break;
                case '1': // Wczytaj z pliku
                    break;
                case '2': // Wygeneruj losowo
                    break;
                case '3': // Wyświetl 
                    break;
                case '4': // Algorytm 1 (Prima) 
                    break;
                default:
                    cout << "Podaj poprawna opcje...\n";
                    break;
                }
            }
            break;

        case '2': // Sciezka
            while(second_choice != '0'){
                display_path_menu();
                switch (second_choice)
                {
                case '0': // Wyjscie
                    break;
                case '1': // Wczytaj z pliku
                    break;
                case '2': // Wygeneruj losowo
                    break;
                case '3': // Wyświetl 
                    break;
                case '4': // Algorytm 1 (Disjktry) 
                    break;
                default:
                    cout << "Podaj poprawna opcje...\n";
                    break;
                }
            }
            break;
        
        default:
            cout << "Podaj poprawna opcje...\n";
            break;
        };
    }
}
