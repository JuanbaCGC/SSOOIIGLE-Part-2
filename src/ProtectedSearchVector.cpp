/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: ProtectedSearchVector.cpp
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 31/04/2021
*
* Purpose			: Class that protect the vector of searchs
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

#include "ProtectedSearchVector.h"

/* Constructor of the class */
ProtectedSearchVector::ProtectedSearchVector(){}

/* Method that return the request vector */
std::vector <SearchRequest> ProtectedSearchVector::get_vector(){
	return request_vector;
}

/* Method that remove the first SearchRequest of the Request_vector */
void ProtectedSearchVector::do_pop(){
	std::lock_guard<std::mutex> lk(m);
	for(int i = 0; i < request_vector.size(); i++){
		if(i == 0){
			while(i < request_vector.size()-1){
				request_vector[i] = request_vector[i+1];
				i++;
			}
		global_wait_search.notify_all();
		break;
		}	
	}
	request_vector.erase(request_vector.end());
}

/* Method that return the first SearchRequest of the Request_vector */
SearchRequest ProtectedSearchVector::get_front(){
	std::lock_guard<std::mutex> lk(m);
	SearchRequest r = request_vector[0];
	return r;
}

/* Method that insert a SearchRequest in the request_vector with a push_back */
void ProtectedSearchVector::insert(SearchRequest r){
	std::lock_guard<std::mutex> lk(m);
	request_vector.push_back(r);
}

/* Method that return the first SearchRequest of the vector with the user id that has in the parameter */
SearchRequest ProtectedSearchVector::getRequest(int userId){
	SearchRequest q(-1,"",0);
	std::lock_guard<std::mutex> lk(m);
	for(int i = 0; i < request_vector.size(); i++){
		if(request_vector[i].get_user_id() == userId){
			q = request_vector[i];
			auto elem_to_remove = request_vector.begin() + i;
			if(elem_to_remove != request_vector.end()){
				request_vector.erase(elem_to_remove);
				global_wait_search.notify_all();
			}
			break;
		}
	}
	return q;
}

/* Method that return true if there is a SearchRequest with the user id that has in the parameter */
bool ProtectedSearchVector::findRequest(int userId){
	bool find = false;
	for(int i = 0; i < request_vector.size(); i++){
		if(request_vector[i].get_user_id() == userId){
			find = true;
			break;
		}
	}
	return find;
}

/* Method that return true if all the SearchRequests has the same priority */
bool ProtectedSearchVector::all_same_type(){
	bool same_type = false;
	int counter = 0;
	std::lock_guard<std::mutex> lk(m);
	for(int i = 0; i < request_vector.size(); i++){
		counter += request_vector[i].get_priority();
	}
	if(counter == 0 || counter == request_vector.size())
		same_type = true;
		
	return same_type;
}

/* Method that return the position of the first SearchRequest with prirority = 0 */
int ProtectedSearchVector::get_free_request_position(){
	int position = 0;
	for(int i = 0; i < request_vector.size();i++){
		if(request_vector[i].get_priority() == 0)
			position = i;
			break;	
	}
	
	return position;
}

/* Method that return the position of the first SearchRequest with prirority = 0 */
int ProtectedSearchVector::get_prime_request_position(){
	int position = 0;
	for(int i = 0; i < request_vector.size();i++){
		if(request_vector[i].get_priority() == 1)
			position = i;
			break;	
	}
	
	return position;
}

/* Method that delete the SearchRequest of a certain positon in the request_vector */
void ProtectedSearchVector::delete_request_by_position(int position){
	SearchRequest q(-1,"",0);
	std::lock_guard<std::mutex> lk(m);
	for(int i = 0; i < request_vector.size(); i++){
		if(i == position){
			q = request_vector[i];
			auto elem_to_remove = request_vector.begin() + i;
			if(elem_to_remove != request_vector.end()){
				request_vector.erase(elem_to_remove);
				global_wait_search.notify_all();
			}
			break;
		}
	}
}

/* Method that return a SearchRequest in certain position */
SearchRequest ProtectedSearchVector::get_request_by_position(int position){
	SearchRequest sr = request_vector[position];
	return sr;
}

