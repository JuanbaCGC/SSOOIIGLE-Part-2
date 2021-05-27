/************************************************************************
* Project			: Practica 2 de Sistemas Operativos II
*
* Program name			: searchLibrary.h
*
* Author			: Juan Bautista Castaño García-Cervigón
*
* Date created:		: 13/04/2021
*
* Purpose			: File where the functions of the 
*				  searchLibrary are showed. The methos will
*				  help to handle with the .txt and find the
*				  coincidences.
*				  			
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

#include <stdio.h>
#include <string>
#include <queue>
#include "compareFunction.h"

/* Method that open the file and return a vector with all the lines of the text */
std::vector<std::string> openFile(std::string file);

/* Methot that convert the line in a string vector that each position is a word of the line */
std::vector<std::string> split(std::string str);

/* Method that convert a string int the same string with upper case */
std::string convertString(std::string s);

/* Method that compare all the words of a line */
priority_queue<CSearch, vector<CSearch>,compareFunction> findWordInLine(std::vector<std::string> string_vector ,std::string searched_word, int id_linea, int thread_id, int lower_limit, int upper_limit, priority_queue<CSearch, vector<CSearch>,compareFunction> pq);

/* Method that compare two words and it return true if the words are the same */
bool compareWords(std::string word, std::string result);
