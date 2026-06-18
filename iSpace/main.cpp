#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iomanip>

using namespace std;

//_structs
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
    int id;
    string title;
    string content;
    string category;
    string date;
    string postedBy;
    string status;
    string rejectionReason;
    bool isPinned;
    bool isUrgent;
};

struct Activity {
    int id;
    string name;
    string description;
    string date;
    string time;
    string location;
    string participants;
    string status;
};

struct Feedback {
    int id;
    string studentID;
    string recipient;
    string category;
    string content;
    string date;
    string status;
};
// 6 structures

const int MAX_STUDENT = 200;
const int MAX_OFFICER = 30;
const int MAX_FACULTY = 20;
const int MAX_ANNOUNCE = 100;
const int MAX_ACTIVITY = 100;
const int MAX_FEEDBACK = 200;
const int MAX_PENDING = 200;

enum Role {
    STUDENT = 1,
    OFFICER,
    FACULTY
};

//_FUNCTIONS DECLARATION w/total of 106

//_header = 4
void displayHeader();
void displayHeader2();
void displayHeader3();
void displayHeader4();
void displayStudentHeader(const string& name);
void homeScreen(const string& name);

//_auth = 8
void auth(Student* students, int& studentCount, Officer* officers, int& officerCount, Faculty* faculty,  int& facultyCount, int& role, int& accIndex, bool& isLoggedIn);
void askRole(int& role);
void registerAccountHandler(int role, Student* students, int& studentCount, Officer* officers, int& officerCount, Faculty* faculty,  int& facultyCount, bool& isLoggedIn);
void studentRegistration();
void createAccount(int role, Officer* officers, int& officerCount, Faculty* faculty,  int& facultyCount);
string createPasscode();
void login(int role, Student* students, int studentCount, Officer* officers, int officerCount, Faculty* faculty,  int facultyCount, int& accIndex, bool& isLoggedIn);
bool idpassNotFound(bool& var, int& attempt, const string& displayMessage);

//_file_handling = 18
void loadStudents(Student* s, int& count);
void loadOfficers(Officer* o, int& count);
void loadFaculty(Faculty* f, int& count);
void saveStudentsCSV(Student* s, int count);
void saveOfficersCSV(Officer* o, int count);
void saveFacultyCSV(Faculty* f, int count);
void appendToCSV(const string& file, int role, Student* s, int si, Officer* o, int oi, Faculty* f, int fi);
void savePendingStudent(Student& s);
void loadPendingStudents(Student* pending, int& count);
void updatePendingCSV(Student* pending, int count);
int  getPendingRequestCount();
void loadAnnouncements(Announcement* a, int& count);
void saveAllAnnouncements(Announcement* a, int count);
void loadActivities(Activity* a, int& count);
void saveAllActivities(Activity* a, int count);
void loadFeedbacks(Feedback* fb, int& count);
void saveAllFeedbacks(Feedback* fb, int count);
int getNextID(int* ids, int count);

//_sorting (Bubble Sort) = 5
void sortStudents(Student* s, int count, int method);
void sortOfficers(Officer* o, int count, int method);
void sortActivities(Activity* a, int count, int method);
void sortAnnouncements(Announcement* a, int count);

//_searching = 7
int searchByID(Student* s, int count, const string& id);  // Binary
int searchByName(Student* s, int count, const string& name);  // Sequential
int searchOfficerByName(Officer* o, int count, const string& name);
int searchFacultyByName(Faculty* f, int count, const string& name);
int searchActivityByID(Activity* a, int count, int id);  // Binary
int searchAnnouncementByID(Announcement* a, int count, int id);
void searchActivityLinear(Activity* a, int count, const string& query, int* results, int& rCount);

//_bulletin board - 2D Array = 5
void buildAnnouncementTable(Announcement* a, int count, string table[][5], int& rows);
void buildActivityTable(Activity* a, int count, string table[][6], int& rows);
void displayCounterUpdates(int studentCount, int pendingCount, int annCount, int actCount);
int getApprovedAnnCount(Announcement* a, int count);
int getUpcomingActCount(Activity* a, int count);

//_template function = 1
template<typename T>
T getMaxID(T* arr, int count);  // returns max id field

//_dynamic memory allocation | pointer to poiter = 1
Announcement** buildPinnedFirst(Announcement* a, int count, int& outCount);

//_sorting - bubble sort = 2
void sortStudents(Student* s, int count, int method);
void sortOfficers(Officer* o, int count, int method);

//_officer module = 2
void officerMenu();
void officerSwitch(int choice, Student* students, int& studentCount, Announcement* ann, int& annCount, Activity* act, int& actCount,
                  Officer* officers, int officerCount, Faculty* faculty, int facultyCount, int accIndex, Feedback* fb, int& fbCount, int role);// officer module handler - handles the main officer switch
//--member management functoins = 4
void memberManagement(Student* students, int& studentCount);
void approveStudentRequests(Student* students, int& studentCount);
void viewMembers(Student* students, int studentCount);
void removeMember(Student* students, int& studentCount);
//--announcement manfaement functions = 5
void announcementManagement(Announcement* ann, int& annCount, const string& officerName);
void proposeAnnouncement(Announcement* ann, int& annCount, const string& officerName);
void editAnnouncement(Announcement* ann, int annCount);
void removeAnnouncement(Announcement* ann, int& annCount);
void pinUrgentAnnouncement(Announcement* ann, int annCount);
//--announcement display helpers = 2
void displayOneAnnouncement(Announcement& a);
void displayAllAnn(Announcement* a, int count, const string& filter);
//--activuty management functions = 5
void activityManagement(Activity* act, int& actCount);
void addActivity(Activity* act, int& actCount);
void viewActivities(Activity* act, int& actCount);
void updateActivity(Activity* act, int actCount);
void deleteActivity(Activity* act, int& actCount);
//--activity display helpers = 3
void displayOneActivity(Activity& a);
void displayAllAct(Activity* a, int count);
void displayBulletinBoard(Announcement* ann, int annCount, Activity* act, int actCount, int role);
//--feedbacks and cocnerns functions = 4
void viewFeedbacks(Feedback* fb, int& fbCount, int role, int accIndex, Officer* officers,
                   Faculty* faculty, Student* students, int studentCount);
void displayCounterUpdates(int studentCount, int pendingCount, int annCount, int actCount);
int getApprovedAnnCount(Announcement* a, int count);
int getUpcomingActCount(Activity* a, int count);

//_faculty module = 6
void facultyMenu();
void facultySwitch(int choice, Announcement* ann, int& annCount, Student* students, int studentCount, Officer* officers, int officerCount, Feedback* fb, int& fbCount,
                   Faculty* faculty, int facultyCount, int accIndex, int role);  // faculty module handler - handles the main faculty switch
void facultyAnnouncementMgmt(Announcement* ann, int& annCount, const string& facultyName);
void reviewPendingAnn(Announcement* ann, int& annCount);
void viewOfficersAndMembers(Student* students, int studentCount, Officer* officers, int officerCount);

//_student module = 6
void studentDashboard(int homeChoice, Student* students, int studentCount, int accIndex, Announcement* ann, int& annCount, Activity* act, int& actCount, Officer* officers,
                      int officerCount, Faculty* faculty, int facultyCount, Feedback* fb, int& fbCount);  // student module handler - handles the main student switch
void studentMenu();
void viewAnnouncements(Announcement* ann, int& annCount);
void studentViewFaculty(Faculty* faculty, int& facultyCount);
void viewOfficers(Officer* officers, int officerCount);
//--feedbacks and concers = 3
void feedbacksAndConcerns(Feedback* fb, int& fbCount, int accIndex, Student* students, int studentCount, Officer* officers, int officerCount, Faculty* faculty, int facultyCount);
void submitFeedback(Feedback* fb, int& fbCount, int accIndex, Student* students, int studentCount, Officer* officers, int officerCount, Faculty* faculty, int facultyCount);
void viewMyFeedbacks(Feedback* fb, int fbCount, int accIndex, Student* students, int studentCount);

//_account management = 4
void accountManagement(int role, int accIndex, Student* students, int& studentCount, Officer* officers, int& officerCount, Faculty* faculty,  int& facultyCount);
void viewMyInfo(int role, int accIndex, Student* students, Officer* officers, Faculty* faculty);
void editMyInfo(int role, int accIndex, Student* students, int& studentCount, Officer* officers, int& officerCount, Faculty* faculty,  int& facultyCount);
void changePasscode(int role, int accIndex, Student* students, int& studentCount, Officer* officers, int& officerCount, Faculty* faculty,  int& facultyCount);

//_helpers = 10
void pauseScreen();
void cls();
void enterPrompt(const string& prompt, string& val);
void enterPrompt(const string& prompt, int& val);
void enterPrompt(const string& prompt, char& val);
bool isEmpty(const string& str);
string getCurrentDate();
bool isValidDate(const string& date);
bool isValidTime(const string& time);
void landingPage(bool& isLoggedIn);


//_MAIN FUNCTION
int main(){
    Student students[MAX_STUDENT];
    Officer officers[MAX_OFFICER];
    Faculty faculty[MAX_FACULTY];
    Announcement ann[MAX_ANNOUNCE];
    Activity act[MAX_ACTIVITY];
    Feedback fb[MAX_FEEDBACK];

    int studentCount = 0;
    int officerCount = 0;
    int facultyCount = 0;
    int annCount = 0;  // announcement count
    int actCount = 0;  // activity ount
    int fbCount = 0;  // feedback count
    int role = 0;
    int accIndex = 0;  // returns user's index upon login
    bool isLoggedIn = false;
    bool firstRun = true;

    srand(time(0));

    loadStudents(students, studentCount);
    loadOfficers(officers, officerCount);
    loadFaculty(faculty, facultyCount);
    loadAnnouncements(ann, annCount);
    loadActivities(act, actCount);
    loadFeedbacks(fb, fbCount);

    displayHeader();

    do {
        isLoggedIn = false;
        role = 0;
        accIndex = 0;

        if(firstRun){
            auth(students, studentCount, officers, officerCount, faculty, facultyCount, role, accIndex, isLoggedIn);
            firstRun = false;
        } else {
            askRole(role);
            login(role, students, studentCount, officers, officerCount, faculty, facultyCount, accIndex, isLoggedIn);
        }

        if(isLoggedIn){
            // reload all data
            loadStudents(students, studentCount);
            loadOfficers(officers, officerCount);
            loadFaculty(faculty, facultyCount);
            loadAnnouncements(ann, annCount);
            loadActivities(act, actCount);
            loadFeedbacks(fb, fbCount);

            int homeChoice = 0;
            int choice = 0;

            switch(role){
                case STUDENT:
                    do {
                        homeScreen(students[accIndex].name);
                        displayBulletinBoard(ann, annCount, act, actCount, STUDENT);

                        cout << "\n" << right << setw(45) << "------------------------------";
                        cout << "\n" << right << setw(44) << "[1] Menu       [2] Log Out\n";

                        enterPrompt("\nEnter choice: ", homeChoice);

                        studentDashboard(homeChoice, students, studentCount, accIndex, ann, annCount, act,
                                         actCount, officers, officerCount, faculty,  facultyCount, fb, fbCount);
                    }while(homeChoice != 2);
                    break;

                case OFFICER: {
                    cls();
                    int pendingReq = getPendingRequestCount();
                    int approvedAnn = getApprovedAnnCount(ann, annCount);
                    int upcomingAct = getUpcomingActCount(act, actCount);

                    do {
                        loadStudents(students, studentCount);
                        loadAnnouncements(ann, annCount);
                        loadActivities(act, actCount);
                        loadFeedbacks(fb, fbCount);
                        pendingReq = getPendingRequestCount();
                        approvedAnn = getApprovedAnnCount(ann, annCount);
                        upcomingAct = getUpcomingActCount(act, actCount);

                        homeScreen(officers[accIndex].name);
                        displayCounterUpdates(studentCount, pendingReq, approvedAnn, upcomingAct);

                        cout << "\n" << right << setw(45) << "------------------------------";
                        cout << "\n" << right << setw(44) << "[1] Menu       [2] Log Out\n";

                        enterPrompt("\nEnter choice: ", homeChoice);

                        if(homeChoice == 1){
                            do{
                                displayHeader2();
                                officerMenu();
                                enterPrompt("\nEnter choice: ", choice);

                                officerSwitch(choice, students, studentCount, ann, annCount, act, actCount, officers,
                                              officerCount, faculty, facultyCount, accIndex, fb, fbCount,role);
                            }while(choice != 6);
                        } else if(homeChoice == 2){
                            cout << "\nLogging out. Please wait...\n";
                            Sleep(400);
                            cls();
                        } else {
                            cout << "\n[!] Invalid choice.\n";
                        }
                    } while(homeChoice != 2);
                    break;
                }

                case FACULTY: {
                    cls();
                    do {
                        loadAnnouncements(ann, annCount);
                        loadActivities(act, actCount);
                        loadFeedbacks(fb, fbCount);

                        homeScreen(faculty[accIndex].name);
                        displayBulletinBoard(ann, annCount, act, actCount, FACULTY);

                        cout << "\n" << right << setw(45) << "------------------------------";
                        cout << "\n" << right << setw(44) << "[1] Menu       [2] Log Out\n";

                        enterPrompt("\nEnter choice: ", homeChoice);

                        if(homeChoice == 1){
                            do{
                                cls();
                                displayHeader3();
                                facultyMenu();
                                enterPrompt("\nEnter choice: ", choice);

                                cls();
                                facultySwitch(choice, ann, annCount, students, studentCount, officers,
                                              officerCount, fb, fbCount, faculty, facultyCount, accIndex, role);
                            }while(choice != 5);
                        } else if(homeChoice == 2){
                            cout << "\nLogging out. Please wait...\n";
                            Sleep(400);
                            cls();
                        } else {
                            cout << "\n[!] Invalid choice.\n";
                        }
                    } while(homeChoice != 2);
                    break;
                }
            }

            landingPage(isLoggedIn);
        }
    } while(isLoggedIn);

    return 0;
}


