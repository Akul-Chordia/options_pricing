//  main.cpp
//  options_pricing
//  Created by Akul Chordia on 10/26/24.

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <sstream>
#include <ctime>
#include "inputs.h"
#include "stock.h"
#include "black_scholes_merton.h"
#include "binomial.h"



int main(int argc, const char * argv[]) {
    int choice;
    
    while (true){
        
        choice = safecin("1 : input stock details\n2 : options pricing\n3 : greeks\n4 : heatmap\n5: binomial option pricing\n");
        switch (choice) {
            case 1:
                set_stock();
                break;
            case 2:
                bsm_option_pricing();
                break;
            case 3:
                get_greeks();
                break;
            case 4:
                get_heatmap();
                break;
            case 5:
                binomial_option_pricing();
                break;
            default:
                break;
        }
    }
    return 0;
}
