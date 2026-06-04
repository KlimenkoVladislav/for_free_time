#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>

class Human{
private:
    std::string _surname;
    std::string _name;
    std::string _znak_zodiaka;
    std::vector<int> _birth_date;
public:
    Human(std::string surname, std::string name, std::string znak_zodiaka, std::vector<int> birth_date)
          : _surname(surname), _name(name), _znak_zodiaka(znak_zodiaka), _birth_date(birth_date) {}
    
    static Human create(std::queue<std::string> &line){
        std::string surname = line.front(); line.pop();
        std::string name = line.front(); line.pop();
        std::string znak_zodiaka = line.front(); line.pop();
        std::vector<int> birth_date;
        for (int i = 0; i<3; i++){
            birth_date.push_back(std::stoi(line.front()));
            line.pop();
        }

        return Human(surname, name, znak_zodiaka, birth_date);
    }

    std::string getSurname() const { return _surname; }
    std::string getName() const { return _name; }
    std::string getZnakZodiaka() const { return _znak_zodiaka; }
    std::vector<int> getBirthDate() const { return _birth_date; }
};

void createQueue(std::queue<Human> &Humans){
    std::ifstream file("test_data.txt");
    if (!file.is_open()){
        std::cout << "Не удалось открыть файл\n";
        return;
    }

    std::queue<std::string> line;
    int count_elem_in_q = 0;
    std::string word;
    while(file >> word){
        line.push(word);
        count_elem_in_q++;
        if (count_elem_in_q == 6){
            Human human = Human::create(line);
            Humans.push(human);
            while (!line.empty()){ line.pop(); }
            count_elem_in_q = 0;
        }
    }

    file.close();
}

void printQueue(std::queue<Human> Humans, int count_humans){
    std::cout << "\n";
    for (int i = 0; i < count_humans; i++){
        std::cout << "Человек по счёту " << i+1 << std::endl;
        std::cout << "Фамилия: " << Humans.front().getSurname() << std::endl
                  << "Имя: " << Humans.front().getName() << std::endl
                  << "Знак зодиака: " << Humans.front().getZnakZodiaka() << std::endl
                  << "Дата рождения: " << Humans.front().getBirthDate()[0] << "."
                                       << Humans.front().getBirthDate()[1] << "."
                                       << Humans.front().getBirthDate()[2] << std::endl << std::endl;
        Humans.pop();
    }
}

void createNewQueue(std::queue<Human> &new_q_Humans, std::queue<Human> &Humans, const std::string query_zz){
    while (!Humans.empty()){
        if (Humans.front().getZnakZodiaka() == query_zz){
            new_q_Humans.push(Humans.front());
        }
        Humans.pop();
    }
}

int main(){
    std::queue<Human> Humans;
    createQueue(Humans);
    printQueue(Humans, Humans.size());

    std::string query_zz;
    std::cout << "Введите знак зодиака, по которому будем искать: ";
    std::getline(std::cin, query_zz);
    std::queue<Human> new_q_Humans;
    createNewQueue(new_q_Humans, Humans, query_zz);
    if (!new_q_Humans.empty()){ printQueue(new_q_Humans, new_q_Humans.size()); }
    else { std::cout << "Людей с таким знаком зодиака нет\n"; }
}