#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include "map_reduce.h"

#define ulli unsigned long long int

struct mapperSpecifications
{
    std::string fileName;
    int reducerCount;
};

struct Accumulator
{
    int id;
    std::set<int> values;
};

double quickPower(double base, int exponent)
{
    if(exponent == 0)
        return 1.0;

    if( exponent % 2 == 0 )
        return quickPower(base*base, exponent/2);
    else
        return base*quickPower(base*base, exponent/2);
}

double root(double number, double order, double error = 0.1)
{
    if( order == 2 )
        return sqrt(number);

    double x = 1;
    while (true)
    {
        double h = ( quickPower(x, order) - number )/( order*quickPower(x, order - 1) );
        if( std::abs(h) < error )
            return x;
        x = x - h;
    }
}

ulli quickPow(ulli base, ulli exponent)
{
    if( exponent == 0 )
        return 1LL;

    if( exponent % 2 == 0 )
        return quickPow(base*base, exponent/2);
    else
        return base*quickPow(base*base, exponent/2);
}

bool isPerfectPower(ulli number, ulli exponent)
{
    if( number == 1 )
        return true;

    ulli val = root(number, exponent);
    bool ok = false;
    for( ulli i = val - 2; i <= val + 2; i++ )
        ok = ok || (number == quickPow(i, exponent));
    return ok;
}

void* mapperJob(void* specs)
{
    auto mArgs = (mapperSpecifications*)specs;
    auto result = new std::map<int, std::set<int>>;

    std::ifstream fin(mArgs->fileName);
    int n; fin>>n;
    for( int i = 0; i < n; i++ )
    {
        int value; fin>>value;
        if( value > 0 )
            for( int j = 2; j <= mArgs->reducerCount + 1; j++ )
                if(((*result)[j].find(value) == (*result)[j].end()) && isPerfectPower(value, j) )
                    (*result)[j].insert(value);
    }
    fin.close();

    delete mArgs;
    return result;
}

std::vector<task> convert(void *x)
{
    auto res = (std::map<int, std::set<int>>*)x;
    std::vector<task> tasks;

    for(auto & re : *res)
    {
        auto s = new std::set<int>(re.second.begin(), re.second.end());
        task t = {re.first, s, nullptr};
        tasks.push_back(t);
    }

    delete res;
    return tasks;
}

void accumulate(void *result, void *args)
{
    auto res = (std::set<int>*)result;
    auto acc = (Accumulator*)args;

    for( int x : (*res) )
        acc->values.insert(x);

    delete res;
}

void* writeToFile(void *args)
{
    auto acc = (Accumulator*)args;
    std::ofstream fout("out" + std::to_string(acc->id) + ".txt");

    fout<<acc->values.size();
    fout.close();

    delete acc;
    return nullptr;
}

int main(int argc, char **argv)
{
    if( argc != 4 )
    {
        std::cout<<"exec M R fileName\n";
        return 1;
    }

    int M = std::stoi(argv[1]);
    int R = std::stoi(argv[2]);
    std::ifstream fin(argv[3]);

    workpool mapperWorkpool, reducerWorkpool;

    int fileCount; fin>>fileCount;
    for( int i = 0; i < fileCount; i++ )
    {
        auto *mSpecs = new mapperSpecifications;
        mSpecs->reducerCount = R;
        fin>>mSpecs->fileName;

        mapperWorkpool.putTask({0, mSpecs, mapperJob});
    }

    mapperArgs mArgs {0, &mapperWorkpool, &reducerWorkpool, convert, nullptr};

    std::vector<reducerArgs> rArgs;
    for( int i = 0; i < R; i++ )
    {
        auto acc = new Accumulator;
        acc->id = i + 2;
        acc->values = std::set<int>();

        reducerArgs rArg {i + 2, &reducerWorkpool, acc, accumulate, writeToFile, nullptr};
        rArgs.push_back(rArg);
    }

    mapreduceArgs mrArgs {M, mArgs, R, rArgs};
    map_reduce::start(&mrArgs);

    return 0;
}
