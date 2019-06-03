
//
//  Created by TCHASSE ODJAC on 24.01.18.
//  Copyright © 2018 TCHASSE ODJAC. All rights reserved.
//


#include <iostream>
using namespace std;
class Timepoint{
private:
    unsigned int dayofyear,year,time;
    static const int days[];
public:
    Timepoint(int day=31,int month=12,int years=9999,int hour=23,int minute=59){
        year=years;
        dayofyear=day+days[month-1];
        time=minute+hour*60;
    }
    int get_dayOfYear(){
        return dayofyear;
    }
    public:friend Timepoint& operator++(Timepoint a);
    public:friend istream& operator>>(istream& out, Timepoint&);
    public:friend ostream& operator<<(ostream& out, Timepoint);
};
Timepoint& operator++(Timepoint a)
{
    a.dayofyear=a.dayofyear+1;
    //    result.seconds=a.seconds;
    if (a.dayofyear==365) {
        a.dayofyear= 1;a.year++;
    }
    return a;
}
istream& operator>>(istream& in, Timepoint& z) // to be continued part for month
{
    int day=31, month=12, years=9999, hour=23, minute=59; char blank;
    in>>day>>blank>>month>>years>>hour>>blank>>minute;
    z = *new Timepoint(day, month, years, hour, minute);
//    minute=z.time/60;
//    cout << "Timepoint:      "; // optional
//
//    in >> z.year;
//    cout<<"input month ";
//    in >> z.dayofyear>>z.dayofyear>>z.time>>minute;
    return in;
}
const int Timepoint::days[]={0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
ostream& operator<<(ostream& out,  Timepoint Time)
{
    return out << Time.year <<Time.dayofyear<<Time.time<<(Time.time)/60; // to be continued also
}
class License{
private:
    int no;
    string issuer;
    Timepoint validUntil ;
public:
    License(int a,string b,Timepoint c):no(a),issuer(b),validUntil(c){}; // not sure about validuntil to be.....
    int  get_no(){
        return no;
    }
    string get_issuer(){
        return issuer;
    }
    Timepoint get_validUntil (){
        return validUntil;
    }
    public:friend ostream& operator<<(ostream& out, License&);
    
};
ostream& operator<<(ostream& out,  License& Li)
{
    return out << Li.issuer<<Li.no<<Li.validUntil ; // to be continued also
}
class Drive{
private:
    string name;
    License license;
public:
    Drive(string a,License b):name(a),license(b){
        cout<<"input name";
        cin>>a;
        name=a;
        cout<<"input number ";
        b.get_no();
        cout<<"input issuer";
        b.get_issuer();
        cout<<"input validity";
        b.get_validUntil();
        }
    string get_name(){
        return name;
    }
    License get_license(){
        return license;
    }
     public:friend ostream& operator<<(ostream& out, Drive&);
  };
ostream& operator <<(ostream& out, Drive& Dr){
    return out << Dr.name<<"("<<Dr.license<<")"<<endl;
}
class Vehicle{
private:
    string model,plate;
     float price24h;
public:
    Vehicle(string a,string b,float c):model(a),plate(b),price24h(c){};
    string get_model (){
        return model;
    }
    string get_plate(){
        return plate;
    }
    float get_price(int numberofdays){
        return price24h*numberofdays;
    }
    float set_price24h (float setprice){
        return price24h;
    }
    virtual void print()=0;
    
};
class Scooter:public Vehicle {
public:
    Scooter(string mod,string pla):Vehicle(mod,pla,9.99){}
  virtual  void print(){
        cout<<"Scooter "<<get_model()<<"("<<get_plate()<<")";
    }
};
class Car:public Vehicle{
private:
    bool navigation;
public:
    Car(string mo,string pla,float pric,bool nom=true):Vehicle(mo,pla,29.99),navigation(nom){}
    virtual bool has_aircondition(){ // not too sure about this ones
        bool input;
        cin>>input;
        return input;
    }
    bool has_navigation(){
        return navigation;
    }
  virtual  void print(){
      cout<<get_plate()<<has_aircondition()<<has_navigation()<<endl;
        }
};
class Cabrio:public Car{
public:
    Cabrio(string mod,string pla,float value):Car(mod,pla,99.90,false){}
    virtual bool  has_aircondition (){
        return false;
    }
    virtual void print(){
        cout<<"Cabrio "<<get_model()<<"("<<get_plate()<<")"<<endl;
    }
};
class  Limousine:public Car{
private:
    bool aircondition;
public:
    Limousine(string a,string b,float prix,bool defaut=true):Car(a,b,149.90,defaut), aircondition(defaut){}
public: virtual bool has_aircondition(){  //not too sure didnt understood the question
        return aircondition;
    
    }
    virtual void print(){
        cout<< "Limousine "<<get_model()<<"("<<get_plate()<<")"<<"air condition "<<has_aircondition()<<", "<<"navigation "<<has_navigation()<<","<<endl;
    }
    };
class Rental{
private:
     int no;
    Timepoint from;
    int days;
    Vehicle *vehicle;
    Drive drive;
    Drive *additionalDriver ;
     int  last_no(int i){
        i=0;
        return i++;
    };
public:
    Rental(Vehicle *a,Timepoint b,Drive c,int nodays=1,Drive *d=nullptr):vehicle(a),from(b),days(nodays),drive(c),additionalDriver(d)
    {
    int i = 1;
    no=last_no(i);
}
    Timepoint get_from(){
        return from;
    }
    Timepoint get_until(){
        int i=0;
        while(i<days) {
            ++from;
        }
        return from;
}
    void print(){
        cout<<"VEHICLE RENTAL"<<"rental no.: "<<no<<vehicle<<from<<get_until()<<drive<<additionalDriver<<endl;// not too sure too btw
    }
    };
class  Schedule{
private:
    int i;
    Rental *point;
    Vehicle *vehicle;
    Rental *year[365];
public:
    Schedule(Vehicle *start):vehicle(start){
        for(int i=0;i<365;i++){
            year[i]=nullptr;
        }
    }
    Vehicle* get_vehicle(){
        return vehicle;
    }
    bool isFree(Timepoint var1,int var2){
        for(int a=var1.get_dayOfYear();a<var1.get_dayOfYear()+var2;a++) {
            int m=a;
            if(a>=365) {
                m=a-365;
            }
            if(year[a]!=nullptr){
                return false;
            }
        }
        return true;
    }
    int book(Timepoint rental,int nom,Drive first,Drive *second){
        
        Rental* obj;
        obj=new Rental(vehicle,rental,first,nom,second);
        
        for(int a=rental.get_dayOfYear();a<rental.get_dayOfYear()+nom;a++) {
            int m=a;
            if(a>=365) {
                m=a-365;
            }
            year[m]=obj;
        }
        return -1;
    }
    void print() {
        Rental *temp = nullptr;
        for(int a=0;a<365;a++){
            if(temp==nullptr) {
                temp=year[a];
            }else if(temp!=year[a]){
                year[a]->print();
            }
        }
    }
};
int main(int argc, const char * argv[]) {
    Timepoint time;
    int input,number,days;
    Schedule *array1[4];
    array1[0] = new Schedule(new Scooter("BMW C 650 GT", "DU-BC 65"));
    array1[1]=new Schedule(new Cabrio("BMW i8 Roadstar", "DU-BR 8", false));
    array1[2]=new Schedule(new Limousine("Mercedes C 350 e", "DU-MC 1", 129 ));
    array1[3]=new Schedule(new Limousine("Mercedes E 350 e","DU-ME 2",189, false));
    Drive *additionalDriver= nullptr;
    
    cout<<"VEHICLE RENTAL AGENCY"<<endl;
    
    while(1) {
        
        cout << endl << "0  end" << endl;
        
        cout << "1  new rental" << endl;
        
        cout << "2  print rentals" << endl;
        
        cin >> input;
        switch (input) {
                
            case 0:
                return 0;
                break;
            case 1: {
                char CHAR;
                cout << "choose a vehicle:";
                
                cout << endl;
                int i=0;
                while(i<4) {
                    
                    cout << i + 1 << "\t";
                    array1[i]->get_vehicle()->print();
                    cout << endl;
                    i++;
                    
                }
                
                cout << endl;
                cin >> number;
                cout << "day of rental:";
                cin >> time;
                cout << "number of days:";
                cin >> days;
                if (array1[number-1]->isFree(time, days)) {
                    cout << "input data vehicle and driver" << endl;
                    Drive *drv ;
                    cout << "additional driver? y/n ";
                    cin >> CHAR;
                    if (CHAR == 'y') {
                        
                    //  additionalDriver = new Drive; has a problem dont know why
                        
                    }
                    
                    cout << "booked" << endl;
                    
                    array1[number-1]->book(time, days, *drv, additionalDriver);
                    
                } else {
                    cout << "sorry, vehicle already booked" << endl;
                }
                break;
            }
                
                
            case 2: {
                
                cout << "choose vehicle:";
                
                cout << endl;
                int i=0;
                while(i<4) {
                    
                    cout << i + 1 << "\t";
                    array1[i]->get_vehicle()->print();
                    cout << endl;
                    i++;
                    
                }
                
                cout << endl;
                
                cin >> number;
                array1[number-1]->print();
                cout << endl;
                break;
            }
        }
    }
    return 0;
    
}
