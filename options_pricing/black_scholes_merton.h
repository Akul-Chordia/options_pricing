//
//  black_scholes.h
//  options_pricing
//
//  Created by Akul Chordia on 10/26/24.
//


void d1_(float spot_price, float strike_price, float time_to_expiration, float risk_free_rate, float volatility, float dividend_yield, double* d1){
    *d1 = (log(spot_price/strike_price) + (risk_free_rate - dividend_yield + (volatility*volatility/2))*time_to_expiration)/(volatility*sqrt(time_to_expiration));
}

void d2_(float d1, float time_to_expiration, float volatility, double* d2){
    *d2 = d1 - (volatility*sqrt(time_to_expiration));
}

// Abramowitz and Stegun’s approximation
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

double ncdf(double d) {
    return 0.5 * erfc(-d / std::sqrt(2));
}

void black_scholes(float spot_price, float strike_price, float time_to_expiration, float risk_free_rate, float volatility, float dividend_yield, float* call_price, float* put_price){
    double d1;
    double d2;
    
    d1_(spot_price, strike_price, time_to_expiration, risk_free_rate, volatility, dividend_yield, &d1);
    d2_(d1, time_to_expiration, volatility, &d2);
    
    *call_price = (spot_price*ncdf(d1)*exp(-dividend_yield*time_to_expiration)) - (ncdf(d2)*strike_price*exp(-risk_free_rate*time_to_expiration));
    *put_price = (ncdf(-d2)*strike_price*exp(-risk_free_rate*time_to_expiration)) - (spot_price*ncdf(-d1)*exp(-dividend_yield*time_to_expiration));
}

void heatmap(float spot_price, float strike_price, float time_to_expiration, float risk_free_rate, float volatility, float dividend_yield){
    float temp_spot_price, temp_volatility, call_price, put_price;
    std::cout << "\nCall Option Prices:\n";
    std::vector<float> put_prices;
    put_prices.reserve(11 * 11);
    
    std::cout << std::setw(12) << "Spot Price" << " | ";
    std::cout << std::fixed << std::setprecision(2);
    for (int j = 80; j <= 120; j += 4) {
        std::cout << std::setw(8) << spot_price * (j * 0.01) << "   ";
    }
    std::cout << std::endl << std::string(140, '-');
    std::cout << std::endl << std::setw(12) << "Volatility" << " | " << std::endl;

    for (int i = -20; i <= 20; i += 4) {
        temp_volatility = volatility + (i * 0.01);
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::setw(12) << temp_volatility << " | ";
        std::cout << std::fixed << std::setprecision(4);
        for (int j = 80; j <= 120; j += 4) {
            temp_spot_price = spot_price * (j * 0.01);
            black_scholes(temp_spot_price, strike_price, time_to_expiration, risk_free_rate, temp_volatility, dividend_yield, &call_price, &put_price);
            put_prices.push_back(put_price);
            std::cout << std::setw(10) << call_price << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\nPut Option Prices:\n";
    
    std::cout << std::setw(12) << "Spot Price" << " | ";
    std::cout << std::fixed << std::setprecision(2);
    for (int j = 80; j <= 120; j += 4) {
        std::cout << std::setw(8) << spot_price * (j * 0.01) << "   ";
    }
    std::cout << std::endl << std::string(140, '-');
    std::cout << std::endl << std::setw(12) << "Volatility" << " | " << std::endl;
    
    int index = 0;

    for (int i = -20; i <= 20; i += 4) {
        temp_volatility = volatility + (i * 0.01);
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::setw(12) << temp_volatility << " | ";
        std::cout << std::fixed << std::setprecision(4);
        for (int j = 80; j <= 120; j += 4) {
            std::cout << std::setw(10) << put_prices[index++] << " ";
        }
        std::cout << std::endl;
    }
}

