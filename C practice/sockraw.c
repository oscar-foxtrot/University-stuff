#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <unistd.h>

// Pseudo header needed for TCP checksum calculation
struct pseudo_header {
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t tcp_length;
};

// IP header structure
struct ip_header {
    u_int8_t ip_hl:4, ip_v:4;
    u_int8_t ip_tos;
    u_int16_t ip_len;
    u_int16_t ip_id;
    u_int16_t ip_off;
    u_int8_t ip_ttl;
    u_int8_t ip_protocol;
    u_int16_t ip_checksum;
    u_int32_t ip_src, ip_dst;
};

// TCP header structure
struct tcp_header {
    u_int16_t th_sport;
    u_int16_t th_dport;
    u_int32_t th_seq;
    u_int32_t th_ack;
    u_int8_t th_lenres;
    u_int8_t th_flags;
    u_int16_t th_win;
    u_int16_t th_sum;
    u_int16_t th_urp;
};

int main() {
    int sockfd;
    struct sockaddr_in source, dest;
    unsigned char *buffer = (unsigned char *)malloc(65536); // buffer to store packet data

    // Create a raw socket
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Receive packets in a loop
    while (1) {
        socklen_t saddr_len = sizeof(source);
        int data_size = recvfrom(sockfd, buffer, 65536, 0, (struct sockaddr *)&source, &saddr_len);
        if (data_size < 0) {
            printf("Error in receiving data\n");
            return 1;
        }

        // Parse the IP header
        struct ip_header *ip_hdr = (struct ip_header *)(buffer);
        struct tcp_header *tcp_hdr = (struct tcp_header *)(buffer + (ip_hdr->ip_hl * 4)); // Skip IP header length

        // Print out basic info
        printf("\n\nPacket received\n");
        printf("IP Header\n");
        printf("   |-Source IP      : %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr->ip_src));
        printf("   |-Destination IP : %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr->ip_dst));

        printf("TCP Header\n");
        printf("   |-Source Port    : %u\n", ntohs(tcp_hdr->th_sport));
        printf("   |-Destination Port : %u\n", ntohs(tcp_hdr->th_dport));
        printf("   |-Sequence Number : %u\n", ntohl(tcp_hdr->th_seq));
        printf("   |-Acknowledgment Number : %u\n", ntohl(tcp_hdr->th_ack));
		fflush(stdout);
    }

    close(sockfd);
    return 0;
}
