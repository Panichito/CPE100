/* Program for validation
 *
 * Created by Panithi Suwanno 63070503426 (Big)
 * 16 NOV 2020
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "validateFunctions.h"
#include "dateFunctions.h"

/**************************************************** CHECK HOTEL NAME ****************************************************/
/* Examine user input if has nothing it will print error message.
 * Then, let user input hotel name again. 
 */
int validateHotelName(char *input) 
{
	int valid = 0;
	if(input[0] == '\n') 
	{
		printf("    Invalid >> Please fill out Thai hotel name information!\n");
	}	
	else
	{
		valid = 1;
	}
	
	return valid;
}

/**************************************************** CHECK DATE BUILT ****************************************************/
/* Local function, convert month abbreviation into integer 1 - 12.
 * For call the checkDate function in dateFunction.c 
 * To make sure all inputted date are certified by Dr.Sally code in correct format.
 */
int convertMonth(char month[])
{
	int i;
	int mon = 0;
	char *check_month[12] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
	
	if(!isdigit(month[0]) && !isdigit(month[1]) && !isdigit(month[2]) && isupper(month[0]) && isupper(month[1]) && isupper(month[2]))
	{
		for(i = 0; i < 12; i++)
		{
			if(strcmp(month,check_month[i]) == 0)
			{
				mon = i + 1;
				break;
			}
		}
		if(mon == 0)
		{
			printf("    Invalid >> Month abbreviation fault!\n");
		}	
	}
	else
	{
		printf("    Invalid >> Month must be all uppercase alphabet!\n");
	}
	return mon;
}
/* Local function, check fure from dataCompare function, 
 *  if return 0 = Today, return 1 = Future (print error message), return -1 = Past.
 */
int checkFuture(DATE_T *date, int monthInteger)
{
	int compare_date = 0;
	compare_date = dateCompare(date->dayBuilt,monthInteger,date->yearBuilt,date->dayToday,date->monthToday,date->yearToday);
	if(compare_date == 1)
	{
		printf("    Invalid >> Date is in the future\n");
	}
	return compare_date;
}
/* Examine date input which year rage 1900 to the current date 
 * inside this functino also recall from dateFunction.h (provided by Dr.Sally)
 * for get current date info, validate future date and check leap year 
 */
int validateDateBuilt(char *input)
{
	int d,m,y; // day month year in order to use this in checkDate
	int built_Date;
	int monthInteger = 0;
	char output[MIN];
	DATE_T date[MAX];
	int valid = 0;
	dateToday(&date->dayToday,&date->monthToday,&date->yearToday);
	if(strlen(input) != 11)
	{
		printf("    Invalid >> Please fill out date dd MMM yyyy format!\n");
	}
	else
	{
		if(input[0] != ' ' && input[1] != ' ' && input[2] == ' ' && input[3] != ' ' && input[4] != ' ' && input[5] != ' '&& input[6] == ' ' && input[7] != ' ' && input[8] != ' ' && input[9] != ' ' && input[10] != ' ')
		{
			sscanf(input,"%2d %s %4d",&date->dayBuilt,date->month,&date->yearBuilt);
			monthInteger = convertMonth(date->month);
			if(monthInteger)
			{
				sprintf(output,"%02d/%02d/%02d",date->dayBuilt,monthInteger,date->yearBuilt);  /* this will create "dd/mm/yyyy" */
				if(checkDate(output,&d,&m,&y) == 0)
				{
					built_Date = checkFuture(date,monthInteger);
					if(built_Date == 0 || built_Date == -1)  /* built date must be in the past or today only */
					{
						valid = 1;
					}
				}
				else 
				{
					printf("    Invalid >> Improper date that hotel never exist!\n");
				}
			}	
		}
		else
		{
			printf("    Invalid >> Date inputted does not in dd MMM yyyy format!\n");
		}
	}
	return valid;
}

/**************************************************** CHECK SERVICE CODE ****************************************************/
/* Local function, for checking 'P','R','W','S','T' are not repeated
 * and have dollar sign no more 4 signs
 */
int checkDuplicated(char *input, int length)
{
	int repeat = 1;
	int count = 0;
	int i,j;

	for(i = 0; i < length; i++)
	{
		for(j = i + 1; j < length; j++)
		{
			if(input[i] == input[j])
			{
				if(input[i] != '$')
				{
					printf("    Invalid >> '%c' is repeated!\n",input[i]);
					repeat = 0;
					break;
				}
				if(input[i] == '$')
				{
					count++;
					break;
				}
			}
		}
		if(repeat == 0)
		{
			break;
		}
	}
	if(count > 3)
	{
		printf("    Invalid >> Dollar sign should between 1 - 4 symbols!\n");
		repeat = 0;
	}
	return repeat;
}
/* Examine hotel service code which must have dollar sign or special characters
 * for indentify kind of service the hotel avaliable (no duplicated word)
 */
