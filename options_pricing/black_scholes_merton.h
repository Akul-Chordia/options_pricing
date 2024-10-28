//  black_scholes_merton.h
//  options_pricing
//  Created by Akul Chordia on 10/26/24.
#pragma once


void d1_(stock s, double* d1){
    *d1 = (log(s.spot_price/s.strike_price) + (s.risk_free_rate - s.dividend_yield + (s.volatility*s.volatility/2))*s.time_to_expiration)/(s.volatility*sqrt(s.time_to_expiration));
}

void d2_(float d1, float time_to_expiration, float volatility, double* d2){
    *d2 = d1 - (volatility*sqrt(time_to_expiration));
}

double ncdf(double d) {
    return 0.5 * erfc(-d / std::sqrt(2));
}

// Abramowitz and Stegun’s approximation of ncdf
    //double ncdf(double d) {
    //    const double a[] = {0.31938153, -0.356563782, 1.781477937, -1.821255978, 1.330274429};
    //
    //    double L = abs(d);
    //    double K = 1.0 / (1.0 + 0.2316419 * L);
    //
    //    double K2 = K*K;
    //    double K3 = K2 * K;
    //    double K4 = K3 * K;
    //    double K5 = K4 * K;
    //
    //
    //    double result = 1.0 - (1.0 / sqrt(2 * M_PI)) * exp(-L * L / 2.0) *
    //                        (a[0] * K + a[1] * K2 + a[2] * K3 + a[3] * K4 + a[4] * K5);
    //
    //    return (d < 0) ? 1.0 - result : result;
    //}

double pdf(double d) {
    return (1.0 / std::sqrt(2 * M_PI)) * std::exp(-0.5 * d * d);
}

void black_scholes_merton(stock s, float* call_price, float* put_price){
    double d1;
    double d2;
    
    d1_(s, &d1);
    d2_(d1, s.time_to_expiration, s.volatility, &d2);
    
    
    *call_price = (s.spot_price*ncdf(d1)*exp(-s.dividend_yield*s.time_to_expiration)) - (ncdf(d2)*s.strike_price*exp(-s.risk_free_rate*s.time_to_expiration));
    *put_price = (ncdf(-d2)*s.strike_price*exp(-s.risk_free_rate*s.time_to_expiration)) - (s.spot_price*ncdf(-d1)*exp(-s.dividend_yield*s.time_to_expiration));
}


