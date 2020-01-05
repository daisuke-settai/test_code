#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/filter.h>
#include <netpacket/packet.h>
#include <net/if.h>

#define IF_NAME  "enp6s0f0"

#if defined PCAP            // use libpcap's bpf compiler
#include <pcap/pcap.h>
#include <pcap/bpf.h>
#elif defined TCPDUMP       // output result: "# tcpdump -dd arp"
struct sock_filter code[] = {
  { 0x28, 0, 0, 0x0000000c },
  { 0x15, 0, 1, 0x00000806 },
  { 0x6, 0, 0, 0x00040000 },
  { 0x6, 0, 0, 0x00000000 },
};
struct sock_fprog bpf = {
  .len = sizeof(code) / sizeof(code[0]),
  .filter = code
};
#else
struct sock_filter code[] = {
  BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 12),             // ldf[12]
  BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x806, 0, 1),  // jeq #0x806 jt 2 jf 3
  BPF_STMT(BPF_RET | BPF_K, -1),                      // ret #-1
  BPF_STMT(BPF_RET | BPF_K, 0)                        // ret #0
};
struct sock_fprog bpf = {
  .len = sizeof(code) / sizeof(code[0]),
  .filter = code
};
#endif


int main(){
  int sock;
  struct ifreq ifr;
  struct sockaddr_ll sll;
  unsigned char buf[4096];

  memset(&ifr, 0, sizeof(ifr));
  memset(&sll, 0, sizeof(sll));

  sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

  strncpy(ifr.ifr_name, IF_NAME, IFNAMSIZ);
  ioctl(sock, SIOCGIFINDEX, &ifr);

  sll.sll_family = AF_PACKET;
  sll.sll_protocol = htons(ETH_P_ALL);
  sll.sll_ifindex = ifr.ifr_ifindex;
  bind(sock, (struct sockaddr *)&sll, sizeof(sll));

#if defined PCAP
  struct bpf_program bpf;
  pcap_t *handle;
  handle = pcap_open_live(IF_NAME, 4096, 1, 1000, buf);
  if(handle == NULL){
    perror("pcap_open_live:");
    exit(1);
  }
  pcap_compile(handle, &bpf, "arp", 1, PCAP_NETMASK_UNKNOWN);
  setsockopt(sock, SOL_SOCKET, SO_ATTACH_FILTER, (struct sock_fprog *)&bpf, sizeof(bpf));
#else
  setsockopt(sock, SOL_SOCKET, SO_ATTACH_FILTER, &bpf, sizeof(bpf));
#endif

  while(-1){
    ssize_t len = recv(sock, buf, sizeof(buf), 0);
    struct ethhdr* ethhdr = (struct ethhdr *)buf;
    int proto = ntohs(ethhdr->h_proto);
    if(len <= 0){
      perror("recv:");
      break;
    }
    printf("%3ld %0x %s\n", len, proto, proto == ETH_P_ARP ? "arp": proto == ETH_P_IP ? "ip" : "other");
  }
  return 0;
}
