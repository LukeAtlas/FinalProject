#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

double string_to_time(string timeString);
class Course { 
    public: 
    int sectCount = 0;
    int subCount = 0;
    string Name = "";
    vector<Course> sects;
    vector<Course> subs;
    vector<vector<double>> times;

    void addSect(Course newSect) {
        sects.push_back(newSect);
        sectCount++;
    }

    void addSub(Course newSub) {
        subs.push_back(newSub);
        subCount++;
    }

    void setName(string newname) {
        Name = newname;
    }

    void resetCourse() {
        sects.erase (sects.begin(),sects.end());
        subs.erase (subs.begin(),subs.end());
        sectCount = 0;
        subCount = 0;
    }

    void update(double theDay, string sTime, string eTime) {
        vector<double> tempTime;
        tempTime.push_back(theDay);
        tempTime.push_back(string_to_time(sTime));
        tempTime.push_back(string_to_time(eTime));
        times.push_back(tempTime);
    }
};

string myCounter(int theCount);
double dayParse(string myDay);
vector<vector<int>> myGen(int n,int r,vector<int> classVec);
vector<Course> allCourses;
Course addCourse();
void isPossible(vector<Course> theCourses);

int main() {
    // vector<int> theVec = {1,2,3,4};
    // int n, r; // n = classVec.size();
    // cin >> n;
    // cin >> r;
    // vector<vector<int>> myvec = myGen(n,r,theVec);
    // cout << myvec.size() << endl;
    string myExit;
    bool isdone = 0;
    cout << "For this purpose of this application we will refer to sections and subsections.\n";
    cout << "Sections of a course are alternatives. Another offering of the same course that\n";
    cout << "may be on different days, at different times, or have a different instructor.\n";
    cout << "Subsections are required additions to a course (ie prelab,lab,discussion,lecture).\n";
    while (isdone==0) {
        allCourses.push_back(addCourse());
        cout << "Would you like to add another course? [y/n]" << endl;
        cin >> myExit;
        if ((myExit.find('N')!=-1) || (myExit.find('n')!=-1)) {
            isdone = 1;
        }
    }
    isPossible(allCourses);
    return 0; 
}

vector<vector<int>> myGen(int n,int r,vector<int> classVec) {
    vector<bool> v(n);
    vector<int> tempVec;
    vector<vector<int>> myVec;
    fill(v.begin(), v.begin() + r, true);
    do {
        for (int i = 0; i < n; ++i) {
            if (v[i]) {
                cout << classVec[i] << " ";
                tempVec.push_back(classVec[i]);
            }
        }
        myVec.push_back(tempVec);
        tempVec.clear();
        cout << "\n";
    } while (prev_permutation(v.begin(), v.end()));
    return myVec;
}

vector<vector<int>> repeatFilter(int n, int r, vector<int> classVec) { // returns all combinations of subsections without any repeats
    cout << n << "," << r<< ","<<classVec[0] << ","<<classVec[1] <<","<<classVec.size()<<endl;
    vector<bool> v(n);
    vector<int> tempVec;
    vector<vector<int>> myVec;
    vector<int> repCheck;
    for (int i=0;i<classVec.size();i++) {
        repCheck.push_back(0);
    }
    fill(v.begin(), v.begin() + r, true);
    do {
        bool repeats = false;
        for (int i = 0; i < n; ++i) {
            if (v[i]) {
                cout << (i+1) << " ";
                tempVec.push_back((i+1)); // 1234
                for (int k=0;k<classVec.size();k++) {
                    if (tempVec[tempVec.size()-1]<=classVec[k]) {
                        if (k==0) {
                            if (tempVec[tempVec.size()-1]>0) {
                                repCheck.at(k) = repCheck.at(k) + 1;
                            }
                        }
                        else if (tempVec[tempVec.size()-1]>classVec[k-1]) {
                            repCheck.at(k) = repCheck.at(k) + 1;
                        }
                    }
                    if (repCheck[k]>1) {
                        repeats = true;
                        break;
                    }
                }
            }
            if (repeats) {
                break;
            }
        }
        if (!repeats) {
            myVec.push_back(tempVec);
        }
        else {
            cout << "deleted";
            repeats = false;
        }
        repCheck.clear();
        for (int i=0;i<classVec.size();i++) {
            repCheck.push_back(0);
        }
        tempVec.clear();
        cout << "\n";
    } while (prev_permutation(v.begin(), v.end()));
    return myVec;
}

