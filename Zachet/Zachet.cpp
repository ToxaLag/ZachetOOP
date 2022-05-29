#include <iostream>
using namespace std;

class Matrica 
{
    int stroka, stolbez,rang;
    double deter;
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
        tmp.DeterGaus();
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
        tmp.DeterGaus();
        return tmp;
    }
    Matrica operator=(const Matrica& r_ob)
    {
        for (int i = 0; i < stroka; ++i)
            delete[] mas[i];
        delete[] mas;
        this->stroka = r_ob.stroka; this->stolbez = r_ob.stolbez; this->deter = r_ob.deter; this->rang = r_ob.rang;
        mas = new double* [stroka];
        for (int i = 0; i < stroka; i++)
            mas[i] = new double[stolbez];
        for (int i = 0; i < stroka; i++)
        {
            for (int j = 0; j < stolbez; j++)
                mas[i][j] = r_ob.mas[i][j];
        }
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
        tmp.DeterGaus();
        return tmp;
    }  // умножение матрицы на матрицу конец;
    Matrica operator*(double r_ob)
    {
        Matrica tmp(this->stroka, this->stolbez, 0);
        for (int i = 0; i < tmp.stroka; i++)
            for (int j = 0; j < tmp.stolbez; j++)
                tmp.mas[i][j] = this->mas[i][j] * r_ob;
        tmp.DeterGaus();
        return tmp;
    }
    double operator()(int stroka_ , int stolbez_);
    friend Matrica operator*(double l_ob, Matrica r_ob);
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
    double MaxOf()
    {
        double max;
        int stroka_max = 0; int stolbez_max = 0;
        max = mas[0][0];
        for (int i = 0; i < stroka;i++)
            for(int j = 0; j < stolbez;j++)
                if (mas[i][j] > max)
                {
                    max = mas[i][j];
                    stroka_max = i; stolbez_max = j;
                }
        cout << "Максимальный элемент [" << stroka_max + 1 << "][" << stolbez_max + 1 << "] = " << max << endl;
        return max;
    };
    double MinOf()
    {
        double min;
        int stroka_max = 0; int stolbez_max = 0;
        min = mas[0][0];
        for (int i = 0; i < stroka; i++)
            for (int j = 0; j < stolbez; j++)
                if (mas[i][j] > min)
                {
                    min = mas[i][j];
                    stroka_max = i; stolbez_max = j;
                }
        cout << "Максимальный элемент [" << stroka_max + 1 << "][" << stolbez_max + 1 << "] = " << min << endl;
        return min;
    };
    Matrica Tranpon(bool p = false) //Метод транспонирования
    {
        /*Если параметр false, то матрица транспонируется;
        Если true, то матрица передаётся */
        if (p)
        {
            Matrica tmp(stroka,stolbez);
            for (int i = 0; i<stroka;i++)
                for (int j = 0; j < stolbez; j++)
                        tmp.mas[i][j] = mas[j][i];
            return tmp;
        }
        double el;
        for (int i = 0; i < stroka; i++)
            for (int j = i+1; j < stolbez; j++)
                {
                    el = mas[i][j];
                    mas[i][j] = mas[j][i];
                    mas[j][i] = el;
                }
        return *this;
    }
    double GetDeter()
    {
        DeterGaus();
        return deter;
    }
    Matrica Revers()
    {
        if ((stroka != stolbez) || (deter == 0))
        {
            cout << "Нет обратной матрицы";
            return *this;
        }
    }
    Matrica SwapStr(int stroka1, int stroka2)
    {
        double chislo;
        for (int j = 0; j < stolbez; j++)
        {
            chislo = mas[stroka1-1][j];
            mas[stroka1-1][j] = mas[stroka2-1][j];
            mas[stroka2-1][j] = chislo;
        }
        return *this;
    }
    Matrica SwapStl(int stolbez1, int stolbez2)
    {
        double chislo;
        for (int i = 0; i < stroka; i++)
        {
            chislo = mas[stolbez1-1][i];
            mas[stolbez1-1][i] = mas[stolbez2-1][i];
            mas[stolbez2-1][i] = chislo;
        }
        return *this;
    }
    double DeterGaus()
    {
        if (stroka != stolbez)
        {
            deter = 999333;
            return deter;
        }
        deter = 1;
        Matrica tmp(stroka, stroka);
        tmp = *this;
        double ches;
        //проверка на нулевые стоки/столбцы
        for (int i = 0; i < stroka; i++)
        {
            for (int j = 0; j < stroka; j++)
            {
                if (tmp.mas[i][j] != 0 || tmp.mas[j][i] != 0)
                    break;
                if ((j == stroka - 1) && (tmp.mas[i][j] == 0))
                {
                    deter = 0;
                    return deter;
                }
            }
        }
        //конец проверки
        //проверка на ненулевые элементы на глав диагонали + замена если возможно
        int notNullMain = 1;
        for (int i = 0; i < stroka; i++)
        {
            while (tmp.mas[i][i] == 0)
            {
                tmp.SwapStl(i, notNullMain);
                notNullMain++;
            }
        }
        //конец проверки
        for (int k = 0; k < stroka; k++)
            for (int i = k + 1; i < stroka; i++)
            {
                ches = -tmp.mas[i][k] / tmp.mas[k][k];
                for (int j = 0; j < stroka; j++)
                    tmp.mas[i][j] += tmp.mas[k][j] * ches;
            }
        for (int i = 0; i < stroka; i++)
            deter *= tmp.mas[i][i];
        return deter;
    }
    //int Rang()
    //{
    //    rang = min(stroka, stolbez);
    //    for (int i = 0; i < stroka; ++i)
    //    {
    //        for (int j = 0; j < stolbez; ++j)
    //            return 0; //дописать
    //    }
    //}

};

