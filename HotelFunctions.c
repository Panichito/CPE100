/* Hotel Data Manipulaation Program which consists of 4 main parts
 * Displaying, Adding, Searching and Modifying Function
 *
 * Created by Panithi Suwanno 63070503426 (Big)
 */

/* Program record, validate record and display total data
 * 16 NOV 2020
 * 09 NOV 2020 (Update - adding system and consistent data)
 * 15 DEC 2020 (Update - display hotel more friendly)
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "validateFunctions.h"
#define filename "hoteldatabase.dat"

int welcomeRA(); // Welcome to Record Adding

void recordData(HOTEL_T *hotel, int amount);

int displayHotel(HOTEL_T oneHotel, int which);

void showData();

void HotelAdding();

/* Program search and modify that search info
 * 09 DEC 2020
 * 15 DEC 2020 (Update - bug fixed and easy to use)
 */
void welcomeSM(); // Welcome to Search & Modify

int askUser();

int YesOrNo(char *command); 

int checkNameSearch(char *input);

int checkStarSearch(char *input);

void searchingHotel(char *input, int option);

void displaySearch(HOTEL_T oneHotel, int position);

void modifyingHotel(char *input, int found, int option);

int editPosition(int found);

int editOption();

void editInput(int option, HOTEL_T hotel, int countLine);

void overwriteModify(HOTEL_T hotel, int writenum, int countLine);

/**********************************************************************************/
/* Welcome Display Adding allowed you to specify 
 * how many data that you want to add into our database. 
 */
int welcomeRA()
{
	int amount = 0;
	char input[MAX];
	printf("  -Welcome to Record Adding system-\n");
	do
	{
		amount = 0;
		printf("  How much information do you want to add (-1 to exit)? ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",input);
		if(input [0] == '\n')
		{
			printf("    Invalid input >> Please type somthing!\n"); 
		}
		else 
		{
			amount = atoi(input);
			if(amount == -1)
				return amount;
			else if(amount < 1)
				printf("    Invalid >> Number of information!\n");
		}
	} while(amount < 1);
	return amount;
}
/* Program record hotel data which consists of name, date, service
 * phone, province, rating information if user input have been examine
 * validate functions, it will store into struct of hotel. Whenever, user
 * finish input all data, it will be write at once into database file. 
 */
void recordData(HOTEL_T *hotel, int amount)
{
	FILE *pOut = NULL;
	pOut = fopen(filename,"rb+");

	if(pOut == NULL)
	{
		printf("   No database '%s' found - Creating new!\n",filename);
    	pOut = fopen(filename,"wb");
        if (pOut == NULL)
		{
		  	printf("   Can't create a new database either!\n");
		  	exit(1);
		}
	}
	
	if(fwrite(&amount,sizeof(int),1,pOut) != 1) 
	{
		printf("   Unexpected error writing hotel amount!\n");
	}
	fseek(pOut,0,SEEK_END);
	if(fwrite(hotel,sizeof(HOTEL_T),amount,pOut) != amount)	
	{
		printf("   Unexpected writing hotel data!\n");
	}
	fclose(pOut);
}
/* Gets the data from the showData function to print. 
 */
int displayHotel(HOTEL_T oneHotel, int which)
{
	int select = 1;
	char command[MIN];
	if(which%5 == 0 && which != 0) // User friendly (easy to track step by five hotels)
	{
		do
		{
			printf(" Would you like to access more five hotels (Y/n)? ");
			fgets(command,sizeof(command),stdin);
			sscanf(command,"%s",command);
			select = YesOrNo(command);
		} while(select == -1);
		printf("\e[1;1H\e[2J"); // Clear screen for user friendly
		if(select == 0)
			return select;
	}
	if(select == 1)
	{
		printf("\n    Display HOTEL %d Information\n",which+1);
		printf("  NAME: %s\n",oneHotel.name);
		printf("  DATE: %s\n",oneHotel.date);
		printf("  SERVICE: %s\n",oneHotel.service);
		printf("  PHONE: %s\n",oneHotel.phone);
		printf("  PROVINCE: %s\n",oneHotel.province);
		printf("  STAR: %s\n",oneHotel.star);
	}
}
/* This function has nothing much. It just open database file and read its
 * data next directly sent those data inro display function for printing. 
 */
