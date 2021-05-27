/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: ReplySearch.cpp
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 10/05/2021
*
* Purpose			: Class where the methods of the ReplySearch.h are implemented.
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

#include "ReplySearch.h"

/* Constructor method of the class */
ReplySearch::ReplySearch(int user_id, std::vector <priority_queue<CSearch, vector<CSearch>,compareFunction>> pq_vector){
	this->user_id = user_id;
	this->pq_vector = pq_vector;
}

/* Method that returns the user id of the Reply Search */
int ReplySearch::get_user_id(){
	return user_id;
}
