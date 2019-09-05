gcc icmp_ping.c raw_socket.c checksum.c -o icmpping
sudo ./icmpping "$1" "$2" "$3"
