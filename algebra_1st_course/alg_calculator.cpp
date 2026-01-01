#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

typedef std::vector<std::vector<float>> v_v_float;

void kramer();
float determinat(int N, v_v_float matrica, int flag);
void sum_matrix();
v_v_float add_new_matrix(int &kol_elem_in_row, int plus_elem_in_row, int kol_row = -1);
std::vector<float> add_str_in_matrix(std::string stroka_for_add_in_matrix, int &kol_elem_in_row);
void det_find();
void multiply_matrix();
void transpose();

int main(){
    while (true){
        int napravlenie;
        std::cout << "\n1 - Работа с матрицами\n"
                  << "0 - Выход\n";
        do{
            std::cout << "Введите выбранное направление: ";
            std::cin >> napravlenie;
        }while (napravlenie < 0 or napravlenie > 1);

        if (napravlenie == 0){
            return 0;
        }
        else if (napravlenie == 1){
            while (true){
                int zadacha;
                std::cout << "\n1 - Сложить матрицы\n"
                          << "2 - Умножить матрицы\n"
                          << "3 - Транспонировать матрицу\n"
                          << "4 - Найти определитель матрицы\n"
                          << "5 - Найти неизвестные (x)\n"
                          << "0 - Вернуться обратно\n";
                do{
                    std::cout << "Выберите задачу: ";
                    std::cin >> zadacha;
                }while(zadacha < 0 or zadacha > 5);

                if (zadacha == 0){break;}
                else if (zadacha == 1){sum_matrix();}
                else if (zadacha == 2){multiply_matrix();}
                else if (zadacha == 3){transpose();}
                else if (zadacha == 4){det_find();}
                else if (zadacha == 5){kramer();}
            }
        }
    }
}

void kramer(){
    int kol_row; 
    do{
        std::cout << "Введите размер матрицы NxN: ";
        std::cin >> kol_row;
    }while(kol_row<2);
    std::cin.ignore();

    int kol_elem_in_row = kol_row+1;
    v_v_float matrica = add_new_matrix(kol_elem_in_row, kol_elem_in_row-kol_row);

    std::cout << "Система уравнений:\n";
    for (int i = 0; i<kol_row; i++){
        for (int j = 0; j<kol_elem_in_row; j++){
            if (j < kol_row-1){
                std::cout << "(" << matrica[i][j] << ")*" << "x" << j+1 << " + ";
            }
            else if (j == kol_row-1){
                std::cout << "(" << matrica[i][j] << ")*" << "x" << j+1 << " ";
            }
            else if (j == kol_row){
                std::cout << "= " << matrica[i][j] << "\n";
            }
        }
    }

    std::cout << "\nРасширенная матрица:\n";
    for (int i = 0; i<kol_row; i++){
        for (int j = 0; j<kol_elem_in_row; j++){
            if (j != kol_row){
                std::cout << matrica[i][j] << " ";
            }
            else{
                std::cout << "| " << matrica[i][j] << "\n";
            }
        }
    }
    std::cout << "\n";

    int main_det = determinat(kol_row, matrica, -1);
    std::cout << GREEN << "\nОТВЕТ" << RESET << std::endl;
    if (main_det!=0){
        for (int i=0; i<kol_row; i++){
            std::cout << "x" << i+1 << " = " << determinat(kol_row, matrica, i)/main_det << "\n"; 
        }
    }
    else{std::cout << "Нет единственного решения\n";}
}

float determinat(int N, v_v_float matrica, int flag){
    float det = 0;

    if (flag >= 0){
        for (int i = 0; i<N; i++){
            matrica[i][flag] = matrica[i][N];
        }
    }

    if (N>2){
        for (int x=0; x<N; x++){
            v_v_float smaller_matrica(N-1, std::vector<float>(N, 0));
            for (int i=0; i<N-1; i++){
                for (int j=0; j<N; j++){
                    if (j<x){smaller_matrica[i][j] = matrica[i][j];}
                    else if (j>=x){smaller_matrica[i][j] = matrica[i][j+1];}
                }
            }
            int znak = (x % 2 == 0)? 1 : -1;
            det+=znak*matrica[N-1][x]*determinat(N-1, smaller_matrica, -1);
        }
    }
    else if (N==2){det=matrica[0][0]*matrica[1][1]-matrica[0][1]*matrica[1][0];}

    return det;
}

