#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>

class HuffmanNode {
public:
    char data;
    int freq;
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;

    HuffmanNode(char ch, int f) : data(ch), freq(f), left(nullptr), right(nullptr) {}
    ~HuffmanNode() = default;
};

struct NodeCompare {
    bool operator()(const std::shared_ptr<HuffmanNode>& a, const std::shared_ptr<HuffmanNode>& b) {
        return a->freq > b->freq;
    }
};

class HuffmanCoder {
public:
HuffmanCoder() : root(nullptr) {}

    void buildTree(const string& text) {
        if (text.empty()) return;

        // Calculate character frequencies
        std::unordered_map<char, int> freqMap;
        for (char ch : text) {
            freqMap[ch]++;
        }

        // Create priority queue (min-heap)
        priority_queue<shared_ptr<HuffmanNode>,
                           vector<shared_ptr<HuffmanNode>>,
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

std::string decode(const std::string& encodedStr) {  
    std::string decoded;  
    auto current = root;  
      
    for (char bit : encodedStr) {  
        current = (bit == '0') ? current->left : current->right;  
          
        if (!current->left && !current->right) {  
            decoded += current->data;  
            current = root;  
        }  
    }  
    return decoded;  
}

void printCodes() const {
        std::cout << "Huffman Codes:\n";
        for (const auto& pair : huffmanCodes) {
            std::cout << "'" << pair.first << "' : " << pair.second << "\n";
        }
    }

    void compressionStats(const std::string& original) const {
        int originalBits = original.length() * 8;
        int compressedBits = 0;

        for (char ch : original) {
            compressedBits += huffmanCodes.at(ch).length();
        }

        double ratio = (1.0 - static_cast<double>(compressedBits) / originalBits) * 100.0;

        std::cout << "\n--- Compression Statistics ---\n";
        std::cout << "Original Size: " << originalBits << " bits\n";
        std::cout << "Compressed Size: " << compressedBits << " bits\n";
        std::cout << "Compression Ratio: " << ratio << "%\n";
        std::cout << "Space Saved: " << (originalBits - compressedBits) << " bits\n";
    }

private:
    std::shared_ptr<HuffmanNode> root;
    std::unordered_map<char, std::string> huffmanCodes;

    void generateCodes(const std::shared_ptr<HuffmanNode>& node, const std::string& code) {
        if (!node) return;

        if (!node->left && !node->right) {
            huffmanCodes[node->data] = code;
            return;
        }

        generateCodes(node->left, code + "0");
        generateCodes(node->right, code + "1");
    }
};

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
