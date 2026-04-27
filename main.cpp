#include <bits/stdc++.h>
#include "headers/event_scheduling.h"
#include "headers/traffic_analyzer.h"
#include "headers/load_balancer.h"
#include "headers/range_query.h"
#include "headers/number_theory.h"
#include "headers/game_theory.h"
#include "headers/graph_module.h"
#include "headers/tree_module.h"
using namespace std;

void autoTestEvent() {

    cout << "\n===== EVENT SCHEDULING AUTO TEST =====\n";

    int n = 100000;
    vector<pair<int,int>> events;

    // generate random intervals
    for(int i = 0; i < n; i++) {
        int start = rand() % 100000;
        int end = start + (rand() % 100 + 1);
        events.push_back({start, end});
    }

    // ---------- BRUTE (O(n^2)) ----------
    auto s1 = chrono::high_resolution_clock::now();

    int bruteCount = 0;
    vector<bool> taken(n, false);

    for(int i = 0; i < n; i++) {
        if(!taken[i]) {
            bruteCount++;
            for(int j = i+1; j < n; j++) {
                if(!(events[j].first >= events[i].second ||
                     events[j].second <= events[i].first)) {
                    taken[j] = true;
                }
            }
        }
    }

    auto e1 = chrono::high_resolution_clock::now();

    // ---------- OPTIMIZED (GREEDY) ----------
    auto s2 = chrono::high_resolution_clock::now();

    sort(events.begin(), events.end(), [](auto &a, auto &b){
        return a.second < b.second;
    });

    int count = 0;
    int lastEnd = -1;

    for(auto &e : events) {
        if(e.first >= lastEnd) {
            count++;
            lastEnd = e.second;
        }
    }

    auto e2 = chrono::high_resolution_clock::now();

    cout << "Brute Count: " << bruteCount << "\n";
    cout << "Optimized Count: " << count << "\n";

    cout << "Brute Time: "
         << chrono::duration_cast<chrono::milliseconds>(e1 - s1).count()
         << " ms\n";

    cout << "Optimized Time: "
         << chrono::duration_cast<chrono::milliseconds>(e2 - s2).count()
         << " ms\n";

    cout << "===== DONE =====\n";
}
void autoTestRange() {

    cout << "\n===== RANGE QUERY AUTO TEST =====\n";

    int n = 100000;
    int q = 100000;

    vector<int> arr(n);

    // generate random array
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    // generate queries
    vector<pair<int,int>> queries(q);
    for(int i = 0; i < q; i++) {
        int l = rand() % n;
        int r = rand() % n;
        if(l > r) swap(l, r);
        queries[i] = {l, r};
    }

    // =============================
    // 🔴 BRUTE FORCE
    // =============================
    auto s1 = chrono::high_resolution_clock::now();

    long long bruteSum = 0;

    for(auto &qr : queries) {
        for(int i = qr.first; i <= qr.second; i++) {
            bruteSum += arr[i];
        }
    }

    auto e1 = chrono::high_resolution_clock::now();

    // =============================
    // 🟢 OPTIMIZED (PREFIX SUM)
    // =============================
    auto s2 = chrono::high_resolution_clock::now();

    vector<long long> prefix(n);
    prefix[0] = arr[0];

    for(int i = 1; i < n; i++) {
        prefix[i] = prefix[i-1] + arr[i];
    }

    long long optSum = 0;

    for(auto &qr : queries) {
        if(qr.first == 0)
            optSum += prefix[qr.second];
        else
            optSum += prefix[qr.second] - prefix[qr.first-1];
    }

    auto e2 = chrono::high_resolution_clock::now();

    // =============================
    // OUTPUT
    // =============================
    cout << "Brute Time: "
         << chrono::duration_cast<chrono::milliseconds>(e1 - s1).count()
         << " ms\n";

    cout << "Optimized Time: "
         << chrono::duration_cast<chrono::milliseconds>(e2 - s2).count()
         << " ms\n";

    cout << "===== DONE =====\n";
}
void showMenu()
{
    cout << "\n=========== OptiVerse ===========\n";
    cout << "Optimization & Analysis System\n";
    cout << "================================\n\n";

    cout << "Choose a problem to solve:\n\n";

    cout << "1.  Smart Event Scheduling System\n";
    cout << "2.  Traffic Flow Analyzer\n";
    cout << "3.  Load Balancing Optimizer\n";
    cout << "4.  Fast Range Query System\n";
    cout << "5.  Secure Data Processing System\n";
    cout << "6.  Game Strategy Analyzer\n";
    cout << "7.  Network Dependency Resolver\n";
    cout << "8.  Hierarchical Query System\n";
    cout << "9.  Select Module for Auto Test\n";
    cout << "0.  Exit\n\n";
}

