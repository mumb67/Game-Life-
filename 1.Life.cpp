#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

int life_counter = 1;
int diff_check = 1;
int generation_count = 0;

void show(int** table, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            switch (table[i][j]) {
            case 0: std::cout << ". "; break;
            case 1: std::cout << "@ "; break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Generation: " << generation_count << ". " << "Allive cells: " << life_counter << std::endl;
}

void copy(int **table, int **table_copy, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            table_copy[i][j] = table[i][j];
        }
    }
}

void step(int** table, int** table_copy, int width, int height) {
    life_counter = 0;
    diff_check = 0;
    generation_count++;
    copy(table, table_copy, width, height);

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int count_neib = 0;
            //      ПОИСК ЖИВЫХ КЛЕТОК ВОКРУГ
            if (i > 0 && j > 0) {
                count_neib += table_copy[i - 1][j - 1];
            }
            if (i > 0) {
                count_neib += table_copy[i - 1][j];
            }
            if (i > 0 && j < height - 1) {
                count_neib += table_copy[i - 1][j + 1];
            }
            if (j > 0) {
                count_neib += table_copy[i][j - 1];
            }
            if (j < height - 1) {
                count_neib += table_copy[i][j + 1];
            }
            if (i < width - 1 && j > 0) {
                count_neib += table_copy[i + 1][j - 1];
            }
            if (i < width - 1) {
                count_neib += table_copy[i + 1][j];
            }
            if (i < width - 1 && j < height - 1) {
                count_neib += table_copy[i + 1][j + 1];
            }

            //      ПРАВИЛА СМЕРТИ ИЛИ ПОЯВЛЕНИЯ ЖИЗНИ В КЛЕТКЕ
            if (count_neib == 3 && table_copy[i][j] == 0) {
                table[i][j] = 1;
            }
            else if (count_neib < 2 || count_neib > 3) {
                table[i][j] = 0;
            }

            //      СЧЕТЧИК ЖИВЫХ КЛЕТОК
            if (table_copy[i][j] == 1) {
                life_counter++;
            }
            //      КОНТРОЛЬ ИЗМЕНЧИВОСТИ МАССИВА
            if (table[i][j] != table_copy[i][j]) {
                diff_check++;
            }
        }
    }
    
}

void delete_array(int** array, int width) {
    for (int i = 0; i < width; i++) {
        delete[] array[i];
    }
    delete[] array;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::ifstream fin("in.txt");
    if (!fin.is_open()) {
        std::cout << "Не получилось открыть файл!" << std::endl;
        return 0;
    }
    int a, b;
    fin >> a;
    fin >> b;

    //      СОЗДАЕМ МАССИВЫ
    const int width = a;
    const int height = b;

    int** table = new int* [width];
    int** table_copy = new int* [width];

    for (int i = 0; i < width; i++) {
        table[i] = new int[height];
        table_copy[i] = new int[height];
        for (int j = 0; j < height; j++) {
            table[i][j] = 0;
            table_copy[i][j] = 0;
        }
    }

    int lifeCell_x = 0, lifeCell_y = 0; //  КООРДИНАТЫ ЖИВЫХ КЛЕТОК

    while (!fin.eof()) {
        fin >> lifeCell_x;
        fin >> lifeCell_y;
        table[lifeCell_x][lifeCell_y] = 1;
    }

    //      ВЫВОД И КОПИРОВАНИЕ
    while (life_counter != 0 && diff_check != 0) {
        system("cls");
        step(table, table_copy, width, height);
        show(table_copy, width, height);
        std::cout << std::endl;
        Sleep(10);
    };

    if (life_counter == 0) { std::cout << "There are no living cells" << std::endl; }
    if (diff_check == 0) { std::cout << "The game is looping" << std::endl; }

    //      УДАЛЕНИЕ МАССИВОВ
    delete_array(table, width);
    delete_array(table_copy, width);
}