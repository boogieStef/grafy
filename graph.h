#ifndef GRAPH
#define GRAPH
#include <vector>
#include <string>
using namespace std;
class Graph{
    public:
        Graph(int edg, int vert); // Konstruktor
        ~Graph(); // Destruktor
        void add_edge(int src, int dest, int weight, bool directed); // Dodawanie krawedzi 
        void read_from_file(string file_name, bool directed); // Czytanie danych z pliku
        void print_graph();
        

    private:
        int edges;     // Liczba krawedzi
        int verticies; // Liczba wierzcholkow
        vector<pair<int, int>>* list_adj; // Lista sasiedztwa
        int **matrix_adj;  // Macierz sasiedztwa
};

#endif //GRAPH