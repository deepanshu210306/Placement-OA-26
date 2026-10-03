#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // adj[u] stores:
    // {child/node, edge_weight}
    vector<vector<pair<int, long long>>> adj;

    // dp0[u]:
    // Maximum weight in the subtree of u when the edge
    // connecting u with its parent is NOT selected.
    //
    // Therefore, u can select at most k edges towards its children.
    vector<long long> dp0;

    // dp1[u]:
    // Maximum weight in the subtree of u when the edge
    // connecting u with its parent IS selected.
    //
    // One degree of u is already occupied by the parent edge,
    // so u can select at most k-1 edges towards its children.
    vector<long long> dp1;

    void dfs(int u, int parent, int k) {

        // ----------------------------------------------------
        // Step 1: Process all children first.
        // This is a post-order DFS because dp[v] is needed
        // before calculating dp[u].
        // ----------------------------------------------------
        for (auto edge : adj[u]) {

            int v = edge.first;

            // Don't go back to the parent.
            if (v == parent)
                continue;

            dfs(v, u, k);
        }

        // ----------------------------------------------------
        // Step 2:
        // Assume initially that we DON'T select any edge
        // from u to its children.
        //
        // Then for every child v, we simply take dp0[v].
        // ----------------------------------------------------
        long long base = 0;

        // gain[i] = extra benefit obtained by selecting
        // the edge between u and child v.
        vector<long long> gain;

        for (auto edge : adj[u]) {

            int v = edge.first;
            long long w = edge.second;

            if (v == parent)
                continue;

            // If edge (u,v) is NOT selected,
            // child v contributes dp0[v].
            base += dp0[v];

            // If edge (u,v) IS selected:
            //
            // We get:
            //     edge weight + dp1[v]
            //
            // because the parent edge of v is now selected.
            //
            // Therefore, the extra benefit is:
            //
            //     w + dp1[v] - dp0[v]
            //
            long long extra = w + dp1[v] - dp0[v];

            // Negative gain is never useful because
            // we are allowed to remove edges.
            if (extra > 0)
                gain.push_back(extra);
        }

        // ----------------------------------------------------
        // Step 3:
        // We want to select the child edges with the largest
        // positive gains.
        // ----------------------------------------------------
        sort(gain.rbegin(), gain.rend());

        // ----------------------------------------------------
        // CASE 1:
        // Parent edge of u is NOT selected.
        //
        // Therefore u has all k degrees available.
        // We can select at most k child edges.
        // ----------------------------------------------------
        dp0[u] = base;

        for (int i = 0; i < min(k, (int)gain.size()); i++) {
            dp0[u] += gain[i];
        }

        // ----------------------------------------------------
        // CASE 2:
        // Parent edge of u IS selected.
        //
        // One degree is already occupied.
        // Therefore only k-1 child edges can be selected.
        // ----------------------------------------------------
        dp1[u] = base;

        for (int i = 0; i < min(k - 1, (int)gain.size()); i++) {
            dp1[u] += gain[i];
        }
    }

    long long maximumWeight(
        int n,
        vector<int>& g_from,
        vector<int>& g_to,
        vector<int>& g_weight,
        int k
    ) {

        // Create adjacency list.
        adj.assign(n, {});

        // Initialize DP arrays.
        dp0.assign(n, 0);
        dp1.assign(n, 0);

        // ----------------------------------------------------
        // Build the undirected tree.
        // ----------------------------------------------------
        for (int i = 0; i < n - 1; i++) {

            int u = g_from[i];
            int v = g_to[i];
            long long w = g_weight[i];

            adj[u].push_back(make_pair(v, w));
            adj[v].push_back(make_pair(u, w));
        }

        // ----------------------------------------------------
        // Root the tree at node 0.
        // Node 0 has no parent edge, so the final answer
        // will be dp0[0].
        // ----------------------------------------------------
        dfs(0, -1, k);

        return dp0[0];
    }
};


// ------------------------------------------------------------
// Driver Code
// ------------------------------------------------------------
int main() {

    int n = 6;

    vector<int> g_from = {0, 0, 0, 1, 2};
    vector<int> g_to   = {1, 2, 3, 4, 5};
    vector<int> g_weight = {8, 6, 10, 5, 9};

    int k = 1;

    Solution sol;

    cout << sol.maximumWeight(
        n,
        g_from,
        g_to,
        g_weight,
        k
    ) << endl;

    return 0;
}