int main()
{
    setlocale(LC_ALL, "Rus");
    Matrica a(3, 3, 5);
    Matrica b(3, 3, 4);
    cin >> b;
    cout << b.GetDeter();

}

Matrica::Matrica(int stroka_, int stolbez_, int chislo)  // конструктор *начало
{
    while ((stroka_ < 1) || (stolbez_ < 1)) // проверка на првильность значений строк/столбцов (отсев нулевых и отриц)
    {
        cout << "Некеррокетная размерность массива" << endl << "Введите число строк и столбцов";
        cin >> stroka_, stolbez_;
    }
    try
    {
        stroka = stroka_; stolbez = stolbez_;
        mas = new double* [stroka];
        for (int i = 0; i < stroka; i++)
            mas[i] = new double[stolbez];
        
    }   // проверка выделения памяти
    catch (bad_alloc)
    {
        cout << "Ошибка выделения памяти...";
    }
    for (int i = 0; i < stroka; i++)
        for (int j = 0; j < stolbez; j++)
            mas[i][j] = chislo;
    deter = 0;
    rang = 1;
}                                                       // конструктор *конец

Matrica::Matrica(const Matrica& ob)
{
    stroka = ob.stroka; stolbez = ob.stolbez; deter = ob.deter; rang = ob.rang;
    mas = new double* [stroka];
    for (int i = 0; i < stroka; i++)
        mas[i] = new double[stolbez];
    for (int i = 0; i < stroka; i++)
        for (int j = 0; j < stolbez; j++)
            mas[i][j] = ob.mas[i][j];
}

double Matrica::operator()(int stroka_, int stolbez_)
{
    if ((stroka_ < 1) || (stolbez_ < 1) || (stroka_ > stroka) || (stolbez_ > stolbez))
        cout << "Out of range" << endl;
    return mas[stroka_-1][stolbez_-1];
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
    ob.DeterGaus();
    return str;
}

Matrica operator*(double l_ob, Matrica r_ob)
{
    Matrica tmp(r_ob.stroka, r_ob.stolbez);
    for (int i = 0; i < tmp.stroka; i++)
        for (int j = 0; j < tmp.stolbez; j++)
            tmp.mas[i][j] = r_ob.mas[i][j] * l_ob;
    return tmp;
}
