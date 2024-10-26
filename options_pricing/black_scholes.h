//
//  black_scholes.h
//  options_pricing
//
//  Created by Akul Chordia on 10/26/24.
//

using namespace std;


void d1_(float spot_price, float strike_price, float time_to_expiration, float risk_free_rate, float volatility, double* d1){
    *d1 = (log(spot_price/strike_price) + (risk_free_rate + (volatility*volatility/2))*time_to_expiration)/(volatility*sqrt(time_to_expiration));
}

void d2_(float d1, float time_to_expiration, float volatility, double* d2){
    *d2 = d1 - (volatility*sqrt(time_to_expiration));
}

double ncdf(double d) {
    const double a[] = {0.31938153, -0.356563782, 1.781477937, -1.821255978, 1.330274429};
    
    double L = abs(d);
    double K = 1.0 / (1.0 + 0.2316419 * L);
    
    double K2 = K*K;
    double K3 = K2 * K;
    double K4 = K3 * K;
    double K5 = K4 * K;

    double result = 1.0 - (1.0 / sqrt(2 * M_PI)) * exp(-L * L / 2.0) *
                        (a[0] * K + a[1] * K2 + a[2] * K3 + a[3] * K4 + a[4] * K5);

    return (d < 0) ? 1.0 - result : result;
}


void black_scholes(float spot_price, float strike_price, float time_to_expiration, float risk_free_rate, float volatility, float* call_price, float* put_price){
    double d1;
    double d2;
    
    d1_(spot_price, strike_price, time_to_expiration, risk_free_rate, volatility, &d1);
    d2_(d1, time_to_expiration, volatility, &d2);
    
    *call_price = (spot_price*ncdf(d1)) - (ncdf(d2)*strike_price*exp(-risk_free_rate*time_to_expiration));
    *put_price = (ncdf(-d2)*strike_price*exp(-risk_free_rate*time_to_expiration)) - (spot_price*ncdf(-d1));
}
