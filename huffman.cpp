#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <map>
#include <ostream>
#include <queue>
#include <string>
#include <unistd.h>
#include <vector>

/*
 * Huffman Encoding:
 * variable size :
 *  it uses the frequencies of each character in the given message
 *  and substitutes calculated huffman codes instead of ASCII codes
 *  - This provides lossless compression
 *  - higher occuring character will have smaller code and vice a versa
 *  - you need to return root of huffman tree to decode
 *
 */

struct HuffNode {
  char c;
  int freq;
  HuffNode *leftchild;
  HuffNode *rightchild;
  HuffNode() {
    c = '\0';
    freq = 0;
    leftchild = NULL;
    rightchild = NULL;
  }

  HuffNode(char c, int freq, HuffNode *leftchild, HuffNode *rightchild) {
    this->c = c;
    this->freq = freq;
    this->leftchild = leftchild;
    this->rightchild = rightchild;
  }
};

/*
 * generation of Huffman tree:
 *  - first sort the Huffman Nodes based on their frequencies
 *  - Then select two nodes with least frequencies and add their frequencies
 *  - repeat the process till there's only single node
 *  PriorityQueue is best DS for getting nodes with least frequencies
 * */
class Compare {
public:
  bool operator()(HuffNode ele1, HuffNode ele2) {
    return ele1.freq > ele2.freq; // comparator to sort in ascending order
  }
};

HuffNode generateHuffTree(std::map<char, int> frequencyTable) {
  std::priority_queue<HuffNode, std::vector<HuffNode>, Compare> PriorityQueue;
  // push all HuffNodes into PriorityQueue
  for (auto it : frequencyTable) {
    PriorityQueue.push(HuffNode(it.first, it.second, NULL, NULL));
    std::cout << "element pushed\n";
  }
  if (PriorityQueue.size() >= 2) {
    //    std::cout << PriorityQueue.top().c << ":" << PriorityQueue.top().freq;
    auto least1 = PriorityQueue.top();
    PriorityQueue.pop();
    //   std::cout << PriorityQueue.top().c << ":" << PriorityQueue.top().freq;
    auto least2 = PriorityQueue.top();
    PriorityQueue.pop();
  }

  // pop the first two
  return HuffNode();
}

std::map<char, int> calcFrequencies(std::string &inputStr) {
  std::map<char, int> frequencyTable;
  for (char c : inputStr) {
    if (frequencyTable.find(c) != frequencyTable.end())
      frequencyTable[c] += 1;
    else
      frequencyTable[c] = 1;
  }
  return frequencyTable;
}

void printFreqTable(std::string &inputStr) {
  std::map<char, int> freqT;
  freqT = calcFrequencies(inputStr);
  for (auto it : freqT) {
    std::cout << it.first << ": " << it.second << std::endl;
  }
  generateHuffTree(freqT);
}

// std::string encode(std::string &inputStr) {}

int main(int argc, char *argv[]) {

  std::string inputStr;
  std::cout << "Enter String to be encoded: ";
  std::cin >> inputStr;
  printFreqTable(inputStr);
  //  std::cout << encode(inputStr);
  return 0;
}
