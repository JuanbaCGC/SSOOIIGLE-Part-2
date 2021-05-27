/* Defines and global variables */
#define USER_AMOUNT 10							/* Max number of users */
#define SEARCH_SYSTEM_AMOUNT 4					/* Max number of search at the same time */
#define MAX_LIMIT 50							/* Max limit for the free and prime users */
#define WORDS_FILE "words.txt"					/* Define with the name of the .txt where the words are stored */

/* Colour defines to show messagges with them */
#define CYN "\e[0;36m"							
#define NC "\e[0m"		
#define GRN "\e[0;32m"
#define RED "\e[0;31m"
#define PRP "\e[0;35m"
#define REDB "\e[41m"

std::condition_variable global_wait_pay;				/* Condition variable for the PaySystem class */
std::condition_variable global_wait_search;				/* Condition variable for the SearchSystem class */
std::condition_variable global_wait_user;				/* Condition variable for the GenerUser class */


/* Vector where the diferents words that are going to be searched by the users are going to be stored */
std::vector<std::string> global_dictionary = {};
/* Diferents texts where the words are going to be searched */
std::vector<std::string> global_books = {"17-LEYES-DEL-TRABJO-EN-EQUIPO.txt", "21-LEYES-DEL-LIDERAZGO.txt", "VIVE-TU-SUEÑO.txt", "El-oro-y-la-ceniza.txt"};

std::atomic<int> global_request_id (0);				/* Variable that is used to identificate the SearchRequests */
int global_books_number = 0;						/* Variable where the number of books is going to be searched */

std::mutex global_sem_search_system;					/* Mutex for the SearchSystem */
std::mutex global_sem_pay_system;					/* Mutex for the PaySystem */
std::mutex global_sem_payment_request;				/* Mutex to protect de Payment Request's queue */					 
std::mutex global_sem_wait_user;					/* Mutex for the GeneralUser class */
std::mutex global_sem_pop_search_request;				/* Mutex to protect a the vector of SearchRequest when a pop is going te be done */
