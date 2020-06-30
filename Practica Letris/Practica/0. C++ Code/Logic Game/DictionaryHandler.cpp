#include "DictionaryHandler.h"
#include <iostream>
DictionaryHandler::DictionaryHandler()
{
}

bool DictionaryHandler::OpenDictionary(int langId)
{
	m_loaded = false;
	switch (langId)
	{
		case 0:
			cout << "OPENING CATALAN DIC" << endl;
			dictionary.open("./data/Dictionaries/Catalan.dic");
			break;
		case 1:
			cout << "OPENING SPANISH DIC" << endl;
			dictionary.open("./data/Dictionaries/Spanish.dic");
			break;
		case 2:
			cout << "OPENING ENGLISH DIC" << endl;
			dictionary.open("./data/Dictionaries/English.dic");
			break;

		default:
			break;	
	}

	if (dictionary.is_open()) {
		string input;
		dictionary >> input;
		dictionaryWord.push_back(input);
		while (!dictionary.eof())
		{
			dictionaryWord.push_back(input);
			dictionary >> input;
		}
		dictionary.close();
		m_loaded = true;
	}
	else {
		cout << "Dictionary is not open" << endl;
	}
	return m_loaded;
}

bool DictionaryHandler::checkWordOnDictionary(string word)
{
	bool hasBeenFound = false;
	cout << "Checking word in dictionary " << word << endl;
	if (dictionaryWord.size() > 0) {
		cout << "DICTIONARY SIZE " << dictionaryWord.size() << endl;
		for (int i = 0; i < dictionaryWord.size(); i++)
		{
			if (word == dictionaryWord[i]) {
				cout << "IS INSIDE THE DICTIONARY "  << dictionaryWord[i] << endl;
				hasBeenFound = true;
				break;
			}
		}
	}
	return hasBeenFound;
}