void showData()
{
	HOTEL_T show; // HOTEL_T show all information if use type Yes
	FILE *pIn = NULL;
	pIn = fopen(filename,"rb+");
	if(pIn == NULL)
	{
		printf("   Error file %s empty for reading!\n",filename);
		pIn = fopen(filename,"wb");
        if (pIn == NULL)
		{
		  	printf("   Can't create a new database either!\n");
		  	exit(1);
		}
	}
	else
	{ 
		int total = 0, count = 0;  // Total hotel and Count displayed hotel 
		int record = 0; // to hold the count from the file
		if(fread(&record,sizeof(int),1,pIn) != 1)
		{
			printf("   Error - file seems to be empty!\n");
			return;
		}
		while(fread(&show,sizeof(HOTEL_T),1,pIn) != 0)  // Find total hotel that exist in database (for printing result)
		{
			total++;
		}

		rewind(pIn);  // Go to the beginning of the file
		if(fread(&record,sizeof(int),1,pIn) != 1)  // If bad thing happen (file empty), show error message
		{
			printf("   Error - file seems to be empty!\n");
			return;
		}
		printf("  -Welcome to Display system-\n");  // Display Function step by five 
		while(fread(&show,sizeof(HOTEL_T),1,pIn) != 0)
		{
			if(displayHotel(show,count) == 0)
			{
				break;
			}
			count++;
		}
		fclose(pIn);
		printf("\n Total %d hotels \n",total); // Printing all of hotel number 
		printf(" Display %d hotels from the file %s\n\n",count,filename); // Printing displayed number
	}
}
/* Funciton for add more hotel. This will ask user about each information for 
 * further add into validation process. After that, it will send the total struct 
 * into recordData for write into datebase file. 
 */
void HotelAdding()
{
	int i = 0;
	int amount;
	HOTEL_T *hotel = NULL;	
	char inputLine[MAX];

	amount = welcomeRA();
	if(amount == -1)
	{
		printf("    Cancle recording!\n");
		return;
	}
	hotel = (HOTEL_T*) calloc(amount,sizeof(HOTEL_T));

	for(int i = 0; i < amount; i++)
	{
		printf("\n Adding Hotel#%d\n",i+1);
		do
		{
			memset(hotel[i].name,0,sizeof(hotel[i].name));
			printf("  Hotel name: ");
			fgets(inputLine,sizeof(inputLine),stdin);
			sscanf(inputLine,"%[^\n]",inputLine);
		} while(validateHotelName(inputLine) != 1);	
		sscanf(inputLine,"%[^\n]",hotel[i].name);
		do
		{
			memset(hotel[i].date,0,sizeof(hotel[i].date));
			printf("  Date Built: ");
			fgets(inputLine,sizeof(inputLine),stdin);
			sscanf(inputLine,"%[^\n]",inputLine);
		} while(validateDateBuilt(inputLine) != 1);	
		sscanf(inputLine,"%[^\n]",hotel[i].date);
		do
		{
			memset(hotel[i].service,0,sizeof(hotel[i].service));
			printf("  Services code: ");
			fgets(inputLine,sizeof(inputLine),stdin);
			sscanf(inputLine,"%[^\n]",inputLine);	
		} while(validateServiceCode(inputLine) != 1); 
		sscanf(inputLine,"%s",hotel[i].service);
		do
		{
			memset(hotel[i].phone,0,sizeof(hotel[i].phone));
			printf("  Thai phone: ");
			fgets(inputLine,sizeof(inputLine),stdin);
			sscanf(inputLine,"%[^\n]",inputLine);
		} while(validatePhoneNumber(inputLine) != 1); 
		sscanf(inputLine,"%s",hotel[i].phone);
		do
		{
			memset(hotel[i].province,0,sizeof(hotel[i].province));
			printf("  Province code: ");
			fgets(inputLine,sizeof(inputLine),stdin);
			sscanf(inputLine,"%[^\n]",inputLine);
		} while(validateProvinceCode(inputLine) != 1); 
		sscanf(inputLine,"%s",hotel[i].province);
		do
		{
			memset(hotel[i].star,0,sizeof(hotel[i].star));
			printf("  Star rating: ");
			fgets(inputLine,sizeof(inputLine),stdin);
			sscanf(inputLine,"%[^\n]",inputLine);
		} while(validateStarRating(inputLine) != 1); 
		sscanf(inputLine,"%s",hotel[i].star);
	} 
	recordData(hotel,amount);
	free(hotel);
	printf(" Successful Adding!\n");
}



/**********************************************************************************/
/* Welcome to Search and Modify, let you to chose which
 * criteria that you what to search by.
 */
