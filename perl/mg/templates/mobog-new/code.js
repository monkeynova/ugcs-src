var lastDiv = null;

var nimages = $global{total};

var images = new Array( nimages );
var i = 0;
BEGIN_LOOP
images[i++] = { file : "$_{file}", thumbfile : "$_{thumbfile}" };
END_LOOP

var curImage;

function prev() 
{
  setImage( (nimages + curImage - 1) % nimages );  
}

function next() 
{
  setImage( (curImage + 1) % nimages );  
}

function setImageByName( imgName )
{
  var i;

  for( i = 0; i < nimages; i++ )
  {
    if ( images[i].file == imgName )
    {
      setImage( i );
      return;
    }
  }
}
 
function setImage( img ) 
{
  var div = parent.main.document.getElementById( "div_" + images[img].file );
  var itag = parent.main.document.getElementById( "img_" + images[img].file );
 
  if ( lastDiv == div )
    return;

  if ( lastDiv != null ) {
    lastDiv.style.display = "none"
  }
  div.style.display = "block";
  itag.src = images[img].file;
 
  lastDiv = div;

  curImage = img;
}

var slideshowgoing = 0;
var delay = 0;
var delaytotal = 100;
var delaytime = 50;
var preload;

function updateslideshowbar()
{
  if ( ! slideshowgoing )
    return

  if ( delay == 0 )
  {
    preload = new Image();
    preload.src = images[(curImage + 1) % nimages].file;
  }

  var fill = parent.main.document.getElementById( "slideshowfill" );
  delay++;
  if ( delay == delaytotal )
  {
    delay = 0;
    next();
  }

  fill.style.width = (100 * delay / delaytotal) + "%";

  setTimeout( updateslideshowbar, delaytime );
}

function startslideshow()
{
  var progress = parent.main.document.getElementById( "slideshowprogress" );
  var start = parent.main.document.getElementById( "slideshowstart" );

  if ( ! progress || ! start )
    return;

  delay = -1;
  slideshowgoing = 1;

  updateslideshowbar();

  start.style.display = "none";
  progress.style.display = "block";
}

function stopslideshow()
{
  slideshowgoing = 0;

  var progress = parent.main.document.getElementById( "slideshowprogress" );
  var start = parent.main.document.getElementById( "slideshowstart" );

  if ( ! progress || ! start )
    return;

  progress.style.display = "none";
  start.style.display = "block";
}

function init()
{
  setImage( 0 );
  stopslideshow();
}
