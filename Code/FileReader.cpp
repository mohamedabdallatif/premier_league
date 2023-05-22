#include <bits/stdc++.h>
#include "../Headers/FileReader.h"

using namespace std;

vector<MatchData> FileReaderx() 
{
    vector<MatchData> matchs;
    // used to create an input file stream object "file" and associate it with 
    // the file "epl_results.csv" for reading data from the file.
    ifstream file("epl_results.csv");
    string line; // represent each row in matches input
    getline(file, line); // taking first line from table which represent columns headlines - ignore it
    while (getline(file, line))
    {
        // used to create a string stream object "ss" and initialize 
        // it with the string "line".
        stringstream ss(line);
        string field;
        vector<string> fields;
        // loop over all fields in each row and parse every coulmn by seperated comma ','
        while (getline(ss, field, ','))
            fields.push_back(field);
        // neglected input from home goals
        if (fields[4] == "-")
            continue;
        // create an entry for current match in generated graph
        MatchData match;
        match.roundNumber = stoi(fields[0]);
        match.date = fields[1];
        match.homeTeam = fields[2];
        match.awayTeam = fields[3];
        match.homeGoals = stoi(fields[4]);
        match.awayGoals = stoi(fields[5]);
        match.result = fields[6][0];
        // insert it beside other matches
        matchs.push_back(match);
    }
    return matchs;
}
