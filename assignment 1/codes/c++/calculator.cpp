#include <iostream>
#include <string>
#include <math.h>
#include "genericStackDL.cpp"
using namespace std;

bool is_operator(string k)						// �����ڸ� �Է¹޾Ҵ��� Ȯ���ϴ� �Լ� 
{
	return (k == "+" || k == "-" || k == "*" || k == "/");
}

bool is_func(string k)							// �Լ��� �Է¹޾Ҵ��� Ȯ���ϴ� �Լ� 
{
	return (k == "pow" || k == "log" || k == "sqrt");
}

double calc(double x, double y, string op)		// ����ϴ� �Լ� 
{
	if(op == "+")
		return x + y;
	else if(op == "-")
		return x - y;
	else if(op == "*")
		return x * y;
	else
		return x / y;
}

int main()
{
	stackClass<double> numS;					// ���� ���� 
	stackClass<string> opS;						// ������ ����  
	
	string exp = " ";							// �Է��� ���� ���� 
	int sBrNum = 0, eBrNum = 0; 				// ���� ��ȣ, �� ��ȣ �� 
	cout << ">> ";
	while(true)
	{
		char a = cin.get();						// �Է��� char������ �޾ƿ� 
		if(a == '\n')							// ���� enterŰ�� ���ȴٸ� ��� ��� 
			break;
		else if(a == '(')						// ���� ��ȣ�� �������� ���� ��� 
		{
			if(!numS.IsEmpty() || !opS.IsEmpty())	// ���� �Ǵ� �����ڰ� ������ ��� 
			{
				cout << "Invalid input";				// �Է� ���� 
				return 0;
			}
			sBrNum++;								// ���� ��ȣ �� ���� 
		}
		else if(a != ' ')						// ó�� get�� '('�� �޾ƿ����� cin >> ���� ���� ���� �Ŀ��� �Է� ���ۿ��� ' ' �� ���� �ȴ�.  
		{										// ������ ��ū�� ' '�� ���еǾ�� �ϱ� ������ ' '�� �ƴ� ���  
			cout << "Invalid input";				// �Է� ���� 
			return 0; 
		}

		cin >> exp;								// �Է� 
		if(is_func(exp))						// �Լ��� �Է��� ���  
		{
			if(exp == "pow")						// pow �Լ� 
			{
				double x, y, result = 1;
				char br1, br2, com;
				string num;
				try
				{
					cin >> br1 >> x >> com >> y >> br2;
				}
				catch(...)								// �Է¿� ������ ���� ��� 
				{
					cout << "Invalid input";
					return 0;
				}
				if(br1 != '(' || com != ',' || br2 != ')')	 // �Է¿� ������ ���� ��� 
				{
					cout << "Invalid input";
					return 0;
				}
				for(int i = 0; i < y; i++)				// ���� 
					result *= x;
				numS.Push(result);						// ����� ���ÿ� push 
			}
			else if(exp == "log")					// log �Լ� 
			{
				double x;
				char br1, br2;
				cin >> br1 >> x >> br2;
				if(br1 != '(' || br2 != ')')	 		// �Է¿� ������ ���� ��� 
				{
					cout << "Invalid input";
					return 0;
				}
				numS.Push(sqrt(x));						// ����� ���ÿ� push 
			}
			else									// sqrt �Լ� 
			{
				double x;
				char br1, br2;
				cin >> br1 >> x >> br2;
				if(br1 != '(' || br2 != ')')			// �Է¿� ������ ���� ��� 
				{
					cout << "Invalid input";
					return 0;
				}
				numS.Push(log(x));						// ����� ���ÿ� push 
			}
		}
		else if(is_operator(exp))				// �����ڸ� �Է����� ��� 
			opS.Push(exp);							// ������ ���ÿ� Ǫ�� 
		else if(exp == "(")						// ���� ��ȣ�� �Է����� ��� 
		{
			sBrNum++;								// ���� ��ȣ �� ���� 
		}
		else if(exp == ")")						// �� ��ȣ�� �Է����� ��� 
		{										// ��ȣ ���� ������ ��� 
			double x, y;
			string op;
			eBrNum++;
			if(numS.IsEmpty()) 						// ���� ������ ����� ��� 
			{
				cout << "Invalid input";				// �Է� ���� 
				return 0;
			}
			y = numS.Pop();							// ��ȣ �ȿ� ���ڰ� �ϳ��� ��츦 �����ؼ� y�� ���� pop 
			if(opS.IsEmpty() && numS.IsEmpty())		// �����ڿ� ���� ���ڰ� �����ϴ��� Ȯ�� 
				numS.Push(y);							// �������� ���� ���, y�� �ٽ� ���ÿ� push 
			else									// �� �� �ϳ��� ������ ��� 
			{
				if(numS.IsEmpty())						// ���� ������ ����� ��� 
				{
					cout << "Invalid input";				// �Է� ���� 
					return 0;
				}
				x = numS.Pop();							// x �� pop 
				if(opS.IsEmpty())						// ������ ������ ����� ��� 
				{
					cout << "Invalid input";				// �Է� ���� 
					return 0;
				}
				else
				{
					op = opS.Pop();							// �����ڸ� pop 
					numS.Push(calc(x, y, op));				// ����ؼ� ���� ���� ���ÿ� push 
				}
			}
		}
		else									// ���ڸ� �Է� �޾��� ��� 
		{
			numS.Push(atof(exp.c_str()));			// ���� ���ÿ� push 
		} 
		//cout << exp;							���� ����� �ԷµǴ��� Ȯ���ϴ� �ڵ�. ù ��ȣ�� ��µ��� ���� 
	}
	if(sBrNum != eBrNum)					// ���� ��ȣ ���� �� ��ȣ ���� ���� ���� ��� 
		cout << "Invalid input";				// �Է� ���� 
	else
		cout << numS.Pop();						// ��� ��� ��� 
}
