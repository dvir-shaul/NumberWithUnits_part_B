#include <iostream>
#include <unordered_map>
#include <string>
#include "NumberWithUnits.hpp"

using namespace std;

const double  epsilon =  0.0001;



namespace ariel{

    std::unordered_map<std::string,std::unordered_map<std::string ,double>> my_map;

   NumberWithUnits::NumberWithUnits(const double amount,const string &Of_What){
        if (my_map.count(Of_What)==0|| Of_What.empty()){
          throw runtime_error("wrong unit type");
        }
        this->amount=amount;
        this->Of_What=Of_What;
      }

    istream& operator>>(istream& istream, NumberWithUnits& a){
        double amount1 = 0;
        string _new_str = " ";
        char b1 = '\0';
        char b2 = '\0';

        ios::pos_type startPosition = istream.tellg();
        istream >> a.amount >> b1 >> _new_str;
        if (_new_str.at(_new_str.length()-1) == ']')
        {
            _new_str = _new_str.substr(0, _new_str.length()-1);
        }
        else{
            istream >> b2;
        }
        if (my_map.find(_new_str) == my_map.end())
        {
            throw invalid_argument("Wrong input, can't build new NumberWithUnits");
        }

        //a.amount = amount1;
        a.Of_What = _new_str;
        return istream;
    }
    

    ostream& operator<<(ostream& ostream, const NumberWithUnits& a){
        return ostream<<a.amount<<"["<<a.Of_What<<"]";
    }


  bool check( NumberWithUnits const & a, NumberWithUnits const & b ) {
    if((a.Of_What==b.Of_What) && my_map.find(a.Of_What) != my_map.end()) {
        return false;
        }
    if ( my_map.find(a.Of_What) != my_map.end() &&  (my_map[a.Of_What].find(b.Of_What) != my_map[a.Of_What].end())) {
                    return false;
            }
    return true;
  }


     double converter(const string& a, const string& b,double val ){
        if(a == b) {return val;}
        try {
            return val * my_map[b][a];
        }
        catch(const exception& e) {
            throw invalid_argument{"Units do not match - ["+a+"] cannot be converted to ["+b+"]"};
        }
    }
  void casting(const string &str1 ,const string &str2){
       for (auto& p : my_map[str1]){
            double cast = my_map[str2][str1] * p.second;
            my_map[str2][p.first] = cast;
            my_map[p.first][str2]= 1/cast;
            }
        for (auto& p : my_map[str2]){
            double cast = my_map[str1][str2] * p.second;
            my_map[str1][p.first] = cast;
            my_map[p.first][str1]= 1/cast;
            }    
  }

    void NumberWithUnits::read_units(ifstream& files){
        double cast = 0;
        double v1 = 0;
        double v2 = 0;
        string equal_sign;
        string str1;
        string str2;
        /**input looks like this: 
        1 km = 1000 m 
        1 m = 100 cm
        */
        while(files >> v1 >> str1 >> equal_sign >> v2 >> str2){
            my_map[str1][str2] = v2;
            my_map[str2][str1] = 1/v2;
            casting(str1,str2);
        }
    }


    //************ plus *********

    NumberWithUnits operator+(const NumberWithUnits & a,const NumberWithUnits & b) {
        if(check(a,b)) {  __throw_invalid_argument("Eror not same type");}
        double converted = converter(a.Of_What, b.Of_What, b.amount);
        return NumberWithUnits(a.amount+converted, a.Of_What);;
    }
    NumberWithUnits operator+(const NumberWithUnits  & a) {
        return NumberWithUnits(+a.amount,a.Of_What);
    }
    NumberWithUnits operator+=(NumberWithUnits  & a,const NumberWithUnits & b){
        if(check(a,b)) {  __throw_invalid_argument("Eror not same type");}
        //double converted = converter(a.Of_What, b.Of_What, b.amount);
        a = a+b;
        return a;
    }


    // ********* minus ********

    NumberWithUnits operator-(const NumberWithUnits  & a) {
        return NumberWithUnits(-1*(a.amount),a.Of_What);
    }
    NumberWithUnits operator-(const NumberWithUnits  & a, const NumberWithUnits  & b) {
        if(check(a,b)) {  __throw_invalid_argument("Eror not same type");}
        double converted = converter(a.Of_What, b.Of_What, b.amount);
        return NumberWithUnits(a.amount-converted, a.Of_What);;
    }

    NumberWithUnits operator-=(NumberWithUnits  & a,const NumberWithUnits & b){
        if(check(a,b)) {  __throw_invalid_argument("Eror not same type");}
        //double converted = converter(a.Of_What, b.Of_What, b.amount);
         a = a-b;
        return a;
    }





  //     ************ ++     -- ************************

     //value--
    NumberWithUnits operator--( NumberWithUnits & a, int ){
        return NumberWithUnits(a.amount--,a.Of_What);
    }
    //--value
    NumberWithUnits & operator--( NumberWithUnits & a ){
      a.amount--;
      return a;
    }

    NumberWithUnits & operator++( NumberWithUnits & a ){
         a.amount++;
        return a;
    }
    NumberWithUnits operator++( NumberWithUnits & a, int ){
        return NumberWithUnits(a.amount++,a.Of_What);
    }


    //************ multiply *********


    NumberWithUnits operator*(const NumberWithUnits& a,const double &val){
        return NumberWithUnits(val * a.amount,a.Of_What);
    }

    NumberWithUnits operator*(const double &val,const NumberWithUnits& a){
        return NumberWithUnits(val * a.amount,a.Of_What);
    }








    //************ comparison between two objects *********




    bool operator<(const NumberWithUnits& first, const NumberWithUnits& second)  {
        if(check(first,second)) {  __throw_invalid_argument("Eror not same type");}
        if( first.Of_What == second.Of_What){
            return first.amount < second.amount;
        }
        double converted = my_map[first.Of_What][second.Of_What];
        double n = first.amount * converted;
        return (n < second.amount);
    }

    bool operator>(const NumberWithUnits& first, const NumberWithUnits& second)  {
        if(check(first,second)) {  __throw_invalid_argument("Eror not same type");}
        double converted = converter(first.Of_What, second.Of_What, second.amount);
        if(first.amount > converted){
            return 'c'=='c';
        }
        return 'c'=='d';
           }

    bool operator<=(const NumberWithUnits& first, const NumberWithUnits& second) {
        if(first==second || first < second){
            return 'c'=='c';
        }
        return false;
    }
    bool operator>=(const NumberWithUnits& first, const NumberWithUnits& second) {
        if(first==second || first > second){
            return 'c'=='c';
        }
        return false;
    }
    
    bool operator==(const NumberWithUnits& first, const NumberWithUnits& second) {
        if(check(first,second)) {  __throw_invalid_argument("Eror not same type");}
        if(first.amount == second.amount && first.Of_What != second.Of_What && first.amount !=0){
            return 'c'=='d';
        }
        double converted = converter(first.Of_What, second.Of_What, second.amount);
        if (abs(first.amount - converted) < epsilon){
            return 'c'=='c';
        }
        return 'c'=='d';
    }
    bool operator!=(const NumberWithUnits& first, const NumberWithUnits& second) {
        if(check(first,second)) {  __throw_invalid_argument("Eror not same type");}
        double converted = converter(first.Of_What, second.Of_What, second.amount);
        if(abs(first.amount - converted) > epsilon){
            return 'c'=='c';
        }
        return 'c'=='d';
    }     

}


