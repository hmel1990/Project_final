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


//����������� ���� � ���������� �� � ���� ������
string today_date()
{
    string today;
    cout << "\n������� ���� ��� ����������� ������: ";
    cin >> today;
    cout << "\n";
    return today;
}

//���� ����������� ���� ��������� � ����� ������ ������� ��� ������ � �������
void deadlines(int HEIGHT, int WIDTH, string** array, string(*pf)(), HANDLE h) // ��������� �� �������
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

//������� ���� ������
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

// ��������� �������� �� ���������� ������ � ���� �� �����������, �������� ����� 20% (��� �������� ��� ����������� � ��������� �����)
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

// �������� �����������, ��� ������� (��� ����������� ��� ����������� � ��������� �����)
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

//������� �������� ����������� ������ � �������� 
int bonus_plus_income(int HEIGHT, string** array, double bonus)
{
    int total_incom = 0;
    total_incom = income(HEIGHT, array) + bonus_plus(HEIGHT, array, bonus);
    //cout << total_incom << "\n";
    return total_incom;
}

//��������� ������ � ������ ������� ��������
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

//c������ ����������� ������ ������� ������ ��� ����������� (������� ������� �������� �� ������� ���������� ��� ��������� ����� �� �����)
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

//c������ ������� ����� ��������� ���������� ���������� ��� ��������� �����
int worker_payment(int HEIGHT, string** array, string worker)
{
    int payment = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        if (array[i][EXECUTOR] == worker)
        {
            if (worker == "��������� 1" || worker == "��������� 2")
            {
                int x = (stoi(array[i][TOTAL]) + stoi(array[i][BONUS])) * 0.25;
                payment += x;
            }
            else if (worker == "��������� �����")
            {
                int x = (stoi(array[i][TOTAL]) + stoi(array[i][BONUS])) * 0.5;
                payment += x;
            }

        }
    }
    //cout << payment;
    return payment;
}

//c������ ������� ����� ��������� ���� ����������� � ��������� ����� (������� ������)
int total_payment(int HEIGHT, string** array)
{
    int payment = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        if (array[i][EXECUTOR] == "��������� 1" || array[i][EXECUTOR] == "��������� 2")
        {
            int x = (stoi(array[i][TOTAL]) + stoi(array[i][BONUS])) * 0.25;
            payment += x;
        }
        else if (array[i][EXECUTOR] == "��������� �����")
        {
            int x = (stoi(array[i][TOTAL]) + stoi(array[i][BONUS])) * 0.5;
            payment += x;
        }
    }
    //cout << payment;
    return payment;
}

//��������� ����� ����� ����� ������ �������� ����������� � ��������� �����
int total_profit(int HEIGHT, string** array, double bonus)
{
    int profit = bonus_plus_income(HEIGHT, array, bonus) - total_payment(HEIGHT, array);
    //cout << profit;
    return profit;
}

// ��������� ������: �������� ���������
bool check_diapazone(const int value)
{
    int min = 1;
    int max = 200;
    return value >= min && value <= max;
}

