#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/select.h>

#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdbool.h>

#define	QLEN 5
#define	BUFSIZE	4096
#define NUMCHAR 2048
#define SMALLNUM 16
#define MAXQUES 256
#define MAXLINES 1024
#define GROUPNUMBER 32

//Add Struct winData
//Where int fd;
//      char *name
//      int score;
//In this struct, save names and scores of all Clients

struct passGroupNum {
    int strFd;
    int strGroupNum;
};

struct oneGroup {
    char *topic;
    char *groupName;
    int groupSize;
    int curr;
    
    char *allLines[MAXLINES];
    char *ans[MAXQUES];
    char *ques[MAXQUES];
    int howMany;

    int adminSsock;
    int allFd[MAXLINES];
    
    int iterat;
    int howToChoose;
    
    //Array Struct of winData for clients
    //struct winData data[GROUPNUMBER]
};
struct oneGroup allGroups[GROUPNUMBER];

int groupNum = 0, fileIterator = 0, childNum = 0;
fd_set afds;

int nClients = 0;
//int checker[GROUPNUMBER];

pthread_mutex_t firstMutex;
pthread_mutex_t secMutex;
pthread_mutex_t thirdMutex;
pthread_mutex_t forthMutex;
pthread_mutex_t fifthMutex;
pthread_mutex_t sixMutex;
pthread_mutex_t seventhMutex;
pthread_mutex_t eightMutex;
pthread_mutex_t nineMutex;

void *groupFunction(void *ptr){

    struct passGroupNum* passValues = (struct passGroupNum*) ptr;

    int	fd = passValues->strFd, thisGroup = passValues->strGroupNum;
    char buf[BUFSIZE], *rgv[SMALLNUM], *token, *rest, fileName[SMALLNUM];
    int cc, increm = 0;
    
    write(fd, "SENDQUIZ", 8);
    write(fd, "\r\n", 2);    
    
    cc = read(fd, buf, BUFSIZE);
	buf[cc] = '\0';
    
    rest = buf;
    while ((token = strtok_r(rest, "|", &rest))) {
        rgv[increm] = (char *) malloc(strlen(token)+1);
        strcpy(rgv[increm], token);
        increm++;
    }
    
    pthread_mutex_lock(&secMutex);
	fileIterator++;
	
	FILE *file;
    sprintf(fileName, "aidar%d.txt", fileIterator);
    file = fopen(fileName, "w");
    
    int realSize = 0;
    int quizSize = atoi(rgv[1]);
    
    if(rgv[2] != NULL) {
        realSize = strlen(rgv[2]);
    }
        
    int remSize = quizSize - realSize;
        
    while(remSize > 0) {
        cc = read(fd, buf, BUFSIZE);
        remSize -= cc;
        fprintf(file, "%s", buf);
    }
    fclose(file);
    pthread_mutex_unlock(&secMutex);   
    

    if(strcmp(rgv[0], "QUIZ") == 0) {
        pthread_mutex_lock(&thirdMutex);
        
        write(fd, "OK", 2);
        write(fd, "\r\n", 2);

        FILE *readFile;
        readFile = fopen(fileName, "r");

        int i = 0, j = 0, k = 0;
        int chAns = 0, question = 1;
        char line[NUMCHAR];
        
        while(fgets(line, NUMCHAR, readFile) != NULL){
            if(strcmp(line,"\n") != 0) {
                if(chAns == 0 && question == 1) {
                    allGroups[thisGroup].ques[k] = (char *) malloc(strlen(line));
                    strcpy(allGroups[thisGroup].ques[k], line);
                    k++;
                    
                    question = 0;  
                }
                if(chAns == 1){
                    allGroups[thisGroup].ans[j] = (char *) malloc(strlen(line));
                    strcpy(allGroups[thisGroup].ans[j], line);
                    j++;
                }
                allGroups[thisGroup].allLines[i] = (char *) malloc(strlen(line));
                strcpy(allGroups[thisGroup].allLines[i], line);
                allGroups[thisGroup].howMany++;
                i++;            
            } else {
                if(chAns == 0){
                    chAns = 1;
                    question = 1;
                }
                else {
                    chAns = 0;
                }
            }
        }

        fclose(readFile); 
    } else {
        write(fd, "BAD", 3);
        write(fd, "\r\n", 2);
    }

    FD_SET(fd, &afds);
    pthread_mutex_unlock(&thirdMutex);
}

