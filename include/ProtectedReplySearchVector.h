/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: ProtectedReplySearchVector.h
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 10/05/2021
*
* Purpose			: Class that create a vector of ReplySearchs. 
*				  It has the methods to manipulate this vector and these methods are going 
*				  to be protected by a lock_guard.
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

#ifndef PROTECTEDREPLYSEARCHVECTOR_H
#define PROTECTEDREPLYSEARCHVECTOR_H

class ProtectedReplySearchVector {
	private:
		std::vector <ReplySearch> reply_search_vector;	/* Vector where the ReplySearchs are going to be stored */
		std::mutex m;						/* Mutex to controll the vector access */
		
	public:
		/* Constructor of the class */
		ProtectedReplySearchVector();
		
		/* Method that return the ReplySearch vector */
		std::vector <ReplySearch> get_vector();
		
		/* Method that insert a reply search in the protected vector */
		void insert(ReplySearch);
		
		/* Method that indicates if the reply request exists*/
		bool findReply(int user_id);
		
		/* Method that return a reply request with a certain user id */
		ReplySearch getReply(int user_id);
};

#endif


