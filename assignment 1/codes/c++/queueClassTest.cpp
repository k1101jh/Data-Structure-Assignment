#include <iostream>
#include <string>
#include "genericQueueDL.cpp"
using namespace std;

int PrintSelection()		// ≈• º±≈√ 
{
	int input;
	do{
		cout << "Select queue (int : 1, double : 2, string : 3, Exit : 0) >> ";
		cin >> input;
	}while(!(input == 0 || input == 1 || input == 2 || input == 3));
	return input;
}

template<class T>
void RemoveAllItems(queueClass<T>* QC)
{
	while(!QC->IsEmpty())
	{
		cout << QC->Remove() << " ";
	}
	cout << endl;
}

int main()
{
	queueClass<int> intQueue;
	queueClass<double> doubleQueue;
	queueClass<string> stringQueue;
	
	int input;
	
	cout << "Add : 1, Remove : 2, Copy Queue : 3, Is Empty? : 4, Exit : 0 >> ";
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
						intQueue.Add(itemI);
						break;
					case 2:
						double itemD;
						cout << "Push double >> ";
						cin >> itemD;
						doubleQueue.Add(itemD);
						break;
					case 3:
						string itemS;
						cout << "Push string >> ";
						cin >> itemS;
						stringQueue.Add(itemS);
						break;	
				}
				break;
			case 2:
				cout << "Remove one item : 1, Remove all items : 2 (Exit : 0) >> ";
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
								if(intQueue.IsEmpty() == false)
									cout << "Item : " << intQueue.Remove() << endl;
								else
									cout << "Queue is Empty" << endl;
								break;
							case 2:
								if(doubleQueue.IsEmpty() == false)
									cout << "Item : " << doubleQueue.Remove() << endl;
								else
									cout << "Queue is Empty" << endl;
								break;
							case 3:
								if(stringQueue.IsEmpty() == false)
									cout << "Item : " << stringQueue.Remove() << endl;
								else
									cout << "Queue is Empty" << endl;
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
								RemoveAllItems(&intQueue);
								break;
							case 2:
								RemoveAllItems(&doubleQueue);
								break;
							case 3:
								RemoveAllItems(&stringQueue);
								break;	
						}
						break;
				}
				break;
			case 3:
				{
					queueClass<int> intQueue2(intQueue);
					queueClass<double> doubleQueue2(doubleQueue);
					queueClass<string> stringQueue2(stringQueue);
					cout << "Items of int Queue : " << endl;
					RemoveAllItems(&intQueue2);
					cout << "Items of double Queue : " << endl;
					RemoveAllItems(&doubleQueue2);
					cout << "Items of string Queue : " << endl;
					RemoveAllItems(&stringQueue2);
				}
				break;
			case 4:
				input = PrintSelection();
				switch(input)
				{
					case 0:
						break;
					case 1:
						cout << ((intQueue.IsEmpty() == true) ? "Yes" : "No") << endl;
						break;
					case 2:
						cout << ((doubleQueue.IsEmpty() == true) ? "Yes" : "No") << endl;
						break;
					case 3:
						cout << ((stringQueue.IsEmpty() == true) ? "Yes" : "No") << endl;
						break;
				}
				break;
		}
		cout << "Add : 1, Remove : 2, Copy Queue : 3, Is Empty? : 4, Exit : 0 >> ";
		cin >> input;
	}
}
