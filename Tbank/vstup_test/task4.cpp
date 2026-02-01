#include <iostream>
#include <string>
#include <sstream>
#include <vector>

bool proverka(const std::vector<int> &massiv, int k) {
    int min_val = massiv[0];
    int max_val = massiv[0];
    
    for (int i = 1; i < massiv.size(); i++) {
        if (massiv[i] < min_val) {
            min_val = massiv[i];
        }
        if (massiv[i] > max_val) {
            max_val = massiv[i];
        }
    }
    return (max_val - min_val <= k);
}

int main(){
    int n, k;
    std::string stroka;
    std::getline(std::cin, stroka);
    std::stringstream ss(stroka);
    ss >> n >> k;
    std::vector<int> a(n);
    std::getline(std::cin, stroka);
    std::stringstream ss2(stroka);
    int i = 0;
    while (ss2 >> a[i]){
        i++;
    }

    int ans = n;
    for (int i = 2; i<n+1; i++){
        int nachalo = 0;
        int konec = nachalo + i - 1;
        while(konec < n){
            std::vector<int> massiv;
            for (int j = nachalo; j<=konec; j++){
                massiv.push_back(a[j]);
            }
            if (proverka(massiv, k)){ ans++; }

            nachalo++;
            konec++;
        }
    }
    std::cout << ans << std::endl;
}