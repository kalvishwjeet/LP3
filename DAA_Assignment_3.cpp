#include <iostream>
#include <vector>
using namespace std;

// Function to solve the 0-1 Knapsack problem using dynamic programming
int knapsackDP(int W, const vector<int>& weights, const vector<int>& values, int n) {
    // Create a 2D array to store the maximum value for each subproblem
    vector<vector<int>> dp(n + 1, vector<int>(W + 1));

    // Build the dp array bottom-up
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;  // Base case: no item or zero capacity
            } else if (weights[i - 1] <= w) {
                // Take the maximum value of either including or excluding the item
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                // Exclude the item if its weight exceeds the current capacity
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The last element of the dp array contains the solution to the problem
    return dp[n][W];
}


struct Node {
    int level;          // Level of the node (corresponds to the index of the item)
    int profit;         // Total profit till this node
    int weight;         // Total weight till this node
    float bound;        // Upper bound on the maximum profit obtainable from this node
};

// Comparison operator for sorting based on the upper bound of profit
struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.bound < b.bound;
    }
};

// Function to calculate the upper bound of the maximum profit for a given node
float calculateBound(const Node& node, int n, int W, const vector<int>& weights, const vector<int>& values) {
    if (node.weight >= W) return 0;

    float bound = node.profit;
    int remainingWeight = W - node.weight;
    
    // Start from the next item (node.level + 1) and add fractional items if necessary
    for (int i = node.level + 1; i < n && remainingWeight > 0; i++) {
        if (weights[i] <= remainingWeight) {
            remainingWeight -= weights[i];
            bound += values[i];
        } else {
            // Add fractional part of the item if remaining weight is less than its weight
            bound += values[i] * ((float)remainingWeight / weights[i]);
            break;
        }
    }
    return bound;
}

// Function to solve the 0-1 Knapsack problem using Branch and Bound
int knapsackBB(int W, const vector<int>& weights, const vector<int>& values, int n) {
    // Sort items based on value-to-weight ratio (for calculating bound)
    vector<pair<float, int>> ratioIndex(n);
    for (int i = 0; i < n; i++) {
        ratioIndex[i] = {(float)values[i] / weights[i], i};
    }
    sort(ratioIndex.begin(), ratioIndex.end(), greater<pair<float, int>>());

    // Create sorted lists of weights and values based on the value-to-weight ratio
    vector<int> sortedWeights(n), sortedValues(n);
    for (int i = 0; i < n; i++) {
        sortedWeights[i] = weights[ratioIndex[i].second];
        sortedValues[i] = values[ratioIndex[i].second];
    }

    // Priority queue (max-heap) to store live nodes of the decision tree
    priority_queue<Node, vector<Node>, Compare> pq;

    // Create a dummy node and calculate its bound
    Node u, v;  // u -> current node, v -> child node
    v.level = -1;
    v.profit = v.weight = 0;
    v.bound = calculateBound(v, n, W, sortedWeights, sortedValues);

    // Push the dummy node to the priority queue
    pq.push(v);

    int maxProfit = 0;  // To store the maximum profit

    // Process nodes in the priority queue
    while (!pq.empty()) {
        v = pq.top();
        pq.pop();

        // If this node cannot lead to a better solution, skip it
        if (v.bound > maxProfit) {
            // Consider the child node where the current item is included
            u.level = v.level + 1;
            u.weight = v.weight + sortedWeights[u.level];
            u.profit = v.profit + sortedValues[u.level];

            // Check if the weight is within the capacity and update maxProfit
            if (u.weight <= W && u.profit > maxProfit) {
                maxProfit = u.profit;
            }

            // Calculate bound for the child node and add it to the queue if promising
            u.bound = calculateBound(u, n, W, sortedWeights, sortedValues);
            if (u.bound > maxProfit) pq.push(u);

            // Consider the child node where the current item is not included
            u.weight = v.weight;
            u.profit = v.profit;
            u.bound = calculateBound(u, n, W, sortedWeights, sortedValues);
            if (u.bound > maxProfit) pq.push(u);
        }
    }

    return maxProfit;
}




int main() {
    int n, W;

    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> weights(n), values(n);
    
    cout << "Enter the weights of the items:\n";
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    cout << "Enter the values of the items:\n";
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    cout << "Enter the maximum capacity of the knapsack: ";
    cin >> W;

    int max_value = knapsackDP(W, weights, values, n);
    cout << "Maximum value that can be obtained: " << max_value << endl;

    return 0;
}
