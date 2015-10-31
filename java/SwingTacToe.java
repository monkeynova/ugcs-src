import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

class TicTacToeButton extends JButton {
  public static final int EMPTY = 0;
  public static final int X = 1;
  public static final int O = 2;
  private int state;
  private int x, y;

  public TicTacToeButton( int _x, int _y ) {
    super( "" );

    state = EMPTY;
    x = _x;
    y = _y;
  }

  void setState( int i ) {
    state = i;

    switch( state ) {
    case EMPTY:
      setText( "" );
      break;
    case X:
      setText( "X" );
      break;
    case O:
      setText( "O" );
      break;
    default:
      setState( EMPTY );
      break;
    }
  }

  int getState() {
    return state;
  }

  int getCoordX() { 
    return x;
  }

  int getCoordY() {
    return y;
  }
}

public class SwingTacToe extends JFrame implements ActionListener { 
  private String name;
  private TicTacToeButton[] board;
  private boolean firstplayer = true;
  private boolean done = false;
  private JButton reset;

  public SwingTacToe( String n ) {
    super( n );
    name = n;
    
    board = new TicTacToeButton[ 9 ];

    getContentPane().setLayout( new GridLayout( 4, 3 ) );

    for( int i = 0; i < 9; i++ ) {
      board[ i ] = new TicTacToeButton( i % 3, i / 3 );
      getContentPane().add( board[ i ] );
      board[ i ].addActionListener( this );
    }

    reset = new JButton( "Reset" );
    getContentPane().add( reset );
    reset.addActionListener( this );
  }

  public void actionPerformed( ActionEvent e ) {
    if ( ! (e.getSource() instanceof TicTacToeButton) ) {
      for( int i = 0; i < 9; i++ )
	board[ i ].setState( TicTacToeButton.EMPTY );

      return;
    }

    if ( done )
      return;

    TicTacToeButton b = (TicTacToeButton)e.getSource();

    if ( b.getState() == TicTacToeButton.EMPTY ) {
      System.out.println( "move to " + b.getCoordX() + "," + b.getCoordY() );

      b.setState( firstplayer?TicTacToeButton.X:TicTacToeButton.O );

      firstplayer = ! firstplayer;
    }

    int c;
    if ( (c = checkWin()) != TicTacToeButton.EMPTY ) {
      System.out.println( ((c==TicTacToeButton.X)?"X":"O") + " won" );
    }
  }

  private int checkWin() {
    int checknum = 0;
    int winner = TicTacToeButton.EMPTY;
    final int winnerX = TicTacToeButton.X * 13; // 111 base 3
    final int winnerO = TicTacToeButton.O * 13; // 111 base 3

    for( int i = 0; i < 9; i++ )
      checknum = 3 * checknum + board[ i ].getState();

    for( int i = 0; i < 9; i++ ) 
      checknum = 3 * checknum + board[ (i%3)*3 + (i/3) ].getState();

    for( int tmp = checknum; tmp > 0; tmp /= 27 ) {
      switch ( tmp % 27 ) {
      case winnerX:
	winner = TicTacToeButton.X;
	break;
      case winnerO:
	winner = TicTacToeButton.O;
	break;
      }
    }
    
    checknum = 0;
    for( int i = 0; i < 3; i++ )
      checknum = 3 * checknum + board[ i * 4 ].getState();
    for( int i = 1; i < 4; i++ )
      checknum = 3 * checknum + board[ i * 2 ].getState();

    for( int tmp = checknum; tmp > 0; tmp /= 27 ) {
      switch ( tmp % 27 ) {
      case winnerX:
	winner = TicTacToeButton.X;
	break;
      case winnerO:
	winner = TicTacToeButton.O;
	break;
      }
    }
    
    if ( winner != TicTacToeButton.EMPTY )
      done = true;

    return winner;
  }

  public static void main( String args [] ) {
    SwingTacToe myWin = new SwingTacToe( "Hello" );

    myWin.setSize( 400, 400 );
    myWin.addWindowListener( new WindowCloser() );
    myWin.show();
  }
}

class WindowCloser extends WindowAdapter {
  public void windowClosing( WindowEvent e ) {
    System.exit( 0 );
  }
}

