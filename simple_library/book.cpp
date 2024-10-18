#include "book.hh"
#include <iostream>


const int LOAN_PERIOD =28;

Book::Book(const std::string& author,
           const std::string& title):

    author_(author), title_(title), is_loaned_(false)
{


}

Book::~Book()
{

}

void Book::loan(const Date &loan_date)
{
    if(is_loaned_){

        std::cout <<"Already loaned: cannot be loaned" << std::endl;
        return;
    }

    is_loaned_ = true;
    loan_date_ = loan_date;
    due_date_= loan_date;
    due_date_.advance(LOAN_PERIOD);

}

void Book::print()
{
    std::cout<<author_<< " : " << title_<< std::endl;
    if (is_loaned_){
        std::cout<<"- loaned: ";
        loan_date_.print();

        std::cout<<"- to be returned: ";
        due_date_.print();
    }
    else{

        std::cout << "- available" << std::endl;

    }

}

void Book::renew()
{
    if (is_loaned_){
        due_date_.advance(LOAN_PERIOD);
        return;
    }

    std::cout <<"Not loaned: cannot be renewed" << std::endl;
}

void Book::give_back()
{
    if (is_loaned_) {
        is_loaned_ = false;
        std::cout << "Book returned successfully" << std::endl;
    } else {
        std::cout << "Book is not loaned, cannot be returned" << std::endl;
    }

}
