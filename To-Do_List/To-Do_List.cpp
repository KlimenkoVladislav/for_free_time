#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

typedef std::string Str;

struct task{
    int task_num;

    Str task_text;
    int task_dif;
    int task_end_day;
    int task_end_month;
    int task_end_year;
    int important;

    task *next;
};

void add(task *last, int day_today, int month_today, int year_today, int kol_task);
task *delete_task(task *begin, int kol_task);
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

        if (num == 0){
            while (begin){
                task *mem_del = begin->next;
                delete[] begin;
                begin = mem_del;
            }
            break;
        }
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
            add(last, day_today, month_today, year_today, kol_task);
        }
        else if (num == 2){
            kol_task--;
            begin = delete_task(begin, kol_task);
        }
        else if (num == 3){
            show_all(begin);
        }
    }
}

void add(task *last, int day_today, int month_today, int year_today, int kol_task){
    last->next = nullptr;

    last->task_num = kol_task;

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

    float from_today_to_end = last->task_end_year*365 + last->task_end_month*30.5 + last->task_end_day - year_today*365 - month_today*30.5 - day_today;
    if (from_today_to_end>30.0){last->important = 0 + last->task_dif;}
    else if (from_today_to_end>20.0 and from_today_to_end<=30.0){last->important = 1 + last->task_dif;}
    else if (from_today_to_end>15.0 and from_today_to_end<=20.0){last->important = 2 + last->task_dif;}
    else if (from_today_to_end>7.0 and from_today_to_end<=15.0){last->important = 3 + last->task_dif;}
    else if (from_today_to_end>2.0 and from_today_to_end<=7.0){last->important = 4 + last->task_dif;}
    else if (from_today_to_end<=2.0){last->important = 5 + last->task_dif;}
}

task *delete_task(task *begin, int kol_task){
    if (begin == nullptr){
        std::cout << "Удалять нечего" << "\n";
        return nullptr;
    }

    int num_delete_task;
    do{
        std::cout << "Введите номер задания, которы вы хотите удалить: ";
        std::cin >> num_delete_task;
    }while(num_delete_task<0 or num_delete_task>kol_task+1);
    
    task *you_here = begin;
    bool change_all_next_num = false;
    while (you_here->next == nullptr or kol_task == 0){
        if (change_all_next_num == true){
            (you_here->task_num)--;
        }
        if (begin->task_num == num_delete_task){
            change_all_next_num = true;
            if (begin->next == nullptr){
                break;
            }
            begin = begin->next;
            you_here->next = nullptr;
            you_here = begin;
            continue;
        }
        else if ((change_all_next_num == false) and (you_here->next!=nullptr) and (you_here->next->task_num == num_delete_task)){
            if (you_here->next->next == nullptr){
                you_here->next = nullptr;
            }
            else{
                you_here->next = you_here->next->next;
                you_here->next->next = nullptr;
            }
            change_all_next_num = true;
        }
        you_here = you_here->next;
    }

    return begin;
}

void show_all(task *prohodka){
    if (prohodka == nullptr){
        std::cout << "Задач нет\n";
        return;
    }
    std::cout << "________________________________________\n";
    while (prohodka){
        std::cout << "\nНомер задания: " << prohodka->task_num << "\n" 
                  << "Задание: " << prohodka->task_text << "\n"
                  << "Выполнить до: " << prohodka->task_end_day << "." << prohodka->task_end_month << "." << prohodka->task_end_year << "\n"
                  << "Сложность задания (от 1 до 5): " << prohodka->task_dif << "\n"
                  << "Срочность (в зависимости от сложности): " << prohodka->important << "\n";

        prohodka = prohodka->next;
    }
    std::cout << "________________________________________\n";
}