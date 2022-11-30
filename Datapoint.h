#pragma once
#include <string>
using namespace std;



/**
 * Proposed fields
 *  * NAICs code
 *  * SOC (occupation code)
 *  * average salaries
 *  * projected job growth
 *  * education requirements
 *  * work experience needed
*/
struct Datapoint {
    string industryNAICS;         // NAICS code
    string occupationCode;        // SOC code
    double avgSalary;                // Need to check if this is big enough
    double projJobGrowth;         // Use fractional (not percentage) representation
    int education;
    // work experience goes here      (possibly minimum number of years?)
    //industry title
    double ranking;               // This is used in sorting

    // Main constructors (just define here for now)
    Datapoint() {
        industryNAICS = "0";
        occupationCode = "0";
        avgSalary = 0;
        projJobGrowth = 0.0;
        ranking = 0.0;
    }

    Datapoint(string SOC, string NAICS, double averageSalary, double projectedGrowth, int edu) {
        // Going to assume data is ok. May want to add checks in
        occupationCode = SOC;
        industryNAICS = NAICS;
        avgSalary = averageSalary;
        projJobGrowth = projectedGrowth;
        education = edu;
        ranking = 0.0;                                 // Ranking needs to be applied later
    }

    // The default big three will be satisfactory

    bool operator<(const Datapoint& other) {
        return ranking < other.ranking;
    }

    bool operator>(const Datapoint& other) {
        return ranking > other.ranking;
    }

    bool operator<=(const Datapoint& other) {
        return ranking <= other.ranking;
    }

    bool operator>=(const Datapoint& other) {
        return ranking >= other.ranking;
    }

    // I.e., equal ranking, not equal in data points
    bool operator==(const Datapoint& other) {
        return ranking == other.ranking;
    }

    bool operator!=(const Datapoint& other) {
        return ranking != other.ranking;
    }
};