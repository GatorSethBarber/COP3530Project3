#include "Datapoint.h"
#include<iostream>


/**
 * Proposed fields
 *  * NAICs code
 *  * SOC (occupation code)
 *  * average salaries
 *  * projected job growth
 *  * education requirements
 *  * work experience needed
*/

Datapoint::Datapoint() {
    industryNAICS = "0";
    industryTitle = "None";
    occupationCode = "0";
    occupationTitle = "None";
    avgSalary = 0;
    projJobGrowth = 0.0;
    ranking = 0.0;
}

Datapoint::Datapoint(string SOC, string NAICS, double averageSalary, double projectedGrowth, int edu)
{
    occupationCode = SOC;
    industryNAICS = NAICS;
    avgSalary = averageSalary;
    projJobGrowth = projectedGrowth;
    education = edu;
    ranking = 0.0;      
}

/*
Datapoint::Datapoint(string NAICS, string industryDesc, string SOC, string occupationDesc, 
int averageSalary, double projectedGrowth, string educationLevel) {
    // Going to assume data is ok. May want to add checks in
    industryNAICS = NAICS;
    industryTitle = industryDesc;
    occupationCode = SOC;
    occupationTitle = occupationDesc;
    avgSalary = averageSalary;
    projJobGrowth = projectedGrowth;
    education = educationLevel;
    ranking = 0.0;                                 // Ranking needs to be applied later
}
*/
    // The default big three will be satisfactory

string Datapoint::getIndustryNAICS()
{
    return this->industryNAICS;
}
void Datapoint::print()
{
    cout << occupationCode << endl;
}

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
