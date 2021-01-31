//
// Created by Mark Barbaric on 31/01/2021.
//

#ifndef GREEDY__MST__DP_ALGORITHMS_H
#define GREEDY__MST__DP_ALGORITHMS_H

#include "FileParser.h"

namespace Algorithms
{
    inline bool CustomComparator1(Job& job1, Job& job2)
    {
        const auto diff1 = job1.weight - job1.length;
        const auto diff2 = job2.weight - job2.length;

        if(diff1 > diff2){
            return true;
        } else if(diff1 < diff2){
            return false;
        } else {
            return job1.weight > job2.weight;
        }

    }

    inline bool CustomComparator2(Job& job1, Job& job2)
    {
        const auto ratio1 = static_cast<double>(job1.weight) / static_cast<double>(job1.length);
        const auto ratio2 = static_cast<double>(job2.weight) / static_cast<double>(job2.length);
        return ratio1 > ratio2;
    }

    inline long greedySort(std::vector<Job>& jobs, bool optimal)
    {
        auto Comparator = optimal ? CustomComparator2 : CustomComparator1;
        std::sort(jobs.begin(), jobs.end(), Comparator);

        long curTime = 0, total = 0;

        for(auto& j : jobs){

            total += (curTime + j.length) * j.weight;
            curTime += j.length;
        }

        return total;
    }

}


#endif //GREEDY__MST__DP_ALGORITHMS_H
