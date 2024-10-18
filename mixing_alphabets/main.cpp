#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>


#include <iostream>
#include <string>
#include <algorithm>
#include <random>

int main() {

    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;

    std::string word;

    while (std::cin >> word) {
        if (word == "END") {
            return EXIT_SUCCESS;
        }

        if (word.length() > 3) {

            std::string middle = word.substr(1, word.length() - 2);

            std::shuffle(middle.begin(), middle.end(), generator);

            word = word.front() + middle + word.back();
        }

        std::cout << word << std::endl;
    }

    return EXIT_SUCCESS;
}


