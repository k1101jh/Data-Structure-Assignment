#include <iostream>
#include <string>
#include "genericStackDL.cpp"
using namespace std;

int PrintSelection()	// 스택을 선택하는 함수 
{
	int input;
	do{
		cout << "Select stack (int : 1, double : 2, string : 3, Exit : 0) >> ";
		cin >> input;
	}while(!(input == 0 || input == 1 || input == 2 || input == 3));
	return input;
}

template<class T>
void PopAllItems(stackClass<T>* SC)	// 모든 아이템을 Pop하는 함수 
{
	while(!SC->IsEmpty())
	{
		cout << SC->Pop() << " ";
	}
	cout << endl;
}

int main()
{
	stackClass<int> intStack;
	stackClass<double> doubleStack;
	stackClass<string> stringStack;
	
	int input;
	
	cout << "Push : 1, Pop : 2, Copy Stack : 3, Is Empty? : 4, Exit : 0 >> ";
	cin >> input;
	while (input != 0)
	{
		switch (input)
		{
			case 1:
				input = PrintSelection();
				switch(input)
				{
					case 0:
						break;
					case 1:
						int itemI;
						cout << "Push int >> ";
						cin >> itemI;
						intStack.Push(itemI);
						break;
					case 2:
						double itemD;
						cout << "Push double >> ";
						cin >> itemD;
						doubleStack.Push(itemD);
						break;
					case 3:
						string itemS;
						cout << "Push string >> ";
						cin >> itemS;
						stringStack.Push(itemS);
						break;	
				}
				break;
			case 2:
				cout << "Pop one item : 1, Pop all items : 2 (Exit : 0) >> ";
				cin >> input;
				switch(input)
				{
					case 0:
						break;
					case 1:
						input = PrintSelection();
						switch(input)
						{
							case 0:
								break;
							case 1:
								if(intStack.IsEmpty() == false)
									cout << "Item : " << intStack.Pop() << endl;
								else
									cout << "Stack is Empty" << endl;
								break;
							case 2:
								if(doubleStack.IsEmpty() == false)
									cout << "Item : " << doubleStack.Pop() << endl;
								else
									cout << "Stack is Empty" << endl;
								break;
							case 3:
								if(stringStack.IsEmpty() == false)
									cout << "Item : " << stringStack.Pop() << endl;
								else
									cout << "Stack is Empty" << endl;
								break;	
						}
						break;
					case 2:
						input = PrintSelection();
						switch(input)
						{
							case 0:
								break;
							case 1:
								PopAllItems(&intStack);
								break;
							case 2:
								PopAllItems(&doubleStack);
								break;
							case 3:
								PopAllItems(&stringStack);
								break;	
						}
						break;
				}
				break;
			case 3:
				{
					stackClass<int> intStack2(intStack);
					stackClass<double> doubleStack2(doubleStack);
					stackClass<string> stringStack2(stringStack);
					cout << "Items of int Stack : " << endl;
					PopAllItems(&intStack2);
					cout << "Items of double Stack : " << endl;
					PopAllItems(&doubleStack2);
					cout << "Items of string Stack : " << endl;
					PopAllItems(&stringStack2);
				}
				break;
			case 4:
				input = PrintSelection();
				switch(input)
				{
					case 0:
						break;
					case 1:
						cout << ((intStack.IsEmpty() == true) ? "Yes" : "No") << endl;
						break;
					case 2:
						cout << ((doubleStack.IsEmpty() == true) ? "Yes" : "No") << endl;
						break;
					case 3:
						cout << ((stringStack.IsEmpty() == true) ? "Yes" : "No") << endl;
						break;
				}
				break;
		}
		cout << "Push : 1, Pop : 2, Copy Stack : 3, Is Empty? : 4, Exit : 0 >> ";
		cin >> input;
	}
}
