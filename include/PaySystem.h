/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: PaySystem.h
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 23/04/2021
*
* Purpose			: Class that is going to implement the PaySystem of the program.
*				  Its objective is to set a new limit for the GeneralUser that has limit = 0.
*				  It will be blocked until the payment_queue get a PaymentRequest
*				  so the lambda function is fullfiled. Then it takes the PaymentRequest of
*				  the front of the queue and it set the new balance for the GeneralUser.
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

#ifndef PAYSYSTEM_H
#define PAYSYSTEM_H

class PaySystem{
	public:
		/* Method that return the user with a certain id */
		GeneralUser get_user_by_id(int id);
	
		/* Overload the operator */
		void operator()();
};

#endif
