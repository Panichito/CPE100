/***********************************************************
* Project 1 - validate information from adorable users
* Topic: 4 16 7 11 
*
* The main purpose of this program is to check data
* from users that it meets the conditions or not.
* And then show the correct results to output in 
* term of Valid and Invalid display.
*
* Created by Panithi Suwanni (Big) 63070503426 CPE KMUTT
* contact: panithi2001big@gmail.com
* 20 OCT 2020
***********************************************************
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 64
#define MID 32
#define MIN 10


	/* the 1st Function */
int validateDate(); 
/* the specific purpose is to check whether the MMM is all uppercase or not */										
int checkUppercase(char word[]);
/* to examine month from user input and follow the coding standard rule (no more 50 lines) */							
int checkMonth(char month[], int* pCount);		


	/* the 2nd function */
int validateString();
/* the function to recieve string input from user in order to reduce funtion length regarding to coding standard */		
void inputString(char returnString[], int sizeString);	
/* check all 32 C language key words */
int checkReserveword(char string[]);			


	/* the 3rd function */
int validatePhone();
/* phone number must contain plus sign and two dash signs and also tell 3rd function the dash position */
int checkPlusDashSign(char phone[], int* pCount, int *pDash1, int *pDash2);
/* to assay all international phone number is number or not */
int checkAllnum(char phone[],int dash1,int dash2, int* pAll_num);


	/* the 4th function */
int validateBank();
/* first three must match the given condition */
int checkPrefix(char bank[]);								
/* last three should contain at least one zero */
int checkTriplet(char bank[]);
/* check when user input information that has 11 characters */
int check11digits(char bank[]);
/* check when user input information that has 13 characters */
int check13digits(char bank[]);


	/* the main function */
