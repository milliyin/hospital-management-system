#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include<sstream>
#include<iomanip>
#include <vector>

using namespace std;

class appointment; class admin; class bed;class ward;
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
    patient(vector<patient> &arr,string NAME,double HEIGHT,double WEIGHT){name=NAME;height=HEIGHT;weight=WEIGHT;
    int Hid;
    for(int i=0;i<arr.size();i++){
        if(Hid<arr[i].getid()){
            Hid = arr[i].getid();
        }
    }
    id= Hid+1;
    }
    void info();
    int getid(){return id;}
    friend bool idcheck(int,vector<patient> &arr);
    void view_appointment(vector<appointment> &arr);
    bool operator==(patient &a){
        return (a.id == id);
    }
    friend class admin;
    friend class appointment;
    friend class doctor;
    friend void save_patients(vector<patient> &,string);
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
    void add_meds(appointment &AP,string D);
    string getPdiagnos(appointment &AP);
    void info();
    void viewappointment_byline(appointment);
    friend bool idcheck(int,vector<doctor> &arr);
    friend class admin;
    friend class appointment;
    int getid(){return id;}
    bool operator==(doctor &d){
        return (d.id == id);
    }
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
    void addmeds(string);
    string getdiagnos(){return diagnosis;};
    public:
    bool appintmentclose;
    bool checkappintmentstatus(){if(diagnosis == "" && medicine ==""){appintmentclose = 0;}else{appintmentclose = 1;}return appintmentclose;}
    patient getpatient(){return P;}
    doctor getdoctor(){return D;}
    appointment(){}
     appointment(int Pid,int Did,int month,int day,int hour,string dia,string med){patientID=Pid;doctorID=Did;CREATEDtime=time(NULL);
     timeON=convertToTimestamp(2024,month,day,hour,0,0); diagnosis=dia;medicine=med; if(diagnosis == ""){appintmentclose = 0;}};

    appointment(int Pid,int Did,int Otime,string dia,string med,int ctime){
    patientID=Pid;doctorID=Did;CREATEDtime=ctime;
    timeON=Otime; diagnosis=dia;medicine=med;if(diagnosis == ""){appintmentclose = 0;}
    }
    bool operator==(appointment &app){
        return (app.CREATEDtime == CREATEDtime);
    }
    void confirm(vector<doctor> &,vector<patient> &);
    friend void save_appintments(vector<appointment> &,string appointmentfile);
    friend class admin;
    friend class doctor;
};
class admin{

    public:
    void edit_appointment(appointment &temp,vector<patient> &patients,vector<doctor> &doctors);
    void view_appointment(appointment A);
    void viewinline_appointment(appointment A);
};
class bed{
    private:
    patient *P;
    doctor *D;
    int bednumber;
    public:
    bed(patient *p,doctor *d,int num){P=p;D=d;bednumber=num;}
    bed(int num){P=nullptr;D=nullptr;bednumber=num;}
    void assignPatient(patient* p) {P=p;}
    void assignDoctor(doctor* d) {D=d;}
    patient* getPatient(){ return P; }
    doctor* getDoctor(){ return D; }
    int getBedNumber(){ return bednumber; }
    void dischargePatient() { P = nullptr;D = nullptr;}
    friend void save_ward(ward &W,string wardfile);
};
class ward{
    private:
    vector<bed> beds;
    string wardname;
    int maxbeds=10;
    public:
    ward(string name){
        wardname = name;
        for(int i=0;i<maxbeds;i++){beds.push_back(bed(i));}}
    string getwardname(){return wardname;}
    bed* getbed(int bednum){
        for(int i=0;i<beds.size();i++){
            if(bednum == beds[i].getBedNumber()){
                return &beds[i];
            }
        }
        return nullptr;
    }
    int getbedsize(){return maxbeds;}
    void assignPtobed(patient *p,int bednumber){
        bed *BED = getbed(bednumber);
        if(BED){
            BED->assignPatient(p);

        }
    }
    void assignDtobed(doctor *d,int bednumber){
        bed *BED = getbed(bednumber);
        if(BED){
            BED->assignDoctor(d);
        }
    }
    void dischargePfrombed(int bednum){
        bed *BED = getbed(bednum);
        if(BED){
            BED->dischargePatient();
        }
    }
    void beds_status() {
    cout << setw(10) << "Bed No." << setw(3) << "|" << setw(13) << "Status" << setw(10) << "Patient Id." << endl;
    for (int i = 0; i < beds.size(); i++) {
        bed *BED = getbed(i);
        if (!BED) continue;
        patient *p = BED->getPatient();
        string status = "Empty";
        int pid = -1;
        if (p) {
            status = "Filled";
            pid = p->getid();
        }
        if(pid == -1){cout << setw(10) << BED->getBedNumber() << setw(3) << "|" << setw(13) << status << setw(10) << endl;}else{
        cout << setw(10) << BED->getBedNumber() << setw(3) << "|" << setw(13) << status << setw(10) << pid << endl;}
    }
}