// ������������� ������ �������
void set_array_widh(int& WIDTH)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 15);
    int number = -1;
    do {
        cout << "������� ������ ������� (8): ";
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

// ������������� ������ �������
void set_array_height(int& HEIGHT)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 15);
    int number = -1;
    do {
        cout << "������� ������ ������� (17): ";
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

// �������� ������ ��� �������
void allocate_2D_array_memory(string**& array, const int WIDTH, const int HEIGHT) // ������� ��������� ��� const �� �������� �������� �������� ��������� � ���� �������
{
    array = new string * [HEIGHT]; // �������� ��������� �� ������ ����������
    for (int i = 0; i < HEIGHT; i++)
    {
        array[i] = new string[WIDTH]; //��������� ������ ��� ��������
    }

}

//_____________________________________________________________________________________________
//���������� ������� �� ���������� ����� � ������������� � ���� ���������
void loadArrayFromFile(const char* filename, int HEIGHT, int WIDTH, string** array)
{
    FILE* file = fopen(filename, "r");  // �������� ����� ��� ������
    if (!file)
    {
        perror("������: �� ������� ������� ����");
        return;
    }

    char buffer[256];  // ����� ��� ���������� �����
    int row = 0;

    while (fgets(buffer, sizeof(buffer), file) && row < HEIGHT)
    {
        // ��������� ������ �� ������
        char* token = strtok(buffer, "\t\n");  // ���������� ������ �� ����������
        int col = 0;

        while (token && col < WIDTH) {
            array[row][col] = string(token);  // �������������� � string � ������ � ������
            token = strtok(NULL, "\t\n"); // ������� �� ��������� ����� ������
            col++;
        }

        row++;
    }

    fclose(file);
}
//_____________________________________________________________________________________________

//���� ������ ��������� ������ ����������
int menu_program(int code, int HEIGHT, int WIDTH, string** array, double bonus, string worker, HANDLE h)
{
    SetConsoleTextAttribute(h, 2);
    switch (code)
    {
    case 49:
        deadlines(HEIGHT, WIDTH, array, today_date, h);
        cout << "\n";
        break;
    case 50:                                                //�������� �����������
        cout << "\n�������� ����������� = " << income(HEIGHT, array) << " ���";
        cout << "\n";
        break;
    case 51:                                                //�������� ����������� ������ � ��������
        cout << "\n�������� ����������� ������ � �������� = " << bonus_plus_income(HEIGHT, array, bonus) << " ���";
        cout << "\n";
        break;
    case 57:                                                //��������� �����
        cout << "\n��������� ����� = " << total_profit(HEIGHT, array, bonus) << " ���";
        cout << "\n";
        break;
    case 52:                                                //����� ��������
        cout << "\n����� �������� = " << bonus_plus(HEIGHT, array, bonus) << " ���";
        cout << "\n";
        break;
    case 53:                                                //����������� ������ ������� ������ ��� �����������
        cout << "\n������� ����������� �������� �� ������� ���������� ��� ��������� ����� �� �����\n������� ���� ����� ����������?\n1-��������� 1\n2-��������� 2\n3-��������� �����\nESC - ����� �� ���������\n\n";
        while (true)
        {
            int code = _getch();
            switch (code)
            {
            case 49:
                worker = "��������� 1";
                break;
            case 50:
                worker = "��������� 2";
                break;
            case 51:
                worker = "��������� �����";
                break;
            case 27:
                cout << "�����\n";
                menu_program_message(code, HEIGHT, WIDTH, array, bonus, worker,h);                          //���������� ��������!
                break;
            }
            if (code == 27)
            {
                break;
            }
            cout << "\n������ ������� ���������(a)" << worker << " = " << worker_earn(HEIGHT, array, worker) << " ���\n";
            cout << "\n";
        }
        break;
    case 54:                                                //�������� ���������� ���������� ��� ��������� �����
        cout << "\n�������� ���������� ���������� ��� ��������� �����\n������� ���� ������?\n1-��������� 1\n2-��������� 2\n3-��������� �����\nESC - ����� �� ���������\n\n";
        while (true)
        {
            int code = _getch();
            switch (code)
            {
            case 49:
                worker = "��������� 1";
                break;
            case 50:
                worker = "��������� 2";
                break;
            case 51:
                worker = "��������� �����";
                break;
            case 27:
                cout << "�����\n";
                menu_program_message(code, HEIGHT, WIDTH, array, bonus, worker, h);                         //���������� ��������!
                break;
            }
            if (code == 27)
            {
                break;
            }
            cout << "������ ������� ����� ��������� " << worker << " = " << worker_payment(HEIGHT, array, worker) << " ���\n";
            cout << "\n";
        }
        break;
    case 55:                                                //������� ����� ��������� ���� ����������� � ��������� ����� (������� ������)
        cout << "����� ����� ��������� �� ������ = " << total_payment(HEIGHT, array) << " ���";
        cout << "\n";
        break;
    case 56:                                                //������ ����� ����� ������
        cout << "\n";
        cout << "\n";
        cout << "���� ������ ��� ";
        cout << "\n";
        cout << "\n";
        show_array(HEIGHT, WIDTH, array, h);
        break;
    case 27:
        cout << "��������� ���������!\n";
        return 27;
        break;
    default:
        cout << code << "\n";
        break;
    }
}


//��������� � ���������� ��� ���� ������ (�������)
void print_message()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 14);
    cout << "\n������� ��� ����� �����������: \n1-������ ��� �� �������\n2-�������� �����������, ��� �������\n3-�������� ����������� ������ � ��������\n4-����� �������� �� ���������� ������ � ���� �� �����������\n5-����������� ������ ������� ������ ��� �����������\n6-�������� ���������� ���������� ��� ��������� �����\n7-������� ����� ��������� ���� ����������� � ��������� ����� (������� ������)\n8-����� ����� ������ ���\n9-��������� �����\nESC - ����� �� ���������\n";
}

//��� ������ �� ����������� ����, ��������� ����� ��������� � ������� ��������
int menu_program_message(int code, int HEIGHT, int WIDTH, string** array, double bonus, string worker, HANDLE h) {
    while (true)
    {
        print_message();
        SetConsoleTextAttribute(h, 2);
        while (true)
        {
            int code = _getch(); // ������� ���������������� ������ ���������, ��� ������� ������������
            menu_program(code, HEIGHT, WIDTH, array, bonus, worker,h);
            if (code == 27)
            {
                return false;
                break;
            }
        }
    }
}

//��������� �����������
void start_message()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 14);
    string x = "����� ���������� � ��������� ����� ���������� ������";
    int length = x.length();
    for (int i = 0; i < length; i++)
    {
        cout << x[i];
        Sleep(30);
    }
    cout << "\n\n";
}

//������� ���������� ������ �� ������ �� ������������ ��������
void delete_array(string** array, int HEIGHT, int WIDTH)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        delete[] array[i];
    }

    delete[] array;
}