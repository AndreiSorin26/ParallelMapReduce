//
// Created by Sorin on 14/11/2022.
//

#include "mapper.h"

void *mapper::work(void *args)
{
    auto mArgs = (mapperArgs*)args;

    workpool *ownWorkpool = mArgs->ownWorkpool;
    workpool *nextWorkpool = mArgs->nextWorkpool;
    int taskType = mArgs->taskType;

    while( !ownWorkpool->empty(taskType) )
    {
        task t = ownWorkpool->getTask(taskType);
        void* result = t.job(t.args);

        std::vector<task> nextTasks = mArgs->convertResult(result);

        for( auto nextTask : nextTasks )
            nextWorkpool->putTask(nextTask);
    }

    pthread_barrier_wait(mArgs->barrier);
    return nullptr;
}
