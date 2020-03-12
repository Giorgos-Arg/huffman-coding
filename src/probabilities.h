#ifndef PROBABILITIES_H_
#define PROBABILITIES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_LENGTH 128

/** @brief Reads the characters from a text file , calculates the probability of occurrence of each characters and 
 *  prints the probabilities in a new file.
 *
 * Reads the characters in a text file given from the user, calculates the probabilities of occurrence of the first 128 
 * characters of the ASCII table and prints them in a new file.
 *
 *  @param argv the command-line argument array which will be used to open the files.
 *  @param probs the array with the probabilities of the first 128 characters of the ASCII table.
 *  @param occur the array with the occurrences of the first 128 characters of the ASCII table.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int probabilities(char **argv, float probs[ASCII_LENGTH], long int occur[ASCII_LENGTH]);

#endif /* PROBABILITIES_H_ */
