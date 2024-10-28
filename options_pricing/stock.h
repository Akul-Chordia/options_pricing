//  stock.h
//  options_pricing
//  Created by Akul Chordia on 10/28/24.

#pragma once

struct stock {
    std::string ticker;
    
    float spot_price;
    float strike_price;
    float time_to_expiration;
    float risk_free_rate;
    float volatility;
    float dividend_yield;
};

struct greeks {
    std::string ticker;

    float delta_call;
    float gamma_call;
    float theta_call;
    float vega_call;
    float rho_call;

    float delta_put;
    float gamma_put;
    float theta_put;
    float vega_put;
    float rho_put;
};

std::map<std::string, stock> stockMap;
std::map<std::string, greeks> greeksMap;

void set_stock(){
    stock stock;
    
    stock.ticker = ticker_input();
    stock.spot_price = safe_cin_float("Enter the spot price (current price of the asset): ");
    stock.strike_price = safe_cin_float("Enter the strike price (price at which the option can be exercised): ");
    stock.time_to_expiration = date_in_years("Enter the date of expiration (DD/MM/YYYY): ");
    stock.risk_free_rate = safe_cin_float("Enter the risk-free interest rate (in decimal, e.g., 0.05 for 5%): ");
    stock.volatility = safe_cin_float("Enter the volatility (standard deviation of the asset's returns, e.g., 0.2 for 20%): ");
    stock.dividend_yield = safe_cin_float("Enter the annualized dividend yield (in decimal, e.g., 0.05 for 5%): ");
    
    stockMap[stock.ticker] = stock;
}


