/* Header file define 2 data structs which are DATE_T and HOTEL_T.
 * HOTEL_T keep the nessesary information that hotel datebase required
 * (according to project2 instructor) 
 * DATE_T keep the day month year of present date and date from user
 * This header also declares MAX MID and MIN variables for using in 
 * char input[] in order to call fgets sscanf funcitino whcih better 
 * than ordinary scanf especially, play with string.
 * Created by Panithi Suwanno 63070503426 (Big)
 * For Project2 CPE100 16 NOV 2020
 */
#define MAX 256 // 256 characters, that enough, not an essay!
#define MID 64
#define MIN 10

typedef struct
{
	int dayToday;
	int monthToday;
	int yearToday;
	int dayBuilt;
	char month[MIN];
	int monthBuilt;
	int yearBuilt;
} DATE_T;

typedef struct
{
	char name[MAX];
	char date[MID];
	char service[MID];
	char phone[MID];
	char province[MID];
	char star[MIN];
} HOTEL_T;

// validate functions
int validateHotelName(char *input);
/* User input if has nothing it will print error message.
 * Then, let user input hotel name again. 
 */
int validateDateBuilt(char *input);
/* Date input which year rage 1900 until the gpresent date 
 * inside this functino also recall from dateFunction.h (provided by Dr.Sally)
 * for get current date info, validate future date and check leap year 
 */
int validateServiceCode(char *input);
/* Hotel service code which must have dollar sign or special characters
 * for indentify kind of service the hotel avaliable (no duplicated word)
 */
int validatePhoneNumber(char *input);
/* Phone number with no dashes. My intention is make all information stored
 * in the same format and easy to understand it. Phone number should star with 
 * 01 05 06 08 09 only. Furthermore, it must be 10 digits. 
 */ 
int validateProvinceCode(char *input);
/* Thai province code started with 'TH-' and has a number at the end.
 * The numbers must be between 10 and 96 inclusive. If the number is not used, 
 * it must be the 'S' of the Pattaya Special Administrative Region only.
 * If the following conditions are not met, an error message will appear.
 */
int validateStarRating(char *input);
/* Star hotel rating. The hotel rating must be 1 to 5 stars only. 
 * No letters or decimal places. To make it more convenient for the 
 * user to remember when displaying the data.
 */