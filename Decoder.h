#ifndef DECODER_H
#define DECODER_H
#include <fstream>

#include <string>
#include "MinHeap.h"
#include "TreeNode.h"
#include "HuffTree.h"

using namespace std;



class Decoder
{
	private:
		unsigned long frequency_table[256];
        ifstream inputFile;
        ofstream outputFile;
        MinHeap*mh;
        HuffTree*ht;
        string inputFilePath;
        unsigned long totalChars;
        string toBinary(unsigned char input);
		// You need to add more class memeber and methods

	public:
		//huff_file_path is the input (encoded) file that we 
		//want to decode
		Decoder(string huff_file_path);

		//Fills up the frequency_table array where frequency_table[i] 
		//will contain the frequency of char with ASCII code i			
		//This method will read the header of the encoded file to 
		//extract the chars and their frequency
		void buildFrequencyTableFromFile();

		//Creates a min-heap and builds the Huffman tree
		void decode();

		//Writes the uncompressed file and save it as file_path
		void writeUncompressedFile(string output_file_path);
        string toBinary(string input);

		~Decoder();

};

#endif
