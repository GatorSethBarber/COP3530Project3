#include "Datapoint.h"
#include<iostream>
#include <map>

/**
 * Proposed fields
 *  * NAICs code
 *  * SOC (occupation code)
 *  * average salaries
 *  * projected job growth
 *  * education requirements
 *  * work experience needed
*/

/**
 * Constructor for the Datapoint struct
 */
Datapoint::Datapoint() {
    industryNAICS = "0";
    occupationCode = "0";
    avgSalary = 0;
    projJobGrowth = 0.0;
    education = 0;
    workExperience = 0;
    ranking = 0.0;
}

Datapoint::Datapoint(string SOC, string NAICS, double averageSalary, double projectedGrowth, int edu
, int work)
{
    occupationCode = SOC;
    industryNAICS = NAICS;
    avgSalary = averageSalary;
    projJobGrowth = projectedGrowth;
    education = edu;
    workExperience = work;
    ranking = 0.0;      
}


/**
 * Print some information associated with the Datapoint
*/
void Datapoint::print(map<string, string> occupations)
{
    cout << occupations[occupationCode] << " " << industryNAICS << endl;
}

// The operators compare the rankings of the Datapoints
bool Datapoint::operator<(const Datapoint& other) {
    return ranking < other.ranking;
}

bool Datapoint::operator>(const Datapoint& other) {
    return ranking > other.ranking;
}

bool Datapoint::operator<=(const Datapoint& other) {
    return ranking <= other.ranking;
}

bool Datapoint::operator>=(const Datapoint& other) {
    return ranking >= other.ranking;
}

// I.e., equal ranking, not equal in data points
bool Datapoint::operator==(const Datapoint& other) {
    return ranking == other.ranking;
}

bool Datapoint::operator!=(const Datapoint& other) {
    return ranking != other.ranking;
}
