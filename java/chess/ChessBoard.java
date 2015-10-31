import java.awt.*;
import java.awt.image.*;
import java.applet.*;

public class ChessBoard {
  public final int width = 8, height = 8;
  private final int White = 1, Black = 2;

  public final int Highlight = 1, Check = 2, Move = 3;
  private Color HighlightColor = Color.green;
  private Color CheckColor = Color.blue;
  private Color MoveColor = null;

  private ChessPiece[][] board = null;
  private int turn;

  // Private method used in Draw() to tell what color a space is
  private boolean IsSpaceWhite( int i, int j ) {
    return (((i + j) & 1) == 0);
  }

  public ChessBoard( Applet parent, int p ) {
    Image wpw, wrw, wnw, wbw, wqw, wkw, bpw, brw, bnw, bbw, bqw, bkw;
    Image wpb, wrb, wnb, wbb, wqb, wkb, bpb, brb, bnb, bbb, bqb, bkb;
    int i, j;

    // Load me some images
    wpw = parent.getImage( parent.getDocumentBase(), "images/wpw.gif" );
    wrw = parent.getImage( parent.getDocumentBase(), "images/wrw.gif" );
    wnw = parent.getImage( parent.getDocumentBase(), "images/wnw.gif" );
    wbw = parent.getImage( parent.getDocumentBase(), "images/wbw.gif" );
    wqw = parent.getImage( parent.getDocumentBase(), "images/wqw.gif" );
    wkw = parent.getImage( parent.getDocumentBase(), "images/wkw.gif" );

    bpw = parent.getImage( parent.getDocumentBase(), "images/bpw.gif" );
    brw = parent.getImage( parent.getDocumentBase(), "images/brw.gif" );
    bnw = parent.getImage( parent.getDocumentBase(), "images/bnw.gif" );
    bbw = parent.getImage( parent.getDocumentBase(), "images/bbw.gif" );
    bqw = parent.getImage( parent.getDocumentBase(), "images/bqw.gif" );
    bkw = parent.getImage( parent.getDocumentBase(), "images/bkw.gif" );

    wpb = parent.getImage( parent.getDocumentBase(), "images/wpb.gif" );
    wrb = parent.getImage( parent.getDocumentBase(), "images/wrb.gif" );
    wnb = parent.getImage( parent.getDocumentBase(), "images/wnb.gif" );
    wbb = parent.getImage( parent.getDocumentBase(), "images/wbb.gif" );
    wqb = parent.getImage( parent.getDocumentBase(), "images/wqb.gif" );
    wkb = parent.getImage( parent.getDocumentBase(), "images/wkb.gif" );

    bpb = parent.getImage( parent.getDocumentBase(), "images/bpb.gif" );
    brb = parent.getImage( parent.getDocumentBase(), "images/brb.gif" );
    bnb = parent.getImage( parent.getDocumentBase(), "images/bnb.gif" );
    bbb = parent.getImage( parent.getDocumentBase(), "images/bbb.gif" );
    bqb = parent.getImage( parent.getDocumentBase(), "images/bqb.gif" );
    bkb = parent.getImage( parent.getDocumentBase(), "images/bkb.gif" );

    board = new ChessPiece[width][height];

    for ( i = 0; i < width; i++ ) {
      for ( j = 0; j < height; j++ ) {
	board[i][j] = null;
      }
    }

    // White goes first
    turn = White;


    // Setup the board
    if ( p != 2 ) { // Allow for player "3" to watch from white's side
      for ( i = 0; i < 8; i++ )
	board[i][6] = new Pawn( this, White, wpw, wpb, Pawn.up );
      
      board[0][7] = new Rook( this, White, wrw, wrb );
      board[1][7] = new Knight( this, White, wnw, wnb );
      board[2][7] = new Bishop( this, White, wbw, wbb );
      board[3][7] = new Queen( this, White, wqw, wqb );
      board[4][7] = new King( this, White, wkw, wkb );
      board[5][7] = new Bishop( this, White, wbw, wbb );
      board[6][7] = new Knight( this, White, wnw, wnb );
      board[7][7] = new Rook( this, White, wrw, wrb );
      
      for ( i = 0; i < 8; i++ )
	board[i][1] = new Pawn( this, Black, bpw, bpb, Pawn.down );
      
      board[0][0] = new Rook( this, Black, brw, brb );
      board[1][0] = new Knight( this, Black, bnw, bnb );
      board[2][0] = new Bishop( this, Black, bbw, bbb );
      board[3][0] = new Queen( this, Black, bqw, bqb );
      board[4][0] = new King( this, Black, bkw, bkb );
      board[5][0] = new Bishop( this, Black, bbw, bbb );
      board[6][0] = new Knight( this, Black, bnw, bnb );
      board[7][0] = new Rook( this, Black, brw, brb );
    } else {
      for ( i = 0; i < 8; i++ )
	board[i][1] = new Pawn( this, White, wpw, wpb, Pawn.down );
      
      board[0][0] = new Rook( this, White, wrw, wrb );
      board[1][0] = new Knight( this, White, wnw, wnb );
      board[2][0] = new Bishop( this, White, wbw, wbb );
      board[3][0] = new King( this, White, wkw, wkb );
      board[4][0] = new Queen( this, White, wqw, wqb );
      board[5][0] = new Bishop( this, White, wbw, wbb );
      board[6][0] = new Knight( this, White, wnw, wnb );
      board[7][0] = new Rook( this, White, wrw, wrb );
      
      for ( i = 0; i < 8; i++ )
	board[i][6] = new Pawn( this, Black, bpw, bpb, Pawn.up );
      
      board[0][7] = new Rook( this, Black, brw, brb );
      board[1][7] = new Knight( this, Black, bnw, bnb );
      board[2][7] = new Bishop( this, Black, bbw, bbb );
      board[3][7] = new King( this, Black, bkw, bkb );
      board[4][7] = new Queen( this, Black, bqw, bqb );
      board[5][7] = new Bishop( this, Black, bbw, bbb );
      board[6][7] = new Knight( this, Black, bnw, bnb );
      board[7][7] = new Rook( this, Black, brw, brb );
    }
  }

