#include <stdio.h>
#include <stdbool.h>
#include "AsciiArtTool.h"

#define BUFFER_SIZE 256
 
RLEList asciiArtRead(FILE *in_stream)
{
    RLEListResult result;
    char buffer[BUFFER_SIZE];
    RLEList list = RLEListCreate();
    RLEList ptr = list;
 
    result = RLEListAppend(list, buffer[0]);
    if (result != RLE_LIST_SUCCESS)
    {
       RLEListDestroy(list);
       return NULL;
    }
   
    while (fgets(buffer, BUFFER_SIZE, in_stream) != NULL)
    {
 
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            result = RLEListAppend(list, buffer[i]);
            if (result != RLE_LIST_SUCCESS)
            {
                RLEListDestroy(list);
                return NULL;
            }
        }
    }
    return list;
}
 
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if ((!list) || (!out_stream))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
 
    RLEListResult result = RLE_LIST_SUCCESS;
    char *str = RLEListExportToString(list, result);
    if(result != RLE_LIST_SUCCESS){
        return result;
    }
    if (!str)
    {
        return RLE_LIST_ERROR;
    }

    FILE* file = fopen(out_stream, 'w');
    if(file == NULL){
        return RLE_LIST_ERROR;
    }
    fprintf(str, out_stream);
    fclose(file);
    free(str);
 
    return RLE_LIST_SUCCESS;
}
 