//_headers
void displayHeader(){
    cls();
    SetConsoleOutputCP(CP_UTF8);
    cout << "+---------------------------------------------------------+\n";
    cout << "|__________________--✨ iSPACE PORTAL ✨--________________|\n";
    cout << "|               IBITS Portal for Announcements,           |\n";
    cout << "|                  Communication and Events               |\n";
    cout << "+---------------------------------------------------------+\n";
}

void displayHeader2(){
    cls();
    cout << "===========================================================";
    cout << "\n|" << right << setw(39) << " __✨ iSpace ✨__" << right << setw(22) << "|\n";
    cout << "|" << right << setw(59) << "|\n";
    cout << "|" << right << setw(48) << "⚙️ OFFICER'S DASHBOARD 📊 " << right << setw(17) << "|\n";
    cout << "|" << right << setw(58) << "|";
    cout << "\n===========================================================\n";
}

void displayHeader3(){
    cls();
    cout << "===========================================================";
    cout << "\n|" << right << setw(39) << " __✨ iSpace ✨__" << right << setw(22) << "|\n";
    cout << "|" << right << setw(59) << "|\n";
    cout << "|" << right << setw(48) << "⚙️ FACULTY DASHBOARD 📊 " << right << setw(17) << "|\n";
    cout << "|" << right << setw(58) << "|";
    cout << "\n===========================================================\n";
}

void displayHeader4(){
    cls();
    cout << "===========================================================";
    cout << "\n|" << right << setw(39) << " __✨ iSpace ✨__" << right << setw(22) << "|\n";
    cout << "|" << right << setw(59) << "|\n";
    cout << "|" << right << setw(48) << "⚙️ STUDENT DASHBOARD 📊 " << right << setw(17) << "|\n";
    cout << "|" << right << setw(58) << "|";
    cout << "\n===========================================================\n";
}

void homeScreen(const string& name){
    cls();

    displayHeader();
    displayStudentHeader(name);
}

void displayStudentHeader(const string& name){
    size_t spacePos = name.find(' ');
    string firstName = (spacePos != string::npos) ? name.substr(0, spacePos) : name;  // if search for space isn't failed, firstName is the string of characters before the first space

    string line1 = "Good day, " + firstName + "! 👋";
    string line2 = "Here's what's happening in iBITS today!";
    string line3 = getCurrentDate();

    cout << "  " << left << setw(56) << line1 << "\n";
    cout << "  " << line2 << "\n";
    cout << "  " << line3 << "\n";
    cout << "+---------------------------------------------------------+";
}

string getCurrentDate(){
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
    return string(buffer);
}

void auth(Student* students, int& studentCount, Officer* officers, int& officerCount, Faculty* faculty,  int& facultyCount,
          int& role, int& accIndex, bool& isLoggedIn){

    ifstream sf("students.csv");
    ifstream of("officers.csv");
    ifstream ff("faculty.csv");

    bool anyOpen = sf.is_open() || of.is_open() || ff.is_open();

    sf.close(); of.close(); ff.close();

    if(anyOpen){
        SetConsoleOutputCP(CP_UTF8);
        cout << "\n[📂] File successfully opened\n";

        char hasAccount;
        cout << "\nAlready have an account? (Y/N): ";
        cin >> hasAccount;
        cin.ignore();

        if(hasAccount == 'Y' || hasAccount == 'y'){
            askRole(role);
            login(role, students, studentCount, officers, officerCount,
                  faculty, facultyCount, accIndex, isLoggedIn);
        } else {
            askRole(role);
            registerAccountHandler(role, students, studentCount, officers, officerCount,
                                   faculty,  facultyCount, isLoggedIn);
            if(role != STUDENT){
                login(role, students, studentCount, officers, officerCount,
                      faculty, facultyCount, accIndex, isLoggedIn);
            }
        }
    } else {
        cout << "\n\n" << "[!] File doesn't exist yet. Start your account.\n\n";
        pauseScreen();
        askRole(role);
        registerAccountHandler(role, students, studentCount, officers, officerCount, faculty,  facultyCount, isLoggedIn);

        if(role != STUDENT){
            login(role, students, studentCount, officers, officerCount,
                  faculty, facultyCount, accIndex, isLoggedIn);
        }
    }
}

void askRole(int& role){
    cls();
    displayHeader();
    cout << "\n" << right << setw(36) << " ---------------";
    cout << "\n" << right << setw(42) << "🚀>>> Roles <<<🚀\n";
    cout << right << setw(37) << " ---------------\n";
    SetConsoleOutputCP(CP_UTF8);
    cout << "\n[1-👩‍🚀] Student \n[2-🧑‍🎓]️Officer \n[3-🧑‍🏫] Faculty";
    enterPrompt("\n\nEnter role: ", role);

    while(role < 1 || role > 3){
        cout << "\n[!] Invalid role. Select only from role choices.\n";
        enterPrompt("\n\nEnter role: ", role);
    }
    cls();
}

void registerAccountHandler(int role, Student* students, int& studentCount, Officer* officers, int& officerCount, Faculty* faculty,  int& facultyCount, bool& isLoggedIn){
    switch(role){
        case STUDENT:
            studentRegistration();
            landingPage(isLoggedIn);
            break;
        case OFFICER:
            createAccount(role, officers, officerCount, faculty, facultyCount);
            break;
        case FACULTY:
            createAccount(role, officers, officerCount, faculty, facultyCount);
            break;
    }
}

void studentRegistration(){
    cls();
    displayHeader();
    SetConsoleOutputCP(CP_UTF8);
    cout << "\n" << right << setw(54) << "📋 >>> Student Registration <<< 📋\n";
    cout << "           Fill in your details to request an account.\n";
    cout << "\n-----------------------------------------------------------\n";

    Student s;
    enterPrompt("\n🆔 Enter Student ID: ", s.ID);
    enterPrompt("👤 Enter Name: ", s.name);
    enterPrompt("📚 Enter Program: ", s.program);
    while(s.program != "BSIT" && s.program != "bsit" &&
          s.program != "DIT"  && s.program != "dit"){
        cout << "\n[!] Program must be BSIT or DIT only.\n";
        enterPrompt("📚 Enter Program: ", s.program);
    }
    enterPrompt("⭐ Enter Year Level: ", s.yearLevel);
    while(s.yearLevel < 1 || s.yearLevel > 4){
        cout << "\n[!] Valid year levels are 1 to 4 only.\n\n";
        enterPrompt("⭐ Enter Year Level: ", s.yearLevel);
    }

    s.passcode = createPasscode();
    savePendingStudent(s);

    cout << "\n[✔ ] Registration request submitted!\n";
    cout << "[i] Your account is pending Officer approval. Come back once notified.\n";

    pauseScreen();
}

void createAccount(int role, Officer* officers, int& officerCount, Faculty* faculty,  int& facultyCount){
    cls();
    displayHeader();

    SetConsoleOutputCP(CP_UTF8);
    cout << "\n" << right << setw(49) << "📋 >>> Create Account <<< 📋\n";
    cout << right << setw(43) << " Enter required details.\n";

    if(role == OFFICER){
        cout << "\n-----------------------------------------------------------\n";
        cout << right << setw(40) << ">>> Role: Officer <<<\n";
        cout << "-----------------------------------------------------------\n\n";

        int i = officerCount;
        enterPrompt("🆔 Enter ID: ", officers[i].ID);
        enterPrompt("👤 Enter Name: ", officers[i].name);
        enterPrompt("💻 Enter Program: ", officers[i].program);
        while(officers[i].program != "BSIT" && officers[i].program != "bsit" &&
              officers[i].program != "DIT"  && officers[i].program != "dit"){
            cout << "\n[!] Program must be BSIT or DIT only.\n\n";
            enterPrompt("💻 Enter Program: ", officers[i].program);
        }
        enterPrompt("📈 Enter Year Level: ", officers[i].yearLevel);
        while(officers[i].yearLevel < 1 || officers[i].yearLevel > 4){
            cout << "\n[!] Valid year levels are 1 to 4 only.\n\n";
            enterPrompt("📈 Enter Year Level: ", officers[i].yearLevel);
        }
        enterPrompt("🎖️ Enter Position: ", officers[i].position);
        officers[i].passcode = createPasscode();

        appendToCSV("officers.csv", OFFICER, nullptr, 0, officers, i, nullptr, 0);
        officerCount++;

    } else if(role == FACULTY){
        cout << "\n-----------------------------------------------------------\n";
        cout << right << setw(39) << ">>> Role: Faculty <<<\n";
        cout << "-----------------------------------------------------------\n\n";

        int i = facultyCount;
        enterPrompt("🆔 Enter ID: ", faculty[i].ID);
        enterPrompt("👤 Enter Name: ", faculty[i].name);
        faculty[i].passcode = createPasscode();

        appendToCSV("faculty.csv", FACULTY, nullptr, 0, nullptr, 0, faculty, i);
        facultyCount++;
    }
}

string createPasscode(){
    cout << "\n-----------------------------------------------------------\n";
    cout << right << setw(45) << "*** Create your passcode ***\n";
    cout << right << setw(60)
         << "\033[3m📌 Note: Passcode must be minimum of 8 characters\033[0m\n";
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
        cout << "\n[!] Passcodes do not match. Try again.\n";
        enterPrompt("\n🔄 Confirm passcode: ", confirm);
    }
    cout << "\n[🔒] Passcode created.\n";
    return passcode;

    //pauseScreen();
}

void login(int role, Student* students, int studentCount, Officer* officers, int officerCount, Faculty* faculty,  int facultyCount,
           int& accIndex, bool& isLoggedIn){
    displayHeader();
   // pauseScreen();
    cls();
    displayHeader();

    cout << "\n============== >>> Login to your account <<< ==============\n";

    string roleLabel = (role == STUDENT) ? "Student" : (role == OFFICER) ? "Officer" : "Faculty";
    cout << "\n                   ==> Role: " << roleLabel << " <==\n\n";

    string id = "", pass = "";
    bool idFound = false, passFound = false;
    int attempt = 0;

    // Pointer to the right count and a generic find loop
    int maxCount = (role == STUDENT) ? studentCount :
                   (role == OFFICER) ? officerCount : facultyCount;

    while(!idFound){
        enterPrompt("🪪 Enter ID: ", id);
        for(int j = 0; j < maxCount; j++){
            if(role == STUDENT && students[j].ID == id){
                idFound = true; accIndex = j;
                break;
            }
            if(role == OFFICER && officers[j].ID == id){
                idFound = true; accIndex = j;
                break;
            }
            if(role == FACULTY && faculty[j].ID  == id){
                idFound = true; accIndex = j;
                break;
            }
        }

        if(idpassNotFound(idFound, attempt, "[!] ID not found. Try again.\n")){
            if(role == STUDENT){
                cout << "\n-----------------------------------------------------------\n";
                cout << "[!] ID not found. If you registered, wait for Officer approval.\n";
                cout << "-----------------------------------------------------------\n";
            } else {
                createAccount(role, officers, officerCount, faculty, facultyCount);
                login(role, students, studentCount, officers, officerCount,
                      faculty, facultyCount, accIndex, isLoggedIn);
            }
            return;
        }
    }

    attempt = 0;

    while(!passFound){
        enterPrompt("🔑 Enter passcode: ", pass);

        string storedPass = (role == STUDENT) ? students[accIndex].passcode :
                            (role == OFFICER) ? officers[accIndex].passcode : faculty[accIndex].passcode;

        if(storedPass == pass)
            passFound = true;

        if(idpassNotFound(passFound, attempt, "[!] Wrong passcode.\n")){
            // reset passcode
            string newPass = createPasscode();

            if(role == STUDENT){
                students[accIndex].passcode = newPass;
                saveStudentsCSV(students, studentCount);
                loadStudents(students, studentCount);
            } else if(role == OFFICER){
                officers[accIndex].passcode = newPass;
                saveOfficersCSV(officers, officerCount);
                loadOfficers(officers, officerCount);
            } else {
                faculty[accIndex].passcode = newPass;
                saveFacultyCSV(faculty, facultyCount);
                loadFaculty(faculty, facultyCount);
            }

            attempt = 0;
            cout << "\n[i] Passcode reset. Please log in with your new passcode.\n";
        }
    }

    cout << "\n[✔ ] Login Successful!\n";
    isLoggedIn = true;
    pauseScreen();
}

bool idpassNotFound(bool& var, int& attempt, const string& displayMessage){
    if(!var){
        cout << displayMessage;
        attempt++;
        if(attempt == 3){
            char ans;
            cout << "\nIt seems that ID doesn't exist. Do you really have an account? (Y/N): ";
            cin >> ans; cin.ignore();
            if(ans == 'N' || ans == 'n'){
                cout << "\n[!] Redirecting to Create Account. Please wait...\n";
                Sleep(2000);
                return true;
            } else {
                cout << "\n[!] Resetting login attempts. Double-check your input.\n";
                attempt = 0;
                return false;
            }
        }
    }
    return false;
}

