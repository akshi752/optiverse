#include<bits/stdc++.h>
#include "../headers/graph_module.h"

using namespace std;

// -------- TOPOLOGICAL SORT (KAHN'S ALGO) --------
vector<int> topoSort(int n, vector<vector<int>>& adj) {

    vector<int> indegree(n, 0);

    // compute indegree
    for(int i = 0; i < n; i++) {
        for(int v : adj[i]) {
            indegree[v]++;
        }
    }

    queue<int> q;

    // push nodes with 0 indegree
    for(int i = 0; i < n; i++) {
        if(indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> order;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        order.push_back(node);

        for(int v : adj[node]) {
            indegree[v]--;
            if(indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    return order;
}

// -------- MAIN MODULE --------
void graphModule() {

    int n, m;
    cout << "Enter number of tasks (nodes): ";
    cin >> n;

    cout << "Enter number of dependencies (edges): ";
    cin >> m;

    vector<vector<int>> adj(n);

    cout << "Enter dependencies (u v) meaning u -> v:\n";
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    cout << "\n--- Processing ---\n";

    auto start = chrono::high_resolution_clock::now();

    vector<int> order = topoSort(n, adj);

    auto end = chrono::high_resolution_clock::now();

    // -------- CHECK CYCLE --------
    if(order.size() != n) {
        cout << "\nCycle Detected!\n";
        cout << "No valid execution order possible.\n";
    }
    else {
        cout << "\nValid Task Order:\n";
        for(int x : order) {
            cout << x << " ";
        }
        cout << "\n";
    }

    cout << "\nExecution Time: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " microseconds\n";
}