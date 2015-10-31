#!/usr/bin/perl

@dirs = map { glob( $_ ) } @ARGV;

if (! @dirs ) {
    die "Usage:\n$0 <dirs>\n";
}

$| = 1;

foreach $d ( @dirs ) {
    print "Processing \"$d\"...";
    %info = ();
    $info{global}{title}="";
    $info{global}{parent}="";

    map { s,^.*/,,; $info{$_}{title}=$_ } glob( "$d/IMG_*.{jpg,JPG,avi,AVI}" );

    if ( open INF, "$d/.inf" ) {
	$curkey = "";
	while( <INF> ) {
	    if ( /^\s*\[(.*)\]\s*$/ ) {
		$curkey = $1;
	    } elsif ( $curkey && /^\s*(.*?)=(.*)$/ ) {
		$info{$curkey}{$1}=$2;
	    }
	}
	close INF;
    }
    open INF, ">$d/.inf.tmp";
    foreach $k ( sort g_first keys %info ) {
	print INF "[$k]\n";
	foreach $k2 ( keys %{$info{$k}} ) {
	    print INF "$k2=$info{$k}{$k2}\n";
	}
	print INF "\n";
    }
    close INF;
    rename "$d/.inf.tmp", "$d/.inf";
    print "Done.\n";
}
    
sub g_first {
    return 0 if ( $a eq $b );
    return -1 if ( $a eq "global" );
    return 1 if ( $b eq "global" );
    return $a cmp $b;
}

