#ifndef MENU
#define MENU

class Menu{
    public:
        void run();
    private:
        char main_choice, second_choice;
        void display_main_menu();
        void display_mst_menu();
        void display_path_menu();
};

#endif //MENU