#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main(){
    int n, t;   //n - количество сотрудников, t - время, когда сотрудник покинет офис
    std::string stroka;
    std::getline(std::cin, stroka);
    std::stringstream ss(stroka);
    ss >> n >> t;

    std::vector<int> nomera(n);
    std::getline(std::cin, stroka);
    std::stringstream ss1(stroka);
    int i = 0;
    while(ss1 >> nomera[i]){
        i++;
    }

    int kakoi_svalivaet;
    std::cin >> kakoi_svalivaet;

    if (nomera[kakoi_svalivaet-1] - nomera.front() <= t){
        std::cout << nomera.back() - nomera.front() << std::endl;
    } else if (nomera.back() - nomera[kakoi_svalivaet-1] <= t){
        std::cout << nomera.back() - nomera.front() << std::endl;
    } else {
        if (nomera.back() - nomera[kakoi_svalivaet-1] < nomera[kakoi_svalivaet-1] - nomera.front()){
            std::cout << 2*(nomera.back() - nomera[kakoi_svalivaet-1]) + nomera[kakoi_svalivaet-1] - nomera.front() << std::endl;
        } else {
            std::cout << 2*(nomera[kakoi_svalivaet-1] - nomera.front()) + nomera.back() - nomera[kakoi_svalivaet-1] << std::endl;
        }
    }
}