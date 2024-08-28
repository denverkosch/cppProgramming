#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> grades;

void addGrade();
void removeGrade();
void showGrades();
void showFinalGrade(bool dropLowest);
int getNumInput();


int main() {
    int selected = 0;
    while (selected != 6) {
        cout << endl << "1. Enter grade" << endl << "2. Remove grade" << endl << "3. Show grades" << endl << "4. Show final grade" << endl << "5. Show final grade, drop lowest" << endl << "6. Quit" << endl;

        cout << "Select an option: ";
        selected = getNumInput();
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

int getNumInput() {
    int num = -1;
    do {
        string input;
        cin >> input;
        try {
            num = stoi(input);
        }
        catch (exception e) {
            cout << "Invalid input. Please enter a number: ";
            continue;
        }
    } while (num == -1);
    return num;
}

void addGrade() {
    int grade = -1;
    cout << "Enter grade: ";
    do {
    grade = getNumInput();
    } while (grade > 100 || grade < 0);
    grades.push_back(grade);
}

void removeGrade() {
    int grade = -1;
    cout << endl << "Enter grade to remove: ";
    grade = getNumInput();

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
    cout << endl;
}

void showFinalGrade(bool dropLowest) {
    int sum = 0;

    if (dropLowest && grades.size() > 0) {
        int lowest = grades[0];
        for (int i = 1; i < grades.size(); i++) {
            if (grades[i] < lowest) lowest = grades[i];
        }

        cout << lowest << endl;
        for (int i = 0; i < grades.size(); i++) sum += grades[i];

        cout << "Final grade: " << (sum - lowest) / (grades.size() - 1) << endl;
    }
    else {
        for (int i = 0; i < grades.size(); i++) sum += grades[i];
        
        cout << "Final grade: " << sum / grades.size() << endl;
    }

    cout << endl;
}
