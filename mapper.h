//
// Created by Sorin on 14/11/2022.
//

#ifndef TEMA1_BONUS2_MAPPER_H
#define TEMA1_BONUS2_MAPPER_H

#include "workpool.h"

struct mapperArgs
{
    int taskType;
    workpool *ownWorkpool;

    workpool *nextWorkpool;
    std::vector<task> (*convertResult)(void*);

    pthread_barrier_t *barrier;
};

class mapper
{
public:
    static void* work(void *args);
};


#endif //TEMA1_BONUS2_MAPPER_H