void isPossible(vector<Course> theCourses) {
    int courseNum = theCourses.size();
    vector<int> indSect;
    for (int i=0;i<courseNum;i++) {
        int sectNum = 0;
        for (int j=0;j<theCourses[i].subCount;j++) {
            sectNum = sectNum + theCourses[i].subs[j].sectCount;
            indSect.push_back(sectNum);
        }
        repeatFilter(sectNum,theCourses[i].subCount,indSect);
        cout << sectNum << endl;
        indSect.clear();
    }
}

string myCounter(int theCount) {
    int size;
    char buffer[10];
    string counted = "";
    if ((theCount>3) && (theCount<21)) {
        size = sprintf(buffer, "%dth",theCount);
    }
    else {
        int tempCount = theCount - (floor(theCount/10)*10);
        switch (tempCount) {
            case 0:
                size = sprintf(buffer, "%dth",theCount);
                break;
            case 1:
                size = sprintf(buffer, "%dst",theCount);
                break;
            case 2:
                size = sprintf(buffer, "%dnd",theCount);
                break;
            case 3:
                size = sprintf(buffer, "%drd",theCount);
                break;
            default:
                size = sprintf(buffer, "%dth",theCount);
                break;
        }
    }
    for (int i = 0; i < size; i++) { 
        counted = counted + buffer[i]; 
    } 
    return counted;
}

double dayParse(string myDay) {
    string days[7] = {
        "onday",
        "uesday",
        "ednesday",
        "hursday",
        "riday",
        "aturday",
        "unday"
    };

    // different member versions of find in the same order as above:
    size_t found;
    double dayVal;
    for (int i=0;i<7;i++) {
        found = myDay.find(days[i]);
        if (found!=string::npos) {
            dayVal = (double) i+1.0;
        }
    }
    return dayVal;
}

// n!/(r!(n-r)!)
// n = amount of possible classes (including various times)
// r = how many classes we are enrolling in

Course section(int sectNum) {
    Course sectCourse;
    int daySelect = 0;
    int dayCount = 1;
    double dayPick;
    string theDate;
    string startTime;
    string endTime;
    string dayExit;
    string sectionName;
    cout << "Please enter the name of the " << myCounter(sectNum) << " section (ie A1, B2, C3).\n";
    getline(cin,sectionName);
    //cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    sectCourse.setName(sectionName);
    while (daySelect==0) {
        cout << "What is the " << myCounter(dayCount) << " day of the week this section meets?\n";
        getline(cin,theDate);
        //cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        dayPick = dayParse(theDate);
        cout << "Please enter the start time of the " << myCounter(sectNum) << " section. (ie. 8:03 AM or 12:04 PM)\n";
        getline(cin,startTime);
        //cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please enter the end time of the " << myCounter(sectNum) << " section. (ie. 8:03 AM or 12:04 PM)\n";
        getline(cin,endTime);
        //cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        sectCourse.update(dayPick,startTime,endTime);
        cout << "Does this section meet another day? [y/n]" << endl;
        cin >> dayExit;
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        dayCount++;
        if ((dayExit.find('N')!=-1) || (dayExit.find('n')!=-1)) {
            daySelect = 1;
        }
    }
    return sectCourse;
}

Course subsection(string courseName, int subNum) {
    Course subCourse;
    string subName;
    int sectCount = 0;
    int sectCounter = 0;
    cout << "What is the name of the " << myCounter(subNum) << " subsection (ie lecture,prelab,lab,discussion)?" << endl;
    cin >> subName;
    cout << "How many sections does " << courseName << " " << subName << " have?\n";
    cin >> sectCount;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    subCourse.setName(subName);

    while (sectCounter<sectCount) {
        sectCounter++;
        subCourse.addSect(section(sectCounter));
    }
    return subCourse;
}

double string_to_time(string timeString) {
    double thetime;
    int dividerPos = timeString.find(':');
    double hours;
    double minutes;
    hours = stod(timeString.substr(0,dividerPos));
    minutes = stod(timeString.substr((dividerPos+1),2));
    if((timeString.find('P')!=-1) || (timeString.find('p')!=-1)) {
        if (hours!=12.0) {
            hours = hours + 12.0;
        }
    }
    else {
        if (hours==12.0) {
            hours = hours - 12;
        }
    }
    thetime = hours + (minutes/100);
    return thetime;
}

Course addCourse() {
    Course myCourse;
    string courseName;
    int subCount = 0;
    int counter = 1;
    cout << "What is the name of the course?" << endl;
    cin >> courseName;
    cout << "How many subsections does " << courseName << " have? (ie lecture,prelab,lab,discussion)\n";
    cin >> subCount;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    myCourse.setName(courseName);
    while (counter<=subCount) {
        myCourse.addSub(subsection(courseName,counter));
        counter++;
    }
    return myCourse;
}