#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>

class HuffmanCoder {
public:
    HuffmanCoder() : root(nullptr) {}

    void buildTree(const std::string& text) {
        if (text.empty()) return;

        // Calculate character frequencies
        std::unordered_map<char, int> freqMap;
        for (char ch : text) {
            freqMap[ch]++;
        }

        // Create priority queue (min-heap)
        std::priority_queue<std::shared_ptr<HuffmanNode>,
                           std::vector<std::shared_ptr<HuffmanNode>>,
                           NodeCompare> pq;

        for (const auto& pair : freqMap) {
            pq.push(std::make_shared<HuffmanNode>(pair.first, pair.second));
        }

        // Build Huffman tree
        while (pq.size() > 1) {
            auto left = pq.top(); pq.pop();
            auto right = pq.top(); pq.pop();

            auto internal = std::make_shared<HuffmanNode>('\0', left->freq + right->freq);
            internal->left = left;
            internal->right = right;

            pq.push(internal);
        }

        root = pq.empty() ? nullptr : pq.top();
        generateCodes(root, "");
    }

    std::string encode(const std::string& text) {
        std::string encoded;
        for (char ch : text) {
            encoded += huffmanCodes[ch];
        }
        return encoded;
    }



 int main(){
     const std::string text = "Design and Analysis of Algorithm";
        HuffmanCoder huffman; 
        huffman.buildTree(text);
        huffman.printCodes();
         std::string encoded = huffman.encode(text);
        std::cout << "\nEncoded Binary: " << encoded << "\n";
        // Decode to verify correctness
        std::string decoded = huffman.decode(encoded);
        std::cout << "Decoded Text: " << decoded << "\n";
        // Display compression statistics
        huffman.compressionStats(text);
        // Verification
        std::cout << "\nVerification: Original and decoded texts "
                  << (text == decoded ? "match!" : "do NOT match!") << "\n";
        
        return 0;
    }
