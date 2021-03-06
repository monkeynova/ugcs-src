#!/usr/ug/bin/perl

use Image::Magick;
use constant ThumbSize => "100x100";
use constant LargeSize => "600x600";

# Options...
$useThumbSize = 1;
$useLargeSize = 1;
$template     = "default";
$reverse      = 0;

if ( ! @ARGV ) {
    die "Usage:\n$0: <input directorys>\n";
}

while( $ARGV[0] =~ /^-/ )
{
    $opt = shift @ARGV;
    $useLargeSize = 0 if $opt eq "-nl";
    $useThumbSize = 0 if $opt eq "-nt";
    $reverse      = 1 if $opt eq "-reverse";
    $template = shift if $opt eq "-template";
}

sub sort_fwd { $a->{file} cmp $b->{file} }
sub sort_rev { $b->{file} cmp $a->{file} }

$sort_ret = $reverse?\&sort_rev:\&sort_fwd;

$|=1;
foreach ( map { glob( $_ ) } @ARGV ) {
    print "Processing \"$_\"...";
    run_dir( $_ );
    print "Done\n";
}

sub run_dir {
    my ( $indir, $outdir ) = @_;
    $outdir ||= $indir;

    my $globals = {};

    opendir DIR, $indir;
    @files = grep /^(?!(thumb|large)_).*\.(jpg|avi)$/i, readdir DIR;
    closedir DIR;

    if ( ! -d $outdir ) {
      system( "mkdir -p $outdir" );
    }

    for ( @files ) { resize( $_, $indir, $outdir ); }

    @info = load_info( $indir, $globals, @files ); 

    ($templatedir = $0) =~ s,/[^/]+$,/templates/$template/,;

    opendir DIR, $templatedir;
    @templates = grep {!/^\./ && !/\~$/} readdir DIR;
    closedir DIR;

    foreach ( @templates )
    {
      run_template( $_, $templatedir, $outdir, $globals, @info ) or
        print "Cannot run $_!\n";
    }
}

sub run_template {
  ($template, $dir, $outdir, $globals, @args) = @_;

  open IN, "$dir/$template" or return 0;
  my $tmp = join( "", <IN> );
  close IN;
  if ( $tmp =~ /BEGIN_LOOP\n?(.*)END_LOOP\n?/s ) {
    my ($a, $loop, $b, $line) = ($`, $1, $');
#' Stupid emacs!

    $a =~ s/\$_\[(\d+)\]\{([^\}]+)\}/$args[$1]{$2}/g;
    $a =~ s/\$global\{([^\}]+)\}/$globals->{$1}/g;
    $b =~ s/\$_\[(\d+)\]\{([^\}]+)\}/$args[$1]{$2}/g;
    $b =~ s/\$global\{([^\}]+)\}/$globals->{$1}/g;

    $tmp = $a;
    foreach ( @args ) {
      ($line = $loop) =~ s/\$_\{([^\}]+)\}/$_->{$1}/g;
      $tmp .= $line;
    } 
    $tmp .= $b;
  } else {
    if ( $args[0] )
    {
      $tmp =~ s/\$_\{([^\}]+)\}/$args[0]{$1}/g;
    }
    $tmp =~ s/\$global\{([^\}]+)\}/$globals->{$1}/g;
  }
  open OUT, ">$outdir/$template" or return 0;
  print OUT $tmp;
  close OUT;
}

sub resize {
  my( $file, $indir, $outdir ) = @_;

  if ( $file =~ /\.jpg$/i )
  {
      if ($useThumbSize && ! -f "$outdir/thumb_$file" ) {
          $p = new Image::Magick;
          $p->Read( "$indir/$file" );
          $p->Resize( ThumbSize );
          $p->Write( "$outdir/thumb_$file" );
      }
      
      if ($useLargeSize && ! -f "$outdir/large_$file" ) {
          $p = new Image::Magick;
          $p->Read( "$indir/$file" );
          $p->Resize( LargeSize );
          $p->Write( "$outdir/large_$file" );
      }
  }
  else
  {
      ($outfile = $file) =~ s/\.avi/\.jpg/i;
      if ( $useThumbSize && ! -f "$outdir/thumb_$outfile" ||
           $useLargeSize && ! -f "$outdir/large_$outfile" )
      {
          my ( $data ) = `lav2yuv +n -f 1 $indir/$file | y4mtoppm > /tmp/foo.ppm`;
          if ( $useLargeSize )
          {
              $p = new Image::Magick;
              $p->Read( "/tmp/foo.ppm" );
              $p->Write( "$outdir/large_$outfile" );
          }

          if ( $useThumbSize )
          {
              $p = new Image::Magick;
              $p->Read( "/tmp/foo.ppm" );
              $p->Resize( ThumbSize );
              $p->Write( "$outdir/thumb_$outfile" );
          }
      }
  }
}

sub load_info {
  my ( $indir, $global, @files ) = @_;

  my $image = new Image::Magick;

  my @ret;

  $global->{total} = scalar( @files );

  foreach ( @files )
  {
      my ( $hash, $p );
      $hash->{file} = $_;
      $hash->{time} = (stat( "$indir/$_" ))[9];
      @$hash{"time-min","time-hour","time-day","time-mon","time-year"} =
          (localtime( $hash->{time} ))[1,2,3,4,5];
      $hash->{"time-min"} = sprintf "%02d", $hash->{"time-min"};
      $hash->{"time-hour"} = sprintf "%02d", $hash->{"time-hour"};
      $hash->{"time-mon"}++;
      $hash->{"time-year"} += 1900;

      if ( /\.jpg$/i )
      {
          ($hash->{width},$hash->{height}) = $image->Ping("$indir/$_");
          ($hash->{thumb_width},$hash->{thumb_height}) = $image->Ping("$indir/thumb_$_");
          ($hash->{large_width},$hash->{large_height}) = $image->Ping("$indir/large_$_");
          $hash->{thumbfile} = "thumb_$_";
          $hash->{largefile} = "large_$_";
      }
      else
      {
          my ($jpg);
          ($jpg = $_) =~ s/\.avi$/\.jpg/i;
          ($hash->{thumb_width},$hash->{thumb_height}) = $image->Ping("$indir/thumb_$jpg");
          ($hash->{width},$hash->{height}) = $image->Ping("$indir/large_$jpg");
          ($hash->{large_width},$hash->{large_height}) = ($hash->{width},$hash->{height});

          $hash->{thumbfile} = "thumb_$jpg";
          $hash->{largefile} = "large_$jpg";
      }
      push @ret, $hash;
  }

  sort $sort_ret @ret;

  my $cur = undef;

  open TXT, "$indir/.inf" or return @ret;
  while ( <TXT> ) {
    if ( /\[(.*)\]/ ) {
      ($cur = $1) =~ s/(^\s+)|(\s+$)//g;
      foreach ( @ret ) {
        if ( $_->{file} eq $cur ) {
          $cur = $_;
          last;
        } 
      }
      if ( ! ref( $cur ) ) { $cur = ($cur eq "global")?$global:undef; }
    } elsif ( $cur && /(.*?)=(.*)/ ) {
      my ($k,$v) = ($1, $2);
      $k =~ s/(^\s+)|(\s+$)//g;
      $v =~ s/(^\s+)|(\s+$)//g;

      $cur->{$k} = $v; 
    }
  }
  close TXT;

  if ( $global->{reverse} )
  {
      $reverse = 1;
      $sort_ret = \&sort_rev;
  }

  return sort $sort_ret @ret;
}
