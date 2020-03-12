/* 
 * @author Giorgos Argyrides
 */
#ifndef TREE_H_
#define TREE_H_

#include "probabilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char data;
	struct node *left;
	struct node *right;
} NODE;

typedef struct {
	NODE *root;
	float prob;
} TREE;

typedef struct {
	TREE **slot;
	int size;
} TREETABLE;

/** @brief initializes a tree.
 *
 *	Allocates memory for the tree and its root and initializes its fields.
 *
 *  @param tree the tree to be initialized.
 *
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int initTree(TREE** tree);

/** @brief initializes a table of trees.
 *
 *	Allocates memory for 128 trees. In each tree root its saved one of the
 *	first 128 characters of the ASCII table and its probability read from the
 *	probability file.
 *
 *  @param table the tree table to be initialized.
 *  @param argv the command-line argument array which will be used to open
 *  the files.
 *
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int initTreeTable(TREETABLE **table, char **argv);

/** @brief makes the Huffman tree.
 *
 *	Finds the two trees with the lowest probability in the tree table and merges
 *	them until there is only 1 tree in the table. That tree is the Huffman tree
 *	which will be used to encode and decode files.
 *
 *  @param huffmanTree the Huffman tree.
 *  @param argv the command-line argument array which will be used to open
 *  the files.
 *
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int makeHuffmanTree(TREE **huffmanTree, char **argv);

/** @brief merges two trees.
 *
 *	Creates a new tree and sets the two trees to be merged as its siblings.
 *	The probability of the new tree is the sum of the probabilities of the other
 *	two trees. Then the first tree is marked as the new tree.
 *
 *  @param tree1 the first tree to be merged with the second tree and be marked
 *  as the new tree.
 *  @param tree2 the second tree to be merged with the first tree.
 *
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int mergeTrees(TREE **tree1, TREE **tree2);

/** @brief prints a tree.
 *
 * 	Given the root of a tree it prints the characters between 33 and 126 in
 * 	the ASCII table (printable characters) of the terminal roots of the tree.
 *
 *  @param root the root of the tree to be printed.
 *
 *  @return void
 **/
void printTree(NODE *root);

/** @brief destroys a tree.
 *
 * 	Calls the destroyTreeNodes function to free all the nodes of the tree and
 * 	then destroys (frees) the tree.
 *
 *  @param tree the tree to be destroyed.
 *
 *  @return void
 **/
void destroyTree(TREE **tree);

/** @brief destroys all the Nodes of a tree.
 *
 * 	Destroys (free) all the nodes of a tree.
 *
 *  @param root the root of the tree to be destroyed.
 *
 *  @return void
 **/
void destroyTreeNodes(NODE *root);


#endif /* TREE_H_ */
