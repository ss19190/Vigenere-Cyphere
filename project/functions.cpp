#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <regex>
#include <map>
#include <vector>
#include <cctype>
#include "functions.h"
#include "structures.h"

void encrypt(const std::string &inputFile, const std::string &outputFile, const std::string &keyFile)
{
    std::string plaintext;
    std::ifstream input(inputFile);
    if (input)
        std::getline(input, plaintext, '\0');

    std::string key;
    std::ifstream key_file(keyFile);
    if (key_file)
        std::getline(key_file, key, '\0');

    if(key.length() == 0){
        std::cout << "Key file is empty";
        return;
    }

    key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());

    for (char &x : key)
        if(!isalpha(x))
            x = 'A';


    std::string encryptedText = "";
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);
    bool upper = true;
    for (int i = 0, j = 0; i < plaintext.length(); i++)
    {
        char c = plaintext[i];
        if (c >= 'A' && c <= 'Z')
        {
            if(!upper){
                std::transform(key.begin(), key.end(), key.begin(), ::toupper);
                upper = true;
            }
            encryptedText += (char)((c + key[j] - 2 * 'A') % 26 + 'A');
            ++j %= key.length();
        }
        else if(c >= 'a' && c <= 'z'){
            if(upper){
                std::transform(key.begin(), key.end(), key.begin(), ::tolower);
                upper = false;
            }
            encryptedText += (char)((c + key[j] - 2 * 'a') % 26 + 'a');
            ++j %= key.length();
        }
        else
        {
            encryptedText += c;
        }
    }
    std::ofstream output_file(outputFile);
    if (output_file)
        output_file << encryptedText;
    output_file.close();
}

void decryptWithKey(const std::string &inputFile, const std::string &outputFile, const std::string &keyFile)
{
    std::string encryptedText;
    std::ifstream input(inputFile);
    if (input)
        std::getline(input, encryptedText, '\0');

    std::string key;
    std::ifstream key_file(keyFile);
    if (key_file)
        std::getline(key_file, key, '\0');
        
    if(key.length() == 0){
        std::cout << "Key file is empty";
        return;
    }

    key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());

    for (char &x : key)
        if(!isalpha(x))
            x = 'A';

    std::string decryptedText = "";
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);
    for (int i = 0, j = 0; i < encryptedText.length(); i++)
    {
        char c = encryptedText[i];
        if (c >= 'A' && c <= 'Z')
        {       
            decryptedText += (char)((c - key[j] + 26) % 26 + 'A');
            ++j %= key.length();
        }
        else if(c >= 'a' && c <= 'z'){
            decryptedText += (char)((c - key[j] + 'A' - 'a' + 26) % 26 + 'a');
            ++j %= key.length();
        }
        else
        {
            decryptedText += c;
        }
    }
    std::ofstream output_file(outputFile);
    if (output_file)
        output_file << decryptedText;
    output_file.close();
}

const int firstLetterA = 'A';
const int lastLetterZ = 'Z';
std::map<int, double> freqOfLetters = {
    {'E', 12.702}, {'T', 9.056}, {'A', 8.167}, {'O', 7.507}, {'I', 6.966}, {'N', 6.749}, {'S', 6.327},
    {'H', 6.094}, {'R', 5.987}, {'D', 4.253}, {'L', 4.025}, {'C', 2.782}, {'U', 2.752}, {'M', 2.406},
    {'W', 2.360}, {'F', 2.228}, {'G', 2.015}, {'Y', 1.974}, {'P', 1.929}, {'B', 1.492}, {'V', 0.978},
    {'K', 0.772}, {'J', 0.153}, {'X', 0.150}, {'Q', 0.095}, {'Z', 0.074}
};

double sumProducts(const std::map<int, double>& map1, const std::map<int, double>& map2){
    const std::map<int, double>* pmap1 = &map1;
    const std::map<int, double>* pmap2 = &map2;
    if(map1.size() > map2.size())
        std::swap(pmap1,pmap2);
    double sumProductsDouble = 0;
    for (std::map<int, double>::const_iterator itr1 = pmap1->begin(); itr1 != pmap1->end(); itr1++)
    {
        std::map<int, double>::const_iterator itr2 = pmap2->find(itr1->first);
        if (itr2 != pmap2->end())
            sumProductsDouble += (itr1->second * itr2->second);
    }
    return sumProductsDouble;
}

