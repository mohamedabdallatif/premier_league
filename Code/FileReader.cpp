#include <bits/stdc++.h>
#include "../Headers/FileReader.h"

using namespace std;

vector<MatchData> FileReaderx()
{
    vector<MatchData> matchs;
    ifstream file("epl_results.csv");                   // used to create an input file stream object "file" and associate it with the file "epl_results.csv" for reading data from the file.
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);                          // used to create a string stream object "ss" and initialize it with the string "line".
        string field;
        vector<string> fields;
        while (getline(ss, field, ','))
        {
            fields.push_back(field);
        }
        if (fields[4] == "-")
            continue;
        MatchData match;
        match.roundNumber = stoi(fields[0]);
        match.date = fields[1];
        match.homeTeam = fields[2];
        match.awayTeam = fields[3];
        match.homeGoals = stoi(fields[4]);
        match.awayGoals = stoi(fields[5]);
        match.result = fields[6][0];
        matchs.push_back(match);
    }
    return matchs;
}
