#include<iostream>
#include<string>
#include<stack>
using namespace std;

void Evalpostfix(string expresion);
int to_int(std::string val);

int main()
{
	
		string expression = "10 2 8 * + 3 -";
		string expression1 = "10 3 3 + /";
		string expression2 = "10 2 8 * +";
		string expression3 = "10 2 8 * -";
		string expression4 = "2 3+ 4 5+*";
		string expression5 = "3 4 * 2 5 * + ";
		
		string arr[] = {expression, expression1, expression2, expression3, expression4, expression5};
		
	
		for(int exp=  0; exp < sizeof(arr)/sizeof(string); exp++)
			Evalpostfix(arr[exp]);
	
	
}
int to_int(std::string val)
{
	int x = 0;
	for(int i = 0; i < val.length(); i++)
	{
		x  = x * 10 + int(val[i])-'0';
		if(val[1] == ' '){
			std::cout << "grapes";
		}
	}
	return x;
}
void Evalpostfix(string expresion)
{
	stack<float> stack;
	
	int length = expresion.length();
	string digits = "";
	float value1 = 0;
	float value2 = 0;
	for(int i= 0 ; i < length; i++)
	{
		if (expresion[i] == ' ')continue ;                        // don't waste cycles                 

		digits = "";
		if(expresion[i] >= '0'  && expresion[i] <= '9')     //means values is an integer
		{
			digits += expresion[i];
			while(i+1 < length && expresion[i+1] >= '0'  && expresion[i+1] <= '9')
			{
				i++;
				digits += expresion[i];

			}
			stack.push(float(to_int(digits)));
		}
		else
		{

			if(expresion[i] == '+' || expresion[i] == '/' ||expresion[i] == '*' ||expresion[i] == '-' )
			{
				value2 = stack.top(); 
				stack.pop();
				value1 = stack.top();
				stack.pop();
			
				if(expresion[i] == '+')
					stack.push(value1 + value2);
				else if(expresion[i] == '*')
					stack.push(value1 * value2);
				else if(expresion[i] == '/')
					stack.push(value1 / value2);
				else if(expresion[i] == '-')
					stack.push(value1 - value2); 
			}
			
					

		}
	}
	
	
	cout<<"Your Result Is: "<<stack.top()<<endl;
	stack.pop();
	
}
