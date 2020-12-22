/* Program shows User Interface window
 *
 * Created by Panithi Suwanno 63070503426 (Big)
 */
#include <stdio.h>
#include <stdlib.h>
#include "HotelFunctions.h" // Hotel functions header file

void uiLogo();
void userhelp();

int main()
{
	char userinput[64];
	uiLogo();
	while(1)
	{
		int option = 0;
		printf("\n  PANITHI's THAI HOTEL DATABASE SYSTEM HOME PAGE \n");
		printf("    [1] - Display All Hotel in Database\n");
		printf("    [2] - Add Hotel Information\n");
		printf("    [3] - Search and Modify Hotel Data\n");
		printf("    [4] - User Help (FAQ)\n"); 
		printf("    [5] - Exit the program\n");
		printf("  What would you like to do? ");
		fgets(userinput,sizeof(userinput),stdin);
		sscanf(userinput,"%d",&option);
		switch(option)
		{
			case 1:
				printf("\e[1;1H\e[2J"); // From https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c#:~:text=just%20type%20clrscr()%3B%20function,function%20easy%20to%20clear%20screen.
				showData();
				break;
			case 2: 
				printf("\e[1;1H\e[2J"); 
				HotelAdding();
				break;
			case 3:
				printf("\e[1;1H\e[2J");
				welcomeSM();
				break;
			case 4:
				printf("\e[1;1H\e[2J");
				userhelp();
				break;
			case 5:
				printf("\e[1;1H\e[2J");
				printf("\n  Good Bye! \n\n");
				exit(0);
			default:
				printf("    Invalid option >> Please try again!\n");
		}
	}
}

void uiLogo()
{
	printf("  ___\n");
	printf(" | _ |            _  _    _      _\n");
	printf(" |  _|___  _____ (_)| |_ | |    (_)\n");
	printf(" | | |_  ||  _  || ||  _|| |___ | |\n");
	printf(" | |  _| || | | || || |_ |  _  || |\n");
	printf(" |_| |___||_| |_||_||___\\|_| |_||_|\n");
	printf("  Apache ActiveMQ Panithi CPE 1.0.0\n\n");
}

void userhelp()
{
	printf("\n\n   ################################################################################################\n");
	printf("                                    -PANITHI THAI HOTEL DATABASE-          \n");
	printf("   HOW TO USE: Choose option 1 - 4, then enter the information correctly in the format specified\n");
	printf("               by the program in the text field.\n");
	printf("   OBJECTIVE: To store the persistent Thai hotel info in order to manipulate or browse it.\n");
	printf("   FUNCTION: 1. Display all existing information in the database file.\n");
	printf("             2. Adding more data which user must input NAME, DATE, SERVICE, PHONE, PROVINCE, STAR\n");
	printf("                into system then program will append it to database.\n");
	printf("             3. Search and Modify by select what user is looking for by Name or Rating. After that,\n");
	printf("                program will ask you to modify that data or not. \n");
	printf("   CREATOR: Panithi Suwanno (Big)     DATE: 16 NOV 2020     CONTACT: panithi2001big@gmail.com\n");
	printf("   ################################################################################################\n\n");
}