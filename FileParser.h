//
// Created by Mark Barbaric on 31/01/2021.
//

#ifndef GREEDY__MST__DP_FILEPARSER_H
#define GREEDY__MST__DP_FILEPARSER_H

struct Job {int weight = 0, length = 0;};

class FileParser {

protected:
    std::ifstream inputStream;

public:
    FileParser(const std::string& file){

        inputStream.open(file);
    }

    ~FileParser() {inputStream.close();}

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

class EdgeFileParser : public FileParser{
    std::vector<std::pair<int,int>> edges;
public:

    explicit EdgeFileParser(const std::string& file): FileParser(file){

    }

    void parseFile() override
    {
        if(inputStream) {
            std::string line;
            std::getline(inputStream, line);

            int numNodes = std::stoi(line);
            std::getline(inputStream, line);
            int numEdges = std::stoi(line);

            for (int i = 0; i < numEdges; ++i) {
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

#endif //GREEDY__MST__DP_FILEPARSER_H
