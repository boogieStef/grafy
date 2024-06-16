#include "graph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <climits>

using namespace std;

Graph::Graph(int edg, int vert){
    this->edges = edg;      // Liczba krawedzi
    this->verticies = vert; // Liczba wierzcholkow
    // Tworzenie listy sasiedztwa
    this->list_adj = new vector<pair<int, int>>[verticies];
    // Tworzenie macierzy sasiedztwa i wypelnianie zerami
    this->matrix_adj = new int *[verticies];
    for(int i = 0; i < verticies; i++)
        matrix_adj[i] = new int [verticies];
    for(int i = 0; i < verticies; i++)
        for(int j = 0; j < verticies; j++)
            matrix_adj[i][j] = 0;
}

Graph::~Graph(){
    // Usuwanie listy sasiedztwa
    delete[] this->list_adj;
    //Usuwanie macierzy sasiedztwa
    for(int i = 0; i < verticies; i++)
        delete[] this->matrix_adj[i];
    delete[] this->matrix_adj;
}

// Dodaj krawedz do obu reprezentacji
void Graph::add_edge(int src, int dest, int weight, bool directed){
    list_adj[src].push_back(make_pair(dest, weight));
    matrix_adj[src][dest] = weight;
    // Jezeli graf ma byc nieskierowany
    if(!directed){
        list_adj[dest].push_back(make_pair(src, weight));
        matrix_adj[dest][src] = weight;
    }
}

// Odczytaj graf z pliku
void Graph::read_from_file(string file_name, bool directed){
    ifstream in_file(file_name);
    if(!in_file.is_open()){
        cout << "Blad otwierania pliku!\n";
        return;
    }

    // Wczytaj pierwsza linie
    string line;
    getline(in_file, line);
    
    // Dodaj krawedzie do grafu (obie reprezentacje)
    size_t position;
    size_t position2;
    int src, dest, weight;
    for(int i = 0; i < verticies; i++){
        getline(in_file, line);
        position = line.find(' ');
        position2 = line.find(' ', position + 1);

        src = stoi(line.substr(0, position));
        dest = stoi(line.substr(position + 1, position2));
        weight = stoi(line.substr(position2 + 1));

        add_edge(src, dest, weight, directed);
    }
    cout << "Wczytano graf!\n";
}

// Wygeneruj graf o gestosci density (skierowany lub nie)
void Graph::generate(int density, bool directed){
    // Stworzenie wszystkich mozliwych krawedzi
    vector<pair<int, int>> all_edges;
    for(int i = 0; i < verticies; i++){
        for(int j = 0; j < verticies; j++){
            if(i != j){
                pair<int, int> p = {i, j};
                all_edges.push_back(p);
            }
        }
    } 
    
    // Mieszanie elementow wektora
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(all_edges.begin(), all_edges.end(), default_random_engine(seed));

    // Tworzenie nowego wektora z wszystkimi numerami wierzcholkow
    vector<int> vec;
    for(int i = 0; i < this->verticies; i++)
        vec.push_back(i);
    // Mieszanie elementow wektora
    unsigned seed2 = chrono::system_clock::now().time_since_epoch().count();
    shuffle(vec.begin(), vec.end(), default_random_engine(seed2));

    // Zapewnianie spojnosci grafu - polaczenie wszystkich wierzchlolkow po kolei
    srand((unsigned) time(NULL));
    for(int i = 0; i < this->verticies - 1; i++){
        int rand_weight = 1 + rand() % (INT_MAX - 1); // Losowa waga
        int src = vec[i];
        int dst = vec[i+1];

        pair<int, int> p = {src, dst};

        this->add_edge(src, dst, rand_weight, directed); // Dodanie krawedzi do grafu
        all_edges.erase(remove(all_edges.begin(), all_edges.end(), p), all_edges.end()); // Usuniecie krawedzi ze wszystkich krawedzi

        // Jeśli ma być nieskierowany to też w druga strone
        if(!directed){
            this->add_edge(dst, src, rand_weight, directed); // Dodanie krawedzi do grafu
            all_edges.erase(remove(all_edges.begin(), all_edges.end(), p), all_edges.end()); // Usuniecie krawedzi ze wszystkich krawedzi
        }
    }

    this->print_graph();

    // Dodanie pozostalych wierzcholkow az do zapewnienia wymaganej gestosci
    int how_many_edges = (verticies * (verticies - 1)) * (density / 100);
    // Obliczanie ile jeszcze krawedzi trzeba dodac
    int num = how_many_edges - (verticies - 1);
    if(!directed)
        num = num / 2; // W grafie nieskierowanym dodaje dwie za jednym razem

    for(int i = 0; i < num; i++){
        int rand_weight = 1 + rand() % (INT_MAX - 1); // Losowa waga
        pair<int, int> p = all_edges.back(); // Wez kolejna krawedz z przemieszanego wektora
        all_edges.pop_back();
        int src = p.first;
        int dst = p.second;
     
        this->add_edge(src, dst, rand_weight, directed); // Dodanie krawedzi do grafu
        all_edges.erase(remove(all_edges.begin(), all_edges.end(), p), all_edges.end()); // Usuniecie krawedzi ze wszystkich krawedzi

        // Jeśli ma być nieskierowany to też w druga strone
        if(!directed){
            p = {dst, src};
            this->add_edge(dst, src, rand_weight, directed); // Dodanie krawedzi do grafu
            all_edges.erase(remove(all_edges.begin(), all_edges.end(), p), all_edges.end()); // Usuniecie krawedzi ze wszystkich krawedzi
        }
    }
}

// Wypisywanie grafu (obie reprezentacje)
// TODO pytanie o wyswietlanie powyzej 100 wiercholkow
// TODO wyrownanie wyswietlania przy duzych liczbach
void Graph::print_graph(){
    cout << "------------------------------\n";
    cout << "Liczba wierzcholkow: " << verticies << endl;
    cout << "Liczba krawedzi: "     << edges << endl;
    cout << "------------------------------\n";
    cout << "Reprezentacja lista sasiedztwa\n";
    for(int i = 0; i < verticies; i++){
        cout << "v-" << i << ": ";
        for(auto neighbor : list_adj[i]){
            cout << neighbor.first << ", " << neighbor.second << " -> ";
        }
        cout << endl;
    }
    cout << "\nReprezentacja macierz sasiedztwa\n";
    for(int i = 0; i < verticies; i++){
        for(int j = 0; j < verticies; j++){
            cout << matrix_adj[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------------------------------\n";
}
// Zwraca pare (liczba_krawedzi, liczba_wierzcholkow) z pliku z pierwszej linii pliku
pair<int, int> get_info(string file_name){
    pair<int, int> info;
    ifstream in_file(file_name);
    if(!in_file.is_open()){
        cout << "Blad otwierania pliku!\n";
        return pair<int, int>(0, 0);
    }
    // Wczytaj pierwsza linie i odczytaj liczbe krawedzi i wierzcholkow
    string line;
    getline(in_file, line);
    size_t position = line.find(' ');
    info.first = stoi(line.substr(0, position));
    info.second = stoi(line.substr(position + 1));

    return info;
}