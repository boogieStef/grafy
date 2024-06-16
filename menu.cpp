#include "menu.h"
#include "graph.h"
#include <iostream>
#include <string>
#include <conio.h>

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
    cout << "3) Wyswietl graf listowo i macierzowo\n";
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
        clear(); // Czyszczenie konsoli
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
                    cout << "Podaj nazwe pliku: ";
                    cin >> this->file_name;
                    this->info = get_info(file_name);
                    this->G = new Graph(info.first, info.second);
                    G->read_from_file(file_name, false);
                    G->print_graph();
                    wait();
                    break;

                case '2': // Wygeneruj losowo
                    int verticies, edges, density;
                    cout << "Podaj dane do wygenerowania grafu.\n";
                    cout << "Liczba wierzcholkow:  ";
                    cin >> verticies;
                    cout << "\nGestosc w % (max 100):  ";
                    cin >> density;
                    edges = (verticies * (verticies - 1)) * (density / 100);
                    // Sprawdzanie mozliwosci wygenerowania grafu
                    if((verticies * density / 100) < verticies - 1){
                        cout << "Za mala gestosc!   Podaj poprawne dane!\n";
                        break;
                    }else if(edges > (verticies * (verticies - 1))){
                        cout << "Za duza liczba krawedzi!   Podaj poprawne dane!\n";
                        break;
                    }else{
                        this->G = new Graph(edges, verticies);
                        this->G->generate(density, false);
                    }
                    break;

                case '3': // Wyświetl
                    this->G->print_graph();
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
                    cout << "Podaj nazwe pliku: ";
                    cin >> this->file_name;
                    this->info = get_info(file_name);
                    this->G = new Graph(info.first, info.second);
                    G->read_from_file(file_name, true);
                    G->print_graph();
                    wait();
                    break;

                case '2': // Wygeneruj losowo
                    int verticies, edges, density;
                    cout << "Podaj dane do wygenerowania grafu.\n";
                    cout << "Liczba wierzcholkow:  ";
                    cin >> verticies;
                    cout << "\nGestosc w % (max 100):  ";
                    cin >> density;
                    edges = (verticies * (verticies - 1)) * (density / 100);
                    // Sprawdzanie mozliwosci wygenerowania grafu
                    if((verticies * density / 100) < verticies - 1){
                        cout << "Za mala gestosc!   Podaj poprawne dane!\n";
                        break;
                    }else if(edges > (verticies * (verticies - 1))){
                        cout << "Za duza liczba krawedzi!   Podaj poprawne dane!\n";
                        break;
                    }else{
                        this->G = new Graph(edges, verticies);
                        this->G->generate(density, true);
                    }
                    break;

                case '3': // Wyświetl
                    this->G->print_graph();
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

void Menu::read_data(bool directed){
    cout << "Podaj nazwe pliku: ";
    cin >> this->file_name;
    this->info = get_info(file_name);
    this->G = new Graph(info.first, info.second);
    G->read_from_file(file_name, true);
    //G->print_graph();
}


// Funkcja czyszczaca konsole
void clear()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#endif
}

// Funkcja czekajaca na akcje uzytkownika
void wait(){
    cout << "Nacisnij dowolny klawisz...\n";
    getch();
    cout << "============\n";
}
