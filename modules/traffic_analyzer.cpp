#include<bits/stdc++.h>
#include "../headers/traffic_analyzer.h"

using namespace std;

// -------- BRUTE FORCE O(n * k) --------
int maxTrafficBrute(vector<int>& arr, int k) {
    int n = arr.size();
    int maxSum = 0;

    for(int i = 0; i <= n - k; i++) {
        int sum = 0;
        for(int j = i; j < i + k; j++) {
            sum += arr[j];
        }
        maxSum = max(maxSum, sum);
    }

    return maxSum;
}

// -------- OPTIMIZED SLIDING WINDOW O(n) --------
int maxTrafficOptimized(vector<int>& arr, int k) {
    int n = arr.size();

    int windowSum = 0;

    // first window
    for(int i = 0; i < k; i++) {
        windowSum += arr[i];
    }

    int maxSum = windowSum;

    // slide window
    for(int i = k; i < n; i++) {
        windowSum += arr[i];
        windowSum -= arr[i - k];
        maxSum = max(maxSum, windowSum);
    }

    return maxSum;
}

// -------- MAIN MODULE --------
void trafficAnalyzerModule() {

    int n;
    cout << "Enter number of time points: ";
    cin >> n;

    vector<int> traffic(n);
    cout << "Enter traffic values:\n";
    for(int i = 0; i < n; i++) {
        cin >> traffic[i];
    }

    int k;
    cout << "Enter window size k: ";
    cin >> k;

    cout << "\n--- Results ---\n";

    // SMALL INPUT → BOTH METHODS
    if(n <= 1000) {
        cout << "\n[Using BOTH Brute & Optimized]\n";

        auto start1 = chrono::high_resolution_clock::now();
        int bruteAns = maxTrafficBrute(traffic, k);
        auto end1 = chrono::high_resolution_clock::now();

        auto start2 = chrono::high_resolution_clock::now();
        int optAns = maxTrafficOptimized(traffic, k);
        auto end2 = chrono::high_resolution_clock::now();

        cout << "Brute Result: " << bruteAns << "\n";
        cout << "Optimized Result: " << optAns << "\n";

        cout << "\nTime Comparison:\n";
        cout << "Brute: "
             << chrono::duration_cast<chrono::microseconds>(end1 - start1).count()
             << " microseconds\n";

        cout << "Optimized: "
             << chrono::duration_cast<chrono::microseconds>(end2 - start2).count()
             << " microseconds\n";
    }

    // LARGE INPUT → ONLY OPTIMIZED
    else {
        cout << "\n[Large Input → Using Optimized Only]\n";

        auto start = chrono::high_resolution_clock::now();

        int ans = maxTrafficOptimized(traffic, k);

        auto end = chrono::high_resolution_clock::now();

        cout << "Maximum Traffic: " << ans << "\n";

        cout << "\nExecution Time: "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms\n";
    }
}