int main();
string today_date();
void deadlines(string today, int HEIGHT, int WIDTH, string** array);
void show_array(int HEIGHT, int WIDTH, string** array);
int bonus_plus(int HEIGHT, string** array, double bonus);
int income(int HEIGHT, string** array);
int bonus_plus_income(int HEIGHT, string** array, double bonus);
int worker_earn(int HEIGHT, string** array, string worker);
void add_bonus(int HEIGHT, string** array, double bonus);
int worker_payment(int HEIGHT, string** array, string worker);
int total_payment(int HEIGHT, string** array);
int total_profit(int HEIGHT, string** array, double bonus);
void loadArrayFromFile(const char* filename, int HEIGHT, int WIDTH, string** array);
int menu_program(int code, int HEIGHT, int WIDTH, string** array, double bonus, string worker);
int menu_program_message(int code, int HEIGHT, int WIDTH, string** array, double bonus, string worker, HANDLE h);
void set_array_widh(int& WIDTH);
void set_array_height(int& HEIGHT);
void allocate_2D_array_memory(string**& array, const int WIDTH, const int HEIGHT);
void print_message();
void start_message();
void delete_array(string** array, int HEIGHT, int WIDTH);


//запрашиваем дату и возвращаем ее в виде строки
string today_date()
{
    string today;
    cout << "\nВведите дату для отображения списка: ";
    cin >> today;
    cout << "\n";
    return today;
}

//если запрошенная дата совпадает с датой выдачи выводим всю строку в консоль
void deadlines(int HEIGHT, int WIDTH, string** array, string(*pf)(), HANDLE h) // указатель на функцию
{
    //HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 15);
    string today = pf();
    SetConsoleTextAttribute(h, 6);

    cout << left;
    for (int i = 0, j = 0; j < WIDTH; j++)
    {
        if (j == 1)
        {
            cout << setw(55) << array[0][j];
        }
        else if (j == 0)
        {
            cout << setw(5) << array[0][j];
        }
        else
        {
            cout << setw(20) << array[0][j];
        }
    }
    cout << "\n";

    for (int i = 1, j = 0; i < HEIGHT; i++)
    {

        if (array[i][DELIVERY] == today)
        {
            cout << left;
            for (j = 0; j < WIDTH; j++)
            {
                if (j == 1)
                {
                    cout << setw(55) << array[i][j];
                }
                else if (j == 0)
                {
                    cout << setw(5) << array[i][j];
                }
                else
                {
                    cout << setw(20) << array[i][j];

                }
            }
            cout << "\n";
        }

    }
}

//выводим весь список
void show_array(int HEIGHT, int WIDTH, string** array, HANDLE h)
{
    //SetConsoleTextAttribute(h, 15);
    SetConsoleTextAttribute(h, 6);

    cout << left;
    for (int i = 0, j = 0; j < WIDTH; j++)
    {
        if (j == 1)
        {
            cout << setw(55) << array[0][j];
        }
        else if (j == 0)
        {
            cout << setw(5) << array[0][j];
        }
        else
        {
            cout << setw(20) << array[0][j];
        }
    }
    cout << "\n";

    for (int i = 1, j = 0; i < HEIGHT; i++)
    {
        cout << left;
        for (j = 0; j < WIDTH; j++)
        {
            if (j == 1)
            {
                cout << setw(55) << array[i][j];
            }
            else if (j == 0)
            {
                cout << setw(5) << array[i][j];
            }
            else
            {
                cout << setw(20) << array[i][j];

            }
        }
        cout << "\n";
    }
}

// суммируем надбавки за выполнение работы в день ее поступления, надбавка равна 20% (все надбавки для сотрудников и подрядной фирмы)
int bonus_plus(int HEIGHT, string** array, double bonus)
{
    int bonus_count = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        if (array[i][INCOME] == array[i][DELIVERY])
        {
            int x = stoi(array[i][TOTAL]) * bonus;
            bonus_count += x;
        }
    }
    //cout << bonus_count << "\n";
    return bonus_count;
}

// сумарные поступления, без бонусов (все поступления для сотрудников и подрядной фирмы)
int income(int HEIGHT, string** array)
{
    int sum = 0;
    for (int i = 1; i < HEIGHT; i++)
    {
        int x = stoi(array[i][TOTAL]);
        sum += x;
    }
    //cout << sum <<"\n";
    return sum;
}

//считаем сумарные поступления вместе с бонусами 
int bonus_plus_income(int HEIGHT, string** array, double bonus)
{
    int total_incom = 0;
    total_incom = income(HEIGHT, array) + bonus_plus(HEIGHT, array, bonus);
    //cout << total_incom << "\n";
    return total_incom;
}

