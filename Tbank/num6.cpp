#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main(){
    int kol_chel;
    std::cin >> kol_chel;
    std::cin.ignore();

    std::string stroka;
    std::getline(std::cin, stroka);
    std::stringstream ss(stroka);

    std::vector<int> vector(kol_chel);
    int j = 0;
    while (ss >> vector[j]){
        j++;
    }

    std::vector<int> ans;
    std::vector<int> duraki;
    for (int i = 1; i<=kol_chel; i++){
        if (vector[i-1]%2 != i%2){
            duraki.push_back(vector[i-1]);
            ans.push_back(i);
        }
    }
    if (duraki.size() == 2){
        std::cout << ans[0] << " " << ans[1] << "\n";
    }
    else if (duraki.size()>2){
        std::cout << -1 << " " << -1 << "\n";
    }
    else if (duraki.size() == 0){
        if (kol_chel > 2){
            std::cout << 1 << " " << 3 << "\n";
        }
        else {
            std::cout << -1 << " " << -1 << "\n";
        }
    }
}