#include <iostream>
#include <string>
#include <sstream>

int main(){
    int l, w, a, b;
    std::string stroka;
    std::getline(std::cin, stroka);
    std::stringstream ss(stroka);
    ss >> l >> w;
    std::getline(std::cin, stroka);
    std::stringstream ss2(stroka);
    ss2 >> a >> b;

    std::cout << (l/a)*(w/b) << std::endl;
}