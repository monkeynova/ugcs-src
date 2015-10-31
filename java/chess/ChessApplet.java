import java.awt.*;
import java.awt.image.*;
import java.applet.*;
import ChessBoard;

public class ChessApplet extends Applet {
  ChessBoard board;
  private static boolean inApplet = true;
  private int fromx = -1, fromy = -1, tox = -1, toy = -1;
  private Applet caller;
  private final int boxwidth = 50;
  private boolean AllowMoves = true;
  private int side = -1;

  public ChessApplet( Applet a ) {
    caller = a;
  }

  public ChessApplet( ) {
    caller = this;
  }

  public Dimension preferredSize( ) {
    return new Dimension( boxwidth * board.width, boxwidth * board.height );
  }

  public void SetAllowMoves( boolean m ) {
    AllowMoves = m;
  }

  public void init ( ) {

  }

  public void StartGame( int s ) {
    String p;

    side = s;

    if ( caller == null )
      caller = this;
    
    board = new ChessBoard( caller, s );
    p = caller.getParameter( "HCOLOR" );
    if ( p != null )
      board.SetColor( new Color( Integer.parseInt( p, 16 )), board.Highlight);

    p = caller.getParameter( "MOVECOLOR" );
    if ( p != null )
      board.SetColor( new Color( Integer.parseInt( p, 16 )), board.Move);
    
    p = caller.getParameter( "CHECKCOLOR" );
    if ( p != null ) {
      if ( p.equalsIgnoreCase( "NULL" ) ) {
	board.SetColor( null, board.Check );
      } else {
	board.SetColor( new Color( Integer.parseInt( p, 16 ) ), board.Check );
      }
    }
    paint( getGraphics() );
  }

  public void EndGame( ) {
    board = null;
    side = -1;
  }

  public boolean Started( ) {
    return (board != null);
  }

  public boolean mouseDown( Event e, int x, int y ) {
    if ( board != null ) {
      if ( fromx == -1 ) {
	fromx = x * board.width / size().width;
	fromy = y * board.height / size().height;
      } else {
	tox = x * board.width / size().width;
	toy = y * board.height / size().height;
      }
    }

    return true;
  }

  public boolean mouseUp( Event e, int x, int y ) {
    if ( board != null ) {
      if ( tox == -1 ) {
	if ( fromx != x * board.width / size().width ||
	     fromy != y * board.height / size().height ||
	     board.Player( fromx, fromy ) != side ) {
	  fromx = fromy = -1;
	}
      } else {
	if ( tox != x * board.width / size().width ||
	     toy != y * board.height / size().height ) {
	  tox = toy = -1;
	} else {
	  if ( tox == fromx && toy == fromy ) {
	    fromx = fromy = tox = toy = -1;	    
	  } else if ( side == board.Turn() &&
		      board.Move( fromx, fromy, tox, toy ) ) {
	    fromx = fromy = tox = toy = -1;
	  } else {
	    tox = toy = -1;
	  }
	}
      }
      paint( getGraphics() );
    }

    return true;
  }

  public boolean Move( int x1, int y1, int x2, int y2 ) {
    boolean ret = board.Move( x1, y1, x2, y2 );

    if ( ret ) {
      paint( getGraphics() );
    }

    return ret;
  }

  public void paint( Graphics g ) {
    if ( board == null ) {
      g.drawString( "Game not started", size().width/2 - 50, size().height/2 );
    } else {
      board.Draw( g, 0, 0, size().width, size().height, this, fromx, fromy );
    }
  }
}











