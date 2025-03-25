#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class courseType {

    private:

        string courseName;
        string courseNo;
        int courseCredits;
        char courseGrade;

    public:

        courseType(string c_name = "", string c_no = "", int c_credits = 0, char c_grade = '*') /* : courseName(c_name), courseNo(c_no), courseGrade(c_grade), courseCredits(c_credits)  */  {

            courseName = c_name;
            courseNo = c_no;
            courseCredits = c_credits;
            courseGrade = c_grade;

        }

        void setCourseInfo(string c_name, string c_no, int c_credits, char c_grade) {

            courseName = c_name;
            courseNo = c_no;
            courseCredits = c_credits;
            courseGrade = c_grade;
        }


        void print(courseType courseEnrolled) {   // print to the screen

            cout << left;
            cout << setw(15) << courseEnrolled.getCourseNumber() << "\t";
            cout << setw(15) << courseEnrolled.getCourseName() << "\t";
            cout << setw(15) <<  courseEnrolled.getCredits() << "\t";
            cout << setw(15) << courseEnrolled.getGrade() << endl;
        
        }    

        void print(courseType courseEnrolled, ofstream& outFile) { 
            
            outFile << left;
            outFile << setw(15) << courseEnrolled.getCourseNumber() << "\t";
            outFile << setw(15) << courseEnrolled.getCourseName() << "\t";
            outFile << setw(15) <<  courseEnrolled.getCredits() << "\t";
            outFile << setw(15) << courseEnrolled.getGrade() << endl;
        
        }   
        
        int getCredits() {

            return courseCredits;

        }
        string getCourseNumber() {

            return courseNo;
        }

        char getGrade() {

            return courseGrade;
        }

        string getCourseName() {
            return courseName;
        }

};

class PersonType {

    protected:
        string firstName;
        string lastName;
};


class StudentType : public PersonType {

    private:
        int sID; // Student ID
        int numberOfCourses;
        char isTuitionPaid;

    public:
        courseType *courseEnrolled;  // In order to define it dynamically
        StudentType();
        StudentType(string, string, int, int, char);
        ~StudentType();
        void setInfo(string s_name, string s_lastname, int s_sID, int s_numberOfCourses, char s_isTuitionPaid, courseType s_courseEnrolled[]);
        void print(ofstream &output_file); 
        void print(); // to print to the screen
        void setName(string s_name, string s_lastname);
        string getName();
        int getHoursEnrolled();
        float getGpa();
        int billingAmount(int paidPerCredit);
        void sortCourses();
        char getIsTuitionPaid();
        int getnumberOfCourses();

};

int main() {

    int total_students, paidPerCredit;
    
    string firstName, lastName;
    int sID, numberOfCourses;
    char isTuitionPaid;


    ifstream file("input.txt");

    if(!file) {
        cerr << "File could not be opened!" << endl;
        return 0;
    }

    file >> total_students;  // reads up to whitespace characters
    file >> paidPerCredit;   // reads up to whitespace characters

    // cout << total_students << endl;
    // cout << paidPerCredit;      // to check if file was read correctly

    if (total_students <= 0) {

        cerr << "Invalid numbers of students!" << endl; 
    }

    StudentType* students = new StudentType[total_students]; // Needs no parameter constructor (It will call none parameter constructor)
    
    for (int i = 0; i < total_students; i++) {

        file >> firstName;
        file >> lastName;
        file >> sID;
        file >> isTuitionPaid;
        file >> numberOfCourses;

        courseType* courseEnrolled = new courseType[numberOfCourses];

        for (int j = 0; j < numberOfCourses; j++) {

            string course_name, course_no;
            int course_credits;
            char course_grade;

            file >> course_name;
            file >> course_no;
            file >> course_credits;
            file >> course_grade;

            courseEnrolled[j].setCourseInfo(course_name, course_no, course_credits, course_grade);

        }

        students[i].setInfo(firstName, lastName, sID, numberOfCourses, isTuitionPaid, courseEnrolled);
        students[i].sortCourses();
        
    }

    file.close();

    ofstream outputFile("output.txt");


    if(!outputFile) {
        cerr << "File could not be opened!" << endl;
        return 0;
    }

    for (int i = 0; i < total_students; i++) {
        
        outputFile << i + 1 << "/" << endl;
        outputFile << "--------" << endl;

        cout << i + 1 << "/" << endl;
        cout << "--------" << endl;

        students[i].print(outputFile);
        students[i].print(); // to print to the screen
    
        if (students[i].getIsTuitionPaid() == 'Y') {
            
            outputFile << left;
            outputFile << setw(15) << "Course No" 
            << setw(15) << "Course Name" 
            << setw(15) <<"Credits" 
            << setw(15) << "Grade" << endl;
            
            cout << left;
            cout << setw(15) << "Course No"
            << setw(15) << "Course Name"
            << setw(15) << "Credits"
            << setw(15) << "Grade" << endl;
            
            for(int j = 0; j < students[i].getnumberOfCourses(); j++) {

                students->courseEnrolled->print(students[i].courseEnrolled[j], outputFile);
                students->courseEnrolled->print(students[i].courseEnrolled[j]); // to print to the screen
            }

            outputFile << endl;
            outputFile << "Total Number of Credits: " << students[i].getHoursEnrolled() << endl;
            outputFile << "Mid - Semester GPA: " << fixed << setprecision(2) << students[i].getGpa() << endl << endl;

            cout << endl;
            cout << "Total Number of Credits: " << students[i].getHoursEnrolled() << endl;
            cout << "Mid - Semester GPA: " << fixed << setprecision(2) << students[i].getGpa() << endl << endl;
        }

        else {

            outputFile << "Total number of credits: " << students[i].getHoursEnrolled() << endl << endl;
            outputFile << "The tuition fee has not been paid, so your grades cannot be shown." << endl;
            outputFile << "Please pay the required fee." << endl;
            outputFile << "Tuition Fee: " << students[i].billingAmount(paidPerCredit) << endl << endl;


            cout << "Total number of credits: " << students[i].getHoursEnrolled() << endl << endl;
            cout << "The tuition fee has not been paid, so your grades cannot be shown." << endl;
            cout << "Please pay the required fee." << endl;
            cout << "Tuition Fee: " << students[i].billingAmount(paidPerCredit) << endl << endl;

        }
    
    
    }


    outputFile.close();




    return 0;
}

