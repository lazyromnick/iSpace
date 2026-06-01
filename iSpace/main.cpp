#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iomanip>
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
void auth(Officer* officers, Faculty* faculty, int size, int& role, int& officerCount, int& facultyCount);
void askRole(Officer* officers, Faculty* faculty, int size, int& role, int& officerCount, int& facultyCount);
void createAccount(Officer* officers, Faculty* faculty, int size, int role, int& officerCount, int& facultyCount);
string createPasscode();
void saveAccountToCSV(Officer* officers, Faculty* faculty, int role, int count, string file);
void login(Officer* officers, Faculty* faculty, int size, int role, int& officerCount, int& facultyCount);
void officerLogin(Officer* officers, Faculty* faculty, int size, int role, int& officerCount, int& facultyCount);
void facultyLogin(Officer* officers, Faculty* faculty, int size, int role, int& officerCount, int& facultyCount);

/// utility function
void pauseScreen();
void clScreen();
void enterPrompt(string prompt, string& val, int width = 0);
void enterPrompt(string prompt, int& val, int width = 0);
bool isEmpty(string str);
void loadIDPassFromFile(Officer* tempOfficer, int& count);
void loadIDPassFromFile(Faculty* tempFaculty, int& count);
bool idpassNotFound(bool& var, int& attempt, string displayMessage);

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

/// opening files csv
ifstream officerFile("officers.csv");
ifstream facultyFile("faculty.csv");

int main(){
    Officer officers[MAX_OFFICER];
    Faculty faculty[MAX_FACULTY];

    int role         = 0;
    int officerCount = 0;
    int facultyCount = 0;

    displayHeader();
    auth(officers, faculty, MAX_OFFICER, role, officerCount, facultyCount);

    return 0;
}

/// function definition

void displayHeader(){
    SetConsoleOutputCP(CP_UTF8);
    cout << "+---------------------------------------------------------+\n";
    cout << "|__________________--✨ iSPACE PORTAL ✨--________________|\n";
    cout << "|               IBITS Portal for Announcements,           |\n";
    cout << "|                 Communication and Events                |\n";
    cout << "+---------------------------------------------------------+\n";
}

void auth(Officer* officers, Faculty* faculty, int size, int& role, int& officerCount, int& facultyCount){
    if(officerFile.is_open() || facultyFile.is_open()){
        SetConsoleOutputCP(CP_UTF8);
        cout << right << setw(55) << "\n[📂] File successfully opened\n";

        char hasAccount;
        cout << "\nAlready have an account? (Y/N): ";
        cin >> hasAccount;
        cin.ignore();

        if(hasAccount == 'Y' || hasAccount == 'y'){
            // go to login
            login(officers, faculty, size, role, officerCount, facultyCount);

        } else {
            // ask role
            askRole(officers, faculty, size, role, officerCount, facultyCount);
        }
    } else {
        cout << "\n\n" << right << setw(55) << "[!] File doesn't exist yet. Start your account.\n\n";
        pauseScreen();

        // ask for role
        askRole(officers, faculty, size, role, officerCount, facultyCount);
    }
}

void askRole(Officer* officers, Faculty* faculty, int size, int& role, int& officerCount, int& facultyCount){
    system("cls");
    displayHeader();
    SetConsoleOutputCP(CP_UTF8);
    cout << "\n" << right << setw(36) << " ---------------";
    cout << "\n" << right << setw(42) << "🚀>>> Roles <<<🚀\n";
    cout << right << setw(37) << " ---------------\n";

    SetConsoleOutputCP(CP_UTF8);
    cout << "\n[1-👩‍🚀] Student \n[2-🧑‍🎓]️Officer \n[3-🧑‍🏫] Faculty";
    enterPrompt("\n\nEnter role: ", role);

    while(role > 3){
        cout << "\n[!] Invalid role. Select only from role choices.\n";
        enterPrompt("\n\nEnter role: ", role);
    }

    switch(role){
        case 1:
            // ask for credentials, go to login
            break;

        case 2:
            createAccount(officers, faculty, size, role, officerCount, facultyCount);
            login(officers, faculty, size, role, officerCount, facultyCount);
            break;

        case 3:
            createAccount(officers, faculty, size, role, officerCount, facultyCount);
            login(officers, faculty, size, role, officerCount, facultyCount);
            break;

        default:
            cout << "\n[!] Invalid role. Select only from choices.\n";
    }
}

