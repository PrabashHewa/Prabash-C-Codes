#include "player.hh"
#include <iostream>

Player::Player(string name):
    name_(name), points_(0)
{

}

Player::~Player()
{

}

string Player::get_name()
{
    return name_;

}

void Player::add_points(int points)
{
    points_ += points;

    if (points_ > 50){
        points_ =25;

        std::cout << name_ << "getscpenalty points!" << std::endl;
    }

}

int Player::get_points()
{
    return points_;

}

bool Player::has_won()
{
    return points_ == 50;

}
