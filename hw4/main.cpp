#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/if_arp.h>
#include <map>


using namespace std;

map<string, int> if_index;
map<int, unsigned char[7]> if_mac;

void list_ifs(struct ifaddrs *ifs);
void listen_ifs();

int main() {
    struct ifaddrs *ifs;
    char *name;
    int pid;
    getifaddrs(&ifs);
    list_ifs(ifs);
    printf("Enter your name: ");
    scanf("%ms", &name);
    printf("Welcome, '%s'!\n", name);
    if((pid = fork()) == 0) {
        listen_ifs();
    }

    while(1) {
        char *msg = NULL;
        printf(">>> ");
        scanf(" %m[^\n]s", &msg);
        if(msg && pid) {
            for(map<int, unsigned char[7]>::iterator it = if_mac.begin(); it != if_mac.end(); ++it) {
                struct sockaddr_ll addr = {0};
                char buf[8192] = {0};
                int packet_socket = socket(PF_PACKET, SOCK_RAW, htons(0x0801)), addr_len;
                addr_len = sizeof(sockaddr_ll);
                addr.sll_family = AF_PACKET;
                addr.sll_protocol = htons(0x0801);
                addr.sll_ifindex = it->first;
                addr.sll_halen = ETH_ALEN;
                snprintf(buf, sizeof(buf), "\xff\xff\xff\xff\xff\xff%c%c%c%c%c%c\x08\x01[%s]: %s", 
                        it->second[0], it->second[1], it->second[2], it->second[3], it->second[4], it->second[5], name, msg);
                sendto(packet_socket, buf, strlen(buf+14) + 14, 0, (struct sockaddr *)&addr, addr_len);
                if(errno) perror("sendto");
            }
        }
    }
    return 0;
}

void list_ifs(struct ifaddrs *ifs) {
    printf("Enumerated network interfaces:\n");
    for(struct ifaddrs *i = ifs; i; i = i->ifa_next) {
        int f = i->ifa_addr->sa_family;
        if(f == AF_INET || f == AF_INET6) {
            if(strcmp(i->ifa_name, "lo") == 0) continue;
            char addr[INET6_ADDRSTRLEN], netmask[INET6_ADDRSTRLEN];
            int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
            if_index[i->ifa_name] = if_nametoindex(i->ifa_name);
            struct ifreq req;
            switch(f) {
                case AF_INET:
                    inet_ntop(f, &((struct sockaddr_in *)i->ifa_addr)->sin_addr, addr, INET6_ADDRSTRLEN);
                    inet_ntop(f, &((struct sockaddr_in *)i->ifa_netmask)->sin_addr, netmask, INET6_ADDRSTRLEN);
                    break;
                case AF_INET6:
                    inet_ntop(f, &((struct sockaddr_in6 *)i->ifa_addr)->sin6_addr, addr, INET6_ADDRSTRLEN);
                    inet_ntop(f, &((struct sockaddr_in6 *)i->ifa_netmask)->sin6_addr, netmask, INET6_ADDRSTRLEN);
                    break;
            }

            strcpy(req.ifr_name, i->ifa_name);
            ioctl(fd, SIOCGIFHWADDR, &req);
            for(int j = 0; j < 6; j++) if_mac[if_index[i->ifa_name]][j] = req.ifr_addr.sa_data[j];
            printf("%u -  %s\tIP %s\tNetmask %s\t", if_index[i->ifa_name], i->ifa_name, addr, netmask);
            printf("MAC %02X:%02X:%02X:%02X:%02X:%02X\n",
                    (unsigned char)req.ifr_addr.sa_data[0], (unsigned char)req.ifr_addr.sa_data[1], (unsigned char)req.ifr_addr.sa_data[2],
                    (unsigned char)req.ifr_addr.sa_data[3], (unsigned char)req.ifr_addr.sa_data[4], (unsigned char)req.ifr_addr.sa_data[5]);
            close(fd);
        }
    }
}

void listen_ifs() {
    int packet_socket = socket(PF_PACKET, SOCK_RAW, htons(0x0801));
    struct sockaddr_ll addr = { 0 };
    addr.sll_family = AF_PACKET;
    addr.sll_protocol = htons(0x0801);
    addr.sll_halen = ETH_ALEN;
    addr.sll_pkttype = PACKET_BROADCAST;
    while(1) {
        char buf[8192], *msg;
        unsigned char *sender;
        int data_size = 0, addr_len = 0;
        addr_len = sizeof(struct sockaddr_ll);
        data_size = recvfrom(packet_socket, buf, sizeof(buf), 0, (struct sockaddr *)&addr, (socklen_t *)&addr_len);
        if(data_size < 0) {
            perror("recvfrom");
            exit(errno);
        } else if (data_size > 0){
            sender = (unsigned char *)buf + 6;
            msg = buf + 14;
            printf("<%02X:%02X:%02X:%02X:%02X:%02X> %s\n",
                    sender[0], sender[1], sender[2], sender[3], sender[4], sender[5], msg);
        }
    }
    exit(0);
}
