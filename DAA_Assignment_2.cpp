#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

// Node structure for Huffman Tree
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Custom comparator for min-heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Generate codes by traversing the Huffman Tree
void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;
    if (!root->left && !root->right) { // Leaf node
        huffmanCodes[root->ch] = code;
    }
    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

// Build the Huffman Tree
Node* buildHuffmanTree(const unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for (const auto& pair : freq) {
        minHeap.push(new Node(pair.first, pair.second));
    }
    
    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();
        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        minHeap.push(merged);
    }
    return minHeap.top();
}

// Encode the text using Huffman codes
string huffmanEncode(const string& text, unordered_map<char, string>& huffmanCodes) {
    unordered_map<char, int> freq;
    for (char ch : text) freq[ch]++;
    Node* root = buildHuffmanTree(freq);
    generateCodes(root, "", huffmanCodes);

    string encodedText;
    for (char ch : text) encodedText += huffmanCodes[ch];
    return encodedText;
}

// Decode the encoded text
string huffmanDecode(const string& encodedText, Node* root) {
    string decodedText;
    Node* current = root;
    for (char bit : encodedText) {
        current = (bit == '0') ? current->left : current->right;
        if (!current->left && !current->right) {
            decodedText += current->ch;
            current = root;
        }
    }
    return decodedText;
}

int main() {
    string text = "hello huffman";
    unordered_map<char, string> huffmanCodes;

    // Encoding
    string encodedText = huffmanEncode(text, huffmanCodes);
    cout << "Encoded text: " << encodedText << endl;

    // Print Huffman Codes
    cout << "Huffman Codes:\n";
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Decoding
    unordered_map<char, int> freq;
    for (char ch : text) freq[ch]++;
    Node* root = buildHuffmanTree(freq);
    string decodedText = huffmanDecode(encodedText, root);

    cout << "Decoded text: " << decodedText << endl;

    return 0;
}
