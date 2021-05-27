/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: ProtectedReplySearchVector.cpp
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 10/05/2021
*
* Purpose			: Class where the methods of the ProtectedReplySearch.h are implemented.
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

#include "ProtectedReplySearchVector.h"

/* Constructor of the class */
ProtectedReplySearchVector::ProtectedReplySearchVector(){}

/* Method that return the ReplySearch vector */
std::vector <ReplySearch> ProtectedReplySearchVector::get_vector(){
	return reply_search_vector;
}

/* Method that insert a reply search in the protected vector */
void ProtectedReplySearchVector::insert(ReplySearch r){
	std::lock_guard<std::mutex> lk(m);
	reply_search_vector.push_back(r);
}

/* Method that indicates if the reply request exists*/
bool ProtectedReplySearchVector::findReply(int user_id){
	bool find = false;
	for(int i = 0; i < reply_search_vector.size(); i++){
		if(reply_search_vector[i].get_user_id() == user_id){
			find = true;
			break;
		}
	}
	return find;
}

/* Method that return a reply request with a certain user id */
ReplySearch ProtectedReplySearchVector::getReply(int user_id){
	std::vector <priority_queue<CSearch, vector<CSearch>,compareFunction>> pq_vector;
	ReplySearch reply_search(-1, pq_vector);
	std::lock_guard<std::mutex> lk(m);
	for(int i = 0; i < reply_search_vector.size(); i++){
		if(reply_search_vector[i].get_user_id() == user_id){
			reply_search = reply_search_vector[i];
			auto elem_to_remove = reply_search_vector.begin() + i;
			if(elem_to_remove != reply_search_vector.end()){
				reply_search_vector.erase(elem_to_remove);
			}
			break;
		}
	}
	return reply_search;
}
