//////////////////////////////////////////////////////////
// Filename: DashboarReceiver.cpp
// Author:   
// Date:     January 23, 2011
//
// Description: This file contains class defintion for the DashBoardReceiver responible all dashboard data through 
// UDP Port 1130...
//
//////////////////////////////////////////////////////////
#include "DashboardReceiver.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


#define BUFLEN 512
#define PORT 1130


DashboardReceiver::DashboardReceiver()
{
	if ((hSocket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
	    printf("Socket Error\n");
	    return;
	}
	    
			    
	memset((char *) &si_me, 0, sizeof(si_me));
	
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(hSocket, (struct sockaddr *)&si_me, sizeof(si_me))==-1){
			printf("Binding Error\n");
		    return;
	}
}


DashboardReceiver::~DashboardReceiver()
{
	close(hSocket);	
}

void
DashboardReceiver::ReceiveData()
{	
		int slen=sizeof(si_other);
		char buf[BUFLEN];

	
		if (recvfrom(hSocket, buf, BUFLEN, 0, (struct sockaddr *)&si_other, &slen)==-1){
	          printf("recvfrom() Error\n");
	          return;
		}
	    printf("Received packet from %s:%d\nData: %s\n\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);
}
