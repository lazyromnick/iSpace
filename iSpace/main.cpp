#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iomanip>
using namespace std;

struct Student {
    string ID;
    string name;
    string program;
    int yearLevel;
    string passcode;
};

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

const int MAX_STUDENT = 200;
const int MAX_OFFICER = 50;
const int MAX_FACULTY = 10;

void displayHeader();
void displayHeader2();

// authentication
void auth(Officer* officers, Faculty* faculty, int& role, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn);
void askRole(int& role);
void roleSwitch(Officer* officers, Faculty* faculty, int& role, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn);
void createAccount(Officer* officers, Faculty* faculty, int role, int& officerCount, int& facultyCount);
string createPasscode();
void saveAccountToCSV(string file, Student* students, int studentCount);  // overloading - student
void saveAccountToCSV(string file, Officer* officers, int officerCount);  // overloading - officer
void saveAccountToCSV(string file, Faculty* faculty, int facultyCount);   // overloading - faculty
void login(Officer* officers, Faculty* faculty, int& role, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn);
void officerLogin(Officer* officers, Faculty* faculty, int role, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn);
void facultyLogin(Officer* officers, Faculty* faculty, int role, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn);
void loadIDPassFromFile(Officer* tempOfficer, int& count);
void loadIDPassFromFile(Faculty* tempFaculty, int& count);
bool idpassNotFound(bool& var, int& attempt, string displayMessage);
void displayWelcome(string name);

// officer module
void officerMenu();
void officerSwitch(int choice,Student* students, int& studentCount);
void memberManagement(Student* students, int& studentCount);
/* managements holder */
void announcementManagement();
void activityManagement();
void searchFunction();
/* member management */
void addMember(Student* students, int& studentCount);

// faculty module
void facultyMenu();

/// utility function
void pauseScreen();
void clScreen();
void enterPrompt(string prompt, string& val, int width = 0);
void enterPrompt(string prompt, int& val, int width = 0);
void enterChoice(string prompt, int& val);
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

/// opening files csv
    ifstream studentFile("students.csv");
    ifstream officerFile("officers.csv");
    ifstream facultyFile("faculty.csv");

/// main function
int main(){
    Student students[MAX_STUDENT];
    Officer officers[MAX_OFFICER];
    Faculty faculty[MAX_FACULTY];

    int role = 0;
    int studentCount = 0;
    int officerCount = 0;
    int facultyCount = 0;
    int accIndex = 0;
    int choice = 0;

    srand(time(0));

    // Load data from files directly into the main arrays at startup
    loadIDPassFromFile(officers, officerCount);
    loadIDPassFromFile(faculty, facultyCount);

    displayHeader();

    bool isLoggedIn = false;
    auth(officers, faculty, role, officerCount, facultyCount, accIndex, isLoggedIn);

    if(isLoggedIn){
        switch(role){
            case 1:
            //student
            break;

            case 2:
                // officer module
                clScreen();

                do{
                    //displayHeader();
                    displayHeader2();
                    officerMenu();
                    enterChoice("\nEnter choice: ",choice);
                    clScreen();
                    officerSwitch(choice,students,studentCount);
                } while(choice != 0);

                break;

            case 3:
                // faculty
                clScreen();

                do{
                    displayHeader2();
                    facultyMenu();
                    enterChoice("\nEnter choice: ",choice);
                    clScreen();
                }  while(choice != 0);

                break;
        }
    }

    return 0;
}

/// function definition
void displayHeader(){
    SetConsoleOutputCP(CP_UTF8);
    cout << "+---------------------------------------------------------+\n";
    cout << "|__________________--✨ iSPACE PORTAL ✨--________________|\n";
    cout << "|               IBITS Portal for Announcements,           |\n";
    cout << "|                  Communication and Events               |\n";
    cout << "+---------------------------------------------------------+\n";
}
void displayHeader2() {
   cout << "==========================================================";
    cout << "\n|" << right << setw(39) << " __✨ iSpace ✨__" << right << setw(21) << "|\n";
    cout << "|" << right << setw(58) << "|\n";
    cout << "|" << right << setw(48) << "⚙️ MANAGEMENT OVERVIEW 📊 " << right << setw(16) << "|\n";
    cout << "|" << right << setw(57) << "|";
    cout << "\n==========================================================\n";
}

