//
// Created by Sorin on 14/11/2022.
//

#ifndef TEMA1_BONUS2_REDUCER_H
#define TEMA1_BONUS2_REDUCER_H

#include "workpool.h"

struct reducerArgs
{
    int taskType;
    workpool *ownWorkpool;

    void* accumulator;
    void (*accumulate)(void*, void*);
    void* (*processAccumulator)(void*);

    pthread_barrier_t *barrier;
};

class reducer
{
public:
    static void* work(void* args);
};


#endif //TEMA1_BONUS2_REDUCER_H
