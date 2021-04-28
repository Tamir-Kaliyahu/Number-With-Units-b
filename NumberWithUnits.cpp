#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include "NumberWithUnits.hpp"

using namespace std;
namespace ariel
{

    map<std::string, map<std::string, double>> Unit_map;

    NumberWithUnits::NumberWithUnits(double val, const std::string &unit)
    {
        if (Unit_map.find(unit) != Unit_map.end())
        {
            this->unit_val = val;
            this->unit_type = unit;
        }
        else
        {
            throw invalid_argument("unit type: [" + unit + "] does not exist!");
        }
    }

    void NumberWithUnits::read_units(istream &file)
    {
        std::string line, word1, word2, preVal;
        double val;

        while (getline(file, line))
        {
            word1 = "";
            word2 = "";
            preVal = "";
            val = 0;
            size_t i = 2;
            while (line.at(i) != ' ')
            {
                word1 += line[i];
                i++;
            }
            while (line.at(i) == ' ' || line.at(i) == '=')
            {
                i++;
            }
            while (isdigit(line.at(i)) || line.at(i) == '.')
            {
                preVal += (line.at(i));
                i++;
            }
            val = std::stof(preVal); //convert a string to a float.
            i++;

            while (i < line.length())
            {
                word2 += char(line[i]);
                i++;
            }

            cout << "word1: " << word1 << ", word2: " << word2 << ", val= " << val << endl;
            Unit_map[word1][word2] = val;
            Unit_map[word2][word1] = 1 / val;

            for (auto UnitKey : Unit_map[word1])
            {
                Unit_map[word2][UnitKey.first] = Unit_map[word2][word1] * UnitKey.second;
                Unit_map[UnitKey.first][word2] = 1 / (Unit_map[word2][word1] * UnitKey.second);
            };
            for (auto UnitKey : Unit_map[word2])
            {
                Unit_map[word1][UnitKey.first] = Unit_map[word1][word2] * UnitKey.second;
                Unit_map[UnitKey.first][word1] = 1 / (Unit_map[word1][word2] * UnitKey.second);
            };
        };
    }
    double ConvertUnit(double init_val, const string &UnitA, const string &UnitB)
    {
        if (UnitA == UnitB)
        {
            return init_val;
        }
        try {
            return (init_val) * (Unit_map.at(UnitA).at(UnitB));
        }
        catch(const exception& ex) {
            throw invalid_argument("Sorry, [" + UnitA + "] cannot be converted to [" + UnitB + "]!");
        }

        
        
    }

    int compare(const NumberWithUnits &N1, const NumberWithUnits &N2)
    {

        double N2_val = ConvertUnit(N2.unit_val, N2.unit_type, N1.unit_type);
        int ans = 0;
        if (N1.unit_val - N2_val > 0) // 1 in case N1 is bigger
        {
            ans=1;
        }
        if (N1.unit_val - N2_val < 0) // -1 in case N2 is bigger
        {
            ans=-1;
        }
        return ans; // return 0 if N1 equals N2.
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num)
    {
        double ans = this->unit_val + ConvertUnit(num.unit_val, num.unit_type,this->unit_type);
        return NumberWithUnits(ans, this->unit_type);
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num)
    {
        this->unit_val += ConvertUnit(num.unit_val,  num.unit_type,this->unit_type);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator+()
    {
        return NumberWithUnits(+this->unit_val, this->unit_type);
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num)
    {
        double ans = this->unit_val - ConvertUnit(num.unit_val,  num.unit_type,this->unit_type);
        return NumberWithUnits(ans, this->unit_type);
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num)
    {
        double val =ConvertUnit(num.unit_val, num.unit_type, this->unit_type);
        this->unit_val -=val;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator-()
    {
        return NumberWithUnits(-this->unit_val, this->unit_type);
    }

    bool NumberWithUnits::operator>(const NumberWithUnits &num) const
    {
        if (compare(*this, num) == 1)
        {
            return true;
        }
        return false;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &num) const
    {
        if (compare(*this, num) == 1 || compare(*this, num) == 0)
        {
            return true;
        }
        return false;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &num) const
    {
        if (compare(*this, num) == -1)
        {
            return true;
        }
        return false;
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &num) const
    {
        if (compare(*this, num) == -1 || compare(*this, num) == 0)
        {
            return true;
        }
        return false;
    }

    bool NumberWithUnits::operator==(const NumberWithUnits &num) const
    {
        if (compare(*this, num) == 0)
        {
            return true;
        }
        return false;
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &num) const
    {
        if (compare(*this, num) != 0)
        {
            return true;
        }
        return false;
    }

    NumberWithUnits &NumberWithUnits::operator++()
    {
        (this->unit_val) ++;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int)
    {
        return NumberWithUnits((this->unit_val)++, this->unit_type);
    }

    NumberWithUnits &NumberWithUnits::operator--()
    {
        --(this->unit_val);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int)
    {
        return NumberWithUnits((this->unit_val)--, this->unit_type);
    }

    std::ostream &operator<<(std::ostream &os, const NumberWithUnits &N)
    {
        os << N.unit_val << "[" << N.unit_type << "]";
        return os;
    }
     std::istream &operator>>(std::istream &is, NumberWithUnits &N) {
        double v=0;
        std::string t;
        char ch=' ';
        is >> v;
        is >> ch ;
        while(ch!=']'){
            if(ch!='[')
            {
                t.insert(t.end(),ch);
            }
            is>>ch;
        }
       if(Unit_map[t].empty()){
           throw invalid_argument{"cannot find the unit!"};
           };
        N.unit_val=v;
        N.unit_type=t;
        return is;
    }
    NumberWithUnits operator*(double num, const NumberWithUnits& N)
    {
        return NumberWithUnits(N.unit_val * num, N.unit_type);
        
    }
    NumberWithUnits operator*(const NumberWithUnits& N, double num)
    {
        return NumberWithUnits(num * N.unit_val, N.unit_type);
    }

    NumberWithUnits& NumberWithUnits:: operator*=(double num) {
        this->unit_val *= num;
        return *this;
    }

};
