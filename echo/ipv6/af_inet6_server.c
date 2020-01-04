#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 10000
#define BUFLEN      512

int main ()
{
  int s, count, datalen;
  in_port_t myport;
  struct sockaddr_in6 myskt, skt;
  char buf[BUFLEN], sbuf[BUFLEN];
  socklen_t sktlen;

  if((s = socket(PF_INET6, SOCK_DGRAM, 0)) < 0){
    perror("socket open.");
    exit(1);
  }

  myport = SERVER_PORT;
  memset(&myskt, 0, sizeof myskt);
  myskt.sin6_family = AF_INET6;
  myskt.sin6_port = htons(myport);
  myskt.sin6_addr = in6addr_any;
  if(bind(s, (struct sockaddr *)&myskt, sizeof myskt) < 0){
    perror("bind");
    exit(1);
  }
  sktlen = sizeof skt;
  
  while(1){
    if((count = recvfrom(s, buf, sizeof buf, 0, (struct sockaddr *)&skt, &sktlen)) < 0) {
      perror("recvfrom");
      exit(1);
    }
  
    fprintf(stdout, "recv:%s\n", buf);
      
    datalen = strlen(buf) + 1;
    strncpy(sbuf, buf, datalen);
     
    if((count = sendto(s, sbuf, datalen, 0, (struct sockaddr *)&skt, sizeof skt)) < 0) {
      perror("sendto");
      exit(1);
    }
    fprintf(stdout, "send:%s\n", sbuf);
  }

  close(s);
  return 0;
}
