#include <bits/stdc++.h>
#include "../Headers/FileReader.h"

using namespace std;

struct MatchData {
    int roundNumber;
    string date;
    string homeTeam;
    string awayTeam;
    int homeGoals;
    int awayGoals;
    char result;
};
vector<MatchData> FileReaderx(){
    vector<MatchData> matchs;
    ifstream file("matches.csv");
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if(fields[4] == "-")    continue;
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
