#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include <tuple>

using namespace std;


vector<tuple<char, string, bitset<8>, int>> txtFile(string tfile){
	vector<tuple<char, string, bitset<8>, int>> vTup;
	ifstream fin(tfile);

	if(fin.is_open() == false)
		cout << "File not found." << endl;
	else {
		int count = 0;

		while(fin.eof() == false){
			char character;
			string morse = "";
			
			fin >> character;
			fin >> morse;
			
			vTup.push_back(make_tuple(character, morse, 00000000, count++));
			
			string oneLine;
			getline(fin, oneLine); 
		}
	}

	return vTup;
}

string binaryFiles(string bfile, vector<tuple<char, string, bitset<8>, int>>& vTup){
	long size;
	unsigned char* memblock;

	string morse = "";
	string text = "";

	ifstream file(bfile, ios::binary);

	if(file.is_open()){
		file.seekg(0, ios::end);
		size = file.tellg();
		memblock = new unsigned char[size];
		file.seekg(0, ios::beg);
		file.read((char*) memblock, size);
		
		bitset<8> isolate;
		int binThresh = 8;
		string morse = "";

		for(int i=0; i<size; i++) {  
            		bitset<8> charBin(memblock[i]);
			bitset<8> check = bitset<8>("11000000");
			bitset<8> bCheck;

			for(int i=0; i<4 ; i++){
				if(i == 0)
					isolate = ((charBin & check) >> (binThresh -= 2)).to_ulong();
				else {
					check = check >> 2;
					bCheck = bitset<8>(check.to_string());
					isolate = ((charBin & bCheck) >> (binThresh -= 2)).to_ulong();
				}

				if(isolate == 1)
					morse += "-";
				else if(isolate == 2)
					morse += ".";
				else if(isolate == 0 || isolate == 3){
					for(tuple<char, string, bitset<8>, int> t : vTup){
						if(get<1>(t) == morse){
							text += string(1, get<0>(t)) + " ";
							
							if(isolate == 0)
								get<2>(t) = charBin;

							morse = "";
						}
					}
				}
			}

			binThresh = 8;
        }

		file.close();
		delete[] memblock;
	}

	return text;
}

int main(){
	vector<tuple<char, string, bitset<8>, int>> vTup = txtFile("morse_alpha.txt");
	string txt = binaryFiles("Morse.bin", vTup);
	cout << txt << endl;

    return 0;
}

