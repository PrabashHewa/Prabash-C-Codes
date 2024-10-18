#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int product;


    cout << "Enter a positive number: ";
    cin >> product;


    if (product <= 0)
    {
        cout << "Only positive numbers accepted" << endl;
        return 0;
    }

    int factor1 = 1;
    int factor2 = product;

    for (int i = static_cast<int>(sqrt(product)); i > 0; --i)
    {
        if (product % i == 0)
        {
            factor1 = i;
            factor2 = product / i;
            break;
        }
    }

    cout << product << " = " << factor1 << " * " << factor2 << endl;

    return 0;
}
