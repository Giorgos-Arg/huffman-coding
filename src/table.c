#include "table.h"

int makeHuffmanTable(TREE **huffmanTree, char **huffmanTable){
	if ((*huffmanTree) == NULL){
		printf("\nError: huffman tree is NULL\n");
		return EXIT_FAILURE;
	}
	if (huffmanTable == NULL){
		printf("\nError: huffman table is NULL\n");
		return EXIT_FAILURE;
	}
	char *s = NULL;
	s = (char *)malloc(sizeof(char) * ASCII_LENGTH);
	if (s == NULL){
		printf("Error in memory allocation!\n");
		return EXIT_FAILURE;
	}
	s[0] = '\0';
	recursiveHuffmanTable((*huffmanTree)->root, huffmanTable, s);
	free(s);
	return EXIT_SUCCESS;
}

void recursiveHuffmanTable(NODE *root, char **huffmanTable, char *s){
	if ((root->left == NULL) && (root->right == NULL)){
		int i = (int)(root->data);
		huffmanTable[i] = NULL;
		huffmanTable[i] = (char *)malloc(sizeof(char) * strlen(s) + 1);
		if (huffmanTable[i] == NULL){
			printf("Error in memory allocation!\n");
			exit(EXIT_FAILURE);
		}
		strcpy(huffmanTable[i], s);
		return;
	}
	strcat(s, "0");
	recursiveHuffmanTable(root->left, huffmanTable, s);
	int l = strlen(s);
	int j;
	for (j = l - 1; j >= 0; j--){
		if (s[j] == '0'){
			s[j] = '1';
			s[j + 1] = '\0';
			break;
		}
	}
	recursiveHuffmanTable(root->right, huffmanTable, s);
}

int printHuffmanTable(char **huffmanTable){
	int i;
	if (huffmanTable == NULL){
		printf("\nError: huffman table is NULL, nothing to be printed\n");
		return EXIT_FAILURE;
	}
	for (i = 32; i <= 126; i++){
		if (huffmanTable[i] == NULL){
			printf("\nError: huffman table[%d] is NULL,it can't be printed\n", i);
			return EXIT_FAILURE;
		}
		printf("\n%c : %s", (char)i, huffmanTable[i]);
	}
	printf("\n");
	return EXIT_SUCCESS;
}

int printFileHuffmanTable(char **huffmanTable){
	int i;
	FILE *fp = NULL;
	if (huffmanTable == NULL){
		printf("\nError: huffman table is NULL, nothing to be printed\n");
		return EXIT_FAILURE;
	}
	if ((fp = fopen("./data/codes.txt", "w")) == NULL){
		printf("\nError: Unable to open %s\n", "./data/codes.txt\n");
		return EXIT_FAILURE;
	}
	for (i = 0; i < ASCII_LENGTH; i++){
		if (huffmanTable[i] == NULL){
			printf("\nError: huffman table[%d] is NULL,it can't be printed\n", i);
			return EXIT_FAILURE;
		}
		fprintf(fp, "%s\n", huffmanTable[i]);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

void destroyHuffmanTable(char **huffmanTable){
	if (huffmanTable != NULL){
		int i;
		for (i = 0; i < ASCII_LENGTH; i++){
			if (huffmanTable[i] != NULL){
				free(huffmanTable[i]);
			}
		}
		free(huffmanTable);
	}
}
