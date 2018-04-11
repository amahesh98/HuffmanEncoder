#include <iostream>
#include "Decoder.h"

Decoder::Decoder(string huff_file_path){
    inputFile.open(huff_file_path, ios::in  | ios::binary);
    inputFilePath=huff_file_path;
    mh=new MinHeap();
    ht=new HuffTree();
    totalChars=0;
}

void Decoder::buildFrequencyTableFromFile(){
    unsigned int nUniqueChars;
    unsigned char val=0;
    unsigned char freq1=0;
    unsigned char freq2=0;
    unsigned char freq3=0;
    unsigned char freq4=0;
    unsigned long totalFreq=0;
    TreeNode*temp;
    inputFile.read((char*)&nUniqueChars, 2);
    for(int i=0; i<nUniqueChars; i++){
        totalFreq=0;
        inputFile.read((char*)&val, 1);
        
        inputFile.read((char*)&freq1, 1);
        totalFreq+=freq1;
        inputFile.read((char*)&freq2, 1);
        totalFreq+=freq2*256;
        inputFile.read((char*)&freq3, 1);
        totalFreq+=freq3*256*256;
        inputFile.read((char*)&freq4, 1);
        totalFreq+=freq4*256*256*256;
//        if(totalFreq==0){
//            cout<<i<<endl;
//            cout<<(int)val<<endl;
//        }
//
        totalChars+=totalFreq;
        frequency_table[val]=totalFreq;
        temp=new TreeNode(val, totalFreq);
        mh->insert(temp);
    }
    //inputFile.close();
}

void Decoder::decode(){
    ht->buildTree(mh);
    ht->generateCodes(ht->getRoot(),0);
//    for(int i=0; i<256; i++){
//        if(!ht->codes[i].empty()){
//            //cout<<(char)i<<": "<<ht->codes[i]<<endl;
//        }
//    }
}

void Decoder::writeUncompressedFile(string output_file_path){
 
    //inputFile.open(inputFilePath, ios::in | ios::binary);
    //inputFile.clear();
    //inputFile.seekg(0, inputFile.beg);
    
    
    
    unsigned char currentChar;
    string encodedChars;
    
    while(!inputFile.eof()){
        inputFile.read((char*)&currentChar,1);
        encodedChars+=currentChar;
    }
    /*
    int peeker=inputFile.peek();
    while(peeker!=EOF){
        inputFile.read((char*)&currentChar,1);
        //cout<<currentChar<<endl;
        encodedChars+=currentChar;
        peeker=inputFile.peek();
    }
     */
    
    //WORKING TILL HERE
    
    
    //inputFile.read((char*)&encodedChars, totalChars);
//    cout<<"encodedChars: "<<encodedChars<<endl;
    
    string encodedBinary = toBinary(encodedChars);
    
//    for(int i=50; i<60; i++){
//        cout<<encodedChars[i]<<": ";
//        for(int j=0; j<8; j++){
//            cout<<encodedBinary[8*i +j];
//        }
//        cout<<endl;
//    }
//    cout<<"encodedBinary: "<<encodedBinary<<endl;
    //unsigned char decodedChar;
    string encodedString;
    int decodedChar;
    string finalMessage;
//    cout<<encodedBinary.length()<<endl;
    for(int i=0; i<encodedBinary.length(); i++){
        encodedString+=encodedBinary[i];
//        cout<<"Encoded string: "<<encodedString<<endl;
        decodedChar=ht->getCharFromCode(encodedString);
//        cout<<"Decoded char: "<<decodedChar<<endl;
        if(decodedChar!=-1){
            //cout<<"DecodedChar: "<<(char)decodedChar<<" "<<decodedString<<endl;
            if(frequency_table[decodedChar]==0){
                //continue;
                break;
            }
            finalMessage+=(unsigned char)decodedChar;
            frequency_table[decodedChar]--;
            encodedString.clear();
        }
    }
    outputFile.open(output_file_path, ios::out | ios::binary);
    //cout<<"Final Message: "<<finalMessage<<endl;
    outputFile<<finalMessage;
    inputFile.close();
    outputFile.close();
}
string Decoder::toBinary(string input){
    string output;
    for(int i=0; i<input.length(); i++){
        output+=toBinary((char)input[i]);
    }
    return output;
}
string Decoder::toBinary(unsigned char input){
    string output="00000000";
    unsigned char inputDup=input;
    int counter=0;
    while(inputDup>0){
        output[7-counter]=inputDup%2+'0';
        counter++;
        inputDup=inputDup/2;
    }
    return output;
}
Decoder::~Decoder(){
    delete mh;
    delete ht;
}

