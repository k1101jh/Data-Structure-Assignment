#include <iostream>
#include <string>
#include <math.h>
#include "genericStackDL.cpp"
using namespace std;

bool is_operator(string k)						// 연산자를 입력받았는지 확인하는 함수 
{
	return (k == "+" || k == "-" || k == "*" || k == "/");
}

bool is_func(string k)							// 함수를 입력받았는지 확인하는 함수 
{
	return (k == "pow" || k == "log" || k == "sqrt");
}

double calc(double x, double y, string op)		// 계산하는 함수 
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
	stackClass<double> numS;					// 숫자 스택 
	stackClass<string> opS;						// 연산자 스택  
	
	string exp = " ";							// 입력을 위한 변수 
	int sBrNum = 0, eBrNum = 0; 				// 시작 괄호, 끝 괄호 수 
	cout << ">> ";
	while(true)
	{
		char a = cin.get();						// 입력을 char형으로 받아옴 
		if(a == '\n')							// 만약 enter키가 눌렸다면 결과 출력 
			break;
		else if(a == '(')						// 식이 괄호로 시작하지 않을 경우 
		{
			if(!numS.IsEmpty() || !opS.IsEmpty())	// 숫자 또는 연산자가 존재할 경우 
			{
				cout << "Invalid input";				// 입력 오류 
				return 0;
			}
			sBrNum++;								// 시작 괄호 수 증가 
		}
		else if(a != ' ')						// 처음 get은 '('를 받아오지만 cin >> 으로 값을 받은 후에는 입력 버퍼에는 ' ' 이 남게 된다.  
		{										// 각각의 토큰은 ' '로 구분되어야 하기 때문에 ' '이 아닐 경우  
			cout << "Invalid input";				// 입력 오류 
			return 0; 
		}

		cin >> exp;								// 입력 
		if(is_func(exp))						// 함수를 입력한 경우  
		{
			if(exp == "pow")						// pow 함수 
			{
				double x, y, result = 1;
				char br1, br2, com;
				string num;
				try
				{
					cin >> br1 >> x >> com >> y >> br2;
				}
				catch(...)								// 입력에 오류가 있을 경우 
				{
					cout << "Invalid input";
					return 0;
				}
				if(br1 != '(' || com != ',' || br2 != ')')	 // 입력에 오류가 있을 경우 
				{
					cout << "Invalid input";
					return 0;
				}
				for(int i = 0; i < y; i++)				// 제곱 
					result *= x;
				numS.Push(result);						// 결과를 스택에 push 
			}
			else if(exp == "log")					// log 함수 
			{
				double x;
				char br1, br2;
				cin >> br1 >> x >> br2;
				if(br1 != '(' || br2 != ')')	 		// 입력에 오류가 있을 경우 
				{
					cout << "Invalid input";
					return 0;
				}
				numS.Push(sqrt(x));						// 결과를 스택에 push 
			}
			else									// sqrt 함수 
			{
				double x;
				char br1, br2;
				cin >> br1 >> x >> br2;
				if(br1 != '(' || br2 != ')')			// 입력에 오류가 있을 경우 
				{
					cout << "Invalid input";
					return 0;
				}
				numS.Push(log(x));						// 결과를 스택에 push 
			}
		}
		else if(is_operator(exp))				// 연산자를 입력했을 경우 
			opS.Push(exp);							// 연산자 스택에 푸쉬 
		else if(exp == "(")						// 시작 괄호를 입력했을 경우 
		{
			sBrNum++;								// 시작 괄호 수 증가 
		}
		else if(exp == ")")						// 끝 괄호를 입력했을 경우 
		{										// 괄호 안의 내용을 계산 
			double x, y;
			string op;
			eBrNum++;
			if(numS.IsEmpty()) 						// 숫자 스택이 비었을 경우 
			{
				cout << "Invalid input";				// 입력 오류 
				return 0;
			}
			y = numS.Pop();							// 괄호 안에 인자가 하나인 경우를 생각해서 y를 먼저 pop 
			if(opS.IsEmpty() && numS.IsEmpty())		// 연산자와 다음 숫자가 존재하는지 확인 
				numS.Push(y);							// 존재하지 않을 경우, y를 다시 스택에 push 
			else									// 둘 중 하나라도 존재할 경우 
			{
				if(numS.IsEmpty())						// 숫자 스택이 비었을 경우 
				{
					cout << "Invalid input";				// 입력 오류 
					return 0;
				}
				x = numS.Pop();							// x 를 pop 
				if(opS.IsEmpty())						// 연산자 스택이 비었을 경우 
				{
					cout << "Invalid input";				// 입력 오류 
					return 0;
				}
				else
				{
					op = opS.Pop();							// 연산자를 pop 
					numS.Push(calc(x, y, op));				// 계산해서 값을 숫자 스택에 push 
				}
			}
		}
		else									// 숫자를 입력 받았을 경우 
		{
			numS.Push(atof(exp.c_str()));			// 숫자 스택에 push 
		} 
		//cout << exp;							식이 제대로 입력되는지 확인하는 코드. 첫 괄호는 출력되지 않음 
	}
	if(sBrNum != eBrNum)					// 시작 괄호 수와 끝 괄호 수가 맞지 않을 경우 
		cout << "Invalid input";				// 입력 오류 
	else
		cout << numS.Pop();						// 계산 결과 출력 
}
