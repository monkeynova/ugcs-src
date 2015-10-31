#!/usr/ug/bin/perl

use Image::Magick;
use constant ThumbSize => "100x100";
use constant LargeSize => "800x800";

$outdir = shift or die "Usage:\n$0: <image directory>\n";

opendir DIR, $outdir;
@files = grep /^(?!thumb).*jpg$/i, readdir DIR;
closedir DIR;

for ( @files ) { resize( $_, $outdir ); }

@info = load_info( $outdir, @files ); 

($templatedir = $0) =~ s,/[^/]+$,/templates/,;

run_template( "side.html", $templatedir, $outdir, @info ) or 
  print "Cannot run side.html\n";
run_template( "main.shtml", $templatedir, $outdir, @info ) or 
  print "Cannot run main.shtml\n";
run_template( "index.html", $templatedir, $outdir, $info[0] ) or 
  print "Cannot run index.html\n";

sub run_template {
  ($template, $dir, $outdir, @args) = @_;

  open IN, "$dir/$template" or return 0;
  my $tmp = join( "", <IN> );
  close IN;
  if ( @args > 1 ) {
    if ( $tmp =~ /BEGIN_LOOP\n?(.*)END_LOOP\n?/s ) {
      my ($a, $loop, $b, $line) = ($`, $1, $');
      $tmp = $a;
      foreach ( @args ) {
        ($line = $loop) =~ s/\$_\{([^\}]+)\}/$_->{$1}/g;
        $tmp .= $line;
      } 
      $tmp .= $b;
    } else {
      print "No loop found: $template\n---$tmp---\n";
    }
  } elsif ( @args ) {
    $tmp =~ s/\$_\{([^\}]+)\}/$args[0]{$1}/g;
  }
  open OUT, ">$outdir/$template" or return 0;
  print OUT $tmp;
  close OUT;
}

sub resize {
  my( $file, $outdir ) = @_;

  if (! -f "$outdir/thumb_$file" ) {
    $p = new Image::Magick;
    $p->Read( "$outdir/$file" );
    $p->Resize( ThumbSize );
    $p->Write( "$outdir/thumb_$file" );
  }
}

sub load_info {
  my ( $outdir, @files ) = @_;

  my @ret = map { { file => $_ } } @files;
  my $cur = undef;

  open TXT, "$outdir/.inf" or return @ret;
  while ( <TXT> ) {
    if ( /\[(.*)\]/ ) {
      ($cur = $1) =~ s/(^\s+)|(\s+$)//g;
      foreach ( @ret ) {
        if ( $_->{file} eq $cur ) {
          $cur = $_;
          last;
        } 
      }
      if ( ! ref( $cur ) ) { $cur = undef; }
    } elsif ( $cur && /(.*?)=(.*)/ ) {
      my ($k,$v) = ($1, $2);
      $k =~ s/(^\s+)|(\s+$)//g;
      $v =~ s/(^\s+)|(\s+$)//g;

      $cur->{$k} = $v; 
    }
  }
  close TXT;

  return @ret;
}
