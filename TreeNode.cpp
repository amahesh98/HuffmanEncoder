#include <iostream>
#include "TreeNode.h"

#include <string>


//TreeNode::TreeNode(unsigned char val, unsigned long frequency)
TreeNode::TreeNode(int val, unsigned long frequency)
{
    huffLeft=NULL;
    huffRight=NULL;
    this->val = val;
    this->frequency=frequency;
}

unsigned long TreeNode::getFrequency()
{
	return frequency;
}
//unsigned char TreeNode::getVal()
int TreeNode::getVal()
{
	return val;
}
bool TreeNode::isLeafNode(){
    if(huffLeft==NULL && huffRight==NULL){
        return true;
    }
    return false;
}
TreeNode* TreeNode::getLeft(){
    return left;
}
TreeNode* TreeNode::getRight(){
    return right;
}
TreeNode* TreeNode::getHuffLeft(){
    return huffLeft;
}
TreeNode* TreeNode::getHuffRight(){
    return huffRight;
}
void TreeNode::setLeft(TreeNode*left){
    this->left=left;
}
void TreeNode::setRight(TreeNode*right){
    this->right=right;
}
void TreeNode::setHuffLeft(TreeNode*huffLeft){
    this->huffLeft=huffLeft;
}
void TreeNode::setHuffRight(TreeNode*huffRight){
    this->huffRight=huffRight;
}
void TreeNode::join(TreeNode * left, TreeNode * right){
    
    if(left==NULL && this->left!=NULL){
        setRight(right);
    }
    else if(right==NULL && this->right!=NULL){
        setLeft(left);
        //this->left=left;
    }
    else{
     
        this->left=left;
        this->right=right;
   }
}
/*
bool TreeNode::operator ==(const TreeNode&other) const{
    if(other.val==val && other.frequency==frequency){
        return true;
    }
    return false;
}
bool TreeNode::operator !=(const TreeNode&other) const{
    if(other.val!=val || other.frequency!=frequency){
        return true;
    }
    return false;
}
*/