void auth(Officer* officers, Faculty* faculty, int& role, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn){
    if(officerFile.is_open() || facultyFile.is_open()){
        SetConsoleOutputCP(CP_UTF8);
        cout << right << setw(55) << "\n[📂] File successfully opened\n";

        char hasAccount;
        cout << "\nAlready have an account? (Y/N): ";
        cin >> hasAccount;
        cin.ignore();

        if(hasAccount == 'Y' || hasAccount == 'y'){
            // go to login
            login(officers, faculty, role, officerCount, facultyCount, accIndex, isLoggedIn);
        } else {
            // ask role
            roleSwitch(officers, faculty, role, officerCount, facultyCount, accIndex, isLoggedIn);
        }
    } else {
        cout << "\n\n" << right << setw(55) << "[!] File doesn't exist yet. Start your account.\n\n";
        pauseScreen();

        // ask for role
        roleSwitch(officers, faculty, role, officerCount, facultyCount, accIndex, isLoggedIn);
    }
}

void askRole(int& role){
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
}

void roleSwitch(Officer* officers, Faculty* faculty, int& role, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn){
    system("cls");
    displayHeader();
    SetConsoleOutputCP(CP_UTF8);

    askRole(role);

    switch(role){
        case 1:
            // ask for credentials, go to login
            break;

        case 2:
            createAccount(officers, faculty, role, officerCount, facultyCount);
            login(officers, faculty, role, officerCount, facultyCount, accIndex, isLoggedIn);
            break;

        case 3:
            createAccount(officers, faculty, role, officerCount, facultyCount);
            login(officers, faculty, role, officerCount, facultyCount, accIndex, isLoggedIn);
            break;

        default:
            cout << "\n[!] Invalid role. Select only from choices.\n";
    }
}