void welcomeSM()
{
	char command[MIN];
	printf("  -Welcome to Search and Modify system-");
	while(1)
	{
		int option = 0;
		char input[MAX];
		printf("\n Hotel Search Choices \n    [1] Hotel Name    [2] Star rating    [3] Exit section\n What are you looking for? ");
		fgets(command,sizeof(command),stdin);
		sscanf(command,"%d",&option);
		if(option == 1)
		{
			do
			{
				printf("  SEARCH NAME >> ");
				fgets(input,sizeof(input),stdin);
				sscanf(input,"%[^\n]",input);
			} while(checkNameSearch(input) != 1);
			searchingHotel(input,option);
		}
		else if(option == 2)
		{
			do
			{
				printf("  SEARCH RATING >> ");
				fgets(input,sizeof(input),stdin);
				sscanf(input,"%[^\n]",input);		
			} while(checkStarSearch(input) != 1);
			searchingHotel(input,option);
		}
		else if(option == 3) 
		{
			break;
		}
		else
		{
			printf("    Invalid option >> Please try 1 - 3 only!\n");
		}
	}
}
/* Check hotel name that user type for searching process.
 * The error message will appear when user not input anything.
 */
int checkNameSearch(char *input)
{
	int bOk = 0;
	if(input[0] == '\n')
	{
		printf("    Hotel name invalid >> Please try again!\n");
	}
	else
	{
		bOk = 1;
	}
	return bOk;
}
/* Star that user provided for searching should match in with rating
 * in dataabase file for compare the digit string efficiency.
 */

int checkStarSearch(char *input)
{
	int star = 0, bOk = 0;
	if(strlen(input) == 1 && isdigit(input[0]))
	{
		star = atoi(input);
	}
	if(star > 0 && star <= 5)
	{
		bOk = 1;
	}
	else
	{
		printf("    Star rating invalid >> Please try again!\n");
	}
	return bOk;	
}
/* Searching function The program will see what type of information entered. 
 * Assuming that it is the hotel rating information, it must be only 1 character 
 * and 1 - 5 numbers, but vice versa, if it meets the conditions mentioned above,
 * but the user option is 1, it will be treated as the hotel name.
 */
void searchingHotel(char *input, int option) 
{
	HOTEL_T hotel;
	FILE *pIn = NULL;
	pIn = fopen(filename,"rb+");
	if(pIn == NULL) 
	{
		printf("   Cannot open database - Exiting!\n");
		exit(1);	
	}
	else
	{
		int total = 0;
		if(fread(&total,sizeof(int),1,pIn) != 1)
		{
			printf("   Database seems to be empty!\n");
			return;
		}
		int count = 0, select = 0;
		if(strlen(input) == 1 && isdigit(input[0]) && option == 2) // Length of input is one and that must be integer number.
		{
			printf("  >> Searching by star rating!\n");
			select = askUser();
			while(fread(&hotel,sizeof(HOTEL_T),1,pIn) != 0)
			{
				if(strcasecmp(hotel.star,input) == 0)
				{
					if(select)
					{
						displaySearch(hotel,count);
					}
					count++;
				}
			}
			printf("\n  >> Found %d hotels, which rating %s star!\n",count,input);
			if(select && count) // If count is zero, it has nothing to deal with.
			{
				modifyingHotel(input,count,option);
			}
		}
		else
		{
			printf("  >> Searching by hotel name!\n");
			select = askUser();
			while(fread(&hotel,sizeof(HOTEL_T),1,pIn) != 0)
			{
				for(int i = 0; i < strlen(input); i++)
				{ 	// Regardless of whether the user will type lower or upper case. The program can still search.
					if(tolower(hotel.name[i]) == tolower(input[i]))   
					{
						if(i == strlen(input) - 1)
						{
							if(select)
							{
								displaySearch(hotel,count);
							}
							count++;
						}
					}
					else
					{
						break;
					}
				}
			}
			printf("\n  >> Found %d hotel, start with '%s'!\n",count,input);
			if(select && count)
			{
				modifyingHotel(input,count,option);
			}
		}
	}		
}
/* Display hotel that search found from searchingHotel which searching star by 
 * string compare and searching string start by for loop to length of input 
 * by regardless to uppercase or lowercase.
 */
void displaySearch(HOTEL_T oneHotel, int position)
{
	printf("\n      SEARCH FOUND#%d\n",position+1);
	printf("  NAME: %s\n",oneHotel.name); 
	printf("  DATE: %s\n",oneHotel.date);
	printf("  SERVICE: %s\n",oneHotel.service);
	printf("  PHONE: %s\n",oneHotel.phone);
	printf("  PROVINCE: %s\n",oneHotel.province);
	printf("  STAR: %s\n",oneHotel.star);
}
/* Yes No question if yes  function return 1 true
 * or return 0 false if no.
 */
