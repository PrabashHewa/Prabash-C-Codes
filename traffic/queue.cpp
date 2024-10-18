#include "queue.hh"
#include <iostream>

// Constructor: Initializes the cycle count and sets the light to red
Queue::Queue(unsigned int cycle)
    :  cycle_(cycle), is_green_(false),first_(nullptr)  , last_(nullptr){}

// Checks if the queue is empty
bool Queue::is_empty() const {
    return first_ == nullptr;
}

void Queue::enqueue(const std::string& reg) {
    if (is_green_) {
        // Print the message that the vehicle does not need to stop
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" << std::endl;
        return;
    }

    // Add the vehicle to the queue if the light is red
    auto new_vehicle = std::make_shared<Vehicle>();
    new_vehicle->reg_num = reg;
    new_vehicle->next = nullptr;

    if (is_empty()) {
        first_ = new_vehicle;
        last_ = new_vehicle;
    } else {
        last_->next = new_vehicle;
        last_ = new_vehicle;
    }
}

void Queue::switch_light() {
    is_green_ = !is_green_;

    if (is_green_) {
        if (is_empty()) {
            std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
        } else {
            std::cout << "GREEN: Vehicle(s) ";
            unsigned int count = 0;
            std::string reg;
            while (!is_empty() && count < cycle_) {
                if (dequeue(reg)) {
                    std::cout << reg << " ";
                    ++count;
                }
            }
            std::cout << "can go on" << std::endl;
        }
    } else {
        // When switching to red, print the state of the queue
        if (is_empty()) {
            std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
        } else {
            std::cout << "RED: Vehicle(s) ";
            auto current = first_;
            while (current != nullptr) {
                std::cout << current->reg_num << " ";
                current = current->next;
            }
            std::cout << "waiting in traffic lights" << std::endl;
        }
    }
}

// Resets the cycle, defining how many vehicles can pass on green
void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

// Prints the current state of the traffic light and vehicles in the queue
void Queue::print() {
    // Force the light to switch to red before printing
    if (is_green_) {
        is_green_ = false;  // Switch light to red
        std::cout << "RED: ";  // Indicate the light status
    } else {
        std::cout << "RED: ";  // Already red, just print the status
    }

    if (is_empty()) {
        std::cout << "No vehicles waiting in traffic lights" << std::endl;
    } else {
        std::cout << "Vehicle(s) ";
        auto current = first_;
        while (current != nullptr) {
            std::cout << current->reg_num << " ";
            current = current->next;
        }
        std::cout << "waiting in traffic lights" << std::endl;
    }
}

// Removes a vehicle from the front of the queue if the light is green
bool Queue::dequeue(std::string& reg) {
    if (is_empty()) {
        return false;
    }

    reg = first_->reg_num;
    first_ = first_->next;

    // If the queue becomes empty, reset the last pointer
    if (first_ == nullptr) {
        last_ = nullptr;
    }

    return true;
}

