#include "graph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

Graph::Graph(int edg, int vert){
    this->edges = edg;
    this->verticies = vert;
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

void Graph::add_edge(int src, int dest, int weight, bool directed){
    //cout << "dodawanie krawedzi..." << src << " " << dest;
    list_adj[src].push_back(make_pair(dest, weight));
    matrix_adj[src][dest] = weight;
    // Jezeli graf ma byc skierowany
    if(directed){
        list_adj[dest].push_back(make_pair(src, weight));
        matrix_adj[dest][src] = weight;
    }
    //cout << "koniec";
}

void Graph::read_from_file(string file_name, bool directed){
    ifstream in_file(file_name);
    if(!in_file.is_open()){
        cout << "Blad otwierania pliku!\n";
        return;
    }

    // Wczytaj pierwsza linie i odczytaj liczbe krawedzi i wierzcholkow
    string line;
    getline(in_file, line);
    size_t position = line.find(' ');
    this->edges = stoi(line.substr(0, position));
    this->verticies = stoi(line.substr(position + 1));

    cout << "!!! " << verticies << edges;
    
    // Dodaj krawedzie do grafu (obie reprezentacje)
    size_t position2;
    for(int i = 0; i < verticies; i++){
        getline(in_file, line);
        position = line.find(' ');
        position2 = line.find(' ', position + 1);
        add_edge(stoi(line.substr(0, position)), stoi(line.substr(position + 1, position2)), stoi(line.substr(position2 + 1)) ,directed);
    }
}

void Graph::print_graph(){
    cout << "Liczba wierzcholkow: " << verticies << endl;
    cout << "Liczba krawedzi: " << edges << endl;
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
}