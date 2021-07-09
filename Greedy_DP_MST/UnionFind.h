
#ifndef GREEDY__MST__DP_UNIONFIND_H
#define GREEDY__MST__DP_UNIONFIND_H

#include <vector>

class UnionFind
{
    std::vector<int> parent;
    std::vector<int> rank;
    std::vector<int> values;
    int count = 0;

public:
    explicit UnionFind(int n)
    {
        parent.resize(n, 0);
        rank.resize(n, 0);
        count = n;

        for(int i = 1; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int i)
    {
        if(i == parent[i]){
            return i;
        } else {
            return find(parent[i]);
        }
    }

    void join(int u, int v)
    {
        const auto s1 = find(u);
        const auto s2 = find(v);

        if(s1 == s2){
            return;
        }

        if(rank[s1] > rank[s2]){
            parent[s2] = s1;
        } else if(rank[s1] < rank[s2]){
            parent[s1] = s2;
        } else {
            rank[s1]++;
            parent[s2] = s1;
        }

        count--;
    }

    bool connected(int u, int v) {return find(u) == find(v);}

    int getCount () const noexcept {return count;}

};

#endif //GREEDY__MST__DP_UNIONFIND_H
