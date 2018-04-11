#include <iostream>
#include <string>
#include "MinHeap.h"
#include "Encoder.h"
#include "Decoder.h"

using namespace std;

void printHelp(){
	cout << "Invalid arguments." << endl;
	cout << "Type \"huffman [mode] [arguments]\" where mode and its arguments are one of the following:" << endl;
	cout << "-e [src] [dest]: encode the source file and place the result into the specified destination" << endl;
	cout << "-d [src] [dest]: decode the source file and place the result into the specified destination" << endl;
	exit(1);
}


int main (int argc, char** argv){
	//printHelp();
    string mode=argv[1];
    string inputFile=argv[2];
    string outputFile=argv[3];
    if(mode=="-e"){
        Encoder*e1=new Encoder(inputFile);
        e1->buildFrequencyTable();
        e1->encode();
        e1->writeEncodedFile(outputFile);
        delete e1;
    }
    else if(mode=="-d"){
        Decoder*d1 = new Decoder(inputFile);
        d1->buildFrequencyTableFromFile();
        d1->decode();
        d1->writeUncompressedFile(outputFile);
        delete d1;
    }
    else{
        cout<<"Error. Format not recognized."<<endl;
    }
	return 0;
}