void heatmap(stock s){
    float temp_spot_price, temp_volatility, call_price, put_price;
    std::cout << "\nCall Option Prices:\n";
    std::vector<float> put_prices;
    put_prices.reserve(11 * 11);
    
    std::cout << std::setw(12) << "Spot Price" << " | ";
    std::cout << std::fixed << std::setprecision(2);
    for (int j = 80; j <= 120; j += 4) {
        std::cout << std::setw(8) << s.spot_price * (j * 0.01) << "   ";
    }
    std::cout << std::endl << std::string(140, '-');
    std::cout << std::endl << std::setw(12) << "Volatility" << " | " << std::endl;

    for (int i = -20; i <= 20; i += 4) {
        temp_volatility = s.volatility + (i * 0.01);
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::setw(12) << temp_volatility << " | ";
        std::cout << std::fixed << std::setprecision(4);
        for (int j = 80; j <= 120; j += 4) {
            temp_spot_price = s.spot_price * (j * 0.01);
            black_scholes_merton(s, &call_price, &put_price);
            put_prices.push_back(put_price);
            std::cout << std::setw(10) << call_price << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\nPut Option Prices:\n";
    
    std::cout << std::setw(12) << "Spot Price" << " | ";
    std::cout << std::fixed << std::setprecision(2);
    for (int j = 80; j <= 120; j += 4) {
        std::cout << std::setw(8) << s.spot_price * (j * 0.01) << "   ";
    }
    std::cout << std::endl << std::string(140, '-');
    std::cout << std::endl << std::setw(12) << "Volatility" << " | " << std::endl;
    
    int index = 0;

    for (int i = -20; i <= 20; i += 4) {
        temp_volatility = s.volatility + (i * 0.01);
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::setw(12) << temp_volatility << " | ";
        std::cout << std::fixed << std::setprecision(4);
        for (int j = 80; j <= 120; j += 4) {
            std::cout << std::setw(10) << put_prices[index++] << " ";
        }
        std::cout << std::endl;
    }
}

void get_option_pricing(){
    float call_price, put_price;
    
    stock stock = stockMap[ticker_input()];
    black_scholes_merton(stock, &call_price, &put_price);
    
    std::cout << "Call : $" << call_price << std::endl;
    std::cout << "Put : $" << put_price << std::endl;
}


void get_heatmap(){
    stock stock = stockMap[ticker_input()];
    heatmap(stock);
}

void display_greeks(const greeks& g) {
    std::cout << std::setw(15) << "Greek" << std::setw(15) << "Call" << std::setw(15) << "Put" << std::endl;
    
    std::cout << std::string(45, '-') << std::endl;
    
    std::cout << std::setw(15) << "Delta : " << std::setw(15) << g.delta_call << std::setw(15) << g.delta_put << std::endl;
    std::cout << std::setw(15) << "Gamma : " << std::setw(15) << g.gamma_call << std::setw(15) << g.gamma_put << std::endl;
    std::cout << std::setw(15) << "Theta : " << std::setw(15) << g.theta_call << std::setw(15) << g.theta_put << std::endl;
    std::cout << std::setw(15) << "Vega : " << std::setw(15) << g.vega_call << std::setw(15) << g.vega_put << std::endl;
    std::cout << std::setw(15) << "Rho : " << std::setw(15) << g.rho_call << std::setw(15) << g.rho_put << std::endl;
}

void get_greeks(){
    std::string ticker = ticker_input();
    if (greeksMap.find(ticker) != greeksMap.end()) {
        greeks g = greeksMap[ticker];
        display_greeks(g);
        
    } else {
        if (stockMap.find(ticker) != stockMap.end()) {
            stock s = stockMap[ticker];
            greeks g;
            
            double d1, d2;
            d1_(s, &d1);
            d2_(d1, s.time_to_expiration, s.volatility, &d2);
            
            g.delta_call = exp(-s.dividend_yield*s.time_to_expiration)*ncdf(d1);
            g.delta_put = -exp(-s.dividend_yield*s.time_to_expiration)*ncdf(-d1);
            
            g.gamma_call = (exp(-s.dividend_yield*s.time_to_expiration)*pdf(d1))/s.spot_price*s.volatility*sqrt(s.time_to_expiration);
            g.gamma_put = g.gamma_call;
            
            g.theta_call = (-((s.spot_price * exp(-s.dividend_yield * s.time_to_expiration) * pdf(d1) * s.volatility) / (2 * sqrt(s.time_to_expiration))) - (s.risk_free_rate * s.strike_price * exp(-s.risk_free_rate * s.time_to_expiration) *ncdf(d2)) + (s.dividend_yield*s.spot_price*exp(-s.dividend_yield*s.time_to_expiration)*ncdf(d1)))/365;
            g.theta_put = (-((s.spot_price * exp(-s.dividend_yield * s.time_to_expiration) * pdf(d1) * s.volatility) / (2 * sqrt(s.time_to_expiration))) + (s.risk_free_rate * s.strike_price * exp(-s.risk_free_rate * s.time_to_expiration) *ncdf(-d2)) - (s.dividend_yield*s.spot_price*exp(-s.dividend_yield*s.time_to_expiration)*ncdf(-d1)))/365;
            
            g.vega_call = (s.spot_price*exp(-s.dividend_yield*s.time_to_expiration)*sqrt(s.time_to_expiration)*pdf(d1))/100;
            g.vega_put = g.vega_call;
            
            g.rho_call = (s.spot_price*s.time_to_expiration*exp(-s.risk_free_rate*s.time_to_expiration)*ncdf(d2))/100;
            g.rho_put = -(s.spot_price*s.time_to_expiration*exp(-s.risk_free_rate*s.time_to_expiration)*ncdf(-d2))/100;
            
            greeksMap[ticker] = g;
            display_greeks(g);

        } else {
            std::cout << "Error: Ticker not found." << std::endl;
        }
    }
}
