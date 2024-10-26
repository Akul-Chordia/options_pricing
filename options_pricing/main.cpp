//
//  main.cpp
//  options_pricing
//
//  Created by Akul Chordia on 10/26/24.
//

#include <iostream>
#include <iomanip>
#include "black_scholes.h"

using namespace std;

int main(int argc, const char * argv[]) {
    float spot_price;
    float strike_price;
    float time_to_expiration;
    float risk_free_rate;
    float volatility;
    float call_price;
    float put_price;
    float temp_volatility;
    float temp_spot_price;
    while (true){
        cout << "Enter the spot price (current price of the asset): ";
        cin >> spot_price;
        cout << "Enter the strike price (price at which the option can be exercised): ";
        cin >> strike_price;
        cout << "Enter the time to expiration (in years, e.g., 0.5 for six months): ";
        cin >> time_to_expiration;
        cout << "Enter the risk-free interest rate (in decimal, e.g., 0.05 for 5%): ";
        cin >> risk_free_rate;
        cout << "Enter the volatility (standard deviation of the asset's returns, e.g., 0.2 for 20%): ";
        cin >> volatility;
    
        black_scholes(spot_price, strike_price, time_to_expiration, risk_free_rate, volatility, &call_price, &put_price);
        cout << "Call : $" << call_price << endl;
        cout << "Put : $" << put_price << endl;
        
        heatmap(spot_price, strike_price, time_to_expiration, risk_free_rate, volatility);
    }
    return 0;
}
