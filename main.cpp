#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include<sstream>
#include<iomanip>
#include <vector>

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
    int getid(){return id;}
    friend bool idcheck(int,vector<patient> &arr);
    void view_appointment(vector<appointment> &arr);
    friend class admin;
    friend class appointment;
    friend class doctor;
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
    string getPdiagnos(appointment &AP);
    void info();
    void viewappointment_byline(appointment);
    friend bool idcheck(int,vector<doctor> &arr);
    friend class admin;
    friend class appointment;
    int getid(){return id;}
};
class appointment{
    private:
    int patientID;
    int doctorID;
    int CREATEDtime;
    int timeON;
    string diagnosis="";
    string medicine="";
    patient P;
    doctor D;
    void diagnos(string);
    string getdiagnos(){return diagnosis;};
    public:
    bool appintmentclose;
    bool checkappintmentstatus(){if(diagnosis == ""){appintmentclose = 0;}else{appintmentclose = 1;}return appintmentclose;}
    patient getpatient(){return P;}
    doctor getdoctor(){return D;}
    appointment(){}
    appointment(int Pid,int Did,int month,int day,int hour,string dia,string med){patientID=Pid;doctorID=Did;CREATEDtime=time(NULL);
    timeON=convertToTimestamp(2024,month,day,hour,0,0); diagnosis=dia;medicine=med; if(diagnosis == ""){appintmentclose = 0;}};

    appointment(int Pid,int Did,int month,int day,int hour,string dia,string med,int ctime){patientID=Pid;doctorID=Did;CREATEDtime=ctime;
    timeON=convertToTimestamp(2024,month,day,hour,0,0); diagnosis=dia;medicine=med;if(diagnosis == ""){appintmentclose = 0;}}

    appointment(int Pid,int Did,int Otime,string dia,string med,int ctime){
    patientID=Pid;doctorID=Did;CREATEDtime=ctime;
    timeON=Otime; diagnosis=dia;medicine=med;if(diagnosis == ""){appintmentclose = 0;}
    }

    void confirm(vector<doctor> &,vector<patient> &);
    friend void save_appintments(vector<appointment> &,string appointmentfile);
    friend class admin;
    friend class doctor;
};
class admin{
    public:
    void view_appointment(appointment A);
    void viewinline_appointment(appointment A);
};
void sleep(float seconds);
int file_linecount(string);
void load_doctors(vector<doctor> &,string);
void load_patients(vector<patient> &,string);
void load_appointments(vector<appointment> &,string,vector<doctor> &,vector<patient> &);
void save_appintments(vector<appointment> &,string appointmentfile);
// bool idcheck(int,patient[]);
// bool idcheck(int,doctor[]);

