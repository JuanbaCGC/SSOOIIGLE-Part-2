/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: PaySystem.cpp
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 23/04/2021
*
* Purpose			: Class where the methods of the PaySystem.h are implemented.
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/
#include "PaySystem.h"
		
/* Method that return the user with a certain id */
GeneralUser PaySystem::get_user_by_id(int id){
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

/* Overload the operator */
void PaySystem::operator()(){
	while(1){
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::unique_lock<std::mutex> lk_queue(global_sem_pay_system);
		global_wait_pay.wait(lk_queue, [] {return (global_payment_queue.empty() == false);});
		/* Get the User that has done the PaymentRequest by their id */
		GeneralUser u = get_user_by_id(global_payment_queue.front().user_id);
		try{
		/* Set the new value for the limit */
			global_payment_queue.front().user_promise.set_value(u.get_first_balance());
		}catch(std::exception e){
			std::cerr << "Error waiting for the new balance... " << std::endl;
		}
				
		std::cout << CYN << "\n------------------------------------- PAY SYSTEM -------------------------------------" << std::endl;
		std::cout << CYN <<"The PaymentRequest of user with ID " << u.get_user_id() << " has been completed." << std::endl;
		std::cout << CYN << "--------------------------------------------------------------------------------------" << std::endl;
	}
}
