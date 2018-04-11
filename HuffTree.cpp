#include <iostream>
#include "HuffTree.h"



HuffTree::HuffTree(){
    //char a='b';
    //root=new TreeNode(a, 10);
    count=0;
    }

void HuffTree::buildTree(MinHeap*mh){
    int c=-1;
    TreeNode*node1;
    TreeNode*node2;
    TreeNode*tNew;
    while(mh->getSize()>1){
            node1=mh->removeMin();
       //cout<<"Remove 1: "<<(unsigned char)node1->getVal()<<" "<<node1->getFrequency()<<endl;

            node2=mh->removeMin();
        //cout<<"Remove 2: "<<(unsigned char)node2->getVal()<<" "<<node2->getFrequency()<<endl;
            //int c=-1
            tNew = new TreeNode(c,node1->getFrequency()+node2->getFrequency());
        //cout<<"New node value: "<<tNew->getFrequency()<<endl;
            tNew->setHuffLeft(node1);
        //left=node1;
        //cout<<"Left: "<<tNew->getHuffLeft()->getFrequency()<<endl;
            tNew->setHuffRight(node2);
        //right=node2;
        //cout<<"Right: "<<tNew->getHuffRight()->getFrequency()<<endl;
            mh->insert(tNew);
        //theTree.push_back(node1);
        //theTree.push_back(node2);
        //removedNodes.push_back(node1);
        //removedNodes.push_back(node2);
    }
    TreeNode*tLast=mh->removeMin();
    //tLast->setLeft(left);
    //tLast->setRight(right);
    //cout<<"Final Node: "<<tLast->getFrequency()<<endl;
    root=tLast;
   // cout<<"Root Freq: "<<root->getFrequency()<<endl;
//    cout<<"Root Left: "<<tLast->getHuffLeft()->getVal()<<endl;
//    cout<<"Root Right: "<<tLast->getHuffRight()->getVal()<<endl;
//    cout<<"Is the left a leaf?: "<<tLast->getHuffLeft()->isLeafNode()<<endl;
    
    //INSERT IS REMOVING THE LEFT AND RIGHT.
    //FIND A WAY TO KEEP THE ORIGINAL LEFT AND RIGHT, AND BRING IT BACK INTO THE MINHEAP FOR NEW LEFT AND RIGHT
}

TreeNode* HuffTree::getRoot(){
    return root;
}

void HuffTree::generateCodes(TreeNode*current, int iteration){
    if(current->getHuffLeft()!=NULL){
        code[iteration]=1;
        int iter2=iteration+1;
        generateCodes(current->getHuffLeft(), iter2);
    }
    if(current->getHuffRight()!=NULL){
        code[iteration]=0;
        int iter2=iteration+1;
        generateCodes(current->getHuffRight(),iter2);
    }
    string codeFinal;
    for(int i=0; i<iteration; i++){
        codeFinal+=code[i]+'0';
    }
    count++;
    codes[current->getVal()]=codeFinal;
    //uniqueChars.push_back(current->getVal());
}

string HuffTree::getCharCode(int c){
    return codes[c];
}

int HuffTree::getSize(){
    return count;
}

/*
int HuffTree::getCharFromCode(string binaryInput){
    for(int i=0; i<256; i++){
        if(!codes[i].empty()){
//            if(binaryInput!="0"&&binaryInput==codes[i]){
            if(binaryInput==codes[i]){
                return i;
            }
        }
    }
    return -1;
}
 */
int HuffTree::getCharFromCode(string binaryInput){
    return getCharFromCode(root, binaryInput, 0);
}

int HuffTree::getCharFromCode(TreeNode*current, string binaryInput, unsigned char directionCounter){
    if(directionCounter==binaryInput.length()){
        return current->getVal();
    }
    if(binaryInput[directionCounter]=='1' && current->getHuffLeft()!=NULL){
        int dc2=directionCounter+1;
        return getCharFromCode(current->getHuffLeft(), binaryInput, dc2);
    }
    else if(binaryInput[directionCounter]=='0' && current->getHuffRight()!=NULL){
        int dc2=directionCounter+1;
        return getCharFromCode(current->getHuffRight(), binaryInput, dc2);
    }
    return -1;
}

HuffTree::~HuffTree(){
    //delete removedNodes;
    //delete[]code;
    //delete root;
}




