# huffman-coding

This C program implements the [huffman-coding](https://en.wikipedia.org/wiki/Huffman_coding) algorithm for encoding and 
decoding text files by creating variable-length codes for characters in a text file based on the probability of 
occurrence of each character.

## Usage

Compilation:
```bash
make -C ./src
```
The user can run the program with four different argument inputs:

1. Reads the data.txt file, calculates the probabilities of the first 128 characters of the ASCII table and prints them 
in the probfile.txt file.
```bash
./src/huffman -p ./data/data.txt ./data/probfile.txt
```

2. Reads the probabilities of each character form the probfile.txt file, creates the Huffman tree and prints the code 
for each character in codes.txt file and on the screen.
```bash
./src/huffman -s ./data/probfile.txt
```

3. Encodes the data.txt file using the Huffman tree and creates the encoded file data.txt.enc.
```bash
./src/huffman -e ./data/probfile.txt ./data/data.txt ./data/data.txt.enc
```

4. Decodes the data.txt.enc file using the Huffman tree and creates the decoded file data.txt.new.
```bash
./src/huffman -d ./data/probfile.txt ./data/data.txt.enc ./data/data.txt.new 
```

## Author

Giorgos Argyrides (g.aryrides@outlook.com)
