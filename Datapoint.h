#pragma once
#include <string>
using namespace std;


struct Datapoint {
    string industryNAICS;         // NAICS code
    string industryTitle;
    string occupationCode;        // SOC code
    string occupationTitle;
    int avgSalary;                // Need to check if this is big enough
    double projJobGrowth;         // Use fractional (not percentage) representation
    string education;
    // work experience goes here      (possibly minimum number of years?)

    double ranking;               // This is used in sorting

    // Main constructors (just define here for now)
    Datapoint();

    Datapoint(string NAICS, string industryDesc, string SOC, string occupationDesc, 
    int averageSalary, double projectedGrowth, string educationLevel);

    // The default big three will be satisfactory

    bool operator<(const Datapoint& other);

    bool operator>(const Datapoint& other);

    bool operator<=(const Datapoint& other);

    bool operator>=(const Datapoint& other);

    // I.e., equal ranking, not equal in data points
    bool operator==(const Datapoint& other);

    bool operator!=(const Datapoint& other);
};