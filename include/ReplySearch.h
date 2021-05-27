/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: ReplySearch.h
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 10/05/2021
*
* Purpose			: Class has been created to send the results of the coincidences 
*				  from the SearchSystem to the Users.
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/
#ifndef REPLYSEARCH_H
#define REPLYSEARCH_H

class ReplySearch{
	private:
		/* Id of the user that will get the ReplySearch */
		int user_id;
	public:
		/* Vector of priority queues where the coincidences in the differents books are going to be stored */
		std::vector <priority_queue<CSearch, vector<CSearch>,compareFunction>> pq_vector;
		
		/* Constructor method of the class */
		ReplySearch(int user_id, std::vector <priority_queue<CSearch, vector<CSearch>,compareFunction>> pq_vector);
		
		/* Method that returns the user id of the Reply Search */
		int get_user_id();
};

#endif
