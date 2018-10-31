#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//Constant Values
//Allowed characters
string allowedSPSymbols = "()+*/^-.";

//Function Prototypes
bool isValidSPChar(char letter);
bool validateInput(string input);


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

		cout << '\t' << input << " = " <<endl <<endl;
		
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
				//Negative sign
				if (input[i] == allowedSPSymbols[6])
					if (!isdigit(input[i + 1]))
						return false;
				for (int j = 1; j < allowedSPSymbols.length(); j++)
				{
					if (input[0] == allowedSPSymbols[j] && j != 6)
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
				if (!isdigit(input[i + 1]) || !isdigit(input[i - 1]))
					return false;
			}
		}
		
	}
	if (leftPar != rightPar)
		return false;

	return true;
}