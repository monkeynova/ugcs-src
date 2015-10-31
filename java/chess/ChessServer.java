import java.net.*;
import java.io.*;

public class ChessServer implements Runnable, ServerSocketGrabber {
  private final int maxSocks = 256;
  private ServerSocket listner;
  private ConnectThread[] connections = new ConnectThread[ maxSocks ];
  private int[] games = new int[ maxSocks ];
  private String[] names = new String[ maxSocks ];
  private int numconnects = 0;
  private final String welcome = "Welcome To ChessWorld";
  private final String prmt ="Start by sending your name from the chat prompt";

  public ChessServer( int port ) {
    int i;

    for ( i = 0; i < maxSocks; i++ )
      games[i] = -1;

    try {
      listner = new ServerSocket( port, maxSocks );
    } catch( IOException e ) {
      fail( e, "Could not open server socket" );
    }
  }

  public static void fail( Exception e, String printer ) {
    System.err.println( printer + "\n" + e + "\n" );
    System.exit( 1 );
  }
    
  public void run( ) {
    try {
      while( true ) {
	Socket s = listner.accept();
	connections[ numconnects ] = new ConnectThread( s, this );
	connections[ numconnects ].SendText( "Chat: " + welcome );
	connections[ numconnects ].SendText( "Chat: " + prmt );

	numconnects++;
      } 
    } catch( IOException e ) {
      fail( e, "Listing loop failed!" );
    }
  }

  public void GrabText( Socket s, String str ) {
    int i;

    System.out.println( str );

    for ( i = 0; i < numconnects; i++ ) {
      if ( connections[i].isSameAs( s ) )
	break;
    }

    if ( i == numconnects ) {
      System.err.println( "Got a message from an unknown source!" );
    }
    
    if ( str.startsWith( "Chat: " ) ) {
      if ( names[i] != null ) {
	SendToAll( "Chat: " + names[i] + ": " + str.substring( 6 ) );
      } else {
	names[i] = str.substring( 6 );
	connections[i].SendText( "Chat: Welcome " + names[i] );
	
	for ( int j = 0; j < numconnects; j++ )
	  if (j != i )
	    connections[j].SendText( "Chat: " + names[i] + 
				     " just joined the discussion." );
      }
    }

    if ( str.startsWith( "Move: " ) )
      if ( games[i] != -1 )
	connections[games[i]].SendText( str );

  }

  public void SendToAll( String str ) {
    int i;

    for ( i = 0; i < numconnects; i++ ) {
      connections[i].SendText( str );
    }
  }
  
  public static void main( String[] args ) {
    int p = 8000;

    if ( args.length > 0 ) {
      try {
	p = Integer.parseInt( args[0] );
      } catch( NumberFormatException e ) {
	fail( e, "USAGE\nChessServer <port #>\n" );
      }
    }

    ChessServer cs = new ChessServer( p );
    System.out.println( "Server started on port " + p );    

    (new Thread( cs )).start();
  }
}

interface ServerSocketGrabber {
  public void GrabText( Socket s, String str );
}

class ConnectThread implements Runnable {
  private Socket sock;
  private ServerSocketGrabber contact;
  private DataInputStream sockin;
  private PrintStream sockout;
  

  public ConnectThread( Socket s, ServerSocketGrabber c ) {
    sock = s;
    contact = c;

    try {
      sockin = new DataInputStream( s.getInputStream() );
      sockout = new PrintStream( s.getOutputStream() );
    } catch ( IOException e ) {
      System.out.println( e );
    }
    (new Thread(this)).start();
  }

  public void run( ) {
    String line;

    try {
      while( true ) {
	line = sockin.readLine();
	if ( line != null )
	  contact.GrabText( sock, line );
      }
    } catch ( IOException e ) {
      System.out.println( e );
    }
  }

  public boolean isSameAs( Socket s ) {
    return (s == sock);
  }

  public void SendText( String s ) {
    sockout.println( s );
  }
}