  // Give the number of the player of the piece at (x,y)
  public int Player( int x, int y ) {
    if ( board[x][y] == null )
      return 0;
    else
      return board[x][y].GetPlayer();
  }

  // Change colors from the defaults
  public void SetColor( Color c, int which ) {
    switch( which ) {
    case Highlight:
      HighlightColor = c;
      break;
    case Check:
      CheckColor = c;
      break;
    case Move:
      MoveColor = c;
      break;
    default:
      break;
    }
  }

  // Whose turn is it, anyway?
  public int Turn( ) {
    return turn;
  }
  
  // Tell me if there is a King at (x,y) in check
  private boolean InCheck( int x, int y ) {
    if ( x >= width || y >= height || x < 0 || y < 0 )
      return false;

    if ( !( board[x][y] instanceof King ) )
      return false;

    int i, j;
    int attacker = 3 - board[x][y].GetPlayer();
    for ( i = 0; i < width; i++ )
      for ( j = 0; j < height; j++ )
	if ( board[i][j] != null && 
	     board[i][j].GetPlayer() == attacker &&
	     board[i][j].isValid( i, j, x, y ) )
	  return true;

    return false;
  }

  // Check for validity and move a piece
  public boolean Move( int x1, int y1, int x2, int y2 ) {
    if ( x1 < 0 || x1 > width || y1 < 0 || y1 > height || 
	 x2 < 0 || x2 > width || y2 < 0 || y2 > height || 
	 board[x1][y1] == null )
      return false;

    if ( board[x1][y1].GetPlayer() != turn )
      return false;

    if ( ! board[x1][y1].isValid( x1, y1, x2, y2 ) )
      return false;

    ChessPiece tmp = board[x2][y2];

    board[x2][y2] = board[x1][y1];
    board[x1][y1] = null;

    // Can't leave youself in Check
    int i = 0, j = 0;
    for ( i = 0; i < width; i++ ) {
      for ( j = 0; j < height; j++ ) {
	if ( board[i][j] != null && board[i][j] instanceof King &&
	     board[i][j].GetPlayer() == turn )
	  break;
      }
      if ( j != height )
	break;
    }
    if ( InCheck( i, j ) ) {
      board[x1][y1] = board[x2][y2];
      board[x2][y2] = tmp;
      return false;
    }

    board[x2][y2].SetMoved();
    
    turn = (turn == 1)?2:1;
    
    return true;
  }

