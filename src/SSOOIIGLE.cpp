/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: SSOOIIGLE.cpp
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 25/04/2021
*
* Purpose			: Main file of the program. In this file the differents users are going to be created. 
*				  It will create too:
*					- As many GeneralUsers threads as the defined variable USER_AMOUNT has.
*					- As many SearchSystems threads as the defined variable SEARCH_AMOUNT has.
*					- A PaySystem thread.
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

/* Libraries includes */
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <functional>
#include <algorithm>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <future>
#include <signal.h>

#include "variables.h"
#include "SearchRequest.cpp"
#include "ProtectedSearchVector.cpp"
ProtectedSearchVector global_search_request_vector;		/* Protected vector for the SearchRequest */
#include "PaymentRequest.cpp"
std::queue<PaymentRequest> global_payment_queue;		/* Queue where the PaymentRequest are going to be stored */
#include "searchLibrary.cpp"
#include "ReplySearch.cpp"
#include "ProtectedReplySearchVector.cpp"
ProtectedReplySearchVector global_reply_search_vector;	/* Protected vector for the ReplySearchs */
#include "GeneralUser.cpp"
std::vector<GeneralUser> global_vUsers; 			/* Vector of Users where the users are going to be manipulated */
#include "SearchSystem.cpp"
#include "PaySystem.cpp"

/* Method that create the differents type of users (the same number of the variable USER_AMOUNT) */
void createUsers();

/* Method that open the WORDS_FILE .txt, then it take every word of this text and it insert them into the dictionary vector */
bool get_words();

/* Method that finish the program if the WORDS_FILE is empty or if the books array is empty too */
void errorControl();

/* Method that create the threads of the diferents GeneralUsers */
void createUserThreads();

/* Method that create the threads of the diferents SearchSystems */
void createSearchSystemThreads();

/* Method that create the USERS directory if this doesn't exist. If this directory exist, it's deleted and create a new one */
void createUsersDirectory();

/* Method that install the signal handler */
void installSignalHandler();

/* Method that capture the Ctrl+c signal */
void signalHandler(int sig);

/* Method that return true if the WORDS_FILE exists */
bool WordsFileExists();


int main(){
	PaySystem p;
	std::cout << "Hi, welcome to the SSOOIIGLE part 2" << std::endl;
	installSignalHandler();
	errorControl();
	/* Create the Users */
	std::thread create_users(createUsers);
	create_users.detach();
	/* Create the Users directory */
	createUsersDirectory();
	global_books_number = global_books.size();
	/* Create the user threads */
	std::thread create_user_threads(createUserThreads);
	create_user_threads.detach();
	/* Create the SearchSystem threads */
	createSearchSystemThreads();
	/* Create the thread of the PaySystem */
	std::thread thread_pay_system(p);	
	thread_pay_system.join();
	
	return 0;
}


/* Method that create the differents type of users (the same number of the variable USER_AMOUNT) */
void createUsers(){
	std::string type;
	int random_type, random_word, random_limit;
	for(int i = 0; i < USER_AMOUNT;i++){
		random_type = 1 + rand()%(4-1);
		random_word = 1 + rand()%(global_dictionary.size()-1);
		random_limit = 1 + rand()%(MAX_LIMIT - 1);
		switch(random_type){
			case 1:{
				type = "FREE";
				GeneralUser u (i,type,global_dictionary[random_word],random_limit);
				global_vUsers.push_back(u);		
				break;
			}
			case 2:{
				type = "PRIME";
				GeneralUser u (i,type,random_limit,global_dictionary[random_word]);
				global_vUsers.push_back(u);
				break;
			}
			case 3:{
				type = "PREMIUM";
				GeneralUser u(i,type,global_dictionary[random_word]);
				global_vUsers.push_back(u);
				break;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

/* Method that open the WORDS_FILE .txt, then it take every word of this text and it insert them into the dictionary vector */
bool get_words(){
	std::vector<std::string> words_vector = openFile(WORDS_FILE);
	if(words_vector[0].size() == 0){
		return true;
	}
	std::vector<std::string> words_split;
	for(int i = 0; i < words_vector.size(); i++){
		words_split = split(words_vector[i]);
	
		for(int j = 0; j < words_split.size(); j++){
			global_dictionary.push_back(words_split[j]);
		}
	}
	return false;
}


/* Method that create the threads of the diferents GeneralUsers */
void createUserThreads(){
	std::thread threads_users[USER_AMOUNT];

	for(int i = 0; i < global_vUsers.size();i++){
		threads_users[i] = std::thread(global_vUsers[i],i);
		threads_users[i].detach();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

/* Method that create the threads of the diferents SearchSystems */
void createSearchSystemThreads(){
	SearchSystem s;
	std::thread threads_search_system[SEARCH_SYSTEM_AMOUNT];
	
	for(int i = 0; i < SEARCH_SYSTEM_AMOUNT;i++){
		threads_search_system[i] = std::thread(s);
		threads_search_system[i].detach();
	}
}

/* Method that create the USERS directory if this doesn't exist. If this directory exist, it's deleted and create a new one */
void createUsersDirectory(){
	if(global_vUsers[0].directoryExists("USERS") == false){
		system("mkdir USERS");
	}else{
		system("rm -r USERS");
		system("mkdir USERS");
	}
}

/* Method that finish the program if the WORDS_FILE is empty or if the books array is empty too */
void errorControl(){
	bool empty;

	if(!WordsFileExists()){
		std::cerr << RED << "The " << WORDS_FILE << " doesn't exists, please, create it " << std::endl;
		exit(-1);
	}
	
	empty = get_words();
	
	if(empty == true && global_books.size() == 0){
		std::cerr << RED << "The " << WORDS_FILE << " and the books array are empty, please, put some words on the " << WORDS_FILE << " and some books on the books array" << std::endl;
		std::cerr << RED << "Finishing the program..." << std::endl;
		exit(-1);
	}
	if(empty == true){
		std::cerr << RED << "The " << WORDS_FILE << " is empty, please, put some words on it " << std::endl;
		std::cerr << RED << "Finishing the program..." << std::endl;
		exit(-1);
	}else if(global_books.size() == 0){
		std::cerr << RED << "The books array is empty, please, put some books on it " << std::endl;
		std::cerr << RED << "Finishing the program..." << std::endl;
		exit(-1);
	}
}

/* Method that install the signal handler */
void installSignalHandler(){
	if(signal(SIGINT,signalHandler) == SIG_ERR){
		std::cerr << RED << "\nError installing the signal handler" << std::endl;
	}
}

/* Method that capture the Ctrl+c signal */
void signalHandler(int sig){
	std::cout << RED << "\nCtrl+c signal received" << std::endl;
	exit(-1);
}

/* Method that return true if the WORDS_FILE exists */
bool WordsFileExists(){
	FILE * f;
	if( (f = fopen(WORDS_FILE,"r")) == NULL)
		return false;
	else
		return true;
}

