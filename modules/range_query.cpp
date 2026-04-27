#include<bits/stdc++.h>
#include "../headers/range_query.h"

using namespace std;

// -------- BRUTE FORCE O(n) per query --------
int rangeSumBrute(vector<int>& arr, int L, int R) {
    int sum = 0;
    for(int i = L; i <= R; i++) {
        sum += arr[i];
    }
    return sum;
}

// -------- PREFIX SUM PREPROCESS --------
vector<int> buildPrefix(vector<int>& arr) {
    int n = arr.size();
    vector<int> prefix(n);

    prefix[0] = arr[0];
    for(int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + arr[i];
    }

    return prefix;
}

// -------- OPTIMIZED QUERY O(1) --------
int rangeSumOptimized(vector<int>& prefix, int L, int R) {
    if(L == 0) return prefix[R];
    return prefix[R] - prefix[L - 1];
}

// -------- MAIN MODULE --------
void rangeQueryModule() {

    int n;
    cout << "Enter array size: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements:\n";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int q;
    cout << "Enter number of queries: ";
    cin >> q;

    vector<pair<int,int>> queries(q);
    cout << "Enter queries (L R) [0-indexed]:\n";
    for(int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }

    cout << "\n--- Results ---\n";

    // SMALL INPUT → compare both
    if(n <= 1000 && q <= 1000) {
        cout << "\n[Using BOTH Brute & Optimized]\n";

        // BRUTE
        auto start1 = chrono::high_resolution_clock::now();
        cout << "\nBrute Results:\n";
        for(auto &qr : queries) {
            cout << "Sum(" << qr.first << "," << qr.second << ") = "
                 << rangeSumBrute(arr, qr.first, qr.second) << "\n";
        }
        auto end1 = chrono::high_resolution_clock::now();

        // OPTIMIZED
        auto start2 = chrono::high_resolution_clock::now();
        vector<int> prefix = buildPrefix(arr);

        cout << "\nOptimized Results:\n";
        for(auto &qr : queries) {
            cout << "Sum(" << qr.first << "," << qr.second << ") = "
                 << rangeSumOptimized(prefix, qr.first, qr.second) << "\n";
        }
        auto end2 = chrono::high_resolution_clock::now();

        cout << "\nTime Comparison:\n";
        cout << "Brute: "
             << chrono::duration_cast<chrono::microseconds>(end1 - start1).count()
             << " microseconds\n";

        cout << "Optimized: "
             << chrono::duration_cast<chrono::microseconds>(end2 - start2).count()
             << " microseconds\n";
    }

    // LARGE INPUT → optimized only
    else {
        cout << "\n[Large Input → Using Optimized Only]\n";

        auto start = chrono::high_resolution_clock::now();

        vector<int> prefix = buildPrefix(arr);

        for(auto &qr : queries) {
            cout << "Sum(" << qr.first << "," << qr.second << ") = "
                 << rangeSumOptimized(prefix, qr.first, qr.second) << "\n";
        }

        auto end = chrono::high_resolution_clock::now();

        cout << "\nExecution Time: "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms\n";
    }
}