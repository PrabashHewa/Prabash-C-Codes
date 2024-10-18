#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"
#include <string>

class Book
{
public:
    Book(const std::string& author,
         const std::string& title);

    ~Book();

    void loan(const Date& loan_date);
    void print();
    void renew();
    void give_back();

private:
    std::string author_;
    std::string title_;
    bool is_loaned_;
    Date loan_date_;
    Date due_date_;

};

#endif // BOOK_HH
