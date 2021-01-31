#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "FileParser.h"
#include "Algorithms.h"

long RunGreedySort(const std::string& file, bool optimal)
{
    JobFileParser jobFileParser(file);
    jobFileParser.parseFile();
    auto jobs = jobFileParser.getJobs();
    return Algorithms::greedySort(jobs, optimal);
}

long RunPrimsMST(const std::string& file, bool optimised)
{
    EdgeFileParser edgeFileParser(file);
    edgeFileParser.parseFile();
    const auto edgeData = edgeFileParser.getEdges();
    return optimised ? Algorithms::primsMSTOptimised(edgeFileParser.getNumNodes(), edgeData) : Algorithms::primsMST(edgeFileParser.getNumNodes(), edgeData);
}

int main() {

    auto ans1 = RunGreedySort("../job2.txt", false);
    std::cout << "The answer to question one is: " << ans1 << std::endl;
    auto ans2 = RunGreedySort("../job1.txt", false);
    std::cout << "The answer to question one is: " << ans2 << "\n" << std::endl;
    auto ans3 = RunGreedySort("../job2.txt", true);
    std::cout << "The answer to question two is: " << ans3 << std::endl;
    auto ans4 = RunGreedySort("../job1.txt", true);
    std::cout << "The answer to question two is: " << ans4 << "\n" << std::endl;
    auto ans5 = RunPrimsMST("../edges2.txt", false);
    std::cout << "The answer to question three is: " << ans5 << "\n" << std::endl;
    auto ans6 = RunPrimsMST("../edges1.txt", false);
    std::cout << "The answer to question three is: " << ans6 << "\n" << std::endl;
    auto ans7 = RunPrimsMST("../edges2.txt", true);
    std::cout << "The answer to question three is: " << ans7 << "\n" << std::endl;
    auto ans8 = RunPrimsMST("../edges1.txt", true);
    std::cout << "The answer to question three is: " << ans8 << "\n" << std::endl;


    return 0;
}
