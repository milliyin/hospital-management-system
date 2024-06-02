#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
using namespace std;
class appointment; class admin;
string monthconverte(int);
class patient{
    private:
    string name;
    double height;
    double weight;
    public:
    patient(){name="null";height=0;weight=0;}
    patient(string NAME,double HEIGHT,double WEIGHT){name=NAME;height=HEIGHT;weight=WEIGHT;}
    friend class admin;
};
class doctor{
    private:
    string name;
    string major;
    public:
    doctor(){name="null";major="non";}
    doctor(string NAME,string MAJOR){name=NAME;major=MAJOR;}
    void diagnos_patient(appointment &AP,string D);
    friend class admin;
};
class appointment{
    private:
    patient P;
    doctor D;
    int day;
    int month;
    string diagnosis="NULL";
    string medicine="NULL";
    void diagnos(string);
    public:
    appointment(patient PATIENT,doctor DOCTOR,int DAY,int MONTH){P=PATIENT;D=DOCTOR;day=DAY;month=MONTH;}
    friend class admin;
    friend class doctor;
};
class admin{
    public:
    void view_appointment(appointment A);
};
void sleep(float seconds);
int main(){
    doctor d1("Jhon","staff surgeon");
    patient p1("illiyin",5.6,53);
    appointment a1(p1,d1,02,5);
    admin ad1;
    ad1.view_appointment(a1);
    sleep(3);
    system("CLS");
    d1.diagnos_patient(a1,"polio");
    ad1.view_appointment(a1);

}
void sleep(float seconds){
    clock_t startClock = clock();
    float secondsAhead = seconds * CLOCKS_PER_SEC;
    while(clock() < startClock+secondsAhead);
}
void admin::view_appointment(appointment A){
    cout<<"APPOITNMENT INFOMATION @ Day: "<<A.day<<" Month: "<<monthconverte(A.month)<<endl;
    cout<<"--------------------"<<endl;
    cout<<"Patient Info: "<<endl;
    cout<<"Name: "<<A.P.name<<endl;
    cout<<"Height: "<<A.P.height<<endl;
    cout<<"Weight: "<<A.P.weight<<endl;
    cout<<"--------------------"<<endl;
    cout<<"Doctor Info: "<<endl;
    cout<<"Name: "<<A.D.name<<endl;
    cout<<"Major: "<<A.D.major<<endl;
    cout<<"--------------------"<<endl;
    cout<<"Diagnosis: "<<A.diagnosis<<endl;
    cout<<"Medicine: "<<A.medicine<<endl;
}
void appointment::diagnos(string diagnosi){
    diagnosis = diagnosi;
}
void doctor::diagnos_patient(appointment &AP,string D){AP.diagnos(D);}
string monthconverte(int mo){
    string month;
    if(mo>0 && mo<13){
            switch (mo) {
        case 1:
            month = "January";
            break;
        case 2:
            month = "February";
            break;
        case 3:
            month = "March";
            break;
        case 4:
            month = "April";
            break;
        case 5:
            month = "May";
            break;
        case 6:
            month = "June";
            break;
        case 7:
            month = "July";
            break;
        case 8:
            month = "August";
            break;
        case 9:
            month = "September";
            break;
        case 10:
            month = "October";
            break;
        case 11:
            month = "November";
            break;
        case 12:
            month = "December";
            break;
    }
    return month;
    }
    return "null";
}
