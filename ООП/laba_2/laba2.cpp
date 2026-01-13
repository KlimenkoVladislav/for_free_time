#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

#define RED   "\033[31m"
#define RESET "\033[0m"

typedef std::vector<std::vector<float>> v_v_float;

class ForCreateClass{
public:
    static void sort_points(v_v_float &quadrilateral){
        v_v_float up_down = quadrilateral;
        quadrilateral.clear();

        std::sort(up_down.begin(), up_down.end(),
            [](const std::vector<float> &A, const std::vector<float> &B){
                return A[1] < B[1];
            });
        
        if (up_down[0][0] < up_down[1][0]){
            quadrilateral.push_back(up_down[0]);
            quadrilateral.push_back(up_down[1]);
        }
        else{
            quadrilateral.push_back(up_down[1]);
            quadrilateral.push_back(up_down[0]);
        }

        if (up_down[2][0] < up_down[3][0]){
            quadrilateral.push_back(up_down[3]);
            quadrilateral.push_back(up_down[2]);
        }
        else{
            quadrilateral.push_back(up_down[2]);
            quadrilateral.push_back(up_down[3]);
        }
    }

    static std::vector<float> len_sides(v_v_float &quadrilateral){
        std::vector<float> len_side;

        for (int i = 0; i<4; i++){
            if (i == 3){
                len_side.push_back(sqrt(pow(quadrilateral[0][0]-quadrilateral[i][0], 2) + pow(quadrilateral[0][1]-quadrilateral[i][1], 2)));
            }
            else{
                len_side.push_back(sqrt(pow(quadrilateral[i+1][0]-quadrilateral[i][0], 2) + pow(quadrilateral[i+1][1]-quadrilateral[i][1], 2)));
            }
        }

        return len_side;
    }
};

class Quadrilateral{
protected:
    v_v_float quadrilateral;
    std::vector<float> len_side;

public:
    Quadrilateral(v_v_float q, std::vector<float> l_s) 
        : quadrilateral(q), len_side(l_s) {}
    
    static Quadrilateral create(){
        v_v_float quadrilateral;
        std::string stroka_chisel;

        while (true){
            std::cout << "Введите через пробел 8 координат (4х точек): ";
            std::getline(std::cin, stroka_chisel);

            std::stringstream ss(stroka_chisel);
            std::vector<float> dot;
            quadrilateral.push_back(dot);
            float num;

            while (ss >> num){
                if (quadrilateral.back().size() == 2){
                    quadrilateral.push_back(dot);
                }
                quadrilateral.back().push_back(num);
            }

            if (quadrilateral.size() != 4 or quadrilateral.back().size() != 2){
                std::cout << "Введено неправильно количество координат\n";
                continue;
            }
            break;
        }

        ForCreateClass::sort_points(quadrilateral);
        std::vector<float> len_side = ForCreateClass::len_sides(quadrilateral);

        return Quadrilateral(quadrilateral, len_side);
    }

    void getPerimetr() const {
        int p = 0;
        for (float num : len_side){
            p += num;
        }
        std::cout << "Периметр = " << p << std::endl;
    }

    void getArea() const {
        //надо сначала запрогать матрицу поворота и интегралы
    }

    virtual void getInfo() const {
        std::cout << "\nКоординаты углов четырёхугольника:\n";
        for (int i = 0; i<quadrilateral.size(); i++){
            std::cout << "(" << quadrilateral[i][0] << ";" << quadrilateral[i][1] << ")   ";
        }
        std::cout << std::endl;

        std::cout << "Длины всех сторон:\n";
        for (float num : len_side){
            std::cout << num << "   ";
        }
        std::cout << std::endl;
    }

    virtual ~Quadrilateral(){}
};

class Trapezoid:public Quadrilateral{
protected:
    bool IsThisTrapezoid;
    std::vector<float> diagonali;

public:
    Trapezoid(v_v_float quadrilateral, std::vector<float> len_side, bool ITT, std::vector<float> d) 
        : Quadrilateral(quadrilateral, len_side), IsThisTrapezoid(ITT), diagonali(d) {}

