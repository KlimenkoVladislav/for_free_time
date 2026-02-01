#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

void nedostatki(int value, std::vector<int> &massiv_for_return){
    int razriad = 10;
    while (value){
        massiv_for_return.push_back(razriad - (razriad/10) - (value%10)*(razriad/10));
        value /= 10;
        razriad *= 10;
    }
}

int main(){
    int n, k;   //n - количество чисел на бумажке, k - органичение на число операций
    std::string stroka;
    std::getline(std::cin, stroka);
    std::stringstream ss(stroka);
    ss >> n >> k;

    std::vector<int> massiv(n);
    std::getline(std::cin, stroka);
    std::stringstream ss2(stroka);
    int i = 0;
    while (ss2 >> massiv[i]){
        i++;
    }

    std::vector<int> massiv_for_sort;
    for (int val : massiv){
        std::vector<int> massiv_for_return;
        nedostatki(val, massiv_for_return);
        if (massiv_for_return.size() != 0){
            for (int num : massiv_for_return){
                massiv_for_sort.push_back(num);
            }
        }
    }
    std::sort(massiv_for_sort.begin(), massiv_for_sort.end(), std::greater<int>());
    
    int finish_sum = 0;
    int j = 0;
    for (int val : massiv_for_sort){
        finish_sum += val;
        j++;
        if (j == k){
            break;
        }
    }

    std::cout << finish_sum << "\n";
}