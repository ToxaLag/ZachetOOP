#include <iostream>
using namespace std;

class Matrica 
{
    int stroka, stolbez;
    double **mas;
public:
    Matrica(int stroka_, int stolbez_, int chislo = 0); //конструктор
    Matrica(const Matrica& ob); //конструктор коппий
    ~Matrica()
    {
        for (int i = 0; i < stroka; ++i)
            delete[] mas[i];
        delete[] mas;
        cout << "Деструктор;" <<endl;
    } //деструктор*/
    friend ostream& operator << (ostream& str, Matrica& ob);
    friend istream& operator >> (istream& str, Matrica& ob);
    Matrica operator+(Matrica r_ob)
    {
        //сравнение размерности матриц //начало
        if ((this->stroka != r_ob.stroka) || (this->stolbez != r_ob.stolbez))
        {   
            cout << "Ошибка: различная размерность матриц" <<endl;
            return *this;
        }
        //сравнение размерности матриц //конец
        Matrica tmp(r_ob.stroka, r_ob.stolbez, 0);
        for (int i = 0; i < r_ob.stroka; i++)
        {
            for (int j = 0; j < r_ob.stolbez; j++)
            {
                tmp.mas[i][j] = this->mas[i][j] + r_ob.mas[i][j];
            }
        }
        return tmp;
    }
    Matrica operator-(Matrica r_ob)
    {
        //сравнение размерности матриц //начало
        if ((this->stroka != r_ob.stroka) || (this->stolbez != r_ob.stolbez))
        {
            cout << "Ошибка: различная размерность матриц" << endl;
            return *this;
        }
        //сравнение размерности матриц //конец
        Matrica tmp(r_ob.stroka, r_ob.stolbez, 0);
        for (int i = 0; i < r_ob.stroka; i++)
        {
            for (int j = 0; j < r_ob.stolbez; j++)
            {
                tmp.mas[i][j] = this->mas[i][j] - r_ob.mas[i][j];
            }
        }
        return tmp;
    }
    Matrica operator=(Matrica r_ob)
    {
        for (int i = 0; i < r_ob.stroka; i++)
            for (int j = 0; j < r_ob.stolbez; j++)
                this->mas[i][j] = r_ob.mas[i][j];
        return *this;
    }
    Matrica operator*(Matrica r_ob) // умножение матрицы на матрицу
    {
        if (this->stroka != r_ob.stolbez)
        {
            cout << "Ошибка: различная размерность матриц" << endl;
            return *this;
        }
        Matrica tmp(this->stroka, r_ob.stolbez, 0);
        for (int i = 0; i < this->stroka; i++)
            for (int j = 0; j < r_ob.stolbez; j++)
                for (int k = 0; k < this->stolbez; k++)
                    tmp.mas[i][j] += this->mas[i][k] * r_ob.mas[k][j];
        return tmp;
    }  // умножение матрицы на матрицу конец;
    Matrica operator*(double r_ob)
    {
        Matrica tmp(this->stroka, this->stolbez, 0);
        for (int i = 0; i < tmp.stroka; i++)
            for (int j = 0; j < tmp.stolbez; j++)
                tmp.mas[i][j] = this->mas[i][j] * r_ob;
        return tmp;
    }
    bool operator==(Matrica& r_ob) 
    {
        if ((this->stroka == r_ob.stroka) && (this->stolbez == r_ob.stolbez))
        {
            for (int i = 0; i < this->stroka; i++)
                for(int j = 0; j < this->stolbez; j++)
                    if (this->mas[i][j] == r_ob.mas[i][j])
                        return true;
        }
        return false;
    }
};

int main()
{
    setlocale(LC_ALL, "Rus");
    Matrica a(3, 3);
    Matrica b(3, 3);
    cin >> a >>b;
    cout << a <<b;
}

Matrica::Matrica(int stroka_, int stolbez_, int chislo)  // конструктор *начало
{
    try
    {
        if ((stroka_ < 1) || (stolbez_ < 1))
            throw (-5);
    }  // проверка на првильность значений строк/столбцов (отсев нулевых и отриц)
    catch (int n)
    {
        cout << "Некеррокетная размерность массива";
    }
    try
    {
        stroka = stroka_; stolbez = stolbez_;
        mas = new double* [stroka];
        for (int i = 0; i < stroka; i++)
            mas[i] = new double[stolbez];
        for (int i = 0; i < stroka; i++)
        {
            for (int j = 0; j < stolbez; j++)
                mas[i][j] = chislo;
        }
    }   // проверка выделения памяти
    catch (bad_alloc)
    {
        cout << "Ошибка выделения памяти...";
    }
}                                                       // конструктор *конец

Matrica::Matrica(const Matrica& ob)
{
    stroka = ob.stroka; stolbez = ob.stolbez;
    mas = new double* [stroka];
    for (int i = 0; i < stroka; i++)
        mas[i] = new double[stolbez];
    for (int i = 0; i < stroka; i++)
        for (int j = 0; j < stolbez; j++)
            mas[i][j] = ob.mas[i][j];
}

ostream& operator << (ostream& str, Matrica& ob)
{
    for (int i = 0; i < ob.stroka; i++)
    {
        for (int j = 0; j < ob.stolbez; j++)
            str << ob.mas[i][j] << " ";
        str << endl;
    }
    str << endl;
    return str;
}

istream& operator >> (istream& str, Matrica& ob)
{
    for (int i = 0; i < ob.stroka; i++)
    {
        for (int j = 0; j < ob.stolbez; j++)
        {
            cout << "Введите[" <<i+1 <<"][" <<j+1 << "] - ый элемент матрицы ";
            str >> ob.mas[i][j];
        }
    }
    return str;
}
