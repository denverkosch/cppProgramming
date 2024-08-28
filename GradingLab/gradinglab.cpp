#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> grades;

void addGrade();
void removeGrade();
void showGrades();
void showFinalGrade(bool dropLowest);


int main() {
    int selected = 0;
    while (selected != 6) {
        cout << endl << "1. Enter grade" << endl << "2. Remove grade" << endl << "3. Show grades" << endl << "4. Show final grade" << endl << "5. Show final grade, drop lowest" << endl << "6. Quit" << endl;

        cin >> selected;
        cout << endl;

        switch (selected) {
            case 1:
                addGrade();
                break;
            case 2:
                removeGrade();
                break;
            case 3:
                showGrades();
                break;
            case 4:
                showFinalGrade(false);
                break;
            case 5:
                showFinalGrade(true);
                break;
            case 6:
                cout << "Done grading!" << endl;
                break;
            default:
                break;
        }
    }
}

void addGrade() {
    int grade;
    cout << "Enter grade: ";
    cin >> grade;
    grades.push_back(grade);
}

void removeGrade() {
    int grade;
    cout << endl << "Enter grade to remove: ";
    cin >> grade;

    for (int i = 0; i < grades.size(); i++) {
        if (grades[i] == grade) {
            grades.erase(grades.begin() + i);
            return;
        }
    }
    cout << "Could not find grade" << endl;

}

void showGrades() {
    cout << "Grades: " << endl;
    for (int i = 0; i < grades.size(); i++) cout << grades[i] << endl;
    
    cout << endl << "Press Enter to continue...";
    cin.get();
}

void showFinalGrade(bool dropLowest) {
    int sum = 0;
    if (dropLowest) {
        int lowest = grades[0];
        for (int i = 1; i < grades.size(); i++) {
            if (grades[i] < lowest) lowest = grades[i];
        }
        for (int i = 0; i < grades.size(); i++) sum += grades[i];

        cout << "Final grade: " << (sum - lowest) / (grades.size() - 1) << endl;
    }
    else {
        for (int i = 0; i < grades.size(); i++) sum += grades[i];
        
        cout << "Final grade: " << sum / grades.size() << endl;
    }
}
