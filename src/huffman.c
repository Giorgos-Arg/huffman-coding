/* 
 * @brief This program implements the Huffman algorithm for encoding and decoding text files by creating variable-length 
 * codes for characters in a text file based on the probability of occurrence of each character.
 *
 * The user can run the program with four different argument inputs:
 *
 * ./huffman -p data.txt probfile.txt
 * reads the data.txt file, calculates the probabilities of the first 128 characters of the ASCII table and prints them 
 * in the probfile.txt file.
 *
 * ./huffman -s probfile.txt
 * reads the probabilities of each character form the probfile.txt file, creates the Huffman tree and prints the code 
 * for each character in codes.txt file and on the screen.
 *
 * ./huffman -e probfile.txt data.txt data.txt.enc
 * encodes the data.txt file using the Huffman tree and creates the encoded file data.txt.enc.
 *
 * ./huffman -d probfile.txt data.txt.enc data.txt.new decodes the  data.txt.enc file using the Huffman tree and creates 
 * the decoded file data.txt.new.
 *
 *  @author Giorgos Argyrides
 */

#include "huffman.h"

int encode(char **huffmanTable, char **argv) {
	int i;
	char c;
	FILE *fp = NULL, *fpout = NULL;
	if ((fp = fopen(argv[3], "r")) == NULL ) {
		printf("\nError: Unable to open %s\n", argv[3]);
		return EXIT_FAILURE;
	}
	if ((fpout = fopen(argv[4], "w")) == NULL ) {
		printf("\nError: Unable to open %s\n", argv[4]);
		return EXIT_FAILURE;
	}
	while ((c = fgetc(fp)) != EOF) {
		i = (int) c;
		if (i > ASCII_LENGTH) {
			printf("\nError: %s file must only include characters >=0 and "
					"<= %d from the ASCII table!\n", argv[3], ASCII_LENGTH);
			return EXIT_FAILURE;
		}
		fprintf(fpout, "%s", huffmanTable[i]);
	}
	fclose(fp);
	fclose(fpout);
	return EXIT_SUCCESS;
}

int decode(TREE *huffmanTree, char **argv) {
	char c;
	NODE *root = huffmanTree->root;
	FILE *fp = NULL, *fpout = NULL;
	if ((fp = fopen(argv[3], "r")) == NULL ) {
		printf("\nError: Unable to open %s\n", argv[3]);
		return EXIT_FAILURE;
	}
	if ((fpout = fopen(argv[4], "w")) == NULL ) {
		printf("\nError: Unable to open %s\n", argv[4]);
		return EXIT_FAILURE;
	}
	while ((c = fgetc(fp)) != EOF) {
		if ((root->left == NULL )&& (root->right == NULL) ){
		fprintf(fpout, "%c",root->data);
		root = huffmanTree->root;
	}
	if(c == '0') {
		root = root->left;
	} else if (c == '1') {
		root = root->right;
	}
	else {
		printf("\nError! %s must only include 0 or 1\n",argv[3]);
		return EXIT_FAILURE;
	}
	}
	fprintf(fpout, "\n");
	fclose(fp);
	fclose(fpout);
	return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
	TREE *huffmanTree = NULL;
	float probs[ASCII_LENGTH];
	long int occur[ASCII_LENGTH] = { 0 };
	char **huffmanTable = NULL;
	huffmanTable = (char **) malloc(sizeof(char*) * ASCII_LENGTH);
	if (huffmanTable == NULL ) {
		printf("error in memory allocation\n");
		return EXIT_FAILURE;
	}
	if (strcmp(argv[1], "-p") == 0) { //  calculate probabilities
		if (argc != 4) {
			printf("\nError: wrong argument input!\n");
			exit(EXIT_FAILURE);
		}
		if (probabilities(argv, probs, occur) == EXIT_FAILURE){
			exit(EXIT_FAILURE);
		}
	} else if (strcmp(argv[1], "-s") == 0) { //  make Huffman tree
		if (argc != 3) {
			printf("\nError: wrong argument input!\n");
			exit(EXIT_FAILURE);
		}
		if (makeHuffmanTree(&huffmanTree, argv) == EXIT_FAILURE){
			exit(EXIT_FAILURE);
		}
		if (makeHuffmanTable(&huffmanTree, huffmanTable) == EXIT_FAILURE){
			exit(EXIT_FAILURE);
		}
		printHuffmanTable(huffmanTable);
		if (printFileHuffmanTable(huffmanTable) == EXIT_FAILURE){
			exit(EXIT_FAILURE);
		}
	} else if (strcmp(argv[1], "-e") == 0) { //  encode file
		if (argc != 5) {
			printf("\nError: wrong argument input!\n");
			exit(EXIT_FAILURE);
		}
		if (makeHuffmanTree(&huffmanTree, argv) == EXIT_FAILURE){
			exit(EXIT_FAILURE);
		}
		if (makeHuffmanTable(&huffmanTree, huffmanTable) == EXIT_FAILURE){
			exit(EXIT_FAILURE);
		}
		if (encode(huffmanTable, argv) == EXIT_FAILURE){
			exit(EXIT_FAILURE);
		}
	} else if (strcmp(argv[1], "-d") == 0) { //  decode file
		if (argc != 5) {
			printf("\nError: wrong argument input!\n");
			exit(EXIT_FAILURE);
		}
		if (makeHuffmanTree(&huffmanTree, argv) == EXIT_FAILURE){
			exit(EXIT_FAILURE);
		}
		if (makeHuffmanTable(&huffmanTree, huffmanTable) == EXIT_FAILURE){
			exit(EXIT_FAILURE);
		}
		if (decode(huffmanTree, argv) == EXIT_FAILURE){
			exit(EXIT_FAILURE);
		}
	} else {
		printf("\nError: wrong argument input!\n");
		exit(EXIT_FAILURE);
	}
	destroyHuffmanTable(huffmanTable);
	destroyTree(&huffmanTree);
	return 0;
}