    bool bed_status(int num){
        bed *BED = getbed(num);
        patient *p = BED->getPatient();
        if(p){
            return 1;
        }else{
            return 0;
        }
    }
    bool beds_availability(){
        for(int i=0;i<=beds.size();i++){
            bed *BED = getbed(i);
            patient *p = BED->getPatient();
            if(!p){
                return 1;
            }
        }
        return 0;
    }
    friend void save_ward(ward &W,string wardfile);
};
void sleep(float seconds);
// int file_linecount(string);
void load_doctors(vector<doctor> &,string);
void load_patients(vector<patient> &,string);
void load_appointments(vector<appointment> &,string,vector<doctor> &,vector<patient> &);
void save_appintments(vector<appointment> &,string appointmentfile);
patient* arrgetpatient(vector<patient>,int);
doctor* arrgetdoctor(vector<doctor>,int);
void load_ward(ward &,string,vector<doctor> &,vector<patient> &);
void save_ward(ward &,string);

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

    string wardfile="ward.csv";
    ward emergencyward("emergency");
    load_ward(emergencyward,wardfile,doctors,patients);
    


    while(1){
        char dec;
        while(1){
                cout<<"--LOGIN PAGE--"<<endl<<"As ADMIN enter 'A'\nAs Doctor enter 'D'\nAs Patient Enter P'\n--------\nEnter WARD Press 'E'\n--------\nPress 'Q' to QUITE\n";
                cout<<">>>>";
                cin>>dec;
                if(dec != 'A' && dec != 'D' && dec != 'P' && dec != 'Q' && dec != 'E'){
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
                string pass="123",inpass;
                cout<<"Enter the PASSWORD:";cin.ignore(200,'\n');getline(cin,inpass,'\n');if(!(inpass== pass)){cout<<"WRONG PASSWORD"<<endl;break;}
                char d1 = '\0';
                while(d1 != 'C' && d1 != 'E' && d1 != 'V' && d1 != 'P' && d1 != 'D' && d1 != 'A' && d1 != 'Q'){
                cout<<"---ADMIN PORTAL---"<<endl;
                cout<<"To create appointment enter 'C' \nTo edit appointment enter 'E'\nTo delete appointment enter 'A'\nView All Appointments enter 'V'\nTo Create a new Patient Enter 'P'\nTo Delete Patient Enter 'D'\nExcape this menu Enter 'Q'"<<endl;
                cout<<">>>>";
                cin>>d1;
                if(d1 != 'C' && d1 != 'E' && d1 != 'V' && d1 != 'P' && d1 != 'D' && d1 != 'A' && d1 != 'Q'){
                cout<<"WRONG INPUT"<<endl;
                sleep(1);
                system("CLS");
                } }
                system("CLS");
                if(d1 == 'Q'){
                        save_appintments(appointments,appointmentfile);
                        save_patients(patients,patientfile);
                        save_ward(emergencyward,wardfile);
                    break;}
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
                        cout<<setw(5)<<"PatientID"<<setw(25)<<"PatientName"<<setw(15)<<"DoctorID"<<setw(15)<<"DoctorName"<<setw(20)<<"Date Created"<<setw(20)<<"Date On"<<setw(25)<<"Appintment status"<<endl;
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
                                cout<<"CORRECT ID :)"<<endl;
                                break;
                            }else{
                                cout<<"WRONG ID"<<endl;
                                sleep(1);
                                system("CLS");
                            }
                        }
                        int count = 0;
                         vector<int> counts;
                         vector<appointment> selecteapp;
                         patient *pat=arrgetpatient(patients,id);
                            for(int i=0;i<appointments.size();i++){
                                if(appointments[i].getpatient() == *pat){
                                    cout<<setw(5)<<"NO.\t"<<setw(5)<<"PatientID"<<setw(25)<<"PatientName"<<setw(15)<<"DoctorID"<<setw(15)<<"DoctorName"<<setw(20)<<"Date Created"<<setw(20)<<"Date On"<<setw(25)<<"Appintment status"<<endl;
                                    cout<<setw(5)<<count<<"\t";
                                                        ADMIN.viewinline_appointment(appointments[i]);
                                    selecteapp.push_back(appointments[i]);
                                    counts.push_back(count);
                                    count++;
                                }
                            }
                        int no;
                            while(true){
                            cout<<"Enter the NO. to Edit:\n>>>";
                            cin>>no;
                            bool found = 0;
                            for(int i=0;i<counts.size();i++){
                                if(no == counts[i]){
                                    found = 1;
                                    break;
                                }

                            }
                            if(found){
                                break;
                            }else{
                                cout<<"No. appointment is not avaiable..try again"<<endl;
                            }
                            }
                            // geting the postion value in appointements vector arry..
                            int position;
                            for(int i=0;i<appointments.size();i++){
                                if(selecteapp[no] == appointments[i]){
                                    position = i;
                                }
                            }
                            ADMIN.edit_appointment(appointments[position], patients ,doctors);
                            cout<<endl<<"appointment edited successfully. ";
                        break;
                    }
                    case 'V':{
                        cout<<"---ADMIN PORTAL---"<<endl;
                        cout<<setw(5)<<"PatientID"<<setw(25)<<"PatientName"<<setw(15)<<"DoctorID"<<setw(15)<<"DoctorName"<<setw(20)<<"Date Created"<<setw(20)<<"Date On"<<setw(25)<<"Appintment status"<<endl;
                        for(int i=0;i<appointments.size();i++){
                            ADMIN.viewinline_appointment(appointments[i]);
                        }
                        break;
                    }
                    case 'A':{
                        char option;
                        while(true){
                        cout<<"---ADMIN PORTAL---"<<endl;
                        cout<<"1->Search by Doctor id?\n2->Search by Patient id?\n>>>"<<endl;
                        cin>>option;
                        if(option == '1' || option == '2'){
                            break;
                        }else{
                            cout<<"Wrong Option Selected!"<<endl;
                            sleep(1);
                            system("CLS");
                            continue;
                        }
                        }
                        system("CLS");
                         int count = 0;
                         vector<int> counts;
                         vector<appointment> selecteapp;
                        if(option == '1'){
                            int id;
                            while(1){
                            cout<<"---ADMIN PORTAL---"<<endl;
                            cout<<"Enter the Doctor ID:"<<endl;
                            cin>>id;
                            if(idcheck(id,doctors)){
                                //cout<<"CORRECT ID :)";
                                break;
                            }else{
                                cout<<"WRONG ID!"<<endl;
                                sleep(1);
                                system("CLS");
                            }
                            system("CLS");
                            cout<<"---ADMIN PORTAL---"<<endl;
                            }
                            doctor *doc=arrgetdoctor(doctors,id);
                            for(int i=0;i<appointments.size();i++){
                                if(appointments[i].getdoctor() == *doc){
                                    cout<<setw(5)<<"NO.\t"<<setw(5)<<"PatientID"<<setw(25)<<"PatientName"<<setw(15)<<"DoctorID"<<setw(15)<<"DoctorName"<<setw(20)<<"Date Created"<<setw(20)<<"Date On"<<setw(25)<<"Appintment status"<<endl;
                                    cout<<setw(5)<<count<<"\t";
                                    ADMIN.viewinline_appointment(appointments[i]);
                                    selecteapp.push_back(appointments[i]);
                                    counts.push_back(count);
                                    count++;
                                }
                            }
                            


                        }else if(option =='2'){
                            int id;
                            while(1){
                            cout<<"---ADMIN PORTAL---"<<endl;
                            cout<<"Enter the Patient ID:"<<endl;
                            cin>>id;
                            if(idcheck(id,patients)){
                                //cout<<"CORRECT ID :)";
                                break;
                            }else{
                                cout<<"WRONG ID!"<<endl;
                                sleep(1);
                                system("CLS");
                            }
                            system("CLS");
                            cout<<"---ADMIN PORTAL---"<<endl;
                            }
                            patient *pat=arrgetpatient(patients,id);
                            for(int i=0;i<appointments.size();i++){
                                if(appointments[i].getpatient() == *pat){
                                    cout<<setw(5)<<"NO.\t"<<setw(5)<<"PatientID"<<setw(25)<<"PatientName"<<setw(15)<<"DoctorID"<<setw(15)<<"DoctorName"<<setw(20)<<"Date Created"<<setw(20)<<"Date On"<<setw(25)<<"Appintment status"<<endl;
                                    cout<<setw(5)<<count<<"\t";
                                                        ADMIN.viewinline_appointment(appointments[i]);
                                    selecteapp.push_back(appointments[i]);
                                    counts.push_back(count);
                                    count++;
                                }
                            }
                            }

                            int no;
                            while(true){
                            cout<<"Enter the NO. to Delete:\n>>>";
                            cin>>no;
                            bool found = 0;
                            for(int i=0;i<counts.size();i++){
                                if(no == counts[i]){
                                    found = 1;
                                    break;
                                }

                            }
                            if(found){
                                break;
                            }else{
                                cout<<"No. appointment is not avaiable..try again"<<endl;
                            }
                            }
                            // geting the postion value in appointements vector arry..
                            int position;
                            for(int i=0;i<appointments.size();i++){
                                if(selecteapp[no] == appointments[i]){
                                    position = i;
                                }
                            }
                            // deleting the appintment and confirming it...

                            int tryes=0;
                            while(true){
                            string confirm;
                            cout<<"Are you sure? Enter YES/NO:"<<endl;
                            if(tryes == 0){
                            cin.ignore(200,'\n');}
                            getline(cin,confirm,'\n');
                            if(confirm == "YES"){
                                appointments.erase(appointments.begin()+position);
                                save_appintments(appointments,appointmentfile);
                                cout<<"Successfull Deleted!"<<endl;
                                break;
                            }
                            else if(confirm == "NO"){
                                break;
                            }else{
                                continue;
                            }
                            }

                        

                        break;
                    }
                    case 'P':{
                        cout<<"---ADMIN PORTAL---"<<endl;
                        cout<<"To create patient id, enter the patient name(1/3): "<<endl;
                        string name; double weight,height;
                        cin.ignore(200,'\n');
                        getline(cin,name,'\n');
                        cout<<"Enter the height of the patient(2/3):"<<endl;
                        cin>>height;
                        cout<<"Enter the weight of the patient(3/3):"<<endl;
                        cin>>weight;
                        patient newp(patients,name,height,weight);
                        patients.push_back(newp);
                        cout<<"Sucssfull Created!"<<endl;
                        system("CLS");
                        cout<<"---ADMIN PORTAL---"<<endl;
                        newp.info();
                        save_patients(patients,patientfile);
                        break;
                    }
                    case 'D':{
                        int id;
                        while(1){
                            cout<<"---ADMIN PORTAL---"<<endl;
                            cout<<"Enter the Patient ID to delete:"<<endl;
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
                        int tryes=0;
                        while(true){
                        string confirm;
                        cout<<"Are you sure? Enter YES/NO:"<<endl;
                        if(tryes == 0){
                            cin.ignore(200,'\n');}
                        getline(cin,confirm,'\n');
                            if(confirm == "YES"){
                                for(int i=0;i<appointments.size();i++){
                                    if((appointments[i].getpatient()).getid() == id){
                                        appointments.erase(appointments.begin()+i);
                                    }
                                }
                                for(int i=0;i<patients.size();i++){
                                    if(patients[i].getid() == id){
                                        patients.erase(patients.begin()+i);
                                    }
                                }
                                save_patients(patients,patientfile);
                                save_appintments(appointments,appointmentfile);
                                cout<<"Successfull Deleted!"<<endl;
                                break;
                                
                            }else if(confirm == "NO"){
                                break;
                            }else{
                                continue;
                            }
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
                        cout<<"To View Appoitments enter 'V'\nTo dignose enter 'D'\nExcape this menu enter 'Q'\n"<<endl;
                        cin>>choice1;
                        if(choice1 == 'V' || choice1 == 'D' || choice1 == 'Q'){
                            break;
                        }else{
                            cout<<"Wrong Entry!"<<endl;
                            sleep(1);
                            system("CLS");
                        }
                    }
                    system("CLS");
                    if(choice1 == 'Q'){break;}
                    cout<<"---DOCTOR PORTAL---"<<endl;
                    vector<int> ids;
                    switch (choice1)
                    {
                    case 'V':{
                        cout<<setw(5)<<"PatientID"<<setw(15)<<"Patient NAME"<<setw(15)<<"Date On:"<<setw(20)<<"Dignose"<<setw(15)<<"Meds"<<endl;
                        for(int i=0;i<appointments.size();i++){
                            if((appointments[i].getdoctor()).getid() == DOC->getid()){
                            DOC->viewappointment_byline(appointments[i]);
                            ids.push_back((appointments[i].getpatient()).getid());
                            }
                            //cout<<"SOMTHING??"<<endl;
                        }
                        //break;
                    }
                    case 'D':{
                        if(choice1 =='D'){
                        for(int i=0;i<appointments.size();i++){
                            if((appointments[i].getdoctor()).getid() == DOC->getid()){
                            ids.push_back((appointments[i].getpatient()).getid());
                            }
                        }
                        }
                        int id;
                        while(1){
                            if(choice1 != 'V')
                                cout<<"---DOCTOR PORTAL---"<<endl;
                            cout<<"Enter the Patient ID to Dignose:"<<endl;
                            cin>>id;
                            if(idcheck(id,patients)){
                                //ids checking
                                bool check=0;
                                for(int i=0;i<ids.size();i++){
                                    if(id == ids[i]){check=1;break;}
                                }
                                if(check){
                                cout<<"CORRECT ID :)\n";
                                break;
                                }else{
                                    cout<<"WRONG ID"<<endl;
                                    sleep(1);
                                    system("CLS");
                                }
                            }else{
                                cout<<"WRONG ID"<<endl;
                                sleep(1);
                                system("CLS");
                                // goto case 'D';
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
                        cout<<"Diagnose:\n>>>";
                        cin.ignore(200,'\n');
                        getline(cin,d,'\n');
                        DOC->diagnos_patient(*ap,d);
                        cout<<"Succefull Diagnosed"<<endl;
                        cout<<"Add Meds:\n>>>";
                        string med;
                        getline(cin,med,'\n');
                        DOC->add_meds(*ap,med);
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
                        cout<<"Enter the Patient ID:"<<endl;
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
                PATIENT->info();
                PATIENT->view_appointment(appointments);
                break;
            }
            case 'E':{
                //Ward System
                char input;
                while(true){
                    cout<<"---WARD PORTAL---"<<endl;
                    cout<<"Admit Patient enter 'A'\nView Beds Status 'V'\nDischarge the Patient enter 'D'\nEscape this page enter 'Q'\n>>>"<<endl;
                    cin>>input;
                    if(input != 'A' && input != 'V' && input != 'D' && input != 'Q'){
                        cout<<"Wrong Input."<<endl;
                        sleep(1);
                        system("CLS");
                    }else{
                        break;
                    }
                }
                system("CLS");
                if(input == 'Q'){break;}
                switch(input){
                    case 'A':{
                        
                        if(emergencyward.beds_availability()){
                                    patient *PATIENT;
                                    int id;
                                    while(1){
                                            cout<<"---WARD PORTAL---"<<endl;
                                            cout<<"Enter the Patient ID(1/3):"<<endl;
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
                                system("CLS");
                                int bednum;
                                while(1){
                                    cout<<"---WARD PORTAL---"<<endl;
                                    cout<<"Enter the bed No(2/3):"<<endl;
                                    cin>>bednum;
                                    if(!(emergencyward.bed_status(bednum))){
                                        break;
                                    }else{
                                        cout<<"This bed is occupied"<<endl;
                                        sleep(1);
                                        system("CLS");
                                        continue;
                                    }
                                }
                                system("CLS");
                                int loginid;
                                doctor *DOC;
                                while(1){
                                    cout<<"---WARD PORTAL---"<<endl;
                                    cout<<"Enter the Doctor ID:"<<endl;
                                    cin>>loginid;
                                    if(idcheck(loginid,doctors)){
                                        break;
                                    }
                                    else{
                                        cout<<"Wrong ID!"<<endl;
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
                                cout<<"---WARD PORTAL---"<<endl;
                                emergencyward.assignPtobed(PATIENT,bednum);
                                emergencyward.assignDtobed(DOC,bednum);
                                cout<<"Succfull Admited!"<<endl;
                        }else{
                            cout<<"---WARD PORTAL---"<<endl;
                            cout<<"All bed is occupied!"<<endl;
                            sleep(1);
                            break;
                        }
                        break;
                    }
                    case 'V':{
                        emergencyward.beds_status();
                        // sleep(1);
                        break;
                    }
                    case 'D':{
                            int bednum;
                                while(1){
                                    cout<<"---WARD PORTAL---"<<endl;
                                    cout<<"Enter the bed No to discharge:"<<endl;
                                    cin>>bednum;
                                    if(!(emergencyward.bed_status(bednum))){
                                        cout<<"This bed is not occupied"<<endl;
                                        sleep(1);
                                        system("CLS");
                                        continue;
                                        
                                    }else{
                                        emergencyward.dischargePfrombed(bednum);
                                        cout<<"Succefull Discharged!"<<endl;
                                        break;
                                    }
                            }
                        break;
                    }

                }
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
    save_appintments(appointments,appointmentfile);
   save_patients(patients,patientfile);
   save_ward(emergencyward,wardfile);
   }

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
    cout<<setw(5)<<A.patientID<<setw(25)<<A.P.name<<setw(15)<<A.doctorID<<setw(15)<<A.D.name<<setw(15)<<dC.day<<"/"<<dC.mon<<"/"<<dC.year<<setw(15)<<dO.day<<"/"<<dO.mon<<"/"<<dO.year<<"| "<<dO.hour<<":"<<dO.min<<setw(5)<<A.checkappintmentstatus()<<endl;
}
void appointment::diagnos(string diagnosi){
    diagnosis = diagnosi;
}
void appointment::addmeds(string meds){
    medicine = meds;
}

void doctor::viewappointment_byline(appointment A){
    datetime dO; timestamptodatetime(dO,A.timeON);
    cout<<setw(5)<<A.patientID<<setw(15)<<A.P.name<<setw(15)<<dO.day<<"/"<<dO.mon<<"/"<<dO.year<<"| "<<dO.hour<<":"<<dO.min<<setw(20)<<A.diagnosis<<setw(15)<<A.medicine<<endl;
}
string doctor::getPdiagnos(appointment &AP){
    return AP.getdiagnos();
}
void doctor::diagnos_patient(appointment &AP,string D){AP.diagnos(D);}
void doctor::add_meds(appointment &AP,string D){AP.addmeds(D);}


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

inline string monthconverte(int mo){
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
        appointment newAppointment(pID,dID,Otimestamp,dia,med,Ctimestamp);
        newAppointment.confirm(doc,pat);
        ap.push_back(newAppointment);
        i++;
    }
}
void load_ward(ward &W,string wardfile,vector<doctor> &doc,vector<patient> &pat){
    fstream fin1;
    fin1.open(wardfile,ios::in);
    string temp1;getline(fin1,temp1); int i=0;string line;
        while(getline(fin1,line)){
            int BEDno,pID,dID;
            istringstream iss(line);
            iss>>BEDno;
            iss.ignore(200,',');
            iss>>pID;
            iss.ignore(200,',');
            iss>>dID;
            //geting p and d
            if(pID){
                for(int i=0;i<pat.size();i++){
                    if(pat[i].getid() == pID){
                      W.assignPtobed(&pat[i],BEDno);
                      break;
                }
                }
                 for(int i=0;i<doc.size();i++){
                    if(doc[i].getid() == dID){
                      W.assignDtobed(&doc[i],BEDno);
                      break;
                }
                }               
            //cout<<"bed no "<<BEDno<<" SUccefull loaded!"<<W.bed_status(BEDno)<<endl;
            }else{
              //cout<<"BED no "<<BEDno<<" did't load"<<endl;
            }
            i++;
        }
}
void save_appintments(vector<appointment> &ap,string appointmentfile){
    fstream fout;
    fout.open(appointmentfile,ios::out);
    fout<<"patientID,doctorID,Ontimestamp,diagnosis,medicine,Ctimestamp"<<endl;
    for(int i=0;i<ap.size();i++){
       fout<<ap[i].patientID<<","<<ap[i].doctorID<<","<<ap[i].timeON<<","<<ap[i].diagnosis<<","<<ap[i].medicine<<","<<ap[i].CREATEDtime<<endl;
    }
}
void save_ward(ward &W, string wardfile) {
    fstream fout;
    fout.open(wardfile, ios::out);
    fout << "bedno,patientID,doctorID" << endl;

    for (int i = 0; i < W.getbedsize(); i++) {
        bed *BED = W.getbed(i);
        patient* Patient = BED->getPatient();
        doctor* Doctor = BED->getDoctor();
        
        int patid = -1, docid = -1;
        
        if (Patient != nullptr) {
            patid = Patient->getid();
        }
        if (Doctor != nullptr) {
            docid = Doctor->getid();
        }

        fout << i << ",";

        if (patid != -1) {
            fout << patid;
        }
        
        fout << ",";

        if (docid != -1) {
            fout << docid;
        }
        
        fout << endl;
    }

    fout.close();
}
void save_patients(vector<patient> &pat,string patfile){
    fstream fout;
    fout.open(patfile,ios::out);
    fout<<"ID,Name,Height,Weight"<<endl;
    for(int i=0;i<pat.size();i++){
        fout<<pat[i].id<<","<<pat[i].name<<","<<pat[i].height<<","<<pat[i].weight<<endl;
    } 
}

patient* arrgetpatient(vector<patient> arr,int id){
    for(int i=0;i<arr.size();i++){
        if(arr[i].getid() == id){
            return &arr[i];
        }
    }
    return nullptr;
}
doctor* arrgetdoctor(vector<doctor> arr,int id){
    for(int i=0;i<arr.size();i++){
        if(arr[i].getid() == id){
            return &arr[i];
        }
    }
    return nullptr;
}
void admin :: edit_appointment(appointment &temp,vector<patient> &patients,vector<doctor> &doctors){
    char t;
    cout<<"\nTo edit patient ID, P\nTo edit doctor ID, D\nTo edit time of appointment, T\nTo edit diagnosis, A\nTo edit medicine, M\nTo edit all, B"<<endl;
    cin>>t;
    switch(t){
        case 'P':{
            int id;
            cout<<"enter patient id; ";
            cin>>id;
            if(idcheck(id,patients)){
                temp.patientID=id;
            }
            else {
                cout<<endl<<"ID already taken."<<endl;
            }
            temp.confirm(doctors,patients);
            break;
        } 
        case 'D':{
            int id;
            cout<<endl<<"enter doctor id; "<<endl;
            cin>>id;
            if(idcheck(id,doctors)){
                temp.doctorID=id;
            }
            else {
                cout<<endl<<"ID already taken."<<endl;
            }

        temp.confirm(doctors,patients);
            break;
        }
        case 'T':{
            int hour,month,day;
            bool check=1;
            
            while(check){
            cout<<"enter month; ";
            cin>>month;
            if(month<=12){
                check=0;
            }
            else {
                cout<<"wrong input \ntry again\n";
            }}
        
            check=1;
             while(check){
            cout<<endl<<"enter day; ";
            cin>>day;
            if(day<=31){
                check=0;
            }
            else {
                cout<<"wrong input \ntry again\n";
            }}
            
             check=1;
             while(check){
             cout<<"enter hours; ";
             cin>>hour;
            if(hour<=24){
                check=0;
            }
            else {
                cout<<"wrong input \ntry again\n";
            }}
    
            temp.timeON=convertToTimestamp(2024,month,day,hour,0,0);
            temp.confirm(doctors,patients);
            break;
        }
        case 'A':{
            cout<<endl<<"enter diagnosis; ";
            cin>>temp.diagnosis;
            temp.confirm(doctors,patients);
            break;
        }
        case 'M':{
            cout<<endl<<"enter medicine; ";
            cin>>temp.medicine;
            temp.confirm(doctors,patients);
            break;
        }
        case 'B':{
            
            cout<<"enter patient id; ";
            cin>>temp.patientID;
            
            cout<<endl<<"enter doctor id; ";
            cin>>temp.doctorID;
            
            cout<<endl<<"enter time of appointment; ";
            cin>>temp.timeON;
            
            cout<<endl<<"enter diagnosis; ";
            cin>>temp.diagnosis;
            
            cout<<endl<<"enter medicine; ";
            cin>>temp.medicine;
            temp.confirm(doctors,patients);
            break;
            }
    }

   }