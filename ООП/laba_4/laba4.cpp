#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define GREEN "\033[32m"
#define RESET "\033[0m"

class EducationalInstitution{
private:
    std::string _type;
    std::string _submission;

    void change_type(){
        std::cout << "\nВведите тип образовательного учреждения: ";
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()){
            _type = input;
        }
        else {
            std::cout << "Ничего не изменено\n";
            return;
        }
    }
    void change_summission(){
        std::cout << "Введите подчинение: ";
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()){
            _submission = input;
        }
        else {
            std::cout << "Ничего не изменено\n";
            return;
        }
    }

public:
    EducationalInstitution(std::string t, std::string s) : _type(t), _submission(s) {}

    static EducationalInstitution create(){
        std::cout << "Введите тип образовательного учреждения: ";
        std::string _type;
        std::getline(std::cin, _type);

        std::cout << "Введите подчинение: ";
        std::string _submission;
        std::getline(std::cin, _submission);

        return EducationalInstitution(_type, _submission);
    }

    void change_info(){
        std::cout << "\nДо изменений:\n";
        get_all();

        change_type();
        change_summission();

        std::cout << "\nПосле изменений:\n";
        get_all();
    }

    std::string get_type() const {
        return _type;
    }

    std::string get_submission() const {
        return _submission;
    }

    void get_all() const {
        std::cout << "Тип учреждения: " << _type << "\n"
                  << "Подчинение: " << _submission << "\n";
    }
};

int main(){
    int kol;
    std::cout << "Введите количество учебных учреждений: ";
    std::cin >> kol;
    std::cin.ignore();

    std::vector<EducationalInstitution> all;
    for (int i = 0; i<kol; i++){
        EducationalInstitution institution = EducationalInstitution::create();

        int change;
        while (true){
            do{
                std::cout << "Хотите ли вы что-то изменить в введённых вами данных? 0 - нет, 1 - да: ";
                std::cin >> change;
            }while(change<0 or change>1);
            std::cin.ignore();
            if (change == 1){
                institution.change_info();
            }
            else {break;}
        }

        std::cout << "Тип учреждения: " << institution.get_type() << std::endl;
        std::cout << "Подчинение: " << institution.get_submission() << std::endl;
        institution.get_all();
        std::cout << std::endl;

        all.push_back(std::move(institution));
    }

    std::vector<EducationalInstitution> new_all;
    for (int i = 0; i<kol; i++){
        if (all[i].get_type() == "school"){
            new_all.push_back(all[i]);
        }
    }
    if (new_all.empty()){
        std::cout << "Новый вектор пуст\n";
        return 0;
    }

    std::sort(new_all.begin(), new_all.end(), 
        [](const EducationalInstitution &a, const EducationalInstitution &b){ return a.get_type().size() > b.get_type().size(); });

    for (const auto &object : new_all){
        std::cout << GREEN;
        object.get_all();
        std::cout << RESET;
    }

    while (true){
        int change;
        do{
            std::cout << "Хотите ли вы что-то добавить в новый вектор? 0 - нет, 1 - да: ";
            std::cin >> change;
        }while(change<0 or change>1);

        if (change == 1){
            std::cin.ignore();
            EducationalInstitution institution = EducationalInstitution::create();
            auto mesto = std::lower_bound(new_all.begin(), new_all.end(), institution,
                            [](const EducationalInstitution &a, const EducationalInstitution &b){ return a.get_type().size() > b.get_type().size(); });
            new_all.insert(mesto, institution); //условие сортировки не нарушает, про нарушение критерия для перемещения в этот вектор ничего сказано не было
        }
        else{ break; }
    }

    for (const auto &object : new_all){
        std::cout << GREEN;
        object.get_all();
        std::cout << RESET;
    }
}