int YesOrNo(char *command)
{
	if(strcasecmp(command,"Y") == 0 || strcasecmp(command,"YES") == 0)
	{
		return 1;
	}
	else if(strcasecmp(command,"N") == 0 || strcasecmp(command,"NO") == 0)
	{
		return 0;
	}
	else 
	{
		printf("    Invalid option >> Please type Y or N only!\n");
		return -1;
	}
}
/* Ask user to show all data that search found or not.
 * If show data user are able to access modirying function further.
 */
int askUser()
{
	int select = 0;
	char input[MIN];
	do
	{
		printf("  >> Show all searching data or not (Y/n)? ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",input);
		select = YesOrNo(input);
	} while(select == -1);
	if(select == 0)
	{
		printf("\e[1;1H\e[2J"); // Clear screen before go to menu.
	}	
	return select;
}
/* If the user searches for information, the program will suggest that the 
 * information will be modify or not.
 */
void modifyingHotel(char *input, int found, int option)  // Parentheses is take a large space but it makes code easy to read.
{
	HOTEL_T hotel;
	int select = 0;
	char command[MIN];
	do
	{
		printf("  Do you want to Modify this hotel data or not (Y/n)? ");
		fgets(command,sizeof(command),stdin);
		sscanf(command,"%s",command); 
		select = YesOrNo(command);
	} while(select == -1);
	if(select == 1)
	{
		int count = 0, edit = 0;
		if(found == 1)
		{
			edit = 1;
		}
		else
		{
			edit = editPosition(found);
		}
		HOTEL_T hotel;
		FILE *pIn = NULL;
		pIn = fopen(filename,"rb+");
		if(pIn == NULL)
		{
			printf("   Cannot open file - Exiting!\n");
			exit(1);
		}
		else
		{
			int total = 0;
			if(fread(&total,sizeof(int),1,pIn) != 1)
			{
				printf("   Database seems to be empty!\n");
				return;
			}
			int count = 0, userchoice = 0, countLine = 0;
			if(strlen(input) == 1 && isdigit(input[0]) && option == 2) // Length of input is one and that must be integer number.
			{
				while(fread(&hotel,sizeof(HOTEL_T),1,pIn) != 0)
				{
					if(strcasecmp(hotel.star,input) == 0)
					{
						count++; // for print that selected iposition
						if(count == edit)
						{
							printf("\n         SELECTED");
							displaySearch(hotel,count - 1);
							printf("   THE ORDER IN FILE %d\n",countLine+1);
							{
								userchoice = editOption();
								if(userchoice == 8)
								{
									printf("\e[1;1H\e[2J"); // Clear screen before go to menu.
									return; // If user select choice 8, it means finish modify process.
								}
								editInput(userchoice,hotel,countLine);	
								printf("      Modifying Process Success!\n");
							}
						}
					}
					countLine++; // for fseek modify in overwrite
				}
					
			}
			else
			{
				while(fread(&hotel,sizeof(HOTEL_T),1,pIn) != 0)
				{
					for(int i = 0; i < strlen(input); i++)
					{ 	
						if(tolower(hotel.name[i]) == tolower(input[i]) && i == strlen(input) - 1)   
						{
							count++;
							if(count == edit)
							{
								printf("\n         SELECTED");
								displaySearch(hotel,count - 1);
								printf("   THE ORDER IN FILE %d\n",countLine+1);
								while(1)
								{
									userchoice = editOption();
									if(userchoice == 8)
									{
										printf("\e[1;1H\e[2J"); // Clear screen before go to menu.
										return; // If user select choice 8, it means finish modify process.
									}
									editInput(userchoice,hotel,countLine);	
									printf("      Modifying Process Success!\n");
								}
							}
						}
						else if(tolower(hotel.name[i]) != tolower(input[i]))
						{
							break; // If some character not match, stop checking.
						}
					}
					countLine++; // for fseek modify in overwrite
				}

			}
		}
	}
	else
	{
		printf("\e[1;1H\e[2J"); // If not modify, clear screen for menu window.
	}
}
/* If the user chooses that they want to modify the information. The program 
 * will ask how much data you want to modify (in case system find more than 
 * one searchable data).
 */
