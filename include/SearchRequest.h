/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: SearchRequest.h
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 29/04/2021
*
* Purpose			: this class has the information of the SearchRequest that the users make. 
*				  
*
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

#ifndef SEARCHREQUEST_H
#define SEARCHREQUEST_H

class  SearchRequest{
	private:
		int user_id;		/* Id of the user who is going to make the request */ 
		int search_id;		/* Identifier of the SearchRequest (it's unique) */
		std::string word;	/* String where the word that is going to be searched in the differents text is going to be stored */
		int priority;		/* Priority of the request, it can be: 
						- 0 if it is a search request of a free user
						- 1 if it is a search request of a prime/premium user */
	public:
		/* Constructor of the class */
		SearchRequest(int user_id, std::string word, int priority);
		
		/* Methot that return the user id of the search request */
		int get_user_id();
		
		/* Methot that return the id of the search request */
		int get_search_id();
		
		/* Methot that return the word of the search request */
		std::string get_word();
		
		/* Methot that return the priority of the search request */
		int get_priority();
		
		/* Method that set the request_id and equals it to the atomic variable request id. Finally, it increase this variable */
		void set_request_id();
		
		/* Methot that show the information of the search request */
		void toString();
};

#endif

