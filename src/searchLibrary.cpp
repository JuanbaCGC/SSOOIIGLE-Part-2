/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: SearchLibrary.cpp
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 29/03/2021
*
* Purpose			: Class with the methods used to search in the diferents texts.
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/
#include <stdio.h>
#include <sstream>
#include <fstream>
#include "CSearch.h"
#include "CThread.h"
#include "compareFunction.h"
#include "searchLibrary.h"

/* Method that open the file and return a vector with all the lines of the text */
std::vector<std::string> openFile(std::string file){	     
	std::ifstream ifs;
	std::vector<std::string> arrayLine;
	std::string line;
	ifs.open(file, std::ios::in);
	if(ifs.fail()){
		std::cout << REDB << NC << std::endl;
		std::cerr << REDB << "Error, the file " << file << " could not be open" << NC << std::endl;
	}else{
		while(!ifs.eof()){
			getline(ifs, line);
			arrayLine.insert(arrayLine.end(), line);
		}
	}
	return arrayLine;
}

/* Methot that convert the line in a string vector that each position is a word of the line */
std::vector<std::string> split(std::string str){	
	std::vector<std::string> string_vector;
	std::istringstream isstream(str);
	std::string palabra;
	while(isstream >> palabra){
		string_vector.push_back(palabra);
	}
	return string_vector;
}

/* Method that convert a string int the same string with upper case */
std::string convertString(std::string s){	
	for(int i = 0;i<s.length();i++){
		s[i]=toupper(s[i]);
	}
	return s;
}

/* Method that compare all the words of a line */
priority_queue<CSearch, vector<CSearch>,compareFunction> findWordInLine(std::vector<std::string> string_vector ,std::string searched_word, int id_linea, int thread_id, int lower_limit, int upper_limit, priority_queue<CSearch, vector<CSearch>,compareFunction> pq){ 
	std::string text;
	searched_word = convertString(searched_word);
	for(int i = 0; i < string_vector.size();i++){
		if(compareWords(searched_word, string_vector[i]) == true) {	
			if(i == 0 && string_vector.size()>1){		/* If the found word is the first word of the line and the line has more than one word... */
				text = string_vector[i] + " " + string_vector[i+1] + " ...";
			}
			else if(string_vector.size() ==1)		/* If there is only a word in the line... */
				text = string_vector[i] + " ...";
			else if(i+1==string_vector.size())		/* If the found word is the last word of the line... */
				text = string_vector[i-1] + " " + string_vector[i] + " ...";
			else 						
				text = string_vector[i-1] + " " + string_vector[i] + " " + string_vector[i+1] + " ...";
			CThread cthread(1, 0, upper_limit);	
			CSearch search(id_linea+1, text, i, cthread);
			pq.push(search);
		}
	}
	return pq;
}

/* Method that compare two words and it return true if the words are the same */
bool compareWords(std::string word, std::string result){	
	bool coincidence_found = false;
	std::vector<std::string> symbols = {"!","¡","·","$","%","&","/","(",")","=","?","¿",",","^","]","[","-","_","@","*","|",">","<","#","+","{","}","¬",".", ";",":"};
	/* Vector with all the simbols that the searched word could have at the begining or at the end */	
	result = convertString(result);
	for(int i = 0; i < symbols.size() && coincidence_found == false;i++){
		if(result == word ||result == word + symbols[i] || result == symbols[i] + word)
			coincidence_found = true;
	}
	return coincidence_found;
}