double avgSumOfSquresFreq(const std::vector<chr>& vecKeyLenFreqTable)
{
    int posOfKey = 0;
    double dChrSSFreqTot = 0;
    for (std::vector<chr>::const_iterator itrFreqTblCount = vecKeyLenFreqTable.begin();
        itrFreqTblCount != vecKeyLenFreqTable.end(); itrFreqTblCount++)
    {
        double sumOfSqauresDouble = 0;
        for (auto itrCount = itrFreqTblCount->mapChrTable.begin();
            itrCount != itrFreqTblCount -> mapChrTable.end(); itrCount++)
        {
            double dChrFreq = (double)itrCount->second / itrFreqTblCount->nChrTotal;
            sumOfSqauresDouble += (dChrFreq * dChrFreq);
        }
        dChrSSFreqTot += sumOfSqauresDouble;
    }
    double dAvgSumFreqTot = dChrSSFreqTot / vecKeyLenFreqTable.size(); 


    return dAvgSumFreqTot;
}

void buildKeyPosFreqTbl(const std::vector<int>& encryptedTextVector, int lengthOfKey, int posOfKey, int unShiftVal, chr& stFreqTableCount)
{
    int nTmpKeyLen = lengthOfKey;
    int c1;
    
    for (std::vector<int>::const_iterator itrEncryptedText = encryptedTextVector.begin() + posOfKey;
        itrEncryptedText != encryptedTextVector.end(); std::advance(itrEncryptedText, nTmpKeyLen))
    {
        int c = *itrEncryptedText;
        if (unShiftVal != 0)
        {
            
            int nNoPostShift = unShiftVal - firstLetterA;
            c = *itrEncryptedText - nNoPostShift;
            if (c > lastLetterZ) c = firstLetterA + (c - lastLetterZ - 1);
        }


        std::map<int, int>::iterator itrFreqCount = stFreqTableCount.mapChrTable.find(c);
        if (itrFreqCount != stFreqTableCount.mapChrTable.end())
        {
            itrFreqCount->second++;
        }
        else
        {
            stFreqTableCount.mapChrTable.insert(std::make_pair(c, 1));
        }
        stFreqTableCount.nChrTotal++;


        int nIndex = distance(std::vector<int>::const_iterator(encryptedTextVector.end()), itrEncryptedText);
        if (nTmpKeyLen > abs(nIndex)) nTmpKeyLen = abs(nIndex);
    }
}

void buildKeyLenFreqTable(const std::vector<int>& encryptedTextVector, int lengthOfKey, std::vector<chr>& vecKeyLenFreqTable)
{
    for (int posOfKey = 0; posOfKey < lengthOfKey; posOfKey++)
    {
        chr stFreqTableCount;
        stFreqTableCount.mapChrTable.clear();
        stFreqTableCount.nChrTotal = 0;


        buildKeyPosFreqTbl(encryptedTextVector, lengthOfKey, posOfKey, 0, stFreqTableCount);


        vecKeyLenFreqTable.push_back(stFreqTableCount);
    }
}

int findKeyLength(const std::vector<int>& encryptedTextVector)
{
    int lengthOfKey = 0;

    std::map<int, std::vector<chr>> mapTotFereqTable;


    for (int lengthOfKey = 1; lengthOfKey <= 9; lengthOfKey++)
    {
        std::vector<chr> vecKeyLenFreqTable;
        vecKeyLenFreqTable.clear();


        buildKeyLenFreqTable(encryptedTextVector, lengthOfKey, vecKeyLenFreqTable);


        mapTotFereqTable.insert(std::make_pair(lengthOfKey, vecKeyLenFreqTable));
    }


    double dEnglishSigmaSquare = sumProducts(freqOfLetters, freqOfLetters) / 10000;


    for (std::map<int, std::vector<chr>>::const_iterator itrLenFreq = mapTotFereqTable.begin();
        itrLenFreq != mapTotFereqTable.end(); itrLenFreq++)
    {


        double dAvgSumFreqTot = avgSumOfSquresFreq(itrLenFreq->second);

        if (dAvgSumFreqTot > dEnglishSigmaSquare)
            lengthOfKey = itrLenFreq->first;
    }

    return lengthOfKey;
}

