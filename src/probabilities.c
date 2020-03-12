#include "probabilities.h"

int probabilities(char **argv, float probs[ASCII_LENGTH], long int occur[ASCII_LENGTH]) {
	int i;
	long int total = 0;
	char c;
	FILE *fp = NULL, *fpout = NULL;
	if ((fp = fopen(argv[2], "r")) == NULL ) {
		printf("\nError: Unable to open %s\n", argv[2]);
		return EXIT_FAILURE;
	}
	while ((c = fgetc(fp)) != EOF) {
		i = (int) c;
		if (i > ASCII_LENGTH) {
			printf("\nError: %s file must only include characters >=0 and "
					"<= %d from the ASCII table!\n", argv[2], ASCII_LENGTH);
			return EXIT_FAILURE;
		}
		occur[i]++;
		total++;
	}
	if(total == 0){
		printf("\nError: %s is empty\n", argv[2]);
		return EXIT_FAILURE;
	}
	fclose(fp);
	if ((fpout = fopen(argv[3], "w")) == NULL ) {
		printf("\nError: Unable to open %s\n", argv[3]);
		return EXIT_FAILURE;
	}
	for (i = 0; i < ASCII_LENGTH; i++) {
		probs[i] = ((float) occur[i]) / total;
		fprintf(fpout, "%f\n", probs[i]);
	}
	fclose(fpout);
	return EXIT_SUCCESS;
}