int validateServiceCode(char *input)
{	
	int i,j;
	int check = 0;
	int count = 0;
	int length = strlen(input);
	int valid = 0;
	char letter[6] = {'P','R','W','S','T','$'};
	
	if(length > 0 && length <= 9)  /* worst case scenario is 9 (PRWST$$$$) */ 
	{
		for(i = 0; i < length; i++)
		{	
			if(input[i] == letter[0] || input[i] == letter[1] || input[i] == letter[2] || input[i] == letter[3] || input[i] == letter[4] || input[i] == letter[5])
			{	
				check = 1;
				count++;  /* count character that match the condition in letter array */
			}
		}
		if(count == length) /* if all character thaht meet our condition it means all inputted characters are valid */
		{	
			count = 0;  /* set old variable for new count and save the significant memmory of computer >.< */
			for(i = 0; i < length; i++)
			{
				if(input[i] == '$')
				{
					count++; /* count dollar symbol */
				}
			}

			if(count == 0)
			{
				printf("    Invalid >> No dollar sign!\n");
			}
			else if(checkDuplicated(input,length))
			{
				valid = 1;
			}
		}
		else
		{
			printf("    Invalid >> Only uppercase 'P','R','W','S','T' with '$' are allowed!\n");
		}	
	}
	else
	{
		printf("    Invalid >> Please fill in hotel service code with correct format!\n");
	}
	return valid;
}

/**************************************************** CHECK THAI MOBILE PHONE ****************************************************/
/* Examine phone number with no dashes. My intention is make all information stored
 * in the same format and easy to understand it. Phone number should star with 
 * 01 05 06 08 09 only. Furthermore, it must be 10 digits. 
 */ 
int validatePhoneNumber(char *input)
{
	int i;
	int nonum = 1; /* not number */
	int valid = 0;
	if(strlen(input) == 10)
	{
		for(i = 0; i < strlen(input); ++i)
		{
			if(isdigit(input[i]) == 0)
			{
				printf("    Invalid >> Only a numeric character is allowed!\n");
				nonum = 0;
				break;
			}
		}
	
		if(nonum)
		{
			if(input[0] == '0' && (input[1] == '1' || input[1] == '5' || input[1] == '6' || input[1] == '8' || input[1] == '9'))
			{
				valid = 1;
			}
			if(valid == 0)
			{
				printf("    Invalid >> First two digits must be 01, 05, 06, 08, 09!\n");
			}
		}
	}
	else
	{
		printf("    Invalid >> Please fill in Thai hotel telephone format which no dashes!\n"); 
	}	
	return valid;
}	

/**************************************************** CHECK PROVINCE CODE ****************************************************/
/* Examine Thai province code started with 'TH-' and has a number at the end.
 * The numbers must be between 10 and 96 inclusive. If the number is not used, 
 * it must be the 'S' of the Pattaya Special Administrative Region only.
 * If the following conditions are not met, an error message will appear.
 */
int validateProvinceCode(char *input)
{
	int valid = 0;
	if(strlen(input) == 4)
	{
		if(input[0] == 'T' && input[1] == 'H' && input[2] == '-' && input[3] == 'S')
		{
			valid = 1;
		}
		else
		{
			printf("    Invalid >> This case hotel province number must be 'TH-S' uppercase only!\n");
		}
	}

	else if(strlen(input) == 5)
	{
		if(input[0] == 'T' && input[1] == 'H' && input[2] == '-' && isdigit(input[3]) != 0 && isdigit(input[4]) != 0)
		{
			if(input[3] != '0') 
			{
				valid = 1;
				if(input[3] == '9' && (input[4] == '7' || input[4] == '8' || input[4] == '9'))
				{
					valid = 0;
				}
			}
			if(valid == 0)
			{
				printf("    Invalid >> Hotel province number is between 10 - 96 only!\n");
			}	
		}	
		else 
		{
			printf("    Invalid >> Your inputted not in 'TH-nn' format!\n");
		}
	}
	else
	{
		printf("    Invalid >> Please fill in Thai province code format!\n"); 
	}
	return valid;
}

/**************************************************** CHECK STAR RATING ****************************************************/
/* Examine hotel rating. The hotel rating must be 1 to 5 stars only. 
 * No letters or decimal places. To make it more convenient for the 
 * user to remember when displaying the data.
 */
int validateStarRating(char *input)
{
	int star;
	int valid = 0;
	if(strlen(input) == 1 && isdigit(input[0]) != 0)
	{
		star = atoi(input);
		if(star > 0 && star <= 5)
		{
			valid = 1;
		}
		else 
		{
			printf("    Invalid >> Star is integer between 1 - 5 !\n");
		}
	}	
	else
	{
		printf("    Invalid >> Please input star rating with correct format!\n");
	}
	return valid;
}