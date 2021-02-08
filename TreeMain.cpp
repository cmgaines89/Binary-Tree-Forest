/*
C. Gaines
Binary Tree Forest
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

struct tnode
{
	char data[25];
	tnode *left;
	tnode *right;
};

using namespace std;


void buildNode(tnode *&parent, char info[]);
void treeSearch(tnode *&parent, char newItem[], int &found);
void inOrder(tnode *tree, ofstream &output);
void preOrder(tnode *tree, ofstream &output);
void postOrder(tnode *tree, ofstream &output);
void findMin(tnode *tree, ofstream &output);
int countedge(tnode *tree);
int countInternal(tnode *tree);
void reversetree(tnode *tree, tnode *&revtree);
void replace(tnode *&tree, char oldval[], char newval[]);
void copy(tnode *tree, tnode *&copytree);
void split(tnode *tree, tnode *&mtree, tnode *&ntree, int &num);
bool isequal(tnode *tree1, tnode *tree2);
bool childcount(tnode *tree);
void findMax(tnode*tree, ofstream &output);
bool mirror(tnode *tree1, tnode *tree2);
bool symmetric(tnode* tree);
void printmaxmin(tnode *tree, ofstream &output);
bool fullTree(tnode *tree);

int main()
{
	tnode *Pine = NULL, *RevPine = NULL, *CopyPine = NULL, *MTree = NULL, *NTree = NULL, *CopyNTree = NULL, *ZTTree = NULL;
	char arr[25];
	char arr2[11];
	int found, num = 0;;

	ifstream in;
	ifstream in2;
	ifstream inm;
	ifstream inn;
	ofstream out;

	in.open("input.txt");
	out.open("output.txt");

	// 1
	strcpy_s(arr, "music");
	treeSearch(Pine, arr, found);

	while (in)
	{
		treeSearch(Pine, arr, found);
		in >> arr;
	}

	// 2
	out << endl << "THE PINE TREE USING INORDER TRAVERSAL:" << endl;
	inOrder(Pine, out);

	out << endl << "THE PINE TREE USING PREORDER TRAVERSAL:" << endl;
	preOrder(Pine, out);

	out << endl << "THE PINE TREE USING POSTORDER TRAVERSAL:" << endl;
	postOrder(Pine, out);

	// 3
	out << endl;
	findMin(Pine, out);

	out << endl << "THE ORIGINAL PINE: " << endl;
	inOrder(Pine, out);

	// 4
	out << endl << "THE NUMBER OF EDGES BETWEEN THE ROOT AND THE SMALLEST VALUE IS: " << countedge(Pine) << endl;
	out << endl << "THE ORIGINAL PINE: " << endl;
	inOrder(Pine, out);

	// 5
	out << endl << "THE NUMBER OF INTERNAL NODES IN PINE IS: " << countInternal(Pine) << endl;;
	out << endl << "THE ORIGINAL PINE: " << endl;
	inOrder(Pine, out);

	// 6
	reversetree(Pine, RevPine);
	out << endl << "PINE IN REVERSE ORDER (REVPINE): " << endl;
	inOrder(RevPine, out);
	out << endl << "THE ORIGINAL PINE: " << endl;
	inOrder(Pine, out);

	// 8
	copy(Pine, CopyPine);
	out << endl << "THE ORIGINAL PINE: " << endl;
	inOrder(Pine, out);
	out << endl << "COPY PINE: " << endl;
	inOrder(CopyPine, out);

	// 7
	replace(CopyPine, "baggy", "apple");
	out << endl << "BAGGY HAS BEEN REPLACED WITH APPLE IN THE COPYPINE TREE:" << endl;
	out << endl << "COPY PINE: " << endl;
	inOrder(CopyPine, out);

	

	// 9
	split(CopyPine, MTree, NTree, num);
	out << endl << "MTREE USING INORDER TRAVERSAL:" << endl;
	inOrder(MTree, out);
	out << endl << "NTREE USING INORDER TRAVERSAL:" << endl;
	inOrder(NTree, out);

	copy(NTree, CopyNTree);
	out << endl << " ORIGINAL NTREE: " << endl;
	inOrder(NTree, out);
	out << endl << "COPY NTREE: " << endl;
	inOrder(CopyNTree, out);

	out << endl << "ARE NTREE AND COPYNTREE EQUAL? [TRUE=1, FALSE=0] " << isequal(NTree, CopyNTree) << endl;

	// 10
	out << endl << "IS PINE A 0-2 TREE? [TRUE=1, FALSE=0] " << childcount(Pine) << endl;

	//11
	out << endl;
	findMax(Pine, out);
	out << endl << "THE ORIGINAL PINE:" << endl;
	inOrder(Pine, out);

	// 12
	// Words for ZTTree: aaaaa, bbbbb, ccccc, ddddd, eeeee, apple, bubba, coder, dunce, eggos, apache
	strcpy_s(arr2, "aaaaa");
	treeSearch(ZTTree, arr2, found);

	in2.open("input2.txt");

	while (in2)
	{
		treeSearch(ZTTree, arr2, found);
		in2 >> arr2;
	}

	in2.close();

	out << endl << "THE ZTTREE USING INORDER TRAVERSAL:" << endl;
	inOrder(ZTTree, out);
	out << endl << "THE ZTTREE USING PREORDER TRAVERSAL:" << endl;
	preOrder(ZTTree, out);
	out << endl << "THE ZTTREE USING POSTORDER TRAVERSAL:" << endl;
	postOrder(ZTTree, out);
	out << endl << "IS ZTTREE A 0-2 TREE? [TRUE=1, FALSE=0] " << childcount(ZTTree) << endl;

	// 13
	out << endl << "IS ZTTREE A SYMMETRIC TREE? [TRUE=1, FALSE=0] " << symmetric(ZTTree) << endl;

	//14
	out << endl << "PINE PRINTED FROM MAX TO MIN:" << endl;
	printmaxmin(Pine, out);

	//15
	out << endl << "IS PINE A FULL TREE? [TRUE=1, FALSE=0] " << fullTree(Pine) << endl;

	in.close();
	out.close();


	//system("pause");
	return 0;
}

void buildNode(tnode *&parent, char info[])
{
	tnode *temp;
	temp = new tnode;

	if (temp != NULL)
	{
		strcpy_s(temp->data, info);
		temp->left = NULL;
		temp->right = NULL;
	}

	parent = temp;
}

void treeSearch(tnode *&parent, char newItem[], int &found)
{// 1.) Builds Tree
	int val;

	if (parent == NULL)
	{
		found = 0;
		buildNode(parent, newItem);
	}

	else
	{
		val = strcmp(newItem, parent->data);

		if (val == 0)
			found = 1;

		else if (val < 0)
			treeSearch(parent->left, newItem, found);
		else
			treeSearch(parent->right, newItem, found);
	}
}

void inOrder(tnode *tree, ofstream &output)
{// 2.) Traverse the tree with all 3 traversal methods
	if (tree != NULL)
	{
		inOrder(tree->left, output);
		output << tree->data << endl;
		inOrder(tree->right, output);
	}
}

void preOrder(tnode *tree, ofstream &output)
{// 2.) Traverse the tree with all 3 traversal methods
	if (tree != NULL)
	{
		output << tree->data << endl;
		preOrder(tree->left, output);
		preOrder(tree->right, output);
	}
}

void postOrder(tnode *tree, ofstream &output)
{// 2.) Traverse the tree with all 3 traversal methods
	if (tree != NULL)
	{
		postOrder(tree->left, output);
		postOrder(tree->right, output);
		output << tree->data << endl;
	}
}

void findMin(tnode *tree, ofstream &output)
{// 3.) Print the smallest element of the binary search tree

	if (tree != NULL)
	{
		if (tree->left!= NULL)
			findMin(tree->left, output);
	}

	if (tree->left==NULL)
	output << "THE MINIMUM VALUE IN THE TREE IS: "<< tree->data <<endl;
}

int countedge(tnode *tree)
{// 4.) Counts the number of edges between the root of the tree and the smallest value in the tree

	int count = 0;

	if (tree != NULL)
	{
		if (tree->left != NULL)
		{
			countedge(tree->left);
			count++;
		}
	}

	return count;
}

int countInternal(tnode *tree)
{// 5.) Counts the number of internal nodes in the tree

	int count = 0;

	if (tree->left != NULL || tree->right != NULL)
	{
		count = 1;

		if (tree->left != NULL)
			count += countInternal(tree->left);

		if (tree->right != NULL)
			count += countInternal(tree->right);
	}

	return count;
}

void reversetree(tnode *tree, tnode *&revtree)
{// 6.) Creates tree in reverse order
	
	if (tree != NULL)
	{
		char item[25];

		strcpy_s(item, tree->data);

		std::reverse(item, item + strlen(item));

		buildNode(revtree, item);

		if (tree->left != NULL)
			reversetree(tree->left, revtree->left);
		if (tree->right != NULL)
			reversetree(tree->right, revtree->right);
	}
}

void replace(tnode *&tree, char oldval[], char newval[])
{// 7.) Replaces oldval with a new value

	tnode *left, *right;

	if (tree != NULL)
	{
		if (strcmp(tree->data, oldval) == 0)
		{
			left = tree->left;
			right = tree->right;
			buildNode(tree, newval);
			tree->left = left;
			tree->right = right;
		}
		replace(tree->left, oldval, newval);
		replace(tree->right, oldval, newval);
	}
}



void copy(tnode *tree, tnode *&copytree)
{// 8.) Copies the original tree

	if (tree != NULL)
	{
		buildNode(copytree, tree->data);
		
		if (tree->left != NULL)
			copy(tree->left, copytree->left);
		if (tree->right != NULL)
			copy(tree->right, copytree->right);

	}
}

void split(tnode *tree, tnode *&mtree, tnode *&ntree, int &num)
{//9.) Splits NTree & MTree
	int found;

	if (tree != NULL)
	{
		if (num < 12)
		{
			treeSearch(mtree, tree->data, found);
			num++;
			if (tree->left != NULL)
				split(tree->left, mtree->left, ntree, num);
			if (tree->right != NULL)
				split(tree->right, mtree->right, ntree, num);
		}

		else if (num < 24)
		{
			treeSearch(ntree, tree->data, found);
			num++;
			if (tree->left != NULL)
				split(tree->left, mtree, ntree->left, num);
			if (tree->right != NULL)
				split(tree->right, mtree, ntree->right, num);
		}
	}
}


bool isequal(tnode *tree1, tnode *tree2)
{// 9.) Determines if two trees are equal

	bool flag;

	if (tree1 == NULL && tree2 == NULL)
		flag = true;

	if (tree1 != NULL && tree2 != NULL)
	{
		(tree1->data == tree2->data && isequal(tree1->left, tree2->left) && isequal(tree1->right, tree2->right));
		flag = true;
	}

	else
		flag = false;

	return flag;
}

bool childcount(tnode *tree)
{// 10.) Determines if a tree is 0-2 tree

	bool flag;

	if (tree == NULL)
		flag = true;

	if (tree->left != NULL && tree->right != NULL)
	{
		childcount(tree->left);
		childcount(tree->right);
		flag = true;
	}

	else
		flag = false;

	return flag;
}

void findMax(tnode*tree, ofstream &output)
{// 11.) Finds the maximum value of a tree

	if (tree != NULL)
	{
		if (tree->right != NULL)
			findMax(tree->right, output);
	}

	if (tree->right == NULL)
		output << "THE MAXIMUMM VALUE IN THE TREE IS: " << tree->data << endl;
}

bool mirror(tnode *tree1, tnode *tree2)
{// 13.) Determines if a tree is a mirror of itself (symmetric)

	bool flag;

	if (tree1 == NULL && tree2 == NULL)
		flag = true;

	if (tree1 != NULL && tree2 != NULL && tree1->data == tree2->data)
	{
		mirror(tree1->left, tree2->right);
		mirror(tree1->right, tree2->left);
		flag = true;
	}

	else
		flag = false;

	return flag;

}

bool symmetric(tnode* tree)
{// 13.) Determines if a tree is a mirror of itself (symmetric)

	return mirror(tree, tree);
}

void printmaxmin(tnode *tree, ofstream &output)
{// 14.) Prints a binary search tree from the maximum element to the minimum element

	if (tree != NULL)
	{
			printmaxmin(tree->right, output);
			output << tree->data << endl;
			printmaxmin(tree->left, output);
	}
}

bool fullTree(tnode *tree)
{// 15.) Determines whether a binary tree is a full binary tree

	bool flag;

	if (tree == NULL)
		flag = true;

	if (tree->left == NULL && tree->right == NULL)
		flag = true;

	if ((tree->left) && (tree->right))
	{
		(fullTree(tree->left) && fullTree(tree->right));
		flag = true;
	}

	else
		flag = false;

	return flag;
}
