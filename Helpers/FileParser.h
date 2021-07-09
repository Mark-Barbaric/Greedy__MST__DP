#ifndef GREEDY__MST__DP_FILEPARSER_H
#define GREEDY__MST__DP_FILEPARSER_H

#include <fstream>
#include <sstream>
#include <vector>
#include <map>

struct Job {int weight = 0, length = 0;};

class FileParser {

protected:
    std::ifstream inputStream;

public:
    explicit FileParser(const std::string& file){

        inputStream.open(file);
    }

    virtual ~FileParser() {inputStream.close();}

    virtual void parseFile() = 0;
};

class JobFileParser : FileParser
{
    std::vector<Job> jobs;
public:
    explicit JobFileParser(const std::string& file): FileParser(file){

    }

    void parseFile() override
    {
        if(inputStream) {
            std::string line;
            std::getline(inputStream, line);

            int n = std::stoi(line);

            for (int i = 0; i < n; ++i) {
                std::getline(inputStream, line);
                std::stringstream ss(line);
                std::string segment;
                Job job;
                std::getline(ss, segment, ' ');
                job.weight = std::stoi(segment);
                std::getline(ss, segment, ' ');
                job.length = std::stoi(segment);
                jobs.push_back(job);
            }
        }
    }

    std::vector<Job> getJobs() const noexcept {return jobs;}
};

struct EdgeData {int node1 = 0, node2 = 0;
    long weight = 0;};

class EdgeFileParser : public FileParser{
    std::vector<EdgeData> edges;
    int numNodes = 0;
public:

    explicit EdgeFileParser(const std::string& file): FileParser(file){

    }

    void parseFile() override
    {
        if(inputStream) {
            std::string line;
            std::getline(inputStream, line);

            std::stringstream fs (line);
            std::string seg1;

            std::getline(fs, seg1, ' ');
            numNodes = std::stoi(seg1) + 1;
            std::getline(fs, seg1, ' ');
            int numEdges = std::stoi(seg1);

            for (int i = 0; i < numEdges; ++i) {
                std::getline(inputStream, line);
                std::stringstream ss(line);
                std::string segment;
                EdgeData edgeData;
                std::getline(ss, segment, ' ');
                edgeData.node1 = std::stoi(segment);
                std::getline(ss, segment, ' ');
                edgeData.node2 = std::stoi(segment);
                std::getline(ss, segment, ' ');
                edgeData.weight = std::stoi(segment);
                edges.push_back(edgeData);
            }
        }
    }

    std::vector<EdgeData> getEdges() const noexcept {return edges;}
    int getNumNodes() const noexcept {return numNodes;}
};

class BigClusteringFileParser : public FileParser
{
    std::vector<long> edges;
    std::map<long,bool> m;

public:
    explicit BigClusteringFileParser(const std::string& file): FileParser(file){

    }

    void parseFile() override
    {
        if(inputStream) {
            std::string line;
            std::getline(inputStream, line);

            std::stringstream fs (line);
            std::string seg1;
            std::getline(fs, seg1, ' ');
            int numEdges = std::stoi(seg1);

            for (int i = 0; i < numEdges; ++i) {

                std::getline(inputStream, line);
                line.erase(std::remove_if(line.begin(), line.end(), [](char x) {return std::isspace(x); }), end(line));
                std::bitset<24> bitNode(line);
                const auto nodeNumber = bitNode.to_ulong();
                edges.push_back(nodeNumber);
                m[nodeNumber] = false;
            }
        }
    }

    std::vector<long> getEdges() const {return edges;}
    std::map<long, bool> getMap() const {return m;}

};

#endif //GREEDY__MST__DP_FILEPARSER_H