  // Draw the board - Call each pieces draw routine
  public void Draw( Graphics g, int x, int y, int width, int height,
		    Applet a, int fromx, int fromy ) {
    int i, j;

    for ( i = 0; i < 8; i++ ) {
      for ( j = 0; j < 8; j++ ) {

	if ( fromx == i && fromy == j )
	  g.setColor( HighlightColor );
	else if ( CheckColor != null && InCheck( i, j ) )
	  g.setColor( CheckColor );
	else if ( MoveColor != null && 
		  fromx >=0 && fromx < width && 
		  fromy >= 0 && fromy < height &&
		  board[fromx][fromy].isValid( fromx, fromy, i, j ) )
	  g.setColor( MoveColor );
        else if ( IsSpaceWhite( i, j ) )
	  g.setColor( Color.white );
	else
	  g.setColor( Color.black );

	g.fillRect( i * width / 8, j * height / 8, 
		    width / 8, height / 8);

	g.setColor( Color.black );
	g.drawRect( i * width / 8, j * height / 8, 
		    width / 8, height / 8);

	if ( board[i][j] != null ) {
	  board[i][j].Draw(g, i * width / 8, j * height / 8, 
			   width / 8, height / 8, a, IsSpaceWhite( i, j ) );
	}
      }
    }
  }
}

// Base class - Derive, Derive!!
abstract class ChessPiece {
  protected ChessBoard GameBoard = null;
  protected Image WhitePicture = null;
  protected Image BlackPicture = null;
  protected int Player = 0;
  private boolean moved = false;

  public ChessPiece( ChessBoard b, int p, Image iw, Image ib ) {
    GameBoard = b;
    Player = p;
    WhitePicture = iw;
    BlackPicture = ib;
  }

  // Heart of the Heirarchy - Each piece knows what moves are valid
  public abstract boolean isValid( int x1, int y1, int x2, int y2 );

  public void Draw(Graphics g, int x, int y, int width, int height, 
		   Applet a, boolean onwhite) {
    int w, h;
    Image Drawer;

    if ( onwhite ) {
      Drawer = WhitePicture;
    } else {
      Drawer = BlackPicture;
    }

    w = Drawer.getWidth( a );
    h = Drawer.getHeight( a );

    g.drawImage( Drawer, x + width / 2 - w / 2, y + height / 2 - h / 2, a );

  }

  public void SetMoved( ) {
    moved = true;
  }

  public boolean HasMoved( ) {
    return moved;
  }

  public int GetPlayer( ) {
    return Player;
  }
  
  // CheckH, CheckV, and Check D check for legal moves in the horizontal
  // vertical and Diagonal directions between (x1,y1) and (x2,y2)
  // Used in the inValid routines to make life easier
  
  protected boolean CheckH( int x1, int y1, int x2, int y2 ) {
    int i;
    
    if ( x1 == x2 && y1 != y2) {
      if ( y1 < y2 ) {
	for ( i = y1 + 1; i < y2; i++ )
	  if ( GameBoard.Player( x1, i ) != 0 )
	    return false;
      } else {
	for ( i = y2 + 1; i < y1; i++ )
	  if ( GameBoard.Player( x1, i ) != 0 )
	    return false;	
      }
      
      return ( Player != GameBoard.Player( x2, y2 ) );
    }
    
    return false;
  }