void *childFunction(void *ptr){
    
    int	groupIdentity = (int) ptr;
    //struct timeval tim;
    
    int size = allGroups[groupIdentity].groupSize;
    int maxfd, i, result, cc;
    int points = 0;
    char buf[BUFSIZE];
    
    fd_set readset;
    FD_ZERO(&readset);
    
    maxfd = 0; 
    for(i = 0; i < size; i++) {
        FD_SET(allGroups[groupIdentity].allFd[i], &readset);
        if(allGroups[groupIdentity].allFd[i] > maxfd) {
            maxfd = allGroups[groupIdentity].allFd[i];
        }
    }
    
printf("Before: %s", allGroups[groupIdentity].ques[0]);
    int u = 0, k = 0, h = 0;
    while(allGroups[groupIdentity].ques[u] != NULL) {
        for(k = 0; k < size; k++) {
            write(allGroups[groupIdentity].allFd[k], "QUES|", 5);
printf("QUES: %s", allGroups[groupIdentity].ques[u]); 
			char si[SMALLNUM]; 			
			sprintf(si, "%i", strlen(allGroups[groupIdentity].ques[u]));				
			write(allGroups[groupIdentity].allFd[k], si, strlen(si)-1);
			write(allGroups[groupIdentity].allFd[k], "|", 1);
			
			for(; h < allGroups[groupIdentity].howMany; h++) {
printf("H: %i   ", h);
				if(strcmp(allGroups[groupIdentity].allLines[h], allGroups[groupIdentity].ans[u]) == 0){				
//Break here does not work because it can't identify that allGroups[groupIdentity].allLines[h] and allGroups[groupIdentity].ans[u] are equal at some step
					break;
				} else {			
					write(allGroups[groupIdentity].allFd[k], allGroups[groupIdentity].allLines[h], strlen(allGroups[groupIdentity].allLines[h]));					
					write(allGroups[groupIdentity].allFd[k], "\n", 1);		
printf("Sub: %s", allGroups[groupIdentity].allLines[h]);	
				}
			}
			h++;
        }
        
/*
        tim.tv_sec = 60
		while(nClients < size) {
		    result = select(maxfd+1, &readset, (fd_set *)0, (fd_set *)0, &tim); 
            if(result == -1) {
                fprintf(stderr, "server select: %s\n", strerror(errno));
//LEAVE
		        exit(-1);		
            } else {
                for(int j = 0; j < size; j++) {
                    if (FD_ISSET(allGroups[groupIdentity].allFd[j], &readset)) {                   
                        cc = read(allGroups[groupIdentity].allFd[j], buf, BUFSIZE);
                        
                        buf[cc] = '\0';
                        buf[strcspn(buf, "\n")]= 0;
						buf[strcspn(buf, "\r")]= 0;
						
						token = strtok(buf, "|");
	                    token = strtok(NULL, "|");
	                    
                        if(strcmp(token, "NOANS") == 0) {
                            points += 0;
                            //allGroups[groupIdentity].data[particClient].score = points;
                        }
                        else if(strcmp(token, ans[u]) == 0) {
                            pthread_mutex_lock(&usa);
                            checker[groupIdentity]++;
                            pthread_mutex_unlock(&usa);
                                               
                            if(checker[groupIdentity] == 1) {
                                points += 1;
                                //allGroups[groupIdentity].data[particClient].score = points;
                            }
                            
                            points += 1;
                            //allGroups[groupIdentity].data[particClient].score = points;
                        }
                        else if(strcmp(token, ans[u]) != 0) {
                            points -= 1;
                            //allGroups[groupIdentity].data[particClient].score = points;
                        } 
                    }         
                }
            }
		}
        
        int max = -99999;
        char *winner;
        for (int a = 0; a < size; a++) {
            if(allGroups[groupIdentity].data[a].score > max) {
                max = allGroups[groupIdentity].data[a].score;
                winner = (char *) malloc(strlen(allGroups[groupIdentity].data[a].name));
                strcpy(winner, allGroups[groupIdentity].data[a].name)
            }
        }
        
        for(int m = 0; m < size; m++) {
            write(allGroups[groupIdentity].allFd[m], "WIN|", 4);
            write(allGroups[groupIdentity].allFd[m], winner, strlen(winner));
            write(ssock, "\n", 1);
        }
    */
        u++;
    }

    /*
    for(int l = 0; l < size; l++) {
        write(allGroups[groupIdentity].allFd[l], "RESULT|", 7);
        int n = 0, k = 0;
        while(allGroups[groupIdentity].data[n].name != NULL && k != size) {
            write(allGroups[groupIdentity].allFd[l], allGroups[groupIdentity].data[n].name, strlen(allGroups[groupIdentity].data[n].name));
            write(allGroups[groupIdentity].allFd[l], "|", 1);
            write(allGroups[groupIdentity].allFd[l], allGroups[groupIdentity].data[n].score, strlen(allGroups[groupIdentity].data[n].score));
            write(allGroups[groupIdentity].allFd[l], "|", 1);
            n++;
        }
    }
    
    for(int s = 0; s < size; s++) {
        write(allGroups[groupIdentity].allFd[s], "ENDGROUP|", 9);
        write(allGroups[groupIdentity].allFd[s], allGroups[groupIdentity].groupName, strlen(allGroups[groupIdentity].groupName));
    }
    */

}

