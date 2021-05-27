*************************************************************************************************************************************************************************************************
*										README.txt													*
*************************************************************************************************************************************************************************************************

The objective of this practice is to enlarge the second practice. It's a client-server simulation where the server has to search differents words in differents texts and send the matches to the users.
The program will create differents users with random words and they will make SearchRequests to the "server". The server is going to be a SearchSystem and it will be conected with a PaySystem, where 
on some specific occasions the program will have to access. Finally, the users create a folder where they put their coincidences in .txt files.

This practice has 2 folders, the SRC folder (with the .cpp files) and the INCLUDE (with the .h files). If you want to see what a class contains or what its methods do, just look at the .h file:
The SRC folder has differents files and each file has it own function:

    - SSOOIIGLE: main file of the practice. In this file, the differents users are created. Then it throw differents threads:
		- As many User threads as Users have been created (the same amount as the define variable USER_AMOUNT has).
		- As many SearchSystem threads as the define variable SEARCH_SYSTEM_AMOUNT has.
		- Just a PaySystem thread.

	- GeneralUser: this is the class where the information of the Users are going to be stored. It has a operator that all the users are going to execute.
	They make a SearchRequest, then they get blocked until they get the coincidences from the SearchSystem with a SearchReply. After this, they do some .txt files with the results of their search.
	They do a .txt file too where the time they have been active is shown. 
	There are different types of Users:
		* Free users: they have a limit of coincidences in all their searchs. When they get as many coincidences as the limit they have, they can't get more coincidences.
		* Prime users: as the free users, they have a limit. The difference between them is that the Prime users, when the limit is equal to 0, they get blocked until 
			       they go to a PaySystem to increment their limit, and then they can get more coincidences.
		* Premium users: this type of users don't have any limit. They can get all the coincidences in the text with no problem.

	- SearchRequest: this class has the information of the SearchRequest that the users make. It store: the user id, the word of the user that is going to be searched and a priority. 
	This priority will have 2 possible values:
		- 0 if it's a free user.
		- 1 if it's a prime or a premium user. 
	The instances of this class is going to be stored in a vector of SearchRequests.

	-ProtectedSearchVector: this class has the vector where the SearchRequest are stored and a mutex. The objective of this class is to protect the vector when it is manipulated just 
	calling the methods.

	- SearchSystem: this class is created in order to get the SearchRequest of the Users, take them (with a relation of 80% SearchRequests of Premium users or Prime users and 20% SearchRequest 
	of the Free users) and do the differents searchs in the differents books. The SearchSystems will be blocked if the queue of the SearchRequest is empty. 

	- PaymentRequest: this class has the information of the PaymentRequest that the prime users make when they don't have more limit. 
	The instances of this class are going to be stored in a queue of PaymentRequests.

	- PaySystem: the objective of this class is to set a new limit to the prime user that have run out of limit and set it to the first limit they had at the begining of the searchs.
	The thread of the PaySystem will be blocked if the queue of the PaymentRequest is empty.

	- ReplySearch: this class has been created to send the results of the coincidences from the SearchSystem to the Users (when this happend, the User get unlock and it create the differents txt).
	It has: the id of the user and a vector of priority queues where the results are stored.

	- ProtectedReplySearchVector: this class has the vector where the SearchReply are going to be stored and a mutex. As the ProtectedSearchVector, the objective of this class is to protect the vector 
	when it is manipulated just calling the methods.

It has some files of the second practice:

	-CSearch: Class where the information of the coincidence will be stored and showed.

	-CThread: Class where the information of the thread that find the coincidenceis going to be stored.
	  
	-searchLibrary: File where the functions of the searchLibrary are showed. The methods will help to handle with the .txt and find the coincidences.

	-compareFunction: file that is going to be used to order the instances of CSearch in the priority queue.

There is also a very important file in the INCLUDE folder (the other files declare the methods that are implemented in the same file with .cpp extension) :
	
	- variables.h: this file has the differents variables of the program, the defines, the global variables...

*WORDS FILE*
The words that take the differents Users are stored in a txt file, this txt file its called "words.txt". If anyone delete this file or create a new file to store the words, he has to change the 
#define WORDS_FILE with the number of the new file. In summary, the .txt that has the words must be in the #define WORDS_FILE, or the program will end when catching the error.

*BOOKS*
The books where the SearchSystem is going to search each word has to be in the folder withe the MAKEFILE, or the program will not find it. The name of the .txt/book has to be in the global variable global_books.
If the books do not meet these two conditions, the word will not be searched in them.

*IMPORTANT DEFINES TO EDIT THE PROGRAM*
There are two important defines in the variables.h file. These defines are:
	- USER_AMOUNT: these are the number of users that will be created.
	- SEARCH_SYSTEM_AMOUNT: these are the number of SearchSystems that will be created.
If you want to have more or fewer users, edit the USER_AMOUNT define. The same with the SEARCH_SYSTEM, in this case, with the SEARCH_SYSTEM_AMOUNT define.

*How to execute the program?*
We've created a Makefile in order to divide the program in diferents directories: src, exec, obj... And facilitate the compilation and execution of the program.

The instructions of the make file are:
	1. If you want to make all de directories, compile the program and execute it at the same time, you just have to put: make all. Then, the Makefile will do the rest.
	2. To create the directories, you only have to put: make dirs.
	3. To compile the program, you have to put on the command line: make compile.
	3. To execute the program, you have to enter on the command line: make execute.
	   To do this, the exec directory must have the executable (do "make compile" before).
	4. If you want to clean all the dirs, just insert: make clean.

*************************************************************************************************************************************************************************************************
*								Practice made by: Juan Bautista Castaño García-Cervigón	& Alberto Mayorga Naranjo						*
*************************************************************************************************************************************************************************************************
