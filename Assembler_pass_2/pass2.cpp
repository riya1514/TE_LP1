
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
using namespace std;
class Pass2
{
	vector<pair<string, string>>SymTab;
	vector<pair<string, string>>literaltab;
	ifstream sym, lit, fin;
	ofstream fout;
public:
	Pass2()
	{
		fin.open("input.txt");
		sym.open("symboltab.txt");
		lit.open("literaltab.txt");
		fout.open("output.txt");
		if (fin.fail() || sym.fail() || fout.fail() || lit.fail())
		{
			cout << "\nError in opening file";
			exit(1);
		}
		cout << "Files opened successfully!!";
		GetSymTab();
		GetLitTab();
	}
	void GetLitTab()
	{
		string line,literal,location;
		while (getline(lit, line))
		{
			stringstream ss(line);
			ss >> literal >> location;
			literaltab.push_back({ literal,location });
		}
	} 
	void GetSymTab()
	{
		string line,symbol,location,word;
		while (getline(sym, line))
		{
			stringstream ss(line);
			ss >> word >> symbol >> location;
			SymTab.push_back({ symbol,location });
		}
	}
	void genearate()
	{
		fout.seekp(0, ios::beg);
		string line,location,opcode,word;
		while (getline(fin, line))
		{
			fout << "\n";
			stringstream ss(line);
			ss >> location>>opcode;
			if (opcode == "(IS,")
			{
				ss >> word;
				fout << location << " " << word.substr(0, word.length() - 1);
				while (ss >> word)
				{
					if (word == "(S,")
					{
						ss >> word;
						int index = stoi(word.substr(0, word.length() - 1))-1;
						fout << " " << SymTab[index].second;

					}
					else if (word == "(L,")
					{
						ss >> word;
						int index = stoi(word.substr(0, word.length() - 1))-1;
						fout << " " << literaltab[index].second;

					}
					else if (word == "(C,")
					{
                        ss>>word;
                        fout<<word.substr(0,word.length()-1);
					}
					else
					{
						fout << " "<<word.substr(1,1);
					}
				}
			}
			else if (opcode == "(DL,")
			{
				ss >> word;
				if (word == "02)")
				{
					fout << location << " 00 0 000 ";
				}
				else if (word == "01)")
				{
					fout << location << " 00 0 ";
					ss >> word;
					ss >> word;
					fout << word.substr(0, word.length() - 1);
				}
			}
			else
			{
				fout << "No machine code";
			}
		}
	}
};
int main()
{
	Pass2 obj;
	 
	obj.genearate();
	cout << "\nPass 2 of two pass assembler done successfully!";

	return 0;
}
