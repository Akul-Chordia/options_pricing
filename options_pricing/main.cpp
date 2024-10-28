//
//  main.cpp
//  options_pricing
//
//  Created by Akul Chordia on 10/26/24.
//

#include <iostream>
#include <iomanip>
#include "black_scholes_merton.h"
#include "inputs.h"


int main(int argc, const char * argv[]) {
    float spot_price, strike_price, time_to_expiration, risk_free_rate, volatility, dividend_yield;
    float call_price, put_price;
    while (true){
        spot_price = safe_cin_float("Enter the spot price (current price of the asset): ");
        strike_price = safe_cin_float("Enter the strike price (price at which the option can be exercised): ");
        time_to_expiration = date_in_years("Enter the date of expiration (DD/MM/YYYY): ");
        risk_free_rate = safe_cin_float("Enter the risk-free interest rate (in decimal, e.g., 0.05 for 5%): ");
        volatility = safe_cin_float("Enter the volatility (standard deviation of the asset's returns, e.g., 0.2 for 20%): ");
        dividend_yield = safe_cin_float("Enter the annualized dividend yield (in decimal, e.g., 0.05 for 5%): ");
    
        black_scholes_merton(spot_price, strike_price, time_to_expiration, risk_free_rate, volatility, dividend_yield, &call_price, &put_price);
        std::cout << "Call : $" << call_price << std::endl;
        std::cout << "Put : $" << put_price << std::endl;
        
        heatmap(spot_price, strike_price, time_to_expiration, risk_free_rate, volatility, dividend_yield);
    }
    return 0;
}