void createAccount(Officer* officers, Faculty* faculty, int size, int role, int& officerCount, int& facultyCount){
    system("cls");
    displayHeader();
    SetConsoleOutputCP(CP_UTF8);
    cout << "\n" << right << setw(49) << "📋 >>> Create Account <<< 📋\n";
    cout << right << setw(43) <<" Enter required details.\n";

    if(role == 2){
        SetConsoleOutputCP(CP_UTF8);
        cout << "\n-----------------------------------------------------------\n";
        cout << right << setw(40) << ">>> Role: Officer <<<" << "\n";
        cout << "-----------------------------------------------------------\n\n";

        enterPrompt("🆔 Enter ID: ",officers[officerCount].ID,26);
        enterPrompt("👤 Enter Name: ",officers[officerCount].name,26);

        enterPrompt("💻 Enter Program: ",officers[officerCount].program,  26);
        while(officers[officerCount].program != "BSIT" && officers[officerCount].program != "DIT"  &&
              officers[officerCount].program != "bsit" && officers[officerCount].program != "dit"){
            cout << "\n[!] Program must be BSIT or DIT only.\n\n";
            enterPrompt("💻 Enter Program: ", officers[officerCount].program, 26);
        }

        enterPrompt("📈 Enter Year Level: ",officers[officerCount].yearLevel,26);
        while(officers[officerCount].yearLevel >= 5){
            cout << "\n[!] Valid year level are Years 1 to 4 only.\n\n";
            enterPrompt("📈 Enter Year Level: ",officers[officerCount].yearLevel,26);
        }

        enterPrompt("🎖️ Enter Position: ",officers[officerCount].position,26);

        officers[officerCount].passcode = createPasscode();

        saveAccountToCSV(officers, faculty, role, officerCount, "officers.csv");

        // update account counter tracker
        officerCount++;

    } else if(role == 3){
        SetConsoleOutputCP(CP_UTF8);
        cout << "\n-----------------------------------------------------------\n";
        cout << right << setw(39) << ">>> Role: Faculty <<<" << "\n";
        cout << "-----------------------------------------------------------\n\n";

        enterPrompt("🆔 Enter ID: ",   faculty[facultyCount].ID,   25);
        enterPrompt("👤 Enter Name: ", faculty[facultyCount].name, 25);

        faculty[facultyCount].passcode = createPasscode();

        saveAccountToCSV(officers, faculty, role, facultyCount, "faculty.csv");

        // update account counter tracker
        facultyCount++;
    }
}

string createPasscode(){
    cout << "\n-----------------------------------------------------------\n";
    cout <<  right << setw(45) << "*** Create your passcode ***\n";
    cout << right << setw(60) <<"\033[3m📌 Note: Passcode must be minimum of characters\033[0m" << "\n";
    cout << "-----------------------------------------------------------\n\n";

    string passcode = "";
    enterPrompt("🔑 Enter passcode: ", passcode);
    while(passcode.length() < 8){
        cout << "\n[!] Must be 8 or more characters.\n";
        enterPrompt("\n🔑 Enter passcode: ", passcode);
    }

    string confirm = "";
    enterPrompt("🔄 Confirm passcode: ", confirm);
    while(confirm != passcode){
        cout << "\n[!] Wrong passcode. Try again.\n";
        enterPrompt("\n🔄 Confirm passcode: ", confirm);
    }

    cout << "\n[🔒] Passcode created.\n";
    return passcode;
}

