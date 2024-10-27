//
//  safe_cin.h
//  options_pricing
//
//  Created by Akul Chordia on 10/27/24.
//
#include <ctime>

float safe_cin_float(const std::string& prompt = "") {
    float number;
    while (true) {
        std::cout << prompt;
        std::cin >> number;

        if (std::cin.fail() || std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a floating-point number.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (number == 69.0f) {
                exit(69);
            }
            return number;
        }
    }
}

float date_in_years(const std::string& prompt = "") {
    float number;
    float dd, mm, yyyy;
    char parser;
    std::cout << prompt;
    std::cin >> dd >> parser >> mm >> parser >> yyyy;
    time_t now = time(0);
    tm int_now = *localtime(&now);
    yyyy = yyyy - int_now.tm_year - 1900;
    mm = mm - int_now.tm_mon - 1;
    if (mm < 0){
        yyyy--;
        mm += 12;
    }
    dd = dd - int_now.tm_mday;
    if (dd < 0){
        mm--;
        dd += 30.5f;
    }
    number = yyyy + (mm/12.0f) + (dd/365.25f);
    return number;
}