  protected boolean CheckV( int x1, int y1, int x2, int y2 ) {
    int i;
    
    if ( y1 == y2 && x1 != x2 ) {
      if ( x1 < x2 ) {
	for ( i = x1 + 1; i < x2; i++ )
	  if ( GameBoard.Player( i, y1 ) != 0 )
	    return false;
      } else {
	for ( i = x2 + 1; i < x1; i++ )
	  if ( GameBoard.Player( i, y1 ) != 0 )
	    return false;
      }
      
      return ( Player != GameBoard.Player( x2, y2 ) );
    }
    
    return false;
  }

  protected boolean CheckD( int x1, int y1, int x2, int y2 ) {
    int i, slope;

    if ( Math.abs( x2 - x1 ) == Math.abs( y2 - y1 ) && x2 != x1 ) {
      slope = (y2 - y1) / (x2 - x1);
      
      if ( x1 < x2 ) {
	for ( i = 1; i + x1 < x2; i++ )
	  if ( GameBoard.Player( x1 + i, y1 + slope * i ) != 0 )
	    return false;
      } else {
	for ( i = 1; i + x2 < x1; i++ )
	  if ( GameBoard.Player( x2 + i, y2 + slope * i ) != 0)
	    return false;
      }

      return ( Player != GameBoard.Player( x2, y2 ) );
    }
    
    return false;
  }  
}

class Pawn extends ChessPiece {
  public final static int up = -1;
  public final static int down = 1;
  private int Direction;

  public Pawn( ChessBoard b, int p, Image iw, Image ib, int d ) {
    super( b, p, iw, ib );
    Direction = d;
  }

  public boolean isValid( int x1, int y1, int x2, int y2 ) {
    // Move up one to an empty spot
    if ( x1 == x2 && y1 + Direction == y2 && GameBoard.Player( x2, y2 ) == 0 )
      return true;

    // Diagonal up to take
    if ( Math.abs( x2 - x1 ) == 1 && y1 + Direction == y2 && 
	 GameBoard.Player( x2, y2 ) != 0 && 
	 GameBoard.Player( x2, y2 ) != Player )
      return true;

    //First Move - Up two to an empty spot
    if ( x1 == x2 && y1 + 2 * Direction == y2 && HasMoved() == false &&
	 GameBoard.Player( x2, y2 ) == 0 &&
	 GameBoard.Player( x2, y1 + Direction) == 0)
      return true;

    // Need En Passant

    return false;
  }
}

class Rook extends ChessPiece {

  public Rook( ChessBoard b, int p, Image iw, Image ib ) {
    super( b, p, iw, ib );
  }

  public boolean isValid( int x1, int y1, int x2, int y2 ) {
    return CheckH( x1, y1, x2, y2 ) || CheckV( x1, y1, x2, y2 );
  }
}

class Knight extends ChessPiece {

  public Knight( ChessBoard b, int p, Image iw, Image ib ) {
    super( b, p, iw, ib );
  }

  public boolean isValid( int x1, int y1, int x2, int y2 ) {
    return (Math.abs( x2 - x1 ) + Math.abs( y2 - y1 ) == 3) &&
      x2 != x1 && y2 != y1 && (Player != GameBoard.Player( x2, y2 ));
  }
}

class Bishop extends ChessPiece {

  public Bishop( ChessBoard b, int p, Image iw, Image ib ) {
    super( b, p, iw, ib );
  }

  public boolean isValid( int x1, int y1, int x2, int y2 ) {
    return CheckD( x1, y1, x2, y2 );
  }
}

class Queen extends ChessPiece {

  public Queen( ChessBoard b, int p, Image iw, Image ib ) {
    super( b, p, iw, ib );
  }

  public boolean isValid( int x1, int y1, int x2, int y2 ) {
    return CheckD( x1, y1, x2, y2 ) || CheckH( x1, y1, x2, y2 ) ||
      CheckV( x1, y1, x2, y2 );
  }
}

class King extends ChessPiece {

  public King( ChessBoard b, int p, Image iw, Image ib ) {
    super( b, p, iw, ib );
  }

  public boolean isValid( int x1, int y1, int x2, int y2 ) {
    return (Math.abs( x2 - x1 ) <= 1) &&  (Math.abs( y2 - y1 ) <= 1) &&
      (Player != GameBoard.Player( x2, y2 ));
  }
}
