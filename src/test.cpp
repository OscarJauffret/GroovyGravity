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
        double G = 6.6743 * pow(10, -11);
        double rs =  2 * G * 1.9891 * pow(10, 30) / static_cast<double>(299792458.0 * 299792458);
        cout << "rs: " << rs << std::endl;
        double x2 = 0;
        double y2 = 0;
        if ((sqrt(x2 + y2) - rs) > 0) {
            cout << "rs * (std::sqrt(x2 + y2) - rs): " << rs * (std::sqrt(x2 + y2) - rs) << endl;
            cout << 2 * std::sqrt(rs * (std::sqrt(x2 + y2) - rs)) << endl;
        }
    }
}