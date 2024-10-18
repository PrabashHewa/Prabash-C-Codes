#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

struct Student
{
    string name_;
    string birth_day_;
};

// Prints the given student and preceding text if such is given.
void print(Student* student, const string& pre_text = "")
{
    cout << pre_text;
    if(student)
    {
        cout << student->name_ << " --- " << student->birth_day_ << endl;
    }
    else
    {
        cout << "None" << endl;
    }
}

void find_same(const vector<Student*>& course1, const vector<Student*>& course2)
{
    unordered_set<Student*> printed_students;

    for (Student* stud1 : course1)
    {
        if (stud1 != nullptr)
        {
            for (Student* stud2 : course2)
            {
                if (stud2 != nullptr && stud1->name_ == stud2->name_ && stud1->birth_day_ == stud2->birth_day_)
                {
                    print(stud1, "* Same student in two courses: ");
                    printed_students.insert(stud1);
                }
            }
        }
    }
}

Student* find_first_occurrence(const string& name, const string& birth_day, const vector<Student*>& course)
{
    for (Student* student : course)
    {
        if (student != nullptr && student->name_ == name && student->birth_day_ == birth_day)
        {
            return student;  // Return the first match found
        }
    }
    return nullptr;  // No match found
}

void find_identical(const vector<Student*>& course)
{
    for (size_t i = 0; i < course.size(); ++i)
    {
        for (size_t j = i + 1; j < course.size(); ++j)
        {
            if (course[i] != nullptr && course[j] != nullptr &&
                course[i]->name_ == course[j]->name_ && course[i]->birth_day_ == course[j]->birth_day_ &&
                course[i] != course[j])  // Ensure they are different pointers
            {
                print(course[i], "* Identical students in a course: ");
            }
        }
    }
}


// Don't remove! Needed for tests.
#ifndef POINTERS_TEST
#define POINTERS_TEST
// Don't remove! Needed for tests.

// Main function (an example test case)
int main()
{
    // Students
    Student stud1{"Mortti", "2001-01-01"};
    Student stud2{"Vertti", "2002-02-02"};
    Student stud3{"Mortti", "2001-01-01"};

    // Assigning students to courses
    vector<Student*> prog1 = {nullptr, &stud1, &stud2};
    vector<Student*> prog2 = {&stud1, &stud2, &stud3};
    vector<Student*> prog3 = {&stud1, &stud3};

    // Different seaches
    cout << "Seaching for same students from two different courses" << endl;
    find_same(prog1, prog2);

    cout << endl << "Searching for identical students from a course" << endl;
    find_identical(prog3);

    cout << endl << "Searching for a certain student from a course" << endl;
    Student* wanted = find_first_occurrence("Mortti", "2001-01-01", prog1);
    print(wanted, "* ");
    wanted = find_first_occurrence("Mortti", "2002-02-02", prog1);
    print(wanted, "* ");

    return 0;
}

// Don't remove! Needed for tests.
#endif //POINTERS_TEST
// Don't remove! Needed for tests.
