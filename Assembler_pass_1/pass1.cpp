#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

class Pass1
{
    int litindex = 0;
    map<string, pair<int, int>> SymTab;
    ifstream fin;
    ofstream fout,sym,lit,pool;
    int LC = -1;
    map<string, pair<string, string>> opcode;
    vector<pair<string, int>> LitTab;
    vector<string> pooltab;

public:
    void initialize()
    {
        opcode = {
            {"STOP", {"IS", "00"}}, {"ADD", {"IS", "01"}}, {"SUB", {"IS", "02"}}, {"MULT", {"IS", "03"}}, {"MOVER", {"IS", "04"}}, {"MOVEM", {"IS", "05"}}, {"COMP", {"IS", "06"}}, {"BC", {"IS", "07"}}, {"DIV", {"IS", "08"}}, {"READ", {"IS", "09"}}, {"PRINT", {"IS", "10"}}, {"START", {"AD", "01"}}, {"END", {"AD", "02"}}, {"ORIGIN", {"AD", "03"}}, {"EQU", {"AD", "04"}}, {"LTORG", {"AD", "05"}}, {"DC", {"DL", "01"}}, {"DS", {"DL", "02"}}, {"AREG", {"1", ""}}, {"BREG", {"2", ""}}, {"CREG", {"3", ""}}, {"DREG", {"4", ""}}, {"LT", {"1", ""}}, {"LE", {"2", ""}}, {"EQ", {"3", ""}}, {"GT", {"4", ""}}, {"GE", {"5", ""}}, {"ANY", {"6", ""}}};
    }

    void Tokenize()
    {
        fout.open("output.txt");
        fin.open("input.txt");
        string line, word, label;
        while (getline(fin, line))
        {
            stringstream ss(line);
            ss >> word;

            // Label processing
            if (opcode.count(word) == 0)
            {
                if (SymTab.count(word) == 0)
                {
                    SymTab[word] = {LC, SymTab.size() + 1};
                }
                else
                {
                    SymTab[word].first = LC;
                }
                label = word;
                ss >> word;
            }

            string operation = word;
            if (operation == "START")
            {
                ss >> word;
                LC = stoi(word);
                fout << "    (" << opcode[operation].first << "," << opcode[operation].second << ")";
            }
            else if (operation == "END")
            {
                fout << "\n" << "    (" << opcode[operation].first << "," << opcode[operation].second << ")";
                pooltab.push_back("#" + to_string(litindex + 1));

                while (litindex < LitTab.size())
                {
                    LitTab[litindex].second = LC;
                    fout << "\n" << LC << " (DL,01) (C," << LitTab[litindex].first.substr(2,1) << ")";
                    litindex++;
                    LC++;
                }
                return;
            }
            else if (operation == "DC")
            {
                fout << "\n" << LC << " (" << opcode[operation].first << "," << opcode[operation].second << ") " << "(C,";
                ss >> word;
                fout << word << ")";
            }
            else if (operation == "DS")
            {
                fout << "\n" << LC << " (" << opcode[operation].first << "," << opcode[operation].second << ") " << "(C,";
                ss >> word;
                fout << word << ")";
                LC += stoi(word);
            }
            else if (operation == "ORIGIN")
            {
                fout << endl << "    (" << opcode[operation].first << "," << opcode[operation].second << ") ";
                ss >> word;
                fout << word;
                int ind = -1;
                char op;
                for (int i = 0; i < word.length(); i++)
                {
                    if (word[i] == '+' || word[i] == '-')
                    {
                        op = word[i];
                        ind = i;
                        break;
                    }
                }
                string beforeind = word.substr(0, ind);
                string afterind = ind != -1 ? word.substr(ind + 1) : "";
                LC = SymTab[beforeind].first;
                if (afterind != "")
                {
                    LC += (op == '+' ? stoi(afterind) : -stoi(afterind));
                }
            }
            else if (operation == "EQU")
            {
                ss >> word;
                int ind = -1;
                char op;
                for (int i = 0; i < word.length(); i++)
                {
                    if (word[i] == '+' || word[i] == '-')
                    {
                        op = word[i];
                        ind = i;
                        break;
                    }
                }
                string beforeind = word.substr(0, ind);
                string afterind = ind != -1 ? word.substr(ind + 1) : "";
                int temp = SymTab[beforeind].first;
                if (afterind != "")
                {
                    temp += (op == '+' ? stoi(afterind) : -stoi(afterind));
                }
                SymTab[label].first = temp;
            }
            else if (operation == "LTORG")
            {
                pooltab.push_back("#" + to_string(litindex + 1));
                while (litindex < LitTab.size())
                {
                    LitTab[litindex].second = LC;
                    fout << "\n" << LC << " (DL,01) (C," << LitTab[litindex].first.substr(2,1) << ")";
                    LC++;
                    litindex++;
                }
            }
            else
            {
                if (opcode.count(word) > 0)
                {
                    fout << endl
                         << LC << " (" << opcode[word].first << "," << opcode[word].second << ")";
                    while (ss >> word)
                    {
                        if (opcode.count(word) > 0)
                        {
                            fout << " (" << opcode[word].first << "," << opcode[word].second << ")";
                        }
                        else if (word.find("=") != string::npos)
                        {
                            LitTab.push_back({word, LC});
                            fout << " (L," << LitTab.size() << ")";
                        }
                        else
                        {
                            if (SymTab.count(word) == 0)
                            {
                                SymTab[word] = {LC, SymTab.size() + 1};
                            }
                            fout << " (S," << SymTab[word].second << ")";
                        }
                    }
                }
                LC++;
            }
        }
    }

    void readSymTab()
    {
        sym.open("symboltab.txt");
        for (auto it : SymTab)
        {
            sym << "\n" <<it.second.second <<" "<< it.first << " " << it.second.first;
        }
    }

    void displayLitTab()
    {
        lit.open("litraltab.txt");
        for (auto it : LitTab)
        {
            lit << endl << it.first << " " << it.second;
        }
    }

    void displayPoolTab()
    {
        pool.open("pooltab.txt");
        for (int i = 0; i < pooltab.size(); i++)
        {
            pool << "\n" << pooltab[i];
        }
    }
};

int main()
{
    Pass1 p1;

    p1.initialize();
    p1.Tokenize();
    p1.readSymTab();
    p1.displayLitTab();
    p1.displayPoolTab();

    cout<<"Pass 1 of two pass assembler done successfully!";

    return 0;
}
