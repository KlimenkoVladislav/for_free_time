#include <iostream>

float determinat(int N, int **matrica, int flag);

int main(){
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