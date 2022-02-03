#include <iostream>
#define RED		true
#define BLACK	false
using namespace std;

typedef struct treeRecord
{
	int key;
	struct treeRecord * LChild;
	struct treeRecord * RChild;
	struct treeRecord * p;
	bool color;
} node;

typedef node* Nptr;

void LRotate(Nptr& t, bool LR)
{
	//cout << "L Rotate" << endl;
	Nptr tr = t->RChild;
	Nptr p = t->p;
	
	if(tr->LChild != NULL)
		tr->LChild->p = t;
	
	if(LR)
	{
		tr->LChild = t;
		t->p = tr;
		t->RChild = NULL;
		tr->RChild = p;
		tr->p = p->p;
		p->LChild = NULL;
		p->p = tr;
		
		t = tr->p;
		return;
	}
	else
	{
		t->RChild = tr->LChild;
		t->p = tr;
		tr->LChild = t;
		tr->p = p;
	}

	if(p != NULL)
	{
		if(p->LChild == t)
			p->LChild = tr;
		else
			p->RChild = tr;
	}
}

void RRotate(Nptr& t, bool RL)
{
	//cout << "R Rotate" << endl;
	Nptr tl = t->LChild;
	Nptr p = t->p;
	
	if(tl->RChild != NULL)
		tl->RChild->p = t;
	
	if(RL)
	{
		tl->RChild = t;
		t->p = tl;
		t->LChild = NULL;
		p->RChild = tl->LChild;
		tl->LChild->p = p;
		tl->LChild = p;
		tl->p = p->p;
		p->p = tl;
		
		t = tl->p;
		return;
	}
	else
	{
		t->LChild = tl->RChild;
		t->p = tl;
		tl->RChild = t;
		tl->p = p;
	}
	
	if(p != NULL)
	{
		if(p->RChild == t)
			p->RChild = tl;
		else
			p->LChild = tl;
	}
}

int Insert(Nptr &t, int key)
{
	Nptr p = t;
	while(t)
	{
		// 중복일 경우 
		//cout << "key : " << t->key << endl;
		if(key == t->key) return 0;
		
		p = t;
		if(key > t->key) t = t->RChild;
		else t = t->LChild;
	}
	// 새 노드 
	t = new node;
	t->key = key;
	t->LChild = NULL;
	t->RChild = NULL;
	t->p = p;
	t->color = RED;
	
	if(p == NULL)
	{
		//cout << "p NULL" << endl;
		
		t->color = BLACK;
		return 1;
	}
	else
	{
		if(key > t->p->key)
		{
			t->p->RChild = t;
			t->p->RChild->p = t->p;
		}
		else
		{
			t->p->LChild = t;
			t->p->LChild->p = t->p;
		}
			
		if(t->p->color == BLACK)
		{
			//cout << "case 2" << endl;
			
			if(t->p->LChild == NULL && t->p->RChild != NULL)
			{
				//cout << "2-1" << endl;
				t->p->RChild->color = BLACK;
				t->p->color = RED;
				LRotate(t->p, false);
			}
			else if(t->p->LChild != NULL && t->p->LChild->color == RED)
			{
				//cout << "2-2" << endl;
				t->p->LChild->color = BLACK;
				if(t->p->RChild != NULL)
					t->p->RChild->color = BLACK;
				else
					t->p->LChild->color = RED;
				if(t->p->p != NULL)
				{
					if((t->p == t->p->p->RChild && t->p->p->LChild->color == BLACK) &&
					t == t->p->RChild)
					{
						//cout << "2-2-1" << endl;
						t->p->p->color = RED;
						LRotate(t->p->p, false);
					}	
					else
					{
						//cout << "2-2-2" << endl;
						if(t->p == t->p->p->RChild)
							t->p->p->LChild->color = BLACK;
						//else 2-3-4 일 때 
							//t->p->p->RChild->color = BLACK;
						//t->color = BLACK; 
					}
				}	
			}
			else if(t->p->RChild == NULL && t->p->LChild != NULL)
			{
				//cout << "2-3" << endl;
				t->p->LChild->color = BLACK;
				t->p->color = RED;
				RRotate(t->p, false);
			}
			else
			{
				t->p->LChild->color = BLACK;
				t->p->RChild->color = BLACK;
			}
			
			while(t->p != NULL)
				t = t->p;
			t->color = BLACK;
			return 1;
		}
		else if(t->p->color == RED)
		{
			//cout << "case 3" << endl;
			if((t == t->p->RChild) && (t->p == t->p->p->LChild))
			{
				//cout << "3-1" << endl;
				t->p->color = BLACK;
				LRotate(t->p, true);
				
				while(t->p != NULL)
					t = t->p;
				t->color = BLACK;
				return 1;
				//t = t->LChild;
			}
			else if((t == t->p->LChild) && (t->p == t->p->p->RChild))
			{
				//cout << "3-2" << endl;
				t->p->color = BLACK;
				RRotate(t->p, true);

				while(t->p != NULL)
					t = t->p;
				t->color = BLACK;
				return 1;
				//t = t->RChild;
			}
			//cout << "case 4" << endl;

			if(t->p->p != NULL)
			{
				if(t == t->p->LChild)
				{
					t->color = BLACK;

					if(t->p->p->p != NULL && t->p->p == t->p->p->p->RChild)
					{
						t->p->p->p->color = RED;
						RRotate(t->p->p, true);
						
						while(t->p != NULL)
							t = t->p;
						t->color = BLACK;
						return 1;
					}
					else
						RRotate(t->p->p, false);
					
					if(t->p != NULL && t->p->color == RED &&
					t->p->p != NULL && t->p->p->color == RED)
					{
						t->p->color = BLACK;
						RRotate(t->p->p->p, false);
					}
	
				}
				else
					LRotate(t->p->p, false);
			}
		}
	}
	
	// 루트 노드는 BLACK 
	
	while(t->p != NULL)
		t = t->p;
	t->color = BLACK;
	return 1;
}

void Delete(Nptr &T, int key)
{
	if(T == NULL)
		cout << "No Record with Such Key" << endl;
	else if(T->key > key)
		Delete(T->LChild, key);
	else if(T->key < key)
		Delete(T->RChild, key);
	else if(T->key == key)
	{
		if((T->LChild == NULL) && (T->RChild == NULL))
		{
			Nptr Temp = T;
			T = NULL;
			delete Temp;
		}
		else if(T->LChild == NULL)
		{
			Nptr Temp = T;
			T = T->RChild;
			delete Temp;
		}
		else if(T->RChild == NULL)
		{
			Nptr Temp = T;
			T = T->LChild;
			delete Temp;
		}
		else
		{
		}
	}
}

bool RBVerify(Nptr node)
{
	
}
