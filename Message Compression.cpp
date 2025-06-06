#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <fstream>
using namespace std;

 int main(){
     const std::string text = "Design and Analysis of Algorithm";
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
