#include<bits/stdc++.h>
#include "../headers/tree_module.h"

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int parent[MAXN];
int depth[MAXN];
int up[MAXN][20]; // binary lifting table

// -------- DFS to compute parent & depth --------
void dfs(int node, int par) {
    parent[node] = par;
    for(auto child : adj[node]) {
        if(child != par) {
            depth[child] = depth[node] + 1;
            dfs(child, node);
        }
    }
}

// -------- BRUTE LCA (O(N)) --------
int lcaBrute(int u, int v) {

    // bring to same depth
    while(depth[u] > depth[v]) u = parent[u];
    while(depth[v] > depth[u]) v = parent[v];

    while(u != v) {
        u = parent[u];
        v = parent[v];
    }

    return u;
}

// -------- BINARY LIFTING PREPROCESS --------
void preprocess(int n) {

    for(int i = 1; i <= n; i++) {
        up[i][0] = parent[i];
    }

    for(int j = 1; j < 20; j++) {
        for(int i = 1; i <= n; i++) {
            if(up[i][j-1] != -1)
                up[i][j] = up[ up[i][j-1] ][j-1];
            else
                up[i][j] = -1;
        }
    }
}

// -------- FAST LCA (O(log N)) --------
int lcaOptimized(int u, int v) {

    if(depth[u] < depth[v]) swap(u, v);

    // lift u up
    int diff = depth[u] - depth[v];
    for(int i = 0; i < 20; i++) {
        if(diff & (1 << i)) {
            u = up[u][i];
        }
    }

    if(u == v) return u;

    for(int i = 19; i >= 0; i--) {
        if(up[u][i] != -1 && up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }

    return parent[u];
}

// -------- MAIN MODULE --------
void treeModule() {

    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    // clear previous data
    for(int i = 1; i <= n; i++) {
        adj[i].clear();
    }

    cout << "Enter " << n-1 << " edges (u v):\n";
    for(int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // initialize
    memset(parent, -1, sizeof(parent));
    memset(depth, 0, sizeof(depth));
    memset(up, -1, sizeof(up));

    // root = 1
    dfs(1, -1);

    preprocess(n);

    int q;
    cout << "Enter number of queries: ";
    cin >> q;

    vector<pair<int,int>> queries(q);
    cout << "Enter queries (u v):\n";
    for(int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }

    cout << "\n--- Results ---\n";

    // SMALL INPUT → SHOW BOTH
    if(n <= 1000) {
        cout << "\n[Using BOTH Brute & Optimized]\n";

        auto start1 = chrono::high_resolution_clock::now();
        for(auto &qr : queries) {
            cout << "Brute LCA(" << qr.first << ", " << qr.second << ") = "
                 << lcaBrute(qr.first, qr.second) << "\n";
        }
        auto end1 = chrono::high_resolution_clock::now();

        auto start2 = chrono::high_resolution_clock::now();
        for(auto &qr : queries) {
            cout << "Optimized LCA(" << qr.first << ", " << qr.second << ") = "
                 << lcaOptimized(qr.first, qr.second) << "\n";
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

    // LARGE INPUT → ONLY OPTIMIZED
    else {
        cout << "\n[Large Input → Using Optimized Only]\n";

        auto start = chrono::high_resolution_clock::now();

        for(auto &qr : queries) {
            cout << "LCA(" << qr.first << ", " << qr.second << ") = "
                 << lcaOptimized(qr.first, qr.second) << "\n";
        }

        auto end = chrono::high_resolution_clock::now();

        cout << "\nExecution Time: "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms\n";
    }
}