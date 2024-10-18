#include <iostream>
#include <limits>

using namespace std;

int main() {

    cout << "Enter a number: ";
    int num;
    cin >> num;

    int cube = num * num * num;

    if (num != 0 && (cube / num / num != num)) {
        cout << "Error! The cube of " << num << " is not " << cube << "." << endl;
    } else {
        cout << "The cube of " << num << " is " << cube << "." << endl;
    }

    return 0;
}