void createAccount(Officer* officers, Faculty* faculty, int role, int& officerCount, int& facultyCount){
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

        enterPrompt("🎖️ Enter Position: ",officers[officerCount].position,29);

        officers[officerCount].passcode = createPasscode();

        saveAccountToCSV("officers.csv",faculty,facultyCount);

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

        saveAccountToCSV("officers.csv",faculty,facultyCount);

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

void saveAccountToCSV(string file, Student* students, int studentCount){
    ifstream checkFile(file);
    bool fileIsEmpty = (checkFile.peek() == ifstream::traits_type::eof());
    checkFile.close();

    ofstream outFile;
    outFile.open(file, ios::app);

    if(outFile.is_open()){
        if(fileIsEmpty){
            outFile << "ID,Name,Program,Year Level,Passcode" << endl;
        }

        outFile << students[studentCount].ID << ',';
        outFile << students[studentCount].name << ',';
        outFile << students[studentCount].program << ',';
        outFile << students[studentCount].yearLevel << ',';
        outFile << students[studentCount].passcode << endl;

        cout << "\n[/] Information saved to csv.\n";
    } else {
        cout << "[!] Error: Could not open file.\n";
    }

    outFile.close();
}

void saveAccountToCSV(string file, Officer* officers, int officerCount){
    ifstream checkFile(file);
        bool fileIsEmpty = (checkFile.peek() == ifstream::traits_type::eof());
        checkFile.close();

        ofstream outFile;
        outFile.open(file, ios::app);

        if(outFile.is_open()){
            if(fileIsEmpty){
                outFile << "ID,Name,Program,Year Level,Position,Passcode" << endl;
            }

            outFile << officers[officerCount].ID << ',';
            outFile << officers[officerCount].name << ',';
            outFile << officers[officerCount].program << ',';
            outFile << officers[officerCount].yearLevel << ',';
            outFile << officers[officerCount].position << ',';
            outFile << officers[officerCount].passcode << endl;

            cout << "\n[/] Information saved to csv.\n";
        } else {
            cout << "[!] Error: Could not open file.\n";
        }

    outFile.close();
}
void saveAccountToCSV(string file, Faculty* faculty, int facultyCount){
      ifstream checkFile(file);
        bool fileIsEmpty = (checkFile.peek() == ifstream::traits_type::eof());
        checkFile.close();

        ofstream outFile;
        outFile.open(file, ios::app);

        if(outFile.is_open()){
            if(fileIsEmpty){
                outFile << "ID,Name,Passcode" << endl;
            }

            outFile << faculty[facultyCount].ID << ',';
            outFile << faculty[facultyCount].name << ',';
            outFile << faculty[facultyCount].passcode << endl;

            cout << "\n[/] Information saved to csv.\n";
        } else {
            cout << "[!] Error: Could not open file.\n";
        }

    outFile.close();
}

void login(Officer* officers, Faculty* faculty, int& role, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn){
    pauseScreen();
    clScreen();
    displayHeader();

    cout << "\n============== >>> Login to your account <<< ==============\n";

    askRole(role);

    if(role == 1){
        // student login
    } else if(role == 2){
        clScreen();
        displayHeader();
        cout << "\n============== >>> Login to your account <<< ==============\n";
        cout << "\n                    ==> Role: Officer <==\n";
        officerLogin(officers, faculty, role, officerCount, facultyCount, accIndex, isLoggedIn);
        pauseScreen();
    } else if(role == 3){
        clScreen();
        displayHeader();
        cout << "\n============== >>> Login to your account <<< ==============\n";
        cout << "\n                    ==> Role: Faculty <==\n";
        facultyLogin(officers, faculty, role, officerCount, facultyCount, accIndex, isLoggedIn);
        pauseScreen();
    }
}

void officerLogin(Officer* officers, Faculty* faculty, int role, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn) {
    ifstream officerFile("officers.csv");
    string id   = "";
    string pass = "";

    // matching loop validation checks
    bool idFound   = false;
    bool passFound = false;
    int  attempt   = 0;

    // ID Validation Loop (Checks the main officers array directly)
    while(!idFound){
        enterPrompt("\n🪪 Enter ID: ", id);

        for(int j = 0; j < officerCount; j++){
            if(officers[j].ID == id){
                idFound = true;
                accIndex = j; // Stores index matching the array in main
                break;
            }
        }

        if(idpassNotFound(idFound, attempt, "[!] ID Not Found. Try again\n")) {
            createAccount(officers, faculty, role, officerCount, facultyCount);
            return;
        }
    }

    attempt = 0;

    // Passcode Validation Loop
    while(!passFound){
        enterPrompt("🔑 Enter passcode: ", pass);

        if(officers[accIndex].passcode == pass){
            passFound = true;
        }

        if(idpassNotFound(passFound, attempt, "[!] Wrong passcode\n")) {
            createAccount(officers, faculty, role, officerCount, facultyCount);
            return;
        }
    }

    cout << "\n[/] Login Successful!";
    displayWelcome(officers[accIndex].name);
    isLoggedIn = true;
}

void facultyLogin(Officer* officers, Faculty* faculty, int role, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn) {
    ifstream facultyFile("faculty.csv");
    string id   = "";
    string pass = "";

    // matching loop validation checks
    bool idFound   = false;
    bool passFound = false;
    int  attempt   = 0;

    // ID Validation Loop (Checks the main faculty array directly)
    while(!idFound){
        enterPrompt("\n🪪 Enter ID: ", id);

        for(int j = 0; j < facultyCount; j++){
            if(faculty[j].ID == id){
                idFound = true;
                accIndex = j; // Stores index matching the array in main
                break;
            }
        }

        if(idpassNotFound(idFound, attempt, "[!] ID Not Found. Try again\n")) {
            createAccount(officers, faculty, role, officerCount, facultyCount);
            return;
        }
    }

    attempt = 0;

    // Passcode Validation Loop
    while(!passFound){
        enterPrompt("🔑 Enter passcode: ", pass);

        if(faculty[accIndex].passcode == pass){
            passFound = true;
        }

        if(idpassNotFound(passFound, attempt, "[!] Wrong passcode\n")) {
            createAccount(officers, faculty, role, officerCount, facultyCount);
            return;
        }
    }

    cout << "\n[/] Login Successful!";
    displayWelcome(faculty[accIndex].name);
    isLoggedIn = true;
}

// load id and passcode - officer
void loadIDPassFromFile(Officer* tempOfficer, int& count){
    officerFile.clear();
    officerFile.seekg(0, ios::beg);

    string line;
    count = 0;

    // Read and skip header line
    if(getline(officerFile, line)) {
        while(getline(officerFile, line) && count < MAX_OFFICER){
            stringstream ss(line);
            string yearStr;

            // Extract all details sequentially, including Name
            getline(ss, tempOfficer[count].ID, ',');
            getline(ss, tempOfficer[count].name, ',');
            getline(ss, tempOfficer[count].program, ',');
            getline(ss, yearStr, ',');
            getline(ss, tempOfficer[count].position, ',');
            getline(ss, tempOfficer[count].passcode);

            if(!yearStr.empty()){
                tempOfficer[count].yearLevel = atoi(yearStr.c_str());
            } else {
                tempOfficer[count].yearLevel = 0;
            }

            count++;
        }
    }
}

// load id and passcode - faculty
void loadIDPassFromFile(Faculty* tempFaculty, int& count){
    facultyFile.clear();
    facultyFile.seekg(0, ios::beg);

    string line;
    count = 0;

    // Read and skip header line
    if(getline(facultyFile, line)) {
        while(getline(facultyFile, line) && count < MAX_FACULTY){
            stringstream ss(line);

            // Extract all details sequentially, including Name
            getline(ss, tempFaculty[count].ID, ',');
            getline(ss, tempFaculty[count].name, ',');
            getline(ss, tempFaculty[count].passcode);

            count++;
        }
    }
}

// if id or passcode is wrong or doesn't exists
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
                return true;
            } else {
                cout << "\n[!] Resetting login attempts. Please double-check your input.\n";
                attempt = 0;
                return false;
            }
        }
    }
    return false;
}

