#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

int main(){
    unsigned long long int l, r;
    std::string stroka;
    std::getline(std::cin, stroka);
    std::stringstream ss(stroka);
    ss >> l >> r;

    int kol = 0;
    unsigned long long int last = 1;
    for (int i = 0; i<18; i++){
        if (last == 0){ break; }
        if (i!=0){
            last = last*10 + 1;
        }
        for (int j = 1; j<10; j++){
            if (last*j >= l and last*j <= r){
                kol++;
            }
            if (last*j > r){
                last = 0;
                break;
            }
        }
    }
    std::cout << kol << "\n";
}