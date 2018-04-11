#ifndef TREENODE_H
#define TREENODE_H

#include <string>

using namespace std;

class TreeNode
{
	private:
		TreeNode * left;
		TreeNode * right;
        TreeNode*huffLeft;
        TreeNode*huffRight;
		unsigned long frequency;
		//unsigned char val;
        int val;
        string direction;
	public:
		
		//TreeNode();
//        TreeNode(unsigned char val, unsigned long frequency);
        TreeNode(int val, unsigned long frequency);
		//returns true if this node is a leaf node, returns false otherwise
		bool isLeafNode();

		//puts left as the left child and right as the right child of this node
        void setLeft(TreeNode*left);
        void setRight(TreeNode*right);
        void setHuffLeft(TreeNode*huffLeft);
        void setHuffRight(TreeNode*huffRight);
		void join(TreeNode * left, TreeNode * right);
        void setParent(TreeNode* input);

		TreeNode * getLeft(); //returns the left child
		TreeNode * getRight(); //returns the right child
        TreeNode * getHuffRight();
        TreeNode * getHuffLeft();

		unsigned long getFrequency(); //returns frequency member variable
        int getVal();
		//unsigned char getVal(); //returns val member variable

};


#endif
