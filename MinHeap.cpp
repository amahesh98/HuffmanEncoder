#include <iostream>
#include <climits>

#include "MinHeap.h"
#include <vector>



//implement the methods in MinHeap.h

MinHeap::MinHeap()
{
    heapSize=0;
    //maxDepth=0;
}

void MinHeap::insert(TreeNode * toAdd)
{
    int tempSize=getSize();
    if(tempSize==0){
        heapSize++;
        nodes.push_back(toAdd);
    }
    
    else{
        heapSize++;
        nodes.push_back(toAdd);
    
        int parentIndex=getSize()/2-1;
        if(flip){
            if(getSize()%2==0){
                nodes.at(parentIndex)->setLeft(toAdd);
            }
            else{
                nodes.at(parentIndex)->setRight(toAdd);
            }
        }
        else{
            if(getSize()%2==1){
                nodes.at(parentIndex)->setLeft(toAdd);
            }
            else{
                nodes.at(parentIndex)->setRight(toAdd);
            }
        }

            upHeap();
    }
}

int MinHeap::getSize()
{
    return heapSize;
}

TreeNode * MinHeap::removeMin()
{
    if(heapSize==0){
        return NULL;
    }
    if(heapSize!=1){
        flip=!flip;
    }
    //TreeNode*output=createCopy(nodes[0]);
    TreeNode*output=nodes.at(0);
    int parentIndex=getSize()/2-1;
    nodes.at(0)=NULL;
    nodes.erase(nodes.begin());
    heapSize--;
    if(heapSize==0){
        //head=NULL;
        output->setLeft(NULL);
        output->setRight(NULL);
        return output;
    }
    
    vector<TreeNode*>::iterator it=nodes.begin();

    TreeNode*temp=nodes.at(getSize()-1);
    //cout<<"New head: "<<temp->getVal()<<endl;
    nodes.insert(it, temp);
    nodes.at(getSize())=NULL;
    //temp=NULL;
    //delete(temp);
    nodes.erase(--nodes.end());
    nodes.at(0)->setLeft(output->getLeft());
    nodes.at(0)->setRight(output->getRight());
    
    //int parentIndex=nodes.size()/2-1;
    if(getSize()%2==1){
        nodes.at(parentIndex)->setLeft(NULL);
    }
    else{
        nodes.at(parentIndex)->setRight(NULL);
    }
    downHeap(0);
    /*
    if(compareNodeVal(output->getLeft(), output->getRight())){
        head=output->getLeft();
        head->join(NULL, output->getRight());
    }
    else{
        head=output->getRight();
        head->join(output->getLeft(), NULL);
    }
     */
    /*
    TreeNode*output=head;
    //TreeNode*output= createCopy(head);
    TreeNode*leftNode = head->getLeft();
    TreeNode*rightNode = head->getRight();
    head=NULL;
    if(compareNodeVal(leftNode, rightNode)){
        head=leftNode;
        head->join(NULL, rightNode);
    }
       else{
           head=rightNode;
           head->join(leftNode, NULL);
       }
    size--;
     */
	return output;

}
bool MinHeap::compareNodeVal(TreeNode*first, TreeNode*second){
    if(first->getFrequency()<=second->getFrequency()){
        return true;
    }
    return false;
}

TreeNode* MinHeap::createCopy(TreeNode*toCopy){
    TreeNode*output=new TreeNode(toCopy->getVal(), toCopy->getFrequency());
    return output;
}

    
    
void MinHeap::upHeap(){
    
    int childIndex=getSize()-1;
    int parentIndex=getSize()/2-1;
    
//    while(childIndex>=0 && parentIndex>=0 && (nodes.at(childIndex)->getFrequency()<nodes.at(parentIndex)->getFrequency() || (nodes.at(childIndex)->getFrequency()==nodes.at(parentIndex)->getFrequency() && nodes.at(parentIndex)->getVal()==0 && nodes.at(childIndex)->getVal()!=0))){
//    while(childIndex>=0 && parentIndex>=0 && (nodes.at(childIndex)->getFrequency()<nodes.at(parentIndex)->getFrequency() || (nodes.at(childIndex)->getFrequency()==nodes.at(parentIndex)->getFrequency() && (nodes.at(childIndex)->getVal()<nodes.at(parentIndex)->getVal())))){
    
    TreeNode*childLeft=NULL;
    TreeNode*childRight=NULL;
    TreeNode*tempParent=NULL;
    TreeNode*tempChild=NULL;
    
    while(childIndex>=0 && parentIndex>=0 && (nodes.at(childIndex)->getFrequency()<nodes.at(parentIndex)->getFrequency())){
        childLeft=nodes.at(childIndex)->getLeft();
        childRight=nodes.at(childIndex)->getRight();
        tempParent=nodes.at(parentIndex);
        tempChild=nodes.at(childIndex);
        
        //cout<<"Upheap swap: "<<nodes.at(childIndex)->getVal()<<" & "<<nodes.at(parentIndex)->getVal()<<endl;
       
        nodes.at(parentIndex)=nodes.at(childIndex);
        nodes.at(childIndex)=tempParent;
        //nodes.at(parentIndex)->setLeft(tempParent);
        
        if(childIndex%2==0){
            tempChild->setRight(tempParent);
            tempChild->setLeft(tempParent->getLeft());
            //nodes.at(parentIndex)->setRight(temp);
            //nodes.at(parentIndex)->setLeft(temp->getLeft());
        }
        else{
            tempChild->setLeft(tempParent);
            tempChild->setRight(tempParent->getRight());
            
           // nodes.at(parentIndex)->setLeft(temp);
           // nodes.at(parentIndex)->setRight(temp->getRight());
        }
        
        tempParent->setLeft(childLeft);
        tempParent->setRight(childRight);
        childIndex=parentIndex;
        parentIndex=(childIndex+1)/2-1;
        
    }
}

void MinHeap::downHeap(int index)
{
    int leftInd = (index+1)*2-1;
    int rightInd = (index+1)*2;
    int smallestIndex=index;
    if(leftInd >= heapSize){
        return;
    }
    
    if(nodes.at(leftInd)->getFrequency()<nodes.at(smallestIndex)->getFrequency())
        {
            smallestIndex = leftInd;
            }
    
    if(rightInd<heapSize && nodes.at(rightInd)->getFrequency()<nodes.at(smallestIndex)->getFrequency())
        {
                smallestIndex = rightInd;
        }
    
    if(smallestIndex != index)
        {
            TreeNode*temp=nodes.at(index);
            TreeNode*oldLeft=nodes.at(smallestIndex)->getLeft();
            TreeNode*oldRight=nodes.at(smallestIndex)->getRight();
            
            nodes.at(index)=nodes.at(smallestIndex);
            nodes.at(smallestIndex)=temp;
            if(smallestIndex==(leftInd)){
                nodes.at(index)->setLeft(temp);
                nodes.at(index)->setRight(temp->getRight());
            }
            else{
                nodes.at(index)->setRight(temp);
                nodes.at(index)->setLeft(temp->getLeft());
            }
            temp->setLeft(oldLeft);
            temp->setRight(oldRight);
            index=smallestIndex;
            downHeap(smallestIndex);
        }
}

MinHeap::~MinHeap(){
    for(int i=nodes.size()-1; i>=0; i--){
        delete nodes.at(i);
    }
}



