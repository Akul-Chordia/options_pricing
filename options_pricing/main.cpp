//  main.cpp
//  options_pricing
//  Created by Akul Chordia on 10/26/24.

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include "inputs.h"
#include "stock.h"
#include "black_scholes_merton.h"



int main(int argc, const char * argv[]) {
    int choice;
    
    while (true){
        
        choice = safecin("1 : input stock details\n2 : options pricing\n3 : greeks\n4 : heatmap\n");
        switch (choice) {
            case 1:
                set_stock();
                break;
            case 2:
                get_option_pricing();
                break;
            case 3:
                get_greeks();
                break;
            case 4:
                get_heatmap();
                break;
            default:
                break;
        }
    }
    return 0;
}
