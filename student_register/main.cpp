#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;

const string HELP_TEXT =
        "N                  = List ordered by student numbers\n"
        "U                  = List ordered alphabetically by user ids\n"
        "C <student_number> = Change the given student's phone number\n"
        "Q                  = Quit\n";

const unsigned int NUMBER_OF_FIELDS = 6;

struct Student {
    string student_number;
    string user_id;
    string name;
    string phone_number;
    string email;
    string skype;
};

vector<string> split(const string& s, const char delimiter, bool ignore_empty = false) {
    vector<string> result;
    string tmp = s;

    while( tmp.find(delimiter) != string::npos ) {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if( not (ignore_empty and new_part.empty()) ) {
            result.push_back(new_part);
        }
    }
    if( not (ignore_empty and tmp.empty()) ) {
        result.push_back(tmp);
    }
    return result;
}

bool read_data(const string& file_name,
               map<string, shared_ptr<Student>>& alphabetical_order,
               map<string, shared_ptr<Student>>& numerical_order) {
    ifstream file_object(file_name);
    if( not file_object ) {
        return false;
    }

    string line = "";
    while( getline(file_object, line) ) {
        vector<string> parts = split(line, ';');
        if( parts.size() != NUMBER_OF_FIELDS ) {
            return false;
        }

        shared_ptr<Student> new_student =
                make_shared<Student>(Student{parts[0], parts[1], parts[2],
                                             parts[3], parts[4], parts[5]});
        numerical_order[parts[0]] = new_student;
        alphabetical_order[parts[1]] = new_student;
    }
    file_object.close();
    return true;
}

void print_data(const Student& s) {
    cout << s.student_number << " " << s.user_id << endl
         << s.name << endl
         << s.phone_number << endl
         << s.email << endl
         << s.skype << endl;
}

bool is_valid_phone_number(const string number) {
    for( unsigned int i = 0; i < number.length(); ++i ) {
        if( not(('0' <= number[i] and number[i] <= '9')
            or number[i] == ' ' or number[i] == '-') ) {
            cout << "Erroneous phone number: " << number << endl;
            return false;
        }
    }
    return true;
}

void update_student_phone(map<string, shared_ptr<Student>>& student_numbers, const string& student_number) {
    auto it = student_numbers.find(student_number);
    if (it == student_numbers.end()) {
        cout << "There is no student with the given number!" << endl;
        return;
    }

    string new_phone;
    while (true) {
        cout << "Enter a new phone number: ";
        getline(cin, new_phone);
        if (is_valid_phone_number(new_phone)) {
            it->second->phone_number = new_phone;
            cout << "Phone number updated successfully!" << endl;
            break;
        }
    }
}

int main() {
    string file_name = "";
    cout << "Student file: ";
    getline(cin, file_name);

    map<string, shared_ptr<Student>> user_ids;
    map<string, shared_ptr<Student>> student_numbers;
    if( not read_data(file_name, user_ids, student_numbers) ) {
        cout << "Error in reading file!" << endl;
        return EXIT_FAILURE;
    }

    cout << HELP_TEXT << endl;

    while( true ) {
        string line;
        cout << "register> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ', true);

        if( parts.empty() ) {
            continue;
        }
        string command = parts.at(0);

        if( command == "U" or command == "u" ) {
            if( parts.size() != 1 ) {
                cout << "Erroneous parameters!" << endl  << HELP_TEXT;
                continue;
            } else {
                for( auto& pair: user_ids ) {
                    print_data(*(pair.second));
                }
            }

        } else if( command == "N" or command == "n" ) {
            if(parts.size() != 1){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            } else {
                for( auto& pair: student_numbers ) {
                    print_data(*(pair.second));
                }
            }

        } else if( command == "C" or command == "c" ) {
            if( parts.size() != 2 ){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string student_number = parts[1];
            update_student_phone(student_numbers, student_number);

        } else if( command == "Q" or command == "q" ) {
            return EXIT_SUCCESS;

        } else {
            cout << "Erroneous command!" << endl << HELP_TEXT;
        }
    }
}


