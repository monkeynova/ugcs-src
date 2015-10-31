#pragma once

class CDReader
{
public:
        CDReader(char *file, char CD = NULL) {
                if ( CD == NULL )
                        CD = DetectCDROM();
                cdrom = CD;
                InitFile(file);
        }
        ~CDReader() {
                if ( fp ) fclose(fp);
        }
        BOOL Okay(void) {
                return (cdrom != 0) && fp;
        }
        long Size(void) {
                long pos = ftell(fp);
                long size;

                fseek(fp, 0, SEEK_END);
                size = ftell(fp);
                fseek(fp, pos, SEEK_SET);
                return(size);
        }
        __int64 Read(char *&data) {
                char *here;
                int   ch; __int64 linecount;
                if ( ! data ) {
                        data = new char[Size()];
                }
                here = data;
                linecount = 0;
                while ( (ch=getc(fp)) != EOF ) {
                        if ( ch == '\n' ) {
                                ++linecount;
                        }
                        *here++ = ch;
                }
                return linecount;
        }
protected:
        char cdrom;
        FILE *fp;

        void InitFile(char *file) {
                char path[MAX_PATH];
                sprintf(path, "%c:\\%s", cdrom, file);
                fp = fopen(path, "rb");
                if ( fp ) {
                        setvbuf(fp, 0, _IONBF, 0);
                }
        }
        char DetectCDROM(void) {
                for ( char ch='A'; ch <= 'Z'; ++ch ) {
                        char root[4];
                        sprintf(root, "%c:\\", ch);
                        if ( GetDriveType(root) == DRIVE_CDROM )
                                break;
                }
                if ( ch > 'Z' )
                        ch = 0;
                return(ch);
        }               
};
