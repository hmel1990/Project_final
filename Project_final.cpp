#include "bonus.h" // все библиотеки, перечисления, using namespace std находятся в этом заголовочном файле
#include "functions.h" // все функции и прототипы функций находятся в этом заголовочном файле


int main()
{
    MoveWindow(GetConsoleWindow(), 250, 150, 1400, 800, true);// установка стартовой позиции окна консоли (250, 150, 1400, 800 - пиксели) отступ слева, отступ справа, ширина окна, высота окна
    setlocale(0, ""); //для корректного отображения кирилицы
    SetConsoleOutputCP(CP_UTF8); // для вывода украинских букв "і"
    system("title EXPERT ASSESSMENT - Денежная оценка"); // Установка заголовка окна

        
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    double bonus = 0.2;
    string worker;
    int WIDTH;
    int HEIGHT;
    string** array;
    int code = 1;
    const char* filename = "my_list.txt";

    //Старовое сообщение
    start_message();

    //Работа с созданием массива
    set_array_widh(WIDTH);                                              // установка ширины массива
    set_array_height(HEIGHT);                                           // установка высоты массива
    allocate_2D_array_memory(array, WIDTH, HEIGHT);                     // выделение памяти в куче (heap)

    //Заполнение массива
    loadArrayFromFile(filename, HEIGHT, WIDTH, array);                  // загрузка данных из файла .txt     
    add_bonus(HEIGHT, array, bonus);                                    // заполнение при необходимых условиях бонусами
    
    //Работа с программой
    menu_program_message(code, HEIGHT, WIDTH, array, bonus, worker,h);  // меню программы
    
    //Завершение работы 
    delete_array(array, HEIGHT, WIDTH);                                 // очистка оперативной памяти от созданного массива
  }