/* inetDaytime - Connecting to "daytime" datagram daemon in other host*/ 

#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <stdio.h> 

#define BUFSZ 256 
#define SERVICE "time" 

main(int argc, char **argv) 
{ 

 int s,n,len; 
 char buf[BUFSZ]; 

 struct hostent *hp; 
 struct servent *sp; 
 struct sockaddr_in sin; 

 if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
 /* acquire a socket */ 
  perror("socket"); 
  exit(1); 
 } 

 /* check the port number of the serverwork byte order */ 
 if ((sp = getservbyname(SERVICE, "udp")) == NULL) { 
  fprintf(stderr, "%s/udp: unknown service. \n", SERVICE); 
  exit(1); 
 } 

 while (--argc){ 

  if ((hp = gethostbyname(*++argv)) == NULL) { 
+   /* look for host network address */ 
   fprintf(stderr,"%s: host unknown.\n", *argv); 
   continue; 
  } 

  /* set server address on the remote host */ 
  sin.sin_family = AF_INET; 
  sin.sin_port = sp->s_port; 
  bcopy(hp->h_addr, &sin.sin_addr, hp->h_length); 

  printf("%s:\t", *argv); 
  fflush(stdout); 

  /* send a datagram to server*/ 
  if (sendto(s,buf,BUFSZ,0,&sin,sizeof(sin)) <0){ 
   perror("sendto"); 
   continue; 
  } 

  /* receive a datagram */ 
  len = sizeof(sin); 
  n = recvfrom(s, buf, sizeof(buf), 0, &sin, &len); 

  if (n<0) { 
   perror("recvfrom"); 
   continue; 
  } 

  buf[n] = '\0'; 
  printf("%s\n", buf); 
 } 

 close(s); 
 exit(0); 

} 
