#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i = 0;
    int arrayIndexes = 2;
    char ** myArray = malloc(arrayIndexes * sizeof(*myArray));

    //Allocate memory for each [x]
    //for (i = 0; i < arrayIndexes; i++)
    //{
    //    myArray[i] = malloc(254 * sizeof(char));
    //    printf(myArray[i], "string %d", i+1);
    //}

    //Populate initial values
    //if(myArray != NULL)
    //{
    //    strcpy(myArray[0], "string 1");
    //    strcpy(myArray[1], "string 2");
    //}
    myArray[0]="string ";
    myArray[1]="string 2";

    //Print out array values
    printf("Before: \n");
    for (i = 0; i < arrayIndexes; i++)
        printf("Array[%d]: %s\n", i, myArray[i]);

    // TODO: Fix this to check the result before orphaning the old
    //  value of myArray if an allocation failure ensues.
    myArray = realloc(myArray, (arrayIndexes+1) * sizeof(char*));
    ++arrayIndexes;

    //Allocate memory for the new string item in the array
    //myArray[arrayIndexes-1] = malloc(254 * sizeof(char*));

    //Populate a new value in the array
    //strcpy(myArray[arrayIndexes-1], "string 3"); //
    myArray[arrayIndexes-1] = "string 3";

    //Print out array values
    printf("After: \n");
    for (i = 0; i < arrayIndexes; i++)
        printf("Array[%d]: %s\n",i, myArray[i]);



    myArray = realloc(myArray, (arrayIndexes+1) * sizeof(char*));
    myArray[arrayIndexes] = "string 4";


    printf("After2: \n");
    for (i = 0; i <= arrayIndexes; i++)
        printf("Array[%d]: %s\n",i, myArray[i]);




    // TODO: write proper cleanup code just for good habits.
    return 0;
}