//заполняем массив в случае наличия бонусами
void add_bonus(int HEIGHT, string** array, double bonus)
{
    for (int i = 1; i < HEIGHT; i++)
    {
        if (array[i][INCOME] == array[i][DELIVERY])
        {
            int x = stoi(array[i][4]) * bonus;
            string y = to_string(x);
            array[i][BONUS] = y;
        }
        else
        {
            int x = 0;
            string y = to_string(x);
            array[i][BONUS] = y;
        }
    }
}

//cчитаем заработаные деньги наемной фирмой или сотрудником (подсчет доходов отдельно по каждому сотруднику или подрядной фирме на выбор)
int worker_earn(int HEIGHT, string** array, string worker)
{
    int payment = 0;
    for (int i = 0, j = 3; i < HEIGHT; i++)
    {
        if (array[i][j] == worker)
        {
            int x = stoi(array[i][TOTAL]) + stoi(array[i][BONUS]);
            payment += x;
        }
    }
    //cout << payment;
    return payment;
}

//cчитаем сколько нужно заплатить отдельному сотруднику или подрядной фирме
int worker_payment(int HEIGHT, string** array, string worker)
{
    int payment = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        if (array[i][EXECUTOR] == worker)
        {
            if (worker == "сотрудник 1" || worker == "сотрудник 2")
            {
                int x = (stoi(array[i][TOTAL]) + stoi(array[i][BONUS])) * 0.25;
                payment += x;
            }
            else if (worker == "подрядная фирма")
            {
                int x = (stoi(array[i][TOTAL]) + stoi(array[i][BONUS])) * 0.5;
                payment += x;
            }

        }
    }
    //cout << payment;
    return payment;
}

//cчитаем сколько нужно заплатить всем сотрудникам и подрядной фирме (включая бонусы)
int total_payment(int HEIGHT, string** array)
{
    int payment = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        if (array[i][EXECUTOR] == "сотрудник 1" || array[i][EXECUTOR] == "сотрудник 2")
        {
            int x = (stoi(array[i][TOTAL]) + stoi(array[i][BONUS])) * 0.25;
            payment += x;
        }
        else if (array[i][EXECUTOR] == "подрядная фирма")
        {
            int x = (stoi(array[i][TOTAL]) + stoi(array[i][BONUS])) * 0.5;
            payment += x;
        }
    }
    //cout << payment;
    return payment;
}

//суммарный доход фирмы после вычета зарплаты сотрудникам и подрядной фирме
int total_profit(int HEIGHT, string** array, double bonus)
{
    int profit = bonus_plus_income(HEIGHT, array, bonus) - total_payment(HEIGHT, array);
    //cout << profit;
    return profit;
}

// отдельная задача: проверка диапазона
bool check_diapazone(const int value)
{
    int min = 1;
    int max = 200;
    return value >= min && value <= max;
}

// устанавливаем ширину массива
void set_array_widh(int& WIDTH)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 15);
    int number = -1;
    do {
        cout << "Введите ширину массива (8): ";
        string attempt;
        cin >> attempt;
        try
        {
            number = stoi(attempt); // stoi = string to int
        }
        catch (...) {
            cout << "ERROR!\n";
        }
    } while (!check_diapazone(number));

    WIDTH = number;
}

// устанавливаем высоту массива
void set_array_height(int& HEIGHT)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 15);
    int number = -1;
    do {
        cout << "Введите высоту массива (17): ";
        string attempt;
        cin >> attempt;
        try
        {
            number = stoi(attempt); // stoi = string to int
        }
        catch (...) {
            cout << "ERROR!\n";
        }
    } while (!check_diapazone(number));

    HEIGHT = number;
}

// выделяем память для массива
void allocate_2D_array_memory(string**& array, const int WIDTH, const int HEIGHT) // пометка параметра как const не позволит изменить значение параметра в теле функции
{
    array = new string * [HEIGHT]; // создание указателя на массив указателей
    for (int i = 0; i < HEIGHT; i++)
    {
        array[i] = new string[WIDTH]; //выделение памяти для массивов
    }

}

//_____________________________________________________________________________________________
//заполнение массива из текстового файла с разделителями в виде табуляции
void loadArrayFromFile(const char* filename, int HEIGHT, int WIDTH, string** array)
{
    FILE* file = fopen(filename, "r");  // открытие файла для чтения
    if (!file)
    {
        perror("Ошибка: не удалось открыть файл");
        return;
    }

    char buffer[256];  // буфер для считывания строк
    int row = 0;

    while (fgets(buffer, sizeof(buffer), file) && row < HEIGHT)
    {
        // Разбиение строки на токены
        char* token = strtok(buffer, "\t\n");  // разделение только по табуляциям
        int col = 0;

        while (token && col < WIDTH) {
            array[row][col] = string(token);  // преобразование в string и запись в массив
            token = strtok(NULL, "\t\n"); // переход на следующий кусок текста
            col++;
        }

        row++;
    }

    fclose(file);
}
//_____________________________________________________________________________________________