void saveAccountToCSV(Officer* officers, Faculty* faculty, int role, int count, string file){
    ofstream outFile;

    outFile.open(file, ios::app);

    if(outFile.is_open()){
        if(role == 2){
            outFile << officers[count].ID << ',';
            outFile << officers[count].name << ',';
            outFile << officers[count].program << ',';
            outFile << officers[count].yearLevel << ',';
            outFile << officers[count].position << ',';
            outFile << officers[count].passcode << endl;
        } else if(role == 3){
            outFile << faculty[count].ID   << ',';
            outFile << faculty[count].name << ',';
            outFile << faculty[count].passcode << endl;
        }

        cout << "\n[/] Information saved to csv.\n";
    }

    outFile.close();
}

void login(Officer* officers, Faculty* faculty, int size, int role, int& officerCount, int& facultyCount){
    pauseScreen();
    clScreen();
    displayHeader();

    //babaguhin mo ui dito for log in
    cout << "\n============== >>> Login to your account <<< ==============\n";
   // cout << "|" << right << setw(45) << ">>> Login to your account <<< " << right << setw(14) << "| \n";


    // officers login
    string id   = "";
    string pass = "";

    cout << "\n[1-👩‍🚀] Student \n[2-🧑‍🎓]️Officer \n[3-🧑‍🏫] Faculty";
    enterPrompt("\n\nEnter role: ", role);

    while(role > 3){
        cout << "[!] Invalid role. Select only from role choices.\n";
        enterPrompt("\n\nEnter role: ", role);
    }

    if(role == 1){
        // student login
    } else if(role == 2){
        system("cls");
        displayHeader();
        cout << "\n============== >>> Login to your account <<< ==============\n";
        cout << "\n                   ==> Role: Officer <==\n";
        officerLogin(officers,faculty,size,role,officerCount,facultyCount);
    } else if(role == 3){
        system("cls");
        displayHeader();
        cout << "\n============== >>> Login to your account <<< ==============\n";
        cout << "\n                   ==> Role: Faculty <==\n";
        facultyLogin(officers,faculty,size,role,officerCount,facultyCount);
    }
}

void officerLogin(Officer* officers, Faculty* faculty, int size, int role, int& officerCount, int& facultyCount) {
    string id   = "";
    string pass = "";

    Officer* tempOfficer = new Officer[MAX_OFFICER];
    int loadedCount = 0;

    loadIDPassFromFile(tempOfficer, loadedCount);

    // matching loop validation checks
    bool idFound   = false;
    bool passFound = false;
    int  attempt   = 0;

    // ID Validation Loop
    while(!idFound){
        enterPrompt("\n🪪 Enter ID: ", id);

        for(int j = 0; j < loadedCount; j++){
            if(tempOfficer[j].ID == id){
                idFound = true;
                break;
            }
        }

        // If idpassNotFound returns TRUE, it means the user chose 'N' and needs a redirect
        if(idpassNotFound(idFound, attempt, "[!] ID Not Found. Try again\n")) {
            createAccount(officers, faculty, size, role, officerCount, facultyCount);
            delete[] tempOfficer;
            return;
        }
    }

    attempt = 0;

    // Passcode Validation Loop
    while(!passFound){
        enterPrompt("🔑 Enter passcode: ", pass);

        for(int j = 0; j < loadedCount; j++){
            if(tempOfficer[j].ID == id && tempOfficer[j].passcode == pass){
                passFound = true;
                break;
            }
        }

        // Same thing here: redirect only if the helper function returns TRUE
        if(idpassNotFound(passFound, attempt, "[!] Wrong passcode\n")) {
            createAccount(officers, faculty, size, role, officerCount, facultyCount);
            delete[] tempOfficer;
            return;
        }
    }

    cout << "\n[/] Login Successful!\n";
    delete[] tempOfficer;
}

