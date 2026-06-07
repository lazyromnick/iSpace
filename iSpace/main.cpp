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
void auth(Student* students, Officer* officers, Faculty* faculty, int& role, int studentCount, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn);
void askRole(int& role);
void roleSwitch(Student* students, Officer* officers, Faculty* faculty, int& role, int studentCount, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn);
void createAccount(Officer* officers, Faculty* faculty, int role, int& officerCount, int& facultyCount);
string createPasscode();
void saveAccountToCSV(string file, Student* students, int studentCount);  // overloading - student
void saveAccountToCSV(string file, Officer* officers, int officerCount);  // overloading - officer
void saveAccountToCSV(string file, Faculty* faculty, int facultyCount);   // overloading - faculty
void login(Student* students, Officer* officers, Faculty* faculty, int& role, int studentCount, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn);
void studentLogin(Student* students, int studentCount, int& accIndex, bool& isLoggedIn);
void officerLogin(Student* students, Officer* officers, Faculty* faculty, int role, int studentCount, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn);
void facultyLogin(Student* students, Officer* officers, Faculty* faculty, int role, int studentCount, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn);
void updateStudentsCSV(string file, Student* students, int studentCount);  // to follow
void updateOfficersCSV(string file, Officer* officers, int officerCount);
void updateFacultyCSV(string file, Faculty* faculty, int facultyCount);
void loadIDPassFromFile(Student* students, int& count);
void loadIDPassFromFile(Officer* tempOfficer, int& count);
void loadIDPassFromFile(Faculty* tempFaculty, int& count);
bool idpassNotFound(bool& var, int& attempt, string displayMessage);
void displayWelcome(string name);

// officer module
void officerMenu();
void officerSwitch(int choice,Student* students, int& studentCount);

/* managements holder */
void memberManagement(Student* students, int& studentCount);
void announcementManagement();
void activityManagement();
void searchFunction(Student* students, int studentCount);

/* member management */
void addMember(Student* students, int& studentCount);
void viewMembers(Student* students, int studentCount);
void sortMember(Student* students, int studentCount, int method);
void editMember(Student* students, int& studentCount);
void removeMember(Student* students, int& studentCount);

/* search */
int searchMember(Student* students, int studentCount, string target, string searchValue="");
void displayMember(Student* students, int index=0);

// faculty module
void facultyMenu();