void loadStudents(Student* s, int& count){
    ifstream file("students.csv");
    count = 0;

    if(!file.is_open())
        return;

    string line;
    if(getline(file, line)){
        while(getline(file, line) && count < MAX_STUDENT){
            stringstream ss(line);
            string yr;

            getline(ss, s[count].ID, ',');
            getline(ss, s[count].name, ',');
            getline(ss, s[count].program, ',');
            getline(ss, yr, ',');
            getline(ss, s[count].passcode);
            s[count].yearLevel = yr.empty() ? 0 : atoi(yr.c_str());
            count++;
        }
    }
    file.close();
}

void loadOfficers(Officer* o, int& count){
    ifstream file("officers.csv");
    count = 0;

    if(!file.is_open())
        return;

    string line;
    if(getline(file, line)){
        while(getline(file, line) && count < MAX_OFFICER){
            stringstream ss(line);
            string yr;

            getline(ss, o[count].ID, ',');
            getline(ss, o[count].name, ',');
            getline(ss, o[count].program, ',');
            getline(ss, yr, ',');
            getline(ss, o[count].position, ',');
            getline(ss, o[count].passcode);
            o[count].yearLevel = yr.empty() ? 0 : atoi(yr.c_str());
            count++;
        }
    }
    file.close();
}

void loadFaculty(Faculty* f, int& count){
    ifstream file("faculty.csv");
    count = 0;

    if(!file.is_open())
        return;

    string line;
    if(getline(file, line)){
        while(getline(file, line) && count < MAX_FACULTY){
            stringstream ss(line);

            getline(ss, f[count].ID, ',');
            getline(ss, f[count].name, ',');
            getline(ss, f[count].passcode);
            count++;
        }
    }
    file.close();
}

void saveStudentsCSV(Student* s, int count){
    ofstream file("students.csv", ios::trunc);

    if(!file.is_open())
        return;

    file << "ID,Name,Program,Year Level,Passcode\n";

    for(int i = 0; i < count; i++)
        file << s[i].ID << ',' << s[i].name << ',' << s[i].program << ',' << s[i].yearLevel << ',' << s[i].passcode << "\n";

    file.close();
}

void saveOfficersCSV(Officer* o, int count){
    ofstream file("officers.csv", ios::trunc);

    if(!file.is_open())
        return;

    file << "ID,Name,Program,Year Level,Position,Passcode\n";

    for(int i = 0; i < count; i++)
        file << o[i].ID << ',' << o[i].name << ',' << o[i].program << ',' << o[i].yearLevel << ',' << o[i].position << ',' << o[i].passcode << "\n";

    file.close();
}

void saveFacultyCSV(Faculty* f, int count){
    ofstream file("faculty.csv", ios::trunc);

    if(!file.is_open())
        return;

    file << "ID,Name,Passcode\n";

    for(int i = 0; i < count; i++)
        file << f[i].ID << ',' << f[i].name << ',' << f[i].passcode << "\n";

    file.close();
}

void appendToCSV(const string& file, int role, Student* s,  int si, Officer* o,  int oi, Faculty* f,  int fi){
    ifstream check(file);
    bool empty = (check.peek() == ifstream::traits_type::eof());
    check.close();

    ofstream out(file, ios::app);

    if(!out.is_open()){
        cout << "\n[!] Could not open " << file << "\n";
        return;
    }

    if(empty){
        if(role == STUDENT)
            out << "ID,Name,Program,Year Level,Passcode\n";
        if(role == OFFICER)
            out << "ID,Name,Program,Year Level,Position,Passcode\n";
        if(role == FACULTY)
            out << "ID,Name,Passcode\n";
    }

    if(role == STUDENT && s)
        out << s[si].ID << ',' << s[si].name << ',' << s[si].program << ',' << s[si].yearLevel << ',' << s[si].passcode << "\n";
    if(role == OFFICER && o)
        out << o[oi].ID << ',' << o[oi].name << ',' << o[oi].program << ',' << o[oi].yearLevel << ',' << o[oi].position << ',' << o[oi].passcode << "\n";
    if(role == FACULTY && f)
        out << f[fi].ID << ',' << f[fi].name << ',' << f[fi].passcode << "\n";

    cout << "\n[✔ ] Information saved.\n";
    out.close();
}

void savePendingStudent(Student& s){
    ifstream check("pending_students.csv");
    bool empty = (check.peek() == ifstream::traits_type::eof());
    check.close();

    ofstream out("pending_students.csv", ios::app);

    if(out.is_open()){
        if(empty)
            out << "ID,Name,Program,Year Level,Passcode\n";

        out << s.ID << ',' << s.name << ',' << s.program << ',' << s.yearLevel << ',' << s.passcode << "\n";
    }

    out.close();
}

void loadPendingStudents(Student* pending, int& count){
    ifstream file("pending_students.csv");
    count = 0;

    if(!file.is_open())
        return;

    string line;
    if(getline(file, line)){
        while(getline(file, line) && count < MAX_PENDING){
            stringstream ss(line);
            string yr;

            getline(ss, pending[count].ID, ',');
            getline(ss, pending[count].name, ',');
            getline(ss, pending[count].program, ',');
            getline(ss, yr, ',');
            getline(ss, pending[count].passcode);
            pending[count].yearLevel = yr.empty() ? 0 : atoi(yr.c_str());
            count++;
        }
    }
    file.close();
}

void updatePendingCSV(Student* pending, int count){
    ofstream file("pending_students.csv", ios::trunc);

    if(!file.is_open())
        return;

    file << "ID,Name,Program,Year Level,Passcode\n";

    for(int i = 0; i < count; i++)
        file << pending[i].ID << ',' << pending[i].name << ',' << pending[i].program << ',' << pending[i].yearLevel << ',' << pending[i].passcode << "\n";

    file.close();
}

int getPendingRequestCount(){
    Student temp[MAX_PENDING];
    int count = 0;

    loadPendingStudents(temp, count);

    return count;
}

void loadAnnouncements(Announcement* a, int& count){
    ifstream file("announcements.txt");
    count = 0;

    if(!file.is_open())
        return;

    string line;
    while(getline(file, line) && count < MAX_ANNOUNCE){
        if(line == "---"){
            Announcement x;
            string idStr, pinStr, urgStr;

            getline(file, idStr);
            getline(file, x.title);
            getline(file, x.content);
            getline(file, x.category);
            getline(file, x.date);
            getline(file, x.postedBy);
            getline(file, x.status);
            getline(file, x.rejectionReason);
            getline(file, pinStr);
            getline(file, urgStr);

            if(!idStr.empty()){
                x.id        = atoi(idStr.c_str());
                x.isPinned  = (pinStr == "1");
                x.isUrgent  = (urgStr == "1");
                a[count++]  = x;
            }
        }
    }
    file.close();
}

void saveAllAnnouncements(Announcement* a, int count){
    ofstream file("announcements.txt", ios::trunc);

    if(!file.is_open()){
        cout << "\n[!] Could not open announcements.txt\n";
        return;
    }

    for(int i = 0; i < count; i++){
        file << "---\n"
             << a[i].id << "\n"
             << a[i].title << "\n"
             << a[i].content << "\n"
             << a[i].category << "\n"
             << a[i].date << "\n"
             << a[i].postedBy << "\n"
             << a[i].status << "\n"
             << a[i].rejectionReason << "\n"
             << (a[i].isPinned ? 1 : 0) << "\n"
             << (a[i].isUrgent ? 1 : 0) << "\n";
    }
    file.close();
}

void loadActivities(Activity* a, int& count){
    ifstream file("activities.txt");
    count = 0;

    if(!file.is_open())
        return;

    string line;
    while(getline(file, line) && count < MAX_ACTIVITY){
        if(line == "---"){
            Activity x;
            string idStr;

            getline(file, idStr);
            getline(file, x.name);
            getline(file, x.description);
            getline(file, x.date);
            getline(file, x.time);
            getline(file, x.location);
            getline(file, x.participants);
            getline(file, x.status);
            if(!idStr.empty()){ x.id = atoi(idStr.c_str()); a[count++] = x; }
        }
    }
    file.close();
}

void saveAllActivities(Activity* a, int count){
    ofstream file("activities.txt", ios::trunc);

    if(!file.is_open()){
        cout << "\n[!] Could not open activities.txt\n";
        return;
    }

    for(int i = 0; i < count; i++){
        file << "---\n"<< a[i].id << "\n" << a[i].name << "\n" << a[i].description << "\n" << a[i].date << "\n"
             << a[i].time << "\n"<< a[i].location << "\n" << a[i].participants << "\n" << a[i].status << "\n";
    }
    file.close();
}

void loadFeedbacks(Feedback* fb, int& count){
    ifstream file("feedback.txt");
    count = 0;

    if(!file.is_open())
        return;

    string line;
    while(getline(file, line) && count < MAX_FEEDBACK){
        if(line == "---"){
            Feedback x;
            string idStr;

            getline(file, idStr);
            getline(file, x.studentID);
            getline(file, x.recipient);
            getline(file, x.category);
            getline(file, x.content);
            getline(file, x.date);
            getline(file, x.status);
            if(!idStr.empty()){
                x.id = atoi(idStr.c_str());
                fb[count++] = x;
            }
        }
    }
    file.close();
}

void saveAllFeedbacks(Feedback* fb, int count){
    ofstream file("feedback.txt", ios::trunc);

    if(!file.is_open()){
        cout << "\n[!] Could not open feedback.txt\n";
        return;
    }

    for(int i = 0; i < count; i++){
        file << "---\n"
             << fb[i].id << "\n"
             << fb[i].studentID << "\n"
             << fb[i].recipient << "\n"
             << fb[i].category << "\n"
             << fb[i].content << "\n"
             << fb[i].date << "\n"
             << fb[i].status << "\n";
    }
    file.close();
}

// generic next-ID using template
template<typename T>
T getMaxID(T* arr, int count){
    if(count == 0)
        return (T)0;

    T maxVal = arr[0];

    for(int i = 1; i < count; i++)
        if(arr[i] > maxVal) maxVal = arr[i];

    return maxVal;
}

int getNextID(int* ids, int count){
    if(count == 0)
        return 1;

    int* maxPtr = ids;

    for(int i = 1; i < count; i++)
        if(*(ids + i) > *maxPtr) maxPtr = ids + i;   // pointer arithmetic

    return *maxPtr + 1;
}

// dito continuation

void sortStudents(Student* s, int count, int method){
    // 1=ID 2=Name 3=Program 4=YearLevel
    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count - 1 - i; j++){
            bool doSwap = false;

            if(method == 1)
                doSwap = s[j].ID > s[j+1].ID;
            else if(method == 2)
                doSwap = s[j].name > s[j+1].name;
            else if(method == 3)
                doSwap = s[j].program > s[j+1].program;
            else
                doSwap = s[j].yearLevel  > s[j+1].yearLevel;

            if(doSwap){
                Student tmp = s[j];
                s[j] = s[j+1];
                s[j+1] = tmp;
            }
        }
    }
}

void sortOfficers(Officer* o, int count, int method){
    // 1=ID 2=Name 3=Program 4=YearLevel
    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count - 1 - i; j++){
            bool doSwap = false;
            if(method == 1)      doSwap = o[j].ID        > o[j+1].ID;
            else if(method == 2) doSwap = o[j].name      > o[j+1].name;
            else if(method == 3) doSwap = o[j].program   > o[j+1].program;
            else                 doSwap = o[j].yearLevel  > o[j+1].yearLevel;
            if(doSwap){ Officer tmp = o[j]; o[j] = o[j+1]; o[j+1] = tmp; }
        }
    }
}

void sortActivities(Activity* a, int count, int method){
    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count - 1 - i; j++){
            bool doSwap = false;
            if(method == 1)      doSwap = a[j].date > a[j+1].date;
            else if(method == 2) doSwap = a[j].name > a[j+1].name;
            else                 doSwap = a[j].id   > a[j+1].id;
            if(doSwap){ Activity tmp = a[j]; a[j] = a[j+1]; a[j+1] = tmp; }
        }
    }
}

void sortAnnouncements(Announcement* a, int count){
    // priority: Urgent=0, Pinned=1, Approved=2, Pending=3, Rejected=4
    auto priority = [](const Announcement& x) -> int {
        if(x.isUrgent)               return 0;
        if(x.isPinned)               return 1;
        if(x.status == "Approved")   return 2;
        if(x.status == "Pending")    return 3;
        return 4;
    };
    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count - 1 - i; j++){
            if(priority(a[j]) > priority(a[j+1])){
                Announcement tmp = a[j]; a[j] = a[j+1]; a[j+1] = tmp;
            }
        }
    }
}


//  SEARCHING
// Binary search by ID (array must be sorted by ID)
int searchByID(Student* s, int count, const string& id){
    // sort a copy mentally — here we do linear since IDs are strings
    // Binary search on sorted-by-ID array
    sortStudents(s, count, 1); // sort first
    int lo = 0, hi = count - 1;
    while(lo <= hi){
        int mid = (lo + hi) / 2;
        if(s[mid].ID == id)      return mid;
        else if(s[mid].ID < id) lo = mid + 1;
        else                    hi = mid - 1;
    }
    return -1;
}

// Sequential search by name (partial match)
int searchByName(Student* s, int count, const string& name){
    for(int i = 0; i < count; i++)
        if(s[i].name.find(name) != string::npos) return i;
    return -1;
}

int searchOfficerByName(Officer* o, int count, const string& name){
    for(int i = 0; i < count; i++)
        if(o[i].name == name) return i;
    return -1;
}

int searchFacultyByName(Faculty* f, int count, const string& name){
    for(int i = 0; i < count; i++)
        if(f[i].name == name) return i;
    return -1;
}

