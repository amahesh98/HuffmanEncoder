#ifndef ENCODER_H
#define ENCODER_H


#include <string>
#include <iostream>
#include <fstream>
#include "TreeNode.h"
#include "MinHeap.h"
#include "HuffTree.h"

using namespace std;

class Encoder
{
	private:
        MinHeap*mh;
		unsigned long frequency_table[256];
		ifstream inputFile;
        HuffTree*ht;
        ofstream outputFile;
    vector<unsigned char> uniqueChars;
		// You need to add more class memeber and methods
	public:
		//test_file_path is the input (decoded) file
    
        Encoder(string file_path);
        void buildFrequencyTable();
        void encode();
		//Generates the encoded file and save it as output_file_path
        void writeEncodedFile(string output_file_path);
        string toBinary(int input, int nBytes);
		~Encoder();
};

#endif
