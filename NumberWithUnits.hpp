#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>


namespace ariel{
    class NumberWithUnits{          
            

        public:
             
            NumberWithUnits(const double amount,const std::string &Of_What);
            ~NumberWithUnits(){}

            double amount; 
            std::string Of_What;
            
            friend NumberWithUnits operator+(const NumberWithUnits & a,const NumberWithUnits & b) ;
            friend NumberWithUnits operator+=(NumberWithUnits  & a,const NumberWithUnits & b);
            friend NumberWithUnits operator+(const NumberWithUnits & a);


            friend NumberWithUnits operator-(const NumberWithUnits & a,const NumberWithUnits & b) ;
            friend NumberWithUnits operator-=(NumberWithUnits  & a,const NumberWithUnits & b);
            friend NumberWithUnits operator-(const NumberWithUnits & a);


            friend NumberWithUnits operator*(const NumberWithUnits& a, const double &val);
            friend NumberWithUnits operator*(const double &val,const NumberWithUnits& a);


            friend  NumberWithUnits operator--( NumberWithUnits & a, int );
            friend  NumberWithUnits & operator--( NumberWithUnits & a );
            friend  NumberWithUnits & operator++( NumberWithUnits & a );
            friend  NumberWithUnits operator++( NumberWithUnits & a, int );


            friend std::istream& operator>>(std::istream& istream, NumberWithUnits& a);
            friend std::ostream& operator<<(std::ostream& ostream, const NumberWithUnits& a);
                    
                    
            friend bool operator<(const NumberWithUnits& first, const NumberWithUnits& second) ;
            friend bool operator>(const NumberWithUnits& first, const NumberWithUnits& secondd) ;
            friend bool operator<=(const NumberWithUnits& first, const NumberWithUnits& second) ;
            friend bool operator>=(const NumberWithUnits& first, const NumberWithUnits& second) ;
            friend bool operator==(const NumberWithUnits& first, const NumberWithUnits& second) ;
            friend bool operator!=(const NumberWithUnits& first, const NumberWithUnits& second) ;                

            static void read_units(std::ifstream& files);           

    };
}



