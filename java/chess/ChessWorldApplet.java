import java.applet.*;
import java.awt.*;
import java.io.*;
import java.net.*;
import ChessApplet;

public class ChessWorldApplet extends Applet implements SocketGrabber {
  private ChessApplet game;
  private TextArea chatbox;
  private TextField prompt;
  private Panel gamearea;
  private Socket inet;
  private SocketListner sl;

  public void init() {
    game = new ChessApplet( this );
    gamearea = new Panel();
    chatbox = new TextArea( 30, 25);
    prompt = new TextField( 70 );

    String server = getParameter( "SERVER" );
    if ( server == null )
      server = "hubris.caltech.edu";
    String ports = getParameter( "PORT" );
    int port;
    if ( ports == null )
      port = 8000;
    else
      port = Integer.parseInt( ports );

    try {
      inet = new Socket( server, port );
      sl = new SocketListner( inet, this );
    } catch(  IOException e ) {
      System.out.println( e );
    }

    chatbox.setEditable( false );

    add( chatbox );
    add( gamearea );
    gamearea.add( "Center", game );
    add( new Button( "Clear" ) );
    add( prompt );
    add( new Button( "Send" ) );

    game.SetAllowMoves( false );
    game.init();
    game.start();
  }

  public boolean action( Event e, Object whatAction ) {
    if ( e.target instanceof Button ) {
      if ( "Send" == (String) whatAction ) {
	String text;

	text = prompt.getText();
	if ( text != null ) {
	  prompt.setText( "" );
	  sl.SendText( text );
	}
      } else if ( "Clear" == (String) whatAction ) {
	chatbox.setText( "" );
      }
    }

    return true;
  }

  public void GrabText( String s ) {
    if ( s.startsWith( "Chat: " ) ) {
      chatbox.appendText( s.substring( 6 ) + "\n" );

    } else if ( s.startsWith( "Game: " )) {
      if ( game.Started() )
	game.EndGame( );

      game.StartGame( Integer.parseInt( s.substring( 6 )) );

    } else if ( s.startsWith( "Move: " )) {
      char[] cnums = s.substring(6).toCharArray();

      int i;
      int[] nums = new int[4];
      for ( i = 0; i < 4; i++ )
	nums[i] = cnums[i] - '0';

      if ( ! game.Started() ) {
	chatbox.appendText( "---Game has not been started!---\n" );
      } else {
	if ( ! game.Move( nums[0], nums[1], nums[2], nums[3] ) ) {
	  chatbox.appendText( "---Invalid Move Sent!---\n" );
	}
      }
    }
  }

  protected void finalize( ) {
    try {
      inet.close();
    } catch ( IOException e ) { }
  }
}

interface SocketGrabber {
  public void GrabText( String s );
}

class SocketListner implements Runnable {
  private Socket sock;
  private SocketGrabber contact;
  private DataInputStream sockin;
  private PrintStream sockout;
  private Thread listner;
  

  public SocketListner( Socket s, SocketGrabber c ) {
    sock = s;
    contact = c;

    try {
      sockin = new DataInputStream( s.getInputStream() );
      sockout = new PrintStream( s.getOutputStream() );
    } catch ( IOException e ) {
      System.out.println( e );
    }

    listner = new Thread( this );
    listner.start();
  }

  public void run( ) {
    String line;

    try {
      while( true ) {
	line = sockin.readLine();
	if ( line != null )
	  contact.GrabText( line );
      }
    } catch ( IOException e ) {
      System.out.println( e );
    }
  }

  public void SendText( String s ) {
    sockout.println( s );
  }
}
