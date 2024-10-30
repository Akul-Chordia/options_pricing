//  inputs.h
//  options_pricing
//  Created by Akul Chordia on 10/27/24.
#pragma once

int safecin(const std::string& prompt = "") {
    int number;
    while (true) {
        std::cout << prompt;
        std::cin >> number;

        if (std::cin.fail() || std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (number == 69){
                exit(69);
            }
            return number;
        }
    }
}

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

tm safe_cin_date(const std::string& prompt = "") {
    int dd, mm, yyyy;
    char parser;
    bool valid;

    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        
        std::istringstream iss(input);
        if (iss >> dd >> parser >> mm >> parser >> yyyy && dd >= 1 && dd <= 31 && mm >= 1 && mm <= 12 && yyyy >= 1900 && yyyy <= 3000) {
            if (mm == 2){
                if ((yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0)){
                    valid = (dd <= 29);
                } else {
                    valid = (dd <= 28);
                }
            } else if (mm == 4 || mm == 6 || mm == 9 || mm == 11) {
                valid = (dd <= 30);
            } else {
                valid = true;
            }

            if (valid) {
                tm date = {};
                date.tm_mday = dd;
                date.tm_mon = mm - 1;
                date.tm_year = yyyy - 1900;
                return date;
            }
        }
        std::cout << "Invalid date format or out of range. Please enter a date in dd/mm/yyyy format.\n";
    }
}

float date_in_years(const std::string& prompt = "") {
    float number;
    float dd, mm, yyyy;
    tm date;
    
    date = safe_cin_date(prompt);
    
    dd = date.tm_mday;
    mm = date.tm_mon;
    yyyy = date.tm_year;
    
    time_t now = time(0);
    tm date_now = *localtime(&now);
    
    yyyy = yyyy - date_now.tm_year;
    mm = mm - date_now.tm_mon;
    dd = dd - date_now.tm_mday;
    
    if (mm < 0){
        yyyy--;
        mm += 12;
    }
    
    if (dd < 0){
        mm--;
        dd += 30.5f;
    }
    number = yyyy + (mm/12.0f) + (dd/365.25f);
    return number;
}

std::string ticker_input(){
    std::string ticker;
    std::cout << "Enter stock ticker: ";
    std::cin >> ticker;
    return ticker;
}


