#ifndef __CDREADER_HH
#define __CDREADER_HH

// I need these for the stat system call
#include <sys/stat.h>
#include <unistd.h>
// For system open
#include <sys/types.h>
#include <fcntl.h>
// Just because
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MTAB_FILE "/etc/mtab"

class CDReader
{
public:
        CDReader(char *file, char *CD = NULL) {
                if ( CD == NULL )
		  cdrom = DetectCDROM();
		else
		  cdrom = strdup( CD );
                InitFile(file);
        }
        ~CDReader() {
                if ( fp ) fclose(fp);
		if ( cdrom ) delete cdrom;
        }
        bool Okay(void) {
                return (cdrom != 0) && fp;
        }
        long Size(void) { // Cache the size
                return(size);
        }
       long long Read(char *&data) {
                char *here;
		long long linecount;
                if ( ! data ) {
                        data = new char[Size()];
                }

		// fgetc is pretty slow - especially without buffering
		/* But if you're going to do it use int ch not char ch
		int ch;
                here = data;
                linecount = 0;
                while ( (ch=fgetc(fp)) != EOF ) {
                        if ( ch == '\n' ) {
                                ++linecount;
                        }
                        *here++ = ch;
                }
 		
		return linecount;*/

		linecount = 0;
		fread( data, 1, Size(), fp );
		
		for( here = data; here - data < Size(); here++ ) {
		  if ( *here == '\n' ) {
		    ++linecount;
		  }
		}

                return linecount;
        }
protected:
        char *cdrom;
        FILE *fp;
	long size;

        void InitFile(char *file) {
                char *path;
		struct stat info;
		path = new char[ strlen( cdrom ) + strlen( file ) + 2 ];
                sprintf(path, "%s/%s", cdrom, file);
                fp = fopen(path, "r");
		if ( ! fp )
		  return;

		// stat is faster and scales better
		if ( stat( path, &info ) != 0 ) {
		  long pos = ftell(fp);

		  fseek(fp, 0, SEEK_END);
		  size = ftell(fp);
		  fseek(fp, pos, SEEK_SET);
		} else {
		  size = info.st_size;
		}
        }
        char *DetectCDROM(void) {
	  int mtab;
	  char *tabbuf, *cdloc, *ret;
	  struct stat info;

	  // Idea - check /etc/mtab for the iso9660 filesystem

	  if ( stat( MTAB_FILE, &info ) != 0 ) {
	    return NULL; // Couldn't find the mtab
	  }
	  tabbuf = new char[ info.st_size ];
	  
	  if ( (mtab = open( MTAB_FILE, O_RDONLY )) == -1 ) {
	    return NULL; // No Mtab file or no permission to read
	  }
	  read( mtab, tabbuf, info.st_size );
	  close( mtab );
	  // find the string iso9660 in the file
	  // and go back one word
	  cdloc = strstr( tabbuf, "iso9660" );
	  if ( cdloc == NULL ) {
	    return NULL; // No ISO9660 Filesystem mounted
	  }
	  for( cdloc--; isspace( *cdloc ); cdloc-- )
	    ;
	  *(cdloc+1) = '\0';
	  for( cdloc--; ! isspace( *cdloc ); cdloc-- )
	    ;
	  cdloc++;
	  ret = strdup( cdloc );
	  delete tabbuf;
	  return ret;
        }               
};

#endif __CDREADER_HH