// Binary search on activity by ID (requires sorted by ID)
int searchActivityByID(Activity* a, int count, int id){
    sortActivities(a, count, 3); // sort by ID
    int lo = 0, hi = count - 1;
    while(lo <= hi){
        int mid = (lo + hi) / 2;
        if(a[mid].id == id)      return mid;
        else if(a[mid].id < id) lo = mid + 1;
        else                    hi = mid - 1;
    }
    return -1;
}

int searchAnnouncementByID(Announcement* a, int count, int id){
    for(int i = 0; i < count; i++)
        if(a[i].id == id) return i;
    return -1;
}

// Linear search — activity by name or date (partial)
void searchActivityLinear(Activity* a, int count, const string& query,
                          int* results, int& rCount){
    rCount = 0;
    for(int i = 0; i < count; i++){
        if(a[i].name.find(query) != string::npos ||
           a[i].date.find(query) != string::npos){
            results[rCount++] = i;
        }
    }
}

void buildAnnouncementTable(Announcement* a, int count, string table[][5], int& rows){
    rows = 0;
    for(int i = 0; i < count; i++){
        if(a[i].status != "Approved" && !a[i].isPinned && !a[i].isUrgent)
            continue;

        string flag = "";
        if(a[i].isUrgent)
            flag = "🚨 ";

        if(a[i].isPinned)
        flag = "📌 ";

        if(!a[i].isUrgent && !a[i].isPinned)
            flag = "📢 ";

        table[rows][0] = to_string(a[i].id);
        table[rows][1] = flag + a[i].title;
        table[rows][2] = a[i].category;
        table[rows][3] = a[i].date;
        table[rows][4] = a[i].status;
        rows++;
        if(rows >= MAX_ANNOUNCE) break;
    }
}

void buildActivityTable(Activity* a, int count, string table[][6], int& rows){
    rows = 0;
    for(int i = 0; i < count; i++){
        string flag = "";
        if(a[i].status == "Ongoing")   flag = "🔁 ";
        if(a[i].status == "Scheduled") flag = "📆 ";
        table[rows][0] = to_string(a[i].id);
        table[rows][1] = flag + a[i].name;
        table[rows][2] = a[i].date;
        table[rows][3] = a[i].time;
        table[rows][4] = a[i].location;
        table[rows][5] = a[i].status;
        rows++;
        if(rows >= MAX_ACTIVITY) break;
    }
}

Announcement** buildPinnedFirst(Announcement* a, int count, int& outCount){
    Announcement** ptrs = new Announcement*[count];
    outCount = 0;

    // pass 1: urgent
    for(int i = 0; i < count; i++)
        if(a[i].isUrgent) ptrs[outCount++] = &a[i];
    // pass 2: pinned (not urgent)
    for(int i = 0; i < count; i++)
        if(a[i].isPinned && !a[i].isUrgent) ptrs[outCount++] = &a[i];
    // pass 3: rest (approved)
    for(int i = 0; i < count; i++)
        if(!a[i].isUrgent && !a[i].isPinned && a[i].status == "Approved")
            ptrs[outCount++] = &a[i];

    return ptrs;
}

void displayOneAnnouncement(Announcement& a){
    string badge = "";

    if(a.isUrgent)
        badge = " 🚨";
    else if(a.isPinned)
        badge = " 📌";
    else if(a.status=="Pending")
        badge = " ⏳";
    else if(a.status=="Rejected")
        badge = " ❌";

    cout << "\n----------------------------------------------------------\n";
    cout << badge << " ID: " << a.id << " | " << a.status << "\n\n";
    cout << "  Title    : " << a.title    << "\n";
    cout << "  Category : " << a.category << "\n";
    cout << "----------------------------------------------------------\n";
    cout << "  Content  : ";
    stringstream ss(a.content); string word; size_t len = 0;
    while(ss >> word){
        if(len + word.length() > 45){ cout << "\n             "; len = 0; }
        cout << word << " "; len += word.length() + 1;
    }
    cout << "\n----------------------------------------------------------\n";
    cout << "  Date     : " << a.date     << "\n";
    cout << "  Posted by: " << a.postedBy << "\n";
    if(a.status == "Rejected" && !a.rejectionReason.empty())
        cout << "  Reason   : " << a.rejectionReason << "\n";
    cout << "----------------------------------------------------------\n";
}

void displayAllAnn(Announcement* a, int count, const string& filter){
    if(filter == "Approved" || filter == "")
        cout << "\n                 📢 ANNOUNCEMENTS BOARD 📢\n";
    else if(filter == "Pending")
        cout << "\n                 ⏳ PENDING ANNOUNCEMENTS ⏳\n";
    else if(filter == "Rejected")
        cout << "\n                 ❌ REJECTED ANNOUNCEMENTS ❌\n";

    bool anyShown = false;
    int  display  = 1;

    auto show = [&](const string& status){
        for(int i = 0; i < count; i++){
            bool match = false;
            if(filter == "Approved")
                match = (a[i].status == "Approved" || a[i].isPinned || a[i].isUrgent);
            else if(filter == "Pending")
                match = (a[i].status == "Pending");
            else if(filter == "Rejected")
                match = (a[i].status == "Rejected");
            else
                match = true;

            if(match && a[i].status == status){
                displayOneAnnouncement(a[i]);
                display++;
                anyShown = true;
            }
        }
    };

    if(filter == "Approved" || filter == ""){
        // use pointer-to-pointer sorted view
        int outCount = 0;
        Announcement** sorted = buildPinnedFirst(a, count, outCount);
        for(int i = 0; i < outCount; i++){
            displayOneAnnouncement(*sorted[i]);
            display++;
            anyShown = true;
        }
        delete[] sorted;
    }
    if(filter == "Pending"  || filter == "") show("Pending");
    if(filter == "Rejected" || filter == "") show("Rejected");

    if(!anyShown) cout << "\n[!] No announcements to show.\n";
}

void displayOneActivity(Activity& a){
    string flag = "";
    if(a.status == "Ongoing")   flag = " [ONGOING]";
    if(a.status == "Scheduled") flag = " [UPCOMING]";

    cout << "\n----------------------------------------------------------\n";
    cout << "  ID          : " << a.id     << flag   << "\n";
    cout << "  Name        : " << a.name            << "\n";
    cout << "----------------------------------------------------------\n";
    cout << "  Description : ";
    stringstream ss(a.description); string word; size_t len = 0;
    while(ss >> word){
        if(len + word.length() > 40){ cout << "\n                "; len = 0; }
        cout << word << " "; len += word.length() + 1;
    }
    cout << "\n----------------------------------------------------------\n";
    cout << "  Date        : " << a.date         << "\n";
    cout << "  Time        : " << a.time         << "\n";
    cout << "  Location    : " << a.location     << "\n";
    cout << "  Participants: " << a.participants << "\n";
    cout << "  Status      : " << a.status       << "\n";
    cout << "----------------------------------------------------------\n";
}

void displayAllAct(Activity* a, int count){
   // cout << "\n" << string(59,'=') << "\n";
    cout << "\n                    📅 ACTIVITIES LIST 📅\n\n";
   // cout << "\n" << string(59,'=') << "\n";
    cout << left << setw(6) << "ID" << setw(22) << "Name"
         << setw(12) << "Date" << setw(8) << "Time" << "Location\n";
    cout << string(59,'=') << "\n";
    for(int i = 0; i < count; i++){
        string flag = (a[i].status == "Scheduled") ? "📆 " :
                      (a[i].status == "Ongoing")   ? "🔁 " : "";
        cout << left << setw(6)  << a[i].id << setw(22) << (flag + a[i].name).substr(0, 21)
                     << setw(12) << a[i].date << setw(8)  << a[i].time << a[i].location << "\n";
    }

    cout << string(59,'=') << "\n";
}

void displayBulletinBoard(Announcement* ann, int annCount, Activity* act, int actCount, int role){
    cout << "\n\n" <<"                >>> 📋 BULLETIN BOARD 📋 <<< \n";

    //_Announcement
    cout << "\n📢 ANNOUNCEMENTS\n";
    cout << string(59, '-') << "\n";
    cout << left << setw(30) << " Title" << setw(14) << "Category" << "Date\n";
    cout << string(59, '-') << "\n";

     // Use 2D array + buildPinnedFirst (dynamic) for display
    string annTable[MAX_ANNOUNCE][5];
    int annRows = 0;
    buildAnnouncementTable(ann, annCount, annTable, annRows);

    if(annRows == 0){
        cout << "  No announcements to show.\n";
    } else {
        for(int r = 0; r < annRows; r++){
            cout << left << setw(33) << annTable[r][1].substr(0, 31) << setw(14) << annTable[r][2] << annTable[r][3] << "\n";
        }
    }

    // ── Activities ──
    cout << "\n\n📅 UPCOMING ACTIVITIES\n";
    cout << string(59, '-') << "\n";
    cout << left << setw(32) << " Title" << setw(14) << "Date" << "Location\n";
    cout << string(59, '-') << "\n";

    string actTable[MAX_ACTIVITY][6];
    int actRows = 0;
    buildActivityTable(act, actCount, actTable, actRows);

    if(actRows == 0){
        cout << "  No activities to show.\n";
    } else {
        for(int r = 0; r < actRows; r++){
            cout << left << setw(32) << actTable[r][1].substr(0, 29) << setw(14) << actTable[r][2] << actTable[r][4] << "\n";
        }
    }
    cout << "\n" << string(59,'=') << "\n";
}


/**  OFFICER MODULE **/

void officerMenu(){
    cout << "\n[1] 👥 Member Management";
    cout << "\n[2] 📢 Announcement Management";
    cout << "\n[3] 📅 Activity Management";
    cout << "\n[4] 📩 View Feedbacks & Concerns";
    cout << "\n[5] ⚙️ Account Management";
    cout << "\n[6] 🚪 Return to Home\n";
}

void displayCounterUpdates(int studentCount, int pendingCount, int annCount, int actCount){
    cout << "\n|  \033[1m" << studentCount  << "\033[0m \033[3mTotal Members\033[0m                                        |";
    cout << "\n|  \033[1m" << pendingCount  << "\033[0m \033[3mPending Account Requests\033[0m                             |";
    cout << "\n|  \033[1m" << annCount      << "\033[0m \033[3mActive Announcements\033[0m                                 |";
    cout << "\n|  \033[1m" << actCount      << "\033[0m \033[3mUpcoming Activities\033[0m                                  |\n";
    cout << "===========================================================\n";
}

int getApprovedAnnCount(Announcement* a, int count){
    int c = 0;
    for(int i = 0; i < count; i++)
        if(a[i].status == "Approved" || a[i].isPinned || a[i].isUrgent) c++;
    return c;
}

int getUpcomingActCount(Activity* a, int count){
    int c = 0;
    for(int i = 0; i < count; i++)
        if(a[i].status == "Scheduled" || a[i].status == "Ongoing") c++;
    return c;
}

void officerSwitch(int choice, Student* students, int& studentCount, Announcement* ann, int& annCount, Activity* act, int& actCount,
                  Officer* officers, int officerCount, Faculty* faculty, int facultyCount, int accIndex, Feedback* fb, int& fbCount, int role){
    switch(choice){
        case 1:
            displayHeader2();
            memberManagement(students, studentCount);
            break;

        case 2:
            displayHeader2();
            announcementManagement(ann, annCount, officers[accIndex].name);
            break;

        case 3:
            displayHeader2();
            activityManagement(act, actCount);
            break;

        case 4:
            displayHeader2();
            viewFeedbacks(fb,fbCount,role,accIndex,officers,faculty,students,studentCount);
            break;

        case 5:
            accountManagement(OFFICER, accIndex, students, studentCount, officers, officerCount, faculty, facultyCount);
            break;

        case 6:
            break;

        default:
            cout << "\n[!] Invalid choice. Try again.\n";
    }
}

// ── Member Management ──
void memberManagement(Student* students, int& studentCount){
    int choice = 0;
    do {
        cls(); displayHeader2();
        int pendingCount = getPendingRequestCount();

        cout << "\n" << right << setw(42) << "-----------------------";
        cout << "\n" << right << setw(46) << "👥 Member Management 👥\n";
        cout << right << setw(42) << "-----------------------\n";

        if(pendingCount > 0)
            cout << "\n  [📥] " << pendingCount << " student account request(s) waiting!\n";

        cout << "\n[1] Approve Account Requests";
        cout << "\n[2] View Members";
        cout << "\n[3] Remove Member";
        cout << "\n[4] Return to Main Menu\n";

        enterPrompt("\nEnter choice: ", choice);

        switch(choice){
            case 1:
                cls(); displayHeader2();
                approveStudentRequests(students, studentCount);
                break;
            case 2:
                cls(); displayHeader2();
                if(studentCount <= 0){ cout << "\n[!] No student records yet.\n"; pauseScreen(); break; }
                viewMembers(students, studentCount);
                break;
            case 3:
                cls(); displayHeader2();
                if(studentCount <= 0){ cout << "\n[!] No student records yet.\n"; pauseScreen(); break; }
                removeMember(students, studentCount);
                break;
            case 4: break;
            default: cout << "\n[!] Invalid choice.\n";
        }
    } while(choice != 4);
    cls();
}

