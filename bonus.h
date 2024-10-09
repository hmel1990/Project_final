#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <iomanip>

enum KeyCodes { NUMBER = 0, ADRESS = 1, CUSTOMER = 2, EXECUTOR = 3, TOTAL = 4, INCOME = 5, DELIVERY = 6, BONUS = 7 };

using namespace std;

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
int menu_program_message(int code, int HEIGHT, int WIDTH, string** array, double bonus, string worker);
void set_array_widh(int& WIDTH);
void set_array_height(int& HEIGHT);
void allocate_2D_array_memory(string**& array, const int WIDTH, const int HEIGHT);
void print_message();
void delete_array(string** array, int HEIGHT, int WIDTH);