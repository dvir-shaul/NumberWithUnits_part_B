#include "NumberWithUnits.hpp"
using namespace ariel;
using namespace std;


void update_table(){
    ofstream myfile;
    myfile.open ("myTestFile.txt");
    myfile << "1 hour = 60 min" << endl;
    myfile << "1 min = 60 sec" << endl;
    myfile << "1 day = 24 hour" << endl;
    myfile << "1 month = 30 day" << endl;
    myfile.close(); 
    ifstream units_file{"myTestFile.txt"};
    NumberWithUnits::read_units(units_file);
}

void update_table_one(){
    ofstream myfile;
    myfile.open ("myTestFile.txt");
    myfile << "1 hour = 30 min" << endl;
    myfile << "1 min = 60 sec" << endl;
    myfile.close(); 
    ifstream units_file{"myTestFile.txt"};
    NumberWithUnits::read_units(units_file);
}
void update_table_two(){
    ofstream myfile;
    myfile.open ("myTestFile.txt");
    myfile << "1 km = 1000 m" << endl;
    myfile << "1 m = 100 cm" << endl;
    myfile << "1 cm = 10 mm" << endl;
    myfile << "1 kg = 1000 g" << endl;
    myfile << "1 ton = 1000 kg" << endl;
    myfile << "1 g = 1000 mg" << endl;
    myfile.close(); 
    ifstream units_file{"myTestFile.txt"};
    NumberWithUnits::read_units(units_file);
}
void update_table_three(){
    ofstream myfile;
    myfile.open ("myTestFile.txt");
    myfile << "1 kg = 1000 g" << endl;
    myfile << "1 ton = 500 kg" << endl;
    myfile << "1 g = 1000 mg" << endl;
    myfile.close(); 
    ifstream units_file{"myTestFile.txt"};
    NumberWithUnits::read_units(units_file);
}
int main(){
    update_table();
    NumberWithUnits min1=NumberWithUnits(1,"min");
    NumberWithUnits min4=NumberWithUnits(4,"min");
    NumberWithUnits hour4=NumberWithUnits(4,"hour");
    NumberWithUnits min15=NumberWithUnits(15,"min");
    NumberWithUnits day1=NumberWithUnits(1,"day");
    NumberWithUnits day_3=NumberWithUnits(-3,"day");
    cout << "update is: normal time" << endl;
    cout << "4 hours + 15 minute in 'hour' time = " << hour4+min15 << "  in minute time = "<<  min15+hour4 << endl; 
    cout << "-3 day  + daytime:  " << day_3+day1 <<  endl; 
    cout << "day + 4 hours + 15 minute time from day = " << day1+hour4+min15 <<  endl; 
    cout << "day + 4 hours + 15 minute time from minute = " << min15+day1+hour4 <<  endl<<endl;
    cout << "check opertor += :";
    min1 += min4; 
    cout << "1 min + 4 min = " <<  min1 << endl;
    min1 -= min4; 
    cout << "check opertor -=  : 5 min - 4 min = " << min1 << endl;
    cout << "check opertor  *  : min4 * 5      = " << min4 * 5 << endl;
    cout << "check opertor  *  : 5 * min4      = " << 5*min4  << endl <<endl ;


    update_table_one();
    cout << "update is: hour reduce from 60 minute to 30 minute per hour" << endl;
    NumberWithUnits new_min1=NumberWithUnits(1,"min");
    NumberWithUnits min0=NumberWithUnits(0,"min");
    NumberWithUnits hour1=NumberWithUnits(1,"hour");
    NumberWithUnits n_min15=NumberWithUnits(15,"min");
    cout << "2 new hours => 1 normal hour = " << min0+hour1+hour1 <<endl;
    cout << "new 1 min + 1 hour =           " <<   new_min1 +hour1 << endl;
    cout << "new 15 min + 1 hour =          " <<   n_min15 +hour1 << endl<<endl;

    update_table_two();
    cout << "now check  weight: " <<endl;
    NumberWithUnits ton_1(1 , "ton");
    NumberWithUnits kg_1000(1000 , "kg");
    NumberWithUnits kg(1 , "kg");
    cout <<"if ton == kg      ? answer is: " <<(ton_1 == kg) << endl;
    cout <<"if ton == 1000 kg ? answer is: " <<(ton_1 == kg_1000) << endl<<endl;


    update_table_three();
    cout << "now check false weight" <<endl;
    NumberWithUnits ton(1 , "ton");
    NumberWithUnits kg_500(500 , "kg");
    NumberWithUnits kg1(1 , "kg");
    bool check3 = ton == kg_500;
    cout <<"if new ton == 500 kg      ? answer is: " <<check3 << endl;

}