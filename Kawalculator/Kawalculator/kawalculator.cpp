/*
*	Jose Alonso
*	CS480
*	Lab03
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <math.h>

using namespace std;

//Constant Values
//Allowed characters
string allowedSPSymbols = "()+*/^-.";

//Function Prototypes
bool isValidSPChar(char letter);
bool validateInput(string input);
vector<string> tokenize(string input);
vector<string> transformToRPN(const vector<string> &tokens);
double evaluateRPN(vector<string> expression);
bool tryParsingNum(const string &number);
bool isOperator(const string &c);
bool isDouble(const string &n);
int getOpPriority(const string &c);

/*
*	RPN algorithm is based on Karim Oumghar's solution shown in
*	https://simpledevcode.wordpress.com/2015/01/03/convert-infix-to-reverse-polish-notation-c-implementation/
*	https://simpledevcode.wordpress.com/2014/03/07/using-stacks-to-evaluate-prefix-postfix-notation-expressions-polish-notation/
*/

//Main function
int main(int argc, char *argv[])
{
	string input = "";
	char code = ' ';
	bool validInput = 0;

	//Alternative way to get input by using parameters
	/*
	for (int i = 1; i < argc; i++)
		input += argv[i];
	cout << input << endl;
	*/

	//Menu
	cout << "\t\tWELCOME TO KAWALKULATOR\t" << endl;
	while (true) {
		cout << "\n\tEnter new expression: "; getline(cin, input);

		//Deletes whitespaces & tabs
		input.erase(remove(input.begin(), input.end(), ' '), input.end());
		input.erase(remove(input.begin(), input.end(), '\t'), input.end());
		
		//Input validation
		validInput = validateInput(input);
		while (!validInput)
		{
			cout << "\n\tEnter a correct expression: "; getline(cin, input);
			validInput = validateInput(input);
		}

		//Prints validated input
		cout << '\t' << input << " = " ;

		//Tokenizing the string
		vector<string> tokens = tokenize(input);
		
		//Tokens
		//cout << endl;
		//for (int i = 0; i<tokens.size(); i++)
		//	cout << tokens[i] << "\n";
		//cout << endl;

		//RPNAlgorithm
		cout << evaluateRPN(transformToRPN(tokens))<<endl;
				
		cout << endl;
		//Menu part 2
		while (true) {
			cout << "\tDo you want to enter a new expression [y/n]: ";  
			code = cin.get();
			cin.ignore(256, '\n');
			if (code == 'n' || code == 'N')
				return 0;
			else if (code == 'y' || code == 'Y')
			{
				break;
			}
			else
			{
				cout << "\tInvalid option.\n\tPress [ENTER] to continue. ";
				cin.ignore();
			}
		}
	}
}

//Transforms infix to postfix
vector<string> transformToRPN(const vector<string> &tokens)
{
	vector<string> resultStack;//output vector
	stack<string> tempStack;//main stack

	for (int i = 0; i < tokens.size(); i++)  
	{
		if (tryParsingNum(tokens[i]))
			resultStack.push_back(tokens[i]);

		if (tokens[i] == "(")
			tempStack.push(tokens[i]);

		if (tokens[i] == ")")
		{
			while (!tempStack.empty() && tempStack.top() != "(")
			{
				resultStack.push_back(tempStack.top());
				tempStack.pop();
			}
			tempStack.pop();
		}

		if (isOperator(tokens[i]))
		{
			while (!tempStack.empty() && getOpPriority(tempStack.top()) >= getOpPriority(tokens[i]))
			{
				resultStack.push_back(tempStack.top());
				tempStack.pop();
			}
			tempStack.push(tokens[i]);
		}
	}
	//pop any remaining operators from the stack and insert to outputlist
	while (!tempStack.empty())
	{
		resultStack.push_back(tempStack.top());
		tempStack.pop();
	}
	//Optional - Prints RPN expression
	for (unsigned int i = 0; i < resultStack.size(); i++)
	{
		cout << resultStack[i] << " ";
	}
	cout << "= ";
	return resultStack;
}

double evaluateRPN(vector<string> expression)
{
	double result = 0.0, n = 0.0;
	stack<double> s;
	//reverse(expression.begin(), expression.end());
	for (int i = 0; i < expression.size(); i++)
	{

		if (isDouble(expression[i]) == true)
		{
			n = stod(expression[i]);
			s.push(n);
		}
		if (expression[i] == "+")
		{
			double x = s.top();
			s.pop();
			double y = s.top();
			s.pop();
			result = x + y;
			s.push(result);
		}
		if (expression[i] == "-")
		{
			double x = s.top();
			s.pop();
			double y = s.top();
			s.pop();
			result = y - x;
			s.push(result);
		}
		if (expression[i] == "*")
		{
			double x = s.top();
			s.pop();
			double y = s.top();
			s.pop();
			result = x*y;
			s.push(result);
		}
		if (expression[i]== "/")
		{
			double x = s.top();
			s.pop();
			double y = s.top();
			s.pop();
			if (x != 0)
				result = y / x;
			else
			{
				cout << "Couldn't perform division by zero!" << endl;
				break;
			}
			s.push(result);
		}
		if (expression[i]== "^")
		{
			double x = s.top();
			s.pop();
			double y = s.top();
			s.pop();
			result = pow(y,x);
			s.push(result);
		}
		if (expression[i] == "#")
		{
			double x = s.top();
			s.pop();
			result = x*(-1);
			s.push(result);
		}
	}
	return result;
}

