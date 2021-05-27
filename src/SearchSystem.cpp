/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: SearchSystem.cpp
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 29/04/2021
*
* Purpose			: Class where the methods of the SearchSystem.h are implemented.
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

#include "SearchSystem.h"

/* Method that do the search acording to the SearchRequest, finally it returns the limit of the user */
int SearchSystem::do_search(SearchRequest r, GeneralUser user, std::string text, int limit, priority_queue<CSearch, vector<CSearch>,compareFunction> &pq_pointer){
	priority_queue<CSearch, vector<CSearch>,compareFunction> new_pq;
	int limit_aux = limit;
	std::vector<std::string> arrayLine;
	arrayLine = openFile(text);
	if(arrayLine.size() != 0)							/* If the arrayLine size is bigger than 0, then delete the las line of the file */
		arrayLine.erase(arrayLine.end());					/* Delete the last line of the file */

	for(int i = 0; i < arrayLine.size(); i++){					/* Do the search in every .txt */
			new_pq = findWordInLine(split(arrayLine[i]), r.get_word(), i, 1, 0, arrayLine.size(), new_pq);
	}
	
	while(limit_aux != 0 && new_pq.size() > 0){
		limit_aux--;
		CSearch search = new_pq.top();
		new_pq.pop();								/* Delete the top of the new priority queue */
		pq_pointer.push(search);
		if(limit_aux == 0 && user.get_type() == "FREE"){			/* If a FREE user has limit = 0... */
			std::cout << GRN << "\n------------------------------------ SEARCH SYSTEM -----------------------------------" << std::endl;
			std::cout << GRN << "FREE user with id " << user.get_user_id() << " without searchs." << std::endl;
			std::cout << GRN << "--------------------------------------------------------------------------------------" << std::endl;
		}else if(limit_aux == 0 && user.get_type()  == "PRIME"){		/* If a PRIME user has limit = 0... */
			std::cout << GRN << "\n------------------------------------ SEARCH SYSTEM -----------------------------------" << std::endl;
			std::cout << GRN << "PRIME user with id " << user.get_user_id() << " without balance." << std::endl;
			std::cout << GRN << "--------------------------------------------------------------------------------------" << std::endl;
			PaymentRequest r(user.get_user_id());				/* Create a PaymentRequest */
			std::lock_guard<std::mutex> lk(global_sem_payment_request);
			global_payment_queue.push(std::move(r));			/* Push it to the payment_queue */
			global_wait_pay.notify_one();					/* Notify one PaySystem */
			limit_aux = global_payment_queue.front().user_future.get();	/* Get the new limit for the user */
			global_payment_queue.pop();
			global_wait_pay.notify_all();					
		}
	}
	return limit_aux;
}

/* Method that return a GeneralUser passing his id by parameter */
GeneralUser SearchSystem::get_user(int id){
	bool find = false;
	GeneralUser u(0,"","");
	for(int i = 0; i < global_vUsers.size() && !find; i++){
		if(global_vUsers[i].get_user_id() == id){
			GeneralUser u = global_vUsers[i];
			find = true;
			return u;
		}
	}
	return u;
}

/* Method that returns the SearchRequest acording to the relation 80-20 (80% premium requests - 20% free requests)  */ 
SearchRequest SearchSystem::get_request(){
	int position = 0;
	srand(time(NULL));
	SearchRequest search_request(-1,"",-1);
	if(global_search_request_vector.all_same_type() == true){
		SearchRequest sr = global_search_request_vector.get_front();
		search_request = sr;
		global_search_request_vector.do_pop();
	}else{
		int random_number = 1 + rand()%(11-1);
		if(random_number <= 8){
			position = global_search_request_vector.get_prime_request_position();
			SearchRequest sr = global_search_request_vector.get_request_by_position(position);
			search_request = sr;
		}else{
			position = global_search_request_vector.get_free_request_position();
			SearchRequest sr = global_search_request_vector.get_request_by_position(position);
			search_request = sr;
		}
		global_search_request_vector.delete_request_by_position(position);		
	}

	return search_request;
}

/* Method that do the search in the differents books */
void SearchSystem::do_searchs_in_books(SearchRequest sr){
	GeneralUser user = get_user(sr.get_user_id());
	int limit = user.get_limit();
				
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));	/* Delay of 1 second to pause the program */
	for(int i = 0; i < global_books.size(); i++){
		limit = do_search(sr, user, global_books[i], limit,std::ref(pq_vector[i]));
	}
}

/* Method that fill the pq_vector with priority queues */
void SearchSystem::fill_pq_vector(){
	priority_queue<CSearch, vector<CSearch>,compareFunction> pq;
	for(int i = 0; i < global_books_number; i++){
			pq_vector.push_back(pq);
	}
}

/* Overload the operator */
void SearchSystem::operator()(){
	while(1){
		/* Fill the vector of priority queues */
		fill_pq_vector();
			
		std::unique_lock<std::mutex> lk_queue(global_sem_search_system);
		/* The SearchSystem will be blocked if the queue of the search request is empty */
		global_wait_search.wait(lk_queue, [] {return (global_search_request_vector.get_vector().size() != 0);});	
		lk_queue.unlock();
		/* Get the front SearchRequest of the vector */
		global_sem_pop_search_request.lock();
		SearchRequest search_request = get_request();
		global_sem_pop_search_request.unlock();
		std::cout << GRN << "\n------------------------------------ SEARCH SYSTEM -----------------------------------" << std::endl;
		std::cout << GRN "Searching the word " << search_request.get_word() << " in all the texts for the user with id " << search_request.get_user_id() << std::endl;
		std::cout << GRN << "--------------------------------------------------------------------------------------" << std::endl;
		do_searchs_in_books(search_request);
				
		std::cout << GRN << "\n------------------------------------ SEARCH SYSTEM -----------------------------------" << std::endl;
		std::cout << GRN <<"The search request of the user with id " << search_request.get_user_id() << " has been completed, the results will be send." << std::endl;
		std::cout << GRN << "--------------------------------------------------------------------------------------" << std::endl;
					
		/* When the SearchRequest has been completed, a ReplySearch is created and inserted in the reply_search_vector */
		ReplySearch reply_search(search_request.get_user_id(), pq_vector);
		global_reply_search_vector.insert(reply_search);
		/* Notify all wait_user condition variable to unlock the user */
		global_wait_user.notify_all();
		/* Notify one wait_search condition variable to unlock other SearchSystem */
		global_wait_search.notify_one();
	}	
}
