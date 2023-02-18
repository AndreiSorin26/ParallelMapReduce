//
// Created by Sorin on 14/11/2022.
//

#ifndef TEMA1_BONUS2_WORKPOOL_H
#define TEMA1_BONUS2_WORKPOOL_H

#include <map>
#include <vector>
#include <deque>
#include <pthread.h>
#include <algorithm>

struct task
{
    int taskType;
    void *args;
    void* (*job)(void*);
};

class workpool
{
public:
    explicit workpool();
    virtual ~workpool();

    task getTask(int type);
    void putTask(task task);

    bool empty(int type);
private:
    std::map<int, std::deque<task>> tasks;
    pthread_mutex_t lock;
};


#endif //TEMA1_BONUS2_WORKPOOL_H