void approveStudentRequests(Student* students, int& studentCount){
    Student pending[MAX_PENDING];
    int pendingCount = 0;
    loadPendingStudents(pending, pendingCount);

    if(pendingCount == 0){
        cout << "\n[✔ ] No pending account requests.\n";
        pauseScreen(); return;
    }

    cout << "\n" << right << setw(47) << "📥 Account Approval Requests 📥\n";
    cout << "\n  " << pendingCount << " pending request(s).\n";

    for(int p = 0; p < pendingCount; p++){
        cls(); displayHeader2();
        cout << "\n📋 Request " << (p + 1) << " of " << pendingCount << "\n";
        cout << "\n----------------------------------------------------------\n";
        cout << "  ID         : " << pending[p].ID        << "\n";
        cout << "  Name       : " << pending[p].name      << "\n";
        cout << "  Program    : " << pending[p].program   << "\n";
        cout << "  Year Level : " << pending[p].yearLevel << "\n";
        cout << "----------------------------------------------------------\n";
        cout << "\n[1] ✅ Approve\n[2] ❌ Reject\n[3] Skip\n";

        int decision;
        enterPrompt("\nYour decision: ", decision);

        if(decision == 1){
            students[studentCount] = pending[p];
            appendToCSV("students.csv", STUDENT, students, studentCount, nullptr, 0, nullptr, 0);
            studentCount++;
            for(int i = p; i < pendingCount - 1; i++) pending[i] = pending[i+1];
            pendingCount--; p--;
            updatePendingCSV(pending, pendingCount);
            cout << "\n[✔ ] Account approved. Student can now log in.\n";
            Sleep(1200);
        } else if(decision == 2){
            for(int i = p; i < pendingCount - 1; i++) pending[i] = pending[i+1];
            pendingCount--; p--;
            updatePendingCSV(pending, pendingCount);
            cout << "\n[✔ ] Request rejected and removed.\n";
            Sleep(1200);
        } else {
            cout << "\n[i] Skipped.\n"; Sleep(800);
        }
    }

    loadStudents(students, studentCount);
    cout << "\n[✔ ] Done reviewing all requests.\n";
    pauseScreen();
}

void viewMembers(Student* students, int studentCount){
    int choice = 0;
    do {
        cls();
        displayHeader2();
        loadStudents(students, studentCount);

        cout << "\n                      🎓 MEMBERS LIST\n\n";
        cout << string(59, '-') << "\n";
        cout << left << setw(17) << "ID" << setw(25) << "Name" << setw(11) << "Program" << "Year";
        cout << "\n" << string(59, '-') << "\n";

        for(int i = 0; i < studentCount; i++){
            Student* sp = students + i;
            cout << left << setw(17) << sp->ID   << setw(25) << sp->name << setw(12) << sp->program << sp->yearLevel << "\n";
        }

        cout << string(59, '-') << "\n";

        cout << "\n[1] Sort     [2] Return to Menu\n";
        enterPrompt("Choose: ", choice);

        if(choice == 1){
            int method;
            cout << "\nSort by: [1] ID  [2] Name  [3] Program  [4] Year Level \n         [5] Return to Menu\n";
            enterPrompt("\nChoose method: ", method);
            while(method < 1 || method > 4){
                cout << "[!] Choose only from 1 to 5.\n";
                enterPrompt("Choose method: ", method);
            }

            if(method >= 1 || method <= 4){
                sortStudents(students, studentCount, method);
                saveStudentsCSV(students, studentCount);
            }
        }
    } while(choice != 2);
}

void removeMember(Student* students, int& studentCount){
    cout << "\n" << right << setw(42) << "-----------------------";
    cout << "\n" << right << setw(41) << ">>> Remove Member <<<\n";
    cout << right << setw(43) << "-----------------------\n";

    cout << "\n🎓 MEMBERS\n";
    cout << string(59, '-') << "\n";
    cout << left << setw(17) << "ID" << setw(25) << "Name" << setw(11) << "Program" << "Year";
    cout << "\n" << string(59, '-') << "\n";

    for(int i = 0; i < studentCount; i++){
        Student* sp = students + i;
        cout << left << setw(17) << sp->ID   << setw(25) << sp->name << setw(12) << sp->program << sp->yearLevel << "\n";
    }

    cout << string(59, '-') << "\n";

    string target;
    enterPrompt("\n👤 Enter name of member to remove: ", target);

    int idx = searchByName(students, studentCount, target);
    if(idx == -1){
        cout << "\n[!] Member not found.\n";
        pauseScreen();
        return;
    }

    cout << "\n📑 Found:\n";
    cout << left << setw(17) << "ID" << setw(25) << "Name"
         << setw(13) << "Program" << "Year Level\n";
    cout << left << setw(17) << students[idx].ID << setw(25) << students[idx].name
                 << setw(13) << students[idx].program << students[idx].yearLevel << "\n";

    char confirm;
    cout << "\n--------------------------------------------------------------------\n";
    enterPrompt("Confirm removal? (Y/N): ", confirm);

    if(confirm == 'Y' || confirm == 'y'){
        // i = member index, loop starting from member's index then assign the value
        // stored on the next index on member's index to overwrite the data stored on it
        for(int i = idx; i < studentCount - 1; i++){
            students[i] = students[i+1];
        }

        // deduct the students count by 1
        studentCount--;
        saveStudentsCSV(students, studentCount);
        cout << "\n[✔ ] Member removed successfully.\n";
    } else {
        cout << "\n[i] Operation cancelled.\n";
    }
    pauseScreen();
}

// ── Announcement Management (Officer) ──
void announcementManagement(Announcement* ann, int& annCount, const string& officerName){
    loadAnnouncements(ann, annCount);
    int choice = 0;

    do {
        cls(); displayHeader2();
        int pendingCount = 0;
        for(int i = 0; i < annCount; i++)
            if(ann[i].status == "Pending") pendingCount++;

        cout << "\n" << right << setw(49) << "📢 Announcement Management 📢\n";

        if(pendingCount > 0)
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

        switch(choice){
            case 1: cls(); displayHeader2(); proposeAnnouncement(ann, annCount, officerName); break;
            case 2:
                cls(); displayHeader2();
                loadAnnouncements(ann, annCount);
                displayAllAnn(ann, annCount, "Approved");
                pauseScreen();
                break;
            case 3:
                cls(); displayHeader2();
                loadAnnouncements(ann, annCount);
                displayAllAnn(ann, annCount, "Pending");
                pauseScreen();
                break;
            case 4:
                cls(); displayHeader2();
                loadAnnouncements(ann, annCount);
                displayAllAnn(ann, annCount, "Rejected");
                pauseScreen();
                break;
            case 5:
                cls(); displayHeader2();
                if(annCount <= 0){ cout << "\n[!] No announcements yet.\n"; pauseScreen(); break; }
                editAnnouncement(ann, annCount);
                break;
            case 6:
                cls(); displayHeader2();
                if(annCount <= 0){ cout << "\n[!] No announcements yet.\n"; pauseScreen(); break; }
                removeAnnouncement(ann, annCount);
                break;
            case 7:
                cls(); displayHeader2();
                if(annCount <= 0){ cout << "\n[!] No announcements yet.\n"; pauseScreen(); break; }
                pinUrgentAnnouncement(ann, annCount);
                break;
            case 8: break;
            default: cout << "\n[!] Invalid choice.\n"; pauseScreen();
        }
    } while(choice != 8);
    cls();
}

void proposeAnnouncement(Announcement* ann, int& annCount,
                         const string& officerName){
    SetConsoleOutputCP(CP_UTF8);
    cout << "\n" << right << setw(47) << "📢 Propose Announcement 📢\n";

    if(annCount >= MAX_ANNOUNCE){
        cout << "\n[!] Announcement list is full.\n"; pauseScreen(); return;
    }

    // get all IDs for getMaxID template usage
    int* ids = new int[annCount];
    for(int i = 0; i < annCount; i++) ids[i] = ann[i].id;
    int nextID = getMaxID(ids, annCount) + 1;
    delete[] ids;

    Announcement n;
    n.id              = nextID;
    n.postedBy        = officerName;
    n.date            = getCurrentDate();
    n.rejectionReason = "";
    n.isPinned        = false;
    n.isUrgent        = false;

    enterPrompt("\n📋 Title : ", n.title);
    enterPrompt("📝 Content : ", n.content);
    enterPrompt("🏷️ Category: ", n.category);

    cout << "\n📌 Set Status:\n[1] Normal (pending)\n[2] Urgent (posted immediately)\n";
    int statusChoice;
    enterPrompt("\nChoose: ", statusChoice);
    while(statusChoice != 1 && statusChoice != 2){
        cout << "\n[!] Invalid choice.\n";
        enterPrompt("\nChoose: ", statusChoice);
    }

    if(statusChoice == 2){
        n.status   = "Approved";
        n.isUrgent = true;
        cout << "\n[✔ ] Announcement marked Urgent and posted immediately.\n";
    } else {
        n.status = "Pending";
        cout << "\n[✔ ] Announcement submitted! Awaiting faculty approval.\n";
    }

    ann[annCount++] = n;
    saveAllAnnouncements(ann, annCount);
    pauseScreen();
}

void editAnnouncement(Announcement* ann, int annCount){
    // guard — if nothing to edit, return immediately without asking for ID
    bool hasPendingOrRejected = false;
    for(int i = 0; i < annCount; i++){
        if(ann[i].status == "Pending" || ann[i].status == "Rejected"){
            hasPendingOrRejected = true; break;
        }
    }
    if(!hasPendingOrRejected){
        cout << "\n[!] No pending or rejected announcements to edit.\n";
        pauseScreen(); return;
    }

    cout << "\n📌 Note: Only Pending or Rejected announcements can be edited.\n";
    displayAllAnn(ann, annCount, "Pending");
    displayAllAnn(ann, annCount, "Rejected");

    int targetID;
    enterPrompt("\n🆔 Enter Announcement ID to edit: ", targetID);

    int found = searchAnnouncementByID(ann, annCount, targetID);
    if(found == -1 ||
      (ann[found].status != "Pending" && ann[found].status != "Rejected")){
        cout << "\n[!] ID not found or announcement is already approved.\n";
        pauseScreen(); return;
    }
    pauseScreen();
    cls();
    displayHeader2();
    //

    //cout << "\n✏️ EDIT ANNOUNCEMENT\n"
    cout << "\nEdit:\n[1] Title\n[2] Content\n[3] Category\n";
    int editChoice;
    enterPrompt("Choose: ", editChoice);
    switch(editChoice){
        case 1: enterPrompt("\n📋 New Title   : ", ann[found].title);    break;
        case 2: enterPrompt("\n📝 New Content : ", ann[found].content);  break;
        case 3: enterPrompt("\n🏷️  New Category: ", ann[found].category); break;
        default: cout << "\n[!] Invalid choice.\n"; pauseScreen(); return;
    }

    // always re-submit as Pending for faculty review (covers Rejected too)
    ann[found].status          = "Pending";
    ann[found].rejectionReason = "";
    saveAllAnnouncements(ann, annCount);
    cout << "\n[✔ ] Announcement updated and re-submitted for faculty approval.\n";
    pauseScreen();
}

void removeAnnouncement(Announcement* ann, int& annCount){
    displayAllAnn(ann, annCount, "");

    int targetID;
    enterPrompt("\n🆔 Enter Announcement ID to remove: ", targetID);

    int found = searchAnnouncementByID(ann, annCount, targetID);
    if(found == -1){ cout << "\n[!] Announcement ID not found.\n"; pauseScreen(); return; }

    pauseScreen();
    system("cls");
    displayHeader2();
    cout << "\n                 📢 ANNOUNCEMENTS BOARD 📢\n";
    displayOneAnnouncement(ann[found]);
    char confirm;
    cout << "\n--------------------------------------------------------------------\n";
    enterPrompt("Confirm removal? (Y/N): ", confirm);

    if(confirm == 'Y' || confirm == 'y'){
        for(int i = found; i < annCount - 1; i++) ann[i] = ann[i+1];
        annCount--;
        saveAllAnnouncements(ann, annCount);
        cout << "\n[✔ ] Announcement removed successfully.\n";
    } else {
        cout << "\n[i] Operation cancelled.\n";
    }
    pauseScreen();
}

void pinUrgentAnnouncement(Announcement* ann, int annCount){
    cout << "\n📌 Note: Only approved announcements can be pinned or marked urgent.\n";
    displayAllAnn(ann, annCount, "Approved");

    int targetID;
    enterPrompt("\n🆔 Enter Announcement ID: ", targetID);

    int found = searchAnnouncementByID(ann, annCount, targetID);
    if(found == -1 ||
      (ann[found].status != "Approved" && !ann[found].isPinned && !ann[found].isUrgent)){
        cout << "\n[!] ID not found or not yet approved.\n"; pauseScreen(); return;
    }

    cout << "\nSet status:\n[1] 📌 Pinned\n[2] 🚨 Urgent\n[3] Approved (remove flag)\n";
    int statusChoice;
    enterPrompt("Choose: ", statusChoice);
    switch(statusChoice){
        case 1:
            ann[found].isPinned  = true;
            ann[found].isUrgent  = false;
            ann[found].status    = "Approved";
            break;
        case 2:
            ann[found].isUrgent  = true;
            ann[found].isPinned  = false;
            ann[found].status    = "Approved";
            break;
        case 3:
            ann[found].isPinned  = false;
            ann[found].isUrgent  = false;
            ann[found].status    = "Approved";
            break;
        default: cout << "\n[!] Invalid choice.\n"; pauseScreen(); return;
    }

    saveAllAnnouncements(ann, annCount);
    cout << "\n[✔ ] Status updated successfully.\n";
    pauseScreen();
}

