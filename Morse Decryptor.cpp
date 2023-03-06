Morse Decryptor.cpp


// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <bitset>
#include <tuple>
#include <regex>
using namespace std;

        

    
    class FileHandler
    {
    private:
        long size;
        unsigned char* memblock;
        vector<string> binary;
        vector<string> morseArr;
        vector<char> chars;
        string s = "";
        string bin;
        string efile; 
        string mfile;
        
        string ch;
        string m;

        string line;
        smatch match;

    public:

        string word;
        vector<tuple<string, string>> morse;

        string CBinaryFiles()
        {
            efile = "Morse.bin";

            ifstream file(efile, ios::binary);

            if (file.is_open())
            {
                file.seekg(0, ios::end);
                size = file.tellg();
                memblock = new unsigned char[size];
                file.seekg(0, ios::beg);
                file.read((char*)memblock, size);
                string s(reinterpret_cast<char*>(memblock));
                word = s;
                file.close();
                delete[] memblock;
            }
            else
            {
                cout << "EncryptBin.bin not found";
            }
            return word;
        }

        vector<tuple<string, string>> MorseFile()
        {
            mfile = "MorseMap.txt";
            ifstream file(mfile);

            if (file.is_open())
            {
                while (getline(file, line))
                {
                    regex r1("([A-Z0-9!$&:;?@=])");
                    regex_search(line, match, r1);
                    s = match.str();
                    if (s != "" && s != ".")
                    {
                        ch = s;
                        regex r2("([.-]+)");
                        regex_search(line, match, r2);
                        s = match.str(1);
                        m = s;
                        morse.push_back(make_tuple(ch, m));
                    }
                }
                file.close();
            }
            else
            {
                cout << "MorseMap.txt not found";
            }
            return morse;
        }
    };

    class Decryptor
    {
    private:
        string decrypted;
        bitset<8> bits;
        vector<string> morse;
        vector<string> morseArr;
        string p;
        string m;
        string t;

    public:

        string charToBin(char c)
        {
            bitset<8> bits = c;
            return bits.to_string();
        }

        void decrypt(string text, vector<tuple<string, string>>& v)
        {
            for (int i = 0; i < text.length(); i++)
            {
                string bin = charToBin(text[i]);
                t += bin;
            }

            int count = 0;
            for (int i = 0; i < t.size(); i += 2)
            {
                if (t[i] == '0' and t[i + 1] == '1')
                {
                    morse.insert(morse.begin() + count, "-");
                }
                else if (t[i] == '1' and t[i + 1] == '0')
                {
                    morse.insert(morse.begin() + count, ".");
                }
                else if (t[i] == '0' and t[i + 1] == '0')
                {
                    morse.insert(morse.begin() + count, "s");
                }
                else if (t[i] == '1' and t[i + 1] == '1')
                {
                    morse.insert(morse.begin() + count, " ");
                }
                count++;
            }

            for (int i = 0; i < morse.size(); i++)
            {
                if (morse[i] != "s")
                {
                    m += morse[i];
                }
                else
                {
                    for (int i = 0; i < v.size(); i++)
                    {
                        if (m == get<1>(v[i]))
                        {
                            cout << get<0>(v[i]);
                        }
                    }
                    m = "";
                }
            }

            
        }
    };

    void main()
    {
        vector<tuple<string, string>> v;
        FileHandler word;
        Decryptor d;
        string text;

        text = word.CBinaryFiles();
        v = word.MorseFile();

        d.decrypt(text, v);
        
    }