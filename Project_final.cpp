#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <iomanip>



using namespace std;

enum KeyCodes { NUMBER = 0, ADRESS = 1, CUSTOMER = 2, EXECUTOR = 3, TOTAL = 4, INCOME = 5, DELIVERY = 6, BONUS = 7 };

int main();
string today_date();
void deadlines(string today, int HEIGHT, int WIDTH, string array_list[][8]);
int bonus_plus(int HEIGHT, string array_list[][8], double bonus);
int income(int HEIGHT, string array_list[][8]);
int bonus_plus_income(int HEIGHT, string array_list[][8], double bonus);
int worker_earn(int HEIGHT, string array_list[][8], string worker);
void add_bonus(int HEIGHT, string array_list[][8], double bonus);
int worker_payment(int HEIGHT, string array_list[][8], string worker);
int total_payment(int HEIGHT, string array_list[][8]);
int total_profit(int HEIGHT, string array_list[][8], double bonus);
void loadArrayFromFile(const char* filename, int HEIGHT, int WIDTH, string array_list[][8]);
int menu_program(int code, int HEIGHT, int WIDTH, string array_list[][8], double bonus, string worker);
void print_message();



//запрашиваем дату и возвращаем ее в виде строки
string today_date()
{
    string today;
    cout << "Введите дату для отображения списка: ";
    cin >> today;
    return today;
}

//если запрошенная дата совпадает с датой выдачи выводим всю строку в консоль
void deadlines(int HEIGHT, int WIDTH, string array_list[][8], string(*pf)()) // указатель на функцию
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 15);
    string today = pf();
    SetConsoleTextAttribute(h, 6);

    cout << left;
    for (int i = 0, j = 0; j < WIDTH; j++)
    {
        if (j == 1)
        {
            cout << setw(55) << array_list[0][j];
        }
        else if (j == 0)
        {
            cout << setw(5) << array_list[0][j];
        }
        else
        {
            cout << setw(20) << array_list[0][j];
        }
    }
    cout << "\n";

    for (int i = 1, j = 0; i < HEIGHT; i++)
    {

        if (array_list[i][DELIVERY] == today)
        {
            cout << left;
            for (j = 0; j < WIDTH; j++)
            {
                if (j == 1)
                {
                    cout << setw(55) << array_list[i][j];
                }
                else if (j == 0)
                {
                    cout << setw(5) << array_list[i][j];
                }
                else
                {
                    cout << setw(20) << array_list[i][j];

                }
            }
            cout << "\n";
        }

    }
}

// суммируем надбавки за выполнение работы в день ее поступления, надбавка равна 20% (все надбавки для сотрудников и подрядной фирмы)
int bonus_plus(int HEIGHT, string array_list[][8], double bonus)
{
    int bonus_count = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        if (array_list[i][INCOME] == array_list[i][DELIVERY])
        {
            int x = stoi(array_list[i][TOTAL]) * bonus;
            bonus_count += x;
        }
    }
    //cout << bonus_count << "\n";
    return bonus_count;
}

// сумарные поступления, без бонусов (все поступления для сотрудников и подрядной фирмы)
int income(int HEIGHT, string array_list[][8])
{
    int sum = 0;
    for (int i = 1; i < HEIGHT; i++)
    {
        int x = stoi(array_list[i][TOTAL]);
        sum += x;
    }
    //cout << sum <<"\n";
    return sum;
}

//считаем сумарные поступления вместе с бонусами 
int bonus_plus_income(int HEIGHT, string array_list[][8], double bonus)
{
    int total_incom = 0;
    total_incom = income(HEIGHT, array_list) + bonus_plus(HEIGHT, array_list, bonus);
    //cout << total_incom << "\n";
    return total_incom;
}

//заполняем массив в случае наличия бонусами
void add_bonus(int HEIGHT, string array_list[][8], double bonus)
{
    for (int i = 1; i < HEIGHT; i++)
    {
        if (array_list[i][INCOME] == array_list[i][DELIVERY])
        {
            int x = stoi(array_list[i][4]) * bonus;
            string y = to_string(x);
            array_list[i][BONUS] = y;
        }
        else
        {
            int x = 0;
            string y = to_string(x);
            array_list[i][BONUS] = y;
        }
    }
    //cout << bonus_count;
}

