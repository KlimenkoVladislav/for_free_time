#include <iostream>
#include <sstream>
#include <string>

int main(){
    int a, b, c, d;
    std::string stroka;
    std::getline(std::cin, stroka);
    std::stringstream ss(stroka);
    ss >> a >> b >> c >> d;
    if (d<=b){ std::cout << a << std::endl; }
    else { std::cout << a+(d-b)*c << std::endl; }
}