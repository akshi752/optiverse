#include<bits/stdc++.h>
#include "../headers/number_theory.h"

using namespace std;

// -------- BRUTE GCD --------
int gcdBrute(int a, int b) {
    int ans = 1;
    for(int i = 1; i <= min(a, b); i++) {
        if(a % i == 0 && b % i == 0)
            ans = i;
    }
    return ans;
}

// -------- OPTIMIZED GCD (EUCLID) --------
int gcdOptimized(int a, int b) {
    if(b == 0) return a;
    return gcdOptimized(b, a % b);
}

// -------- BRUTE PRIME CHECK --------
bool isPrimeBrute(int n) {
    if(n < 2) return false;
    for(int i = 2; i < n; i++) {
        if(n % i == 0) return false;
    }
    return true;
}

// -------- OPTIMIZED PRIME CHECK --------
bool isPrimeOptimized(int n) {
    if(n < 2) return false;
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) return false;
    }
    return true;
}

// -------- BRUTE XOR RANGE --------
int xorBrute(int L, int R) {
    int res = 0;
    for(int i = L; i <= R; i++) {
        res ^= i;
    }
    return res;
}

// -------- OPTIMIZED XOR PREFIX --------
int xorUpto(int x) {
    if(x % 4 == 0) return x;
    if(x % 4 == 1) return 1;
    if(x % 4 == 2) return x + 1;
    return 0;
}

int xorOptimized(int L, int R) {
    return xorUpto(R) ^ xorUpto(L - 1);
}

// -------- MAIN MODULE --------
void secureProcessingModule() {

    cout << "\nChoose Operation:\n";
    cout << "1. GCD Computation\n";
    cout << "2. Prime Check\n";
    cout << "3. XOR Range Query\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    cout << "\n--- Results ---\n";

    // -------- GCD --------
    if(choice == 1) {
        int a, b;
        cout << "Enter two numbers: ";
        cin >> a >> b;

        if(max(a,b) <= 10000) {
            cout << "\n[Using BOTH Brute & Optimized]\n";

            auto s1 = chrono::high_resolution_clock::now();
            int g1 = gcdBrute(a, b);
            auto e1 = chrono::high_resolution_clock::now();

            auto s2 = chrono::high_resolution_clock::now();
            int g2 = gcdOptimized(a, b);
            auto e2 = chrono::high_resolution_clock::now();

            cout << "Brute GCD: " << g1 << "\n";
            cout << "Optimized GCD: " << g2 << "\n";

            cout << "\nTime:\n";
            cout << "Brute: "
                 << chrono::duration_cast<chrono::microseconds>(e1 - s1).count()
                 << " us\n";

            cout << "Optimized: "
                 << chrono::duration_cast<chrono::microseconds>(e2 - s2).count()
                 << " us\n";
        } else {
            cout << "\n[Large Input → Optimized Only]\n";
            cout << "GCD: " << gcdOptimized(a, b) << "\n";
        }
    }

    // -------- PRIME --------
    else if(choice == 2) {
        int n;
        cout << "Enter number: ";
        cin >> n;

        if(n <= 10000) {
            cout << "\n[Using BOTH Brute & Optimized]\n";

            auto s1 = chrono::high_resolution_clock::now();
            bool p1 = isPrimeBrute(n);
            auto e1 = chrono::high_resolution_clock::now();

            auto s2 = chrono::high_resolution_clock::now();
            bool p2 = isPrimeOptimized(n);
            auto e2 = chrono::high_resolution_clock::now();

            cout << "Brute: " << (p1 ? "Prime" : "Not Prime") << "\n";
            cout << "Optimized: " << (p2 ? "Prime" : "Not Prime") << "\n";

            cout << "\nTime:\n";
            cout << "Brute: "
                 << chrono::duration_cast<chrono::microseconds>(e1 - s1).count()
                 << " us\n";

            cout << "Optimized: "
                 << chrono::duration_cast<chrono::microseconds>(e2 - s2).count()
                 << " us\n";
        } else {
            cout << "\n[Large Input → Optimized Only]\n";
            cout << (isPrimeOptimized(n) ? "Prime\n" : "Not Prime\n");
        }
    }

    // -------- XOR --------
    else if(choice == 3) {
        int L, R;
        cout << "Enter range (L R): ";
        cin >> L >> R;

        if(R - L <= 10000) {
            cout << "\n[Using BOTH Brute & Optimized]\n";

            auto s1 = chrono::high_resolution_clock::now();
            int x1 = xorBrute(L, R);
            auto e1 = chrono::high_resolution_clock::now();

            auto s2 = chrono::high_resolution_clock::now();
            int x2 = xorOptimized(L, R);
            auto e2 = chrono::high_resolution_clock::now();

            cout << "Brute XOR: " << x1 << "\n";
            cout << "Optimized XOR: " << x2 << "\n";

            cout << "\nTime:\n";
            cout << "Brute: "
                 << chrono::duration_cast<chrono::microseconds>(e1 - s1).count()
                 << " us\n";

            cout << "Optimized: "
                 << chrono::duration_cast<chrono::microseconds>(e2 - s2).count()
                 << " us\n";
        } else {
            cout << "\n[Large Input → Optimized Only]\n";
            cout << "XOR: " << xorOptimized(L, R) << "\n";
        }
    }

    else {
        cout << "Invalid choice\n";
    }
}