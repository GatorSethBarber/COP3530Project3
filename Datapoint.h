#pragma once
#include <vector>
#include <string>
#include <map>
using namespace std;


struct Datapoint {
    string industryNAICS;         // NAICS code
    string occupationCode;        // SOC code
    double avgSalary;             // Average salary
    double projJobGrowth;         // Projected job growth
    int education;                // Average education needed
    int workExperience;           // Work experience needed
    double ranking;               // This is used to sort

    // Main constructors
    Datapoint();

    Datapoint(string SOC, string NAICS, double averageSalary, double projectedGrowth, 
    int edu, int work);

    void print(map<string, string> occupations, map<string, string> industries);

    bool operator<(const Datapoint& other);

    bool operator>(const Datapoint& other);

    bool operator<=(const Datapoint& other);

    bool operator>=(const Datapoint& other);

    // I.e., equal ranking, not equal in data points
    bool operator==(const Datapoint& other);

    bool operator!=(const Datapoint& other);
};