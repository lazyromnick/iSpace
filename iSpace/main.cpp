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

struct Announcement {
    int    id;
    string title;
    string content;
    string date;
    string postedBy;
    string status;
    string rejectionReason;
};

struct Activity {
    int    id;
    string name;
    string description;
    string date;
    string time;
    string location;
    string participants;
    string status;
};

const int MAX_STUDENT = 200;
const int MAX_OFFICER = 50;
const int MAX_FACULTY = 10;

const int MAX_ANNOUNCEMENTS = 100;
const int MAX_ACTIVITIES = 100;

// headers
void displayHeader();
void displayHeader2();
void displayCounterUpdates(int studentCount, int announcementCount, int activityCount);
void displayName(string name);
string getCurrentDate();

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

// officer module
void officerMenu();
void officerSwitch(int choice, Student* students, int& studentCount, Announcement* announcements,
                   int& announcementCount, Activity* activities, int& activityCount, Officer* officers, int accIndex);

/* managements holder */
void memberManagement(Student* students, int& studentCount);
void officerSwitch(int choice, Student* students, int& studentCount, Announcement* announcements, int& announcementCount, Officer* officers, int accIndex);
void activityManagement(Activity* activities, int& activityCount);
void searchFunction(Student* students, int studentCount);

/* member management */
void addMember(Student* students, int& studentCount);
void viewMembers(Student* students, int studentCount);
void sortMember(Student* students, int studentCount, int method);
void editMember(Student* students, int& studentCount);
void removeMember(Student* students, int& studentCount);

/* announcement management */
void loadAnnouncements(Announcement* announcements, int& announcementCount);
void saveAllAnnouncements(Announcement* announcements, int announcementCount);
int  getNextAnnouncementID(Announcement* announcements, int announcementCount);
void displayAnnouncement(Announcement& a, int displayIndex);
void displayAllAnnouncements(Announcement* announcements, int announcementCount, string filterStatus = "");
void announcementManagement(Announcement* announcements, int announcementannouncementCount, string officerName);
void proposeAnnouncement(Announcement* announcements, int& announcementCount, string officerName);
void viewAnnouncements(Announcement* announcements, int& announcementCount);
void editAnnouncement(Announcement* announcements, int announcementCount);
void removeAnnouncement(Announcement* announcements, int& announcementCount);
void pinUrgentAnnouncement(Announcement* announcements, int announcementCount);
void viewRejectedAnnouncements(Announcement* announcements, int& announcementCount);
void displayBulletin(Announcement* announcements);


/* activity management */
/* activity management */
void loadActivities(Activity* activities, int& activityCount);
void saveAllActivities(Activity* activities, int activityCount);
int  getNextActivityID(Activity* activities, int activityCount);
void displayActivity(Activity& a);
void displayAllActivities(Activity* activities, int activityCount);
void sortActivity(Activity* activities, int activityCount, int method);
void addActivity(Activity* activities, int& activityCount);
void viewActivities(Activity* activities, int& activityCount);
void updateActivity(Activity* activities, int activityCount);
void deleteActivity(Activity* activities, int& activityCount);
bool isValidDate(string date);
bool isValidTime(string time);

/* search */
int searchMember(Student* students, int studentCount, string target, string searchValue="");
void displayMember(Student* students, int index=0);

// faculty module
void facultyMenu();
void facultySwitch(int choice, Announcement* announcements, int announcementCount);

/* announcement management */
void facultyAnnouncementManagement(Announcement* announcements, int& count);
void reviewPendingAnnouncements(Announcement* announcements, int& count);


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

    Announcement announcements[MAX_ANNOUNCEMENTS];
    Activity activities[MAX_ACTIVITIES];

    int role = 0;
    int studentCount = 0;
    int officerCount = 0;
    int facultyCount = 0;
    int accIndex = 0;

    int announcementCount = 0;
    int activityCount = 0;

    srand(time(0));

    // oad data from files
    loadIDPassFromFile(students,studentCount);
    loadIDPassFromFile(officers, officerCount);
    loadIDPassFromFile(faculty, facultyCount);

    displayHeader();

    int choice = 0;

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
                    displayName(officers[accIndex].name);
                    displayCounterUpdates(studentCount,announcementCount,activityCount);
                    officerMenu();
                    enterPrompt("\nEnter choice: ",choice);
                    clScreen();
                    officerSwitch(choice, students, studentCount, announcements, announcementCount, activities, activityCount, officers, accIndex);
                } while(choice != 5);

                break;

            case 3:
                // faculty
                clScreen();

                do{
                    displayHeader2();
                    facultyMenu();
                    enterPrompt("\nEnter choice: ",choice);
                    facultySwitch(choice,announcements,announcementCount);
                    clScreen();
                }  while(choice != 6);

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
    cout << "|" << right << setw(48) << "⚙️ OFFICER'S DASHBOARD 📊 " << right << setw(16) << "|\n";
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
        cout << "\n                   ==> Role: Student <==\n";
        studentLogin(students,studentCount,accIndex,isLoggedIn);
    } else if(role == 2){
        clScreen();
        displayHeader();
        cout << "\n============== >>> Login to your account <<< ==============\n";
        cout << "\n                   ==> Role: Officer <==\n";
        officerLogin(students, officers, faculty, role, studentCount, officerCount, facultyCount, accIndex, isLoggedIn);
    } else if(role == 3){
        clScreen();
        displayHeader();
        cout << "\n============== >>> Login to your account <<< ==============\n";
        cout << "\n                   ==> Role: Faculty <==\n";
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
    isLoggedIn = true;
    pauseScreen();
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

void displayName(string name){
    size_t getSpace = name.find(' ');
    string displayName = name.substr(0,getSpace);
    cout << "\nGood day, " << displayName << "! 👋\n";
    cout << "Here's what happening in iBITS today!\n";
    cout << "" << getCurrentDate() << endl;
}

string getCurrentDate() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);

    return string(buffer);
}

