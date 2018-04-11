#ifndef MINHEAP_H
#define MINHEAP_H

#include "TreeNode.h"
#include <vector>

using namespace std;

class MinHeap
{
	private:
		int heapSize;
		//TreeNode*head;
		//int maxDepth;
		vector<TreeNode*>nodes;
		//TreeNode*last;
		bool flip=true;
		void upHeap();
		void downHeap(int index);
	public:
		MinHeap();
		TreeNode * removeMin(); //returns root of heap
		void insert(TreeNode * toAdd); //adds element to heap
		int getSize(); //returns size of heap
		~MinHeap();
		TreeNode*createCopy(TreeNode*toCopy);
		bool compareNodeVal(TreeNode*first, TreeNode*second);
		

};

#endif
