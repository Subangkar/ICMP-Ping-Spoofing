#include <pcap.h>
#include <stdio.h>
#include <arpa/inet.h>

#include <net/ethernet.h>
#include <arpa/inet.h>

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>


void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {

	int packet_length = header->len;
	struct ether_header *eth = (struct ether_header *) packet;

	if (ntohs(eth->ether_type) == ETHERTYPE_IP) {
		struct iphdr *ip = (struct iphdr *) (packet + sizeof(struct ether_header));
		if (ip->protocol == IPPROTO_ICMP) {
			struct icmphdr *icmp = (struct icmphdr *) (packet + sizeof(struct ether_header) + sizeof(struct iphdr));
			printf(" Protocol: ICMP\n");
			printf("     From: %s\n", inet_ntoa(*(struct in_addr *) &ip->saddr));
			printf("       To: %s\n", inet_ntoa(*(struct in_addr *) &ip->daddr));
			printf("     Type: ");

			if (icmp->type == ICMP_ECHO || icmp->type == ICMP_ECHOREPLY) {
				if (icmp->type == ICMP_ECHO) {
					printf("ping request\n");
				} else if (icmp->type == ICMP_ECHOREPLY) {
					printf("ping reply\n");
				}
				if (packet_length > (sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct icmphdr))) {
					printf("  Payload: ");
					puts((char *) packet + (sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct icmphdr)));
				}
			}
			printf("\n");
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Enter adapter name");
		return 0;
	}

	pcap_t *handle;
	char errbuf[PCAP_ERRBUF_SIZE];
	struct bpf_program fp;
	char filter_exp[] = "icmp";
	bpf_u_int32 net;

	// Step 1: Open live pcap session on NIC with given adapter
	handle = pcap_open_live(argv[1], BUFSIZ, 1, 1000, errbuf);

	// Step 2: Compile filter_exp into BPF psuedo-code
	pcap_compile(handle, &fp, filter_exp, 0, net);
	pcap_setfilter(handle, &fp);

	printf("Capturing ICMP Packets.....\n");
	// Step 3: Capture packets
	pcap_loop(handle, -1, got_packet, NULL);

	pcap_close(handle); //Close the handle
	return 0;
}