//cчитаем заработаные деньги наемной фирмой или сотрудником (подсчет доходов отдельно по каждому сотруднику или подрядной фирме на выбор)
int worker_earn(int HEIGHT, string array_list[][8], string worker)
{
    int payment = 0;
    for (int i = 0, j = 3; i < HEIGHT; i++)
    {
        if (array_list[i][j] == worker)
        {
            int x = stoi(array_list[i][TOTAL]) + stoi(array_list[i][BONUS]);
            payment += x;
        }
    }
    //payment *= 0.25;
    //cout << payment;
    return payment;
}

//cчитаем сколько нужно заплатить отдельному сотруднику или подрядной фирме
int worker_payment(int HEIGHT, string array_list[][8], string worker)
{
    int payment = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        if (array_list[i][EXECUTOR] == worker)
        {
            if (worker == "сотрудник 1" || worker == "сотрудник 2")
            {
                int x = (stoi(array_list[i][TOTAL]) + stoi(array_list[i][BONUS])) * 0.25;
                payment += x;
            }
            else if (worker == "подрядная фирма")
            {
                int x = (stoi(array_list[i][TOTAL]) + stoi(array_list[i][BONUS])) * 0.5;
                payment += x;
            }

        }
    }
    //cout << payment;
    return payment;
}

//cчитаем сколько нужно заплатить всем сотрудникам и подрядной фирме (включая бонусы)
int total_payment(int HEIGHT, string array_list[][8])
{
    int payment = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        if (array_list[i][EXECUTOR] == "сотрудник 1" || array_list[i][EXECUTOR] == "сотрудник 2")
        {
            int x = (stoi(array_list[i][TOTAL]) + stoi(array_list[i][BONUS])) * 0.25;
            payment += x;
        }
        else if (array_list[i][EXECUTOR] == "подрядная фирма")
        {
            int x = (stoi(array_list[i][TOTAL]) + stoi(array_list[i][BONUS])) * 0.5;
            payment += x;
        }
    }
    //cout << payment;
    return payment;
}

//суммарный доход фирмы после вычета зарплаты сотрудникам и подрядной фирме
int total_profit(int HEIGHT, string array_list[][8], double bonus)
{
    int profit = bonus_plus_income(HEIGHT, array_list, bonus) - total_payment(HEIGHT, array_list);
    //cout << profit;
    return profit;
}


//_____________________________________________________________________________________________
//заполнение массива из текстового файла с разделителями в виде табуляции
void loadArrayFromFile(const char* filename, int HEIGHT, int WIDTH, string array_list[][8]) {
    FILE* file = fopen(filename, "r");  // открытие файла для чтения
    if (!file) {
        perror("Ошибка: не удалось открыть файл");
        return;
    }

    char buffer[256];  // буфер для считывания строк
    int row = 0;

    while (fgets(buffer, sizeof(buffer), file) && row < HEIGHT) {
        // Разбиение строки на токены
        char* token = strtok(buffer, "\t\n");  // разделение только по табуляциям
        int col = 0;

        while (token && col < WIDTH) {
            array_list[row][col] = string(token);  // преобразование в string и запись в массив
            token = strtok(NULL, "\t\n"); // переход на следующий кусок текста
            col++;
        }

        row++;
    }

    fclose(file);
}
//_____________________________________________________________________________________________

