//
// Created by Sorin on 14/11/2022.
//

#include "workpool.h"

workpool::workpool()
{
    pthread_mutex_init(&lock, nullptr);
}

workpool::~workpool()
{
    pthread_mutex_destroy(&lock);
}

void workpool::putTask(task task)
{
    pthread_mutex_lock(&lock);
        tasks[task.taskType].push_back(task);
    pthread_mutex_unlock(&lock);
}

task workpool::getTask(int type)
{
    pthread_mutex_lock(&lock);
        task task = tasks[type].front();
        tasks[type].pop_front();
    pthread_mutex_unlock(&lock);

    return task;
}

bool workpool::empty(int type)
{
    return tasks[type].empty();
}