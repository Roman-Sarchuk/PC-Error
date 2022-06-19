#include <iostream>
#include <string>
using namespace std;

// Enums
enum ErrStatus {
    NONE,
    SAFE,
    MEDIUM,
    DANGEROUS
};

// Global variables
short const ESIZE = 4;
string err[ESIZE];
ErrStatus status[ESIZE]{ ErrStatus::NONE, ErrStatus::NONE , ErrStatus::NONE , ErrStatus::NONE };

// Structures
short const VSIZE = 3;
struct QstList
{
    string Questions;
    string Version[VSIZE];
};

// Functions
short ProtcInput(short max)
{
	short vers;
	while (true) {
		cout << "> ";
		cin >> vers;
		cin.clear();
		cin.ignore(32767, '\n');
		if (vers >= 1 && vers <= max)
			break;
		cout << "! Число має бути від 1 до " << max << " !" << endl;
	}
	cout << endl;
	return vers;
}

short Ask(QstList qst)	// Довге запитання
{
	short vcount = 0;
	cout << qst.Questions << endl;
	for (int i = 0; i < VSIZE; i++)
		if (qst.Version[i] != "")
		{
			vcount++;
			cout << qst.Version[i] << endl;
		}
	return ProtcInput(vcount);
}

short Ask(string qst)	// Коротке запитання
{
	cout << qst << endl;
	cout << "1) Так" << endl << "2) Ні" << endl;
	return ProtcInput(2);
}
