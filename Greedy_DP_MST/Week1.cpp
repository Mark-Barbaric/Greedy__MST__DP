#include <iostream>
#include "../Helpers/FileParser.h"
#include "Algorithms.h"

inline long RunGreedySort(const std::string& file, bool optimal)
{
    JobFileParser jobFileParser(file);
    jobFileParser.parseFile();
    auto jobs = jobFileParser.getJobs();
    return Algorithms::greedySort(jobs, optimal);
}

inline long RunPrimsMST(const std::string& file, bool optimised)
{
    EdgeFileParser edgeFileParser(file);
    edgeFileParser.parseFile();
    const auto edgeData = edgeFileParser.getEdges();
    return optimised ? Algorithms::primsMSTOptimised(edgeFileParser.getNumNodes(), edgeData) : Algorithms::primsMST(edgeFileParser.getNumNodes(), edgeData);
}

inline void Week1()
{
    std::cout << "Week 1.\n" << std::endl;
    auto ans1 = RunGreedySort("../Greedy_DP_MST/Data/job2.txt", false);
    std::cout << "The answer to question one is: " << ans1 << std::endl;
    auto ans2 = RunGreedySort("../Greedy_DP_MST/Data/job1.txt", false);
    std::cout << "The answer to question one is: " << ans2 << std::endl;
    auto ans3 = RunGreedySort("../Greedy_DP_MST/Data/job2.txt", true);
    std::cout << "The answer to question two is: " << ans3 << std::endl;
    auto ans4 = RunGreedySort("../Greedy_DP_MST/Data/job1.txt", true);
    std::cout << "The answer to question two is: " << ans4 << std::endl;
    auto ans5 = RunPrimsMST("../Greedy_DP_MST/Data/edges2.txt", false);
    std::cout << "The answer to question three is: " << ans5 << std::endl;
    auto ans6 = RunPrimsMST("../Greedy_DP_MST/Data/edges1.txt", false);
    std::cout << "The answer to question three is: " << ans6 << std::endl;
    auto ans7 = RunPrimsMST("../Greedy_DP_MST/Data/edges2.txt", true);
    std::cout << "The answer to question three is: " << ans7 << std::endl;
    auto ans8 = RunPrimsMST("../Greedy_DP_MST/Data/edges1.txt", true);
    std::cout << "The answer to question three is: " << ans8 << std::endl;
    std::cout << "\n" << std::endl;
}