#include<bits/stdc++.h>
#include "../headers/load_balancer.h"

using namespace std;

// -------- CHECK FUNCTION (Greedy) --------
// Can we assign tasks so that max load <= mid ?
bool isPossible(vector<int>& tasks, int workers, int maxLoad) {

    int usedWorkers = 1;
    int currentLoad = 0;

    for(int task : tasks) {

        // if single task > maxLoad → impossible
        if(task > maxLoad) return false;

        if(currentLoad + task <= maxLoad) {
            currentLoad += task;
        }
        else {
            usedWorkers++;
            currentLoad = task;
        }
    }

    return usedWorkers <= workers;
}

// -------- OPTIMIZED (Binary Search on Answer) --------
int minimizeMaxLoad(vector<int>& tasks, int workers) {

    int low = *max_element(tasks.begin(), tasks.end());
    int high = accumulate(tasks.begin(), tasks.end(), 0);
    int ans = high;

    while(low <= high) {
        int mid = (low + high) / 2;

        if(isPossible(tasks, workers, mid)) {
            ans = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    return ans;
}

// -------- MAIN MODULE --------
void loadBalancerModule() {

    int n;
    cout << "Enter number of tasks: ";
    cin >> n;

    vector<int> tasks(n);
    cout << "Enter task sizes:\n";
    for(int i = 0; i < n; i++) {
        cin >> tasks[i];
    }

    int workers;
    cout << "Enter number of workers: ";
    cin >> workers;

    cout << "\n--- Results ---\n";

    // SMALL INPUT → explain concept + run optimized
    if(n <= 20) {
        cout << "\n[Small Input]\n";
        cout << "Brute force (all distributions) is exponential → not feasible.\n";
        cout << "Using optimized Binary Search approach.\n\n";

        auto start = chrono::high_resolution_clock::now();

        int ans = minimizeMaxLoad(tasks, workers);

        auto end = chrono::high_resolution_clock::now();

        cout << "Minimum Maximum Load: " << ans << "\n";

        cout << "\nExecution Time: "
             << chrono::duration_cast<chrono::microseconds>(end - start).count()
             << " microseconds\n";
    }

    // LARGE INPUT → optimized only
    else {
        cout << "\n[Large Input → Using Optimized Only]\n";

        auto start = chrono::high_resolution_clock::now();

        int ans = minimizeMaxLoad(tasks, workers);

        auto end = chrono::high_resolution_clock::now();

        cout << "Minimum Maximum Load: " << ans << "\n";

        cout << "\nExecution Time: "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms\n";
    }
}