/// officer's module
void officerMenu(){
    cout << "\n[1] 👥 Member Management";
    cout << "\n[2] 📢 Announcement Management";
    cout << "\n[3] 📅 Activity Management";
    cout << "\n[4] 🔍 Search\n";
    cout << "[5] 🚪 Log Out\n";
}

void officerSwitch(int choice, Student* students, int& studentCount, Announcement* announcements, int& announcementCount, Activity* activities, int& activityCount, Officer* officers, int accIndex){
    loadIDPassFromFile(students, studentCount);

    switch(choice){
        case 1:
            displayHeader2();
            memberManagement(students, studentCount);
            break;

        case 2:
            displayHeader2();
            announcementManagement(announcements, announcementCount, officers[accIndex].name);
            break;

        case 3:
            displayHeader2();
            activityManagement(activities,activityCount);
            break;

        case 4:
            searchFunction(students, studentCount);
            break;

        case 5:
            break;

        default:
            cout << "\n[!] Invalid choice. Try again.\n";
    }
}

// member management
void memberManagement(Student* students, int& studentCount){
    int memberChoice = 0;

    do{
        clScreen();
        displayHeader2();
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
                displayHeader2();
                if(studentCount <= 0){
                    cout << "\n[!] No students record yet. Go to Add Member.\n";
                    return;
                }
                displayHeader2();
                editMember(students,studentCount);
                break;

            case 4:
                // remove member
                //displayHeader2();
                clScreen();
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
                cout << endl;
        }
    } while(memberChoice != 5);

    clScreen();
}

