#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include "probabilities.h"
#include "tree.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** @brief Encodes a text file given from the user using the Huffman table and creates the encoded text file.
 *
 *	Reads the characters one by one from a text file given from the user. For every character finds it's code from the 
 *  Huffman table and prints the code in a new text file.
 *
 *  @param huffmanTable a table with the codes of the first 128 characters of the ASCII table.
 *  @param argv the command-line argument array which will be used to open the files.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/

int encode(char **huffmanTable, char **argv);

/** @brief Decodes a text file given from the user using the Huffman tree and creates the decoded text file.
 *
 *	Reads the characters one by one from a text file given from the user. The text file must contain only the characters
 *  '0' and '1'. It starts from the root of the Huffman tree and moves right if it reads '1', left if it reads '0'. When 
 *  it reaches a terminal node it prints the character of that node in a new file and reads the next character starting 
 *  again from the root of the tree.
 *
 *  @param huffmanTree
 *  @param argv the command-line argument array which will be used to open the files.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/

int decode(TREE *huffmanTree, char **argv);

#endif /* HUFFMAN_H_ */
