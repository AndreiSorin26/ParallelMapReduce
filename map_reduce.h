//
// Created by Sorin on 14/11/2022.
//

#ifndef TEMA1_BONUS2_MAP_REDUCE_H
#define TEMA1_BONUS2_MAP_REDUCE_H

#include "mapper.h"
#include "reducer.h"

struct mapreduceArgs
{
    int mapperCount;
    mapperArgs mArgs;
    int reducerCount;
    std::vector<reducerArgs> rArgs;
};


class map_reduce
{
public:
    static void* start(void *args);
};


#endif //TEMA1_BONUS2_MAP_REDUCE_H
