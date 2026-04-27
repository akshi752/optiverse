#include<bits/stdc++.h>
#include "../headers/event_scheduling.h"
#include "../utils/visualizer.h"
#include "../utils/timer.h"

using namespace std;

// -------- BRUTE --------
int maxEventsBrute(vector<pair<int,int>>& events, int n) {
    int maxCount = 0;

    for(int mask = 0; mask < (1 << n); mask++) {
        vector<pair<int,int>> subset;

        for(int i = 0; i < n; i++) {
            if(mask & (1 << i)) {
                subset.push_back(events[i]);
            }
        }

        sort(subset.begin(), subset.end());

        bool valid = true;
        for(int i = 1; i < subset.size(); i++) {
            if(subset[i].first < subset[i-1].second) {
                valid = false;
                break;
            }
        }

        if(valid) {
            maxCount = max(maxCount, (int)subset.size());
        }
    }

    return maxCount;
}

// -------- GREEDY --------
int maxEventsGreedy(vector<pair<int,int>>& events) {
    sort(events.begin(), events.end(), [](auto &a, auto &b){
        return a.second < b.second;
    });

    int count = 0, lastEnd = -1;

    for(auto &e : events) {
        if(e.first >= lastEnd) {
            count++;
            lastEnd = e.second;
        }
    }

    return count;
}

// -------- MODULE --------
void eventSchedulingModule() {

    int n;
    cout << "Enter number of events: ";
    cin >> n;

    vector<pair<int,int>> events(n);

    cout << "Enter start and end time:\n";
    for(int i = 0; i < n; i++) {
        cin >> events[i].first >> events[i].second;
    }

    vector<pair<int,int>> copyEvents = events;

    int THRESHOLD = 20;

    cout << "\n========== ANALYSIS ==========\n";

    // ---- GREEDY ----
    clock_t g1 = clock();
    int greedyAns = maxEventsGreedy(events);
    clock_t g2 = clock();

    double greedyTime = getTime(g1, g2);

    cout << "\n[CP APPROACH - GREEDY]\n";
    cout << "Answer: " << greedyAns << endl;
    cout << "Time: " << greedyTime << " sec\n";

    double bruteTime = 0;

    // ---- BRUTE ----
    if(n <= THRESHOLD) {
        cout << "\n[BRUTE FORCE APPROACH]\n";

        clock_t b1 = clock();
        int bruteAns = maxEventsBrute(copyEvents, n);
        clock_t b2 = clock();

        bruteTime = getTime(b1, b2);

        cout << "Answer: " << bruteAns << endl;
        cout << "Time: " << bruteTime << " sec\n";
    }
    else {
        cout << "\n[BRUTE FORCE APPROACH]\n";
        cout << "Skipped ❌ (Input too large)\n";
    }

    // ---- VISUAL ----
    cout << "\n========== VISUAL COMPARISON ==========\n";
    showBar("Greedy", greedyTime);

    if(n <= THRESHOLD)
        showBar("Brute ", bruteTime);

    // ---- SPEEDUP ----
    if(n <= THRESHOLD && greedyTime > 0)
        cout << "\nSpeedup: " << bruteTime / greedyTime << "x faster\n";

    // ---- COMPLEXITY ----
    cout << "\n========== COMPLEXITY ==========\n";
    cout << "Brute: O(2^n * n log n)\n";
    cout << "Greedy: O(n log n)\n";
}