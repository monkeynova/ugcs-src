#include <windows.h>
#include <stdio.h>

#include "CDReader.h"
#include "CDReader.h"   /* Not a typo, the file is included twice */

int main(int argc, char *argv[])
{
        static char *data;
        CDReader reader(argv[1]);

        if ( reader.Okay() )
                printf("File had %d lines\n", reader.Read(data));
        else
                printf("Unable to open %s on the CD\n", argv[1]);
        return(0);
}

