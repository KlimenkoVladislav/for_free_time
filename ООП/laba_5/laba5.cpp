#include <iostream>
#include <list>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

class File{
private:
    std::string file_name;
    int start;
    int end;
    bool IsFree;
public:
    File(std::string f_name, int s, int e, bool IF)
        : file_name(f_name), start(s), end(e), IsFree(IF) {}
    static File create(std::string file_name, int start, int end, bool IsFree){
        return File(file_name, start, end, IsFree);
    }

    std::string getFileName() const { return file_name; }
    int getStart() const { return start; }
    int getEnd() const { return end; }
    bool getIsFree() const { return IsFree; }
    void changeFileName(std::string new_file_name) { file_name = new_file_name; }
    void changeStart(int new_start) { start = new_start; }
    void changeIsFree(bool IF) { IsFree = IF; }
    void getFile() const {
        std::cout << GREEN << file_name << RESET << std::endl
                  << "Старт: " << start << std::endl
                  << "Конец: " << end << std::endl;
        std::cout << std::endl;
    }
};

class Disk{
private:
    std::list<File> files;
    const int disk_size = 320;
public:
    Disk(){
        File free_spase = File::create("__NONE__", 0, disk_size, true);
        files.push_back(std::move(free_spase));
    }
    static Disk create(){
        return Disk();
    }

    void CreateFile(){
        std::string file_name;
        int file_size;
        do{
            std::cout << "Введите название файла: ";
            std::getline(std::cin, file_name);
            for (const auto file : files){
                if (file_name == file.getFileName() or file_name == "__NONE__"){
                    std::cout << RED << "Это имя уже присвоену одному из файлов\n" << RESET;
                    file_name.clear();
                }
            }
        }while(file_name.length() == 0);
        do{
            std::cout << "Введите размер файла в Кбайтах: ";
            std::cin >> file_size;
        }while(file_size<18 or file_size>32);

        int start = -1;
        int min_free_space = __INT_MAX__;
        for (const auto file : files){
            if (file.getIsFree() and (file.getEnd()-file.getStart() >= file_size) and (file.getEnd()-file.getStart() < min_free_space)){
                min_free_space = file.getEnd()-file.getStart();
                start = file.getStart();
            }
        }
        if (start == -1){
            std::cout << "Мест нет\n";
            return;
        }

        int end = start + file_size;
        for (int i = 0; i<files.size(); i++){
            auto it = files.begin();
            std::advance(it, i);
            if (it->getStart() == start){
                it->changeStart(start + file_size);
                File new_file = File::create(file_name, start, end, false);
                files.emplace(it, std::move(new_file));
                if (it->getEnd() - it->getStart() == 0){
                    files.erase(it);
                }
                break;
            }
        }
    }

    void DeleteFile(){
        std::string file_name_for_delete;
        std::cout << "Имена всех файлов: \n";
        for (const auto file : files){
            if (file.getFileName() != "__NONE__"){
                std::cout << file.getFileName() << std::endl;
            }
        }
        do{
            std::cout << "Выберите файл: ";
            std::getline(std::cin, file_name_for_delete);
        }while(file_name_for_delete.length() == 0 and file_name_for_delete != "__NONE__");
        
        for (int i = 0; i<files.size(); i++){
            auto it = files.begin();
            std::advance(it, i);
            if (file_name_for_delete == it->getFileName()){
                it->changeIsFree(true);
                it->changeFileName("__NONE__");
                break;
            }
            if (i == files.size()-1){
                std::cout << RED << "Файла с таким именем не обнаружено\n" << RESET;
                return;
            }
        }

        Merge();
    }

    void Merge(){
        for (int i = 0; i<files.size(); i++){
            if (i != files.size()-1){
                auto it1 = files.begin();
                std::advance(it1, i);
                auto it2 = std::next(it1);
                if (it1->getIsFree() and it2->getIsFree()){
                    it2->changeStart(it1->getStart());
                    files.erase(it1);
                    return;
                }
            }
        }
    }
};

int main(){
    Disk disk = Disk::create();
    while (true){
        int num;
        do{
            std::cout << "2 - Добавить файл\n"
                      << "1 - Удалить файл\n"
                      << "0 - Выход\n";
            std::cout << "Введите число: ";
            std::cin >> num;
        }while(num<0 or num>2);
        std::cin.ignore();

        if (num == 0){ break; }
        else if (num == 1){ disk.DeleteFile(); }
        else if (num == 2){ disk.CreateFile(); }
    }
}