#ifndef MENU
#define MENU
#include <string>
#include "graph.h"
using namespace std;
class Menu{
    public:
        void run();
        string file_name;
    private:
        Graph *G;
        char main_choice, second_choice;
        void display_main_menu();
        void display_mst_menu();
        void display_path_menu();
};

#endif //MENU