int main(){
    
    //Loading Doctors
    vector<doctor> doctors;
    string doctorfile = "doctors.csv";
    load_doctors(doctors,doctorfile);

    //Loading Patients
    vector<patient> patients;
    string patientfile = "patients.csv";
    load_patients(patients,patientfile);

    // loading Appointments
    vector<appointment> appointments;
    string appointmentfile="appointments.csv";
    load_appointments(appointments,appointmentfile,doctors,patients);


    while(1){
        char dec;
        while(1){
                cout<<"--LOGIN PAGE--"<<endl<<"As ADMIN enter 'A'\nAs Doctor enter 'D'\nAs Patient Enter P'\nPress 'Q' to QUITE\n";
                cout<<">>>>";
                cin>>dec;
                if(dec != 'A' && dec != 'D' && dec != 'P' && dec != 'Q'){
                    cout<<"WRONG INPUT"<<endl;
                    sleep(1);
                    system("CLS");
                    continue;
                }else{
                    break;
                }
            }
        if(dec == 'Q'){
            break;
        }
        system("CLS");
        switch (dec){
            case 'A':
            {   admin ADMIN;
                char d1 = '\0';
                while(d1 != 'C' && d1 != 'E' && d1 != 'V'){
                cout<<"---ADMIN PORTAL---"<<endl;
                cout<<"To create appointment, enter 'C' \nTo edit appointment enter 'E'\nView All Appointments enter 'V'\n"<<endl;
                cout<<">>>>";
                cin>>d1;
                if(d1 != 'C' && d1 != 'E' && d1 != 'V'){
                cout<<"WRONG INPUT"<<endl;
                sleep(1);
                system("CLS");
                } }
                system("CLS");
                switch (d1)
                {
                    case 'C':{
                        int Pid;
                        int Did;
                        while(1){
                            cout<<"---ADMIN PORTAL---"<<endl;
                            cout<<"Enter the required information to create an appointment Below(1/2)\n"<<endl;
                            cout<<"Enter the Patient ID:"<<endl;
                            cin>>Pid;
                            if(idcheck(Pid,patients)){
                                cout<<"CORRECT ID :)";
                                break;
                            }else{
                                cout<<"WRONG ID"<<endl;
                                sleep(1);
                                system("CLS");
                            }
                        }
                        system("CLS");
                        while(1){
                            cout<<"---ADMIN PORTAL---"<<endl;
                            cout<<"Enter the required information to create an appointment Below(2/3)\n"<<endl;
                            cout<<"Enter the Doctor ID:"<<endl;
                            cin>>Did;
                            if(idcheck(Did,doctors)){
                                cout<<"CORRECT ID :)";
                                break;
                            }else{
                                cout<<"WRONG ID"<<endl;
                                sleep(1);
                                system("CLS");
                            } 
                        }
                        system("CLS");
                        int mon,day,hour;
                        while(1){
                            cout<<"---ADMIN PORTAL---"<<endl;
                            cout<<"Enter the required information to create an appointment Below(3/3)\n"<<endl;
                            cout<<"Enter the Date & time:"<<endl; 
                            cout<<"Month:"<<endl;
                            cin>>mon;
                            if(!(mon <= 12 && mon > 0)){
                                cout<<"Wrong Month Entry"<<endl;
                                sleep(1);
                                system("CLS");
                                continue;
                            }
                            cout<<"Day:"<<endl;
                            cin>>day;
                            if(!(day <= 31 && day > 0)){
                                cout<<"Wrong Day Entry"<<endl;
                                sleep(1);
                                system("CLS");
                                continue;
                            }
                            cout<<"Hour in 24h:"<<endl;
                            cin>>hour;
                            if(!(hour <= 24 && hour > 0)){
                                cout<<"Wrong Hour Entry"<<endl;
                                sleep(1);
                                system("CLS");
                                continue;
                            }else{
                                break;
                            }
                        }
                        system("CLS");
                        cout<<"---ADMIN PORTAL---"<<endl;
                        appointment NEWapp(Pid,Did,mon,day,hour,"","");
                        NEWapp.confirm(doctors,patients);
                        appointments.push_back(NEWapp);
                        cout<<"Sucessfull Created!"<<endl;
                        cout<<setw(5)<<"PatientID"<<setw(15)<<"Patient NAME"<<setw(15)<<"Doctor ID"<<setw(15)<<"Doctor Name"<<setw(15)<<"Date Created"<<setw(15)<<"Date On"<<endl;
                        ADMIN.viewinline_appointment(NEWapp);
                        break;
                    } 
                    case 'E':{
                        int id;
                        while(1){
                            cout<<"---ADMIN PORTAL---"<<endl;
                            cout<<"Enter the Patient ID:"<<endl;
                            cin>>id;
                            if(idcheck(id,patients)){
                                cout<<"CORRECT ID :)";
                                break;
                            }else{
                                cout<<"WRONG ID"<<endl;
                                sleep(1);
                                system("CLS");
                            }

                        }
                        break;
                    }
                    case 'V':{
                        cout<<"---ADMIN PORTAL---"<<endl;
                        cout<<setw(5)<<"PatientID"<<setw(15)<<"Patient NAME"<<setw(15)<<"Doctor ID"<<setw(15)<<"Doctor Name"<<setw(15)<<"Date Created"<<setw(15)<<"Date On"<<setw(5)<<"Appintment status"<<endl;
                        for(int i=0;i<appointments.size();i++){
                            ADMIN.viewinline_appointment(appointments[i]);
                        }
                        break;
                    }
                break;
                }
            break;
            }
            case 'D':{
                    int loginid;
                    doctor *DOC;
                    while(1){
                        cout<<"---DOCTOR PORTAL---"<<endl;
                        cout<<"LOGIN id:"<<endl;
                        cin>>loginid;
                        if(idcheck(loginid,doctors)){
                            cout<<"Login Sucesfull!"<<endl;
                            break;
                        }
                        else{
                            cout<<"Wrong Login Id!"<<endl;
                            sleep(1);
                            system("CLS");
                        }
                    }

                    for(int i=0;i<doctors.size();i++){
                        if(doctors[i].getid() == loginid){
                            DOC = &doctors[i];
                            break;
                        }
                    }

                    sleep(1);
                    system("CLS");
                    char choice1;
                    while(1){
                        cout<<"---DOCTOR PORTAL---"<<endl;
                        cout<<"To View Appoitments enter 'V'\nTo dignose enter 'D'\n"<<endl;
                        cin>>choice1;
                        if(choice1 == 'V' || choice1 == 'D'){
                            break;
                        }else{
                            cout<<"Wrong Entry!"<<endl;
                            sleep(1);
                            system("CLS");
                        }
                    }
                    system("CLS");
                    cout<<"---DOCTOR PORTAL---"<<endl;
                    switch (choice1)
                    {
                    case 'V':{
                        cout<<setw(5)<<"PatientID"<<setw(15)<<"Patient NAME"<<setw(15)<<"Date On:"<<setw(20)<<"Dignose"<<setw(15)<<"Meds"<<endl;
                        for(int i=0;i<appointments.size();i++){
                            if((appointments[i].getdoctor()).getid() == DOC->getid())
                            DOC->viewappointment_byline(appointments[i]);
                            //cout<<"SOMTHING??"<<endl;
                        }
                        //break;
                    }
                    case 'D':{
                        int id;
                        while(1){
                            if(choice1 != 'V')
                                cout<<"---DOCTOR PORTAL---"<<endl;
                            cout<<"Enter the Patient ID to Dignose:"<<endl;
                            cin>>id;
                            if(idcheck(id,patients)){
                                cout<<"CORRECT ID :)\n";
                                break;
                            }else{
                                cout<<"WRONG ID"<<endl;
                                sleep(1);
                                system("CLS");
                            }
                        }
                        appointment *ap;
                        for(int i=0;i<appointments.size();i++){
                            patient p = appointments[i].getpatient();
                            if(p.getid() == id){
                                ap = &appointments[i];
                                if(!(ap->checkappintmentstatus())){
                                    break;
                                }
                                
                            }
                        }
                        if(ap->checkappintmentstatus()){
                            cout<<"Already Diagnose"<<endl;
                        }else{
                        string d;
                        cout<<"Diagnose:\n>>>"<<endl;
                        cin.ignore(200,'\n');
                        getline(cin,d,'\n');
                        DOC->diagnos_patient(*ap,d);
                        cout<<"Succefull Diagnosed"<<endl;
                        }
                        break;
                    }
                    }
                break;
            }
            case 'P':{
                patient *PATIENT;
                int id;
                while(1){
                        cout<<"---Patient PORTAL---"<<endl;
                        cout<<"Enter the Patient ID to Dignose:"<<endl;
                        cin>>id;
                        if(idcheck(id,patients)){
                                cout<<"CORRECT ID :)\n";
                                break;
                        }else{
                                cout<<"WRONG ID"<<endl;
                                sleep(1);
                                system("CLS");
                        }
                    }
                for(int i=0;i<patients.size();i++){
                    if(patients[i].getid() == id){
                        PATIENT = &patients[i];
                        break;
                    }
                }
                PATIENT->view_appointment(appointments);
                break;
            }

        }
        cout<<"Enter To contiune to main menu..."<<endl;
        char c = '\0';
        cin.ignore(1,'\n');
        c = cin.get();
        if(c== '\n'){
            system("CLS");
            continue;
        }
   }
   save_appintments(appointments,appointmentfile);
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
    datetime dt,dtc;
    timestamptodatetime(dtc,A.CREATEDtime);
    timestamptodatetime(dt,A.timeON);
    cout<<endl;
    cout<<"APPOITNMENT INFOMATION @ Day: "<<dt.day<<" Month: "<<monthconverte(dt.mon)<<" Hour:"<<dt.hour<<endl;
    cout<<"Created ON | "<<"Day: "<<dtc.day<<" Month: "<<monthconverte(dtc.mon)<<" Hour:"<<dtc.hour<<endl;
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
void admin::viewinline_appointment(appointment A){
    datetime dO,dC;
    timestamptodatetime(dO,A.timeON); //"Date On(day/month/year| Hour:Min)"
    timestamptodatetime(dC,A.CREATEDtime);//"Date Created(day/month/year)"
    cout<<setw(5)<<A.patientID<<setw(15)<<A.P.name<<setw(15)<<A.doctorID<<setw(15)<<A.D.name<<setw(15)<<dC.day<<"/"<<dC.mon<<"/"<<dC.year<<setw(15)<<dO.day<<"/"<<dO.mon<<"/"<<dO.year<<"| "<<dO.hour<<":"<<dO.min<<setw(5)<<A.checkappintmentstatus()<<endl;
}
void appointment::diagnos(string diagnosi){
    diagnosis = diagnosi;
}
void doctor::viewappointment_byline(appointment A){
    datetime dO; timestamptodatetime(dO,A.timeON);
    cout<<setw(5)<<A.patientID<<setw(15)<<A.P.name<<setw(15)<<dO.day<<"/"<<dO.mon<<"/"<<dO.year<<"| "<<dO.hour<<":"<<dO.min<<setw(20)<<A.diagnosis<<setw(15)<<A.medicine<<endl;
}
string doctor::getPdiagnos(appointment &AP){
    return AP.getdiagnos();
}
void doctor::diagnos_patient(appointment &AP,string D){AP.diagnos(D);}
void doctor::info(){cout<<"ID: "<<id<<"| Name: "<<name<<"| Major: "<<major<<"| PhoneNumber: "<<phonenumber<<endl;}
void patient::info(){cout<<"ID: "<<id<<"| Name: "<<name<<"| Hight: "<<height<<"| Weight: "<<weight<<endl;}
void appointment::confirm(vector<doctor> &doc,vector<patient> &pat){
    bool doctorFound = false, patientFound = false;
    for(int i=0;i<doc.size();i++){
        //cout<<doctorID;
        if(doc[i].id==doctorID){
            doctorFound = true;
            D = doc[i];
            break;
            //cout<<"Doctor Found!\n";
            
        }
    }
        for(int i=0;i<pat.size();i++){
        if(pat[i].id==patientID){
            patientFound = true;
            P = pat[i];
            break;
            //cout<<"Patient Found!\n";
        }
    }
    if (!doctorFound) cout << "Doctor with ID " << doctorID << " not found." << endl;
    if (!patientFound) cout << "Patient with ID " << patientID << " not found." << endl;
}

void patient::view_appointment(vector<appointment> &arr){
    for(int i=0;i<arr.size();i++){
        if((arr[i].getpatient()).getid() == id){
            admin ADMIN;
            ADMIN.view_appointment(arr[i]);
        }
    }
}

bool idcheck(int id,vector<patient> &arr){
    for(int i=0;i<arr.size();i++){
        if(id==arr[i].id){
            return 1;
        }
    }
    return 0;
}

bool idcheck(int id,vector<doctor> &arr){
    for(int i=0;i<arr.size();i++){
        if(id==arr[i].id){
            return 1;
        }
    }
    return 0;
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

// int file_linecount(string filename){
//     fstream fin;
//     int linecount=0;
// 		string temp;
// 		fin.open(filename,ios::in);
// 	while(getline(fin,temp)){linecount++;}
//     fin.close(); return linecount;
// }
void load_doctors(vector<doctor> &doc,string doctorfile){
    fstream fin1;
    fin1.open(doctorfile,ios::in);
    string temp1,line;getline(fin1,temp1);
    while(getline(fin1,line)){
        string name,major,number; int id;
        istringstream iss(line);
        iss>>id;
        iss.ignore(200,',');
        getline(iss,name,',');
        getline(iss,major,',');
        getline(iss,number,',');
        doc.push_back(doctor(id,name,major,number));
    }
}

void load_patients(vector<patient> &pat,string patientfile){
    fstream fin1;
    fin1.open(patientfile,ios::in);
    string temp1;getline(fin1,temp1);string line;
    while(getline(fin1,line)){
        string name;int Height,Weight;int id;
        istringstream iss(line);
        iss>>id;
        iss.ignore(200,',');
        getline(iss,name,',');
        iss>>Height;
        iss.ignore(200,',');
        iss>>Weight;
        pat.push_back(patient(id,name,Height,Weight));
        //pat[i].info();
    }
}
void load_appointments(vector<appointment> &ap ,string appointmentfile,vector<doctor> &doc,vector<patient> &pat){
    fstream fin1;
    fin1.open(appointmentfile,ios::in);
    string temp1;getline(fin1,temp1); int i;string line;
    while(getline(fin1,line)){
        int pID,dID,Otimestamp,Ctimestamp; string dia,med;
        istringstream iss(line);
        iss>>pID;
        iss.ignore(200,',');
        iss>>dID;
        iss.ignore(200,',');
        iss>>Otimestamp;
        iss.ignore(200,',');
        getline(iss,dia,',');
        getline(iss,med,',');
        iss>>Ctimestamp;
        //cout<<pID<<dID<<mon<<day<<hour<<dia<<med;
        appointment newAppointment(pID,dID,Otimestamp,dia,med,Ctimestamp);
        newAppointment.confirm(doc,pat);
        ap.push_back(newAppointment);
        i++;
       //cout<<"CONFIRMED!!\n";
    }
}
void save_appintments(vector<appointment> &ap,string appointmentfile){
    fstream fout;
    fout.open(appointmentfile,ios::out);
    fout<<"patientID,doctorID,Ontimestamp,diagnosis,medicine,Ctimestamp"<<endl;
    for(int i=0;i<ap.size();i++){
        //datetime dt,dtc; timestamptodatetime(dt,ap[i].timeON);timestamptodatetime(dtc,ap[i].CREATEDtime);
        //fout<<ap[i].patientID<<","<<ap[i].doctorID<<","<<dt.mon<<","<<dt.day<<","<<dt.hour<<","<<ap[i].diagnosis<<","<<ap[i].medicine<<","<<dtc.mon<<","<<dtc.day<<","<<dtc.hour<<endl;
        fout<<ap[i].patientID<<","<<ap[i].doctorID<<","<<ap[i].timeON<<","<<ap[i].diagnosis<<","<<ap[i].medicine<<","<<ap[i].CREATEDtime<<endl;
    }
}
