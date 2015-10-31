#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/ioctl.h>

#define MAX_PACKET 256
#define DEFAULT_PORT 8888

void error( char * );
void usage( char * );
void client( char *, int );
void server( int );

void error( char *msg ) {
  perror( msg );
  exit( 0 );
}

void usage( char *prog_name ) {
  printf( "USAGE:\n" );
  printf( "server: %s [port]\n", prog_name );
  printf( "client: %s hostname port\n", prog_name );
}

int main( int argc, char *argv[] ) {
  switch ( argc ) {
  case 1:
    server( DEFAULT_PORT );
    break;
  case 2:
    server( atoi( argv[1] ) );
    break;
  case 3:
    client( argv[1], atoi( argv[2] ) );
    break;
  default:
    usage( argv[0] );
    break;
  }

  return 0;
}

void client( char *server, int test_port ) {
  int udp_socket;
  struct sockaddr_in destination;
  /*struct iphdr ip;
    struct udphdr udp;*/
  char buffer[ MAX_PACKET ];
  int true = 1;
  struct hostent *hp;
  int dest_size = sizeof( destination );

  memset( &destination, 0, sizeof( destination ) );

  destination.sin_family = AF_INET;
  destination.sin_port = test_port;

  hp = gethostbyname( server );
  memcpy( hp->h_addr, &destination.sin_addr, hp->h_length );

  printf( "Creating socket...\n" );
  udp_socket = socket( PF_INET, SOCK_DGRAM, IPPROTO_UDP );
  if ( udp_socket < 0 ) {
    error( "Could not create UDP socket" );
  }

  printf( "Binding to port %d...\n", test_port );
  if ( bind( udp_socket, &destination, sizeof( destination ) ) < 0 ) {
    error( "Could not bind" );
  }

  printf( "Connecting to %s...\n", server );
  if ( connect( udp_socket, &destination, sizeof( destination ) ) != 0 ) {
    error( "Could not connect to port" );
  }

  printf( "Entering Interactive mode...\n" );
  while ( !feof( stdin ) ) {
    fgets( buffer, MAX_PACKET, stdin );
    if ( sendto( udp_socket, buffer, MAX_PACKET, 0,
		 &destination, sizeof( destination )) == -1 ) {
      error( "Could not send" );
    }

    recvfrom( udp_socketm buffer, MAX_PACKET, 0, &destination, dest_size );

    printf( "%s\n", buffer );
  }
}

void server( int test_port ) {
  int udp_socket;
  struct sockaddr_in destination;
  fd_set set;
  int max_socket;
  struct timeval tv;
  char buffer[ MAX_PACKET + 1 ];
  int chars_read;
  int dest_size = sizeof( destination );
  int true = 1;

  memset( &destination, 0, sizeof( destination ) );

  destination.sin_family = AF_INET;
  destination.sin_port = htons (test_port);
  destination.sin_addr.s_addr = htonl( INADDR_ANY );
  /*destination.sin_addr.s_addr = INADDER_ANY; */

  printf( "Creating socket...\n" );
  udp_socket = socket( PF_INET, SOCK_DGRAM, IPPROTO_UDP );
  if ( udp_socket < 0 ) {
    error( "Could not create UDP socket" );
  }
  
  printf( "Binding to port %d...\n", test_port );
  if ( bind( udp_socket, &destination, sizeof( destination ) ) < 0 ) {
    error( "Could not bind" );
  }

  printf( "Connecting to scoket...\n" );
  if ( connect( udp_socket, &destination, sizeof( destination ) ) < 0 ) {
    error( "Could not bind to port" );
  }

  FD_ZERO( &set );
  FD_SET( udp_socket, &set );
  max_socket = udp_socket;

  memset( &tv, 0, sizeof( tv ) );
  tv.tv_sec = 10;
  tv.tv_usec = 0;

  printf( "Waiting for connections...\n" );
  while( 1 ) {
    /*
    if ( select( max_socket + 1, &set, NULL, NULL, (struct timeval *)NULL ) < 0 ) {
      error( "Select failed" );
    }
    */

    chars_read = recvfrom( udp_socket, buffer, MAX_PACKET, 0,
			   &destination, &dest_size ); 
    if ( chars_read == -1 ) {
      error( "Problem with recv" );
    }
    buffer[ chars_read ] = '\0';
    printf( "%s", buffer );
  }
}