int editPosition(int found)
{
	int edit = 0;
	char input[MIN];
	while(1)
	{
		printf("    Please specify which found number from searching >> ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",input);
		if(isdigit(input[0]) && strlen(input) == 1)
		{
			edit = atoi(input);
			if(edit > 0 && edit <= found)
			{
				return edit;
			}
			else
			{
				printf("      Edit number invalid >> Please specify number 1 - %d that was found!\n",found);
			}
		}
		else
		{
			printf("      Edit index invalid >> Please fill out integer 1 - %d only!\n",found);
		}
	}
}
/* When the struct of the data to be edited can be specified. The program will choose 
 * which part of the information you want to edit, such as name, service date, phone number, 
 * province, rating or want to edit all of the above If you want to edit not all, you can select 
 * only one item at a time. When finished the first selected one, the program will let choose to 
 * edit other things in the future.
 */
int editOption()
{
	while(1)
	{
		int option = -1;
		char input[MIN];
		printf("\n  Hotel Modifying option\n");
		printf("      [1] - Hotel name      [2] - Date built      [3] - Service code\n");
		printf("      [4] - Phone number    [5] - Province code   [6] - Star rating\n");
		printf("      [7] - Change all      [8] - Finish modify this data\n");
		printf("  What would you like to modify? ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",input);
		if(strlen(input) == 1 && isdigit(input[0]))
		{
			option = atoi(input);
			if(option > 0 && option <= 8)
			{
				return option;
			}
			else 
			{
				option = -1;
			}
		}	
		if(option == -1)
		{
			printf("    Modify option invalid >> Please try 1 - 7!\n");	
		}
	}
}
/* Of course, when changing the information to a new one Must have to check if 
 * the newly received data matches the format specified by the system or not, 
 * if the conditions cannot be met, the program will display an error message and ask 
 * the user to enter information again.
 */
void editInput(int option, HOTEL_T hotel, int countLine)
{
	char input[MAX];
	switch(option)
	{
		case 7:
		case 1:
			do
			{
				printf("  (NEW) HOTEL NAME: ");
				fgets(input,sizeof(input),stdin);
				sscanf(input,"%[^\n]",input);
			} while(validateHotelName(input) != 1);
			sscanf(input,"%[^\n]",hotel.name);
			if(option != 7)
				break;
		case 2:
			do
			{
				printf("  (NEW) DATE BUILT: ");
				fgets(input,sizeof(input),stdin);
				sscanf(input,"%[^\n]",input);
			} while(validateDateBuilt(input) != 1);
			sscanf(input,"%[^\n]",hotel.date);
			if(option != 7)
				break;
		case 3:
			do
			{
				printf("  (NEW) SERVICE CODE: ");
				fgets(input,sizeof(input),stdin);
				sscanf(input,"%[^\n]",input);
			} while(validateServiceCode(input) != 1);
			sscanf(input,"%[^\n]",hotel.service);
			if(option != 7)
				break;
		case 4:
			do
			{
				printf("  (NEW) PHONE NUMBER: ");
				fgets(input,sizeof(input),stdin);
				sscanf(input,"%[^\n]",input);
			} while(validatePhoneNumber(input) != 1);
			sscanf(input,"%[^\n]",hotel.phone);
			if(option != 7)
				break;
		case 5:
			do
			{
				printf("  (NEW) PROVINCE CODE: ");
				fgets(input,sizeof(input),stdin);
				sscanf(input,"%[^\n]",input);
			} while(validateProvinceCode(input) != 1);
			sscanf(input,"%[^\n]",hotel.province);
			if(option != 7)
				break;
		case 6:
			do
			{
				printf("  (NEW) STAR RATING: ");
				fgets(input,sizeof(input),stdin);
				sscanf(input,"%[^\n]",input);
			} while(validateStarRating(input) != 1);
			sscanf(input,"%[^\n]",hotel.star);
			if(option != 7)
				break;
	}	
	overwriteModify(hotel,1,countLine);
}
/* The data to be modified and validated will be overwritten by the old data in the 
 * database based on the first struct location the file was read (can be seen from 
 * the search process).
 */
void overwriteModify(HOTEL_T hotel, int writenum, int countLine) // Edit just one hotel
{
	HOTEL_T edit;
	FILE *pOut = NULL;
	pOut = fopen(filename,"rb+");

	if(pOut == NULL)
	{   // For the worst case scenario happend.
		printf("   No database '%s' found - Creating new!\n",filename);
    	pOut = fopen(filename,"wb");
        if (pOut == NULL)
		{
		  	printf("   Can't create a new database either!\n");
		  	exit(1);
		}
	}

	fseek(pOut,(countLine)*sizeof(HOTEL_T) + sizeof(int),SEEK_SET);
	if(fwrite(&hotel,sizeof(HOTEL_T),writenum,pOut) != writenum)
	{
		printf("   Unexpected writing hotel data!\n");
	}
	fclose(pOut);
}
