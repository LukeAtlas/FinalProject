#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <Python.h>

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
        cout << tempTime[0] << ","<< tempTime[1] << ","<< tempTime[2] << endl;
    }
};

string myCounter(int theCount);
double dayParse(string myDay);
vector<vector<int>> myGen(int n,int r,vector<int> classVec);
void printSched(vector<vector<int>> schedules, vector<Course> myCourses, vector<vector<vector<int>>> subGroups);
Course addCourse();
void isPossible(vector<Course> theCourses);

int main() {
    string myExit;
    bool isdone = 0;
    vector<Course> allCourses;
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

vector<vector<int>> firstFilter(int n, int r, vector<int> classVec, vector<vector<vector<double>>> sectTimes) { // returns all combinations of subsections without any repeats or time conflicts
    cout << n << "," << r << "," << classVec[0] << "," << classVec.size() << endl;
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
                tempVec.push_back((i+1));
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
                    else {
                        bool conflict = false;
                        if (tempVec.size()>1) {
                            for (int m=tempVec.size()-2;m>=0;m--) {
                                for (int l=0;l<sectTimes[tempVec[tempVec.size()-1]-1].size();l++) {
                                    for (int p=0;p<sectTimes[tempVec[m]-1].size();p++){
                                        if (sectTimes[tempVec[tempVec.size()-1]-1][l][0]==sectTimes[tempVec[m]-1][p][0]) {
                                            if ((sectTimes[tempVec[tempVec.size()-1]-1][l][1]>=sectTimes[tempVec[m]-1][p][1])&&(sectTimes[tempVec[tempVec.size()-1]-1][l][1]<=sectTimes[tempVec[m]-1][p][2])) {
                                                conflict = true;
                                                break;
                                            }
                                            else if ((sectTimes[tempVec[tempVec.size()-1]-1][l][2]>=sectTimes[tempVec[m]-1][p][1])&&(sectTimes[tempVec[tempVec.size()-1]-1][l][2]<=sectTimes[tempVec[m]-1][p][2])) {
                                                conflict = true;
                                                break;
                                            }
                                            else if ((sectTimes[tempVec[tempVec.size()-1]-1][l][1]<=sectTimes[tempVec[m]-1][p][1])&&(sectTimes[tempVec[tempVec.size()-1]-1][l][2]>=sectTimes[tempVec[m]-1][p][2])) {
                                                conflict = true;
                                                break;
                                            }
                                        }
                                    }
                                    if (conflict) {
                                        break;
                                    }
                                }
                                if (conflict) {
                                    break;
                                }
                            }
                        }
                        if (conflict) {
                            repeats = true;
                            break;
                        }
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

vector<vector<int>> secondFilter(int n, int r, vector<int> courseVec, vector<vector<vector<int>>> subGroups, vector<Course> allCourses) { // returns all combinations of subsections without any repeats or time conflicts
    cout << n << "," << r << "," << subGroups.size() <<endl;
    vector<bool> v(n);
    vector<int> tempVec;
    vector<int> repCheck;
    vector<vector<int>> myVec;
    vector<vector<double>> theTimes;
    for (int i=0;i<courseVec.size();i++) {
        repCheck.push_back(0);
    }
    fill(v.begin(), v.begin() + r, true);
    do {
        bool repeats = false;
        for (int i = 0; i < n; ++i) {
            if (v[i]) {
                cout << (i+1) << " ";
                tempVec.push_back((i+1));
                for (int k=0;k<courseVec.size();k++) {
                    bool wasfound = false;
                    if (tempVec[tempVec.size()-1]<=courseVec[k]) {
                        if (k==0) {
                            if (tempVec[tempVec.size()-1]>0) {
                                repCheck.at(k) = repCheck.at(k) + 1;
                                wasfound = true;
                            }
                        }
                        else if (tempVec[tempVec.size()-1]>courseVec[k-1]) {
                            repCheck.at(k) = repCheck.at(k) + 1;
                            wasfound = true;
                        }
                    }
                    if (repCheck[k]>1) {
                        repeats = true;
                        break;
                    }
                    else if (wasfound) {
                        bool conflict = false;
                        int subOffset = 0;
                        if (k>0) {
                            for (int d=k-1;d>=0;d--) {
                                subOffset = subOffset + subGroups[d].size();
                            }
                        }
                        int sectOffset = 0;
                        int timesAdded = 0;
                        int groupNum = tempVec[tempVec.size()-1]-1-subOffset;
                        int groupSize = subGroups[k][groupNum].size();
                        for (int v=0;v<groupSize;v++) {
                            if (v>0) {
                                for (int r=v-1;r>=0;r--) {
                                    sectOffset = sectOffset + allCourses[k].subs[r].sectCount;
                                }
                            }
                            int timeCount = allCourses[k].subs[v].sects[subGroups[k][groupNum][v]-1-sectOffset].times.size();
                            for (int c=0;c<timeCount;c++) {
                                theTimes.push_back(allCourses[k].subs[v].sects[subGroups[k][groupNum][v]-1-sectOffset].times[c]);
                                timesAdded++;
                            }
                        }
                        if (tempVec.size()>1) {
                            for (int m=theTimes.size()-timesAdded-1;m>=0;m--) {
                                for (int l=theTimes.size()-timesAdded;l<theTimes.size();l++) {
                                    if (theTimes[l][0]==theTimes[m][0]) {
                                        if ((theTimes[l][1]>=theTimes[m][1])&&(theTimes[l][1]<=theTimes[m][2])) {
                                            conflict = true;
                                            break;
                                        }
                                        else if ((theTimes[l][2]>=theTimes[m][1])&&(theTimes[l][2]<=theTimes[m][2])) {
                                            conflict = true;
                                            break;
                                        }
                                        else if ((theTimes[l][1]<=theTimes[m][1])&&(theTimes[l][2]>=theTimes[m][2])) {
                                            conflict = true;
                                            break;
                                        }
                                    }
                                    if (conflict) {
                                        break;
                                    }
                                }
                                if (conflict) {
                                    break;
                                }
                            }
                        }
                        if (conflict) {
                            repeats = true;
                            break;
                        }
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
        for (int i=0;i<courseVec.size();i++) {
            repCheck.push_back(0);
        }
        tempVec.clear();
        theTimes.clear();
        cout << "\n";
    } while (prev_permutation(v.begin(), v.end()));
    return myVec;
}

void isPossible(vector<Course> theCourses) {
    int courseNum = theCourses.size();
    vector<int> indSect;
    vector<vector<vector<int>>> filtList; // list of filtered subsection pairs grouped by course
    vector<vector<vector<double>>> sectTimes;
    bool notPossible = false;
    for (int i=0;i<courseNum;i++) {
        int sectNum = 0;
        for (int j=0;j<theCourses[i].subCount;j++) {
            sectNum = sectNum + theCourses[i].subs[j].sectCount;
            for (int k=0;k<theCourses[i].subs[j].sectCount;k++) {
                sectTimes.push_back(theCourses[i].subs[j].sects[k].times);
            }
            indSect.push_back(sectNum);
        }
        filtList.push_back(firstFilter(sectNum,theCourses[i].subCount,indSect,sectTimes)); // returns all combinations of subsections without any repeats or time conflicts
        if (filtList[i].size() == 0) {
            notPossible = true;
            break;
        }
        cout << sectNum << endl;
        indSect.clear();
        sectTimes.clear();
    }
    int subNum = 0;
    vector<int> indCourses;
    for (int i=0;i<courseNum;i++) {
        subNum = subNum + filtList[i].size();
        indCourses.push_back(subNum);
    }
    printSched(secondFilter(subNum,courseNum,indCourses,filtList,theCourses), theCourses, filtList);
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

void printSched(vector<vector<int>> schedules, vector<Course> myCourses, vector<vector<vector<int>>> subGroups) {
    ofstream myfile;
    myfile.open ("thesched.txt", std::ofstream::trunc);
    for (int i=0;i<schedules.size();i++) {
        cout << "Schedule " << (i+1) << ":" << endl;
        for (int j=0;j<myCourses.size();j++) {
            int subOffset = 0;
            if (j>0) {
                for (int d=j-1;d>=0;d--) {
                    subOffset = subOffset + subGroups[d].size();
                }
            }
            int sectOffset = 0;
            int groupNum = schedules[i][j]-1-subOffset;
            int groupSize = subGroups[j][groupNum].size();
            for (int v=0;v<groupSize;v++) {
                if (v>0) {
                    sectOffset = sectOffset + myCourses[j].subs[v-1].sectCount;
                }
                int sectNum = subGroups[j][groupNum][v]-1-sectOffset;
                int timeCount = myCourses[j].subs[v].sects[sectNum].times.size();
                cout << myCourses[j].Name << " " << myCourses[j].subs[v].Name;
                cout << " " << myCourses[j].subs[v].sects[sectNum].Name << ": ";
                for (int c=0;c<timeCount;c++) {
                    cout << myCourses[j].subs[v].sects[sectNum].times[c][0] << ",";
                    cout << myCourses[j].subs[v].sects[sectNum].times[c][1] << ",";
                    cout << myCourses[j].subs[v].sects[sectNum].times[c][2] << " | ";
                }
                cout << endl;
            }
        }
        cout << endl << endl;
    }
    myfile.close();
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