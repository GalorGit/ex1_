

#include "AsciiArtTool.c"
#define FLAG_INDEX 1
#define SOURCE_STREAM_INDEX 2
#define TRAGET_STREAM_INDEX 3
#define E_OR_I_INDEX 2
#define E 'e'
#define I 'i'
#define INVERTE_CHAR_SPACE ' '
#define INVERTE_CHAR_STRUDEL'@'


/**
 * @brief gets flag, source file, output file.
 * if the flag is 'e' - print in the output file the encoded source file image
 * if the flag is 'i' - print in the output file the inverted source file image
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char** argv)
{

    RLEListResult result;
    if((argv[FLAG_INDEX])[E_OR_I_INDEX] == E)
    {
        RLEList listedImage = asciiArtRead(argv[SOURCE_STREAM_INDEX]);
        if(listedImage == NULL){
            return 0;
        }
        result = asciiArtPrintEncoded(listedImage, argv[TRAGET_STREAM_INDEX]);
        if(result != RLE_LIST_SUCCESS){
            RLEListDestroy(listedImage);
            return 0;
        }
        RLEListDestroy(listedImage);
    }
    else
    {
        RLEList listedImage = asciiArtRead(argv[SOURCE_STREAM_INDEX]);
        if(listedImage == NULL){
            return 0;
        }
        MapFunction mapFunction = invertLetter;
        result = RLEListMap(listedImage, mapFunction);
        if(result != RLE_LIST_SUCCESS){
            RLEListDestroy(listedImage);
            return 0;
        }
        asciiArtPrint(listedImage, argv[TRAGET_STREAM_INDEX]);
        RLEListDestroy(listedImage);
    }

    return 0;
}


/**
 * @brief gets char c, if it is '@' it'll be changed to ' ', if it is ' ' it'll be changed to ' ',
 * else it would return c without changes
 * 
 * @param c char to invert
 * @return char 
 */
char invertLetter(char c)
{
    if(c == INVERTE_CHAR_SPACE){
        return INVERTE_CHAR_STRUDEL;
    }
    if(c == INVERTE_CHAR_STRUDEL){
        return INVERTE_CHAR_SPACE;
    }

    return c;
}





