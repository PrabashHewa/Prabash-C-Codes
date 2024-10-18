#include <iostream>

using namespace std;

unsigned long long factorial(int num) {
    if (num == 0 || num == 1)
        return 1;

    unsigned long long fact = 1;
    for (int i = 2; i <= num; i++)
        fact *= i;

    return fact;
}


unsigned long long combinations(int total_balls, int drawn_balls) {
    return factorial(total_balls) / (factorial(drawn_balls) * factorial(total_balls - drawn_balls));
}

int main() {
    int total_balls, drawn_balls;


    cout << "Enter the total number of lottery balls: ";
    cin >> total_balls;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn_balls;


    if (total_balls <= 0 || drawn_balls <= 0) {
        cout << "The number of balls must be a positive number." << endl;
        return 0;  // Return 0 to indicate successful termination
    }

    if (drawn_balls > total_balls) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return 0;  // Return 0 to indicate successful termination
    }

    unsigned long long total_combinations = combinations(total_balls, drawn_balls);

    cout << "The probability of guessing all " << drawn_balls
         << " balls correctly is 1/" << total_combinations << endl;

    return 0;  // Return 0 to indicate successful termination
}

