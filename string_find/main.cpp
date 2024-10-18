#include <iostream>
#include <string>

using namespace std;

int main()
{

    std::string longer,shorter;

    std::cout << "Enter a (longer) string: " ;
    std :: getline(std::cin, longer) ;

    std::cout << "Enter a (shorter) string to be found: ";
    std::getline (std::cin, shorter);

    bool found = false;
    bool first = true;


        for (size_t i = 0; i <= longer.length() - shorter.length(); i++) {

            if (longer.substr(i, shorter.length()) == shorter) {
                if (first) {
                    std::cout << "Found at " << i;
                    first = false;
                } else {
                    std::cout << ", " << i;
                }
                found = true;
            }
        }

        if (!found) {
              std::cout << "Not found";
          }

          std::cout << std::endl;
          return 0;

}