void displayWelcome(string name){
    cout << "\nWelcome, " << name << "!\n";
}


/// officer's module
void officerMenu(){
    cout << "\n" << right << setw(40) << ">>> Role: Officer <<<" << "\n";
    cout << "\n[1] 👥 Member Management";
    cout << "\n[2] 📢 Announcement Management";
    cout << "\n[3] 📅 Activity Management";
    cout << "\n[4] 🔍 Search\n";
    cout << "[0] 🚪 Log Out\n";



}

void officerSwitch(int choice,Student* students, int& studentCount){
    switch(choice){
        case 1:
            // member management
            displayHeader2();
            memberManagement(students,studentCount);
            break;

        case 2:
            // announcement management
            displayHeader2();
            announcementManagement();
            break;

        case 3:
            // activity management
            displayHeader2();
            activityManagement();
            break;

        case 4:
            // search
            displayHeader2();
            searchFunction();
            break;

        case 0:
            // log out
            // go back to landing page
            break;

        default:
            cout << "\n[!] Invalid choice. Try again.\n";
    }

}

// member management
void memberManagement(Student* students, int& studentCount){
    int memberChoice = 0;

    do{
       cout << "\n" << right << setw(42) << "-----------------------";
        cout << "\n" << right << setw(46) << "👥 Member Management 👥" << "\n";
        cout << right << setw(42) << "-----------------------" << "\n";
        cout << "\n[1] Add Member";
        cout << "\n[2] View Member";
        cout << "\n[3] Edit Member";
        cout << "\n[4] Remove Member";
        cout << "\n[0] Return to Main Menu\n";

        enterChoice("\nEnter choice: ",memberChoice);

        switch(memberChoice){
            case 1:
                // add member
                displayHeader2();
                addMember(students,studentCount);
                break;

            case 2:
                // view member
                displayHeader2();
                break;

            case 3:
                // edit member
                displayHeader2();
                break;

            case 4:
                // remove member
                displayHeader2();
                break;

            case 0:
                // return to menu
                break;

            default:
                cout << "\n[!] Invalid choice. Try again.\n";
        }
    } while(memberChoice != 0);

    clScreen();
}

/** Member management functions **/
void addMember(Student* students, int& studentCount){
    clScreen();
    cout << "\n" << right << setw(38) << "----------------";
    cout << "\n" << right << setw(42) << "👥 Add Member 👥" << "\n";
    cout << right << setw(38) << "----------------" << "\n";
    enterPrompt("\nEnter Student ID: ", students[studentCount].ID);
    enterPrompt("Enter Student Name: ", students[studentCount].name);

    enterPrompt("Enter Program: ", students[studentCount].program);
    /*while(students[studentCount].program != "BSIT" && students[studentCount].program != "DIT"  &&
          students[studentCount].program != "bsit" && students[studentCount] != "dit"){
            cout << "\n[!] Program must be BSIT or DIT only.\n\n";
            enterPrompt("💻 Enter Program: ", students[studentCount].program, 26);
    }*/

    enterPrompt("Enter Year Level: ", students[studentCount].yearLevel);
    while(students[studentCount].yearLevel >= 5){
            cout << "\n[!] Valid year level are Years 1 to 4 only.\n\n";
            enterPrompt("\n📈 Enter Year Level: ",students[studentCount].yearLevel,26);
    }

    cout << "\nPress Enter to generate passcode.\n";

    int* code = new int[8];
    string generatedCode = "";
    for(int i = 0; i < 8; i++){
        code[i] = rand() % 10;
        generatedCode += to_string(code[i]);
    }

    cout << "\n[/] Passcode generated.\n";

    students[studentCount].passcode = generatedCode;

    saveAccountToCSV("students.csv",students,studentCount);

    delete[] code;

    pauseScreen();
    clScreen();
}

