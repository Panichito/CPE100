/* Hotel manipulation functions header file
 * 
 * Created by Panithi Suwanno 63070503426 (Big) 
 * 28 NOV 2020
 * 09 DEC 2020 (Updated - search and modify)
 * 15 DEC 2020 (Updated - test run and comment)
 */
#include "validateFunctions.h" // declares struct

/************************************** DisplayAdding.c **************************************/
int welcomeRA(); 
/* Welcome to Adding, this allowed you to specify 
 * how many data that you want to add into our database. 
 */
void recordData(HOTEL_T *hotel, int amount);
/* Program record hotel data which consists of name, date, service
 * phone, province, rating information if user input have been examine
 * validate functions, it will store into struct of hotel. Whenever, user
 * finish input all data, it will be write at once into database file. 
 */
int displayHotel(HOTEL_T oneHotel, int which);
/* Gets the data from the showData function and order of its for printing display output. 
 * Display step by five hotels for user friendly.
 */
void showData();
/* This function has nothing much. It just open database file and read its
 * data next directly sent those data inro display function for printing. 
 */
void HotelAdding();
/* Funciton for add more hotel. This will ask user about each information for 
 * further add into validation process. After that, it will send the total struct 
 * into recordData for write into datebase file. 
 */

/************************************** SearchModify.c **************************************/
void welcomeSM();
/* Welcome to Search and Modify, let you to chose which
 * criteria that you what to search by.
 */
int askUser();
/* Ask user to show all data that search found or not.
 * If show data user are able to access modirying function further.
 */
int YesOrNo(char *command);
/* Yes No question if yes  function return 1 true
 * or return 0 false if no.
 */
int checkNameSearch(char *input);
/* Check hotel name that user type for searching process.
 * The error message will appear when user not input anything.
 */
int checkStarSearch(char *input);
/* Star that user provided for searching should match in with rating
 * in dataabase file for compare the digit string efficiency.
 */
void searchingHotel(char *input, int option);
/* Searching function The program will see what type of information entered. 
 * Assuming that it is the hotel rating information, it must be only 1 character 
 * and 1 - 5 numbers, but vice versa, if it meets the conditions mentioned above,
 * but the user option is 1, it will be treated as the hotel name.
 */
void displaySearch(HOTEL_T oneHotel, int position);
/* Display hotel that search found from searchingHotel which searching star by 
 * string compare and searching string start by for loop to length of input 
 * by regardless to uppercase or lowercase.
 */
void modifyingHotel(char *input, int found);
/* If the user searches for information, the program will suggest that the 
 * information will be modify or not.
 */
int editPosition(int found);
/* If the user chooses that they want to modify the information. The program 
 * will ask how much data you want to modify (in case system find more than 
 * one searchable data).
 */
int editOption();
/* When the struct of the data to be edited can be specified. The program will choose 
 * which part of the information you want to edit, such as name, service date, phone number, 
 * province, rating or want to edit all of the above If you want to edit not all, you can select 
 * only one item at a time. When finished the first selected one, the program will let choose to 
 * edit other things in the future.
 */
void editInput(int option, HOTEL_T hotel, int countLine);
/* Of course, when changing the information to a new one Must have to check if 
 * the newly received data matches the format specified by the system or not, 
 * if the conditions cannot be met, the program will display an error message and ask 
 * the user to enter information again.
 */
void overwriteModify(HOTEL_T hotel, int writenum, int countLine);
/* The data to be modified and validated will be overwritten by the old data in the 
 * database based on the first struct location the file was read (can be seen from 
 * the search process).
 */