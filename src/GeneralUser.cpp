/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: GeneralUser.cpp
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 27/04/2021
*
* Purpose			: Class where the methods of the GeneralUser.h are implemented.
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/
#include <dirent.h>
#include "GeneralUser.h"

/* Constructor of the Premium User */
GeneralUser::GeneralUser(int user_id, std::string type, std::string word){				
	this->user_id = user_id;
	this->type = type;
	this->word = word;
	this->limit = -1;
}

/* Constructor of the Free User */
GeneralUser::GeneralUser(int user_id, std::string type, std::string word, int limit){		
	this->user_id = user_id;
	this->type = type;
	this->word = word;
	this->limit = limit;
}

/* Constructor of the Prime User */
GeneralUser::GeneralUser(int user_id, std::string type, int first_balance, std::string word){	
	this->user_id = user_id;
	this->type = type;
	this->word = word;
	this->first_balance = first_balance;
	this->limit = first_balance;
}

/* Method that return the id of the GeneralUsers */
int GeneralUser::get_user_id(){
	return user_id;
}

/* Metheod that return the type of the GeneralUsers */
std::string GeneralUser::get_type(){
	return type;
}

/* Method that return the word of the GeneralUsers */
std::string GeneralUser::get_word(){
	return word;
}

/* Method that return the first balance of the GeneralUsers */
int GeneralUser::get_first_balance(){
	return first_balance;
}

/* Method that return the limit of the GeneralUsers */
int GeneralUser::get_limit(){
	return limit;
}

/* Method that set the limit of the GeneralUsers */
void GeneralUser::set_limit(int limit){
	this->limit = limit;
}

/* Method that return a SearchRequest */
SearchRequest GeneralUser::do_search_request(){
	SearchRequest search_request (-1,"",-1);
	if(type == "FREE"){
		SearchRequest sr(user_id, get_word(),0);
		search_request = sr;
	}else{
		SearchRequest sr(user_id, get_word(),1);
		search_request = sr;
	}
	
	search_request.set_request_id();
	return search_request;
}

/* Method that will create the diferents .txt files and will put the result inside them */
void GeneralUser::createFiles(ReplySearch rs){
	std::string title;
	char user_direction[20];
	std::sprintf(user_direction, "cd USERS/%d", user_id);
	system(user_direction);
	for(int i = 0; i < global_books_number; i++){
		std::string text = "./USERS/" + to_string(user_id) + "/Results_" + global_books[i];
		std::ofstream file(text.c_str());
		title = "----------------------- RESULTS IN THE TEXT SEARCHING THE WORD " + get_word() + " IN THE TEXT -----------------------\n";
		file << title;
		while(rs.pq_vector[i].empty() == false){
			CSearch c = rs.pq_vector[i].top();
			rs.pq_vector[i].pop();
			file << c.getString() + "\n";
		}
		file.close();
	}
}

/* Method that return true or false if the directory passed by parameters exists or not */
bool GeneralUser::directoryExists(std::string dir){
	DIR * directory;
	if(directory = opendir(dir.c_str())){
		closedir(directory);
		return true;
	}
	
	return false;
}

/* Method that create the time.txt in the Users directory */
void GeneralUser::createTimeFile(double time){
	std::string title;
	char user_direction[20];
	std::sprintf(user_direction, "mkdir USERS/%d", user_id);
	system(user_direction);
	std::string text = "./USERS/" + to_string(user_id) + "/User_time.txt";
	/* Create the User_time.txt file */
	std::ofstream file(text.c_str());
	title = "The user with id " + to_string(user_id) + " has taken since it was created until it he got the results a total time of " + to_string(time) + " seconds \n";
	file << title;
	file.close();
}

/* Overload the operator */
int GeneralUser::operator()(int number){
	std::cout << PRP << "\n---------------------------------- USER WITH ID " << user_id << " ------------------------------------" << std::endl;
	toString();
	std::cout << PRP << " has been created." << std::endl;
	std::cout << PRP << "--------------------------------------------------------------------------------------" << std::endl;
	unsigned t1, t2;
	const int id = user_id;
	/* Get the first runtime */
	t1 = clock();
	SearchRequest search_request = do_search_request();
	global_search_request_vector.insert(search_request);
	/* When the SearchRequest is in the vector, notify the wait_search condition variable to unlock a SearchSystem */
	global_wait_search.notify_one();
			
	std::unique_lock<std::mutex> lk_user(global_sem_wait_user);
	/* It will be blocked if the reply_search_vector is empty and if this vector doesn't have a SearchReply with the id of the user */
	global_wait_user.wait(lk_user, [id] {return (global_reply_search_vector.get_vector().empty() == false && global_reply_search_vector.findReply(id) == true);});
	/* Get the second runtime */
	t2 = clock();
	/* Get the difference of the times */
    	double time = (double(t2-t1)/CLOCKS_PER_SEC);
    	/* Create the txt with the time for the user */
    	createTimeFile(time);
	ReplySearch reply_search = global_reply_search_vector.getReply(id);
	/* Create the txt of the coincidences for the user */
	createFiles(reply_search);
			
	std::cout << PRP << "\n---------------------------------- USER WITH ID " << user_id << " ------------------------------------" << std::endl;
	std::cout << PRP <<"The user with ID " << user_id << " has his results in his folder." << std::endl;
	std::cout << PRP << "--------------------------------------------------------------------------------------" << std::endl;
			
	return EXIT_SUCCESS;
}

/* Method that will show the information of the instance of the GeneralUser */
void GeneralUser::toString(){
	if(type == "PREMIUM")
		std::cout << "User with id " << get_user_id() << ", type "<< get_type() << " and word " << get_word();
	else if (type == "PRIME")
		std::cout << "User with id " << get_user_id() << ", type "<< get_type() << ",word " << get_word() << " and first balance " << get_limit();
	else
		std::cout << "User with id " << get_user_id() << ", type "<< get_type() << ",word " << get_word() << " and limit " << get_limit();
}

