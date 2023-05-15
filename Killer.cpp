#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "FileReader.h"

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

struct TeamStats {
    int points;
    int goal_difference;    // -----------> Goals Scored - Goals Encoded.
};

int main() {
    vector<MatchData> matches;
    // matches = FileReaderx();
    FileReaderx();
    for (int i = 0; i < 5; i++){
        cout << matches[i].date << ' ';
    }
    // Initialize standings
    map<string, TeamStats> standings;
    
    return 0;
}
