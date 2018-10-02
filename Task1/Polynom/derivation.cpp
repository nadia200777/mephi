#include <iostream>
#include <map>

#include "derivation.h"

using namespace std;

std::string derivation(std::string poly)
{
        string s = poly;
        s = s + '+';
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
            s = s.substr(1);
        for (auto i = s.begin(); i != s.end(); ++i)
        {
            if (*i=='+' || *i=='-')
            {
                koef = *i;
                if (!fl_x) continue;
                if (fl_x && !flag_step) step="1";
                fl_x=false;
                flag_step = false;
                b = stoi(step);
                step = "";
                for (auto j = element.begin(); j != element.end(); j++)
                {
                    if (j->first == (b-1))
                    {
                        j->second += a*b;
                        fl_b = true;
                    }
                }
                if (!fl_b)
                    element.insert(pair <int,int>(b-1,a*b));
                fl_b = false;
                continue;
            }
            if (*i=='x')
                {
                    fl_x=true;
                    if (koef == "-" || koef == "+" || koef == "")
                        koef += '1';
                    a = stoi(koef);
                }
            if (isdigit(*i) && !(flag_step))
                    koef += *i;
            if (isdigit(*i) && flag_step)
                    step += *i;
            if (*i == '^')
                flag_step = true;

        }
        string result = "";
        for (auto j = element.begin(); j != element.end(); j++)
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

        return result;
}
