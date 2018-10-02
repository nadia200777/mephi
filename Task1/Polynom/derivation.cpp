#include <iostream>
#include <map>

#include "derivation.h"

using namespace std;

std::string derivation(std::string poly)
{
        string s = poly;
        s = s + '+';     		// для верной обработки последнего слагаемого полинома
        string koef = "";
        string step = "";
        int a=0; int b=0;
        bool flag_step = false;
        bool fl_b = false;     
        bool fl_x = false;
        map <int, int> element;

        if (s[0]=='-')
            koef = '-';
        if (s[0]=='+' || s[0]=='-')
            s = s.substr(1);      //отрезать знак спереди, учтя его в коэффициенте
        for (auto i = s.begin(); i != s.end(); ++i)     // цикл по каждому элементу исходного полинома
        {
            if (*i=='+' || *i=='-')			// если текущий элемент знак, то надо степень и коэффициент перед степенью занести в map
            {
                koef = *i;
                if (!fl_x) continue;
                if (fl_x && !flag_step) step="1";
                fl_x=false;
                flag_step = false;
                b = stoi(step);
                step = "";
                for (auto j = element.begin(); j != element.end(); j++)    // цикл по MAP, вносящий значение ПРОИЗВОДНОЙ 
                {														// элемента с учётом возможных одинаковых степеней у Х
                    if (j->first == (b-1))
                    {
                        j->second += a*b;
                        fl_b = true;
                    }
                }
                if (!fl_b)				// Как только работа со степенью закончена, значит текущее слагаемое полинома кончилось и мы сохраняем его в MAP
                    element.insert(pair <int,int>(b-1,a*b));
                fl_b = false;
                continue;
            }
            if (*i=='x')			// Если мы добрались до Х то нужно сохранить коэффициент перед ним
                {
                    fl_x=true;
                    if (koef == "-" || koef == "+" || koef == "")
                        koef += '1';
                    a = stoi(koef);
                }
            if (isdigit(*i) && !(flag_step))    // Если текущий элемент цифра и мы не в степени - дополняет коэффициент
                    koef += *i;
            if (isdigit(*i) && flag_step)		// Если текущий элемент цифра и мы в степени - дополняем степень
                    step += *i;
            if (*i == '^')						// Определение, когда мы переходим к степени
                flag_step = true;

        }
        string result = "";
        for (auto j = element.begin(); j != element.end(); j++) 		// Вывод в порядке убывания степеней и с учётом особых случаев
        {
            if (j->second == 0 ) continue;
            if (j->first == 0)
                {
                    result = to_string(j->second) + result;
                    if (j->second > 0) result = "+" + result;
                    continue;
                }
            if (j->first == 1)	result = "x" + result;
            if (j->first > 1) result = "x^" + to_string(j->first) + result;
            if (j->second == -1) result = "-" + result;
            if (abs(j->second)>1) result = to_string(j->second) + "*" +result;
            if (j->second > 0) result = "+" + result;

        }
        if (result[0] == '+') result = result.substr(1);
        if (result == "") result = "0";

        return result;
}