void facultyLogin(Officer* officers, Faculty* faculty, int size, int role, int& officerCount, int& facultyCount) {
    string id   = "";
    string pass = "";

    Faculty* tempFaculty = new Faculty[MAX_FACULTY];
    int loadedCount = 0;

    loadIDPassFromFile(tempFaculty, loadedCount);

    // matching loop validation checks
    bool idFound   = false;
    bool passFound = false;
    int  attempt   = 0;

    // ID Validation Loop
    while(!idFound){
        enterPrompt("\n🪪 Enter ID: ", id);

        for(int j = 0; j < loadedCount; j++){
            if(tempFaculty[j].ID == id){
                idFound = true;
                break;
            }
        }

        // If idpassNotFound returns TRUE, it means the user chose 'N' and needs a redirect
        if(idpassNotFound(idFound, attempt, "[!] ID Not Found. Try again\n")) {
            createAccount(officers, faculty, size, role, officerCount, facultyCount);
            delete[] tempFaculty;
            return;
        }
    }

    attempt = 0;

    // Passcode Validation Loop
    while(!passFound){
        enterPrompt("🔑 Enter passcode: ", pass);

        for(int j = 0; j < loadedCount; j++){
            if(tempFaculty[j].ID == id && tempFaculty[j].passcode == pass){
                passFound = true;
                break;
            }
        }

        // Same thing here: redirect only if the helper function returns TRUE
        if(idpassNotFound(passFound, attempt, "[!] Wrong passcode\n")) {
            createAccount(officers, faculty, size, role, officerCount, facultyCount);
            delete[] tempFaculty;
            return;
        }
    }

    cout << "\n[/] Login Successful!\n";
    delete[] tempFaculty;
}

void loadIDPassFromFile(Officer* tempOfficer, int& count){
    // reset file flags and seek cursor back to top
    officerFile.clear();
    officerFile.seekg(0, ios::beg);

    string line, ignore;
    count = 0;

    while(getline(officerFile, line)){
        stringstream ss(line);

        getline(ss, tempOfficer[count].ID,      ',');
        getline(ss, ignore,                     ',');
        getline(ss, ignore,                     ',');
        getline(ss, ignore,                     ',');
        getline(ss, ignore,                     ',');
        getline(ss, tempOfficer[count].passcode     );

        count++;
    }
}

void loadIDPassFromFile(Faculty* tempFaculty, int& count){
    // reset file flags and seek cursor back to top
    facultyFile.clear();
    facultyFile.seekg(0, ios::beg);

    string line, ignore;
    count = 0;

    while(getline(facultyFile, line)){
        stringstream ss(line);

        getline(ss, tempFaculty[count].ID,      ',');
        getline(ss, ignore,                     ',');
        getline(ss, tempFaculty[count].passcode     );

        count++;
    }
}

bool idpassNotFound(bool& var, int& attempt, string displayMessage){
    if(!var){
        cout << displayMessage;
        attempt++;

        if(attempt == 3){
            char hasAccount;
            cout << "\nIt seems that ID doesn't exist. Do you really have an account? (Y/N): ";
            cin >> hasAccount;
            cin.ignore();

            if(hasAccount == 'N' || hasAccount == 'n'){
                cout << "\n[!] Redirecting to Create Account. Please wait...\n";
                Sleep(2000);
                return true; // SIGNAL: Yes, redirect to Create Account
            } else {
                // User insists they have an account! Reset attempts so they can try logging in again
                cout << "\n[!] Resetting login attempts. Please double-check your input.\n";
                attempt = 0;
                return false; // SIGNAL: Do NOT redirect, let the loop continue
            }
        }
    }
    return false; // SIGNAL: Normal failure or field matches, do not redirect
}

/// utility function definition
void pauseScreen(){
    cout << "\n";
    system("pause");
}

void clScreen(){
    system("cls");
}

// overloading - get user input
void enterPrompt(string prompt, string& val, int width){
    do{
        cout << left << setw(width) << prompt;
        getline(cin, val);
    } while(isEmpty(val));
}

void enterPrompt(string prompt, int& val, int width){
    do{
        cout << left << setw(width) << prompt;
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