void sum_matrix(){
    int kol_matric;
    do{
        std::cout << "Введите количество матриц, которые хотите сложить: ";
        std::cin >> kol_matric;
    }while(kol_matric < 2);
    std::cin.ignore();

    std::vector<v_v_float> massiv_matric;
    int kol_elem_in_row = 0;
    for (int i = 0; i<kol_matric; i++){
        massiv_matric.push_back(add_new_matrix(kol_elem_in_row, 0));
    }

    std::cout << GREEN << "\nОТВЕТ" << RESET << std::endl;
    int sum = 0;
    for (int i = 0; i<kol_elem_in_row; i++){
        for (int j = 0; j<kol_elem_in_row; j++){
            for (int z = 0; z<kol_matric; z++){
                sum += massiv_matric[z][i][j];
            }
            std::cout << sum << " ";
            sum = 0;
        }
        std::cout << std::endl;
    }

    massiv_matric.clear();
}

v_v_float add_new_matrix(int &kol_elem_in_row, int plus_elem_in_row, int kol_row){
    v_v_float new_matrix;
    if (kol_row == -1){
        kol_row = kol_elem_in_row - plus_elem_in_row;
    }
    int row = 0;
    
    do{
        std::string str_row;
        while (true){
            std::cout << "Введите строку матрицы: ";
            std::getline(std::cin, str_row);
            new_matrix.push_back(add_str_in_matrix(str_row, kol_elem_in_row));
            if (new_matrix.back().size() != 0){
                break;
            }
            else{
                new_matrix.pop_back();
            }
        }
        if (kol_row <= 0){
            kol_row = kol_elem_in_row - plus_elem_in_row;
        }
        if (row == 0){
            new_matrix.reserve(kol_elem_in_row*(kol_row-1));
        }
        row++;
    }while(row < kol_row);

    return new_matrix;
}

std::vector<float> add_str_in_matrix(std::string stroka_for_add_in_matrix, int &kol_elem_in_row_global){
    std::vector<float> str_for_matrix;
    float elem = 0.0;
    std::stringstream ss(stroka_for_add_in_matrix);
    int kol_elem_in_row_local = 0;
    while (ss >> elem){
        kol_elem_in_row_local++;
        str_for_matrix.push_back(elem);
    }
    if (kol_elem_in_row_global == 0){
        kol_elem_in_row_global = kol_elem_in_row_local;
    }
    else if (kol_elem_in_row_global != kol_elem_in_row_local){
        std::cout << RED << "error " << RESET;
        str_for_matrix.clear();
    }
    return str_for_matrix;
}

void det_find(){
    std::cin.ignore();
    int kol_elem_in_row = 0;
    v_v_float matrica = add_new_matrix(kol_elem_in_row, 0);
    for (auto &row : matrica){
        row.push_back(0);
    }
    float det = determinat(kol_elem_in_row, matrica, -1);
    std::cout << GREEN << "\nОТВЕТ" << RESET << std::endl;
    std::cout << det << std::endl;
}

void multiply_matrix(){
    v_v_float matrica_1, matrica_2;
    int kol_elem_in_row_1 = 0;
    int kol_elem_in_row_2 = 0;
    int kol_row;
    do{
        std::cout << "Введите количество строк в первой матрице: ";
        std::cin >> kol_row;
    }while(kol_row <= 0);
    std::cin.ignore();
    
    matrica_1 = add_new_matrix(kol_elem_in_row_1, 0, kol_row);
    std::cout << "\nВторая матрица: \n";
    matrica_2 = add_new_matrix(kol_elem_in_row_2, 0, kol_elem_in_row_1);

    std::cout << GREEN << "\nОТВЕТ" << RESET << std::endl;
    for (int i = 0; i<kol_row; i++){
        for (int j = 0; j<kol_elem_in_row_2; j++){
            float mult = 0.0;
            int z = 0;
            for (const auto &row : matrica_2){
                mult += matrica_1[i][z] * row[j];
                z++;
            }
            std::cout << mult << " ";
        }
        std::cout << std::endl;
    }
}

void transpose(){
    v_v_float matrica;
    int kol_elem_in_row = 0;
    int kol_row;
    do{
        std::cout << "Введите количекство строк матрицы: ";
        std::cin >> kol_row;
    }while(kol_row <= 0);
    std::cin.ignore();

    matrica = add_new_matrix(kol_elem_in_row, 0, kol_row);
    for (int i = 0; i<kol_elem_in_row; i++){
        for (const auto &row : matrica){
            std::cout << row[i] << " ";
        }
        std::cout << std::endl;
    }
}