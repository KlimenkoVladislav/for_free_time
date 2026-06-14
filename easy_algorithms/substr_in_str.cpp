#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

u_int32_t findHashSubstr(const std::vector<int> &p_in_pow, 
                         const std::string substr){
    u_int32_t hash = 0;
    int substr_length = substr.length();
    for (int i = 0; i < substr_length; i++){
        hash += substr[i] * p_in_pow[i];
    }
    hash %= 512;

    return hash;
}

u_int32_t countingMatches(const std::vector<int> &p_in_pow, 
                          const std::string str, 
                          const std::string substr){
    u_int32_t hash_substr = findHashSubstr(p_in_pow, substr);

    int count = 0;
    for (int i = 0; i < str.length()-substr.length()+1; i++){
        u_int32_t hash_part_of_str = 0;
        for (int j = i; j < i+substr.length(); j++){
            hash_part_of_str += str[j] * p_in_pow[j-i];
        }
        hash_part_of_str %= 512;

        if (hash_part_of_str == hash_substr){ count++; }
    }

    return count;
}

int main(){
    std::string str;
    std::string substr;

    std::cout << "Введите строку: ";
    std::getline(std::cin, str);
    std::cout << "Введите подстроку, которую будем искать: ";
    std::getline(std::cin, substr);

    if (substr.length() > 8){
        std::cout << "Тяжёлое количество символов в подстроке для простой программки\n";
        return -2;
    }
    if (substr.length() > str.length()){
        std::cout << "Подстрока не может быть больше строки\n";
        return -2;
    }

    std::vector<int> p_in_pow = {1};
    int p = 1;
    for (int i = 1; i < substr.length(); i++){
        p *= 31;
        p_in_pow.push_back(p);
    }
    std::reverse(p_in_pow.begin(), p_in_pow.end());

    std::cout << countingMatches(p_in_pow, str, substr) << "\n";
}