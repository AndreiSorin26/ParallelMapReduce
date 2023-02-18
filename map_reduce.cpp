//
// Created by Sorin on 14/11/2022.
//

#include <iostream>
#include "map_reduce.h"

void *map_reduce::start(void *args)
{
    auto *mrArgs = (mapreduceArgs*)args;

    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, nullptr, mrArgs->mapperCount + mrArgs->reducerCount);
    mrArgs->mArgs.barrier = &barrier;
    for( int i = 0; i < mrArgs->reducerCount; i++ )
        mrArgs->rArgs[i].barrier = &barrier;

    pthread_t mapperThreads[mrArgs->mapperCount];
    for(int i = 0; i < mrArgs->mapperCount; i++)
        pthread_create(&mapperThreads[i], nullptr, mapper::work, &mrArgs->mArgs);

    pthread_t reducerThreads[mrArgs->mapperCount];
    for(int i = 0; i < mrArgs->reducerCount; i++)
        pthread_create(&reducerThreads[i], nullptr, reducer::work, &mrArgs->rArgs[i]);

    for(int i = 0; i < mrArgs->mapperCount; i++)
        pthread_join(mapperThreads[i], nullptr);
    for(int i = 0; i < mrArgs->reducerCount; i++)
        pthread_join(reducerThreads[i], nullptr);

    pthread_barrier_destroy(&barrier);
    return nullptr;
}
