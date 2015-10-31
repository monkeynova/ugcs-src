package RPG;

@rooms = (
  [ "name" => "Entry", 
    "init" => 1,
    "north" => "MainRoom", 
    "description" => "A boring room you start in"
  ],
  [ "name" => "MainRoom",
    "init" => 0,
    "south" => "Entry",
    "description" => "Your second room to be in"
  ]
);

@objects = (

);

sub new {
  my $self = shift;
  my $class = ref($self) || $self;
  my $ret = \{};

  $ret->Init( @_ );

  return bless $ret, $class;
}

sub Init {
  $self = shift;
  my $rm_init, $obj_init;

  foreach $rm_init (@rooms) {
    $name = $rm_init->{"name"};
    $self->{Rooms}->{$name} = $rm_init;
    if ( $rm_init->{Init} ) {
      $self->{Location} = $name;
    }
  } 
  foreach $obj_init ( @objects ) {
    $name = $obj_init->{"name"};
    $self->{Objects}->{$name} = $obj_init;
  }
}

sub Move {
  $self = shift;
  my $direction = shift;

  if ( defined $self->{Rooms}->{$self->{Location}}->{$direction} ) {
    $self->{Location} = $self->{Rooms}->{$self->{Location}}->{$direction};
  } else {
    print "No such exit\n";
  }
}

sub Command {
  $self = shift;
  my $cmd = shift;
  my $cmd_ent, @cmd_line;
  @cmd_line = split / /, $cmd;

  foreach $cmd_ent ( keys %cmd_list ) {
    if ( $cmd_line[0] eq $cmd_name ) {
      &{$cmd_name{$cmd_ent}}(@cmd_line);
    }
  }
}

1;
