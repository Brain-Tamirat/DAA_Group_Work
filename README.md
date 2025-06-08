# Huffman Coding for Data Compression

This project implements Huffman coding in C++ to compress text data. It is developed as a collaborative group assignment for the Data Structures and Algorithms (DAA) course.

---

## Table of Contents

1. [Overview](#overview)
2. [Group Members](#group-members)
3. [Dependencies](#dependencies)
4. [Code Walkthrough](#code-walkthrough)
5. [Data Structures and Design Choices](#data-structures-and-design-choices)
6. [Compression Efficiency](#compression-efficiency)
7. [Usage Example](#usage-example)

---

## Overview

Huffman coding is a lossless data compression algorithm that assigns variable-length codes to input characters based on their frequencies. Characters that occur more frequently are assigned shorter codes, resulting in an overall reduction of the message size.

This C++ implementation reads a text message from the user, builds a Huffman tree, generates prefix codes, encodes the message, decodes it back to text, and prints compression statistics.

## Group Members

1. Brain Tamirat NSR/234/15
2. Bisrat Birhanu NSR/231/15
3. DanielDebebe NSR/267/15
4. DigafeDireso NSR/295/15
5. Faris Damtew NSR/1050/15
6. Hamza Muktar NSR/465/15

## Dependencies Or Libraries

* **C++11** or later
* Standard Library headers:

  * `<iostream>`
  * `<string>`
  * `<queue>`
  * `<unordered_map>`
  * `<vector>`
  * `<memory>`
  * `<algorithm>`

No external libraries are required.

## Code Walkthrough

* **`HuffmanNode`** : Represents each tree node, storing a character, its frequency, and pointers to left/right children.

* **`NodeCompare`**: A functor that orders `HuffmanNode` pointers in a min-heap based on frequency.

* **`HuffmanCoder`**:

  * `buildTree(const string&)` — Counts frequencies, builds a min-heap, merges nodes, and generates codes via a recursive helper.
  * `encode(const string&)` — Converts text to a binary string using the generated code map.
  * `decode(const string&)` — Traverses the Huffman tree bit by bit to reconstruct the original text.
  * `printCodes()` — Displays each character’s Huffman code.
  * `compressionStats(const string&)` — Calculates and prints original vs. compressed bit sizes, compression ratio, and space saved.

* **`main()`**: Handles user input/output, calls the above methods in sequence, and verifies correctness.

## Data Structures and Design Choices

* **Priority Queue (`std::priority_queue`)**:

  * Min-heap of `shared_ptr<HuffmanNode>` uses `NodeCompare` to always extract the two nodes with lowest frequency in O(log n) time.

* **Shared Pointers (`std::shared_ptr`)**:

  * Manage dynamic memory for tree nodes automatically, avoiding manual `delete` calls.

* **Unordered Map (`std::unordered_map<char,string>`)**:

  * Stores the mapping from characters to their Huffman codes for O(1) lookup during encoding and statistics calculation.

* **Recursion**:

  * Employed in `generateCodes()` to traverse left/right subtrees and build binary code strings.

## Compression Efficiency

* **Original Size**: `N * 8` bits (where `N` is the length of the input string).
* **Compressed Size**: Sum of `frequency(ch) * codeLength(ch)` for all characters.
* **Compression Ratio**: `100 * (1 - compressedSize / originalSize)`

By tailoring code lengths to character frequencies, Huffman coding often achieves substantial savings on real-world text (e.g., English prose), typically in the range of 20–60% reduction depending on content entropy.

## Usage Example

plaintext
Enter Your Message: hello huffman
Huffman Codes:
' ' : 11
'a' : 101
'e' : 001
'f' : 000
'h' : 01
'l' : 100
'm' : 110
'n' : 111

Encoded Binary: 01 001 100 100 11 01 000000 101111  (spaces added for readability)
Decoded Text: hello huffman

--- Compression Statistics ---
Original Size: 112 bits
Compressed Size: 68 bits
Compression Ratio: 39.29%
Space Saved: 44 bits

Verification: Original and decoded texts match!