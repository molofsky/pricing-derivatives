/*
* One-period binomial asset pricing model 
*
* S_0 - S_1(H) = uS_0
*  |
*     - S_1(T) = dS_0
*
*
* with d < 1 + r < u, i.e. no arbitrage exists between the stock and money market
*
* An example input for a European option with a fair strike price: 
* S(0) = 4, X_0 = 1.20, u = 2, d = 0.5, r = 0.25, K = 5
*
* @author Adrian Molofsky
* @version August 8, 2025
*
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double exercise_option(double S_1, double K) {
    return max(S_1 - K, 0.0); // (S_1 - K)^+
}

vector<double> one_period_binomial(double S_0, double u, double d) {
    return {u * S_0, d * S_0};
}

int main() {
    double S_0, X_0, delta_0, K, u, d, r, b;

    cout << "Stock price at time zero: ";
    cin >> S_0;

    cout << "Initial wealth: ";
    cin >> X_0;

    cout << "Number of shares: ";
    cin >> delta_0;

    cout << "Up factor: ";
    cin >> u;
    if (u <= 0) {
        cerr << "Error: up factor must be greater than zero" << endl;
    }

    cout << "Down factor: ";
    cin >> d;
    if (d <= 0) {
        cerr << "Error: down factor must be greater than zero" << endl;
    }

    cout << "Interest rate: ";
    cin >> r;
    if (!(d < 1 + r && 1 + r < u)) {
        cerr << "Error: assume no arbitrage between stock and money market, i.e. d < 1 + r < u" << endl;
    }

    cout << "Strike price: ";
    cin >> K;

    vector<double> S_1 = one_period_binomial(S_0, u, d);
    double option_H = exercise_option(S_1[0], K);
    double option_T = exercise_option(S_1[1], K);
    double portfolio_H = delta_0 * S_1[0] + (1 + r) * (X_0 - delta_0 * S_0);
    double portfolio_T = delta_0 * S_1[1] + (1 + r) * (X_0 - delta_0 * S_0);

    cout << "If heads, stock price: " << S_1[0] << ", value of option: " << option_H << ", value of portfolio: " << portfolio_H << endl;
    cout << "If tails, stock price: " << S_1[1] << ", value of option: " << option_T << ", value of portfolio: " << portfolio_T << endl;

    if (option_H == portfolio_H && option_T == portfolio_T) {
        cout << "Fair price of option at time zero" << endl;
    } else {
        cout << "Arbitrage price exists at time zero" << endl;
    }

    return 0;
}
