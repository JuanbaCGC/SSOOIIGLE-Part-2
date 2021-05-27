/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: ProtectedSearchVector.h
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 31/04/2021
*
* Purpose			: This class has the vector where the SearchRequest are stored and a mutex. 
*				  The objective of this class is to protect the vector when it is manipulated just 
*				  calling the methods.
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

#ifndef PROTECTEDSEARCHVECTOR_H
#define PROTECTEDSEARCHVECTOR_H

class ProtectedSearchVector {
	private:
		/* Vector where the SearchRequest are going to be stored */
		std::vector <SearchRequest> request_vector;
		/* Mutex to protect the request_vector */
		std::mutex m;
	public:
		/* Constructor of the class */
		ProtectedSearchVector();
		
		/* Method that return the request vector */
		std::vector <SearchRequest> get_vector();
		
		/* Method that remove the first SearchRequest of the Request_vector */
		void do_pop();
		
		/* Method that return the first SearchRequest of the Request_vector */
		SearchRequest get_front();
		
		/* Method that insert a SearchRequest in the request_vector with a push_back */
		void insert(SearchRequest r);
		
		/* Method that return the first SearchRequest of the vector with the user id that has in the parameter */
		SearchRequest getRequest(int userId);
		
		/* Method that return true if there is a SearchRequest with the user id that has in the parameter */
		bool findRequest(int userId);
		
		/* Method that return true if all the SearchRequests has the same priority */
		bool all_same_type();
		
		/* Method that return the position of the first SearchRequest with prirority = 0 */
		int get_free_request_position();
		
		/* Method that return the position of the first SearchRequest with prirority = 0 */
		int get_prime_request_position();
		
		/* Method that delete the SearchRequest of a certain positon in the request_vector */
		void delete_request_by_position(int position);
		
		/* Method that return a SearchRequest in certain position */
		SearchRequest get_request_by_position(int position);
};


#endif


