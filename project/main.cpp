/**
 * @file main.cpp
 * @author Sara Sobstyl
 * @brief Vigeneré project
 * @version 1.0
 * @date 2023-02-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <cstring>
#include <string>
#include "functions.h"
#include "structures.h"

int main(int argc, char const *argv[])
{

    if(argc == 1){
        std::cout << "You didn't provide any arguments\nUse --en in case of encrypting\nUse --de in case of decrypting with key\nUse --br in case of decrypting without they key";
    }
    if(!strcmp(argv[1],"--en"))
    {
        std::string inputFile, outputFile, keyFile;
        if(argc > 8){
            std::cout << "Too many arguments for this command\n\nUse:\n-i <input_file> for input file\n-o <output_file> for output file\n-k <key_file> for key file\nKey can contain only letters";
        }else if(argc < 8)
            std::cout << "Too few arguments for this command\n\nUse:\n-i <input_file> for input file\n-o <output_file> for output file\n-k <key_file> for key file\nKey can contain only letters"; 
        else{
            for(int i = 2; i < argc; i += 2){
                if(!strcmp(argv[i], "-i"))
                    inputFile = argv[i + 1];
                else if(!strcmp(argv[i], "-o"))
                    outputFile = argv[i + 1];
                else if(!strcmp(argv[i], "-k"))
                    keyFile = argv[i + 1];
                else 
                    std::cout << "Unknown switch: " << argv[i] << "\n\nUse:\n-i <input_file> for input file\n-o <output_file> for output file\n-k <key_file> for key file";
            }
        }
        encrypt(inputFile, outputFile, keyFile);
    }else if(!strcmp(argv[1], "--de")){
        std::string inputFile, outputFile, keyFile;
        if(argc > 8){
            std::cout << "Too many arguments for this command\n\nUse:\n-i <input_file> for input file\n-o <output_file> for output file\n-k <key_file> for key file";
        } else if(argc < 8)
            std::cout << "Too few arguments for this command\n\nUse:\n-i <input_file> for input file\n-o <output_file> for output file\n-k <key_file> for key file"; 
        else{
            for(int i = 2; i < argc; i += 2){
                if(!strcmp(argv[i], "-i"))
                    inputFile = argv[i + 1];
                else if(!strcmp(argv[i], "-o"))
                    outputFile = argv[i + 1];
                else if(!strcmp(argv[i], "-k"))
                    keyFile = argv[i + 1];
                else 
                    std::cout << "Unknown switch: " << argv[i] << "\n\nUse:\n-i <input_file> for input file\n-o <output_file> for output file\n-k <key_file> for key file";
            }
        } 
        decryptWithKey(inputFile, outputFile, keyFile);
    }else if(!strcmp(argv[1], "--br")){
        std::string inputFile, outputFile;
        if(argc > 6){
            std::cout << "Too many arguments for this command\n\nUse:\n-i <input_file> for input file\n-o <output_file> for output file";
        } else if(argc < 6)
            std::cout << "Too few arguments for this command\n\nUse:\n-i <input_file> for input file\n-o <output_file> for output file";
        else{
            for(int i = 2; i < argc; i += 2){
                if(!strcmp(argv[i], "-i"))
                    inputFile = argv[i + 1];
                else if(!strcmp(argv[i], "-o"))
                    outputFile = argv[i + 1];
                else
                    std::cout << "Unknown switch: " << argv[i] << "\n\nUse:\n-i <input_file> for input file\n-o <output_file> for output file";
            }
        decryptWithoutKey(inputFile, outputFile);
        }
    } else
        std::cout << "Unknown command\nUse --en in case of encrypting\nUse --de in case of decrypting with key\nUse --br in case of decrypting without they key";
    
    return 0;
}