
/*******************************************************
 * Student: Nick Martin
 * ONID: martinn6
 * Date: 20160201
 * Project: #2 - Adventure
 * Description: 
 * *******************************************************/

#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct Rooms {
	char roomName[20];
	char roomType[20];
	int roomLevel; //store # of levels deep in tree.
	int connections[5];
	int connectionCount;
};

int main (void) {

	//Declare variables
	
	struct Rooms room[7];
	
	int file_descriptor;
	char *file = "test.txt";
	ssize_t nread;
	ssize_t nwritten;
	char buffer[512];
	const char *roomNames[9];
	roomNames[0] = "Kitchen";
	roomNames[1] = "Bathroom";
	roomNames[2] = "Arcade";
	roomNames[3] = "Pool Room";
	roomNames[4] = "Family Room";
	roomNames[5] = "Cinema";
	roomNames[6] = "Bedroom";
	roomNames[7] = "Master";
	roomNames[8] = "Garage";
	roomNames[9] = "Living Room";

	srand(time(NULL));

	//Assign random name to rooms
	int i = 0;
	int n = 0;
	int notfound = 0;
	int r = rand() % 9;
	while (i < 7)
	{
		r = rand() % 9;
		//printf("%i", r);
		n = 0;
		while (n < i)
		{
			//printf("\nTest: %i", notfound);
			//printf("\nname to give: %s", roomNames[r]);
			//printf("\ni=%i, room %i's name: %s",i, n, room[n].roomName);
			if(strcmp(room[n].roomName, roomNames[r])==0)
			{
				notfound = 1;
				n = i;
			}
			n++;
		}
		if(notfound == 0)	
		{
			strcpy(room[i].roomName, roomNames[r]);
			i++;
		}
		notfound = 0;
	}

	//Assign Room Types
	i = 0;
	while (i < 7)
	{
		if(i == 0)
			strcpy(room[i].roomType, "START_ROOM");
		else if (i == 6)
			strcpy(room[i].roomType, "END_ROOM");
		else
			strcpy(room[i].roomType, "MID_ROOM");
		i++;
	}


	//Create Connections


	//Set all connections to -1
	i=0;
	while (i < 7)
	{
		room[i].connectionCount=0;
		room[i].roomLevel=0;
		n=0;
		while (n < 6)
		{
			room[i].connections[n]=-1;
			n++;
		}
		i++;
	}

	i=0;
	int ranroom = -1;
	while (i < 7)
	{
		//generate a number between 3-6.
		r = rand() % 4 + 3;
		n=0;
		while (n < r)
		{
			//find empty room
			ranroom = rand() % 6; //rooms start to mid - leaving out end room
			printf("room=%i",ranroom);		
			if(room[ranroom].connectionCount < 6)
			{
				room[i].connections[n] = ranroom;
				room[i].connectionCount++;
				printf("room[i].connectionCount=%i",room[i].connectionCount);
				room[ranroom].connections[room[ranroom].connectionCount] = i;
				room[ranroom].connectionCount++;
				
				printf("r=%i",r);
				n++;
			}
		}
		i++;
	}

	
	//Create Connections
	i=0;
	while (i < 7)
	{
		n=0;
		while (n < 6)
		{
			printf("Room[%i].Connection[%i]=%i; Room[%i].connectionCount=%i\n",
				i,n,room[i].connections[n], i, room[i].connectionCount);
			n++;
		}
		i++;
	}
	

	//Open file (read & write)
	file_descriptor = open(file, O_RDWR);

	//If error, exit
	if (file_descriptor == -1)
	{
		printf("Error opening file. Cant continue.\n");
		exit(1);
	}
	nread = read(file_descriptor, buffer, 512);
	//nwritten = write(file_descriptor, buffer, nread);

	i = 0;
	while (i < 7)
	{
		printf("\nRoom[%i]'s name is %s.\n", i,  room[i].roomName);
		printf("Its room type is %s.", room[i].roomType);
		i++;
	}

	printf("\n\nEnd of Program.\n");
	printf("Have a nice day.\n");


	exit(0);
}


