/* Fractional knapasack problem:
 * it is one of the variations of knapasack problem
 * knapasack problem --
 * imagine you're a theif
 *  - you're given a sack of capacity m
 *  - you're given an array of items with weight and their respective value
 *  - THE PROBLEM IS TO FIND THE BEST COMBINATION OF items TO MAXIMIZE value
 *  of the TOTAL SACK and the TOTAL WEIGHT MUST NOT EXCEED BAG CAPACITY.
 * - in fractional items are divisible
 *  - in 0/1 knapsack they are not
 * WE're going to solve fractional knapsack by using GREEDY strategy
 *  */

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct item {
  int index;
  float weight;
  float value;
};

bool compare(item &i1, item &i2) {
  return ((double)(i1.value / i1.weight) > (double)(i2.value / i2.weight));
}

std::vector<double> sortBasedOnValuePerWeight(std::vector<item> &items) {
  // for GREEDY approach we have to select items that have most ValuePerWeight
  // sort the ValuePerWeight array in Descending order such that
  // highest ValuePerWeight items are first
  std::sort(items.begin(), items.end(), compare);
  std::vector<double> ValuePerWeight;
  for (item i : items) {
    ValuePerWeight.push_back((double)(i.value / i.weight));
  }
  return ValuePerWeight;
}

std::map<int, float> itemsToPick(std::vector<item> &items, int &MaxCapacity) {

  std::map<int, float> result;
  for (int i = 0; i < items.size(); i++) {
    if (items[i].weight <= MaxCapacity) { // if item can be completely taken
      result[items[i].index] = 1.0;
      MaxCapacity -= items[i].weight;
    } else { // if item can be partially taken
      result[items[i].index] = ((float)MaxCapacity / (float)items[i].weight);
      MaxCapacity = 0;
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
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
    items[i].index = i + 1;
  }
  sortBasedOnValuePerWeight(items);
  std::map<int, float> result = itemsToPick(items, MaxCapacity);
  std::cout << "Items to pick are: \n";
  std::cout << "Item\tQuantity\n";
  for (auto i : result) {
    std::cout << i.first << "\t" << i.second << std::endl;
  }
  return 0;
}
