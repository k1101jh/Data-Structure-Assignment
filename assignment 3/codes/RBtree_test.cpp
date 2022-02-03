#include "RBtree.cpp"
using namespace std;

void RBPrettyPrint(const string& prefix, Nptr node, bool isLeft)
{
	if(node != NULL)
	{
		cout << prefix;
		if(node->color == RED) cout << (isLeft ? " " : "	");
		else cout << (isLeft ? "|----" : "-----");
		
		cout << node->key;
		
		if(node->color == RED) cout << "*";
		cout << endl;
		
		RBPrettyPrint(prefix + (isLeft ? "|   " : " "), node->LChild, true);
		RBPrettyPrint(prefix + (isLeft ? "|   " : " "), node->RChild, false);
	}
}

int main()
{
	Nptr root = NULL;
	Nptr root2 = NULL;
	
	for(int i = 10; i <= 100; i += 10)
	{
		Insert(root, i);
		//RBPrettyPrint("", root, false);
	}
	RBPrettyPrint("", root, false);
	cout << endl << endl;
	
	/*
	for(int i = 10; i <= 1000; i += 10)
	{
		Insert(root2, i);
		//RBPrettyPrint("", root2, false);
	}
	RBPrettyPrint("", root2, false);
	cout << endl << endl;
	*/
	return 0;
}