//Main starts
int passivesock(char *service, char *protocol, int qlen, int *rport);

int main(int argc, char *argv[])
{
	char buf[BUFSIZE];
	char *service;
	
	struct sockaddr_in	fsin;
	
	int	msock, ssock, rport = 0;
    int	alen, fd, nfds, cc, status, status2;
		
	fd_set rfds;
	
	//My fields
	pthread_mutex_init(&firstMutex, NULL);
	pthread_mutex_init(&secMutex, NULL);
    pthread_mutex_init(&thirdMutex, NULL);
    pthread_mutex_init(&forthMutex, NULL);
    pthread_mutex_init(&fifthMutex, NULL);
	pthread_mutex_init(&sixMutex, NULL);
    pthread_mutex_init(&seventhMutex, NULL);
    pthread_mutex_init(&eightMutex, NULL);
    pthread_mutex_init(&nineMutex, NULL);
	
	pthread_t tAdmin[GROUPNUMBER];
    pthread_t tJoin[GROUPNUMBER];
    

	switch (argc) 
	{
		case 1:
			rport = 1;
			break;
		case 2:
			service = argv[1];
			break;
		default:
			fprintf(stderr, "usage: server [port]\n");
			exit(-1);
	}

	msock = passivesock(service, "tcp", QLEN, &rport);
	if (rport)
	{
		//	Tell the user the selected port
		printf("Server: port %d\n", rport);	
		fflush(stdout);
	}

	
	// Set the max file descriptor being monitored
	nfds = msock+1;

	FD_ZERO(&afds);
	FD_SET(msock, &afds);
	for (;;)
	{
		// Reset the file descriptors you are interested in
		memcpy((char *)&rfds, (char *)&afds, sizeof(rfds));

		// Only waiting for sockets who are ready to read
		//  - this also includes the close event
		if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0,
				(struct timeval *)0) < 0)
		{
			fprintf(stderr, "server select: %s\n", strerror(errno));
			exit(-1);
		}

		// Since we've reached here it means one or more of our sockets has something
		// that is ready to read

		// The main socket is ready - it means a new client has arrived
		if (FD_ISSET(msock, &rfds)) 
		{
			int	ssock;

			// we can call accept with no fear of blocking
			alen = sizeof(fsin);
			ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
			if (ssock < 0)
			{
				fprintf(stderr, "accept: %s\n", strerror(errno));
				exit(-1);
			}

			/* start listening to this guy */
			FD_SET(ssock, &afds);
			
            write(ssock, "OPENGROUPS", 10);
            for(int i = 0; i < groupNum; i++) {
                if(allGroups[i].curr < allGroups[i].groupSize) {
                    write(ssock, "|", 1);
                    write(ssock, allGroups[i].topic, strlen(allGroups[i].topic));
                    
                    write(ssock, "|", 1);
                    write(ssock, allGroups[i].groupName, strlen(allGroups[i].groupName));
                    
                    write(ssock, "|", 1);
                    char si[SMALLNUM];
                    sprintf(si, "%i", allGroups[i].groupSize);
                    write(ssock, si, strlen(si));
                    
                    write(ssock, "|", 1);
                    char mi[SMALLNUM];
                    sprintf(mi, "%i", allGroups[i].curr);
                    write(ssock, mi, strlen(mi));    
                }
            }
            write(ssock, "\r\n", 2);

			// increase the maximum
			if (ssock+1 > nfds)
				nfds = ssock+1;
		}

		/*	Handle the participants requests  */
		for (fd = 0; fd < nfds; fd++)
		{		
			// check every socket to see if it's in the ready set
			if (fd != msock && FD_ISSET(fd, &rfds))
			{
				// read without blocking because data is there
				if ((cc = read(fd, buf, BUFSIZE)) <= 0)
				{
					printf("The client has gone.\n");
					(void) close(fd);
					FD_CLR(fd, &afds);
					// lower the max socket number if needed
					if (nfds == fd+1)
						nfds--;

				} else {				
				    buf[cc] = '\0';
                    
					char *rgv[SMALLNUM], *token, *rest;
					int increm = 0;
					
                    rest = buf;
                    while ((token = strtok_r(rest, "|", &rest))) {
                        rgv[increm] = (char *) malloc(strlen(token));
                        strcpy(rgv[increm], token);
		                increm++;
                    }

					if(strcmp(rgv[0], "GETOPENGROUPS") == 0) {
					
					    write(fd, "OPENGROUPS", 10);
                        for(int i = 0; i < groupNum; i++) {
                            if(allGroups[i].curr < allGroups[i].groupSize) {
                                write(fd, "|", 1);
                                write(fd, allGroups[i].topic, strlen(allGroups[i].topic));
                                
                                write(fd, "|", 1);
                                write(fd, allGroups[i].groupName, strlen(allGroups[i].groupName));
                                
                                write(fd, "|", 1);
                                char si[SMALLNUM];
                                sprintf(si, "%i", allGroups[i].groupSize);
                                write(fd, si, strlen(si));
                                
                                write(fd, "|", 1);
                                char mi[SMALLNUM];
                                sprintf(mi, "%i", allGroups[i].curr);
                                write(fd, mi, strlen(mi));          
                            }
                        }
                        write(ssock, "\r\n", 2);
					 
					} else if(strcmp(rgv[0], "GROUP") == 0) {
					
					    pthread_mutex_lock(&forthMutex);
					    int flag = 0;
					    for(int i = 0; i < groupNum; i++) {
					        if(strcmp(rgv[2], allGroups[i].groupName) == 0) {
					            write(fd, "BAD|The group name is not unique", 32);
					            write(fd, "\r\n", 2);
					            flag = 1;
					            break;
					        }
					    }
					    pthread_mutex_unlock(&forthMutex);
					    
					    if(flag == 0) {
					        pthread_mutex_lock(&firstMutex);
					        
					        allGroups[groupNum].topic = (char *) malloc(strlen(rgv[1]));
                            strcpy(allGroups[groupNum].topic, rgv[1]);
                            
                            allGroups[groupNum].groupName = (char *) malloc(strlen(rgv[2]));
                            strcpy(allGroups[groupNum].groupName, rgv[2]);
                            
                            allGroups[groupNum].groupSize = atoi(rgv[3]);
                            allGroups[groupNum].curr = 0;
                            allGroups[groupNum].iterat = 0;
                            allGroups[groupNum].howMany = 0;
                            allGroups[groupNum].adminSsock = fd;
                            allGroups[groupNum].howToChoose = groupNum;
                            
                            struct passGroupNum passValues;
                            passValues.strFd = fd;
                            passValues.strGroupNum = groupNum;
                            
                            FD_CLR(fd, &afds);
                            status = pthread_create(&tAdmin[groupNum], NULL, groupFunction, (void*) &passValues);
                            if (status != 0) {
			                    printf("Pthread_create error %d\n", status);
			                    exit(-1);
		                    }
                            
                            groupNum++;
                            pthread_mutex_unlock(&firstMutex);
					    }
					    
					} else if(strcmp(rgv[0], "JOIN") == 0) {

					    int flag2 = 0, flag3 = 0, takeGroupNum;
					    
					    pthread_mutex_lock(&fifthMutex);
					    for(int i = 0; i < groupNum; i++) {
					        if(strcmp(rgv[1], allGroups[i].groupName) == 0) {
					            if(allGroups[i].curr < allGroups[i].groupSize) {
					                flag2 = 1;
					                takeGroupNum = allGroups[i].howToChoose;
					            }
					            else {
					                flag3 = 1;
					                write(fd, "BAD|FULL", 8);
					                write(fd, "\r\n", 2);
					            }
					            break;
					        }
					    }

					    
					    if(flag2 == 1) {
					        write(fd, "OK", 2);
					        write(fd, "\r\n", 2);
					        
					        allGroups[takeGroupNum].curr++;
					        int currIter = allGroups[takeGroupNum].iterat;
					        allGroups[takeGroupNum].allFd[currIter] = fd;
					        allGroups[takeGroupNum].iterat++;
					        
					        //Also update winData
					        					        
					        if(allGroups[takeGroupNum].curr == allGroups[takeGroupNum].groupSize) {
					        
					            for(int k = 0; k < allGroups[takeGroupNum].groupSize; k++) {
					                FD_CLR(allGroups[takeGroupNum].allFd[k], &afds);
					            }
					        	        
					            status2 = pthread_create(&tJoin[childNum], NULL, childFunction, (void*) takeGroupNum);
                                if (status2 != 0) {
			                        printf("Pthread_create2 error %d\n", status2);
			                        exit(-1);
		                        }
		                        childNum++;
					        } 
					        
					    } else if(flag3 == 0) {
					        write(fd, "BAD|NOGROUP", 11);
					        write(fd, "\r\n", 2);
					    }
					    pthread_mutex_unlock(&fifthMutex);
					    
					}
				}
			}
		}
	}
	
	pthread_mutex_destroy(&firstMutex);
	pthread_mutex_destroy(&secMutex);
	pthread_mutex_destroy(&thirdMutex);
	pthread_mutex_destroy(&forthMutex);
	pthread_mutex_destroy(&fifthMutex);
	pthread_mutex_destroy(&sixMutex);
	pthread_mutex_destroy(&seventhMutex);
	pthread_mutex_destroy(&eightMutex);
	pthread_mutex_destroy(&nineMutex);	
	
	return 0;	
}
