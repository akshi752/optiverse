#include<bits/stdc++.h>
#include "../headers/game_theory.h"

using namespace std;

// -------- MEX FUNCTION --------
int mex(set<int>& s) {
    int m = 0;
    while(s.count(m)) m++;
    return m;
}

// -------- COMPUTE GRUNDY --------
int computeGrundy(int n, vector<int>& dp) {
    if(n == 0) return 0;
    if(dp[n] != -1) return dp[n];

    set<int> s;

    if(n >= 1) s.insert(computeGrundy(n - 1, dp));
    if(n >= 3) s.insert(computeGrundy(n - 3, dp));
    if(n >= 4) s.insert(computeGrundy(n - 4, dp));

    return dp[n] = mex(s);
}

// -------- MAIN MODULE --------
void gameTheoryModule() {

    int piles;
    cout << "Enter number of piles: ";
    cin >> piles;

    vector<int> stones(piles);
    cout << "Enter stones in each pile:\n";
    for(int i = 0; i < piles; i++) {
        cin >> stones[i];
    }

    int maxStone = *max_element(stones.begin(), stones.end());

    vector<int> dp(maxStone + 1, -1);
    dp[0] = 0;

    cout << "\n--- Grundy Numbers ---\n";

    for(int i = 0; i < piles; i++) {
        int g = computeGrundy(stones[i], dp);
        cout << "Pile " << i+1 << " (" << stones[i] << ") -> Grundy = " << g << "\n";
    }

    // XOR all Grundy values
    int xorSum = 0;
    for(int x : stones) {
        xorSum ^= computeGrundy(x, dp);
    }

    cout << "\nOverall Grundy XOR = " << xorSum << "\n";

    if(xorSum == 0) {
        cout << "Result: Losing Position (Second player wins)\n";
    } else {
        cout << "Result: Winning Position (First player wins)\n";
    }

    // -------- SUGGEST ONE WINNING MOVE --------
    if(xorSum != 0) {
        cout << "\nSuggested Winning Move:\n";

        for(int i = 0; i < piles; i++) {
            int g = computeGrundy(stones[i], dp);

            for(int move : {1, 3, 4}) {
                if(stones[i] >= move) {
                    int newVal = stones[i] - move;
                    int newXor = xorSum ^ g ^ computeGrundy(newVal, dp);

                    if(newXor == 0) {
                        cout << "Remove " << move << " stones from pile "
                             << i+1 << "\n";
                        return;
                    }
                }
            }
        }
    }
}