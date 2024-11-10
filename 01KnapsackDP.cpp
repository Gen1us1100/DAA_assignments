
/*
	In DP Approach we'll be tabulating result by simple logic
	for all changing variables i.e index and RemCapacity ( increasing and decreasing ) 
	we'll be storing the value for dp[index][RemCapacity] in a  n x MaxCapacity 2D array
*/

#include <iostream>
#include <vector>

struct item {
    int weight;
    int value;
    bool whetherTaken = false; // Used for backtracking
};

// DP approach for 0/1 Knapsack
int DP_Approach(std::vector<item> &items, int n, int MaxCapacity) {
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(MaxCapacity + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= MaxCapacity; w++) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = std::max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Print DP array for verification (optional)
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= MaxCapacity; w++) {
            std::cout << dp[i][w] << " ";
        }
        std::cout << std::endl;
    }

    // Backtrack to find the items that were taken
    int w = MaxCapacity;
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            items[i - 1].whetherTaken = true; // Mark item as taken
            w -= items[i - 1].weight;
        }
    }

    return dp[n][MaxCapacity];
}

// Print the result
void printResult(const std::vector<item> &items) {
    std::cout << "Items taken in the knapsack:" << std::endl;
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].whetherTaken) {
            std::cout << "Item " << i + 1 << " (Weight: " << items[i].weight << ", Value: " << items[i].value << ")" << std::endl;
        }
    }
}

int main() {
    int MaxCapacity, n;
    std::cout << "Enter Total capacity of the bag: ";
    std::cin >> MaxCapacity;
    std::cout << "Enter no. of items: ";
    std::cin >> n;

    std::vector<item> items(n);
    for (int i = 0; i < n; i++) {
        std::cout << "Enter weight of item " << i + 1 << ": ";
        std::cin >> items[i].weight;
        std::cout << "Enter value of item " << i + 1 << ": ";
        std::cin >> items[i].value;
    }

    int maxProfit = DP_Approach(items, n, MaxCapacity);
    std::cout << "Maximum value in knapsack = " << maxProfit << std::endl;
    printResult(items);

    return 0;
}

