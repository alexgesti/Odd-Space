#ifndef __ENCRYPT_H_
#define __ENCRYPT_H_

#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>

using namespace std;

class Encrypt {
public:
	Encrypt() {};
	~Encrypt() {};

	string EncryptFile(string inputFileName, string outputFileName)
	{
		string temp = inputFileName;
		int status = remove(outputFileName.c_str());

		if (status == 0)
			cout<<"\nFile Deleted Successfully!";
		else
			cout<<"\nErorr Occurred!";
		cout << endl;

		GenerateKey();

		char c;
		ifstream fin;
		ofstream fout;
		fin.open(inputFileName.c_str(), ios::binary);
		inputFileName = outputFileName;
		fout.open(inputFileName.c_str(), ios::binary);
		while (!fin.eof())
		{
			fin >> noskipws >> c;
			int temp = (c + key);

			// If temp > 256 c++ will automatically do temp = temp - 256
			fout << (char)temp;
		}
		fin.close();
		fout.close();

		remove(temp.c_str());

		return outputFileName;
	}

	string Decrypt(string inputFileName, string outputFileName)
	{
		string temp = inputFileName;

		char c;
		ifstream fin;
		ofstream fout;
		fin.open(inputFileName.c_str(), ios::binary);
		if (fin.fail()) return "";
		inputFileName = outputFileName;
		fout.open(inputFileName.c_str(), ios::binary);

		//ATERNATIVE KEY CALCULATOR, MAYBE MORE EFICIENT
		// If we closed the game and want to continue we have to guess the key
		/*if (key == 0)
		{
			char firstChar;
			fin >> noskipws >> firstChar;
			// First letter of XML is allways '<' or 60 in ASCII
			int AsciiExpected = 60;

			// Calculate key
			key = (int)firstChar - AsciiExpected;

			// In c++ if we try to write a char over 256, the number gets readjusted, so for example: 273 = 17 (273 - 256)
			if (key < 0) key = 256 + key;
		}*/

		while (!fin.eof())
		{
			fin >> noskipws >> c;

			// If we closed the game and want to continue we have to guess the key
			if (key == 0)
			{
				// First letter of XML is allways '<' or 60 in ASCII
				int AsciiExpected = 60;

				// Calculate key
				key = (int)c - AsciiExpected;

				// In c++ if we try to write a char over 256, the number gets readjusted, so for example: 273 = 17 (273 - 256)
				if (key < 0) key = 256 + key;
			}

			int temp = (c - key);
			fout << (char)temp;
		}
		fin.close();
		fout.close();

		int status = remove(temp.c_str());

		if (status == 0)
			cout<<"\nFile Deleted Successfully!";
		else
			cout<<"\nErorr Occurred!";
		cout << endl;

		return outputFileName;
	}

private:
	void GenerateKey()
	{
		key = rand() % 255 + 1; //Max is 256
	}

	/*int GetKey()
	{
		if (key != 0) return key;
		else return 0;
	}*/

	int key = 0;
	string inputFileName;
};

#endif //__ENCRYPT_H_