#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//Constant Values
//Allowed characters
char allowedSPSymbols[] = { '(',')','+','-','*','/','^','.' };
int spsLength = sizeof(allowedSPSymbols) / sizeof(allowedSPSymbols[0]);

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
	

	for (int i = 0; i < spsLength; i++)
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
			//First character can only be an ( or a digit
			if (i == 0)
			{
				for (int j = 1; j < spsLength; j++)
				{
					if (input[0] == allowedSPSymbols[j])
						return false;
				}
			}
			//Not a digit & not an allowd sp char
			if(!isValidSPChar(input[i]))
				return false;
			//Not a digit, but a (
			else if (input[i] == allowedSPSymbols[0])
				leftPar++;
			//Not a digit, but a )
			else if (input[i] == allowedSPSymbols[1])
				rightPar++;
		}
		if (i>0 && i < input.length() - 1)
		{
			//() case
			if ((input[i] == allowedSPSymbols[0] && input[i + 1] == allowedSPSymbols[1]))
				return false;
			//Regular operator can only have a digit or ) in the left OR a digit or ( on the right
			for (int j = 2; j < spsLength-1; j++)
			{
				if (input[i] == allowedSPSymbols[j])
				{
					if(!isdigit(input[i + 1]) && (input[i + 1] != allowedSPSymbols[0]))
						return false;
					else if (!isdigit(input[i - 1]) && (input[i - 1] != allowedSPSymbols[1]))
						return false;
				}
			}
			//[.] can only have digits on both sides
			if (input[i] == allowedSPSymbols[7])
			{
				if (!isdigit(input[i + 1]) && !isdigit(input[i - 1]))
					return false;
			}
		}
		
	}
	if (leftPar != rightPar)
		return false;

	return true;
}