//
// Created by Oscar Jauffret on 21/06/2026.
//
#include <cmath>
#include <complex>
#include <iostream>

using namespace std;
int main() {
    for (int i = 0; i < 1; i++) {
        // r_S = 2GM/c^2
        double c2 = 299792458.0 * 299792458;
        double G = 6.6743 * pow(10, -11);
        //double mass = desiredRs * c2/(2 * G);
        float mass =  3.36648e+27;
        //cout << "Mass required for rs=" << desiredRs << " is " << mass << endl;
        double rs =  2 * G * mass / c2;
        cout << "rs: " << rs << std::endl;
        double x = 5;
        double y = 5;
        double x2 = x * x;
        double y2 = y * y;
        if ((sqrt(x2 + y2) - rs) > 0) {
            cout << "rs * (std::sqrt(x2 + y2) - rs): " << rs * (std::sqrt(x2 + y2) - rs) << endl;
            cout << 2 * std::sqrt(rs * (std::sqrt(x2 + y2) - rs)) << endl;
        }
    }
}