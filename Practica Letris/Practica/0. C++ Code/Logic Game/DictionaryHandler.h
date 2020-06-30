#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "../Graphic Lib/libreria.h"
using namespace std;
class DictionaryHandler
{
public:
	DictionaryHandler();
	bool OpenDictionary(int langId);
	bool checkWordOnDictionary(string word);
	bool hasBeenLoaded() { return m_loaded; };
	void resetDictionary() { dictionaryWord.clear(); };
private:
	ifstream dictionary;
	vector<string> dictionaryWord;
	bool m_loaded;
};