int main()
{
	int count[4] = {0,0,0,0};
	int option = 0;
	char input[MIN];

	while(option != 5)
	{
		printf("Validation options: ");
		printf("\n\t1 - Check date in form dd MMM yyyy");
		printf("\n\t2 - Check a string as a C language identifier");
		printf("\n\t3 - Check international phone number");
		printf("\n\t4 - Check bank account number");
		printf("\n\t5 - Exit the program");

		printf("\nWhat do you want to do? ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&option);
		// let user choose option of validation
		if(option >= 1 && option <= 5)
		{
			if(option == 1)
			{
				count[0] += validateDate();
			}
			else if(option == 2)
			{
				count[1] += validateString();
			}
			else if(option == 3)
			{
				count[2] += validatePhone();
			}
			else if(option == 4)
			{
				count[3] += validateBank();
			}
			else if(option == 5)
			{
				break;
			}
		}
		else
		{
			printf("    Invalid option, please try again!\n");
		}
	}
	// print the result 
	printf("Program run summary:\n");
	printf("    Validation type 1: %d\n",count[0]);
	printf("    Validation type 2: %d\n",count[1]);
	printf("    Validation type 3: %d\n",count[2]);
	printf("    Validation type 4: %d\n",count[3]);
	
	return 0;
}

/******************************** Start the First Function *************************************/

int checkUppercase(char word[]) // This function create for specific check MMM input are capital letters 
{
	int i = 0; // set for use in loop
	int bOk = 1; // check true or false
	
	for(i = 0; i < strlen(word); i++) // loop check all letters 
	{
		if(isupper(word[i]))
		{
			bOk = 1; // True when word are all uppercase
		}
		else
		{
			bOk = 0; // False when word are not match the format
		}
	}
	
	return bOk;
}

int checkMonth(char month[], int* pCount)
{
	char *check_month[12] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"}; //month possible form (condition)
	int mon, bOk = 0; // bOk variabel on behalf of check true or false in MMM format // declare mon variable to use in loop (it is sequence for check month 1 - 12)
	int correct_month = 0; // if month that inputted correct according to MMM format it will show a value 1
	int count = 0;
 
	if(strlen(month) == 3) // check MMM consist of 3 letters
	{
		bOk = checkUppercase(month); // call the function in order to check MMM are all uppercase
		if(bOk == 1) 
		{
			for(mon = 0; mon < 12; mon++) // use for loop in order to check month that inputted meets check_month array or not
			{
				if(strcmp(month,check_month[mon]) == 0) // I want to examine that input month match the condition in check_month or not
				{
					correct_month = 1; // Valid
					break; // FOUND THE MONTH - keep it for further testing correct day 
				}
			}
    		if(correct_month == 0)
    		{
        		printf("\tInvalid - month\n");
        		count++;
    		}
		}
		else
		{
			printf("\tInvalid - month must be all capital letters\n");
			count++;
		}
	}
	else
	{
		printf("\tInvalid - month abbreviation\n");
		count++;
	}
	*pCount = count;
	return correct_month;
}

int validateDate() 
{
    int total_count = 0;
	int count = 0;
	int *pCount = &count;
	int day = 0;
	char month[MIN];
	int correct_month = 0;
	int year = 0;
	char input[MAX];

	printf(" Validate Date dd MMM yyyy - Western year (Hit return to stop)\n");
	while(1)
	{
		printf("    Enter date: ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%2d %s %4d",&day,month,&year);
	
		if(input[0] == '\n')
		{
			break;
		}
		// examine year cannot over than 100 years in the past or the future 
		if(year >= 1920 && year <= 2120)
		{	// examine month
			correct_month = checkMonth(month,pCount);
			if(correct_month == 1) 
			{	// examine day
				if((day >= 1 && day <= 31) && (strcmp(month,"JAN") == 0 || strcmp(month,"MAR") == 0 || strcmp(month,"MAY") == 0 || strcmp(month,"JUL") == 0 || strcmp(month,"AUG") == 0 || strcmp(month,"OCT") == 0 || strcmp(month,"DEC") == 0))
		       	{
		            printf("\tValid\n");
		            count++; 
		        }  
		        else if((day >= 1 && day <= 30) && (strcmp(month,"APR") == 0 || strcmp(month,"JUN") == 0 || strcmp(month,"SEP") == 0 || strcmp(month,"NOV") == 0))
		        {
		            printf("\tValid\n");
		            count++; 
		        } 
		        else if((day >= 1 && day <= 28) && strcmp(month,"FEB") == 0)
				{
		           	printf("\tValid\n");
		            count++;
		        } 
		        else if(day == 29 && strcmp(month,"FEB") == 0 && (year%400 == 0 ||(year%4 == 0 && year%100 != 0)))
		        {
		            printf("\tValid\n");
		            count++;
		        } 
		        else 
		        {
		            printf("\tInvalid - day of month\n");
		            count++;
		        }
			}
		}
		else if(year - 543 >= 1920 && year -543<= 2120)
        {
            printf("\tInvalid - buddhist year\n");
            count++;
        }
		else 
		{
			printf("\tInvalid - year outside allowed range\n");
			count++;
		}			   
		total_count += count; count = 0; // set count to zero because in ELSE case because count will store duplicate with function and count inside if condition
	}									// and due to I declared ELSE condition an input that come through ELSE count will store in total_count go on and on that makes count incorrect
	return total_count;	
}

/******************************** End the First Function *************************************/


/******************************** Start the Second Function *************************************/

void inputString(char returnString[], int sizeString)
{
    printf("    Enter a string: ");
    fgets(returnString,sizeString,stdin);
    sscanf(returnString,"%[^\n]",returnString);
}

int checkReserveword(char string[])
{
    int word = 0; // loop
    int not_keyword = 1; // 1 means Valid
    char *reserve_word[32]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long",
                            "register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
    for(word = 0; word < 32; word++)
    {
        if(strcmp(string,reserve_word[word]) == 0)
        {
            not_keyword = 0; 
            break;
        } 
    }
    return not_keyword;
}

int validateString()
{
	int i = 0;
	int count = 0;
	int correct_string = 0;
	char string[MID];

	printf(" Validate a string as a C language identifier (Hit return to stop)\n");
	while(1)
	{
		inputString(string,sizeof(string));
		if(string[0] == '\n')
		{
			break;
		}
		for(i = 0; i < strlen(string); i++)
		{
			if((isalpha(string[i]) == 0) && (string[i] != '_'))
			{
				if((isalpha(string[0]) == 0) && (string[0] != '_'))
				{
					printf("\tInvalid - start with number or illegal sign\n");
					correct_string = 0;
					count++;
					break;
				}
				else
				{
					if(string[i] == ' ')
					{
						printf("\tInvalid - embedded space\n");
						correct_string = 0;
						count++;
						break;
					}
					else if(isdigit(string[i]) == 0)
					{
						printf("\tInvalid - '%c' is not allowed symbol\n",string[i]);
		                correct_string = 0;
		                count++;
		                break;
	            	}
				}
			}
			else
			{
				correct_string = 1;
			}
		}
		if(correct_string == 1)
		{
			correct_string = checkReserveword(string);
			if(correct_string == 1)
			{
				printf("\tValid\n");
				count++;
			}
			else
			{
				printf("\tInvalid - C langauge keyword\n");
				count++;
			}
		}
		correct_string = 0;
	}
	return count;
}

/******************************** End the Second Function *************************************/


/******************************** Start the Third Function *************************************/

int checkPlusDashSign(char phone[], int* pCount, int *pDash1, int *pDash2)
{
    int i = 0; // loop
    int count = 0;
    int valid = 0; // define 0-false no dash, 1-true has dash, 2-miss dash (just one dash now), 3-use parentheses replace dashes sign
    int dash_position1 = 0;
    int dash_position2 = 0;

    if(phone[0] == '+')
    {
        for(i = 1; i < strlen(phone); i++) // check first number afterplus sign until the last number
        {
            if(phone[i] == '-')
            {   
                dash_position1 = i; valid = 2;
                break;
            }
            else if(phone[i] == '(' || phone[i] == ')')
            {   
                valid = 3;
                break;
            }
        }
        if(valid == 0)
        {
        	printf("\tInvalid - no dash\n");
            count++;
        }
        else if(valid == 2)
        {
            for(i = dash_position1 + 1; i < strlen(phone); i++) // check the number after previous dash until the last number
            {
                if(phone[i] == '-')
                {   
                    dash_position2 = i; valid = 1;
                    break;
                }
            }  
        }
        if(valid == 2)
        {
            printf("\tInvalid - missing dash\n");
            count++;
        } 
        else if(valid == 3)
        {
        	printf("\tInvalid - parentheses not allowed please use dashes sign instead\n");
            count++;
        }
    }
    else
    {
        printf("\tInvalid - no plus\n");
        count++;
    } 
    *pCount = count; *pDash1 = dash_position1; *pDash2 = dash_position2;
    return valid;
}

int checkAllnum(char phone[], int dash1, int dash2, int* pAll_num) // check all inputted number must had no alphabet character
{
    int i = 0; // loop
    int num = 1; // 0 - invalid alphabet, 1 - valid
    int specify = 0; // where character located is not allowed

    for(i = 1; i < dash1; i++) // examine number between plus sign until the first dash sign
    {
        if(isdigit(phone[i]) == 0)
        {
            num = 0; // not valid
            specify = i;
            break;
        }
    }
    if(num == 1) // examine number between the first dash sign until the second dash sign
    {
        for(i = dash1 + 1; i< dash2; i++)
        {
            if(isdigit(phone[i]) == 0)
            {
                num = 0; // not valid
                specify = i;
                break;
            }            
        }
    }
    if(num == 1) // examine number between the second dash sign until the last one
    {
        for(i = dash2 +1; i < strlen(phone); i++)
        {
            if(isdigit(phone[i]) == 0)
            {
                num = 0; // not valid
                specify = i;
                break;
            }            
        }
    }
    *pAll_num = num;
    return specify; // send i back to function because it will return array number that make it did not meet the condition
}

int validatePhone()
{
    int i = 0;  // loop
    int total_count = 0;
    int count = 0; 
    int *pCount = &count;
    int dash1 = 0; int dash2 = 0;
    int *pDash1 = &dash1; int *pDash2 = &dash2;
    int phone_sign = 0; // to check phone number must have plus and dash sign
    int all_num = 1; // to check all phone number is not consist of alphabetic character (0 - invalid alphabet, 1 - valid)
    int *pAll_num = &all_num;
    int specify = 0; // to specify which character is not allowed
    char phone[MID];

    printf(" Validate international phone number (Hit return to stop)\n");
    while(1)
    {
        printf("    Enter international phone number: ");
        fgets(phone,sizeof(phone),stdin);
        sscanf(phone,"%s",phone);

        if(phone[0] == '\n')
        {
            break;
        }

        phone_sign = checkPlusDashSign(phone,pCount,pDash1,pDash2);
        if(phone_sign == 1)
        {   
            if(dash1 > 4)
            {
                printf("\tInvalid - country code too long\n");
                count++;
            }
            else if(dash1 <= 4 && dash2 - dash1 > 4)
            {
                printf("\tInvalid - city/area code too long\n");
                count++;
            }
            else
            {
                if((strlen(phone) - 1 - dash2) >= 6 && (strlen(phone) - 1 - dash2) <= 10)
                {
                    specify = checkAllnum(phone,dash1,dash2,pAll_num);
                    if(all_num == 0)
                    {
                        printf("\tInvalid - '%c' is not allowed please type all numbers\n",phone[specify]);
                        count++;
                    }
                    else
                    {
                        printf("\tValid\n");
                        count++;
                    }
                }
                else
                {
                    printf("\tInvalid - individual phone number must be between 6 and 10 additional digits\n");
                    count++;
                }
            }
        }      
        total_count += count;
    }
    return total_count;
}

/******************************** End the Third Function *************************************/

/******************************** Start the Fourth Function *************************************/


int checkPrefix(char bank[]) // check prefix first three digits
{
	int i = 0; // loop
	int true_prefix = 0;
	char *accept_prefix[6] = {"206","209","128","921","403","421"};
	char prefix[3];

	sscanf(bank,"%3s",prefix); // get only first three digits

	for(i = 0; i < 6; i++)
	{
		if(strcmp(prefix,accept_prefix[i]) == 0)
		{
			true_prefix = 1;
			break;
		}
	}

	return true_prefix;
}
int checkTriplet(char bank[]) // check suffix in last three digits must have zero
{
	int i = 0; // loop
	int true_suffix = 0;
	
	for(i = strlen(bank) - 1; i > strlen(bank) - 4; i--)
	{
		if(bank[i] == '0')
		{
			true_suffix = 1;
			break;
		}
	}

	return true_suffix;
}

int check11digits(char bank[])
{
	int count = 0;
	int prefix = 0; 
	int triplet = 0;

	if(isdigit(bank[0]) != 0 && isdigit(bank[1]) != 0 && isdigit(bank[2]) != 0 && isdigit(bank[3]) != 0 && isdigit(bank[4]) != 0 && isdigit(bank[5]) != 0 
		&& isdigit(bank[6]) != 0 && isdigit(bank[7]) != 0 && isdigit(bank[8]) != 0 && isdigit(bank[9]) != 0 && isdigit(bank[10]) != 0)
	{
		prefix = checkPrefix(bank);
		triplet = checkTriplet(bank);
		if(prefix == 1 && triplet == 1)
		{
			printf("\tValid\n");
			count++;
		}
		else if(prefix == 0)
		{
			printf("\tInvalid - wrong prefix\n");
			count++;
		}
		else if(triplet == 0)
		{
			printf("\tInvalid - no zero in the ending triplet\n"); 
			count++;
		}
	}
	else
	{
		printf("\tInvalid - not all digits\n");
		count++;					
	}
	return count;
}

int check13digits(char bank[])
{
	int count = 0;
	int prefix = 0; 
	int triplet = 0;

	if(isdigit(bank[0]) != 0 && isdigit(bank[1]) != 0 && isdigit(bank[2]) != 0 && bank[3] == '-' && isdigit(bank[4]) != 0 && isdigit(bank[5]) != 0 && isdigit(bank[6]) != 0 
		&& isdigit(bank[7]) != 0 && isdigit(bank[8]) != 0 && bank[9] == '-' && isdigit(bank[10]) != 0 && isdigit(bank[11]) != 0 && isdigit(bank[12]) != 0)
	{
		prefix = checkPrefix(bank);
		triplet = checkTriplet(bank);
		if(prefix == 1 && triplet == 1)
		{
			printf("\tValid\n");
			count++;
		}
		else if(prefix == 0)
		{
			printf("\tInvalid - wrong prefix\n");
			count++;
		}
		else if(triplet == 0)
		{
			printf("\tInvalid - no zero in the ending triplet\n");
			count++;
		}		
	}
	else if(bank[3] != '-' || bank[9] != '-')
	{
		printf("\tInvalid - missing dash in the correct position\n");
		count++;
	}
	else
	{
		printf("\tInvalid - not all digits\n");
		count++;	
	}
	return count;
}

int validateBank()
{
	int count = 0; 
	char bank[MID];

	printf(" Validate bank account number (Hit return to stop)\n");
	while(1)
	{
		printf("    Enter bank account number: ");
		fgets(bank,sizeof(bank),stdin);
		sscanf(bank,"%s",bank);

		if(bank[0] == '\n')
		{
			break;
		}
		if(strlen(bank) == 11)
		{
			count += check11digits(bank);
		}
		else if(strlen(bank) == 13)
		{
			count += check13digits(bank);
		}
		else if(strlen(bank) > 13)
		{
			printf("\tInvalid - too much digits (%ld digits)\n",strlen(bank));
			count++;
		}
		else if(strlen(bank) < 11)
		{
			printf("\tInvalid - too few digits (%ld digits)\n",strlen(bank));
			count++;
		}
		else if(strlen(bank) == 12)
		{
			printf("\tInvalid - incorrect digits (%ld digits)\n",strlen(bank));
			count++;
		}
	}
	return count;
}
 
/******************************** End the Fourth Function *************************************/