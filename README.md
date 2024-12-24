# Huffman Algorithm in C++

This project implements the **Huffman Coding algorithm** in C++ for efficient lossless data compression. Huffman Coding is a widely-used technique that reduces the size of data by encoding characters with variable-length codes based on their frequencies.

## Features

- **Frequency Table**: Builds a frequency table from the input data.
- **Huffman Tree**: Constructs the Huffman tree using a priority queue.
- **Encoding**: Encodes text files using Huffman codes.
- **Decoding**: Decodes compressed data back to its original form.

## How It Works

1. **Build Frequency Table**: The algorithm starts by analyzing the frequency of each character in the input text.
2. **Create Huffman Tree**: A binary tree is constructed where each leaf node represents a character, and the tree is built based on character frequencies.
3. **Generate Codes**: Shorter codes are assigned to more frequent characters, and longer codes to less frequent ones.
4. **Compress and Decompress**: The input text is then compressed and can later be decompressed using the same Huffman tree.

## Usage

To run the project:

1. Clone this repository:
   ```bash
   git clone https://github.com/Ma7moud-Mansour/Huffman-Algorithm.git