    static Trapezoid create(){
        v_v_float quadrilateral;
        std::string stroka_chisel;

        while (true){
            std::cout << "Введите через пробел 8 координат (4х точек): ";
            std::getline(std::cin, stroka_chisel);

            std::stringstream ss(stroka_chisel);
            std::vector<float> dot;
            quadrilateral.push_back(dot);
            float num;

            while (ss >> num){
                if (quadrilateral.back().size() == 2){
                    quadrilateral.push_back(dot);
                }
                quadrilateral.back().push_back(num);
            }

            if (quadrilateral.size() != 4 or quadrilateral.back().size() != 2){
                std::cout << "Введено неправильно количество координат\n";
                quadrilateral.clear();
                continue;
            }
            break;
        }

        ForCreateClass::sort_points(quadrilateral);
        std::vector<float> len_side = ForCreateClass::len_sides(quadrilateral);

        bool IsThisTrapezoid = false;
        if (abs((((quadrilateral[1][0]-quadrilateral[0][0]) * (quadrilateral[3][0]-quadrilateral[2][0])) + 
                 ((quadrilateral[1][1]-quadrilateral[0][1]) * (quadrilateral[3][1]-quadrilateral[2][1]))) / 
                  (len_side[0] * len_side[2])) == 1 or 
            abs((((quadrilateral[2][0]-quadrilateral[1][0]) * (quadrilateral[0][0]-quadrilateral[3][0])) + 
                 ((quadrilateral[2][1]-quadrilateral[1][1]) * (quadrilateral[0][1]-quadrilateral[3][1]))) / 
                  (len_side[1] * len_side[3])) == 1)
            {
                IsThisTrapezoid = true;
            }

        std::vector<float> diagonali;
        diagonali.push_back(sqrt(pow(quadrilateral[2][0]-quadrilateral[0][0], 2) + pow(quadrilateral[2][1]-quadrilateral[0][1], 2)));
        diagonali.push_back(sqrt(pow(quadrilateral[3][0]-quadrilateral[1][0], 2) + pow(quadrilateral[3][1]-quadrilateral[1][1], 2)));

        return Trapezoid(quadrilateral, len_side, IsThisTrapezoid, diagonali);
    }

    bool getIsThisTrapezoid() const {
        return IsThisTrapezoid;
    }

    std::vector<float> getDiagonali() const {
        return diagonali;
    }

    void getInfo() const override final {
        Quadrilateral::getInfo();
        if (abs((((quadrilateral[1][0]-quadrilateral[0][0]) * (quadrilateral[3][0]-quadrilateral[2][0])) + 
                 ((quadrilateral[1][1]-quadrilateral[0][1]) * (quadrilateral[3][1]-quadrilateral[2][1]))) / 
                  (len_side[0] * len_side[2])) == 1)
        {
            if (len_side[1] == len_side[3]){
                std::cout << "Трапеция равнобокая\n";
            }
            else{
                std::cout << "Трапеция не равнобокая\n";
            }
        }
        else{
            if (len_side[0] == len_side[2]){
                std::cout << "Трапеция равнобокая\n";
            }
            else{
                std::cout << "Трапеция не равнобокая\n";
            }
        }

        std::cout << "Длины диагоналей: " << diagonali[0] << "  " << diagonali[1] << std::endl;
    }
};

int main(){
    int M;
    do{
        std::cout << "Введите количество трапеций: ";
        std::cin >> M;
    }while (M<1);
    std::cin.ignore();

    std::vector<Trapezoid> massiv;
    for (int i = 0; i<M; i++){
        Trapezoid t = Trapezoid::create();
        if (t.getIsThisTrapezoid()){massiv.push_back(t);}
    }

    int kol_min = 0;
    int elem_massiva_with_min_diag;
    float min_diag = 1000000;
    for (int i = 0; i<massiv.size(); i++){
        massiv[i].getInfo();
        for (int j = 0; j<2; j++){
            if (massiv[i].getDiagonali()[j] < min_diag){
                min_diag = massiv[i].getDiagonali()[j];
                elem_massiva_with_min_diag = i;
                kol_min = 1;
            }
            else if (massiv[i].getDiagonali()[j] == min_diag and i!=elem_massiva_with_min_diag){
                elem_massiva_with_min_diag = i;
                kol_min++;
            }
        }
    }

    if (kol_min == 1){
        std::cout << RED << "Трапеция с наименьшей диагональю:" << RESET;
        massiv[elem_massiva_with_min_diag].getInfo();
    }
    else if (kol_min>1){
        std::cout << RED << "Количество трапеций с наименьшей диагональю: " << RESET << kol_min << std::endl;
    }
}