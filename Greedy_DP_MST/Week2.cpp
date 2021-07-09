#include "UnionFind.h"
#include "Algorithms.h"
#include "../Helpers/FileParser.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>

inline long Clustering(const std::string& file)
{
    EdgeFileParser edgeFileParser(file);
    edgeFileParser.parseFile();
    auto edgeData = edgeFileParser.getEdges();
    std::sort(edgeData.begin(), edgeData.end(), [](const EdgeData& edgeData1, const EdgeData& edgeData2){
        return edgeData1.weight < edgeData2.weight;
    });

    UnionFind unionFind(edgeFileParser.getNumNodes());

    EdgeData toConnect;

    for(auto& e : edgeData){
        toConnect = e;
        unionFind.join(e.node1, e.node2);

        if(unionFind.getCount() == 4)
            break;
    }

    return toConnect.weight;
}


inline long ClusteringBig(const std::string& file)
{
    BigClusteringFileParser bigClusteringFileParser(file);
    bigClusteringFileParser.parseFile();
    auto edgeData = bigClusteringFileParser.getEdges();
    std::vector<int> distances_one = Algorithms::getHammingDistances(1, 24);
    std::vector<int> distances_two = Algorithms::getHammingDistances(2, 24);
    int num_edg_cost_one = 0;
    int num_edg_cost_two = 0;

    const int MAX_NODES = (int)std::pow(2, 24);
    auto m = bigClusteringFileParser.getMap();
    UnionFind unionFind(MAX_NODES);


    // iterate through the map and find the neighbors
    for (auto& el : m)
    {
        el.second = true;           // we won't bother to add already seen edge to UnionFind

        for (auto d : distances_one)
        {
            int res = el.first ^ d;
            auto exists = m.find(res);

            if (exists != m.end() && !exists->second) // if it's found but not yet seen!
            {
                // add to UF (there is an edge from current element to the one 1 Hamming distance away)
                num_edg_cost_one++;
                unionFind.join(exists->first, el.first);
            }
        }
        for (auto d : distances_two)
        {
            int res = el.first ^ d;
            auto exists = m.find(res);
            if (exists != m.end() && !exists->second)
            {
                // add node connected to current one 2 Hamming distances away
                num_edg_cost_two++;
                unionFind.join(exists->first, el.first);
            }
        }
    }
    // from total number of nodes (all clusters)
    // subtract leaders (clusters with nodes that are at most 2 Hamming distances away from each other)
    // and duplicated nodes to get number of clusters that are at least 3 Hamming distances away from others

    size_t totalNumberClusters = edgeData.size() - (MAX_NODES - unionFind.getCount()) - (edgeData.size() - m.size());
    std::cout << "Edges 1 Hamming distance away: " << num_edg_cost_one << std::endl;
    std::cout << "Edges 2 Hamming distances away: " << num_edg_cost_two << std::endl;
    assert(totalNumberClusters == 6118);
    return totalNumberClusters;
}

inline void Week2()
{
    std::cout << "Week 2.\n" << std::endl;
    auto ans1 = Clustering("../Greedy_DP_MST/Data/clustering.txt");
    std::cout << "The answer to question one is: " << ans1 << std::endl;
    auto ans2 = Clustering("../Greedy_DP_MST/Data/clustering2.txt");
    std::cout << "The answer to question one is: " << ans2 << std::endl;
    auto ans3 = ClusteringBig("../Greedy_DP_MST/Data/clustering_big.txt");
    std::cout << "The answer to question two is: " << ans3 << std::endl;
}