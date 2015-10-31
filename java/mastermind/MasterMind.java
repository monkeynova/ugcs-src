import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class MasterMind extends Applet {
    private int board[][] = new int[12][4];
    private int hidden[] = new int[4];
    private Color clist[] = new Color[ 5 ];
    private boolean done = true;
    private int currentRow = 0;
    private int currentColor = 0;
    private int lastx = 0, lasty = 0;
    private Image back;
    
    private final static double cwp = .15;
    private final static double chp = .06;
    private final static double pad = .02;
    private final static double left = .2;
    private final static double right = .8;
    private final static double vpad = .07;
    
    public void init() {
	int i, j;
	
	clist[ 0 ] = Color.black;
	clist[ 1 ] = Color.red;
	clist[ 2 ] = Color.blue;
	clist[ 3 ] = Color.green;
	clist[ 4 ] = Color.yellow;
	
	for ( i = 0; i < 4; i++ )
	    hidden[ i ] = (int)((Math.random() * 4) + 1);

	for( j = 0; j < 12; j++ )
	    for( i = 0; i < 4; i++ )
		board[j][i] = 0;
	
	currentRow = 0;
	done = false;
    }

    public int getMatch( int row1[], int row2[] ) {
	int blacks = 0, whites = 0;
	int i, j;
	int r1t, r2t;
	int ret = 0;

	for( i = 0; i < 4; i++ )
	    if ( row1[i] == row2[i] )
		blacks++;

	for( j = 1; j < 5; j++ ) {
	    r1t = r2t = 0;
	    for( i = 0; i < 4; i++ ) {
		if ( row1[ i ] == j )
		    r1t++;
		if ( row2[ i ] == j )
		    r2t++;
	    }
	    whites += (r1t<r2t)?r1t:r2t;
	}
	whites -= blacks;
	    
	for( i = 0; i < 4; i++ ) {
	    ret = ret * 3;
	    if ( blacks > 0 ) {
		ret++;
		blacks--;
	    } else if ( whites > 0 ) {
		ret += 2;
		whites--;
	    }
	}
	    
	return ret;
    }
    
    public boolean mouseDown( Event e, int x, int y ) {
	int width = size().width;
	int height = size().height;
	
	if ( x >= pad * width && x <= width * (cwp + pad) &&
	     y >= 2 * pad * height && y <= (2 * pad + 4 * vpad) * height ) {
	    currentColor = (int)((y - 2 * pad * height) / (vpad * height)) + 1;
	    
	    lastx = x;
	    lasty = y;
	    update( getGraphics() );
	}

	if ( x <= left * width && y >= (1 - vpad) * height ) {
	    init();
	    update( getGraphics() );
	}
	
	return true;
    }
    
    public boolean mouseUp( Event e, int x, int y ) {
	int width = size().width;
	int height = size().height;
	int dx, dy, i;
	
	if ( currentColor != 0 && ! done ) {
	    if ( x < right * width && x > left * width &&
		 y > height - 13 * vpad * height ) {
		dx = (int)((x - left * width) / (cwp * width));
		dy = (int)((height - y) / (vpad * height));
		
		if ( dy == currentRow ) {
		    board[dy][dx] = currentColor;
		    for ( i = 0; i < 4; i++ )
			if ( board[dy][i] == 0 )
			    break;
		    if ( i == 4 ) {
			currentRow++;
			if ( currentRow >= 12 )
			    done = true;
		    }
		}
	    }
	
	    currentColor = 0;
	    update( getGraphics() );
	}
	
	return true;
    }
    
    public boolean mouseDrag( Event e, int x, int y ) {
	if ( currentColor != 0 ) {
	    lastx = x;
	    lasty = y;
	    update( getGraphics() );
	}

	return true;
    }
    
    public void update( Graphics g ) {
	if ( back == null )
	    back = createImage( size().width, size().height );
	
	Graphics dbg = back.getGraphics();
	dbg.setColor( getBackground() );
	dbg.fillRect( 0,0, size().width, size().height );
	dbg.setColor( g.getColor() );
	paint( dbg );
	g.drawImage( back, 0, 0, this ); 
    }
    
    public void paint( Graphics g ) {
	int i, j, k;
	int width = size().width;
	int height = size().height;
	
	for( i = 0; i < 4; i++ ) {
	    g.setColor( clist[ i + 1 ] );
	    g.fillArc( (int)(width * pad), 
		       (int)(2 * pad * height + i * vpad * height),
		       (int)(width * cwp), (int)(height * chp),
		       0, 360 );
	    g.setColor( Color.black );
	    g.drawArc( (int)(width * pad), 
		       (int)(2 * pad * height + i * vpad * height),
		       (int)(width * cwp), (int)(height * chp),
		       0, 360 );
	}
	
	g.setColor( Color.black );
	g.drawLine( (int)(width * left), 0, (int)(width * left), height );
	g.drawLine( (int)(width * right), 0, (int)(width * right), height );

	g.drawRect( 0, (int)(height * ( 1 - vpad )), (int)(left * width) - 1, 
		    (int)(vpad * height) - 1 );
	g.drawString( "Reset", (int)(left * width / 2) - 20, (int)((1 - vpad / 2) * height));

	for ( j = 0; j < 12; j++ ) {
	    for( i = 0; i < 4; i++ ) {
		g.setColor( clist[ board[j][i] ] );
		g.fillArc( (int)(width * left + i * cwp * width),
			   (int)(height - (j + 1) * vpad * height),
			   (int)(cwp * width), (int)(chp * height),
			   0, 360 );
		g.setColor( Color.black );
		g.drawArc( (int)(width * left + i * cwp * width),
			   (int)(height - (j + 1) * vpad * height),
			   (int)(cwp * width), (int)(chp * height),
			   0, 360 );

		if ( j < currentRow ) {
		    int colors = getMatch( hidden, board[ j ] );
		    if (colors == 40) 
			done = true;
		    for( k = 0; k < 4; k++ ) {
			if ( colors % 3 == 1 )
			    g.setColor( Color.black );
			else if ( colors % 3 == 2 )
			    g.setColor( Color.white );

			if ( colors % 3 != 0 ) {
			    g.fillArc( (int)((right + pad + (1-(k%2)) * cwp / 2) * width),
				       (int)((1 - (j+1) * vpad + (k/2) * chp / 2)*height),
				       (int)(cwp / 2 * width), (int)(chp / 2 * height),
				       0, 360 );
			}
			colors /= 3;
		    }
		}
	    }
	}
	
	if ( done ) {
	    for( i = 0; i < 4; i++ ) {
		g.setColor( clist[ hidden[ i ] ] );
		g.fillArc( (int)(width * left + i * cwp * width),
			   (int)(pad * height), 
			   (int)(cwp * width), (int)(chp * height),
			   0, 360 );
		g.setColor( Color.black );
		g.drawArc( (int)(width * left + i * cwp * width),
			   (int)(pad * height), 
			   (int)(cwp * width), (int)(chp * height),
			   0, 360 );
	    }
	} else {
	    g.setColor( Color.black );
	    g.drawRect( (int)(width * (left + pad)), (int)(height * pad),
			(int)(width * (right - left - pad * 2)), 
			(int)(height * chp) );
	}
	
	if ( currentColor != 0 ) {
	    g.setColor( clist[ currentColor ] );
	    g.fillArc( lastx - (int)(cwp *.5 * width), 
		       lasty - (int)(chp * .5 * height), 
		       (int)(cwp * width), (int)(chp * height),
		       0, 360 );
	}
    }
    
    
    
    public static void main( String args[] ) {
	Frame f = new Frame( "MasterMind" );
	f.setSize( 300, 700 );
	MasterMind mm = new MasterMind();
	f.add( mm );
	mm.start();
	mm.init();
	f.addWindowListener( new WindowAdapter() {
	    public void windowClosing( WindowEvent e ) {
		System.exit( 0 );
	    }
	});
	f.show();
    }
}


