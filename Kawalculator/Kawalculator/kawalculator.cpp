#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string input = "";
	char code = ' ';
	
	/*
	for (int i = 1; i < argc; i++)
		input += argv[i];
	cout << input << endl;
	*/
	cout << "\t\tWELCOME TO KAWALKULATOR\t" << endl;
	while (true) {
		
		cout << "\n\tEnter new expression: "; getline(cin, input);
		cout << '\t' << input << endl<<endl;
		
		while (true) {
			cout << "\tDo you want to enter a new expression [y/n]: ";  
			code = cin.get();
			if (code == 'n' || code == 'N')
				return 0;
			else if (code == 'y' || code == 'Y')
				break;
			else
			{
				cout << "\tInvalid option." << endl;
				cin.ignore();
			}
		}
	}
}