#pragma once
#include <string>
#include <vector>
#include <map>
#include "structures.h"

/** @file */


/**
 * @brief The function encrypts the text from the file to another file with key
 * @param inputFile name of the file with plain text
 * @param outputFile name of the file to where the encrypted text should go to
 * @param keyFile name of the file with key to encrypt a text
 * @return doesn't return anything
*/

void encrypt(const std::string &inputFile, const std::string &outputFile, const std::string &keyFile);


/**
 * @brief The function decrypts the text from the file to another file with key
 * @param inputFile name of the file with plain text
 * @param outputFile name of the file to where the encrypted text should go to
 * @param keyFile name of the file with key to encrypt a text
 * @return doesn't return anything
*/

void decryptWithKey(const std::string &inputFile, const std::string &outputFile, const std::string &keyFile);


/**
 * @brief The function calculates the sum of the element-wise product of two maps with integer keys and double values
 * @param map1 container with letter frequency
 * @param map2 container with letter frequency
 * @return returns a double with the sum
*/

double sumProducts(const std::map<int, double>& map1, const std::map<int, double>& map2);

/**
 * @brief The function calculates the average of the sum of the squares of the frequency of characters in a vector
 * @param vecKeyLenFreqTable vector used to store the frequency od the characters in the encrypted text
 * @return returns a vector 
*/

double avgSumOfSquresFreq(const std::vector<chr>& vecKeyLenFreqTable);

/**
 * @brief The function builds a frequency table of characters for a given position in a vector of encrypted text.
 * @param encryptedTextVector the encrypted text
 * @param lengthOfKey length of the key
 * @param posOfKey the position of the key
 * @param unShiftVal not shifted value
 * @param stFreqTableCount reference to a structure that will hold the frequency table
 * @return doesn't return anything
*/

void buildKeyPosFreqTbl(const std::vector<int>& encryptedTextVector, int lengthOfKey, int posOfKey, int unShiftVal, chr& stFreqTableCount);

/**
 * @brief This function builds a frequency table for the encrypted text for each position of the key of length
 * @param encryptedTextVector vector of integers that represent the encrypted text
 * @param lengthOfKey key length
 * @param vecKeyLenFreqTable vector used to store the frequency od the characters in the encrypted text
 * @return doesn't return anything
*/
void buildKeyLenFreqTable(const std::vector<int>& encryptedTextVector, int lengthOfKey, std::vector<chr>& vecKeyLenFreqTable);


/**
 * @brief This function finds the length of a Vigenère cipher key
 * @param encryptedTextVector vector of integers that represent the encrypted text
 * @return the length of the key
*/

int findKeyLength(const std::vector<int>& encryptedTextVector);


/**
 * @brief The function is used to find the key used for the encryption of text in the input vector
 * @param encryptedTextVector vector of integers that represent the encrypted text
 * @param lengthOfKey key length
 * @param vecKeyText output vector that stores the calculated key text
 * @return true if the key is found successfully
*/

bool findKey(const std::vector<int>& encryptedTextVector, int lengthOfKey, std::vector<int>& vecKeyText);


/**
 * @brief The function performs a decryption operation on a vector of integers
 * @param encryptedText text to decrypt
 * @param vecKey vector of integers that serves as a key for the decryption process
 * @return doesn't return anything
*/

std::string decrypt(std::string& encryptedText, std::vector<int> vecKey);


/**
 * @brief The function decrypts a text from a file and outputs to a file
 * @param inputFile name of the file with encrypted text
 * @param outputFile name of the file to where the decrypted text should go
 * @return doesn't return anything
*/

void decryptWithoutKey(const std::string &inputFile, const std::string &outputFile);