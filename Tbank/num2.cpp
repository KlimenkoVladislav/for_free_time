#include <iostream>
#include <math.h>

int main(){
    int a;
    std::cin >> a;
    int k = 0;
    while (pow(2, k)<a){
        k++;
    }
    std::cout << k << std::endl;
}