// ── Activity Management ──
void activityManagement(Activity* act, int& actCount){
    loadActivities(act, actCount);
    int choice = 0;

    do {
        cls(); displayHeader2();
        cout << "\n" << right << setw(47) << "📅 Activity Management 📅\n";
        cout << "\n[1] Add Activity\n[2] View Activities\n[3] Update Activity\n[4] Delete Activity\n[5] Return to Main Menu\n";
        enterPrompt("\nEnter choice: ", choice);

        switch(choice){
            case 1: cls(); displayHeader2(); addActivity(act, actCount);  break;
            case 2:
                cls(); displayHeader2();
                if(actCount <= 0){ cout << "\n[!] No activities yet.\n"; pauseScreen(); break; }
                viewActivities(act, actCount);
                break;
            case 3:
                cls(); displayHeader2();
                if(actCount <= 0){ cout << "\n[!] No activities yet.\n"; pauseScreen(); break; }
                updateActivity(act, actCount);
                break;
            case 4:
                cls(); displayHeader2();
                if(actCount <= 0){ cout << "\n[!] No activities yet.\n"; pauseScreen(); break; }
                deleteActivity(act, actCount);
                break;
            case 5: break;
            default: cout << "\n[!] Invalid choice. Try again.\n";
        }
    } while(choice != 5);
    cls();
}

void addActivity(Activity* act, int& actCount){
    cout << "\n" << right << setw(44) << "📅 Add Activity 📅\n";

    if(actCount >= MAX_ACTIVITY){ cout << "\n[!] Activity list is full.\n"; pauseScreen(); return; }

    int* ids = new int[actCount];
    for(int i = 0; i < actCount; i++) ids[i] = act[i].id;
    int nextID = getMaxID(ids, actCount) + 1;
    delete[] ids;

    Activity n;
    n.id     = nextID;
    n.status = "Scheduled";

    enterPrompt("\n📌 Activity Name : ", n.name);
    enterPrompt("📝 Description   : ", n.description);
    do {
        enterPrompt("📅 Date (DD/MM/YYYY): ", n.date);
        if(!isValidDate(n.date)) cout << "\n[!] Enter a valid date (DD/MM/YYYY).\n";
    } while(!isValidDate(n.date));
    do {
        enterPrompt("🕐 Time (HH:MM)     : ", n.time);
        if(!isValidTime(n.time)) cout << "\n[!] Enter a valid time (HH:MM).\n";
    } while(!isValidTime(n.time));
    enterPrompt("📍 Location         : ", n.location);
    enterPrompt("👥 Participants      : ", n.participants);

    act[actCount++] = n;
    saveAllActivities(act, actCount);
    cout << "\n[✔ ] Activity added successfully.\n";
    pauseScreen();
}

void viewActivities(Activity* act, int& actCount){
    int choice = 0;
    do {
        cls(); displayHeader();
        loadActivities(act, actCount);
        displayAllAct(act, actCount);

        cout << "\nSort by: [1] Date  [2] Name  [3] ID  [4] Return\n";
        enterPrompt("Choose: ", choice);
        if(choice >= 1 && choice <= 3){
            sortActivities(act, actCount, choice);
            saveAllActivities(act, actCount);
        }
    } while(choice != 4);
    pauseScreen();
}

void updateActivity(Activity* act, int actCount){
    loadActivities(act, actCount);
    displayAllAct(act, actCount);

    int targetID;
    enterPrompt("\n🆔 Enter Activity ID to update: ", targetID);

    int found = searchActivityByID(act, actCount, targetID);
    if(found == -1){ cout << "\n[!] Activity not found.\n"; pauseScreen(); return; }
    pauseScreen();
    system("cls");
    displayHeader2();
    cout << "\n                    📅 ACTIVITIES LIST 📅\n";
    cout << "\n📝FULL DETAILS\n";
    displayOneActivity(act[found]);
    cout << "\n[1] Name  [2] Description  [3] Date  [4] Time  [5] Location  [6] Participants  [7] Status\n";
    int editChoice;
    enterPrompt("\nChoose field to update: ", editChoice);

    switch(editChoice){
        case 1: enterPrompt("\n📌 New Name        : ", act[found].name);         break;
        case 2: enterPrompt("\n📝 New Description : ", act[found].description);  break;
        case 3:
            do {
                enterPrompt("\n📅 New Date (DD/MM/YYYY): ", act[found].date);
                if(!isValidDate(act[found].date)) cout << "\n[!] Enter a valid date.\n";
            } while(!isValidDate(act[found].date));
            break;
        case 4:
            do {
                enterPrompt("\n🕐 New Time (HH:MM): ", act[found].time);
                if(!isValidTime(act[found].time)) cout << "\n[!] Enter a valid time.\n";
            } while(!isValidTime(act[found].time));
            break;
        case 5: enterPrompt("\n📍 New Location    : ", act[found].location);    break;
        case 6: enterPrompt("\n👥 New Participants: ", act[found].participants); break;
        case 7:
            cout << "\n[1] Scheduled  [2] Ongoing  [3] Completed  [4] Cancelled\n";
            int sc;
            enterPrompt("Choose: ", sc);
            if(sc == 1) act[found].status = "Scheduled";
            else if(sc == 2) act[found].status = "Ongoing";
            else if(sc == 3) act[found].status = "Completed";
            else if(sc == 4) act[found].status = "Cancelled";
            else { cout << "\n[!] Invalid choice.\n"; pauseScreen(); return; }
            break;
        default: cout << "\n[!] Invalid choice.\n"; pauseScreen(); return;
    }

    if(editChoice != 7) act[found].status = "Modified";
    saveAllActivities(act, actCount);
    cout << "\n[✔ ] Activity updated successfully.\n";
    pauseScreen();
}

void deleteActivity(Activity* act, int& actCount){
    loadActivities(act, actCount);
    displayAllAct(act, actCount);

    int targetID;
    enterPrompt("\n🆔 Enter Activity ID to delete: ", targetID);

    int found = searchActivityByID(act, actCount, targetID);
    if(found == -1){ cout << "\n[!] Activity not found.\n"; pauseScreen(); return; }

    pauseScreen();
    system("cls");
    displayHeader2();
    cout << "\n                    📅 ACTIVITIES LIST 📅\n";
    cout << "\n📝FULL DETAILS\n";
    displayOneActivity(act[found]);
    char confirm;
    cout << "\n----------------------------------------------------------\n";
    enterPrompt("Confirm deletion? (Y/N): ", confirm);

    if(confirm == 'Y' || confirm == 'y'){
        for(int i = found; i < actCount - 1; i++) act[i] = act[i+1];
        actCount--;
        saveAllActivities(act, actCount);
        cout << "\n[✔ ] Activity deleted successfully.\n";
    } else {
        cout << "\n[i] Operation cancelled.\n";
    }
    pauseScreen();
}

// ── Officer View Feedbacks & Concerns ──
void viewFeedbacks(Feedback* fb, int& fbCount, int role, int accIndex, Officer* officers, Faculty* faculty, Student* students, int studentCount){
    cls();

    (role == OFFICER) ? displayHeader2() : displayHeader3();
    loadFeedbacks(fb, fbCount);

    string myName = (role == OFFICER) ? officers[accIndex].name
                                      : faculty[accIndex].name;

    // collect feedbacks where this user is recipient or General
    int matches[MAX_FEEDBACK];
    int mCount = 0;
    for(int i = 0; i < fbCount; i++){
        if(fb[i].recipient == myName || fb[i].recipient == "General")
            matches[mCount++] = i;
    }

    if(mCount == 0){
        cout << "\n[!] No feedbacks or concerns for you.\n";
        pauseScreen(); return;
    }

    cout << "\n" << right << setw(49) << "📩 Feedbacks & Concerns 📩\n\n";
    cout << left << setw(6) << "ID" << setw(20) << "Sender"
         << setw(13) << "Category" << setw(12) << "Date" << "Status\n";
    cout << string(59, '-') << "\n";

    for(int i = 0; i < mCount; i++){
        Feedback* f = &fb[matches[i]];  // pointer

        string senderName = "Anonymous";
        if(f->studentID != "Anonymous"){
            for(int j = 0; j < studentCount; j++){
                if(students[j].ID == f->studentID){ senderName = students[j].name; break; }
            }
        }

        string flag = (f->status == "Unread") ? " [NEW]" : "";
        cout << left << setw(6)  << f->id
                     << setw(20) << senderName
                     << setw(13) << f->category
                     << setw(12) << f->date
                     << f->status << flag << "\n";
    }

    char viewDetail;
    cout << "\nView full details of a feedback? (Y/N): ";
    cin >> viewDetail; cin.ignore();

    if(viewDetail == 'Y' || viewDetail == 'y'){
        int fid;
        enterPrompt("\n🆔 Enter Feedback ID: ", fid);
        bool found = false;
        for(int i = 0; i < mCount; i++){
            Feedback* f = &fb[matches[i]];
            if(f->id == fid){
                found = true;

                string senderName = "Anonymous";
                if(f->studentID != "Anonymous"){
                    for(int j = 0; j < studentCount; j++){
                        if(students[j].ID == f->studentID){ senderName = students[j].name; break; }
                    }
                }
                pauseScreen();
                cls();
                displayHeader2();
                cout << "\n" << right << setw(49) << "📩 Feedbacks & Concerns 📩\n\n";
                cout << "📩 FULL DETAILS\n";
                cout << "\n----------------------------------------------------------\n";
                cout << "  ID        : " << f->id         << "\n";
                cout << "  Sender    : " << senderName    << "\n";
                cout << "  Recipient : " << f->recipient  << "\n";
                cout << "  Category  : " << f->category   << "\n";
                cout << "  Date      : " << f->date       << "\n";
                cout << "  Status    : " << f->status     << "\n";
                cout << "----------------------------------------------------------\n";
                cout << "  Content   : " << f->content    << "\n";
                cout << "----------------------------------------------------------\n";
                if(f->status == "Unread"){
                    f->status = "Read";
                    saveAllFeedbacks(fb, fbCount);
                }
                break;
            }
        }
        if(!found) cout << "\n[!] Feedback not found.\n";
    }
    pauseScreen();
    cls();
}

/** FACULTY MODULE **/
void facultyMenu(){
    cout << "\n[1] 📢 Announcement Management";
    cout << "\n[2] 👥 View Officers and Members";
    cout << "\n[3] 📩 View Feedbacks & Concerns";
    cout << "\n[4] ⚙️ Account Management";
    cout << "\n[5] 🚪 Return to Home\n";;
}

void facultySwitch(int choice, Announcement* ann, int& annCount, Student* students, int studentCount,
          Officer* officers, int officerCount, Feedback* fb, int& fbCount, Faculty* faculty, int facultyCount, int accIndex, int role){

    switch(choice){
        case 1: displayHeader2();
                facultyAnnouncementMgmt(ann, annCount, faculty[accIndex].name);
                break;

        case 2: displayHeader2();
                viewOfficersAndMembers(students, studentCount, officers, officerCount);
                break;

        case 3: displayHeader2();
                viewFeedbacks(fb,fbCount,role,accIndex,officers,faculty,students,studentCount);
            break;

        case 4:
            accountManagement(FACULTY, accIndex, students, studentCount, officers, officerCount,faculty,  facultyCount);
            break;

        case 5:
            break;

        default:
            cout << "\n[!] Invalid choice. Try again.\n";
    }
}

void facultyAnnouncementMgmt(Announcement* ann, int& annCount, const string& facultyName){
    loadAnnouncements(ann, annCount);
    int choice = 0;

    do {
        cls();
        displayHeader2();

        int pendingCount = 0;
        for(int i = 0; i < annCount; i++){
            if(ann[i].status == "Pending") pendingCount++;
        }

        cout << "\n" << right << setw(49) << "📢 Announcement Management 📢\n";

        if(pendingCount > 0)
            cout << "\n  [⏳] " << pendingCount << " announcement(s) pending your approval!\n";

        cout << "\n[1] Review Pending Announcements";
        cout << "\n[2] View All Approved Announcements";
        cout << "\n[3] Post Announcement";
        cout << "\n[4] Return to Main Menu\n";
        enterPrompt("\nEnter choice: ", choice);

        switch(choice){
            case 1:
                cls();
                displayHeader2();
                reviewPendingAnn(ann, annCount);
                break;

            case 2:
                cls();
                displayHeader2();
                loadAnnouncements(ann, annCount);
                viewAnnouncements(ann,annCount);
                break;
            case 3:
                cls();
                displayHeader2();

                {
                // faculty posts directly — Approved, no pending step
                if(annCount >= MAX_ANNOUNCE){
                    cout << "\n[!] Announcement list is full.\n"; pauseScreen(); break;
                }
                int* ids = new int[annCount];
                for(int i = 0; i < annCount; i++) ids[i] = ann[i].id;
                int nextID = getMaxID(ids, annCount) + 1;
                delete[] ids;

                Announcement n;
                n.id = nextID;
                n.postedBy = facultyName;
                n.date = getCurrentDate();
                n.status = "Approved";
                n.rejectionReason = "";
                n.isPinned = false;
                n.isUrgent = false;

                cout << "\n" << right << setw(47) << "📢 Post Announcement 📢\n";
                enterPrompt("\n📋 Title: ", n.title);
                enterPrompt("📝 Content: ", n.content);
                enterPrompt("🏷️ Category: ", n.category);

                ann[annCount++] = n;
                saveAllAnnouncements(ann, annCount);
                cout << "\n[✔ ] Announcement posted successfully.\n";
                pauseScreen();
                break;
            }

            case 4:
                 break;

            default:
                cout << "\n[!] Invalid choice.\n"; pauseScreen();
        }
    } while(choice != 4);
    cls();
}

