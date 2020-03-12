#include "tree.h"

int initTree(TREE** tree) {
	(*tree) = (TREE *) malloc(sizeof(TREE));
	if ((*tree) == NULL ) {
		printf("error in memory allocation!\n");
		return EXIT_FAILURE;
	}
	(*tree)->prob = 0;
	(*tree)->root = NULL;
	(*tree)->root = (NODE *) malloc(sizeof(NODE));
	if ((*tree)->root == NULL ) {
		printf("error in memory allocation!\n");
		return EXIT_FAILURE;
	}
	(*tree)->root->data = 0;
	(*tree)->root->left = NULL;
	(*tree)->root->right = NULL;
	return EXIT_SUCCESS;
}

int initTreeTable(TREETABLE **table, char **argv) {
	int i, err;
	float prob = 1;
	FILE *fp = NULL;
	(*table) = (TREETABLE *) malloc(sizeof(TREETABLE));
	if ((*table) == NULL ) {
		printf("error in memory allocation!\n");
		return EXIT_FAILURE;
	}
	(*table)->size = 0;
	(*table)->slot = NULL;
	(*table)->slot = (TREE **) malloc(sizeof(TREE *) * ASCII_LENGTH);
	if ((*table)->slot == NULL ) {
		printf("error in memory allocation!\n");
		return EXIT_FAILURE;
	}
	if ((fp = fopen(argv[2], "r")) == NULL ) {
		printf("\nError: Unable to open %s\n", argv[2]);
		return EXIT_FAILURE;
	}
	for (i = 0; i < ASCII_LENGTH; i++) {
		(*table)->slot[i] = NULL;
		if (initTree(&((*table)->slot[i])) == EXIT_FAILURE) {
			printf("error at initializing tree!\n");
			return EXIT_FAILURE;
		}
		if ((err = fscanf(fp, "%f", &prob)) != 1) {
			printf("error reading probabilities from file\n");
			return EXIT_FAILURE;
		}
		if(prob > 1 || prob < 0){
			printf("\nError in probabilities file. Probability must be between 0 and 1\n");
			return EXIT_FAILURE;
		}
		(*table)->slot[i]->prob = prob;
		(*table)->slot[i]->root->data = (char) i;
		((*table)->size)++;
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int mergeTrees(TREE **tree1, TREE **tree2) {
	TREE *tree = NULL;
	if (tree1 == NULL || tree2 == NULL ) {
		printf("error: tree is NULL\n");
		return EXIT_FAILURE;
	}
	if (initTree(&tree) == EXIT_FAILURE){
		return EXIT_FAILURE;
	}
	tree->prob = (*tree1)->prob + (*tree2)->prob;
	tree->root->left = (*tree1)->root;
	tree->root->right = (*tree2)->root;
	(*tree1)->prob = tree->prob;
	(*tree1)->root = tree->root;
	free(tree);
	return EXIT_SUCCESS;
}

int makeHuffmanTree(TREE **huffmanTree, char **argv) {
	int tree1, tree2, i;
	float prob1, prob2;
	TREETABLE *table = NULL;
	if (initTree(huffmanTree) == EXIT_FAILURE) {
		printf("error at initializing Huffman tree!\n");
		return EXIT_FAILURE;
	}
	if (initTreeTable(&table, argv) == EXIT_FAILURE) {
		printf("error at initializing tree table!\n");
		return EXIT_FAILURE;
	}
	while (table->size > 1) {
		// find the two trees with the lowest probability
		prob1 = (table->slot[0]->prob);
		prob2 = (table->slot[1]->prob);
		tree1 = 0;
		tree2 = 1;
		if (prob2 < prob1) {
			prob1 = (table->slot[1]->prob);
			prob2 = (table->slot[0]->prob);
			tree1 = 1;
			tree2 = 0;
		}
		for (i = 2; i < table->size; i++) {
			if ((table->slot[i]->prob) < prob1) {
				prob2 = prob1;
				tree2 = tree1;
				prob1 = (table->slot[i]->prob);
				tree1 = i;

			} else if ((table->slot[i]->prob) < prob2) {
				prob2 = (table->slot[i]->prob);
				tree2 = i;
			}
		}
		// merge trees
		if (mergeTrees(&(table->slot[tree1]),
				&(table->slot[tree2]))== EXIT_FAILURE) {
			printf("error at merging trees!\n");
			return EXIT_FAILURE;
		}
		// append tree2 at the end of the table
		TREE *tmp = table->slot[tree2];
		table->slot[tree2] = table->slot[table->size - 1];
		table->slot[table->size - 1] = tmp;
		free(table->slot[table->size - 1]);
		(table->size)--;
	}
	free((*huffmanTree)->root);
	(*huffmanTree)->root = table->slot[0]->root;
	free(table->slot[0]);
	free(table->slot);
	free(table);
	return EXIT_SUCCESS;
}

void printTree(NODE *root) {
	if (root == NULL ){
		return;
	}
	if ((root->left == NULL )&& (root->right == NULL) ){
		if ((root->data >= ((char) 33)) && (root->data <= ((char) 126))) {
			printf("%c ", root->data);
		}
	}
	printTree(root->left);
	printTree(root->right);
}

void destroyTree(TREE **tree) {
	if ((*tree) != NULL ) {
		destroyTreeNodes((*tree)->root);
		free(*tree);
	}
}

void destroyTreeNodes(NODE *root) {
	if (root != NULL ) {
		destroyTreeNodes(root->left);
		destroyTreeNodes(root->right);
		free(root);
	}
}

#ifdef DEBUG

static void tester(TREE **tree1, TREE **tree2, TREE **tree3) {

	initTree(tree1);
	initTree(tree2);
	initTree(tree3);
	(*tree1)->root->data = 'a';
	(*tree2)->root->data = 'b';
	(*tree3)->root->data = 'c';
	mergeTrees(tree1, tree2);
	mergeTrees(tree1, tree3);
	printTree((*tree1)->root);
	printf("\n");
	destroyTree(tree1);
	destroyTree(tree2);
	destroyTree(tree3);
}

int main() {
	TREE *tree1 = NULL, *tree2 = NULL, *tree3 = NULL;
	tester(&tree1, &tree2, &tree3);
	return 0;
}
#endif

