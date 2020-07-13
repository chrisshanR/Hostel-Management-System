#include "library.h"
#include "functionPrototype.h"
#include "structStudent.h"
int main()
{
	int internet = 0, gym = 0, week, limit = 0, count, b, a1[100], a3[100], b1[100], b2[100], choose1 = 0;
	char choose3[100], choose2[100], skip[100], tempoTP[50], week1[100], currentRoom[1000], currentBlock[3], line[256], rooom[1000];
	char *room1;
	FILE *fptra1, *fptra3, *fptrb1, *fptrb2, *fptrw, *fptrr, *fptra;
	struct student student1;
	time_t currentTime;
	time(&currentTime);
	printf("%s", ctime(&currentTime));
	printf("Please enter your first name: "); /*The first startup of the program by saving the fundamental information of the hosteler*/
	scanf("%s", &student1.FirstName);
	printf("\nPlease enter your last name: ");
	scanf("%s", &student1.LastName);
	while (1)
	{
		printf("\nPlease enter the gender (male/female): ");
		scanf("%s", &student1.gender);
		strcpy(student1.gender, strlwr(student1.gender));
		if (!strcmp(student1.gender, "male") || !strcmp(student1.gender, "female"))
		{
			break;
		}
		else
			continue;
	}
	printf("\nPlease enter your student ID: ");
	scanf("%s", &student1.TP);
	strcpy(tempoTP, strupr(student1.TP));
	strcat(tempoTP, ".txt");
	fptrr = fopen(tempoTP, "r");
	if (fptrr == NULL)
	{
		fptrw = fopen(tempoTP, "w");
		fprintf(fptrw, "%s\n", student1.FirstName);
		fprintf(fptrw, "%s\n", student1.LastName);
		fprintf(fptrw, "%s\n", student1.gender);
		fprintf(fptrw, "%s", student1.TP);
		fclose(fptrw);
	}
	if (fptrr != NULL)
	{
		fclose(fptrr);
	}
	while (1)
	{
		system("cls");
		printf("Please choose what you want to do?\n1. Check room availability\n2. Booking the room\n3. Hosteler room detail\n4. Payment facility\n5. Cancellation\n6. Change room\n7. Exit the program\nPlease choose (1 - 7) from above: "); /*Features option for the main menu*/
		scanf("%s", &choose2);
		if (!(!strcmp(choose2, "1") || !strcmp(choose2, "2") || !strcmp(choose2, "3") || !strcmp(choose2, "4") || !strcmp(choose2, "5") || !strcmp(choose2, "6") || !strcmp(choose2, "7")))
		{
			continue;
		}
		strcpy(choose3, choose2);
		for (b = 0; choose3[b] != NULL; b++)
		{
			choose1 = choose3[b] - '0';
		}
		switch (choose1)
		{
		case 1: /*Viewing the room*/
			if (!strcmp(student1.gender, "male"))
			{
				fptra1 = fopen("A1.txt", "r");
				printf("SINGLE BED\n");
				for (b = 0; b < 100; b++)
				{
					fscanf(fptra1, "%d", &a1[b]);
				}
				fclose(fptra1);
				view(a1);
				fptra3 = fopen("A3.txt", "r");
				printf("TRIPLE BED\n");
				for (b = 0; b < 100; b++)
				{
					fscanf(fptra3, "%d", &a3[b]);
				}
				fclose(fptra3);
				view(a3);
			}
			else if (!strcmp(student1.gender, "female"))
			{
				fptrb1 = fopen("B1.txt", "r");
				printf("SINGLE BED\n");
				for (b = 0; b < 100; b++)
				{
					fscanf(fptrb1, "%d", &b1[b]);
				}
				fclose(fptrb1);
				view(b1);
				fptrb2 = fopen("B2.txt", "r");
				printf("DOUBLE BED\n");
				for (b = 0; b < 100; b++)
				{
					fscanf(fptrb2, "%d", &b2[b]);
				}
				fclose(fptrb2);
				view(b2);
			}
			printf("Please enter anything to go back to main menu: ");
			scanf("%s", skip);
			break;
		case 2: /*Booking the room*/
			fptrr = fopen(tempoTP, "r");
			count = 0;
			while (!feof(fptrr))
			{
				fscanf(fptrr, "%s", line);
				count++;
			}
			fclose(fptrr);
			if (count > 4)
			{
				printf("Sorry, you already booked a room in the hostel so you can not proceed further.\nPress anything to go back to main menu: ");
				scanf("%s", skip);
				break;
			}
			if (!strcmp(student1.gender, "male"))
			{
				printf("How long would you like to stay (in week): ");
				scanf("%d", &week);
				printf("1. A1(Single Bed) RM 400\n2. A3(Triple Bed) RM 150\nPlease Choose your desired block(A1/A3): ");
				scanf("%s", &student1.block);
				strcpy(student1.block, strupr(student1.block));
				if (!strcmp(student1.block, "A1"))
				{
					fptra1 = fopen("A1.txt", "r");
					printf("SINGLE BED\n");
					for (b = 0; b < 100; b++)
					{
						fscanf(fptra1, "%d", &a1[b]);
					}
					fclose(fptra1);
					view(a1);
					limit = 1;
					room1 = booking("A1.txt", a1, limit);
					strcpy(rooom, room1);
					while (1)
					{
						printf("Would you like to subscribe to the internet services for RM 40?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							internet = 40;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					while (1)
					{
						printf("Would you like to subscribe to the gym services for RM 10?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							gym = 10;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					student1.outstanding = payment(400, week, internet, gym);
					fptra = fopen(tempoTP, "a");
					fprintf(fptra, "\nA1\n");
					fprintf(fptra, "%s\n", rooom);
					fprintf(fptra, "%d\n", week);
					fprintf(fptra, "%d\n", student1.outstanding);
					fprintf(fptra, "%s", ctime(&currentTime));
					fclose(fptra);
				}
				else if (!strcmp(student1.block, "A3"))
				{
					fptra3 = fopen("A3.txt", "r");
					printf("TRIPLE BED\n");
					for (b = 0; b < 100; b++)
					{
						fscanf(fptra3, "%d", &a3[b]);
					}
					fclose(fptra3);
					view(a3);
					limit = 3;
					room1 = booking("A3.txt", a3, limit);
					strcpy(rooom, room1);
					while (1)
					{
						printf("Would you like to subscribe to the internet services for RM 15?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							internet = 15;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					while (1)
					{
						printf("Would you like to subscribe to the gym services for RM 10?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							gym = 10;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					student1.outstanding = payment(150, week, internet, gym);
					fptra = fopen(tempoTP, "a");
					fprintf(fptra, "\nA3\n");
					fprintf(fptra, "%s\n", rooom);
					fprintf(fptra, "%d\n", week);
					fprintf(fptra, "%d\n", student1.outstanding);
					fprintf(fptra, "%s", ctime(&currentTime));
					fclose(fptra);
				}
			}
			else if (!strcmp(student1.gender, "female"))
			{
				printf("How long would you like to stay (in week): ");
				scanf("%d", &week);
				printf("1. B1(Single Bed) RM 400\n2. B2(Double Bed) RM 200\nPlease Choose your desired block (B1/B2): ");
				scanf("%s", &student1.block);
				strcpy(student1.block, strupr(student1.block));
				if (!strcmp(student1.block, "B1"))
				{
					fptrb1 = fopen("B1.txt", "r");
					printf("SINGLE BED\n");
					for (b = 0; b < 100; b++)
					{
						fscanf(fptrb1, "%d", &b1[b]);
					}
					fclose(fptrb1);
					view(b1);
					limit = 1;
					room1 = booking("B1.txt", b1, limit);
					strcpy(rooom, room1);
					while (1)
					{
						printf("Would you like to subscribe to the internet services for RM 40?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							internet = 40;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					while (1)
					{
						printf("Would you like to subscribe to the gym services for RM 10?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							gym = 10;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					student1.outstanding = payment(400, week, internet, gym);
					fptra = fopen(tempoTP, "a");
					fprintf(fptra, "\nB1\n");
					fprintf(fptra, "%s\n", rooom);
					fprintf(fptra, "%d\n", week);
					fprintf(fptra, "%d\n", student1.outstanding);
					fprintf(fptra, "%s", ctime(&currentTime));
					fclose(fptra);
				}
				else if (!strcmp(student1.block, "B2"))
				{
					fptrb2 = fopen("B2.txt", "r");
					printf("DOUBLE BED\n");
					for (b = 0; b < 100; b++)
					{
						fscanf(fptrb2, "%d", &b2[b]);
					}
					fclose(fptrb2);
					view(b2);
					limit = 2;
					room1 = booking("B2.txt", b2, limit);
					strcpy(rooom, room1);
					while (1)
					{
						printf("Would you like to subscribe to the internet services for RM 20?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							internet = 20;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					while (1)
					{
						printf("Would you like to subscribe to the gym services for RM 10?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							gym = 10;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					student1.outstanding = payment(200, week, internet, gym);
					fptra = fopen(tempoTP, "a");
					fprintf(fptra, "\nB2\n");
					fprintf(fptra, "%s\n", rooom);
					fprintf(fptra, "%d\n", week);
					fprintf(fptra, "%d\n", student1.outstanding);
					fprintf(fptra, "%s", ctime(&currentTime));
					fclose(fptra);
				}
			}
			printf("Please enter anything to go back to main menu: ");
			scanf("%s", skip);
			break;
		case 3: /*Displaying the hosteler information*/
			fptrr = fopen(tempoTP, "r");
			count = 0;
			while (!feof(fptrr))
			{
				fscanf(fptrr, "%s", line);
				count++;
			}
			fclose(fptrr);
			if (count <= 4)
			{
				printf("You are not registered yet, please register as the hosteler first.\nPress anything to go back to main menu: ");
				scanf("%s", skip);
				break;
			}
			fptrr = fopen(tempoTP, "r");
			fscanf(fptrr, "%s", student1.FirstName);
			fscanf(fptrr, "%s", student1.LastName);
			fscanf(fptrr, "%s", student1.gender);
			fscanf(fptrr, "%s", student1.TP);
			fscanf(fptrr, "%s", student1.block);
			fscanf(fptrr, "%s", student1.room);
			fscanf(fptrr, "%d", &student1.week);
			fscanf(fptrr, "%d", &student1.outstanding);
			fscanf(fptrr, "%s %s %s %s %s", student1.bookDay, student1.bookMonth, student1.bookDate, student1.bookTime, student1.bookYear);
			printf("Hosteler First Name : %s\nHosteler Last Name  : %s\nHosteler Gender     : %s\nHosteler TPNumber   : %s\nHosteler Block      : %s\nHosteler Room       : %s\nHosteler week stay  : %d\nHosteler Outstanding: %d\nHosteler Book Time  : %s %s %s %s %s\n", student1.FirstName, student1.LastName, student1.gender, student1.TP, student1.block, student1.room, student1.week, student1.outstanding, student1.bookTime, student1.bookDay, student1.bookDate, student1.bookMonth, student1.bookYear);
			fclose(fptrr);
			printf("Please enter anything to go back to main menu: ");
			scanf("%s", skip);
			break;
		case 4: /*To enter the amount the hosteler would like to pay*/
			fptrr = fopen(tempoTP, "r");
			count = 0;
			while (!feof(fptrr))
			{
				fscanf(fptrr, "%s", line);
				count++;
			}
			fclose(fptrr);
			if (count <= 4)
			{
				printf("You are not registered yet, please register as the hosteler first.\nPress anything to go back to main menu: ");
				scanf("%s", skip);
				break;
			}
			paymentFacility(tempoTP);
			printf("Please enter anything to go back to main menu: ");
			scanf("%s", skip);
			break;
		case 5: /*Used for hosteler cancellation*/
			fptrr = fopen(tempoTP, "r");
			count = 0;
			while (!feof(fptrr))
			{
				fscanf(fptrr, "%s", line);
				count++;
			}
			fclose(fptrr);
			if (count <= 4)
			{
				printf("You are not registered yet, please register as the hosteler first.\nPress anything to go back to main menu: ");
				scanf("%s", skip);
				break;
			}
			fptrr = fopen(tempoTP, "r");
			for (count = 0; count < 9; count++)
			{
				fscanf(fptrr, "%s", line);
				if (count == 4)
				{
					strcpy(currentBlock, line);
				}
				else if (count == 5)
				{
					strcpy(currentRoom, line);
				}
			}
			fclose(fptrr);
			remove(tempoTP);
			strcat(currentBlock, ".txt");
			fptra1 = fopen(currentBlock, "r");
			for (b = 0; b < 100; b++)
			{
				fscanf(fptra1, "%d", &a1[b]);
			}
			fclose(fptra1);
			deleteRoom(currentBlock, a1, currentRoom);
			printf("The cancellation has been carried out.\nThe linked information on the hosteler has been successfully removed.\n");
			printf("Please enter anything to go back to the register menu: ");
			scanf("%s", skip);
			system("cls");
			main();
			break;
		case 6: /*Used for hosteler that would like to change their room*/
			fptrr = fopen(tempoTP, "r");
			count = 0;
			while (!feof(fptrr))
			{
				fscanf(fptrr, "%s", line);
				count++;
			}
			fclose(fptrr);
			if (count <= 4)
			{
				printf("You are not registered yet, please register as the hosteler first.\nPress anything to go back to main menu: ");
				scanf("%s", skip);
				break;
			}
			fptrr = fopen(tempoTP, "r");
			for (count = 0; count < 9; count++)
			{
				fscanf(fptrr, "%s", line);
				if (count == 4)
				{
					strcpy(currentBlock, line);
				}
				else if (count == 2)
				{
					strcpy(student1.gender, line);
				}
				else if (count == 5)
				{
					strcpy(currentRoom, line);
				}
				else if (count == 6)
				{
					strcpy(week1, line);
				}
			}
			fclose(fptrr);
			strcat(currentBlock, ".txt");
			fptra1 = fopen(currentBlock, "r");
			for (b = 0; b < 100; b++)
			{
				fscanf(fptra1, "%d", &a1[b]);
			}
			fclose(fptra1);
			deleteRoom(currentBlock, a1, currentRoom);
			if (!strcmp(student1.gender, "male"))
			{
				printf("How long would you like to stay (in week): ");
				scanf("%d", &week);
				printf("1. A1(Single Bed) RM 400\n2. A3(Triple Bed) RM 150\nPlease Choose your desired block(A1/A3): ");
				scanf("%s", &student1.block);
				strcpy(student1.block, strupr(student1.block));
				if (!strcmp(student1.block, "A1"))
				{
					fptra1 = fopen("A1.txt", "r");
					printf("SINGLE BED\n");
					for (b = 0; b < 100; b++)
					{
						fscanf(fptra1, "%d", &a1[b]);
					}
					fclose(fptra1);
					view(a1);
					limit = 1;
					room1 = booking("A1.txt", a1, limit);
					strcpy(rooom, room1);
					while (1)
					{
						printf("Would you like to subscribe to the internet services for RM 40?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							internet = 40;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					while (1)
					{
						printf("Would you like to subscribe to the gym services for RM 10?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							gym = 10;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					student1.outstanding = payment(400, week, internet, gym);
					fptrw = fopen(tempoTP, "w");
					fprintf(fptrw, "%s\n", student1.FirstName);
					fprintf(fptrw, "%s\n", student1.LastName);
					fprintf(fptrw, "%s\n", student1.gender);
					fprintf(fptrw, "%s", student1.TP);
					fprintf(fptrw, "\nA1\n");
					fprintf(fptrw, "%s\n", rooom);
					fprintf(fptrw, "%d\n", week);
					fprintf(fptrw, "%d\n", student1.outstanding);
					fprintf(fptrw, "%s", ctime(&currentTime));
					fclose(fptrw);
				}
				else if (!strcmp(student1.block, "A3"))
				{
					fptra3 = fopen("A3.txt", "r");
					printf("TRIPLE BED\n");
					for (b = 0; b < 100; b++)
					{
						fscanf(fptra3, "%d", &a3[b]);
					}
					fclose(fptra3);
					view(a3);
					limit = 3;
					room1 = booking("A3.txt", a3, limit);
					strcpy(rooom, room1);
					while (1)
					{
						printf("Would you like to subscribe to the internet services for RM 15?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							internet = 15;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					while (1)
					{
						printf("Would you like to subscribe to the gym services for RM 10?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							gym = 10;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					student1.outstanding = payment(150, week, internet, gym);
					fptrw = fopen(tempoTP, "w");
					fprintf(fptrw, "%s\n", student1.FirstName);
					fprintf(fptrw, "%s\n", student1.LastName);
					fprintf(fptrw, "%s\n", student1.gender);
					fprintf(fptrw, "%s", student1.TP);
					fprintf(fptrw, "\nA3\n");
					fprintf(fptrw, "%s\n", rooom);
					fprintf(fptrw, "%d\n", week);
					fprintf(fptrw, "%d\n", student1.outstanding);
					fprintf(fptrw, "%s", ctime(&currentTime));
					fclose(fptrw);
				}
			}
			else if (!strcmp(student1.gender, "female"))
			{
				printf("How long would you like to stay (in week): ");
				scanf("%d", &week);
				printf("1. B1(Single Bed) RM 400\n2. B2(Double Bed) RM 200\nPlease Choose your block (B1/B2): ");
				scanf("%s", &student1.block);
				strcpy(student1.block, strupr(student1.block));
				if (!strcmp(student1.block, "B1"))
				{
					fptrb1 = fopen("B1.txt", "r");
					printf("SINGLE BED\n");
					for (b = 0; b < 100; b++)
					{
						fscanf(fptrb1, "%d", &b1[b]);
					}
					fclose(fptrb1);
					view(b1);
					limit = 1;
					room1 = booking("B1.txt", b1, limit);
					strcpy(rooom, room1);
					while (1)
					{
						printf("Would you like to subscribe to the internet services for RM 40?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							internet = 40;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					while (1)
					{
						printf("Would you like to subscribe to the gym services for RM 10?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							gym = 10;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					student1.outstanding = payment(400, week, internet, gym);
					fptrw = fopen(tempoTP, "w");
					fprintf(fptrw, "%s\n", student1.FirstName);
					fprintf(fptrw, "%s\n", student1.LastName);
					fprintf(fptrw, "%s\n", student1.gender);
					fprintf(fptrw, "%s", student1.TP);
					fprintf(fptrw, "\nB1\n");
					fprintf(fptrw, "%s\n", rooom);
					fprintf(fptrw, "%d\n", week);
					fprintf(fptrw, "%d\n", student1.outstanding);
					fprintf(fptrw, "%s", ctime(&currentTime));
					fclose(fptrw);
				}
				else if (!strcmp(student1.block, "B2"))
				{
					fptrb2 = fopen("B2.txt", "r");
					printf("DOUBLE BED\n");
					for (b = 0; b < 100; b++)
					{
						fscanf(fptrb2, "%d", &b2[b]);
					}
					fclose(fptrb2);
					view(b2);
					limit = 2;
					room1 = booking("B2.txt", b2, limit);
					strcpy(rooom, room1);
					while (1)
					{
						printf("Would you like to subscribe to the internet services for RM 20?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							internet = 20;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					while (1)
					{
						printf("Would you like to subscribe to the gym services for RM 10?\n1. YES\n2. NO\nEnter your choice (1 or 2): ");
						scanf("%d", &choose1);
						if (choose1 == 1)
						{
							gym = 10;
							break;
						}
						else if (choose1 == 2)
						{
							break;
						}
						else
							continue;
					}
					student1.outstanding = payment(200, week, internet, gym);
					fptrw = fopen(tempoTP, "w");
					fprintf(fptrw, "%s\n", student1.FirstName);
					fprintf(fptrw, "%s\n", student1.LastName);
					fprintf(fptrw, "%s\n", student1.gender);
					fprintf(fptrw, "%s", student1.TP);
					fprintf(fptrw, "\nB2\n");
					fprintf(fptrw, "%s\n", rooom);
					fprintf(fptrw, "%d\n", week);
					fprintf(fptrw, "%d\n", student1.outstanding);
					fprintf(fptrw, "%s", ctime(&currentTime));
					fclose(fptrw);
				}
			}
			printf("Please enter anything to go back to main menu: ");
			scanf("%s", skip);
			break;
		case 7:
			exit(0);
		default:
			continue;
		}
	}
	return 0;
}

int view(int block[100])
{
	int b, c = 1;
	for (b = 0; b < 100; b++)
	{
		if (b < 9)
		{
			printf("B00%d(%d)   *   ", b + 1, block[b]);
		}
		else if (b < 99)
		{
			printf("B0%d(%d)   *   ", b + 1, block[b]);
		}
		else
		{
			printf("B%d(%d)   *   ", b + 1, block[b]);
		}
		if (c == 5 || c == 10 || c == 15 || c == 20 || c == 25 || c == 30 || c == 35 || c == 40 || c == 45 || c == 50 || c == 55 || c == 60 || c == 65 || c == 70 || c == 75 || c == 80 || c == 85 || c == 90 || c == 95 || c == 100)
		{
			printf("\n");
		}
		c++;
	}
	return 0;
}

int deleteRoom(char text[7], int hostel[100], char room[100])
{
	int b, num1, num2, num3, number;
	FILE *fptrw;
	num1 = room[1] - '0';
	num2 = room[2] - '0';
	num3 = room[3] - '0';
	number = num1 * 100 + num2 * 10 + num3;
	hostel[number - 1] = hostel[number - 1] - 1;
	fptrw = fopen(text, "w");
	for (b = 0; b < 100; b++)
	{
		fprintf(fptrw, "%d", hostel[b]);
		if (b < 99)
		{
			fprintf(fptrw, "\n");
		}
	}
	fclose(fptrw);
	return 0;
}

char *booking(char text[7], int hostel[100], int limit)
{
	char room[1000];
	int b, num1, num2, num3, number;
	FILE *fptrw;
	while (1)
	{
		printf("Please enter the desired room number: ");
		scanf("%s", room);
		strcpy(room, strupr(room));
		if (room[4] != NULL)
		{
			continue;
		}
		else
		{
			num1 = room[1] - '0';
			num2 = room[2] - '0';
			num3 = room[3] - '0';
			number = num1 * 100 + num2 * 10 + num3;
			if (number >= 1 && number <= 100)
			{
				if (hostel[number - 1] < limit)
				{
					hostel[number - 1] = hostel[number - 1] + 1;
					fptrw = fopen(text, "w");
					for (b = 0; b < 100; b++)
					{
						fprintf(fptrw, "%d", hostel[b]);
						if (b < 99)
						{
							fprintf(fptrw, "\n");
						}
					}
					fclose(fptrw);
					printf("your book has completely been record.\n");
					break;
				}
				else if (hostel[number - 1] == limit)
				{
					printf("The room has already been booked please book another room.\n");
					continue;
				}
			}
		}
	}
	
	return room;
}

int payment(int roomRate, int week, int internet, int gym)
{
	int outstanding;
	outstanding = week * (roomRate + internet + gym);
	return outstanding;
}
int paymentFacility(char tpNumber[15])
{
	FILE *fptrr, *fptrw, *fptra;
	fptrr = fopen(tpNumber, "r");
	char line[256], ch[1000], money[100];
	int receive, temp = 0, a, i = 0, n = 0;
	struct student student1;
	for (i = 0; i < 9; i++)
	{
		fscanf(fptrr, "%s", line);
		if (i == 7)
		{
			strcpy(money, line);
			for (a = 0; money[a] != NULL; a++)
			{
				n = n * 10 + money[a] - '0';
			}
			fclose(fptrr);
			printf("Please enter the amount you want to pay: ");
			scanf("%d", &receive);
			printf("The amount pay for the accommodation is RM %d\n", receive);
			receive = n - receive;
			printf("The outstanding has been updated to RM %d\n", receive);
			fptrr = fopen(tpNumber, "r");
			fscanf(fptrr, "%s", student1.FirstName);
			fscanf(fptrr, "%s", student1.LastName);
			fscanf(fptrr, "%s", student1.gender);
			fscanf(fptrr, "%s", student1.TP);
			fscanf(fptrr, "%s", student1.block);
			fscanf(fptrr, "%s", student1.room);
			fscanf(fptrr, "%d", &student1.week);
			fscanf(fptrr, "%d", &student1.outstanding);
			fscanf(fptrr, "%s %s %s %s %s", student1.bookDay, student1.bookMonth, student1.bookDate, student1.bookTime, student1.bookYear);
			fclose(fptrr);
			fptrw = fopen(tpNumber, "w");
			fprintf(fptrw,"%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n%s %s %s %s %s", student1.FirstName, student1.LastName, student1.gender, student1.TP, student1.block, student1.room, student1.week, receive, student1.bookDay, student1.bookMonth, student1.bookDate, student1.bookTime, student1.bookYear);
			fclose(fptrw);
		}
	}
	return 0;
}