//меню выбора вариантов вывода информации
int menu_program(int code, int HEIGHT, int WIDTH, string** array, double bonus, string worker, HANDLE h)
{
    SetConsoleTextAttribute(h, 2);
    switch (code)
    {
    case 49:
        deadlines(HEIGHT, WIDTH, array, today_date, h);
        cout << "\n";
        break;
    case 50:                                                //сумарные поступления
        cout << "\nсумарные поступления = " << income(HEIGHT, array) << " грн";
        cout << "\n";
        break;
    case 51:                                                //сумарные поступления вместе с бонусами
        cout << "\nсумарные поступления вместе с бонусами = " << bonus_plus_income(HEIGHT, array, bonus) << " грн";
        cout << "\n";
        break;
    case 57:                                                //суммарный доход
        cout << "\nсуммарный доход = " << total_profit(HEIGHT, array, bonus) << " грн";
        cout << "\n";
        break;
    case 52:                                                //сумма надбавок
        cout << "\nсумма надбавок = " << bonus_plus(HEIGHT, array, bonus) << " грн";
        cout << "\n";
        break;
    case 53:                                                //заработаные деньги наемной фирмой или сотрудником
        cout << "\nПодсчет поступлений отдельно по каждому сотруднику или подрядной фирме на выбор\nУкажите кого хотим посмотреть?\n1-сотрудник 1\n2-сотрудник 2\n3-подрядная фирма\nESC - выход из программы\n\n";
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
                menu_program_message(code, HEIGHT, WIDTH, array, bonus, worker,h);                          //используем рекурсию!
                break;
            }
            if (code == 27)
            {
                break;
            }
            cout << "\nденьги которые заработал(a)" << worker << " = " << worker_earn(HEIGHT, array, worker) << " грн\n";
            cout << "\n";
        }
        break;
    case 54:                                                //зарплата отдельного сотрудника или подрядной фирмы
        cout << "\nЗарплата отдельного сотрудника или подрядной фирмы\nУкажите кому платим?\n1-сотрудник 1\n2-сотрудник 2\n3-подрядная фирма\nESC - выход из программы\n\n";
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
                menu_program_message(code, HEIGHT, WIDTH, array, bonus, worker, h);                         //используем рекурсию!
                break;
            }
            if (code == 27)
            {
                break;
            }
            cout << "деньги которые нужно заплатить " << worker << " = " << worker_payment(HEIGHT, array, worker) << " грн\n";
            cout << "\n";
        }
        break;
    case 55:                                                //сколько нужно заплатить всем сотрудникам и подрядной фирме (включая бонусы)
        cout << "всего нужно заплатить за работу = " << total_payment(HEIGHT, array) << " грн";
        cout << "\n";
        break;
    case 56:                                                //просто вывод всего списка
        cout << "\n";
        cout << "\n";
        cout << "Весь список дел ";
        cout << "\n";
        cout << "\n";
        show_array(HEIGHT, WIDTH, array, h);
        break;
    case 27:
        cout << "Программа завершена!\n";
        return 27;
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
    cout << "\nВведите что хотим просмотреть: \n1-список дел на сегодня\n2-сумарные поступления, без бонусов\n3-сумарные поступления вместе с бонусами\n4-сумма надбавок за выполнение работы в день ее поступления\n5-заработаные деньги наемной фирмой или сотрудником\n6-зарплата отдельного сотрудника или подрядной фирмы\n7-сколько нужно заплатить всем сотрудникам и подрядной фирме (включая бонусы)\n8-вывод всего списка дел\n9-суммарный доход\nESC - выход из программы\n";
}

//при выходе из предыдущего меню, повторный вывод подсказки с выбором действий
int menu_program_message(int code, int HEIGHT, int WIDTH, string** array, double bonus, string worker, HANDLE h) {
    while (true)
    {
        print_message();
        SetConsoleTextAttribute(h, 2);
        while (true)
        {
            int code = _getch(); // функция приостанавливает работу программы, ждёт реакции пользователя
            menu_program(code, HEIGHT, WIDTH, array, bonus, worker,h);
            if (code == 27)
            {
                return false;
                break;
            }
        }
    }
}

//сообщение приветствия
void start_message()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 14);
    string x = "Добро пожаловать в программу учета експертных оценок";
    int length = x.length();
    for (int i = 0; i < length; i++)
    {
        cout << x[i];
        Sleep(30);
    }
    cout << "\n\n";
}

//очистка выделенной памяти от данных из динамических массивов
void delete_array(string** array, int HEIGHT, int WIDTH)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        delete[] array[i];
    }

    delete[] array;
}