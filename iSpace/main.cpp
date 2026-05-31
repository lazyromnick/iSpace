#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>
using namespace std;


struct Officer {
    string ID;
    string name;
    string program;
    int yearLevel;
    string position;
    string passcode;
};

struct Faculty {
    string ID;
    string name;
    string passcode;
};

const string pos[50];

const int MAX_OFFICER = 50;
const int MAX_FACULTY = 10;

void displayHeader();
void auth(Officer* officers, Faculty* faculty, int size, int& role, int& officerCount);
void askRole(Officer* officers, Faculty* faculty, int size, int& role, int& count);
void createAccount(Officer* officers, Faculty* faculty, int size, int role, int& count);
string createPasscode();

/// utility function
void pauseScreen();
void enterPrompt(string prompt, string& val);
void enterPrompt(string prompt, int& val);
bool isEmpty(string str);

/// utility function template
template <typename T>
T isValidDigit(T digit){
    if(!digit){
        cout << "Please enter a valid value.\n";
        cin.clear();
        cin.ignore(1000,'\n');
        return true;
    }
    cin.ignore();
    return false;
}

int main(){
    Officer officers[MAX_OFFICER];
    Faculty faculty[MAX_FACULTY];

    int role = 0;
    int officerCount = 0;

    displayHeader();
    auth(officers,faculty,MAX_OFFICER,role,officerCount);

    return 0;
}

/// function definition

void displayHeader(){
    cout << "+---------------------------------------------------------+\n";
    cout << "|_________________________iSPACE:_________________________|\n";
    cout << "|              IBITS Portal for Announcements,            |\n";
    cout << "|                 Communication, and Events               |\n";
    cout << "+---------------------------------------------------------+\n";
}

void auth(Officer* officers, Faculty* faculty, int size, int& role, int& officerCount){
    ifstream inFile("officers.csv");

    if(inFile.is_open()){
        cout << "\n[/] officers.csv successfully opened.\n";

        char hasAccount;
        cout << "\nAlready have an account? (Y/N): ";
        cin >> hasAccount;
        cin.ignore();

        if(hasAccount == 'Y' || hasAccount == 'y'){
            // go to login
        } else {
            // ask role
            askRole(officers,faculty,size,role,officerCount);
        }
    } else {
        cout << "[!] File doesn't exist yet. Start your account.\n";
        pauseScreen();

        // ask for role
        askRole(officers,faculty,size,role,officerCount);
    }
}

void askRole(Officer* officers, Faculty* faculty, int size, int& role, int& count){
    cout << "\nRoles: 1 = Student, 2 = Officer, 3 = Faculty";
    cout << "\n\nEnter your role: ";
    cin >> role;
    cin.ignore();

    switch(role){
        case 1:
            // ask for credentials, go to login
            break;

        case 2:
            createAccount(officers,faculty,size,role,count);
            break;

        case 3:
            createAccount(officers,faculty,size,role,count);
            break;

        default:
            cout << "\n[!] Invalid role. Select only from choices.\n";
    }
}

void createAccount(Officer* officers, Faculty* faculty, int size, int role, int& count){
    cout << "\n-----------------------\n";
    cout << "Create Account\n";
    cout << "Enter required details.\n";

    if(role == 2){
        cout << "\nRole: Officer\n\n";

        enterPrompt("Enter ID: ",officers[count].ID);
        enterPrompt("Enter Name: ",officers[count].name);

        enterPrompt("Enter Program: ",officers[count].program);
        while(officers[count].program != "BSIT" && officers[count].program != "DIT" &&
              officers[count].program != "bsit" && officers[count].program == "dit"){
            cout << "\n[!] Program must be BSIT or DIT only.\n";
            enterPrompt("Enter Program: ",officers[count].program);
        }

        enterPrompt("Enter Year Level: ",officers[count].yearLevel);
        while(officers[count].yearLevel >= 5){
            cout << "\n[!] Valid year level are Years 1 to 4 only.\n";
            enterPrompt("Enter Year Level: ",officers[count].yearLevel);

        }

        enterPrompt("Enter Position: ",officers[count].position);

        officers[count].passcode = createPasscode();
    } else if(role == 3){
        cout << "\nRole: Faculty\n\n";

        enterPrompt("Enter ID: ",faculty[count].ID);
        enterPrompt("Enter Name: ",faculty[count].name);

        faculty[count].passcode = createPasscode();
    }
}

string createPasscode(){
    cout << "\n-----------------------\n";
    cout << "Create your passcode.\n";
    cout << "\033[3mNote: Passcode must be minimum of characters\033[0m\n";

    string passcode = "";
    enterPrompt("\nEnter passcode: ",passcode);
    while(passcode.length() < 8){
        cout << "\n[!] Must be 8 or more characters.\n\n";
        enterPrompt("\nEnter passcode: ",passcode);
    }

    string confirm = "";
    enterPrompt("\nConfirm passcode: ",confirm);
    while(confirm != passcode){
        cout << "\n[!] Wrong passcode. Try again.\n";
        enterPrompt("\nConfirm passcode: ",confirm);
    }

    cout << "\n[/] Passcode created. Proceed to login.\n";
    return passcode;
}

/// utility function definition
void pauseScreen(){
    cout << "\n";
    system("pause");
}

// overloading - get user input
void enterPrompt(string prompt, string& val){  // string input
    do{
        cout << prompt;
        getline(cin, val);
    }while(isEmpty(val));
}

void enterPrompt(string prompt, int& val){
    do{
        cout << prompt;
        cin >> val;
    } while(isValidDigit(val));
}

bool isEmpty(string str){
    if(str.empty()){
        cout << "\n[!] Please fill in this field.\n" << endl;
        return true;
    }
    return false;
}
