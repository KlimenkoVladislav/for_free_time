#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void kramer();
float determinat(int N, int **matrica, int flag);
void sum_matrix();
std::vector<std::vector<float>> add_new_matrix(int &kol_elem_in_row);
std::vector<float> add_str_in_matrix(std::string stroka_for_add_in_matrix, int &kol_elem_in_row);

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
                std::cout << "\n1 - Посчитать определитель\n"
                          << "2 - Сложить матрицы\n"
                          << "0 - Вернуться обратно\n";
                do{
                    std::cout << "Выберите задачу: ";
                    std::cin >> zadacha;
                }while(zadacha < 0 or zadacha > 2);

                if (zadacha == 0){break;}
                else if (zadacha == 1){kramer();}
                else if (zadacha == 2){sum_matrix();}
            }
        }
    }
}

void kramer(){
    int n; 
    do{
        std::cout << "Введите размер матрицы NxN: ";
        std::cin >> n;
    }while(n<2);

    int **matrica = new int*[n];
    matrica[0] = new int[n*(n+1)];
    for (int i = 0; i<n; i++){
        matrica[i] = matrica[0] + i*(n+1);
        for (int j = 0; j<n+1; j++){
            int k; 
            if (j!=n){std::cout << "Введите значение x" << j+1 << ": ";}
            else {std::cout << "Введите значение, которому будет равна ваша строка: ";}
            std::cin >> k;
            matrica[i][j] = k;
        }
        std::cout << "__________________________________________________________\n";
    }

    std::cout << "Система уравнений:\n";
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n+1; j++){
            if (j < n-1){
                std::cout << "(" << matrica[i][j] << ")*" << "x" << j+1 << " + ";
            }
            else if (j == n-1){
                std::cout << "(" << matrica[i][j] << ")*" << "x" << j+1 << " ";
            }
            else if (j == n){
                std::cout << "= " << matrica[i][j] << "\n";
            }
        }
    }

    std::cout << "\nРасширенная матрица:\n";
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n+1; j++){
            if (j != n){
                std::cout << matrica[i][j] << " ";
            }
            else{
                std::cout << "| " << matrica[i][j] << "\n";
            }
        }
    }
    std::cout << "\n";

    int main_det = determinat(n, matrica, -1);
    if (main_det!=0){
        for (int i=0; i<n; i++){
            std::cout << "x" << i+1 << " = " << determinat(n, matrica, i)/main_det << "\n"; 
        }
    }
    else{std::cout << "Нет единственного решения\n";}

    delete[] matrica[0];
    delete[] matrica;
}

float determinat(int N, int **matrica, int flag){
    float det = 0;
    int **d_matrica = new int*[N];
    d_matrica[0] = new int[N*(N+1)];
    for (int i=0; i<N; i++){
        d_matrica[i] = d_matrica[0] + i*(N+1);
        for (int j=0; j<N+1; j++){
            d_matrica[i][j] = matrica[i][j];
        }
        if (flag>=0){d_matrica[i][flag] = matrica[i][N];}
    }

    if (N>2){
        for (int x=0; x<N; x++){
            int **smaller_matrica = new int*[N-1];
            smaller_matrica[0] = new int[N];
            for (int i=0; i<N-1; i++){
                smaller_matrica[i] = smaller_matrica[0] + i*N;
                for (int j=0; j<N; j++){
                    if (j<x){smaller_matrica[i][j] = d_matrica[i][j];}
                    else if (j>=x){smaller_matrica[i][j] = d_matrica[i][j+1];}
                }
            }
            int znak = (x % 2 == 0)? 1 : -1;
            det+=znak*d_matrica[N-1][x]*determinat(N-1, smaller_matrica, -1);

            delete[] smaller_matrica[0];
            delete[] smaller_matrica;
        }
    }
    else if (N==2){det=d_matrica[0][0]*d_matrica[1][1]-d_matrica[0][1]*d_matrica[1][0];}

    delete[] d_matrica[0];
    delete[] d_matrica;
    return det;
}

void sum_matrix(){
    int kol_matric;
    do{
        std::cout << "Введите количество матриц, которые хотите сложить: ";
        std::cin >> kol_matric;
    }while(kol_matric < 2);
    std::cin.ignore();

    std::vector<std::vector<std::vector<float>>> massiv_matric;
    int kol_elem_in_row = 0;
    for (int i = 0; i<kol_matric; i++){
        massiv_matric.push_back(add_new_matrix(kol_elem_in_row));

        for (const auto &row: massiv_matric[i]){
            for(float val: row){
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << GREEN << "ОТВЕТ" << RESET << std::endl;
    for (int i = 0; i<kol_elem_in_row; i++){
        for (int j = 0; j<kol_elem_in_row; j++){
            std::cout << massiv_matric[0][i][j] + massiv_matric[1][i][j] << " ";
        }
        std::cout << std::endl;
    }

    massiv_matric.clear();
}

std::vector<std::vector<float>> add_new_matrix(int &kol_elem_in_row){
    std::vector<std::vector<float>> new_matrix;
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
        if (row == 0){
            new_matrix.reserve(kol_elem_in_row*(kol_elem_in_row-1));
        }
        row++;
    }while(row < kol_elem_in_row);

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