bool findKey(const std::vector<int>& encryptedTextVector, int lengthOfKey, std::vector<int>& vecKeyText)
{
    double dEngSumSquare = sumProducts(freqOfLetters, freqOfLetters) / 10000;


    for (int i = 0; i < lengthOfKey; i++)
    {
        int B = firstLetterA;
        for (B = firstLetterA; B <= lastLetterZ; B++)
        {
            chr stChrTblCnt;
            stChrTblCnt.mapChrTable.clear();
            stChrTblCnt.nChrTotal = 0;


            buildKeyPosFreqTbl(encryptedTextVector, lengthOfKey, i, B, stChrTblCnt);


            std::map<int, double> mapundChrFreqTblCnt;
            for( std::map<int, int>::iterator itrChrTbl = stChrTblCnt.mapChrTable.begin();
                itrChrTbl != stChrTblCnt.mapChrTable.end(); itrChrTbl++)
            {
                mapundChrFreqTblCnt.insert(
                    std::make_pair(itrChrTbl->first, ((double)itrChrTbl->second * 100/ stChrTblCnt.nChrTotal))
                );
            }


            double dEnchSumSquare = sumProducts(freqOfLetters, mapundChrFreqTblCnt) / 10000;

            if (dEnchSumSquare > 0.05)
                break;
        }


        if (B <= lastLetterZ){
            vecKeyText[i] = B;
        }
            
    }
    return true;
}

std::string decrypt(std::string& encryptedText, std::vector<int> vecKey)
{
    std::string key;
    for(int x : vecKey){
        key += (char)x;
    }
    std::string decryptedText = "";
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);
    for (int i = 0, j = 0; i < encryptedText.length(); i++)
    {
        char c = encryptedText[i];
        if (c >= 'A' && c <= 'Z')
        {
            decryptedText += (char)((c - key[j] + 26) % 26 + 'A');
            ++j %= key.length();
        }
        else if(c >= 'a' && c <= 'z'){
            decryptedText += (char)((c - key[j] + 'A' - 'a' + 26) % 26 + 'a');
            ++j %= key.length();
        }
        else
        {
            decryptedText += c;
        }
    }
    return decryptedText;

}

void decryptWithoutKey(const std::string &inputFile, const std::string &outputFile){

    std::string encryptedText;
    std::ifstream input(inputFile);
    if (input)
        std::getline(input, encryptedText, '\0');

    std::string encryptedTextCopy = encryptedText;

    std::transform(encryptedText.begin(), encryptedText.end(), encryptedText.begin(), ::toupper);

    std::string encryptedTextOnlyLetters = "";

    for (char c : encryptedText){
        if(isalpha((int)c))
            encryptedTextOnlyLetters += c;
    }

    std::vector<int> EncryptedTextVecToDecrypt(encryptedTextOnlyLetters.begin(), encryptedTextOnlyLetters.end());
    
    int keyLength = findKeyLength(EncryptedTextVecToDecrypt);

    if(keyLength == 0){
        std::cout << "Key was not found";
        std::ofstream output_file(outputFile);
        if (output_file)
            output_file << "Key was not found for text:\n\n" << encryptedText;
        output_file.close();
        return;
    }

    std::vector<int> vecKey;
    vecKey.resize(keyLength);
    bool bRet = findKey (EncryptedTextVecToDecrypt, keyLength, vecKey);

    std::string textToFile = decrypt(encryptedTextCopy, vecKey);

    std::ofstream output_file(outputFile);
    if (output_file)
        output_file << textToFile;
    output_file.close();

}