// ---------------- MAIN ----------------
int main()
{

    int choice;

    while (true)
    {

        showMenu();

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {

        case 1:
        {
            cout << "\n====================================\n";
            cout << "SMART EVENT SCHEDULING SYSTEM\n";
            cout << "====================================\n";

            cout << "Problem:\n";
            cout << "Select the maximum number of non-overlapping events\n";
            cout << "from a given list of event intervals.\n\n";

            cout << "Real-World Use:\n";
            cout << "Used in scheduling meetings, rooms, or CPU tasks\n";
            cout << "where conflicts must be avoided.\n\n";

            cout << "Input:\n";
            cout << "- Number of events (n)\n";
            cout << "- n lines of start and end time\n\n";

            cout << "Output:\n";
            cout << "- Maximum events scheduled\n";
            cout << "- Performance comparison (Brute vs Optimized)\n\n";

            char run;
            cout << "Do you want to run this module? (y/n): ";
            cin >> run;

            if (run == 'y' || run == 'Y')
            {
                eventSchedulingModule();
            }
            break;
        }

        case 2:
        {
            cout << "\n====================================\n";
            cout << "TRAFFIC FLOW ANALYZER\n";
            cout << "====================================\n";

            cout << "Problem:\n";
            cout << "Find the maximum traffic load in any window of size k.\n\n";

            cout << "Real-World Use:\n";
            cout << "Used in network monitoring, website traffic analysis,\n";
            cout << "and real-time data streams.\n\n";

            cout << "Input:\n";
            cout << "- Size of traffic array (n)\n";
            cout << "- Traffic values\n";
            cout << "- Window size k\n\n";

            cout << "Output:\n";
            cout << "- Maximum traffic in any window\n";
            cout << "- Performance comparison\n\n";

            char run;
            cout << "Do you want to run this module? (y/n): ";
            cin >> run;

            if (run == 'y' || run == 'Y')
            {
                trafficAnalyzerModule();
            }
            break;
        }

        case 3:
        {
            cout << "\n====================================\n";
            cout << "LOAD BALANCING OPTIMIZER\n";
            cout << "====================================\n";

            cout << "Problem:\n";
            cout << "Distribute tasks among workers such that\n";
            cout << "maximum workload is minimized.\n\n";

            cout << "Real-World Use:\n";
            cout << "Used in server load balancing, job scheduling,\n";
            cout << "and resource allocation.\n\n";

            cout << "Input:\n";
            cout << "- Number of tasks\n";
            cout << "- Task sizes\n";
            cout << "- Number of workers\n\n";

            cout << "Output:\n";
            cout << "- Minimum possible maximum load\n";
            cout << "- Performance comparison\n\n";

            char run;
            cout << "Do you want to run this module? (y/n): ";
            cin >> run;

            if (run == 'y' || run == 'Y')
            {
                loadBalancerModule();
            }
            break;
        }

        case 4:
        {
            cout << "\n====================================\n";
            cout << "FAST RANGE QUERY SYSTEM\n";
            cout << "====================================\n";

            cout << "Problem:\n";
            cout << "Efficiently answer multiple range sum queries.\n\n";

            cout << "Real-World Use:\n";
            cout << "Used in analytics dashboards, databases,\n";
            cout << "and financial systems.\n\n";

            char run;
            cout << "Do you want to run this module? (y/n): ";
            cin >> run;

            if (run == 'y' || run == 'Y')
            {
                rangeQueryModule();
            }
            break;
        }

        case 5:
        {
            cout << "\n====================================\n";
            cout << "SECURE DATA PROCESSING SYSTEM\n";
            cout << "====================================\n";

            cout << "Problem:\n";
            cout << "Process large-scale mathematical queries efficiently\n";
            cout << "(GCD, primes, XOR, etc).\n\n";

            cout << "Real-World Use:\n";
            cout << "Used in encryption, data validation, and computation-heavy systems.\n\n";

            char run;
            cout << "Do you want to run this module? (y/n): ";
            cin >> run;

            if (run == 'y' || run == 'Y')
            {
                secureProcessingModule();
            }
            break;
        }

        case 6:
        {
            cout << "\n====================================\n";
            cout << "GAME STRATEGY ANALYZER\n";
            cout << "====================================\n";

            cout << "Problem:\n";
            cout << "Determine winning player using game theory.\n\n";

            char run;
            cout << "Do you want to run this module? (y/n): ";
            cin >> run;

            if (run == 'y' || run == 'Y')
            {
                gameTheoryModule();
            }
            break;
        }

        case 7:
        {
            cout << "\n====================================\n";
            cout << "NETWORK DEPENDENCY RESOLVER\n";
            cout << "====================================\n";

            cout << "Problem:\n";
            cout << "Resolve dependencies and detect cycles.\n\n";

            char run;
            cout << "Do you want to run this module? (y/n): ";
            cin >> run;

            if (run == 'y' || run == 'Y')
            {
                graphModule();
            }
            break;
        }

        case 8:
        {
            cout << "\n====================================\n";
            cout << "HIERARCHICAL QUERY SYSTEM\n";
            cout << "====================================\n";

            cout << "Problem:\n";
            cout << "Answer queries on hierarchical tree structures.\n\n";

            char run;
            cout << "Do you want to run this module? (y/n): ";
            cin >> run;

            if (run == 'y' || run == 'Y')
            {
                treeModule();
            }
            break;
        }
        case 9:
        {
            cout << "\nSelect Module for Auto Test:\n";
            cout << "1. Event Scheduling\n";
            cout << "2. Traffic Analyzer\n";
            cout << "Enter choice: ";

            int testChoice;
            cin >> testChoice;

            if (testChoice == 1)
                autoTestEvent();
            else if (testChoice == 2)
                autoTestRange();
            else
                cout << "Invalid\n";

            break;
        }

        case 0:
            cout << "\nExiting OptiVerse...\n";
            return 0;

        default:
            cout << "\nInvalid choice! Try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}