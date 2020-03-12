#ifndef TABLE_H_
#define TABLE_H_

/* included libraries */
#include "probabilities.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Function prototypes */

/** @brief Makes the Huffman table.
 *
 *  Given the Huffman tree it makes a table with a code(string of 0's and 1's) for each one of the first 128 characters 
 *  of the ASCII table.
 *
 *  @param huffmanTree the Huffman tree which will be used to create the Huffman table.
 *  @param huffmanTable the Huffman table to be created.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int makeHuffmanTable(TREE **huffmanTree, char **huffmanTable);

/** @brief A recursive function for creating codes for each one of the first 128 characters of the ASCII table using the
 *  Huffman tree.
 *
 *	Given the root of the Huffman tree it moves right and left in the tree until it goes through all the nodes. When is 
 *  moves left it adds a '0' in the code, when it moves right it replaces the last zero of the code with '1' and sets 
 *  the next character of the code as nul. When it reaches a terminal node it copies the code of the character of that 
 *  node in the Huffman table.
 *
 *  @param root the root of the Huffman tree.
 *  @param huffmanTable the Huffman table to be created.
 *  @param s the string where the code for every character will be calculated.
 *
 *  @return void
 **/
void recursiveHuffmanTable(NODE *root, char **huffmanTable, char *s);

/** @brief Prints a Huffman table.
 *
 *	It prints the characters between 33 and 126 in the ASCII table (printable characters) and their codes from the 
 *  Huffman table.
 *
 *  @param huffmanTable the Huffman table to be printed.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int printHuffmanTable(char **huffmanTable);

/** @brief Prints a Huffman table in a file.
 *
 *	It prints the codes of the first 128 characters in the ASCII table form the Huffman table.
 *
 *  @param huffmanTable the Huffman table to be printed.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int printFileHuffmanTable(char **huffmanTable);

/** @brief Destroys a Huffman table.
 *
 *	It destroys (frees) all the codes of the huffman table and then destroys (frees) the table.
 *
 *  @param huffmanTable the table to be destroyed.
 *  @return void
 **/
void destroyHuffmanTable(char **huffmanTable);

#endif /* TABLE_H_ */
