//
//  safe_cin.h
//  options_pricing
//
//  Created by Akul Chordia on 10/27/24.
//

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
    int dd, mm, yyyy;
    char parser;
    while (true) {
        std::cout << prompt;
        std::cin >> dd >> parser >> mm >> parser >> yyyy;

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

