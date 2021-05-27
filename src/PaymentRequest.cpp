/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: PaymentRequest.cpp
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 31/04/2021
*
* Purpose			: this class has the information of the PaymentRequest that the prime 
*				  users make when they don't have more limit. 
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

class  PaymentRequest{
	public:
		int user_id;						/* Varible that will store the id of the user that do the PaymentRequest */
		std::promise<int> user_promise;			/* Promise and future to change the limit of the user */
		std::future<int> user_future;
						
		PaymentRequest(int id): user_id(id){			/* Constructor method */	
			user_future = user_promise.get_future();
		};
};
