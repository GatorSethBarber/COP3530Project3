#pragma once
#include <vector>
#include <string>
#include <map>
using namespace std;


struct Datapoint {
    string industryNAICS;         // NAICS code
    string occupationCode;        // SOC code
    double avgSalary;                // Need to check if this is big enough
    double projJobGrowth;         // Use fractional (not percentage) representation
    int education;
    int workExperience;
    double ranking;               // This is used in sorting

    // Main constructors (just define here for now)
    Datapoint();

    Datapoint(string SOC, string NAICS, double averageSalary, double projectedGrowth, int edu, int work);

    // The default big three will be satisfactory

    void print(map<string, string> occupations);

    bool operator<(const Datapoint& other);

    bool operator>(const Datapoint& other);

    bool operator<=(const Datapoint& other);

    bool operator>=(const Datapoint& other);

    // I.e., equal ranking, not equal in data points
    bool operator==(const Datapoint& other);

    bool operator!=(const Datapoint& other);
};