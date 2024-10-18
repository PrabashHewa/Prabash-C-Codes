#include <iostream>
#include <string>



using namespace std;

bool check_islower(const string& s)
{
    for (unsigned int i = 0 ; i < s.size() ; ++i)
    {
       if( not islower(s.at(i)) )
       {
           return false;
       }
    }

    return true;
}

bool check_alp( const string& key){
    for ( char c ='a' ; c < 'z' ; ++c)
    {
        if (key.find(c) == string::npos)
        {
            return false;

        }
    }

    return true;
}

string encrypt(const string& msg, const string& key)
{
    string encrypt_msg = "";

    for( unsigned int i = 0; i < msg.size() ; ++i)
    {
        char character = msg.at(i);
        unsigned int ascii_value = character;
        unsigned int position = ascii_value - static_cast<unsigned int>('a');
        char encrypted_char = key.at(position);
        encrypt_msg += encrypted_char;
    }

    return encrypt_msg;
}


int main()
{
    cout << "Enter the encryption key: " ;
    string key ="";
    getline(cin,key);

    if ( key.size() != 26)
    {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;

    }

    if ( not check_islower(key) )
    {
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    }

    if ( not check_alp(key))
    {
        cout <<"Error! The encryption key must contain all alphabets a-z." << endl;
        return EXIT_FAILURE;
    }

    cout << "Enter the text to be encrypted: ";
    string text="";
    getline(cin, text);

    cout <<"Encrypted text: " << encrypt(text, key) << endl;

    return 0;
}
