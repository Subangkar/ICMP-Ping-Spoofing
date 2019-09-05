gcc icmp_ping.c raw_socket.c checksum.c -o icmpping
icmpping "$1" "$2"
