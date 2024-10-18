#include "array_operations.hh"


int greatest_v1(int *itemptr, int size)
{
   int max_value = *itemptr;

   for(int* ptr =itemptr; ptr <itemptr + size; ++ptr){
       if(*ptr > max_value){
           max_value = *ptr;
       }
   }

   return max_value;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int max_value = *itemptr;

    for(int* ptr =itemptr; ptr < endptr; ++ptr){
        if(*ptr > max_value){
            max_value= *ptr;
        }
    }

    return max_value;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    while(itemptr < endptr){
        *targetptr = *itemptr;
        ++itemptr;
        ++targetptr;
    }

}

void reverse(int *leftptr, int *rightptr)
{
    --rightptr;

    while (leftptr <rightptr) {

        int temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;

        ++leftptr;
        --rightptr;

    }

}
