#ifndef GREEDY__MST__DP_ALGORITHMS_H
#define GREEDY__MST__DP_ALGORITHMS_H

#include <queue>
#include <list>
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

    inline int getMinimum(std::vector<long>& distance, std::vector<bool>& inMST)
    {
        auto min = LONG_MAX;
        auto u = -1;

        for(int i = 1; i < distance.size(); ++i)
        {
            if(distance[i] <= min && !inMST[i])
            {
                min = distance[i];
                u = i;
            }
        }

        return u;
    }

    inline long primsMST(int n, const std::vector<EdgeData>& edgeData)
    {
        std::vector<std::vector<long>> adj (n, std::vector<long> (n, 0));

        for(auto& e : edgeData)
        {
            adj[e.node1][e.node2] = e.weight;
            adj[e.node2][e.node1] = e.weight;
        }

        std::vector<long> key (n, LONG_MAX);
        std::vector<bool> inMST (n, false);
        key[1] = 0;

        for(int i = 1; i < n - 1; ++i)
        {
            const auto u = getMinimum(key, inMST);
            inMST[u] = true;

            for(int v = 1; v < n; ++v)
            {
                if(adj[u][v] && !inMST[v] && adj[u][v] < key[v])
                {
                    key[v] = adj[u][v];
                }

            }

        }

        long cost = 0;

        for(auto& k : key)
        {
            if(k != LONG_MAX)
                cost += k;
        }

        return cost;
    }


    inline long primsMSTOptimised(int n, const std::vector<EdgeData>& edgeData)
    {
        std::vector<std::vector<long>> adj (n, std::vector<long> (n, 0));

        for(auto& e : edgeData)
        {
            adj[e.node1][e.node2] = e.weight;
            adj[e.node2][e.node1] = e.weight;
        }

        std::vector<long> key (n, LONG_MAX);
        std::vector<bool> inMST (n, false);
        std::priority_queue<std::pair<long,int>, std::vector<std::pair<long,int>>, std::greater<std::pair<long,int>>> q;
        q.push({0, 1});
        key[1] = 0;

        while(!q.empty())
        {
            const auto cur = q.top();
            const auto u = cur.second;
            q.pop();

            if(!inMST[u])
            {
                inMST[u] = true;

                for(int v = 1; v < n; ++v)
                {
                    if(adj[u][v] && !inMST[v] && adj[u][v]  < key[v])
                    {
                        key[v] = adj[u][v];
                        q.push({key[v], v});
                    }

                }
            }
        }

        long cost = 0;

        for(auto& k : key)
        {
            if(k != LONG_MAX)
                cost += k;
        }

        return cost;
    }

}


#endif //GREEDY__MST__DP_ALGORITHMS_H
