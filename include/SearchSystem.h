/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: SearchSystem.h
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 29/04/2021
*
* Purpose			: Class that is going to implement the SearchSystem of the program.
*				  The instances of this class are going to be blocked until a SearchRequest
*				  is entered in the search_request_vector. When the lambda function is fullfiled
*				  it will take a SearchRequest of the vector and will search in the differents books.
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

#ifndef SEARCHSYSTEM_H
#define SEARCHSYSTEM_H

class SearchSystem{
	public:
		/* Vector of priority queues where the coincidences of the texts are going to be stored */
		std::vector <priority_queue<CSearch, vector<CSearch>,compareFunction>> pq_vector;
		
		/* Method that do the search acording to the SearchRequest, finally it returns the limit of the user */
		int do_search(SearchRequest r, GeneralUser user, std::string text, int limit, priority_queue<CSearch, vector<CSearch>,compareFunction> &pq_pointer);
		
		/* Method that return a GeneralUser passing his id by parameter */
		GeneralUser get_user(int id);
		
		/* Method that returns the SearchRequest acording to the relation 80-20 (80% premium requests - 20% free requests)  */ 
		SearchRequest get_request();
		
		/* Method that do the search in the differents books */
		void do_searchs_in_books(SearchRequest sr);
		
		/* Method that fill the pq_vector with priority queues */
		void fill_pq_vector();
		
		/* Overload the operator */
		void operator()();
};

#endif


