//
// Created by Sorin on 14/11/2022.
//

#include "reducer.h"

void *reducer::work(void *args)
{

    auto *rArgs = (reducerArgs*)args;

    int taskType = rArgs->taskType;
    workpool *ownWorkpool = rArgs->ownWorkpool;
    void *accumulator = rArgs->accumulator;


    pthread_barrier_wait(rArgs->barrier);
    while( !ownWorkpool->empty(taskType) )
    {
        task t = ownWorkpool->getTask(taskType);
        rArgs->accumulate(t.args, accumulator);
    }

    rArgs->processAccumulator(accumulator);
    return nullptr;
}
