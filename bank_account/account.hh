#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);
    void set_credit_limit(double limit);
    void save_money(double amount);
    bool take_money(double amount);
    bool transfer_to(Account& target_account, double amount);
    void print() const;

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();
    std::string owner_;
    std::string iban_;
    double balance_;
    bool has_credit_;
    double credit_limit_;

    // Used for generating IBAN.
    // Static means this value is shared among all Account objects.
    static int running_number_;

};

#endif // ACCOUNT_HH
