#pragma once 
#include <iostream>
#include <map>
#include <fstream>
#include <string.h>
#include <stdbool.h>

using namespace std;

namespace ariel{

    class NumberWithUnits{

        private:
            std::string unit_type;
            double unit_val;
            

        public:
            NumberWithUnits(double val, const std::string &unit);
            ~NumberWithUnits(){};
           
            
            friend int compare(const NumberWithUnits& N1, const NumberWithUnits& N2);

            static void read_units(istream& filename);
            NumberWithUnits operator +(const NumberWithUnits &N);
            NumberWithUnits& operator +=(const NumberWithUnits &N);
            NumberWithUnits operator +();//unary plus
            NumberWithUnits operator -(const NumberWithUnits &N);
            NumberWithUnits& operator -=(const NumberWithUnits &N);
            NumberWithUnits operator -();//unary minus

            bool operator >(const NumberWithUnits &N) const;
            bool operator >=(const NumberWithUnits &N) const;
            bool operator <(const NumberWithUnits &N) const;
            bool operator <=(const NumberWithUnits &N) const;
            bool operator ==(const NumberWithUnits &N) const;
            bool operator !=(const NumberWithUnits &N) const;

            NumberWithUnits &operator ++();
            NumberWithUnits operator ++(int x);
            NumberWithUnits &operator --();
            NumberWithUnits operator --(int x);

            friend NumberWithUnits operator*(double num,const NumberWithUnits &N);
            friend NumberWithUnits operator*(const NumberWithUnits &N2, double num2);
            NumberWithUnits& operator*=( double n);

            friend std::ostream& operator<<(std::ostream& os, const NumberWithUnits& N);
            friend std::istream& operator>>(std::istream& is, NumberWithUnits& N);
            

            
            
    };
};