/** Member management functions **/
void addMember(Student* students, int& studentCount){
    clScreen();
    displayHeader2();
    SetConsoleOutputCP(CP_UTF8);
    cout << "\n" << right << setw(38) << "----------------";
    cout << "\n" << right << setw(42) << "👥 Add Member 👥" << "\n";
    cout << right << setw(38) << "----------------" << "\n";
    enterPrompt("\n🆔 Enter Student ID: ", students[studentCount].ID);
    enterPrompt("👤Enter Student Name: ", students[studentCount].name);

    enterPrompt("📚 Enter Program: ", students[studentCount].program);
    /*while(students[studentCount].program != "BSIT" && students[studentCount].program != "DIT"  &&
          students[studentCount].program != "bsit" && students[studentCount] != "dit"){
            cout << "\n[!] Program must be BSIT or DIT only.\n\n";
            enterPrompt("💻 Enter Program: ", students[studentCount].program, 26);
    }*/

    enterPrompt("⭐ Enter Year Level: ", students[studentCount].yearLevel);
    while(students[studentCount].yearLevel >= 5){
            cout << "\n[!] Valid year level are Years 1 to 4 only.\n\n";
            enterPrompt("\n⭐ Enter Year Level: ",students[studentCount].yearLevel);
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
        displayHeader2();
        loadIDPassFromFile(students,studentCount);

        cout << "\n" << right << setw(40) << "---------------------";
        cout << "\n" << right << setw(39) << ">>> Member list <<<";
        cout << "\n" << right << setw(42) << "---------------------\n\n";
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
    clScreen();
    displayHeader2();
    loadIDPassFromFile(students, studentCount);

    cout << "\n" << right << setw(40) << "----------------------";
    cout << "\n" << right << setw(39) << ">>> Edit Member  <<<";
    cout << "\n" << right << setw(42) << "----------------------\n\n";

    string target;
    enterPrompt("\n👤 Enter name of member to edit: ", target);

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
        SetConsoleOutputCP(CP_UTF8);
        case 1:
            enterPrompt("\n🆔 Edit ID: ", stud->ID);
            break;
        case 2:
            enterPrompt("\n👤 Edit Name: ", stud->name);
            break;
        case 3:
            enterPrompt("\n📚 Edit Program: ", stud->program);
            break;
        case 4:
            enterPrompt("\n⭐ Edit Year Level: ", stud->yearLevel);
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

    cout << "\n" << right << setw(40) << "-----------------------";
    cout << "\n" << right << setw(39) << ">>> Remove Member <<<";
    cout << "\n" << right << setw(42) << "-----------------------\n\n";

    string target;
    enterPrompt("\n👤 Enter name of member to remove: ", target);

    int memberIdx = searchMember(students, studentCount, target, "Name");

    if(memberIdx == -1){
        cout << "\n[!] Member not found.\n";
        pauseScreen();
        return;
    }

    // display found member before confirming
    cout << "\n\n";
    displayMember(students, memberIdx);

    char confirm;
    cout << "\n\n--------------------------------------------------------------------\n";
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
void announcementManagement(Announcement* announcements, int announcementCount, string officerName) {
    loadAnnouncements(announcements, announcementCount);

    int choice = 0;

    do {
        clScreen();
        displayHeader2();

        // Count pending/rejected for officer awareness
        int pendingCount  = 0;
        for (int i = 0; i < announcementCount; i++) {
            if (announcements[i].status == "Pending")  pendingCount++;
        }

        cout << "\n" << right << setw(43) << "--------------------------";
        cout << "\n" << right << setw(49) << "📢 Announcement Management 📢\n";
        cout << right << setw(44) << "--------------------------\n";

        if (pendingCount > 0)
            cout << "\n[⏳] " << pendingCount << " announcement(s) awaiting faculty approval.\n";

        cout << "\n[1] Propose Announcement";
        cout << "\n[2] View Approved Announcements";
        cout << "\n[3] View My Pending Announcements";
        cout << "\n[4] View Rejected Announcements";
        cout << "\n[5] Edit Announcement";
        cout << "\n[6] Remove Announcement";
        cout << "\n[7] Pin / Mark as Urgent";
        cout << "\n[8] Return to Main Menu\n";

        enterPrompt("\nEnter choice: ", choice);

        switch (choice) {
            case 1:
                clScreen(); displayHeader2();
                proposeAnnouncement(announcements, announcementCount, officerName);
                break;

            case 2:
                clScreen(); displayHeader2();
                loadAnnouncements(announcements, announcementCount);
                displayAllAnnouncements(announcements, announcementCount, "Approved");
                pauseScreen();
                break;

            case 3:
                clScreen(); displayHeader2();
                loadAnnouncements(announcements, announcementCount);
                cout << "\n📋 Your Pending Announcements (awaiting faculty approval):\n";
                displayAllAnnouncements(announcements, announcementCount, "Pending");
                pauseScreen();
                break;

            case 4:
                clScreen(); displayHeader2();
                viewRejectedAnnouncements(announcements, announcementCount);
                break;

            case 5:
                clScreen(); displayHeader2();
                if (announcementCount <= 0) { cout << "\n[!] No announcements yet.\n"; pauseScreen(); break; }
                editAnnouncement(announcements, announcementCount);
                break;

            case 6:
                clScreen(); displayHeader2();
                if (announcementCount <= 0) { cout << "\n[!] No announcements yet.\n"; pauseScreen(); break; }
                removeAnnouncement(announcements, announcementCount);
                break;

            case 7:
                clScreen(); displayHeader2();
                if (announcementCount <= 0) { cout << "\n[!] No announcements yet.\n"; pauseScreen(); break; }
                pinUrgentAnnouncement(announcements, announcementCount);
                break;

            case 8:
                break;

            default:
                cout << "\n[!] Invalid choice.\n";
                pauseScreen();
        }
    } while (choice != 8);

    clScreen();
}

void loadAnnouncements(Announcement* announcements, int& announcementCount) {
    ifstream file("announcements.txt");
    announcementCount = 0;

    if (!file.is_open()) return;

    string line;
    while (getline(file, line) && announcementCount < MAX_ANNOUNCEMENTS) {
        if (line == "---") {
            Announcement a;
            string idStr;

            getline(file, idStr);
            getline(file, a.title);
            getline(file, a.content);
            getline(file, a.date);
            getline(file, a.postedBy);
            getline(file, a.status);
            getline(file, a.rejectionReason);

            if (!idStr.empty()) {
                a.id = atoi(idStr.c_str());
                announcements[announcementCount++] = a;
            }
        }
    }

    file.close();
}

// Save all to announcements.txt
void saveAllAnnouncements(Announcement* announcements, int announcementCount) {
    ofstream file("announcements.txt", ios::trunc);

    if (!file.is_open()) {
        cout << "\n[!] Error: Could not open announcements.txt\n";
        return;
    }

    for (int i = 0; i < announcementCount; i++) {
        file << "---\n";
        file << announcements[i].id              << "\n";
        file << announcements[i].title           << "\n";
        file << announcements[i].content         << "\n";
        file << announcements[i].date            << "\n";
        file << announcements[i].postedBy        << "\n";
        file << announcements[i].status          << "\n";
        file << announcements[i].rejectionReason << "\n";
    }

    file.close();
}

int getNextAnnouncementID(Announcement* announcements, int announcementCount) {
    if (announcementCount == 0) return 1;
    int maxID = 0;
    for (int i = 0; i < announcementCount; i++)
        if (announcements[i].id > maxID) maxID = announcements[i].id;
    return maxID + 1;
}

// Display one announcement — shows rejection reason if rejected
void displayAnnouncement(Announcement& a, int displayIndex) {
    string badge = "";
    if (a.status == "Pinned")   badge = " 📌";
    else if (a.status == "Urgent")   badge = " 🚨";
    else if (a.status == "Pending")  badge = " ⏳";
    else if (a.status == "Rejected") badge = " ❌";

    cout << "\n----------------------------------------------------------\n";
    cout << badge << " ID: " << a.id << " | " << a.status << "\n\n";
    cout << "  Title    : " << a.title     << "\n";
    cout << "----------------------------------------------------------\n";
    cout << "  Content  : ";
    stringstream ss(a.content); string word; size_t currentLength = 0;
    while(ss >> word){
        if(currentLength + word.length() > 45){
            cout << "\n             ";
            currentLength = 0;
        }
        cout << word << " ";
        currentLength += word.length() + 1;
    }
    cout << "\n----------------------------------------------------------";
    cout << "\n  Date     : " << a.date      << "\n";
    cout << "  Posted by: " << a.postedBy  << "\n";
    if (a.status == "Rejected" && !a.rejectionReason.empty())
        cout << "  Reason   : " << a.rejectionReason << "\n";
    cout << "----------------------------------------------------------\n";
}

void displayAllAnnouncements(Announcement* announcements, int announcementCount, string filterStatus) {
    bool anyShown = false;

    cout << "\n==========================================================";
    if (filterStatus == "Approved" || filterStatus == "")
        cout << "\n              📢 ANNOUNCEMENTS BOARD 📢";
    else if (filterStatus == "Pending")
        cout << "\n              ⏳ PENDING ANNOUNCEMENTS ⏳";
    else if (filterStatus == "Rejected")
        cout << "\n              ❌ REJECTED ANNOUNCEMENTS ❌";
    cout << "\n==========================================================\n";

    int display = 1;

    auto show = [&](string status) {
        for (int i = 0; i < announcementCount; i++) {
            bool match = false;
            if (filterStatus == "Approved")
                match = (announcements[i].status == status &&
                        (status == "Urgent" || status == "Pinned" || status == "Approved"));
            else if (filterStatus == "")
                match = (announcements[i].status == status);
            else
                match = (announcements[i].status == filterStatus && announcements[i].status == status);

            if (match) {
                displayAnnouncement(announcements[i], display++);
                anyShown = true;
            }
        }
    };

    if (filterStatus == "Approved" || filterStatus == "") {
        show("Urgent");
        show("Pinned");
        show("Approved");
    }
    if (filterStatus == "Pending"  || filterStatus == "") show("Pending");
    if (filterStatus == "Rejected" || filterStatus == "") show("Rejected");

    if (!anyShown)
        cout << "\n  (No announcements to display)\n";
}

void proposeAnnouncement(Announcement* announcements, int& announcementCount, string officerName) {
    SetConsoleOutputCP(CP_UTF8);
    cout << "\n" << right << setw(43) << "----------------------------";
    cout << "\n" << right << setw(47) << "📢 Propose Announcement 📢\n";
    cout << right << setw(43) << "----------------------------\n";

    if (announcementCount >= MAX_ANNOUNCEMENTS) {
        cout << "\n[!] Announcement list is full.\n";
        pauseScreen();
        return;
    }

    Announcement newA;
    newA.id              = getNextAnnouncementID(announcements, announcementCount);
    newA.postedBy        = officerName;
    newA.date            = getCurrentDate();
    newA.rejectionReason = "";

    enterPrompt("\n📋 Title  : ", newA.title);
    enterPrompt("📝 Content: ", newA.content);

    cout << "\n📌 Set Status:\n";
    cout << "[1] Normal\n";
    cout << "[2] 🚨 Urgent\n";
    int statusChoice;
    enterPrompt("Choose: ", statusChoice);

    while(statusChoice != 1 && statusChoice != 2){
        cout << "\n[!] Invalid choice.\n";
        enterPrompt("Choose: ", statusChoice);
    }

    if(statusChoice == 2){
        newA.status = "Urgent";
        cout << "\n[✔] Announcement marked Urgent and posted immediately.\n";
    } else {
        newA.status = "Pending";
        cout << "\n[✔] Announcement submitted! Waiting for faculty approval.\n";
    }

    announcements[announcementCount++] = newA;
    saveAllAnnouncements(announcements, announcementCount);
    pauseScreen();
}


// Officer: View rejected announcements with reasons
void viewRejectedAnnouncements(Announcement* announcements, int& announcementCount) {
    loadAnnouncements(announcements, announcementCount);
    displayAllAnnouncements(announcements, announcementCount, "Rejected");
    pauseScreen();
}

// Officer: Edit (only Pending or Rejected announcements — re-submits as Pending)
void editAnnouncement(Announcement* announcements, int announcementCount) {
    cout << "\n  Note: You can only edit Pending or Rejected announcements.\n";
    cout << "  Editing a Rejected announcement re-submits it for approval.\n";

    displayAllAnnouncements(announcements, announcementCount, "Pending");
    displayAllAnnouncements(announcements, announcementCount, "Rejected");

    int targetID;
    enterPrompt("\n\n🆔 Enter Announcement ID to edit: ", targetID);

    int found = -1;
    for (int i = 0; i < announcementCount; i++) {
        if (announcements[i].id == targetID &&
           (announcements[i].status == "Pending" || announcements[i].status == "Rejected")) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        cout << "\n[!] ID not found or announcement is already approved.\n";
        pauseScreen();
        return;
    }

    cout << "\nWhat do you want to edit?\n";
    cout << "[1] Title\n[2] Content\n";
    int editChoice;
    enterPrompt("Choose: ", editChoice);

    switch (editChoice) {
        case 1: enterPrompt("\n📋 New Title: ", announcements[found].title);   break;
        case 2: enterPrompt("\n📝 New Content: ", announcements[found].content); break;
        default:
            cout << "\n[!] Invalid choice.\n";
            pauseScreen();
            return;
    }

    // Re-submit as Pending after edit
    announcements[found].status          = "Pending";
    announcements[found].rejectionReason = "";

    saveAllAnnouncements(announcements, announcementCount);
    cout << "\n[✔] Announcement updated and re-submitted for faculty approval.\n";
    pauseScreen();
}

// Officer: Remove any of their announcements
void removeAnnouncement(Announcement* announcements, int& announcementCount) {
    displayAllAnnouncements(announcements, announcementCount, "");

    int targetID;
    enterPrompt("\n🆔 Enter Announcement ID to remove: ", targetID);

    int found = -1;
    for (int i = 0; i < announcementCount; i++) {
        if (announcements[i].id == targetID) { found = i; break; }
    }

    if (found == -1) {
        cout << "\n[!] Announcement ID not found.\n";
        pauseScreen();
        return;
    }

    displayAnnouncement(announcements[found], found + 1);

    char confirm;
    cout << "\n--------------------------------------------------------------------\n";
    enterPrompt("Confirm removal? (Y/N): ", confirm);

    if (confirm == 'Y' || confirm == 'y') {
        for (int i = found; i < announcementCount - 1; i++)
            announcements[i] = announcements[i + 1];
        announcementCount--;

        saveAllAnnouncements(announcements, announcementCount);
        cout << "\n[✔] Announcement removed successfully.\n";
    } else {
        cout << "\n[i] Operation cancelled.\n";
    }

    pauseScreen();
}

// Officer: Pin / Urgent — only for Approved announcements
void pinUrgentAnnouncement(Announcement* announcements, int announcementCount) {
    cout << "\n  Note: Only approved announcements can be pinned or marked urgent.\n";
    displayAllAnnouncements(announcements, announcementCount, "Approved");

    int targetID;
    enterPrompt("\n🆔 Enter Announcement ID: ", targetID);

    int found = -1;
    for (int i = 0; i < announcementCount; i++) {
        if (announcements[i].id == targetID &&
           (announcements[i].status == "Approved" ||
            announcements[i].status == "Pinned" ||
            announcements[i].status == "Urgent")) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        cout << "\n[!] ID not found or not yet approved.\n";
        pauseScreen();
        return;
    }

    cout << "\nSet status:\n";
    cout << "[1] 📌 Pinned\n[2] 🚨 Urgent\n[3] Approved\n";
    int statusChoice;
    enterPrompt("Choose: ", statusChoice);

    switch (statusChoice) {
        case 1: announcements[found].status = "Pinned"; break;
        case 2: announcements[found].status = "Urgent"; break;
        case 3: announcements[found].status = "Normal"; break;
        default:
            cout << "\n[!] Invalid choice.\n";
            pauseScreen();
            return;
    }

    saveAllAnnouncements(announcements, announcementCount);
    cout << "\n[✔] Status updated to: " << announcements[found].status << "\n";
    pauseScreen();
}

/** Activity Management Functions **/
void activityManagement(Activity* activities, int& activityCount){
    loadActivities(activities, activityCount);
    int choice = 0;

    do{
        clScreen();
        displayHeader2();
        cout << "\n" << right << setw(44) << "--------------------------";
        cout << "\n" << right << setw(47) << "📅 Activity Management 📅" << "\n";
        cout << right << setw(44) << "--------------------------" << "\n";
        cout << "\n[1] Add Activity";
        cout << "\n[2] View Activities";
        cout << "\n[3] Update Activity";
        cout << "\n[4] Delete Activity";
        cout << "\n[5] Return to Main Menu\n";

        enterPrompt("\nEnter choice: ", choice);

        switch(choice){
            case 1:
                clScreen(); displayHeader2();
                addActivity(activities, activityCount);
                break;

            case 2:
                clScreen(); displayHeader2();
                if(activityCount <= 0){ cout << "\n[!] No activities yet.\n"; pauseScreen(); break; }
                viewActivities(activities, activityCount);
                break;

            case 3:
                clScreen(); displayHeader2();
                if(activityCount <= 0){ cout << "\n[!] No activities yet.\n"; pauseScreen(); break; }
                updateActivity(activities, activityCount);
                break;

            case 4:
                clScreen(); displayHeader2();
                if(activityCount <= 0){ cout << "\n[!] No activities yet.\n"; pauseScreen(); break; }
                deleteActivity(activities, activityCount);
                break;

            case 5:
                break;

            default:
                cout << "\n[!] Invalid choice. Try again.\n";
        }
    } while(choice != 5);

    clScreen();
}

void loadActivities(Activity* activities, int& activityCount){
    ifstream file("activities.txt");
    activityCount = 0;

    if(!file.is_open()) return;

    string line;
    while(getline(file, line) && activityCount < MAX_ACTIVITIES){
        if(line == "---"){
            Activity a;
            string idStr;

            getline(file, idStr);
            getline(file, a.name);
            getline(file, a.description);
            getline(file, a.date);
            getline(file, a.time);
            getline(file, a.location);
            getline(file, a.participants);
            getline(file, a.status);

            if(!idStr.empty()){
                a.id = atoi(idStr.c_str());
                activities[activityCount++] = a;
            }
        }
    }

    file.close();
}

void saveAllActivities(Activity* activities, int activityCount){
    ofstream file("activities.txt", ios::trunc);

    if(!file.is_open()){
        cout << "\n[!] Error: Could not open activities.txt\n";
        return;
    }

    for(int i = 0; i < activityCount; i++){
        file << "---\n";
        file << activities[i].id          << "\n";
        file << activities[i].name        << "\n";
        file << activities[i].description << "\n";
        file << activities[i].date        << "\n";
        file << activities[i].time        << "\n";
        file << activities[i].location    << "\n";
        file << activities[i].participants<< "\n";
        file << activities[i].status      << "\n";
    }

    file.close();
}

int getNextActivityID(Activity* activities, int activityCount){
    if(activityCount == 0) return 1;
    int maxID = 0;
    for(int i = 0; i < activityCount; i++)
        if(activities[i].id > maxID) maxID = activities[i].id;
    return maxID + 1;
}

bool isValidDate(string date){
    if(date.length() != 10) return false;
    if(date[2] != '/' || date[5] != '/') return false;
    for(int i = 0; i < 10; i++){
        if(i == 2 || i == 5) continue;
        if(!isdigit(date[i])) return false;
    }
    return true;
}

bool isValidTime(string time){
    if(time.length() != 5) return false;
    if(time[2] != ':') return false;
    for(int i = 0; i < 5; i++){
        if(i == 2) continue;
        if(!isdigit(time[i])) return false;
    }
    return true;
}

void displayActivity(Activity& a){
    cout << "\n----------------------------------------------------------\n";
    cout << "  ID       : " << a.id          << "\n";
    cout << "  Name     : " << a.name        << "\n";
    cout << "\n----------------------------------------------------------\n";
    cout << "  Desc     : ";
    stringstream ss(a.description); string word; size_t currentLength = 0;
    while(ss >> word){
        if(currentLength + word.length() > 40){ cout << "\n               "; currentLength = 0; }
        cout << word << " ";
        currentLength += word.length() + 1;
    }
    cout << "\n----------------------------------------------------------\n";
    cout << "  Date     : " << a.date        << "\n";
    cout << "  Time     : " << a.time        << "\n";
    cout << "  Location : " << a.location    << "\n";
    cout << "  Participants: " << a.participants << "\n";
    cout << "----------------------------------------------------------\n";
}

void displayAllActivities(Activity* activities, int activityCount){
    cout << "\n==========================================================";
    cout << "\n                 📅 ACTIVITIES LIST 📅";
    cout << "\n==========================================================\n";
    cout << left << setw(6) << "ID" << setw(22) << "Name" << setw(13) << "Date"
         << setw(8) << "Time" << "Location\n";
    cout << "----------------------------------------------------------\n";
    for(int i = 0; i < activityCount; i++){
        cout << left << setw(6)  << activities[i].id
                     << setw(22) << activities[i].name
                     << setw(13) << activities[i].date
                     << setw(8)  << activities[i].time
                     << activities[i].location << "\n";
    }
    cout << "----------------------------------------------------------\n";
}

void sortActivity(Activity* activities, int activityCount, int method){
    for(int i = 0; i < activityCount - 1; i++){
        for(int j = 0; j < activityCount - 1 - i; j++){
            bool swap = false;
            if(method == 1)      swap = activities[j].date > activities[j+1].date;
            else if(method == 2) swap = activities[j].name > activities[j+1].name;
            else if(method == 3) swap = activities[j].id   > activities[j+1].id;

            if(swap){
                Activity temp   = activities[j];
                activities[j]   = activities[j+1];
                activities[j+1] = temp;
            }
        }
    }
}

void addActivity(Activity* activities, int& activityCount){
    clScreen();
    displayHeader2();
    cout << "\n" << right << setw(40) << "--------------------";
    cout << "\n" << right << setw(44) << "📅 Add Activity 📅\n";
    cout << right << setw(40) << "--------------------\n";

    if(activityCount >= MAX_ACTIVITIES){
        cout << "\n[!] Activity list is full.\n";
        pauseScreen();
        return;
    }

    Activity newA;
    newA.id     = getNextActivityID(activities, activityCount);
    newA.status = "Scheduled";

    enterPrompt("\n📌 Activity Name: ", newA.name);
    enterPrompt("📝 Description: ", newA.description);

    do {
        enterPrompt("📅 Date (DD/MM/YYYY): ", newA.date);
        if(!isValidDate(newA.date)) cout << "\n[!] Enter a valid date (DD/MM/YYYY).\n";
    } while(!isValidDate(newA.date));

    do {
        enterPrompt("🕐 Time (HH:MM)     : ", newA.time);
        if(!isValidTime(newA.time)) cout << "\n[!] Enter a valid time (HH:MM).\n";
    } while(!isValidTime(newA.time));

    enterPrompt("📍 Location         : ", newA.location);
    enterPrompt("👥 Participants      : ", newA.participants);

    activities[activityCount++] = newA;
    saveAllActivities(activities, activityCount);

    cout << "\n[✔] Activity added successfully.\n";
    pauseScreen();
}

void viewActivities(Activity* activities, int& activityCount){
    int returnOrSort;

    do{
        clScreen();
        displayHeader2();
        loadActivities(activities, activityCount);
        displayAllActivities(activities, activityCount);

        cout << "\nSort by: [1] Date     [2] Name     [3] ID     [4] Return to Menu\n";
        enterPrompt("Choose: ", returnOrSort);

        if(returnOrSort >= 1 && returnOrSort <= 3){
            sortActivity(activities, activityCount, returnOrSort);
            saveAllActivities(activities, activityCount);
        }
    } while(returnOrSort != 4);
}

void updateActivity(Activity* activities, int activityCount){
    loadActivities(activities, activityCount);
    displayAllActivities(activities, activityCount);

    int targetID;
    enterPrompt("\n🆔 Enter Activity ID to update: ", targetID);

    int found = -1;
    for(int i = 0; i < activityCount; i++){
        if(activities[i].id == targetID){ found = i; break; }
    }

    if(found == -1){
        cout << "\n[!] Activity not found.\n";
        pauseScreen();
        return;
    }

    displayActivity(activities[found]);

    cout << "\n[1] Name  [2] Description  [3] Date  [4] Time  [5] Location  \n[6] Participants\n";
    int editChoice;
    enterPrompt("\nChoose field to update: ", editChoice);

    switch(editChoice){
        case 1: enterPrompt("\n📌 New Name: ", activities[found].name);         break;
        case 2: enterPrompt("\n📝 New Description: ", activities[found].description);  break;
        case 3:
            do {
                enterPrompt("\n📅 New Date (DD/MM/YYYY): ", activities[found].date);
                if(!isValidDate(activities[found].date)) cout << "\n[!] Enter a valid date (DD/MM/YYYY).\n";
            } while(!isValidDate(activities[found].date));
            break;
        case 4:
            do {
                enterPrompt("\n🕐 New Time (HH:MM): ", activities[found].time);
                if(!isValidTime(activities[found].time)) cout << "\n[!] Enter a valid time (HH:MM).\n";
            } while(!isValidTime(activities[found].time));
            break;
        case 5: enterPrompt("\n📍 New Location    : ", activities[found].location);     break;
        case 6: enterPrompt("\n👥 New Participants: ", activities[found].participants);  break;
        default:
            cout << "\n[!] Invalid choice.\n";
            pauseScreen();
            return;
    }

    activities[found].status = "Modified";
    saveAllActivities(activities, activityCount);
    cout << "\n[✔] Activity updated successfully.\n";
    pauseScreen();
}

void deleteActivity(Activity* activities, int& activityCount){
    loadActivities(activities, activityCount);
    displayAllActivities(activities, activityCount);

    int targetID;
    enterPrompt("\n🆔 Enter Activity ID to delete: ", targetID);

    // binary search — array sorted by ID from file order
    int lo = 0, hi = activityCount - 1, found = -1;
    while(lo <= hi){
        int mid = (lo + hi) / 2;
        if(activities[mid].id == targetID){ found = mid; break; }
        else if(activities[mid].id < targetID) lo = mid + 1;
        else hi = mid - 1;
    }

    if(found == -1){
        cout << "\n[!] Activity not found.\n";
        pauseScreen();
        return;
    }

    displayActivity(activities[found]);

    char confirm;
    cout << "\n----------------------------------------------------------\n";
    enterPrompt("Confirm deletion? (Y/N): ", confirm);

    if(confirm == 'Y' || confirm == 'y'){
        for(int i = found; i < activityCount - 1; i++)
            activities[i] = activities[i+1];
        activityCount--;

        saveAllActivities(activities, activityCount);
        cout << "\n[✔] Activity deleted successfully.\n";
    } else {
        cout << "\n[i] Operation cancelled.\n";
    }

    pauseScreen();
}

/** Search Functionalities **/
void searchFunction(Student* students,int studentCount){
    int searchChoice = 0;

    do{
       displayHeader2();
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
                clScreen();
                displayHeader2();

                cout << "\n" << right << setw(43) << "-----------------------------";
                cout << "\n" << right << setw(46) << ">>> 🔍 Search Member 👥 <<<";
                cout << "\n" << right << setw(45) << "-----------------------------\n\n";

                char searchIdName;
                enterPrompt("\nSearch Member by [I]D or [N]ame: ",searchIdName);
                pauseScreen();

                if(searchIdName == 'I' || searchIdName == 'i'){
                    clScreen();
                    displayHeader2();
                    searchValue = "ID";

                    cout << "\n" << right << setw(44) << ">>> Search by ID <<<\n\n";
                    enterPrompt("🆔 Enter ID to search: ",target);

                    int idIndex = searchMember(students,studentCount,target,searchValue);

                    if(idIndex == -1){
                        cout << "\n[!] Member with that ID not found.\n";
                    } else {
                        cout << "\n[/] Member found\n\n\n";
                        displayMember(students,idIndex);
                    }
                } else if(searchIdName == 'N' || searchIdName == 'n'){
                    clScreen();
                    displayHeader2();
                    searchValue = "Name";
                    cout << "\n" << right << setw(42) << ">>> Search by Name <<<\n\n";
                    enterPrompt("🔍 Enter Name to search: ",target);

                    int nameIndex = searchMember(students,studentCount,target,searchValue);

                    if(nameIndex == -1){
                        cout << "\n[!] Member with that Name not found.\n";
                    } else {
                        cout << "\n[/] Member found\n\n\n";
                        displayMember(students,nameIndex);
                    }
                } else {
                    cout << "\n[!] Invalid choice. Choose only from the choice above.\n";
                }

                pauseScreen();
                clScreen();
                break;

            case 2:
                // search announcement
                // conditional - id or name?
                clScreen();
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
    cout << "📑Search Result\n";
    cout << "====================================================================\n";
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
    cout << "\n[6] Log Out\n";
}

void facultySwitch(int choice, Announcement* announcements, int announcementCount){
    switch(choice){
        case 1:
            // announcement management
            displayHeader2();
            facultyAnnouncementManagement(announcements,announcementCount);
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

        case 6:
            // log out
            break;

        default:
            cout << "\n[!] Invalid choice. Try again.\n";
    }
}

/** Announcement Management **/
void facultyAnnouncementManagement(Announcement* announcements, int& count) {
    loadAnnouncements(announcements, count);

    int choice = 0;

    do {
        clScreen();
        displayHeader2();

        // Count pending for badge
        int pendingCount = 0;
        for (int i = 0; i < count; i++)
            if (announcements[i].status == "Pending") pendingCount++;

        cout << "\n" << right << setw(43) << "--------------------------";
        cout << "\n" << right << setw(49) << "📢 Announcement Management 📢\n";
        cout << right << setw(43) << "--------------------------\n";

        if (pendingCount > 0)
            cout << "\n  [⏳] " << pendingCount << " announcement(s) pending your approval!\n";

        cout << "\n[1] Review Pending Announcements";
        cout << "\n[2] View All Approved Announcements";
        cout << "\n[3] Return to Main Menu\n";

        enterPrompt("\nEnter choice: ", choice);

        switch (choice) {
            case 1:
                clScreen(); displayHeader2();
                reviewPendingAnnouncements(announcements, count);
                break;

            case 2:
                clScreen(); displayHeader2();
                loadAnnouncements(announcements, count);
                displayAllAnnouncements(announcements, count, "Approved");
                pauseScreen();
                break;

            case 3:
                break;

            default:
                cout << "\n[!] Invalid choice.\n";
                pauseScreen();
        }
    } while (choice != 3);

    clScreen();
}

void reviewPendingAnnouncements(Announcement* announcements, int& count) {
    loadAnnouncements(announcements, count);

    // Collect pending indices
    int pendingIndices[MAX_ANNOUNCEMENTS];
    int pendingCount = 0;
    for (int i = 0; i < count; i++)
        if (announcements[i].status == "Pending")
            pendingIndices[pendingCount++] = i;

    if (pendingCount == 0) {
        cout << "\n[✔] No pending announcements. All caught up!\n";
        pauseScreen();
        return;
    }

    cout << "\n  " << pendingCount << " pending announcement(s) to review.\n";

    for (int p = 0; p < pendingCount; p++) {
        int i = pendingIndices[p];
        clScreen();
        displayHeader2();

        cout << "\n⏳ Reviewing " << (p + 1) << " of " << pendingCount << "\n";
        displayAnnouncement(announcements[i], p + 1);

        cout << "\n[1] ✅ Approve";
        cout << "\n[2] ❌ Reject";
        cout << "\n[3] Skip (decide later)\n";

        int decision;
        enterPrompt("\nYour decision: ", decision);

        if (decision == 1) {
            announcements[i].status          = "Approved";
            announcements[i].rejectionReason = "";
            saveAllAnnouncements(announcements, count);
            cout << "\n[✔] Announcement approved and posted to the board.\n";
            Sleep(1200);

        } else if (decision == 2) {
            string reason = "";
            enterPrompt("\n📝 Enter rejection reason: ", reason);
            announcements[i].status          = "Rejected";
            announcements[i].rejectionReason = reason;
            saveAllAnnouncements(announcements, count);
            cout << "\n[✔] Announcement rejected. Officer will be notified.\n";
            Sleep(1200);

        } else {
            cout << "\n[i] Skipped.\n";
            Sleep(800);
        }
    }

    cout << "\n[✔] Done reviewing all pending announcements.\n";
    pauseScreen();
}

void displayCounterUpdates(int studentCount, int announcementCount, int activityCount){
    cout << "\n\033[1m" << studentCount << "\033[0m \033[3mTotal Members\033[0m";
    cout << "\n\033[1m" << announcementCount << "\033[0m \033[3mActive Announcements\033[0m";
    cout << "\n\033[1m" << activityCount << "\033[0m \033[3mUpcoming Activity\033[0m\n\n";
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

void landingPage() {

}
