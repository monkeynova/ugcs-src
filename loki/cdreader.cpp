#include <stdio.h>

#include "CDReader.h"
#include "CDReader.h"   /* Not a typo, the file is included twice */

int main(int argc, char *argv[])
{
        static char *data = NULL;
        CDReader reader(argv[1]);

        if ( reader.Okay() )
                printf("File had %lld lines\n", reader.Read(data));
        else
                printf("Unable to open %s on the CD\n", argv[1]);

	// Clean up memory - the only thing that could be a memory leak
	// but it's a little silly to worry about in this case since
	// two lines afterwards it gets cleaned up with the system exitting

	if ( data ) delete data; 
	
        return(0);
}

