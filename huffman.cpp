#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

/*
 * Huffman Encoding:
 * variable size :
 *  it uses the frequencies of each character in the given message
 *  and substitutes calculated huffman codes instead of ASCII codes
 *  - This provides lossless compression
 *  - higher occuring character will have smaller code and vice a versa
 *  - you need to return root of huffman tree to decode
 *  - characters appearing with same frequencies can have interchangeable codes
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
  bool operator()(HuffNode *ele1, HuffNode *ele2) {
    return ele1->freq > ele2->freq; // comparator to sort in ascending order
  }
};

HuffNode *generateHuffTree(std::map<char, int> frequencyTable) {
  std::priority_queue<HuffNode *, std::vector<HuffNode *>, Compare>
      PriorityQueue;
  // push all HuffNodes into PriorityQueue
  for (auto it : frequencyTable) {
    PriorityQueue.push(new HuffNode(it.first, it.second, NULL, NULL));
  }

  HuffNode *least1, *least2;
  //  std::cout << "NO SEF";
  while (PriorityQueue.size() > 1) {
    // std::cout << PriorityQueue.top()->c << ":" << PriorityQueue.top()->freq;
    least1 = PriorityQueue.top();
    PriorityQueue.pop();
    // std::cout << PriorityQueue.top()->c << ":" << PriorityQueue.top()->freq;
    least2 = PriorityQueue.top();
    PriorityQueue.pop();
    PriorityQueue.push(
        new HuffNode('\0', least1->freq + least2->freq, least1, least2));
  }
  HuffNode *root;
  root = PriorityQueue.top();
  // pop the first two
  return root;
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
}

void generateCharMap(HuffNode *HuffRoot, std::string currentEncoding,
                     std::map<char, std::string> &charMap) {
  if (!HuffRoot)
    return;
  // if it is a terminal node -> it is a character node
  if (!HuffRoot->leftchild && !HuffRoot->rightchild) {
    charMap[HuffRoot->c] = currentEncoding;
    return;
  }

  generateCharMap(HuffRoot->leftchild, currentEncoding + "0", charMap);
  generateCharMap(HuffRoot->rightchild, currentEncoding + "1", charMap);
}

std::string encode(std::string &inputStr) {
  std::string encoded_str;
  std::map<char, int> freqT = calcFrequencies(inputStr);
  std::map<char, std::string> charEncodings;
  std::string currentEncoding;
  HuffNode *HuffRoot = generateHuffTree(freqT);
  generateCharMap(HuffRoot, currentEncoding, charEncodings);
  std::cout << "char\t" << "encoding" << std::endl;
  for (auto it : charEncodings) {
    std::cout << it.first << "\t" << it.second << std::endl;
  }
  for (auto ch : inputStr) {
    encoded_str.append(charEncodings[ch]);
  }
  return encoded_str;
}

int main(int argc, char *argv[]) {

  std::string inputStr;
  std::cout << "Enter String to be encoded: ";
  std::cin >> inputStr;
  printFreqTable(inputStr);
  encode(inputStr);
  //  std::cout << "\nENCODED STRING IS : " << encode(inputStr);
  return 0;
}
