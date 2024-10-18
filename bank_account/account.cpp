#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit)
        : owner_(owner), balance_(0.0), has_credit_(has_credit), credit_limit_(0.0)
{
    generate_iban();
}

void Account::set_credit_limit(double limit)
{
    if (!has_credit_) {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
        return;
    }
    credit_limit_ = limit;
}

void Account::save_money(double amount)
{
        balance_ += amount;
}

bool Account::take_money(double amount)
{
    if (!has_credit_) {
        if (balance_ >= amount) {
            balance_ -= amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
            return true;
        } else {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            return false;
        }
    } else {
        if (balance_ - amount >= -credit_limit_) {
            balance_ -= amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
            return true;
        } else {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            return false;
        }
    }

}

bool Account::transfer_to(Account &target_account, double amount)
{
    if (this->take_money(amount)) {
        target_account.save_money(amount);
        return true;
    } else {
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        return false;
    }

}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << std::endl;

}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