StudentType::StudentType() {

    sID = 0;
    numberOfCourses = 0;
    courseEnrolled = nullptr; // Initialize to nullptr(without this program does not work!!!)

}

StudentType::StudentType(string s_firstName, string s_lastName, int s_sID, int s_numberOfCourse, char s_isTuitionPaid) {

    setName(s_firstName, s_lastName);
    lastName = s_lastName;
    sID = s_sID;
    numberOfCourses = s_numberOfCourse;
    isTuitionPaid = s_isTuitionPaid;
    courseEnrolled = nullptr; // Initialize to nullptr


}

StudentType::~StudentType() {

    delete[] courseEnrolled;
}

void StudentType::setInfo(string s_firstName, string s_lastName, int s_sID, int s_numberOfCourses, char s_isTuitionPaid, courseType s_courseEnrolled[]) {

    setName(s_firstName, s_lastName);
    lastName = s_lastName;
    sID = s_sID;
    numberOfCourses = s_numberOfCourses;
    isTuitionPaid = s_isTuitionPaid;

    if (courseEnrolled != nullptr) {  

        delete[] courseEnrolled;
    }

    courseEnrolled = new courseType[numberOfCourses];
    
    for (int i = 0; i < s_numberOfCourses; i++) {

        courseEnrolled[i] = s_courseEnrolled[i];
    }
}

void StudentType::print(ofstream &output_file) {

    output_file << "Student Name: " << getName() << endl;
    output_file << "Student ID: " << sID << endl;
    output_file << "Number of courses enrolled: " << numberOfCourses << endl;

    output_file << endl;

}

void StudentType::print() {

    cout << "Student Name: " << getName() << endl;
    cout << "Student ID: " << sID << endl;
    cout << "Number of courses enrolled: " << numberOfCourses << endl;

    cout << endl;

}

void StudentType::setName(string s_name, string s_lastName) {

    firstName = s_name;
    lastName = s_lastName;
}

string StudentType::getName() {

    return firstName + " " + lastName;
}

int StudentType::getHoursEnrolled() {
    
    if (numberOfCourses == 0) {
        
        cout << "No courses enrolled." << endl;   // Checks if numberOfCourses is updated
        return 0;
    }

    int total = 0;
    for (int i = 0; i < numberOfCourses; i++) {

        total += courseEnrolled[i].getCredits();
    }

    return total;
}

float StudentType::getGpa() {

    float totalPoints = 0;
    int totalCredits = 0;
    char grade_check;

    for (int i = 0; i < numberOfCourses; i++) {

        grade_check = courseEnrolled[i].getGrade();
        int credits = courseEnrolled[i].getCredits();
        int points = 0;
    

        switch(grade_check) {

            case 'A':
                points = 4;
                break;

            case 'B':
                points = 3;
                break;

            case 'C':
                points = 2;
                break;

            case 'D':
                points = 1;
                break;

            default:
                cout << "Grade value was not captured correctly" << endl;
                points = 0;
                break;

        }
    
        totalPoints += points * credits;
        totalCredits += credits;
    }

        if (totalCredits == 0) return 0;
        return float(totalPoints / totalCredits);
}


int StudentType::billingAmount(int paidPerCredit) {

    return getnumberOfCourses() * paidPerCredit;
}

void StudentType::sortCourses() {

    for (int i = 0; i < numberOfCourses - 1; i++) {

        for (int j = 0; j < numberOfCourses - i - 1; j++) {

            if (courseEnrolled[j].getCourseNumber() > courseEnrolled[j + 1].getCourseName()) {

                courseType temp = courseEnrolled[j];
                courseEnrolled[j] = courseEnrolled[j + 1];
                courseEnrolled[j + 1] = temp;
            }
        }
    }
}

char StudentType::getIsTuitionPaid() {
   
    return isTuitionPaid;
}

int StudentType::getnumberOfCourses() {

    return numberOfCourses;
}