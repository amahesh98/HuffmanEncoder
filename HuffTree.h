        #ifndef HUFFTREE_H
#define HUFFTREE_H

#include "MinHeap.h"
//#include "TreeNode.h"
#include <string>

#define MAXCODELENGTH 256
#define BYTESIZE 8

using namespace std;

class HuffTree
{
	private:
        TreeNode*root;
        //TreeNode*left;
        //TreeNode*right;
        //vector<TreeNode*>removedNodes;
        //vector<TreeNode*>theTree;
        int getCharFromCode(TreeNode*current, string binaryInput, unsigned char directionCounter);
    
        int count;
        char code[MAXCODELENGTH];

	public:
        HuffTree();
//        vector<unsigned char>uniqueChars;
        string codes[256];
		//build a hiffman  tree  give a minheap
		void buildTree(MinHeap * mh);

		//generate codes by traversing the huffman tree
		//and store them in an internal data structure (array of strings for example)
		void generateCodes(TreeNode*current, int interation);

		//returns root of the tree
		TreeNode * getRoot();

		//returns huffman code from  the ascii code
		string getCharCode(int c);
        int getCharFromCode(string binaryInput);
    
		~HuffTree();
        int getSize();
		
};


#endif
