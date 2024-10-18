#include <iostream>

using namespace std;

int main()
{
    double tempCelsius, tempFahrenheit;

    cout << "Enter a temperature: ";
    cin >> tempCelsius;

    tempFahrenheit = (tempCelsius * 1.8) + 32;
    cout << tempCelsius << " degrees Celsius is " << tempFahrenheit << " degrees Fahrenheit" << endl;

    tempFahrenheit = tempCelsius;
    tempCelsius = (tempFahrenheit - 32) / 1.8;
    cout << tempFahrenheit << " degrees Fahrenheit is " << tempCelsius << " degrees Celsius" << endl;

    return 0;
}