bool isDouble(const string& s)
{
	try
	{
		stod(s);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

vector<string> tokenize( string input)
{
	//Tokenizes input based on allowed characters
	vector<string> wordVector;
	int len = 0, i = 0, j = 0;
	for (i = 0; i < input.length(); i++)
	{
		//If [i] is a digit, ot iterates until it find a non digit non period
		if (isdigit(input[i]) || input[i] == '.')
		{
			j = i;
			while (isdigit(input[j]) || input[j] == '.')
			{
				len++;
				j++;
			}
			//negative sign case
			/*if (i == 1 && input[i - 1] == '-')
			{
				//input.at(i) = '#';
				//i--;
				len++;t
			}
			if (i > 1 && input[i - 1] == '-' && !isdigit(input[i - 2]))
			{
				input.at(i) = '#';
				i--;
				len++;
			*/
			//pushes number into stack
			wordVector.push_back(input.substr(i, len));
			i = j - 1;
			len = 0;
		}
		else
		{
			if (input[i] == '-')
			{
				if (i == 0)
					wordVector.push_back("#");
				if (i > 0 && i < input.length() - 1)
				{
					if (!isdigit(input[i - 1]) && isdigit(input[i + 1]))
						wordVector.push_back("#");
					else
						wordVector.push_back(input.substr(i, 1));
				}
			}
			else
				wordVector.push_back(input.substr(i, 1));
		}
	}

	return wordVector;
}

bool isValidSPChar(char letter)
{
	bool valid = false;
	for (int i = 0; i < allowedSPSymbols.length(); i++)
		if (letter == allowedSPSymbols[i])
			valid = true;
	return valid;
}

bool validateInput(string input)
{
	bool valid = true;
	int leftPar = 0, rightPar = 0;

	if (input == "" || input.empty() == true)
		return false;
	for (int i = 0; i < input.length(); i++)
	{
	
		//Not a digit
		if (!isdigit(input[i]))
		{
			//Not a digit & not an allowed sp char
			if (!isValidSPChar(input[i]))
				return false;
			//First character can only be an [(], a digit or [-] 
			if (i == 0)
			{
				//Not a digit, but a (
				if (input[i] == allowedSPSymbols[0] && input[i + 1] == allowedSPSymbols[1])
					return false;
				//Negative sign
				if (input[i] == allowedSPSymbols[6])
					if (!isdigit(input[i + 1]))
						return false;
				//No operators can be at the beginning of the expression
				for (int j = 1; j < allowedSPSymbols.length(); j++)
				{
					if (input[0] == allowedSPSymbols[j] && j != 6)
						return false;
				}
			}
			//Last character can only be an [)] or a digit
			if (i == input.length() - 1)
			{
				for (int j = 0; j < allowedSPSymbols.length(); j++)
				{
					if (j != 1 && input[i] == allowedSPSymbols[j])
						return false;
				}
			}

			
			//Not a digit, but a (
			if (input[i] == allowedSPSymbols[0])
				leftPar++;
			//Not a digit, but a )
			if (input[i] == allowedSPSymbols[1])
			{
				rightPar++;
				//Enforcing case that there has to be an operator between sets of parentheses
				if (i < input.length() - 1 && input[i + 1] == allowedSPSymbols[0])
					return false;
			}
		}
		if (i>0 && i < input.length() - 1)
		{
			//Negative sign
			if (input[i] == allowedSPSymbols[6])
				//if next char is not a digit AND next char is not [(]
				if (!isdigit(input[i + 1]) && input[i + 1] != allowedSPSymbols[0])
					return false;
			//() case
			if ((input[i] == allowedSPSymbols[0] && input[i + 1] == allowedSPSymbols[1]))
				return false;
			//#( case
			if (input[i] == allowedSPSymbols[0] && isdigit(input[i - 1]))
				return false;
			//)# case
			if (input[i] == allowedSPSymbols[1] && isdigit(input[i + 1]))
				return false;
			//Operators +*/^ can only have a DIGIT OR [)] in the left OR a DIGIT, [(] or [-] on the right side
			for (int j = 2; j < allowedSPSymbols.length() - 2; j++)
			{
				//If [i] is an allowed operator
				if (input[i] == allowedSPSymbols[j])
				{
					//but the next char is not a digit AND next char is not [(]
					if(!isdigit(input[i + 1]) && (input[i + 1] != allowedSPSymbols[0]) && (input[i + 1] != allowedSPSymbols[6]))
						return false;
					//OR the previous char is not a digit AND previous char is not [(]
					else if (!isdigit(input[i - 1]) && (input[i - 1] != allowedSPSymbols[1]) && (input[i + 1] != allowedSPSymbols[6]))
						return false;
				}
			}
			//[.] can only have digits on both sides
			if (input[i] == allowedSPSymbols[7])
			{
				if (!isdigit(input[i - 1]) || !isdigit(input[i + 1]))
					return false;
			}
		}
		
	}
	if (leftPar != rightPar)
		return false;

	return true;
}

bool tryParsingNum(const string &symbol)
{
	bool isNumber = false;
	for (unsigned int i = 0; i < symbol.size(); i++)
	{
		if (!isdigit(symbol[i]))
		{
			isNumber = false;
		}
		else
		{
			isNumber = true;
		}
	}
	return isNumber;
}

int getOpPriority(const string &c)
{
	if (c == "^" || c == "#")
	{
		return 3;
	}
	if (c == "*" || c == "/")
	{
		return 2;
	}
	if (c == "+" || c == "-")
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//
bool isOperator(const string &c)
{
	return (c == "+" || c == "-" || c == "*" || c == "/" || c == "^" || c == "#");
}
