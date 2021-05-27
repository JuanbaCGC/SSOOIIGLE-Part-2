/************************************************************************
* Project			: Practica 3 de Sistemas Operativos II
*
* Program name			: GeneralUser.h
*
* Author			: Juan Bautista Castaño García-Cervigón and Alberto Mayorga Naranjo
*
* Date created:		: 27/04/2021
*
* Purpose			: this is the class where the information of the Users are going to be stored. 
*				  It has a operator that all the users are going to execute.
*				  They make a SearchRequest, then they get blocked until they get the 
*				  coincidences from the SearchSystem with a SearchReply. After this, 
*				  they do some .txt files with the results of their search.
*				  They do a .txt file too where the time they have been active is shown. 
*
* Revision History :
*
* Date		Author		Ref		Revision
*
*
/************************************************************************/

#ifndef GENERALUSER_H
#define GENERALUSER_H

class GeneralUser{
	private:
		int user_id;			/* Id of the diferents user. Each id is unique */
		std::string type;		/* Type of the users. It can be: FREE, PRIME or PREMIUM */
		std::string word;		/* Word that is going to be searched by the user */
		int first_balance;		/* First balance of the user */
		int limit;			/* Limit of the user (it will be -1 if the user has the type PREMIUM) */
	public:
		
		/* Constructor of the Premium User */
		GeneralUser(int user_id, std::string type, std::string word);
		
		/* Constructor of the Free User */
		GeneralUser(int user_id, std::string type, std::string word, int limit);
				
		/* Constructor of the Prime User */
		GeneralUser(int user_id, std::string type, int first_balance, std::string word);
		
		/* Method that return the id of the GeneralUsers */
		int get_user_id();
		
		/* Metheod that return the type of the GeneralUsers */
		std::string get_type();
		
		/* Method that return the word of the GeneralUsers */
		std::string get_word();
		
		/* Method that return the first balance of the GeneralUsers */
		int get_first_balance();
		
		/* Method that return the limit of the GeneralUsers */
		int get_limit();
		
		/* Method that set the limit of the GeneralUsers */
		void set_limit(int limit);
		
		/* Method that return a SearchRequest */
		SearchRequest do_search_request();
		
		/* Method that will create the diferents .txt files and will put the result inside them */
		void createFiles(ReplySearch rs);
		
		/* Method that return true or false if the directory passed by parameters exists or not */
		bool directoryExists(std::string dir);
		
		void createTimeFile(double time);
		
		/* Overload the operator */
		int operator()(int number);
		
		/* Method that will show the information of the instance of the GeneralUser */
		void toString();
		
};

#endif

