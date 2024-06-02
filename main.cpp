#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include<sstream>

using namespace std;

class appointment; class admin;
string monthconverte(int);
struct datetime{int year,mon,day,hour,min,sec;};
void timestamptodatetime(datetime &,int timestamp);
int convertToTimestamp(int year, int month, int day, int hour, int minute, int second);

class patient{
    private:
    string name;
    double height;
    double weight;
    int id;
    public:
    patient(){name="null";height=0;weight=0;}
    patient(int ID,string NAME,double HEIGHT,double WEIGHT){id=ID;name=NAME;height=HEIGHT;weight=WEIGHT;}
    void info();
    friend class admin;
};
class doctor{
    private:
    string name;
    string major;
    string phonenumber;
    int id;
    public:
    doctor(){name="null";major="non";phonenumber="0000";}
    doctor(int ID,string NAME,string MAJOR,string Phonenumber){id=ID;name=NAME;major=MAJOR;phonenumber=Phonenumber;}
    void diagnos_patient(appointment &AP,string D);
    void info();
    friend class admin;
    friend class appointment;
};
class appointment{
    private:
    int patientID;
    int doctorID;
    int CREATEDtime;
    int timeON;
    string diagnosis="NULL";
    string medicine="NULL";
    patient P;
    doctor D;
    void diagnos(string);
    public:
    appointment(){}
    appointment(int Pid,int Did,int month,int day,int hour,string dia,string med){patientID=Pid;doctorID=Did;CREATEDtime=time(NULL);
    timeON=convertToTimestamp(2024,month,day,hour,0,0); diagnosis=dia;medicine=med;}
    void confirm(doctor doc[],int docsize,patient pat[],int patsize);
    friend class admin;
    friend class doctor;
};
class admin{
    public:
    void view_appointment(appointment A);
};
void sleep(float seconds);
int file_linecount(string);
void load_doctors(doctor[],string,int);
void load_patients(patient[],string,int);
void load_appointments(appointment[],string,int,doctor doc[],int docsize,patient pat[],int patsize);

int main(){
    //Loading Doctors
    string doctorfile = "doctors.csv";
    int no_doctors = file_linecount(doctorfile)-1;
    doctor *doctors = new doctor[(no_doctors)];
    load_doctors(doctors,doctorfile,no_doctors);


    //Loading Patients
    string patientfile = "patients.csv";
    int no_patients = file_linecount(patientfile)-1;
    patient *patients = new patient[(no_patients)];
    load_patients(patients,patientfile,no_patients);

    admin ADMIN;
    // loading Appointments
    string appointmentfile="appointments.csv";
    int no_appointments = file_linecount(appointmentfile)-1;
    appointment *appointments = new appointment[(no_appointments)];
    load_appointments(appointments,appointmentfile,no_appointments,doctors,no_doctors,patients,no_patients);

}
void sleep(float seconds){
    clock_t startClock = clock();
    float secondsAhead = seconds * CLOCKS_PER_SEC;
    while(clock() < startClock+secondsAhead);
}
void timestamptodatetime(datetime &dt,int timestamp){
    time_t now = timestamp;
    tm *ltm = localtime(&now);
    dt.year=1900 + ltm->tm_year;
    dt.mon=1 + ltm->tm_mon;
    dt.day = ltm->tm_mday;
    dt.hour=5+ltm->tm_hour;
    dt.min = 30+ltm->tm_min;
    dt.sec=ltm->tm_sec;
}
int convertToTimestamp(int year, int month, int day, int hour, int minute, int second) {
    struct tm timeinfo = {0};
    timeinfo.tm_year = year - 1900;    
    timeinfo.tm_mon = month - 1;       
    timeinfo.tm_mday = day;            
    timeinfo.tm_hour = hour;           
    timeinfo.tm_min = minute;          
    timeinfo.tm_sec = second;          
    time_t timestamp = mktime(&timeinfo);
    return timestamp;
}


void admin::view_appointment(appointment A){
    datetime dt;
    timestamptodatetime(dt,A.timeON);
    cout<<"APPOITNMENT INFOMATION @ Day: "<<dt.day<<" Month: "<<monthconverte(dt.mon)<<endl;
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
void doctor::info(){cout<<"ID: "<<id<<"| Name: "<<name<<"| Major: "<<major<<"| PhoneNumber: "<<phonenumber<<endl;}
void patient::info(){cout<<"ID: "<<id<<"| Name: "<<name<<"| Hight: "<<height<<"| Weight: "<<weight<<endl;}
void appointment::confirm(doctor doc[],int docsize,patient pat[],int patsize){
    for(int i=0;i<docsize;i++){
        if(doc[i].id==doctorID){
            D = doc[i];
            //cout<<"Doctor Found!\n";
        }
    }
        for(int i=0;i<patsize;i++){
        if(doc[i].id==patientID){
            P = pat[i];
            //cout<<"Patient Found!\n";
        }
    }
}


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

int file_linecount(string filename){
    fstream fin;
    int linecount=0;
		string temp;
		fin.open(filename,ios::in);
	while(getline(fin,temp)){linecount++;}
    fin.close(); return linecount;
}
void load_doctors(doctor doc[],string doctorfile,int no_doctors){
    fstream fin1;
    fin1.open(doctorfile,ios::in);
    string temp1;getline(fin1,temp1);
    for(int i=0;i<no_doctors;i++){
        string name,major,number,line; int id;
        getline(fin1,line);
        istringstream iss(line);
        iss>>id;
        iss.ignore(200,',');
        getline(iss,name,',');
        getline(iss,major,',');
        getline(iss,number,',');
        doc[i] = doctor(id,name,major,number);
        //doc[i].info();
    }
}

void load_patients(patient pat[],string patientfile,int no_patients){
    fstream fin1;
    fin1.open(patientfile,ios::in);
    string temp1;getline(fin1,temp1);
    for(int i=0;i<no_patients;i++){
        string name,line;int Height,Weight;int id;
        getline(fin1,line);
        istringstream iss(line);
        iss>>id;
        iss.ignore(200,',');
        getline(iss,name,',');
        iss>>Height;
        iss.ignore(200,',');
        iss>>Weight;
        pat[i] = patient(id,name,Height,Weight);
        //pat[i].info();
    }
}
void load_appointments(appointment ap[] ,string appointmentfile,int no_appointments,doctor doc[],int docsize,patient pat[],int patsize){
    fstream fin1;
    fin1.open(appointmentfile,ios::in);
    string temp1;getline(fin1,temp1);
    for(int i=0;i<no_appointments;i++){
        int pID,dID,mon,day,hour; string dia,med,line;
        getline(fin1,line);
        istringstream iss(line);
        iss>>pID;
        iss.ignore(200,',');
        iss>>dID;
        iss.ignore(200,',');
        iss>>mon;
        iss.ignore(200,',');
        iss>>day;
        iss.ignore(200,',');
        iss>>hour;
        iss.ignore(200,',');
        getline(iss,dia,',');
        getline(iss,med,',');
        ap[i] = appointment(pID,dID,mon,day,hour,dia,med);
        ap[i].confirm(doc,docsize,pat,patsize);
        cout<<"CONFIRMED!!\n";
    }

}
