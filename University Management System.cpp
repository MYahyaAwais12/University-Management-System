#include<iostream>
#include<fstream>
using namespace std;

class University {
private:
    string name[100];
    int rollNo[100];
    string dept[100];
    string subjects[100][3];
    float marks[100][3];
    int total;

public:
    University(): total(0){
        cout<<"University System Started\n";
    }

    ~University(){
        cout<<"University System Closed\n";
    }

    void addStudent(){
        int n;
        cout<<"Enter number of students: ";
        cin>>n;

        for(int i=0;i<n;i++){
            cout<<"\nEnter Name: ";
            cin>>name[total];

            cout<<"Enter Roll No: ";
            cin>>rollNo[total];

            cout<<"Enter Department: ";
            cin>>dept[total];

            cout<<"Enter 3 Subjects & Marks\n";
            for(int j=0;j<3;j++){
                cout<<"Subject "<<j+1<<": ";
                cin>>subjects[total][j];

                cout<<"Marks: ";
                cin>>marks[total][j];
            }

            total++;
        }
    }

    float calculateGPA(int i){
        float totalMarks = 0;
        for(int j=0;j<3;j++){
            totalMarks += marks[i][j];
        }

        float avg = totalMarks / 3;

        if(avg >= 85) return 4.0;
        else if(avg >= 70) return 3.0;
        else if(avg >= 50) return 2.0;
        else return 1.0;
    }

    void showAll(){
        for(int i=0;i<total;i++){
            cout<<"\nName: "<<name[i];
            cout<<"\nRoll No: "<<rollNo[i];
            cout<<"\nDept: "<<dept[i];

            for(int j=0;j<3;j++){
                cout<<"\n"<<subjects[i][j]<<": "<<marks[i][j];
            }

            cout<<"\nGPA: "<<calculateGPA(i);
            cout<<"\n----------------------\n";
        }
    }

    void updateStudent(){
        int r;
        cout<<"Enter Roll No: ";
        cin>>r;

        for(int i=0;i<total;i++){
            if(r==rollNo[i]){
                int ch;
                do{
                    cout<<"\n1 Update Name\n";
                    cout<<"2 Update Marks\n";
                    cout<<"3 Exit\n";
                    cout<<"Enter choice: ";
                    cin>>ch;

                    switch(ch){
                        case 1:
                            cout<<"Enter new name: ";
                            cin>>name[i];
                            break;

                        case 2:
                            for(int j=0;j<3;j++){
                                cout<<"Enter marks for "<<subjects[i][j]<<": ";
                                cin>>marks[i][j];
                            }
                            break;
                    }
                }while(ch!=3);
                return;
            }
        }

        cout<<"Student not found\n";
    }

    void studentMenu(int index){
        int ch;
        do{
            cout<<"\n--- STUDENT MENU ---\n";
            cout<<"1 View Info\n";
            cout<<"2 Update Marks\n";
            cout<<"3 Exit\n";
            cout<<"Enter choice: ";
            cin>>ch;

            switch(ch){
                case 1:
                    cout<<"\nName: "<<name[index];
                    cout<<"\nRoll No: "<<rollNo[index];
                    cout<<"\nDept: "<<dept[index];

                    for(int j=0;j<3;j++){
                        cout<<"\n"<<subjects[index][j]<<": "<<marks[index][j];
                    }

                    cout<<"\nGPA: "<<calculateGPA(index)<<endl;
                    break;

                case 2:
                    for(int j=0;j<3;j++){
                        cout<<"Enter marks for "<<subjects[index][j]<<": ";
                        cin>>marks[index][j];
                    }
                    break;
            }

        }while(ch!=3);
    }

    void studentLogin(){
        int r;
        cout<<"Enter Roll No: ";
        cin>>r;

        for(int i=0;i<total;i++){
            if(r==rollNo[i]){
                cout<<"Login Successful\n";
                studentMenu(i);
                return;
            }
        }

        cout<<"Student not found\n";
    }

    void operator+(int bonus){
        for(int i=0;i<total;i++){
            for(int j=0;j<3;j++){
                marks[i][j] += bonus;
            }
        }
        cout<<"Bonus Marks Added!\n";
    }

    void saveToFile(){
        ofstream file("students.txt");

        for(int i=0;i<total;i++){
            file<<name[i]<<" "<<rollNo[i]<<" "<<dept[i]<<" ";

            for(int j=0;j<3;j++){
                file<<subjects[i][j]<<" "<<marks[i][j]<<" ";
            }

            file<<endl;
        }

        file.close();
        cout<<"Data Saved to File\n";
    }

    void adminMenu(){
        int ch;
        do{
            cout<<"\n--- ADMIN MENU ---\n";
            cout<<"1 Add Student\n";
            cout<<"2 Update Student\n";
            cout<<"3 Show All\n";
            cout<<"4 Add Bonus Marks\n";
            cout<<"5 Save Data\n";
            cout<<"6 Exit\n";
            cout<<"Enter choice: ";
            cin>>ch;

            switch(ch){
                case 1:
                    addStudent();
                    break;
                case 2:
                    updateStudent();
                    break;
                case 3:
                    showAll();
                    break;
                case 4:
                    int b;
                    cout<<"Enter bonus marks: ";
                    cin>>b;
                    (*this) + b;
                    break;
                case 5:
                    saveToFile();
                    break;
            }

        }while(ch!=6);
    }

    void adminLogin(){
        string pass;
        cout<<"Enter Admin Password: ";
        cin>>pass;

        if(pass=="admin123"){
            adminMenu();
        } else {
            cout<<"Wrong Password\n";
        }
    }
};

int main(){
    University obj;
    int ch;

    do{
        cout<<"\n===== UNIVERSITY SYSTEM =====\n";
        cout<<"1 Admin\n";
        cout<<"2 Student\n";
        cout<<"3 Exit\n";
        cout<<"Enter choice: ";
        cin>>ch;

        switch(ch){
            case 1:
                obj.adminLogin();
                break;
            case 2:
                obj.studentLogin();
                break;
        }

    }while(ch!=3);

    return 0;
}