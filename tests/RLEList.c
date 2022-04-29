#include "RLEList.h"
#include <stdio.h>
#include <stdlib.h>

struct RLEList_t
{
    // TODO: implement
    char letter;
    int length;
    struct RLEList_t *next;
};

// implement the functions here

/**
 * RLEListCreate: Allocates a new empty RLE list.
 *
 * The function allocates and returns a new RLEList struct containing a list with no characters.
 * Note that the user must free the returned list using RLEListDestroy() once it is no longer needed.
 *
 * @return
 *  NULL if allocations failed.
 *  A new RLEList in case of success.
 */
RLEList RLEListCreate()
{
    RLEList ptr = malloc(sizeof(*ptr));
    if (!ptr)
    {
        return NULL;
    }
    ptr -> letter = '\0';
    ptr->length = 0;
    ptr->next = NULL;
    return ptr;
}

/**
 * RLEListDestroy: Deallocates an existing RLE list.
 *
 * @param list - RLE list to be deallocated. If RLE list is NULL nothing will be done
 */
void RLEListDestroy(RLEList list)
{
    if (list == NULL)
    {
        return;
    }
    while (list)
    {
        RLEList toDetele = list;
        list = list->next;
        free(toDetele);
    }
}

/**
 *   RLEListAppend: add a specified character at the end of the list.
 *
 * @param list - The RLE list for which to add the character
 * @param value - The character which needs to be added.
 * @return
 *  RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *  RLE_LIST_OUT_OF_MEMORY if an allocation failed
 *  RLE_LIST_SUCCESS if the character has been inserted successfully
 */
RLEListResult RLEListAppend(RLEList list, char value)
{
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (value == '\0')
    {
        return RLE_LIST_ERROR;
    }

    RLEList ptr = list;
    if (list->length == 0)
    {
        ptr->letter = value;
        ptr->length = 1;
        return RLE_LIST_SUCCESS;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }

        if (ptr->letter == value)
        {
            ptr->length++;
            return RLE_LIST_SUCCESS;
        }
        else
        {
            if ((ptr->next = RLEListCreate()) == NULL)
            {
                return RLE_LIST_OUT_OF_MEMORY;
            }

            ptr->next->letter = value;
            ptr->next->length = 1;

            return RLE_LIST_SUCCESS;
        }
    }
}

/**
 * RLEListSize: Returns the total number of characters in an RLE list.
 * @param list - The RLE list whose size is requested
 * @return
 *   -1 if a NULL pointer was sent.
 *   Otherwise the total number of characters in the list.
 */
int RLEListSize(RLEList list)
{
    if (!list)
    {
        return -1;
    }
    RLEList ptr = list;
    int length;
    while (!ptr)
    {
        length += ptr->length;
        ptr = ptr->next;
    }
    return length + 1;
}

/**
 *   RLEListRemove: Removes a character found at a specified index in an RLE list.
 *
 * @param list - The RLE list to remove the character from.
 * @param index - The index at which the character to be removed is found.
 * @return
 *   RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function.
 *   RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
 *   RLE_LIST_SUCCESS the character found at index has been removed successfully.
 */
RLEListResult RLEListRemove(RLEList list, int index)
{
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int fullSize = RLEListSize(list);
    if (fullSize <= index)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int length = list->length;
    if (length < index)
    {
        /*
        // Galor - maby its unnecessary
        if(length == 0)
        {
            RLEList ptr = list;
            list = list -> next;
            free(ptr);
        }
        */
        return RLEListRemove(list->next, index - length);
    }
    else if (length <= 1)
    {
        RLEList ptr = list;
        list = list->next;
        free(ptr);
    }
    if (index != 0)
    {
        list->length -= 1;
    }

    return RLE_LIST_SUCCESS;
}

/**
 *   RLEListGet: Returns the character found at a specified index in an RLE list.
 *
 * @param list - The RLE list to retrieve the character from.
 * @param index - The index at which the character to be retrieved is found.
 * @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
 *  RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
 *  RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
 *  LIST_SUCCESS the character found at index has been retrieved successfully.
 * @return
 *  0 if result is not RLE_LIST_SUCCESS.
 *  The character found at given index in case of success.
 */
char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (list == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if (index + 1 > RLEListSize(list))
    {
        if (result != NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }

    RLEList ptr = list, lastNode = list;
    int sum = 0;
    while ((sum < index + 1) && (ptr != NULL))
    {
        sum += ptr->length;
        lastNode = ptr;
        ptr = ptr->next;
    }

    if (sum == (index + 1))
    {
        if (result != NULL)
        {
            *result = RLE_LIST_SUCCESS;
        }
        return ptr->letter;
    }

    if (result != NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return lastNode->letter;
}

/**
 *   RLEListMap: Change the given RLE list's characters according to the received mapping function.
 *               This function replaces each character of the give RLE list with its mapped character.
 *
 * @param list - The RLE list to edit.
 * @param MapFunction - Pointer to a function of type MapFunction.
 * @return
 *  RLE_LIST_NULL_ARGUMENT if a NULL was sent as a paramater.
 *  LIST_SUCCESS if the mapping is done successfully.
 */
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{

    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (map_function == NULL){
        return RLE_LIST_ERROR;
    }
    RLEList ptr = list;
    while (ptr != NULL)
    {
        ptr->letter = map_function(ptr->letter);
        ptr = ptr->next;
    }
    return RLE_LIST_SUCCESS;
}

/**
 *   RLEListExportToString: Returns the characters found in an RLE list as a string.
 *
 * @param list - The RLE list to be exported as a string.
 * @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
 *  RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
 *  LIST_SUCCESS the RLE list has been successfuly exported as a string.
 * @return
 *  NULL if result is not RLE_LIST_SUCCESS.
 *  The string that corresponds to the received RLE list.
 */
char *RLEListExportToString(RLEList list, RLEListResult *result)
{
    if (list == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }

    char *str = malloc(RLEListSize(list) * 3);
    if (str == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_ERROR;
        }
        return NULL;
    }
    int size = 0;
    RLEList ptr = list;
    while (ptr != NULL)
    {
        *str = ptr->letter;
        *(str + 1) = (char)(ptr->length);
        *(str + 2) = '\n';
        // printf("%c%d", ptr ->letter, ptr ->length);
        ptr = ptr->next;
        str += 3;
        size += 3;
    }

    char *tmp = malloc(size);
    if (tmp == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        free(str);
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        tmp[i] = str[i];
    }
    free(str);

    if (result != NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return tmp;
}