/// utility function
void pauseScreen();
void clScreen();
void enterPrompt(string prompt, string& val);
void enterPrompt(string prompt, int& val);
void enterPrompt(string prompt, char& val);
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

    // oad data from files
    loadIDPassFromFile(students,studentCount);
    loadIDPassFromFile(officers, officerCount);
    loadIDPassFromFile(faculty, facultyCount);

    displayHeader();

    bool isLoggedIn = false;
    auth(students, officers, faculty, role, studentCount, officerCount, facultyCount, accIndex, isLoggedIn);

    if(isLoggedIn){
        switch(role){
            case 1:
            //student module
            break;

            case 2:
                // officer module
                clScreen();

                do{
                    //displayHeader();
                    displayHeader2();
                    officerMenu();
                    enterPrompt("\nEnter choice: ",choice);
                    clScreen();
                    officerSwitch(choice,students,studentCount);
                } while(choice != 5);

                break;

            case 3:
                // faculty
                clScreen();

                do{
                    displayHeader2();
                    facultyMenu();
                    enterPrompt("\nEnter choice: ",choice);
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

void auth(Student* students, Officer* officers, Faculty* faculty, int& role, int studentCount, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn){
    ifstream studentFile("students.csv");
    ifstream officerFile("officers.csv");
    ifstream facultyFile("faculty.csv");

    if(studentFile.is_open() || officerFile.is_open() || facultyFile.is_open()){
        SetConsoleOutputCP(CP_UTF8);
        cout << right << setw(55) << "\n[📂] File successfully opened\n";

        char hasAccount;
        cout << "\nAlready have an account? (Y/N): ";
        cin >> hasAccount;
        cin.ignore();

        if(hasAccount == 'Y' || hasAccount == 'y'){
            // go to login
            login(students, officers, faculty, role,studentCount, officerCount, facultyCount, accIndex, isLoggedIn);
        } else {
            // ask role
            roleSwitch(students, officers, faculty, role, studentCount, officerCount, facultyCount, accIndex, isLoggedIn);
        }
    } else {
        cout << "\n\n" << right << setw(55) << "[!] File doesn't exist yet. Start your account.\n\n";
        pauseScreen();

        roleSwitch(students, officers, faculty, role, studentCount, officerCount, facultyCount, accIndex, isLoggedIn);
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

void roleSwitch(Student* students, Officer* officers, Faculty* faculty, int& role, int studentCount, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn){
    system("cls");
    displayHeader();
    SetConsoleOutputCP(CP_UTF8);

    askRole(role);

    switch(role){
        case 1:
            // ask for credentials, go to login
            cout << "\nDo you already have your credentials? (Y/N): ";
            char hasCred;
            cin >> hasCred;
            cin.ignore();

            if(hasCred == 'Y' || hasCred == 'y'){
                login(students, officers,faculty,role,studentCount, officerCount,facultyCount,accIndex,isLoggedIn);
            } else {
                cout << "\nRequest your credentials from an officer.\n";
                cout << "\nReturning...";
                Sleep(2000);
                clScreen();
            }
            break;

        case 2:
            createAccount(officers, faculty, role, officerCount, facultyCount);
            login(students, officers, faculty, role,studentCount, officerCount, facultyCount, accIndex, isLoggedIn);
            break;

        case 3:
            createAccount(officers, faculty, role, officerCount, facultyCount);
            login(students, officers, faculty, role,studentCount, officerCount, facultyCount, accIndex, isLoggedIn);
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

        enterPrompt("🆔 Enter ID: ",officers[officerCount].ID);
        enterPrompt("👤 Enter Name: ",officers[officerCount].name);

        enterPrompt("💻 Enter Program: ",officers[officerCount].program);
        while(officers[officerCount].program != "BSIT" && officers[officerCount].program != "DIT"  &&
              officers[officerCount].program != "bsit" && officers[officerCount].program != "dit"){
            cout << "\n[!] Program must be BSIT or DIT only.\n\n";
            enterPrompt("💻 Enter Program: ", officers[officerCount].program);
        }

        enterPrompt("📈 Enter Year Level: ",officers[officerCount].yearLevel);
        while(officers[officerCount].yearLevel >= 5){
            cout << "\n[!] Valid year level are Years 1 to 4 only.\n\n";
            enterPrompt("📈 Enter Year Level: ",officers[officerCount].yearLevel);
        }

        enterPrompt("🎖️ Enter Position: ",officers[officerCount].position);

        officers[officerCount].passcode = createPasscode();

        saveAccountToCSV("officers.csv",officers,officerCount);

        // update account counter tracker
        officerCount++;

    } else if(role == 3){
        SetConsoleOutputCP(CP_UTF8);
        cout << "\n-----------------------------------------------------------\n";
        cout << right << setw(39) << ">>> Role: Faculty <<<" << "\n";
        cout << "-----------------------------------------------------------\n\n";

        enterPrompt("🆔 Enter ID: ",   faculty[facultyCount].ID);
        enterPrompt("👤 Enter Name: ", faculty[facultyCount].name);

        faculty[facultyCount].passcode = createPasscode();

        saveAccountToCSV("faculty.csv",faculty,facultyCount);

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

void login(Student* students, Officer* officers, Faculty* faculty, int& role, int studentCount, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn){
    pauseScreen();
    clScreen();
    displayHeader();

    cout << "\n============== >>> Login to your account <<< ==============\n";

    askRole(role);

    if(role == 1){
        clScreen();
        displayHeader();
        cout << "\n============== >>> Login to your account <<< ==============\n";
        cout << "\n                    ==> Role: Student <==\n";
        studentLogin(students,studentCount,accIndex,isLoggedIn);
    } else if(role == 2){
        clScreen();
        displayHeader();
        cout << "\n============== >>> Login to your account <<< ==============\n";
        cout << "\n                    ==> Role: Officer <==\n";
        officerLogin(students, officers, faculty, role, studentCount, officerCount, facultyCount, accIndex, isLoggedIn);
    } else if(role == 3){
        clScreen();
        displayHeader();
        cout << "\n============== >>> Login to your account <<< ==============\n";
        cout << "\n                    ==> Role: Faculty <==\n";
        facultyLogin(students, officers, faculty, role, studentCount, officerCount, facultyCount, accIndex, isLoggedIn);
    }
}

void studentLogin(Student* students, int studentCount, int& accIndex, bool& isLoggedIn){
    string id = "";
    string pass = "";

    bool idFound = false;
    bool passFound = false;
    int attempt = 0;

    // ID Validation Loop
    while(!idFound){
        enterPrompt("\n🪪 Enter ID: ", id);

        for(int j = 0; j < studentCount; j++){
            // sequential search to find student id
            if(students[j].ID == id){
                idFound = true;
                accIndex = j;
                break;
            }
        }

        if(idpassNotFound(idFound, attempt, "[!] ID Not Found. Try again\n")) {
            cout << "\n-----------------------------------------------------------\n";
            cout << "[!] Access Denied: Student accounts are managed by administrators.\n";
            cout << "[i] If your ID is unregistered, please approach an Officer for account creation.\n";
            cout << "-----------------------------------------------------------\n";
            return; // Cleanly breaks out and returns to the login menu
        }
    }

    // Reset attempts tracker specifically for passcode checking
    attempt = 0;

    // Passcode Validation Loop
    while(!passFound){
        enterPrompt("🔑 Enter passcode: ", pass);

        if(students[accIndex].passcode == pass){
            passFound = true;
        }

        if(idpassNotFound(passFound, attempt, "[!] Wrong passcode\n")) {
            cout << "\n-----------------------------------------------------------\n";
            cout << "[!] Access Denied: Student password self-reset is disabled.\n";
            cout << "[i] Please talk to an Officer to verify or reset your passcode.\n";
            cout << "-----------------------------------------------------------\n";
            return; // Cleanly breaks out and returns to the login menu
        }
    }

    // Success State
    cout << "\n[/] Login Successful!";
    displayWelcome(students[accIndex].name);
    isLoggedIn = true;
}

void officerLogin(Student* students, Officer* officers, Faculty* faculty, int role, int studentCount, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn) {
    string id   = "";
    string pass = "";

    bool idFound   = false;
    bool passFound = false;
    int  attempt   = 0;

    // ID Validation Loop
    while(!idFound){
        enterPrompt("\n🪪 Enter ID: ", id);

        for(int j = 0; j < officerCount; j++){
            if(officers[j].ID == id) {
                idFound = true;
                accIndex = j;
                break;
            }
        }

        if(idpassNotFound(idFound, attempt, "[!] ID Not Found. Try again\n")) {
            createAccount(officers, faculty, role, officerCount, facultyCount);
            login(students,officers, faculty, role, studentCount, officerCount, facultyCount, accIndex, isLoggedIn);
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
            cout << "\n[!] Resetting passcode for ID: " << officers[accIndex].ID << "...\n";

            officers[accIndex].passcode = createPasscode();
            updateOfficersCSV("officers.csv", officers, officerCount);
            loadIDPassFromFile(officers, officerCount);

            attempt = 0;
            cout << "\n[i] File updated & synchronized. Please log in with your new passcode.\n";
        }
    }

    cout << "\n[/] Login Successful!";
    displayWelcome(officers[accIndex].name);
    isLoggedIn = true;
}

void facultyLogin(Student* students, Officer* officers, Faculty* faculty, int role, int studentCount, int& officerCount, int& facultyCount, int& accIndex, bool& isLoggedIn) {
    string id   = "";
    string pass = "";

    bool idFound   = false;
    bool passFound = false;
    int  attempt   = 0;

    // ID Validation Loop
    while(!idFound){
        enterPrompt("\n🪪 Enter ID: ", id);

        for(int j = 0; j < facultyCount; j++){
            if(faculty[j].ID == id){
                idFound = true;
                accIndex = j;
                break;
            }
        }

        if(idpassNotFound(idFound, attempt, "[!] ID Not Found. Try again\n")) {
            createAccount(officers, faculty, role, officerCount, facultyCount);
            login(students,officers, faculty, role, studentCount, officerCount, facultyCount, accIndex, isLoggedIn);
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
            cout << "\n[!] Resetting passcode for ID: " << faculty[accIndex].ID << "...\n";

            faculty[accIndex].passcode = createPasscode();
            updateFacultyCSV("faculty.csv", faculty, facultyCount);
            loadIDPassFromFile(faculty, facultyCount);

            attempt = 0;
            cout << "\n[i] File updated & synchronized. Please log in with your new passcode.\n";
        }
    }

    cout << "\n[/] Login Successful!";
    displayWelcome(faculty[accIndex].name);
    isLoggedIn = true;
}

void updateStudentsCSV(string file, Student* students, int studentCount){
    ofstream outFile(file, ios::trunc);

    if(outFile.is_open()){
        outFile << "ID,Name,Program,Year Level\n";
        for(int i = 0; i < studentCount;i++){
            outFile << students[i].ID << ',';
            outFile << students[i].name << ',';
            outFile << students[i].program << ',';
            outFile << students[i].yearLevel << ',';
            outFile << students[i].passcode << "\n";
        }
        outFile.close();
    }
}

void updateOfficersCSV(string file, Officer* officers, int officerCount) {
    ofstream outFile(file, ios::trunc); // Overwrites the old file completely
    if (outFile.is_open()) {
        outFile << "ID,Name,Program,Year Level,Position,Passcode\n";
        for (int i = 0; i < officerCount; i++) {
            outFile << officers[i].ID << ','
                    << officers[i].name << ','
                    << officers[i].program << ','
                    << officers[i].yearLevel << ','
                    << officers[i].position << ','
                    << officers[i].passcode << "\n";
        }
        outFile.close();
    }
}

void updateFacultyCSV(string file, Faculty* faculty, int facultyCount) {
    ofstream outFile(file, ios::trunc); // Overwrites the old file completely
    if (outFile.is_open()) {
        outFile << "ID,Name,Passcode\n";
        for (int i = 0; i < facultyCount; i++) {
            outFile << faculty[i].ID << ','
                    << faculty[i].name << ','
                    << faculty[i].passcode << "\n";
        }
        outFile.close();
    }
}

// load id and passcode - students
void loadIDPassFromFile(Student* tempStudents, int& count){
    ifstream studentFile("students.csv");

    studentFile.clear();
    studentFile.seekg(0, ios::beg);

    string line;
    string yearStr;
    count = 0;

    // Read and skip header line
    if(getline(studentFile,line)){
        while(getline(studentFile,line) && count < MAX_STUDENT){
            stringstream ss(line);

            getline(ss, tempStudents[count].ID, ',');
            getline(ss, tempStudents[count].name, ',');
            getline(ss, tempStudents[count].program, ',');
            getline(ss, yearStr, ',');
            getline(ss, tempStudents[count].passcode);

            if(!yearStr.empty()){
                tempStudents[count].yearLevel = atoi(yearStr.c_str());
            } else {
                tempStudents[count].yearLevel = 0;
            }

            count++;
        }
    }

    studentFile.close();
}

// load id and passcode - officer
void loadIDPassFromFile(Officer* tempOfficer, int& count){
    ifstream officerFile("officers.csv");
    officerFile.clear();
    officerFile.seekg(0, ios::beg);

    string line;
    count = 0;

    // Read and skip header line
    if(getline(officerFile, line)) {
        while(getline(officerFile, line) && count < MAX_OFFICER){
            stringstream ss(line);
            string yearStr;

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

    officerFile.close();
}

// load id and passcode - faculty
void loadIDPassFromFile(Faculty* tempFaculty, int& count){
    ifstream facultyFile("faculty.csv");
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

    facultyFile.close();
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
    cout << "[5] 🚪 Log Out\n";
}

void officerSwitch(int choice,Student* students, int& studentCount){
    loadIDPassFromFile(students,studentCount);

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
            searchFunction(students,studentCount);
            break;

        case 5:
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
        cout << "\n[5] Return to Main Menu\n";

        enterPrompt("\nEnter choice: ",memberChoice);

        switch(memberChoice){
            case 1:
                // add member
                displayHeader2();
                addMember(students,studentCount);
                break;

            case 2:
                // view member
                displayHeader2();
                if(studentCount <= 0){
                    cout << "\n[!] No students record yet. Go to Add Member.\n";
                    return;
                }
                viewMembers(students,studentCount);
                break;

            case 3:
                // edit member
                if(studentCount <= 0){
                    cout << "\n[!] No students record yet. Go to Add Member.\n";
                    return;
                }
                displayHeader2();
                editMember(students,studentCount);
                break;

            case 4:
                // remove member
                if(studentCount <= 0){
                    cout << "\n[!] No students record yet. Go to Add Member.\n";
                    return;
                }
                displayHeader2();
                removeMember(students, studentCount);
                break;

            case 5:
                // return to menu
                break;

            default:
                cout << "\n[!] Invalid choice. Try again.\n";
        }
    } while(memberChoice != 5);

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
            enterPrompt("\n📈 Enter Year Level: ",students[studentCount].yearLevel);
    }

    cout << "\nPress Enter to generate passcode.\n";
    cin.get();

    int* code = new int[8];
    string generatedCode = "";
    for(int i = 0; i < 8; i++){
        code[i] = rand() % 10;
        generatedCode += to_string(code[i]);
    }

    cout << "\n[/] Passcode generated.";

    students[studentCount].passcode = generatedCode;

    saveAccountToCSV("students.csv",students,studentCount);

    delete[] code;

    pauseScreen();
    clScreen();
}

void viewMembers(Student* students, int studentCount){
    int returnOrSort;
    do{
        clScreen();
        loadIDPassFromFile(students,studentCount);

        cout << "\nMember list\n\n";
        cout << left << setw(17) << "ID" << setw(25) << "Name" << setw(13) << "Program" << "Year Level\n";
        for(int i = 0; i < studentCount; i++){
            cout << left << setw(17) << students[i].ID << setw(25) << students[i].name << setw(13) <<
                                        students[i].program << students[i].yearLevel << "\n";
        }

        enterPrompt("\n[1] Sort     [2] Return to Menu \nChoose: ",returnOrSort);

        if(returnOrSort == 1){
            int method;
            cout << "\nSort by: [1] ID     [2] Name\n";

            enterPrompt("\nChoose method: ",method);
            while(method != 1 && method != 2){
                cout << "[!] Choose only from the options above.\n";
                enterPrompt("\nChoose method: ",method);
            }

            sortMember(students,studentCount,method);
        }

        updateStudentsCSV("students.csv",students,studentCount);
    }while(returnOrSort != 2);

}

// bubble sort - id
void sortMember(Student* students, int studentCount, int method){
    for(int i = 0; i < studentCount - 1; i++){
        for(int j = 0; j < studentCount - 1 - i; j++){
            if(method == 1){
                if(students[j].ID > students[j+1].ID){
                    Student temp = students[j];
                    students[j] = students[j+1];
                    students[j+1] = temp;
                }
            } else {
                if(students[j].name > students[j+1].name){
                    Student temp = students[j];
                    students[j] = students[j+1];
                    students[j+1] = temp;
                }
            }
        }
    }
}

void editMember(Student* students, int& studentCount){
    loadIDPassFromFile(students, studentCount);

    string target;
    enterPrompt("\nEnter name of member to edit: ", target);

    // pass "Name" explicitly, or it defaults to "" and returns -1
    int memberIdx = searchMember(students, studentCount, target,"Name");

    if(memberIdx == -1){
        cout << "\n[!] Member not found.\n";
        pauseScreen();
        return;
    }

    Student* stud = &students[memberIdx];

    cout << "\nEdit member\n\n";
    int edit;
    cout << "[1] ID     [2] Name     [3] Program     [4] Year Level\n";
    enterPrompt("\nChoose which data you want to edit: ", edit);

    switch(edit){
        case 1:
            enterPrompt("\nEdit ID: ", stud->ID);
            break;
        case 2:
            enterPrompt("\nEdit Name: ", stud->name);
            break;
        case 3:
            enterPrompt("\nEdit Program: ", stud->program);
            break;
        case 4:
            enterPrompt("\nEdit Year Level: ", stud->yearLevel);
            break;
        default:
            cout << "[!] Invalid choice. Choose only from choice above.\n";
            return;
    }

    updateStudentsCSV("students.csv", students, studentCount);
    cout << "\n[/] Member updated successfully.\n";
    pauseScreen();
}

void removeMember(Student* students, int& studentCount){
    loadIDPassFromFile(students, studentCount);

    string target;
    enterPrompt("\nEnter name of member to remove: ", target);

    int memberIdx = searchMember(students, studentCount, target, "Name");

    if(memberIdx == -1){
        cout << "\n[!] Member not found.\n";
        pauseScreen();
        return;
    }

    // display found member before confirming
    displayMember(students, memberIdx);

    char confirm;
    enterPrompt("Confirm removal? (Y/N): ", confirm);

    if(confirm == 'Y' || confirm == 'y'){
        // pointer to target member
        Student* toDelete = &students[memberIdx];
        toDelete = nullptr;

        // shift elements left to fill the gap
        for(int i = memberIdx; i < studentCount - 1; i++){
            students[i] = students[i + 1];
        }

        studentCount--;

        updateStudentsCSV("students.csv", students, studentCount);
        cout << "\n[/] Member removed successfully.\n";
    } else {
        cout << "\n[i] Operation cancelled.\n";
    }

    pauseScreen();
}

/** Announcement Management Functions **/
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
        cout << "\n[6] Return to Main Menu\n";

        enterPrompt("\nEnter choice: ",announcementChoice);

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

            case 6:
                // return to menu
                break;

            default:
                cout << "\n[!] Invalid choice. Try again.\n";
        }
    } while(announcementChoice != 6);
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
        cout << "\n[5] Return to Main Menu\n";

        enterPrompt("\nEnter choice: ",activityChoice);

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

            case 5:
                // return to menu
                break;

            default:
                cout << "\n[!] Invalid choice. Try again.\n";
        }
    } while(activityChoice != 5);

    clScreen();
}

void searchFunction(Student* students,int studentCount){
    int searchChoice = 0;

    do{
        cout << "\n" << right << setw(43) << "--------------------------";
        cout << "\n" << right << setw(46) << "🔍 Search Management 🔍" << "\n";
        cout << right << setw(43) << "--------------------------" << "\n";
        cout << "\n[1] Search Member";
        cout << "\n[2] Search Announcement";
        cout << "\n[3] Search Activity";
        cout << "\n[4] Return to Main Menu\n";

        enterPrompt("\nEnter choice: ",searchChoice);

        string target;
        string searchValue;

        switch(searchChoice){
            case 1:
                displayHeader2();

                char searchIdName;
                enterPrompt("\nSearch Member by [I]D or [N]ame: ",searchIdName);

                if(searchIdName == 'I' || searchIdName == 'i'){
                    searchValue = "ID";

                    cout << "\nSearch by ID\n\n";
                    enterPrompt("Enter ID to search: ",target);

                    int idIndex = searchMember(students,studentCount,target,searchValue);

                    if(idIndex == -1){
                        cout << "\n[!] Member with that ID not found.\n";
                    } else {
                        cout << "\n[/] Member found\n\n";
                        displayMember(students,idIndex);
                    }
                } else if(searchIdName == 'N' || searchIdName == 'n'){
                    searchValue = "Name";

                    cout << "\nSearch by Name\n\n";
                    enterPrompt("Enter Name to search: ",target);

                    int nameIndex = searchMember(students,studentCount,target,searchValue);

                    if(nameIndex == -1){
                        cout << "\n[!] Member with that Name not found.\n";
                    } else {
                        cout << "\n[/] Member found\n\n";
                        displayMember(students,nameIndex);
                    }
                } else {
                    cout << "\n[!] Invalid choice. Choose only from the choice above.\n";
                }
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

            case 4:
                // return to menu
                break;

            default:
                cout << "\n[!] Invalid choice. Try again.\n";
        }
    } while(searchChoice != 4);

    clScreen();
}

int searchMember(Student* students, int studentCount, string target, string searchValue){
    if(searchValue == "ID"){
        for(int i = 0; i < studentCount; i++){
            if(students[i].ID == target){
                return i;
            }
        }
    } else if(searchValue == "Name"){
        for(int i = 0; i < studentCount; i++){
            // partial match
            if(students[i].name.find(target) != string::npos){
                return i;
            }
        }
    }
    return -1;
}

void displayMember(Student* students, int index){
    cout << left << setw(17) << "ID" << setw(25) << "Name" << setw(13) << "Program" << "Year Level\n";
    cout << left << setw(17) << students[index].ID << setw(25) << students[index].name << setw(13) <<
                                students[index].program << students[index].yearLevel << "\n\n";
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

void enterPrompt(string prompt, string& val){
    do{
        cout << prompt;
        getline(cin, val);
    } while(isEmpty(val));
}

void enterPrompt(string prompt, int& val){
    do{
        cout << prompt;
        cin >> val;
    } while(isValidDigit(val));
}

void enterPrompt(string prompt, char& val){
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
