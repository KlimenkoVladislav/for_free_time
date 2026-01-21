#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <algorithm>

#define GREEN "\033[32m"
#define RESET "\033[0m"

class TicketsSales{
private:
    std::string _country;
    std::vector<int> _sold;
    int _total_revenue;
public:
    TicketsSales(std::string country, std::vector<int> sold, int total_revenue)
        : _country(country), _sold(sold), _total_revenue(total_revenue) {}

    static TicketsSales create(const std::string &stroka){
        std::string _country;
        std::vector<int> _sold(7);

        std::stringstream ss(stroka);
        if (!(ss >> _country >> _sold[0] >> _sold[1] >> _sold[2] >> _sold[3] >> _sold[4] >> _sold[5] >> _sold[6])){
            throw std::invalid_argument("Неправильная строка!\n");
        }

        for (int num : _sold){
            if (num < 0){
                throw std::invalid_argument("Отрицательное значение в строке\n");
            }
        }

        int _total_revenue = _sold[0] * (_sold[1] + _sold[2] + _sold[3] + _sold[4] + _sold[5] + _sold[6]);

        return TicketsSales(_country, _sold, _total_revenue);
    }

    std::string getCountry() const { return _country; }
    int getTicketCost() const { return _sold[0]; }
    int getAprilSold() const { return _sold[1]; }
    int getMaySold() const { return _sold[2]; }
    int getJuneSold() const { return _sold[3]; }
    int getJulySold() const { return _sold[4]; }
    int getAugustSold() const { return _sold[5]; }
    int getSeptemberSold() const { return _sold[6]; }
    int getTotalRevenue() const { return _total_revenue; }
    int getSumTickets() const { return _sold[1]+_sold[2]+_sold[3]+_sold[4]+_sold[5]+_sold[6]; }
};

void FromTxtToBin(){
    std::ifstream txtfile("for_laba3.txt");
    std::fstream binfile("for_laba3.bin", std::ios::binary | std::ios::out);
    if (!txtfile.is_open() or !binfile.is_open()){
        throw std::runtime_error("Один из файлов не открылся");
    }

    std::string stroka;
    while (std::getline(txtfile, stroka)){
        size_t len = stroka.size();
        binfile.write(reinterpret_cast<const char*> (&len), sizeof(len));
        binfile.write(stroka.c_str(), len);
    }

    txtfile.close();
    binfile.close();
}

std::vector<TicketsSales> FromBinToClass(){
    std::fstream binfile("for_laba3.bin", std::ios::binary | std::ios::in);
    if (!binfile.is_open()){
        throw std::runtime_error("Бинарный файл не открылся");
    }

    std::vector<TicketsSales> all;

    while (binfile.peek() != EOF){
        size_t len;
        if (!binfile.read(reinterpret_cast<char*> (&len), sizeof(size_t))){
            if (binfile.eof()){ break; }
            throw std::runtime_error("Не прочиталась длина строки");
        }
        
        std::string stroka(len, '\0');
        if (!binfile.read(&stroka[0], len)){
            throw std::runtime_error("Не прочиталась строка");
        }

        TicketsSales for_one_country = TicketsSales::create(stroka);
        all.push_back(std::move(for_one_country));
    }

    binfile.close();
    return all;
}

int main(){
    FromTxtToBin();
    std::vector<TicketsSales> all = FromBinToClass();
    if (all.size() == 0){
        std::cout << "Строк в файле не было\n";
        return 0;
    }

    std::sort(all.begin(), all.end(), 
        [](const TicketsSales &a, const TicketsSales &b){ return a.getSumTickets() > b.getSumTickets(); });
    
        for (int i = 0; i<3 and i!=all.size(); i++){
        std::cout << GREEN << "топ " << i+1 << " страна:" << all[i].getCountry() << RESET << std::endl
                  << "продано билетов за апрель: " << all[i].getAprilSold() << std::endl
                  << "продано билетов за май: " << all[i].getMaySold() << std::endl
                  << "продано билетов за июнь: " << all[i].getJuneSold() << std::endl
                  << "продано билетов за июль: " << all[i].getJulySold() << std::endl
                  << "продано билетов за август: " << all[i].getAugustSold() << std::endl
                  << "продано билетов за сентябрь: " << all[i].getSeptemberSold() << std::endl
                  << "продано всего билетов: " << all[i].getSumTickets() << std::endl
                  << "билетов продано на сумму: " << all[i].getTotalRevenue() << std::endl;
    }
}