//
// Created by Subangkar on 07-Aug-19.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "icmp_ping.h"


void send_raw_ip_packet(struct iphdr *ip) {
	struct sockaddr_in dest_info;
	int enable = 1;

	// Step 1: Create a raw network socket.
	int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

	if (sock < 0) PRINT_ERROR("Could Not create raw socket")

	// Step 2: Set socket option.
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &enable, sizeof(enable)) < 0) 
		PRINT_ERROR("Could Not set socket option");

	// Step 3: Provide needed information about destination.
	dest_info.sin_family = AF_INET;
	dest_info.sin_addr = *(struct in_addr *) &ip->daddr;

	// Step 4: Send the packet out.
	if (sendto(sock, ip, ntohs(ip->tot_len), 0, (struct sockaddr *) &dest_info, sizeof(dest_info)) < 0) 
		PRINT_ERROR("Could not send ip packet");
	close(sock);
}