void announcementManagement(){
    int announcementChoice = 0;

    do{
        cout << "\n" << right << setw(43) << "--------------------------";
        cout << "\n" << right << setw(49) << "📢 Announcement Management 📢" << "\n";
        cout << right << setw(43) << "--------------------------" << "\n";

        cout << "\n[1] Propose Announcement";
        cout << "\n[2] View Announcement";
        cout << "\n[3] Edit Announcement";
        cout << "\n[4] Remove Announcement";
        cout << "\n[5] Pin/Urgent";
        cout << "\n[0] Return to Main Menu\n";

        enterChoice("\nEnter choice: ",announcementChoice);

        switch(announcementChoice){
            case 1:
                // propose
                displayHeader2();
                break;

            case 2:
                // view announcement
                displayHeader2();
                break;

            case 3:
                // edit announcement
                break;

            case 4:
                // remove
                displayHeader2();
                break;

            case 5:
                // pin / urgent
                displayHeader2();
                break;

            case 0:
                // return to menu
                break;

            default:
                cout << "\n[!] Invalid choice. Try again.\n";
        }
    } while(announcementChoice != 0);
    clScreen();

}

void activityManagement(){
    int activityChoice = 0;

    do{
        cout << "\n" << right << setw(44) << "--------------------------";
        cout << "\n" << right << setw(47) << "📅 Activity Management 📅" << "\n";
        cout << right << setw(44) << "--------------------------" << "\n";
        cout << "\n[1] Add Activity";
        cout << "\n[2] View Activities";
        cout << "\n[3] Update Activity";
        cout << "\n[4] Remove Activity";
        cout << "\n[0] Return to Main Menu\n";

        enterChoice("\nEnter choice: ",activityChoice);

        switch(activityChoice){
            case 1:
                // add activity
                displayHeader2();
                break;

            case 2:
                // view
                displayHeader2();
                break;

            case 3:
                // edit
                displayHeader2();
                break;

            case 4:
                // remove
                displayHeader2();
                break;

            case 0:
                // return to menu
                break;

            default:
                cout << "\n[!] Invalid choice. Try again.\n";
        }
    } while(activityChoice != 0);

    clScreen();
}

void searchFunction(){
    int searchChoice = 0;

    do{
        cout << "\n" << right << setw(43) << "--------------------------";
        cout << "\n" << right << setw(46) << "🔍 Search Management 🔍" << "\n";
        cout << right << setw(43) << "--------------------------" << "\n";
        cout << "\n[1] Search Member";
        cout << "\n[2] Search Announcement";
        cout << "\n[3] Search Activity";
        cout << "\n[0] Return to Main Menu\n";

        enterChoice("\nEnter choice: ",searchChoice);

        switch(searchChoice){
            case 1:
                // search member
                // conditional - id or name?
                displayHeader2();
                break;

            case 2:
                // search announcement
                // conditional - id or name?
                displayHeader2();
                break;

            case 3:
                // search activity
                // conditional - id or name?
                break;

            case 0:
                // return to menu
                break;

            default:
                cout << "\n[!] Invalid choice. Try again.\n";
        }
    } while(searchChoice != 0);

    clScreen();
}

/// faculty module
void facultyMenu(){
    cout << "\n" << right << setw(40) << ">>> Role: faculty <<<" << "\n";
    cout << "\n[1] Announcement Management";
    cout << "\n[2] View Students";
    cout << "\n[3] View Officers";
    cout << "\n[4] Search";
    cout << "\n[5] View Feedbacks";
    cout << "\n[0] Log Out\n";
}

void facultySwitch(int choice){
    switch(choice){
        case 1:
            // announcement management
            displayHeader2();
            break;

        case 2:
            // view students
            displayHeader2();
            break;

        case 3:
            // view officers
            displayHeader2();
            break;

        case 4:
            // search
            displayHeader2();
            break;

        case 5:
            // view feedbacks
            displayHeader2();
            break;

        case 0:
            // log out
            break;

        default:
            cout << "\n[!] Invalid choice. Try again.\n";
    }
}


/// utility function definition
void pauseScreen(){
    cout << "\n";
    system("pause");
}

void clScreen(){
    system("cls");
}

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

void enterChoice(string prompt, int& val){
    cout << prompt;
    cin >> val;
    cin.ignore();
}

bool isEmpty(string str){
    if(str.empty()){
        cout << "\n[!] Please fill in this field.\n" << endl;
        return true;
    }
    return false;
}
