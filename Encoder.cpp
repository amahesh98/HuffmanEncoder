#include <iostream>

#include "Encoder.h"
#include <stdio.h>

Encoder::Encoder(string file_path){
    inputFile.open(file_path, ios::in | ios::binary);
    mh=new MinHeap();
    ht=new HuffTree();
}

//Fills up the frequency_table array where frequency_table[i]
//will contain the frequency of char with ASCII code i
void Encoder::buildFrequencyTable(){
    //char c=inputFile.get();
    unsigned char c=0;
    //char c=0;
    inputFile.read((char*)&c,1);
    //while(c!=-1){
    //while(inputFile.read((char*)&c,1)){
    while(!inputFile.eof()){
        //int c=inputFile.get();
        //cout<<c<<endl;
        frequency_table[c]++;
        //c=inputFile.get();
        inputFile.read((char*)&c,1);
    }
    /*
    for(int i=0; i<256; i++){
        if(frequency_table[i]==0){
            //cout<<(unsigned char)frequency_table[i]<<endl;
        }
    }
     */
    
}

//Builds the min head and run the encoding algorithm
void Encoder::encode(){
    unsigned char val;
    unsigned long freq;
    TreeNode*temp;
    for(int i=0; i<256; i++){
        if(frequency_table[i]!=0){
            freq=frequency_table[i];
            val=i;
            //cout<<val<<endl;
            //cout<<freq<<endl;
            temp=new TreeNode(val, freq);
            mh->insert(temp);
            uniqueChars.push_back(val);
        }
    }
//    cout<<"Unique Chars size: "<<ht->uniqueChars.size()<<endl;
//    for(int i=0; i<ht->uniqueChars.size(); i++){
//        cout<<ht->uniqueChars.at(i)<<endl;
//    }
    ht->buildTree(mh);
    ht->generateCodes(ht->getRoot(), 0);
}
void Encoder::writeEncodedFile(string output_file_path){
    
    //ofstream outputFile(output_file_path);
    //ofstream outputFile;
    outputFile.open(output_file_path, ios::out | ios::binary);
    //outputFile.open(output_file_path);
    //int nChars=ht->getSize();
    //string nChars=to_string(ht->uniqueChars.size());
    unsigned short nChars = uniqueChars.size();
    //cout<<"Casting: "<<(char*)&nChars<<endl;
    outputFile.write(reinterpret_cast<const char *>(&nChars), 2);

    //outputFile<<toBinary(ht->getSize(),2);
    //string currChar;
    //string currFreq;
    //cout<<"Size:"<<ht->uniqueChars.size()<<endl;
//    cout<<"nChars: "<<nChars<<endl;
    unsigned char currChar;
    unsigned long currFreq;
    for(int i=0; i<nChars; i++){
        ///cout<<nChars<<endl;
        //currChar=toBinary((int)ht->uniqueChars[i],1);
        //cout<<"count: "<<i<<endl;
        currChar=uniqueChars.at(i);
//        if(currChar==128){
//            cout<<"Here"<<endl;
//        }
        outputFile.write((char*)&currChar, 1);
        //outputFile.write(reinterpret_cast<const char *>(&currChar), 1);
        currFreq=frequency_table[(int)uniqueChars[i]];
        outputFile.write(reinterpret_cast<const char *>(&currFreq), 4);
                         
        //outputFile<<toBinary((int)ht->uniqueChars[i],1);
        //outputFile<<toBinary(frequency_table[(int)ht->uniqueChars[i]],4);
    }
    //cout<<"Testing"<<endl;
    inputFile.clear();
    inputFile.seekg(0, inputFile.beg);
    unsigned char c=inputFile.get();
    int counter=0;
    //cout<<c<<endl;
//    for(int i=0; i<256; i++){
//        cout<<ht->codes[i]<<endl;
//    }
    int nBits=0;
    unsigned char bit_buffer;
    string currCode;
    
    /*
    unsigned char xx=255;
    for(int j=0; j<100; j++){
         outputFile.write(reinterpret_cast<const char *>(&xx), 1);
    }
     */
    //while(c!=-1){
    
    while(!inputFile.eof()){
        //cout<<c<<endl;
        currCode=ht->getCharCode(c);
        for(int i=0; i<currCode.size(); i++){
            //cout<<"nBits: "<<nBits<<endl;
            bit_buffer=bit_buffer<<1;
            bit_buffer=bit_buffer | (currCode[i]-'0');
            nBits++;
            if(nBits==8){
                //outputFile.write((char*)&bit_buffer, sizeof(bit_buffer));
                outputFile.write(reinterpret_cast<const char *>(&bit_buffer), sizeof(bit_buffer));
                nBits=0;
                bit_buffer=0;
            }
        }
        //outputFile.write((const char*)&currCode, sizeof(currCode));
        //outputFile<<ht->getCharCode(c);
        //cout<<(char)c<<": "<<ht->getCharCode(c)<<endl;
        counter++;
        //cout<<counter<<endl;
        //if(counter==378){
            //cout<<"Here at error"<<endl;
        //}
        c=inputFile.get();
        //cout<<"Getting character after "<<counter<<endl;
    }
    if(nBits!=0 && nBits<8){
        bit_buffer=bit_buffer<<(8-nBits);
        outputFile.write(reinterpret_cast<const char *>(&bit_buffer), sizeof(bit_buffer));
        nBits=0;
        bit_buffer=0;
        //for(int i=nBits; i<8; i++){
            
        //}
    }
    inputFile.close();
    outputFile.close();
}
string Encoder::toBinary(int input, int nBytes){
    string output;
    for(int i=0; i<nBytes; i++){
        output+="00000000";
    }
    int count=0;
    while(input>0){
        output[output.size()-count-1]=input%2 + '0';
        count++;
        input=input/2;
    }
    //cout<<output<<endl;
    return output;
}

Encoder::~Encoder(){
    //delete[]frequency_table;
    delete mh;
    delete ht;
}


