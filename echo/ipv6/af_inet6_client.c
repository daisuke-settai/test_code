#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP   "::1"
#define SERVER_PORT 10000
#define BUFLEN      512
#define IPLEN       32

int main ()
{
  int s, count, datalen;
  in_port_t port;
  struct sockaddr_in6 myskt, skt, res;
  char ip_addr[IPLEN];
  char buf[BUFLEN], sbuf[BUFLEN];
  socklen_t sktlen;

  if((s = socket(PF_INET6, SOCK_DGRAM, 0)) < 0){ 
    perror("socket open.");
    exit(1);
  }

  port = SERVER_PORT;
  strncpy(ip_addr, SERVER_IP, IPLEN - 1);
  memset(&skt, 0, sizeof skt);
  if(inet_pton(AF_INET6, ip_addr, &skt.sin6_addr) != 1){
    perror("inet_pton");
    exit(1);
  }
  skt.sin6_family = AF_INET6;
  skt.sin6_port = htons(port);
  sktlen = sizeof skt;
  
  while(1){
    fprintf(stdout, "send:");
    fgets(sbuf, BUFLEN, stdin);
    sbuf[strlen(sbuf) - 1] = '\0';
    if(strncmp(sbuf, "exit", BUFLEN) == 0){
      break;
    }
    datalen = strlen(sbuf) + 1;
    if((count = sendto(s, sbuf, datalen, 0, (struct sockaddr *)&skt, sizeof skt)) < 0) {
      perror("sendto");
      exit(1);
    }
    if((count = recvfrom(s, buf, sizeof buf, 0, (struct sockaddr *)&skt, &sktlen)) < 0) {
      perror("recvfrom");
      exit(1);
    }
    fprintf(stdout, "recv:%s\n", buf);
  }
  close(s);
  fprintf(stdout, "close socket\n");
  return 0;
}
