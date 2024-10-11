#include "bonus.h" // все библиотеки, перечисления, using namespace std находятся в этом заголовочном файле
#include "functions.h" // все функции и прототипы функций находятся в этом заголовочном файле


int main()
{
    MoveWindow(GetConsoleWindow(), 250, 150, 1400, 800, true);// установка стартовой позиции окна консоли (250, 150, 1400, 800 - пиксели) отступ слева, отступ справа, ширина окна, высота окна
    setlocale(0, "");
    SetConsoleOutputCP(CP_UTF8); // для вывода украинских букв "і"
    system("title EXPERT ASSESSMENT"); // Установка заголовка окна
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    start_message();
        
    double bonus = 0.2;
    string worker;
    int WIDTH;
    int HEIGHT;
    string** array;
    int code = 1;
    const char* filename = "my_list.txt";

    set_array_widh(WIDTH);                              // установка ширины массива
    set_array_height(HEIGHT);                           // установка высоты массива
    allocate_2D_array_memory(array, WIDTH, HEIGHT);

    loadArrayFromFile(filename, HEIGHT, WIDTH, array);     
    
    add_bonus(HEIGHT, array, bonus);
    menu_program_message(code, HEIGHT, WIDTH, array, bonus, worker,h);
    delete_array(array, HEIGHT, WIDTH);
  }

