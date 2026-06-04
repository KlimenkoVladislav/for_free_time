#include <iostream>
#include <stack>

void createStack(std::stack<float> &numbers){
    int kol_num;
    std::cout << "Сколько чисел вы хотите добавить в стек: ";
    std::cin >> kol_num;
    float num;
    for (int i = 0; i < kol_num; i++){
        std::cin >> num;
        numbers.push(num);
    }
}

void printStack(std::stack<float> numbers){
    while (!numbers.empty()){ std::cout << numbers.top() << " "; numbers.pop(); }
    std::cout << "\n";
}

void createNewStack(std::stack<float> &new_stack, std::stack<float> &numbers){
    int num;
    std::cout << "Введите число, относительно которого будет производиться поиск: ";
    std::cin >> num;

    while (!numbers.empty()){
        if (numbers.top() > num){
            new_stack.push(numbers.top());
        }
        numbers.pop();
    }
}

int main(){
    std::stack<float> numbers;
    createStack(numbers);
    printStack(numbers);
    
    std::stack<float> new_stack;
    createNewStack(new_stack, numbers);
    if (!new_stack.empty()){ printStack(new_stack); }
    else { std::cout << "Чисел, больше введённого нет\n"; }
}