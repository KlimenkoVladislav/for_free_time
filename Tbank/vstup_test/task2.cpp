#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

int main(){
    int n, k;
    std::string stroka;
    std::getline(std::cin, stroka);
    std::stringstream ss(stroka);
    ss >> n >> k;
    std::vector<int> vector(n);
    std::getline(std::cin, stroka);
    std::stringstream ss2(stroka);
    int i = 0;
    while (ss2 >> vector[i]){
        i++;
    }

    std::vector<int> ans(n, 0);
    ans[0] = 1;
    for (int i = 0; i<n; i++){
        if (ans[i] == 0){ break; }
        for (int j = i+1; j<n; j++){
            if (abs(vector[i] - vector[j]) <= k){
                ans[j] = 1;
            }
        }
    }
    for (int num : ans){
        std::cout << num << " ";
    }
    std::cout << std::endl;
}