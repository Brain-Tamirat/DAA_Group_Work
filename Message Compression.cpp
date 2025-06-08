//***HuffMan Coding DAA Group Work***
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

//***Faris***
class HuffmanNode {
public:
    char data;
    int freq;
    shared_ptr<HuffmanNode> left;
    shared_ptr<HuffmanNode> right;

    HuffmanNode(char ch, int f) : data(ch), freq(f), left(nullptr), right(nullptr) {}
    ~HuffmanNode() = default;
};

//***Daniel***
struct NodeCompare {
    bool operator()(const shared_ptr<HuffmanNode>& a, const shared_ptr<HuffmanNode>& b) {
        return a->freq > b->freq;
    }
};

class HuffmanCoder {
public:
    HuffmanCoder() : root(nullptr) {}

    void buildTree(const string& text) {
        if (text.empty()) return;

        // Calculate character frequencies
        unordered_map<char, int> freqMap;
        for (char ch : text) {
            freqMap[ch]++;
        }

        // Create priority queue (min-heap)
        priority_queue<shared_ptr<HuffmanNode>,
                           vector<shared_ptr<HuffmanNode>>,
                           NodeCompare> pq;

        for (const auto& pair : freqMap) {
            pq.push(make_shared<HuffmanNode>(pair.first, pair.second));
        }

        // Build Huffman tree
        while (pq.size() > 1) {
            auto left = pq.top(); pq.pop();
            auto right = pq.top(); pq.pop();

            auto internal = make_shared<HuffmanNode>('\0', left->freq + right->freq);
            internal->left = left;
            internal->right = right;

            pq.push(internal);
        }

        root = pq.empty() ? nullptr : pq.top();
        generateCodes(root, "");
    }

    string encode(const string& text) {
        string encoded;
        for (char ch : text) {
            encoded += huffmanCodes[ch];
        }
        return encoded;
    }

//***Hamza***
    string decode(const string& encodedStr) {  
        string decoded;  
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

//***Digafe***
    void printCodes() const {
            cout << "Huffman Codes:\n";
            for (const auto& pair : huffmanCodes) {
                cout << "'" << pair.first << "' : " << pair.second << "\n";
            }
        }

        void compressionStats(const string& original) const {
            int originalBits = original.length() * 8;
            int compressedBits = 0;

            for (char ch : original) {
                compressedBits += huffmanCodes.at(ch).length();
            }

            double ratio = (1.0 - static_cast<double>(compressedBits) / originalBits) * 100.0;

            cout << "\n--- Compression Statistics ---\n";
            cout << "Original Size: " << originalBits << " bits\n";
            cout << "Compressed Size: " << compressedBits << " bits\n";
            cout << "Compression Ratio: " << ratio << "%\n";
            cout << "Space Saved: " << (originalBits - compressedBits) << " bits\n";
        }

private:
    shared_ptr<HuffmanNode> root;
    unordered_map<char, string> huffmanCodes;

    void generateCodes(const shared_ptr<HuffmanNode>& node, const string& code) {
        if (!node) return;

        if (!node->left && !node->right) {
            huffmanCodes[node->data] = code;
            return;
        }

        generateCodes(node->left, code + "0");
        generateCodes(node->right, code + "1");
    }
};

//***Bisrat***
 int main(){
    string message;
    HuffmanCoder huffman;

	cout<<" Enter Your Message: ";
	getline(cin,message);
    string text = message;

    // Build Huffman tree and generate codes
        huffman.buildTree(text);

    // Display generated codes
        huffman.printCodes();

    // Encode the text
    string encoded = huffman.encode(text);
    cout << "\nEncoded Binary: " << encoded << "\n";

    // Decode to verify correctness
    string decoded = huffman.decode(encoded);
    cout << "Decoded Text: " << decoded << "\n";

    // Display compression statistics
    huffman.compressionStats(text);

    // Verification
    cout << "\nVerification: Original and decoded texts "
                << (text == decoded ? "match!" : "do NOT match!") << "\n";
    
    return 0;
    }