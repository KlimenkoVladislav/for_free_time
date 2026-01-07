#include <iostream>
#include <string>

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

    std::string get_type(){
        return _type;
    }

    std::string get_submission(){
        return _submission;
    }

    void get_all(){
        std::cout << "Тип учреждения: " << _type << "\n"
                  << "Подчинение: " << _submission << "\n";
    }
};

int main(){
    EducationalInstitution institution = EducationalInstitution::create();

    int change;
    while (true){
        do{
            std::cout << "Хотите ли вы что-то изменить в введённых вами данных? 0 - нет, 1 - да: ";
            std::cin >> change;
        }while(change<0 or change>1);
        if (change == 1){
            std::cin.ignore();
            institution.change_info();
        }
        else {break;}

    }

    std::cout << "Тип учреждения: " << institution.get_type() << std::endl;
    std::cout << "Подчинение: " << institution.get_submission() << std::endl;
    std::cout << "\n";
    institution.get_all();
}