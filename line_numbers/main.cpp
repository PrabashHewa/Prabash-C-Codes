#include <iostream>
#include <fstream>

using namespace std;
int main() {

    string input_file = "" ;
    cout <<"Input file: ";
    cin >> input_file ;

    string output_file = "" ;
    cout <<"Output file: ";
    cin >> output_file ;


    ifstream input_file_obj(input_file);

    if(not input_file_obj){

        cout<< "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;

    }

    ofstream output_file_obj (output_file);

    string line= "";
    int i=1 ;

    while (getline(input_file_obj,line)){

        output_file_obj << i << " " << line << endl;
        i++;
    }

    input_file_obj.close();
    output_file_obj.close();


    return 0;

}