void reviewPendingAnn(Announcement* ann, int& annCount){
    loadAnnouncements(ann, annCount);

    int pendingIdx[MAX_ANNOUNCE];
    int pendingCount = 0;
    for(int i = 0; i < annCount; i++)
        if(ann[i].status == "Pending") pendingIdx[pendingCount++] = i;

    if(pendingCount == 0){
        cout << "\n[✔ ] No pending announcements. All caught up!\n";
        pauseScreen(); return;
    }

    cout << "\n  " << pendingCount << " pending announcement(s) to review.\n";

    for(int p = 0; p < pendingCount; p++){
        int i = pendingIdx[p];
        cls(); displayHeader2();
        cout << "\n⏳ Reviewing " << (p + 1) << " of " << pendingCount << "\n";
        displayOneAnnouncement(ann[i]);

        cout << "\n[1] ✅ Approve\n[2] ❌ Reject\n[3] Skip (decide later)\n";
        int decision;
        enterPrompt("\nYour decision: ", decision);

        if(decision == 1){
            ann[i].status = "Approved";
            ann[i].rejectionReason = "";
            saveAllAnnouncements(ann, annCount);
            cout << "\n[✔ ] Announcement approved and posted to the board.\n";
            Sleep(1200);
        } else if(decision == 2){
            string reason = "";
            enterPrompt("\n📝 Enter rejection reason: ", reason);
            ann[i].status          = "Rejected";
            ann[i].rejectionReason = reason;
            saveAllAnnouncements(ann, annCount);
            cout << "\n[✔ ] Announcement rejected.\n";
            Sleep(1200);
        } else {
            cout << "\n[i] Skipped.\n"; Sleep(800);
        }
    }
    cout << "\n[✔ ] Done reviewing all pending announcements.\n";
    pauseScreen();
}


// ── Faculty View Officers and Members — submenu, display first, then sort ──
void viewOfficersAndMembers(Student* students, int studentCount, Officer* officers, int officerCount){
    int choice = 0;
    do {
        cls(); displayHeader2();
        cout << "\n" << right << setw(49) << "👥 Officers and Members 👥\n";
        cout << "\n[1] View Officers\n[2] View Members\n[3] Return to Main Menu\n";
        enterPrompt("\nEnter choice: ", choice);

        if(choice == 1){
            viewOfficers(officers,officerCount);
        } else if(choice == 2){
            viewMembers(students,studentCount);
        } else if(choice != 3){
            cout << "\n[!] Invalid choice.\n";
        }
    } while(choice != 3);
}

void studentDashboard(int homeChoice, Student* students, int studentCount, int accIndex, Announcement* ann, int& annCount, Activity* act,
                      int& actCount, Officer* officers, int officerCount, Faculty* faculty, int facultyCount, Feedback* fb, int& fbCount){
    cls();
    int choice = 0;

    if(homeChoice == 1){
        do{
            displayHeader4();
            studentMenu();
            enterPrompt("\nEnter choice: ", choice);
            cls();

            // reload on each iteration
            loadAnnouncements(ann, annCount);
            loadActivities(act, actCount);
            loadFeedbacks(fb, fbCount);

            switch(choice){
                case 1:
                    viewAnnouncements(ann, annCount);
                    break;

                case 2:
                    viewActivities(act,actCount);
                    break;

                case 3:
                    studentViewFaculty(faculty, facultyCount);
                    break;

                case 4:
                    viewOfficers(officers, officerCount);
                    break;

                case 5:
                    feedbacksAndConcerns(fb, fbCount, accIndex, students, studentCount, officers, officerCount, faculty, facultyCount);
                    break;

                case 6:
                    accountManagement(STUDENT, accIndex,students, studentCount,officers, officerCount, faculty, facultyCount);
                    break;

                case 7:
                    break;

                default: cout << "\n[!] Invalid choice. Please try again.\n";
            }
        } while(choice != 7);
        } else if(homeChoice == 2){
            cout << "\nLogging out. Please wait...\n";
            Sleep(400);
            cls();
        } else {
            cout << "\n[!] Invalid choice.\n";
        }
}

void studentMenu(){
    cout << "\n[1] 📢 View Announcements";
    cout << "\n[2] 📅 View Activities";
    cout << "\n[3] 🧑‍🏫 View Faculty";
    cout << "\n[4] 🎓 View Officers";
    cout << "\n[5] 📩 Feedbacks & Concerns";
    cout << "\n[6] ⚙️ Account Management";
    cout << "\n[7] 🚪 Return to Home\n";
}

void viewAnnouncements(Announcement* ann, int& annCount){
    cls();
    displayHeader();
    loadAnnouncements(ann, annCount);

    // only approved
    bool any = false;
    for(int i = 0; i < annCount; i++)
        if(ann[i].status == "Approved" || ann[i].isPinned || ann[i].isUrgent)
            { any = true; break; }

    if(!any){
        cout << "\n[!] No announcements available.\n";
        pauseScreen();
        return;
    }

    int outCount = 0;
    Announcement** sorted = buildPinnedFirst(ann, annCount, outCount);

    cout <<"\n" << right << setw(44) << "📢 ANNOUNCEMENTS 📢" << "\n\n";
   // cout << string(59, '-') << "\n";
    cout << left << setw(5) << "ID" << setw(31) << "Title" << setw(14) << "Category" << "Date\n";
    cout << string(59, '-') << "\n";
    for(int i = 0; i < outCount; i++){
        string flag = sorted[i]->isUrgent ? "🚨 " :
                      sorted[i]->isPinned ? "📌 " : "   ";
        cout << left << setw(5)  << sorted[i]->id << setw(33) << (flag + sorted[i]->title).substr(0, 31) << setw(11) << sorted[i]->category
                     << sorted[i]->date << "\n";

    }
    cout << string(59, '-') << "\n";
    delete[] sorted;

    char viewDetail;
    cout << "\nView full details? (Y/N): ";
    cin >> viewDetail; cin.ignore();
    if(viewDetail == 'Y' || viewDetail == 'y'){
        int aid;
        enterPrompt("\n🆔 Enter Announcement ID: ", aid);
        int idx = searchAnnouncementByID(ann, annCount, aid);
        if(idx == -1 || (ann[idx].status != "Approved" && !ann[idx].isPinned && !ann[idx].isUrgent)){
            cout << "\n[!] Announcement not found or not available.\n";
        } else {
            pauseScreen();
            system("cls");
            displayHeader();
            cout <<"\n" << right << setw(44) << "📢 ANNOUNCEMENTS 📢" << "\n";
            cout << "\n📝FULL DETAILS\n";
            displayOneAnnouncement(ann[idx]);
        }
    }
    pauseScreen();
    cls();
}

// ── View Faculty — sort by ID or Name instead of specific view ──
void studentViewFaculty(Faculty* faculty, int& facultyCount){
    cls();
    displayHeader();
    if(facultyCount == 0){
        cout << "\n[!] No faculty records available.\n";
        pauseScreen();
        return;
    }

    cout << "\n                      🧑‍🏫 FACULTY LIST\n\n";
    cout << string(59, '-') << "\n";
    cout << left << setw(22) << "ID" << "Name\n";
    cout << string(59, '-') << "\n";
    for(int i = 0; i < facultyCount; i++){
        Faculty* fp = faculty + i;
        cout << left << setw(22) << fp->ID << fp->name << "\n";
    }

    int choice = 0;

    cout << "\n[1] Sort [2] Return to Menu\n";
    enterPrompt("Choose: ",choice);

    if(choice == 1){
        cout << "\nSort by: [1] ID  [2] Name\n";

        int method;
        enterPrompt("Choose: ", method);
        while(method != 1 && method != 2){
            cout << "[!] Choose only 1 or 2.\n";
            enterPrompt("Choose: ", method);
        }

        // Bubble sort on Faculty array
        for(int i = 0; i < facultyCount - 1; i++){
            for(int j = 0; j < facultyCount - 1 - i; j++){
                bool doSwap = (method == 1) ? faculty[j].ID   > faculty[j+1].ID : faculty[j].name > faculty[j+1].name;
                if(doSwap){
                    Faculty tmp = faculty[j];
                    faculty[j] = faculty[j+1];
                    faculty[j+1] = tmp;
                }
            }
        }

        cls();
        displayHeader();
        cout << "\n                      🧑‍🏫 FACULTY LIST\n\n";
        cout << string(59, '-') << "\n";
        cout << left << setw(22) << "ID" << "Name\n";
        cout << string(59, '-') << "\n";
        for(int i = 0; i < facultyCount; i++){
            Faculty* fp = faculty + i;
            cout << left << setw(22) << fp->ID << fp->name << "\n";
        }
    }
    pauseScreen();
}

void viewOfficers(Officer* officers, int officerCount){
    cls(); displayHeader();
    if(officerCount == 0){ cout << "\n[!] No officer records available.\n"; pauseScreen(); return; }

    sortOfficers(officers, officerCount, 2); // sort by name

    cout << "\n                     🎓OFFICERS LIST\n\n";
    cout << string(59, '-') << "\n";
    cout << left << setw(17) << "ID" << setw(25) << "Name" << "Position";
    cout << "\n" << string(59, '-') << "\n";

    for(int i = 0; i < officerCount; i++){
        cout << left << setw(17) << officers[i].ID  << setw(25) << officers[i].name << officers[i].position << "\n";
    }

    cout << string(59, '-') << "\n";

    char viewDetail;
    cout << "\nView a specific officer? (Y/N): ";
    cin >> viewDetail;
    cin.ignore();

    if(viewDetail == 'Y' || viewDetail == 'y'){
        string oname;
        enterPrompt("\n🆔 Enter Officer Name: ", oname);
        int idx = searchOfficerByName(officers, officerCount, oname);
        if(idx == -1) cout << "\n[!] Officer not found.\n";
        else {
            cout << "\n📋RESULT";
            cout << "\n----------------------------------------------------------\n";
            cout << "  ID        : " << officers[idx].ID        << "\n";
            cout << "  Name      : " << officers[idx].name      << "\n";
            cout << "  Program   : " << officers[idx].program   << "\n";
            cout << "  Year Level: " << officers[idx].yearLevel << "\n";
            cout << "  Position  : " << officers[idx].position  << "\n";
            cout << "----------------------------------------------------------\n";
        }
    }
    pauseScreen();
}

// ── Feedbacks & Concerns ──
void feedbacksAndConcerns(Feedback* fb, int& fbCount, int accIndex, Student* students, int studentCount, Officer* officers, int officerCount,
                          Faculty* faculty, int facultyCount){
    int choice = 0;
    do {
        cls();
        displayHeader();

        cout << "\n" << right << setw(50) << "📩 Feedbacks & Concerns 📩\n";
        cout << "\n[1] Submit Feedback\n[2] View My Feedbacks\n[3] Return to Main Menu\n";
        enterPrompt("\nEnter choice: ", choice);

        switch(choice){
            case 1:
                cls();
                displayHeader();
                submitFeedback(fb, fbCount, accIndex, students, studentCount, officers, officerCount,
                               faculty, facultyCount);
                break;

            case 2:
                cls();
                displayHeader();
                viewMyFeedbacks(fb, fbCount, accIndex, students, studentCount);
                break;

            case 3:
                break;

            default: cout << "\n[!] Invalid choice.\n";
        }
    } while(choice != 3);
}

void submitFeedback(Feedback* fb, int& fbCount, int accIndex, Student* students, int studentCount, Officer* officers, int officerCount,
                    Faculty* faculty, int facultyCount){
    cout << "\n" << right << setw(47) << "📝 Submit Feedback 📝\n\n";

    if(fbCount >= MAX_FEEDBACK){ cout << "\n[!] Feedback list is full.\n"; pauseScreen(); return; }

    // dynamic memory for new feedback
    Feedback* n = new Feedback();

    // template getMaxID usage
    int* ids = new int[fbCount];
    for(int i = 0; i < fbCount; i++) ids[i] = fb[i].id;
    n->id = getMaxID(ids, fbCount) + 1;
    delete[] ids;

    n->date   = getCurrentDate();
    n->status = "Unread";

    // anonymous?
    char anon;
    cout << "Submit anonymously? (Y/N): ";
    cin >> anon; cin.ignore();
    n->studentID = (anon == 'Y' || anon == 'y') ? "Anonymous" : students[accIndex].ID;

    // recipient — with back option
    bool recipientSet = false;
    while(!recipientSet){
        cout << "\nRecipient:\n [1] Faculty\n [2] Officer\n [3] General\n [4] Back to Menu\n";
        int recChoice;
        enterPrompt("\nChoose: ", recChoice);

        if(recChoice == 1){
            cout << "\n";
            for(int i = 0; i < facultyCount; i++)
                cout << "  " << faculty[i].name << "\n";

            string fname;
            enterPrompt("\n🆔 Faculty Name: ", fname);
            int idx = searchFacultyByName(faculty, facultyCount, fname);
            if(idx == -1){
                cout << "\n[!] Faculty not found. Try again.\n";
            } else {
                n->recipient = fname;
                recipientSet = true;
            }

        } else if(recChoice == 2){
            cout << "\n";
            for(int i = 0; i < officerCount; i++)
                cout << "  " << officers[i].name << "\n";

            string oname;
            enterPrompt("🆔 Officer Name: ", oname);
            int idx = searchOfficerByName(officers, officerCount, oname);
            if(idx == -1){
                cout << "\n[!] Officer not found. Try again.\n";
            } else {
                n->recipient = oname;
                recipientSet = true;
            }

        } else if(recChoice == 3){
            n->recipient = "General";
            recipientSet = true;

        } else if(recChoice == 4){
            delete n;
            cout << "\n[i] Cancelled. Returning to menu.\n";
            pauseScreen(); return;

        } else {
            cout << "\n[!] Invalid choice.\n";
        }
    }
    pauseScreen();
    cls();
    displayHeader2();
    cout << "\n" << right << setw(47) << "📝 Submit Feedback 📝\n\n";

    // category
    cout << "\nCategory:\n[1] Concern\n[2] Suggestion\n[3] Complaint\n";
    int catChoice;
    enterPrompt("Choose: ", catChoice);
    while(catChoice < 1 || catChoice > 3){
        cout << "\n[!] Invalid category.\n";
        enterPrompt("\nChoose: ", catChoice);
    }
    n->category = (catChoice == 1) ? "Concern" :
                  (catChoice == 2) ? "Suggestion" : "Complaint";

    pauseScreen();
    cls();
    displayHeader2();
    cout << "\n" << right << setw(47) << "📝 Submit Feedback 📝\n\n";
    enterPrompt("\n📝 Feedback Content: ", n->content);

    fb[fbCount++] = *n;
    delete n;

    saveAllFeedbacks(fb, fbCount);
    cout << "\n[✔ ] Feedback submitted successfully.\n";
    pauseScreen();
}

