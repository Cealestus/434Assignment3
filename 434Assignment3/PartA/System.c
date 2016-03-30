/*
 * System.c
 *
 *  Created on: Mar 27, 2016
 *      Author: meisl
 */

#include <pthread.h>
#include <stdio.h>

int x[11];
int y[11];
int K = 10;
int D = 1;

struct packet{
	char *myPacket;
};

struct packet *packets[11];

void *Sensor(void *SensorID){
	int ID;
	int i;
	int dir;
	int diff;
	char stringIdent[10];
	char *datapacket = malloc(sizeof(char) * (101));
	strcat(datapacket, "N");
	ID = (int)SensorID;
	sprintf(stringIdent, "%d", ID);
	strcat(datapacket, stringIdent);
	strcat(datapacket, " Hello");
	packets[ID] = malloc(sizeof(struct packet));
	packets[ID]->myPacket = malloc(sizeof(char) * (101));
	sprintf(packets[ID]->myPacket, "%s", datapacket);
	printf("%s\n", packets[ID]->myPacket);
	srand(ID);
	x[ID] = rand() % 1001;
	y[ID] = rand() % 1001;
	printf("Sensor %d activated, X: %d, Y: %d\n", ID, x[ID], y[ID]);
	for(i = 0; i < K; i++){
		dir = rand() % 4;
		if(dir == 0){
			/*Move north*/
			y[ID] = y[ID] + D;
			if(y[ID] > 1000){
				diff = 1000 - y[ID];
				y[ID] = 1000 + diff;
			}
		}else if(dir == 1){
			/*Move east*/
			x[ID] = x[ID] + D;
			if(x[ID] > 1000){
				diff = 1000 - x[ID];
				x[ID] = 1000 + diff;
			}
		}else if(dir == 2){
			/*Move south*/
			y[ID] = y[ID] - D;
			if(y[ID] < 0){
				y[ID] = 0 - y[ID];
			}
		}else if(dir == 3){
			/*Move west*/
			x[ID] = x[ID] - D;
			if(x[ID] < 0){
				x[ID] = 0 - x[ID];
			}
		}
		printf("Sensor %d, X: %d, Y: %d\n", ID, x[ID], y[ID]);
	}

	pthread_exit(NULL);
}

void *Hub(void *HubID){
	int ID;
	ID = (int)HubID;
	x[ID] = 500;
	y[ID] = 500;
	printf("Hub %d has been activated, X: %d, Y: %d\n", ID, x[ID], y[ID]);
	pthread_exit(NULL);
}

int main(int argc, char*argv[]){
	pthread_t threads[11];
	int rc;
	int i;

	if(argc != 3){
		printf("Use is K, D\n");
		return 0;
	}

	K = atoi(argv[1]);
	D = atoi(argv[2]);

	for(i = 1; i < 11; i++){
		rc = pthread_create(&threads[i], NULL, Sensor, (void *)i);
		if(rc){
			printf("ERROR happened in pthread creation, error code %d, sensor number %d\n", rc, i);
		}
	}
	rc = pthread_create(&threads[0], NULL, Hub, (void *)0);
	if(rc){
		printf("ERROR happened in hub creation, error code %d\n", rc);
	}
	for(i = 1; i < 11; i++){
		pthread_join(threads[i], NULL);
	}

	return 0;
}
