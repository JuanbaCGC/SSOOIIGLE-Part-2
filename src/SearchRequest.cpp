/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: SearchRequest.cpp
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 29/04/2021
*
* Purpose			: Class with the information of the SearchRequest
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

#include "SearchRequest.h"

/* Constructor of the class */
SearchRequest::SearchRequest(int user_id, std::string word, int priority){
	this->user_id = user_id;
	this->word = word;
	this->priority = priority;
}

/* Methot that return the user id of the search request */
int SearchRequest::get_user_id(){
	return user_id;
}

/* Methot that return the id of the search request */
int SearchRequest::get_search_id(){
	return search_id;
}

/* Methot that return the word of the search request */
std::string SearchRequest::get_word(){
	return word;
}

/* Methot that return the priority of the search request */
int SearchRequest::get_priority(){
	return priority;
}

/* Method that set the request_id and equals it to the atomic variable request id. Finally, it increase this variable */
void SearchRequest::set_request_id(){
	this->search_id = global_request_id;
	global_request_id++;
}

/* Methot that show the information of the search request */
void SearchRequest::toString(){
	std::cout << "SearchRequest: user id " << user_id << " ,search id " << search_id << " ,searched word " << word << " and priority " << priority;
}
