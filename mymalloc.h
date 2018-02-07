//
//  mymalloc.h
//  Asst1
//
//  Created by Ridhima Sakhuja on 2/4/18.
//  Copyright © 2018 Ridhima Sakhuja. All rights reserved.
//


#include <stdio.h>


static char myblock[5000];  //array size simulated

typedef struct subBlock{
    int size; //size of data
    int free;       //flag to indicate if block is empty or not
    struct subBlock *next;  //pointer to next block
}subBlock;

subBlock *memory = (char*) myblock; //points to first block of memory




