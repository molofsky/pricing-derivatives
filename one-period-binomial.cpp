/*
* One-period binomial asset pricing model 
*
* S_0 - S_1(H) = uS_0
*  |
*     - S_2(T) = dS_0
*
* with d < 1 + r < u
*
*
*
* @author Adrian Molofsky
* @version August 8, 2025
*
*/
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int exercise_option(int S_1, int K) {
    return std::max(S_1 - K, 0); // (S_1 - K)^+
}

vector<int> one_period_binomial(int S_0, int u, int d) {
    return {u * S_0, d * S_0};
}

int main() {
    int S_0, X_0, delta_0, K, u, d, r, b;

    cout << "Stock price: ";
    cin >> S_0;

    cout << "Initial Wealth: ";
    cin >> X_0;

    cout << "Number of shares: ";
    cin >> delta_0;

    cout << "Up factor: ";
    cin >> u;

    cout << "Down factor: ";
    cin >> d;

    cout << "Interest rate: ";
    cin >> r;

    cout << "Strike price: ";
    cin >> K;

    vector<int> S_1 = one_period_binomial(S_0, u, d);
    int option_H = exercise_option(S_1[0], K);
    int option_T = exercise_option(S_1[1], K);
    int portfolio_H = delta_0 * S_1[0] + (1 + r) * (X_0 - delta_0 * S_0);
    int portfolio_T = delta_0 * S_1[1] + (1 + r) * (X_0 - delta_0 * S_0);

    cout << "/n If heads, value of option" << option_H << "value of portfolio" << portfolio_H << endl;
    cout << "If tails, value of option" << option_T << "value of portfolio" << portfolio_T << endl;

    if (d < 1 + r < u && payoff_H == portfolio_H && payoff_T == portfolio_T) {
        cout << "Fair priced option" << endl;
    } else {
        cout << "Arbitrage price at time zero" << endl;
    }

    return 0;

}