void viewMyFeedbacks(Feedback* fb, int fbCount, int accIndex, Student* students, int studentCount){
    string myID = students[accIndex].ID;

    // collect matching indices
    int matches[MAX_FEEDBACK];
    int mCount = 0;
    for(int i = 0; i < fbCount; i++){
        if(fb[i].studentID == myID || fb[i].studentID == "Anonymous")
            matches[mCount++] = i;
    }

    if(mCount == 0){
        cout << "\n[!] You have not submitted any feedback.\n";
        pauseScreen(); return;
    }

    cout << "\n📩 MY FEEDBACKS\n";
    cout << string(59, '-') << "\n";
    cout << left << setw(6) << "ID" << setw(12) << "Category"
         << setw(20) << "Recipient" << setw(14) << "Date" << "Status\n";
    cout << string(59, '-') << "\n";
    for(int i = 0; i < mCount; i++){
        Feedback* f = &fb[matches[i]]; // pointer
        string flag = (f->status == "Unread")   ? " [UNREAD]"  :
                      (f->status == "Resolved")  ? " [RESOLVED]": "";
        cout << left << setw(6)  << f->id
                     << setw(12) << f->category
                     << setw(20) << f->recipient
                     << setw(14) << f->date
                     << f->status << "\n";
    }

    char viewDetail;
    cout << "\nView full details? (Y/N): ";
    cin >> viewDetail; cin.ignore();
    if(viewDetail == 'Y' || viewDetail == 'y'){
        int fid;
        enterPrompt("\n🆔 Enter Feedback ID: ", fid);
        bool found = false;
        for(int i = 0; i < mCount; i++){
            Feedback* f = &fb[matches[i]];
            if(f->id == fid){
                found = true;
                cout << "\n----------------------------------------------------------\n";
                cout << "  Category  : " << f->category  << "\n";
                cout << "  Recipient : " << f->recipient << "\n";
                cout << "  Content   : " << f->content   << "\n";
                cout << "  Date      : " << f->date      << "\n";
                cout << "  Status    : " << f->status    << "\n";
                cout << "----------------------------------------------------------\n";
                break;
            }
        }
        if(!found) cout << "\n[!] Feedback not found.\n";
    }
    pauseScreen();
}

//_account_management
void accountManagement(int role, int accIndex, Student* students, int& studentCount, Officer* officers, int& officerCount, Faculty* faculty,  int& facultyCount){
    int choice = 0;
    do {
        cls(); displayHeader();
        cout << "\n" << right << setw(52) << "⚙️ Account Management ⚙️\n";
        cout << "\n[1] View My Information";
        cout << "\n[2] Edit Information";
        cout << "\n[3] Change Passcode";
        cout << "\n[4] Return to Main Menu\n";
        enterPrompt("\nEnter choice: ", choice);

        switch(choice){
            case 1:
                cls();
                displayHeader();
                viewMyInfo(role,accIndex,students,officers,faculty);
                break;

            case 2:
                cls();
                displayHeader();
                editMyInfo(role,accIndex,students,studentCount,officers,officerCount,faculty,facultyCount);
                break;

            case 3:
                cls();
                displayHeader();
                changePasscode(role, accIndex, students, studentCount, officers, officerCount,faculty,  facultyCount);
                break;

            case 4:
                break;

            default:
                cout << "\n[!] Invalid choice.\n";
        }
    } while(choice != 4);
}

void viewMyInfo(int role, int accIndex, Student* students, Officer* officers, Faculty* faculty){
    cout << "\n  ⚙️ MY INFORMATION\n";
    cout << "----------------------------------------------------------\n";

    if(role == STUDENT){
        Student* sp = &students[accIndex];  // pointer
        cout << "  ID         : " << sp->ID        << "\n";
        cout << "  Name       : " << sp->name      << "\n";
        cout << "  Program    : " << sp->program   << "\n";
        cout << "  Year Level : " << sp->yearLevel << "\n";
    } else if(role == OFFICER){
        Officer* op = &officers[accIndex];  // pointer
        cout << "  ID         : " << op->ID        << "\n";
        cout << "  Name       : " << op->name      << "\n";
        cout << "  Program    : " << op->program   << "\n";
        cout << "  Year Level : " << op->yearLevel << "\n";
        cout << "  Position   : " << op->position  << "\n";
    } else {
        Faculty* fp = &faculty[accIndex];   // pointer
        cout << "  ID         : " << fp->ID   << "\n";
        cout << "  Name       : " << fp->name << "\n";
    }

    cout << "----------------------------------------------------------\n";
    pauseScreen();
}

void editMyInfo(int role, int accIndex, Student* students, int& studentCount, Officer* officers, int& officerCount, Faculty* faculty,  int& facultyCount){
    cout << "\n✏️ EDIT MY INFORMATION\n";
    cout << "----------------------------------------------------------\n";

    if(role == STUDENT){
        Student* sp = &students[accIndex];
        cout << "  Current ID         : " << sp->ID        << "\n";
        cout << "  Current Name       : " << sp->name      << "\n";
        cout << "  Current Program    : " << sp->program   << "\n";
        cout << "  Current Year Level : " << sp->yearLevel << "\n";
        cout << "----------------------------------------------------------\n";
        cout << "\n[1] ID\n[2] Name\n[3] Program\n[4] Year Level\n";
    } else if(role == OFFICER){
        Officer* op = &officers[accIndex];
        cout << "  Current ID         : " << op->ID        << "\n";
        cout << "  Current Name       : " << op->name      << "\n";
        cout << "  Current Program    : " << op->program   << "\n";
        cout << "  Current Year Level : " << op->yearLevel << "\n";
        cout << "  Current Position   : " << op->position  << "\n";
        cout << "----------------------------------------------------------\n";
        cout << "\n[1] ID\n[2] Name\n[3] Program\n[4] Year Level\n[5] Position\n";
    } else {
        Faculty* fp = &faculty[accIndex];
        cout << "  Current ID   : " << fp->ID   << "\n";
        cout << "  Current Name : " << fp->name << "\n";
        cout << "----------------------------------------------------------\n";
        cout << "\n[1] ID\n[2] Name\n";
    }

    int field;
    enterPrompt("\nSelect field to edit: ", field);

    if(role == STUDENT){
        switch(field){
            case 1: enterPrompt("🆔 New ID          : ", students[accIndex].ID);   break;
            case 2: enterPrompt("👤 New Name        : ", students[accIndex].name); break;
            case 3:
                enterPrompt("📚 New Program     : ", students[accIndex].program);
                while(students[accIndex].program != "BSIT" && students[accIndex].program != "bsit" &&
                      students[accIndex].program != "DIT"  && students[accIndex].program != "dit"){
                    cout << "\n[!] Must be BSIT or DIT only.\n";
                    enterPrompt("📚 New Program     : ", students[accIndex].program);
                }
                break;
            case 4:
                enterPrompt("⭐ New Year Level  : ", students[accIndex].yearLevel);
                while(students[accIndex].yearLevel < 1 || students[accIndex].yearLevel > 4){
                    cout << "\n[!] Valid year levels are 1 to 4 only.\n";
                    enterPrompt("⭐ New Year Level  : ", students[accIndex].yearLevel);
                }
                break;
            default: cout << "\n[!] Invalid choice.\n"; pauseScreen(); return;
        }
        saveStudentsCSV(students, studentCount);

    } else if(role == OFFICER){
        switch(field){
            case 1: enterPrompt("🆔 New ID          : ", officers[accIndex].ID);   break;
            case 2: enterPrompt("👤 New Name        : ", officers[accIndex].name); break;
            case 3:
                enterPrompt("💻 New Program     : ", officers[accIndex].program);
                while(officers[accIndex].program != "BSIT" && officers[accIndex].program != "bsit" &&
                      officers[accIndex].program != "DIT"  && officers[accIndex].program != "dit"){
                    cout << "\n[!] Must be BSIT or DIT only.\n";
                    enterPrompt("💻 New Program     : ", officers[accIndex].program);
                }
                break;
            case 4:
                enterPrompt("📈 New Year Level  : ", officers[accIndex].yearLevel);
                while(officers[accIndex].yearLevel < 1 || officers[accIndex].yearLevel > 4){
                    cout << "\n[!] Valid year levels are 1 to 4 only.\n";
                    enterPrompt("📈 New Year Level  : ", officers[accIndex].yearLevel);
                }
                break;
            case 5: enterPrompt("🎖️ New Position    : ", officers[accIndex].position); break;
            default: cout << "\n[!] Invalid choice.\n"; pauseScreen(); return;
        }
        saveOfficersCSV(officers, officerCount);

    } else {
        switch(field){
            case 1: enterPrompt("🆔 New ID  : ", faculty[accIndex].ID);   break;
            case 2: enterPrompt("👤 New Name: ", faculty[accIndex].name); break;
            default: cout << "\n[!] Invalid choice.\n"; pauseScreen(); return;
        }
        saveFacultyCSV(faculty, facultyCount);
    }

    cout << "\n[✔ ] Information updated successfully.\n";
    pauseScreen();
}

void changePasscode(int role, int accIndex, Student* students, int& studentCount, Officer* officers, int& officerCount, Faculty* faculty,  int& facultyCount){
    string* storedPass = (role == STUDENT) ? &students[accIndex].passcode :
                         (role == OFFICER) ? &officers[accIndex].passcode  :
                                             &faculty[accIndex].passcode;

    string currentPass;
    enterPrompt("🔑 Enter current passcode: ", currentPass);
    if(*storedPass != currentPass){
        cout << "\n[!] Incorrect passcode.\n"; pauseScreen(); return;
    }

    string newPass;
    enterPrompt("🔑 Enter new passcode   : ", newPass);
    while(newPass.length() < 8){
        cout << "\n[!] Passcode too short. Minimum 8 characters.\n";
        enterPrompt("🔑 Enter new passcode   : ", newPass);
    }

    string confirm;
    enterPrompt("🔄 Confirm new passcode : ", confirm);
    while(confirm != newPass){
        cout << "\n[!] Passcodes do not match.\n";
        enterPrompt("🔄 Confirm new passcode : ", confirm);
    }

    *storedPass = newPass;  // pointer write — updates the correct array

    if(role == STUDENT)       saveStudentsCSV(students, studentCount);
    else if(role == OFFICER)  saveOfficersCSV(officers, officerCount);
    else                      saveFacultyCSV(faculty,   facultyCount);

    cout << "\n[✔ ] Passcode changed successfully.\n";
    pauseScreen();
}

void landingPage(bool& isLoggedIn){
    cls(); displayHeader();
    int choice = 0;
    do {
        cout << "\n[1] Login\n[2] Exit\n";
        enterPrompt("\nEnter choice: ", choice);
        if(choice != 1 && choice != 2)
            cout << "\n[!] Invalid choice. Please enter 1 or 2 only.\n";
    } while(choice != 1 && choice != 2);

    if(choice == 1){
        isLoggedIn = true;
    } else {
        cls(); displayHeader();
        cout << "\n       Thank you for using iSPACE Portal. Goodbye! 👋\n\n";
        cout << "\033[94m" << R"(
                           /\_/\  /\
                          ( o.o )/ /
                           > ^ <  /
                          /     \/

                         |       |
                        (___)___)
                        )" << "\033[0m" << endl;
        Sleep(1500);
        isLoggedIn = false;
    }
}

bool isValidDate(const string& date){
    if(date.length() != 10) return false;
    if(date[2] != '/' || date[5] != '/') return false;
    for(int i = 0; i < 10; i++){
        if(i == 2 || i == 5) continue;
        if(!isdigit(date[i])) return false;
    }
    return true;
}

bool isValidTime(const string& time){
    if(time.length() != 5) return false;
    if(time[2] != ':') return false;
    for(int i = 0; i < 5; i++){
        if(i == 2) continue;
        if(!isdigit(time[i])) return false;
    }
    return true;
}

void pauseScreen(){
    cout << "\n";
    system("pause");
}

void cls(){
    system("cls");
}

// Function Overloading — three versions of enterPrompt
void enterPrompt(const string& prompt, string& val){
    do {
        cout << prompt;
        getline(cin, val);
    } while(isEmpty(val));
}

void enterPrompt(const string& prompt, int& val){
    while(true){
        cout << prompt;
        if(cin >> val && val != 0){
            cin.ignore(1000, '\n');
            return;
        }
        if(val == 0 && cin.good()){
            cin.ignore(1000, '\n');
            return; // 0 is valid for "log out"
        }
        cout << "\n[!] Please enter a valid number.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

void enterPrompt(const string& prompt, char& val){
    cout << prompt;
    cin >> val;
    cin.ignore(1000, '\n');
}

bool isEmpty(const string& str){
    if(str.empty()){ cout << "\n[!] Please fill in this field.\n\n"; return true; }
    return false;
}