//меню выбора вариантов вывода информации
int menu_program(int code, int HEIGHT, int WIDTH, string array_list[][8], double bonus, string worker)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 2);
    switch (code)
    {
    case 49:
        deadlines(HEIGHT, WIDTH, array_list, today_date);
        cout << "\n";
        break;
    case 50:                                                //сумарные поступления
        cout << "сумарные поступления = " << income(HEIGHT, array_list) << " грн";
        cout << "\n";
        break;
    case 51:                                                //сумарные поступления вместе с бонусами
        cout << "сумарные поступления вместе с бонусами = " << bonus_plus_income(HEIGHT, array_list, bonus) << " грн";
        cout << "\n";
        break;
    case 57:                                                //суммарный доход
        cout << "суммарный доход = " << total_profit(HEIGHT, array_list, bonus) << " грн";
        cout << "\n";
        break;
    case 52:                                                //сумма надбавок
        cout << "сумма надбавок = " << bonus_plus(HEIGHT, array_list, bonus) << " грн";
        cout << "\n";
        break;
    case 53:                                                //заработаные деньги наемной фирмой или сотрудником
        cout << "Укажите кого хотим посмотреть?\n1-сотрудник 1\n2-сотрудник 2\n3-подрядная фирма\nESC - выход из программы\n";
        while (true)
        {
            int code = _getch();
            switch (code)
            {
            case 49:
                worker = "сотрудник 1";
                break;
            case 50:
                worker = "сотрудник 2";
                break;
            case 51:
                worker = "подрядная фирма";
                break;
            case 27:
                cout << "Выход\n";
                main();                         //используем рекурсию!
                break;
            }
            if (code == 27)
            {
                break;
            }
            cout << "деньги которые заработал(a)" << worker << " = " << worker_earn(HEIGHT, array_list, worker) << " грн\n";
            cout << "\n";
        }
        break;
    case 54:                                                //зарплата отдельного сотрудника или подрядной фирмы
        cout << "Укажите кому платим?\n1-сотрудник 1\n2-сотрудник 2\n3-подрядная фирма\nESC - выход из программы\n";
        while (true)
        {
            int code = _getch();
            switch (code)
            {
            case 49:
                worker = "сотрудник 1";
                break;
            case 50:
                worker = "сотрудник 2";
                break;
            case 51:
                worker = "подрядная фирма";
                break;
            case 27:
                cout << "Выход\n";
                main();                         //используем рекурсию!
                break;
            }
            if (code == 27)
            {
                break;
            }
            cout << "деньги которые нужно заплатить " << worker << " = " << worker_payment(HEIGHT, array_list, worker) << " грн\n";
            cout << "\n";
        }
        break;
    case 55:                                                //сколько нужно заплатить всем сотрудникам и подрядной фирме (включая бонусы)
        cout << "всего нужно заплатить за работу = " << total_payment(HEIGHT, array_list) << " грн";//!!!!!!!!!!!!!!
        cout << "\n";
        break;
    case 27:
        cout << "Программа завершена!\n";
        return false;
        break;
    default:
        cout << code << "\n";
        break;
    }
}

//сообщение с подсказкой для меню выбора (цветное)
void print_message()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 14);
    cout << "Введите что хотим просмотреть: \n1-список дел на сегодня\n2-сумарные поступления, без бонусов\n3-сумарные поступления вместе с бонусами\n4-сумма надбавок за выполнение работы в день ее поступления\n5-заработаные деньги наемной фирмой или сотрудником\n6-зарплата отдельного сотрудника или подрядной фирмы\n7-сколько нужно заплатить всем сотрудникам и подрядной фирме (включая бонусы)\n9-суммарный доход\nESC - выход из программы\n";
}

int main()
{
    setlocale(0, "");

    double bonus = 0.2;

    string worker;

    const int WIDTH = 8;
    const int HEIGHT = 17;
    const char* filename = "my_list.txt";
    string array_list[HEIGHT][WIDTH] = {};

    loadArrayFromFile(filename, HEIGHT, WIDTH, array_list);

    add_bonus(HEIGHT, array_list, bonus);

    print_message();

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 2);

    while (true)
    {
        add_bonus(HEIGHT, array_list, bonus);
        int code = _getch(); // функция приостанавливает работу программы, ждёт реакции пользователя

        menu_program(code, HEIGHT, WIDTH, array_list, bonus, worker);

        if (code == 27)
        {
            break;
        }
    }
    //строка для изменений
}

