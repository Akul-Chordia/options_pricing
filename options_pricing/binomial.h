//  binomial.h
//  options_pricing
//  Created by Akul Chordia on 11/1/24.

#pragma once

double delta_t;
int steps;

void delta_T(float time_to_expiration){
    if (time_to_expiration >= 2){
        steps = 12;
        delta_t = time_to_expiration/steps;
    } else if (time_to_expiration >= 0.5){
        steps = 52;
        delta_t = time_to_expiration/steps;
    } else {
        steps = 252;
        delta_t = time_to_expiration/steps;
    }
}

void binomial_tree(stock s, double up_factor, double down_factor, double risk_neutral_probability, float* call_price, float* put_price) {
    // Arrays to store option prices at each node
    double* optionPricesCall = new double[steps + 1];
    double* optionPricesPut = new double[steps + 1];

    // Calculate option values at maturity (last nodes)
    for (int i = 0; i <= steps; ++i) {
        double stockPriceAtMaturity = s.spot_price * pow(up_factor, steps - i) * pow(down_factor, i);
        optionPricesCall[i] = fmax(0.0, stockPriceAtMaturity - s.strike_price);
        optionPricesPut[i] = fmax(0.0, s.strike_price - stockPriceAtMaturity);
    }

    // Step back through the tree
    for (int j = steps - 1; j >= 0; --j) {
        for (int i = 0; i <= j; ++i) {
            optionPricesCall[i] = exp(-s.risk_free_rate * delta_t) * (risk_neutral_probability * optionPricesCall[i] + (1 - risk_neutral_probability) * optionPricesCall[i + 1]);
            optionPricesPut[i] = exp(-s.risk_free_rate * delta_t) * (risk_neutral_probability * optionPricesPut[i] + (1 - risk_neutral_probability) * optionPricesPut[i + 1]);
        }
    }

    *call_price = optionPricesCall[0];
    *put_price = optionPricesPut[0];
    
    delete[] optionPricesPut;
    delete[] optionPricesCall;
}



void cox_ross_rubinstein(stock s, float* call_price, float* put_price){
    delta_T(s.time_to_expiration);
    double up_factor = exp(s.volatility*sqrt(delta_t));
    double down_factor = 1/up_factor;
    double risk_neutral_probability = (exp(s.risk_free_rate*delta_t) - down_factor)/(up_factor - down_factor);
    binomial_tree(s, up_factor, down_factor, risk_neutral_probability, call_price, put_price);
}

void jarrow_rudd(stock s, float* call_price, float* put_price){
    delta_T(s.time_to_expiration);
    double up_factor = exp(s.volatility*sqrt(delta_t));
    double down_factor = 1/up_factor;
    double risk_neutral_probability = 0.5;
    std::cout << up_factor << down_factor;
    binomial_tree(s, up_factor, down_factor, risk_neutral_probability, call_price, put_price);
}

void leisen_reimer(stock s, float* call_price, float* put_price){
    double moneyness = (s.spot_price == s.strike_price) ? 0.0 : -0.5 + 0.5 * (1 + (log(s.spot_price / s.strike_price) / (s.volatility * sqrt(s.time_to_expiration)))); //replace logic later
    delta_T(s.time_to_expiration);
    double up_factor = exp(s.volatility*sqrt(delta_t));
    double down_factor = 1/up_factor;
    double risk_neutral_probability = ncdf((moneyness*sqrt(delta_t) + log(s.spot_price/s.strike_price))/(s.volatility*sqrt(s.time_to_expiration))); //replace new_var
    binomial_tree(s, up_factor, down_factor, risk_neutral_probability, call_price, put_price);
}

void binomial_option_pricing(){
    float call_price, put_price;
    
    stock stock = stockMap[ticker_input()];
sorry_for_using_this:
    int choice = safecin("1 : cox_ross_rubinstein\n2 : jarrow_rudd\n3 : leisen_reimer\n");
    switch (choice) {
        case 1:
            cox_ross_rubinstein(stock, &call_price, &put_price);
            break;
        case 2:
            jarrow_rudd(stock, &call_price, &put_price);
            break;
        case 3:
            leisen_reimer(stock, &call_price, &put_price);
            break;
        default:
            std::cout << "Enter a valid options.\n";
            goto sorry_for_using_this;
            break;
    }
    
    std::cout << "Call : $" << call_price << std::endl;
    std::cout << "Put : $" << put_price << std::endl;
}
