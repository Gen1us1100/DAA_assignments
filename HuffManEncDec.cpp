#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <chrono>

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char character, int frequency) : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};

// Comparator for the priority queue
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Function to print Huffman codes from the root of the Huffman tree
void buildCodes(Node* root, const std::string& str, std::unordered_map<char, std::string>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    buildCodes(root->left, str + "0", huffmanCode);
    buildCodes(root->right, str + "1", huffmanCode);
}

// Function to build the Huffman Tree and generate codes
Node* buildHuffmanTree(const std::string& text) {
    std::unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (const auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* sum = new Node('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        pq.push(sum);
    }

    return pq.top();
}

// Function to encode the input text
std::string encodeText(const std::string& text, std::unordered_map<char, std::string>& huffmanCode) {
    std::string encodedStr;
    for (char ch : text) {
        encodedStr += huffmanCode[ch];
    }
    return encodedStr;
}

// Function to decode the encoded text using the Huffman tree
std::string decodeText(Node* root, const std::string& encodedText) {
    std::string decodedStr;
    Node* currentNode = root;
    for (char bit : encodedText) {
        currentNode = (bit == '0') ? currentNode->left : currentNode->right;

        if (!currentNode->left && !currentNode->right) {
            decodedStr += currentNode->ch;
            currentNode = root;
        }
    }
    return decodedStr;
}

// Function to deallocate the Huffman tree
void freeHuffmanTree(Node* root) {
    if (!root) return;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}

int main() {
    std::string fileName;
    std::cout << "Enter the filename to encode: ";
    std::cin >> fileName;

    // Reading the input file
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string text((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    if (text.empty()) {
        std::cerr << "File is empty!" << std::endl;
        return 1;
    }

    // Record the start time for encoding
    auto startEncoding = std::chrono::high_resolution_clock::now();

    Node* root = buildHuffmanTree(text);
    std::unordered_map<char, std::string> huffmanCode;
    buildCodes(root, "", huffmanCode);

    std::string encodedText = encodeText(text, huffmanCode);

    // Record the end time for encoding
    auto endEncoding = std::chrono::high_resolution_clock::now();
    auto encodingDuration = std::chrono::duration_cast<std::chrono::microseconds>(endEncoding - startEncoding);

    // Display the encoded text and encoding time
    std::cout << "Encoded Text: " << encodedText << std::endl;
    std::cout << "Time taken for encoding: " << encodingDuration.count() << " microseconds" << std::endl;

    // Record the start time for decoding
    auto startDecoding = std::chrono::high_resolution_clock::now();

    std::string decodedText = decodeText(root, encodedText);

    // Record the end time for decoding
    auto endDecoding = std::chrono::high_resolution_clock::now();
    auto decodingDuration = std::chrono::duration_cast<std::chrono::microseconds>(endDecoding - startDecoding);

    // Display the decoded text and decoding time
    std::cout << "Decoded Text: " << decodedText << std::endl;
    std::cout << "Time taken for decoding: " << decodingDuration.count() << " microseconds" << std::endl;

    // Free the Huffman tree memory
    freeHuffmanTree(root);

    return 0;
}

