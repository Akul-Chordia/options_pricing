# Options Pricing

Welcome to the Options Pricing repository! This project is dedicated to implementing and analyzing different models for pricing European options. It includes well-known pricing methods such as the Black-Scholes-Merton model and binomial tree models like Cox-Ross-Rubinstein (CRR), Jarrow-Rudd, and Leisen-Reimer.

## Overview
This repository focuses on:
- Using the **Black-Scholes-Merton model** for pricing European call and put options.
- Implementing various **binomial options pricing models** for comparative analysis.
- Calculating **Greeks** (Delta, Gamma, Theta, Vega, and Rho) to measure the sensitivity of option prices to various factors.
   
---

## Screenshots
- **Adding stock info:** <br>
        <img width="648" alt="image" src="https://github.com/user-attachments/assets/ee2b7733-0367-436f-9cd0-aa399f9c96ac" />
- **Black-Scholes Calculation:** <br>
        <img width="218" alt="image" src="https://github.com/user-attachments/assets/21dc1994-45f9-45af-adc4-49aced7fcb06" />
- **Greeks:** <br>
        <img width="329" alt="image" src="https://github.com/user-attachments/assets/c3111674-0203-46c7-a021-69c70a27af0c" />
- **Price heatmap:** <br>
        <img width="969" alt="image" src="https://github.com/user-attachments/assets/6ddb81d7-eeb3-4231-a936-9942addfa9ba" />

---

## Features
- **Black-Scholes-Merton Model:**
  - Pricing of European call and put options.
  - Closed-form solution for quick calculations.
  
- **Cox-Ross-Rubinstein Model (CRR):**
  - Uses a binomial tree approach with dynamic step size based on the time to expiration.
  - Up and down factors are determined based on volatility and time step.
  - Calculates risk-neutral probabilities for accurate option valuation.

- **Jarrow-Rudd Model:**
  - A simplified binomial model with equal up and down probabilities (0.5).
  - Provides a faster but less complex approximation of option prices.
  
- **Leisen-Reimer Model:**
  - Improves binomial tree convergence by incorporating a refined probability calculation based on option moneyness.
  - Achieves higher accuracy with fewer steps compared to CRR and Jarrow-Rudd.

---

## Requirements
- **Language:** C++
- **Development Environment:** Xcode (macOS) or any compatible C++ IDE.

Ensure that you have a C++ compiler installed (e.g., GCC, Clang) and Xcode or an equivalent IDE set up to execute the code files.

---

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/Akul-Chordia/options_pricing.git
   ```
2. Navigate to the project directory:
   ```bash
   cd options_pricing
   ```
3. Open the project in your IDE (e.g., Xcode) and build the project.

---

## Usage
1. Run the program by executing the main file in your IDE.
2. Input parameters such as:
   - Option type (Call/Put)
   - Strike price
   - Underlying price
   - Time to maturity
   - Volatility
   - Risk-free rate
3. Select options:
   - **1: Black-Scholes pricing**
   - **2: Greeks**
   - **3: Heatmap**
   - **4: Binomial pricing**
       - *1: Cox-Ross-Rubinstein*
       - *2: Jarrow-Rudd*
       - *3: Leisen-Reimer*

---

## Future Additions
We aim to expand this project with the following features:
- [ ] Implement the **Heston model** for stochastic volatility.
- [ ] Support for **American options** pricing.
- [ ] Add a graphical user interface (GUI) for easier parameter inputs and visualization.
- [ ] Include more detailed error handling and input validation.

---

## Contributing
Contributions are welcome! If you'd like to add features or improve existing ones, feel free to fork this repository and submit a pull request.

1. Fork the repository.
2. Create a new branch for your feature.
3. Commit your changes with descriptive messages.
4. Submit a pull request.

---

## License
This project is licensed under the MIT License. See the LICENSE file for more details.
