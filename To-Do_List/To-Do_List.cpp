#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

typedef std::string Str;

struct task{
    Str task_text;
    int task_dif;
    int task_end_day;
    int task_end_month;
    int task_end_year;
    int important;
    task *next;
};

void add(task *last, int day_today, int month_today, int year_today);
void show_all(task *prohodka);

int main(){
    task *begin = nullptr;
    task *last = nullptr;
    int kol_task = 0;
    int day_today, month_today, year_today;

    Str date_today;
    while (true){
        std::cout << "Введите сегодняшнюю дату (дд.мм.гггг): ";
        std::getline(std::cin, date_today);
        if (date_today.size() == 10){
            std::replace(date_today.begin(), date_today.end(), '.', ' ');
            std::stringstream ss(date_today);
            if (ss.fail()){
                std::cout << "Ошибка преобразования\n";
                continue;
            }
            ss >> day_today >> month_today >> year_today;
            if (day_today>0 and day_today<32 and month_today>0 and month_today<13){
                break;
            }
        }
    }

    while (true){
        std::cout << "\nВыберите действие:\n"
                << "1 - Добавить задачу\n"
                << "2 - Удалить задачу\n"
                << "3 - Показать все задачи\n"
                << "4 - Найти срочные задачи\n"
                << "5 - Очистить список\n"
                << "6 - Вывести количество задач\n"
                << "0 - Выход\n";
        
        int num;
        do{
            std::cout << "Введите номер действия: ";
            std::cin >> num;
        }while (num<0 or num>5);

        if (num == 0){break;}
        else if (num == 1){
            if (kol_task == 0){
                begin = new task;
                last = begin;
            }
            else{
                last->next = new task;
                last = last->next;
            }
            kol_task++;
            add(last, day_today, month_today, year_today);
        }
        else if (num == 3){
            kol_task++;
            show_all(begin);
        }
    }
}

void add(task *last, int day_today, int month_today, int year_today){
    last->next = nullptr;

    std::cout << "\nВведите задачу: \n";
    std::cin.ignore();
    std::getline(std::cin, last->task_text);

    int dif;
    std::cout << "\nВыберите сложность задачи:\n"
              << "1 - очень легко\n"
              << "2 - легко\n"
              << "3 - средне\n"
              << "4 - сложно\n"
              << "5 - крайне сложно\n";
    do{
        std::cout << "Введите сложность задачи цифрой: ";
        std::cin >> dif;
    }while(dif<0 or dif>5);
    last->task_dif = dif;

    Str date;
    std::cin.ignore();
    while (true){
        std::cout << "\nВведите дату, к которой нужно выполнить задачу (дд.мм.гггг): ";
        std::getline(std::cin, date);
        if (date.size() == 10){
            std::replace(date.begin(), date.end(), '.', ' ');
            std::stringstream ss(date);
            if (ss.fail()){
                std::cout << "Ошибка преобразования\n";
                continue;
            }
            ss >> last->task_end_day >> last->task_end_month >> last->task_end_year;
            if (last->task_end_day>0 and last->task_end_day<32 and last->task_end_month>0 and last->task_end_month<13){
                break;
            }
        }
    }

    int from_today_to_end = last->task_end_year*365 + last->task_end_month*31 + last->task_end_day - year_today*365 - month_today*31 - day_today;
    if (from_today_to_end>30){last->important = 0 + last->task_dif;}
    else if (from_today_to_end>20 and from_today_to_end<=29){last->important = 1 + last->task_dif;}
    else if (from_today_to_end>15 and from_today_to_end<=19){last->important = 2 + last->task_dif;}
    else if (from_today_to_end>7 and from_today_to_end<=14){last->important = 3 + last->task_dif;}
    else if (from_today_to_end>2 and from_today_to_end<=6){last->important = 4 + last->task_dif;}
    else if (from_today_to_end<=2){last->important = 5 + last->task_dif;}
}

void show_all(task *prohodka){
    while (prohodka){
        std::cout << "\nЗадание: " << prohodka->task_text << "\n"
                  << "Выполнить до: " << prohodka->task_end_day << "." << prohodka->task_end_month << "." << prohodka->task_end_year << "\n"
                  << "Сложность задания (от 1 до 5): " << prohodka->task_dif << "\n"
                  << "Срочность (в зависимости от сложности): " << prohodka->important << "\n";

        prohodka = prohodka->next;
    }
}