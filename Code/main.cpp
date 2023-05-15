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

struct TeamStats {
    int points;
    int goal_difference;    // -----------> Goals Scored - Goals Encoded.
};
void Printer(vector<MatchData> matches){
    for(auto i : matches){
        cout << i.roundNumber << '\t' << i.date << '\t' << i.homeTeam << '\t' << i.awayTeam << '\t' << i.homeGoals << '\t' << i.homeGoals << '\t' << i.result << '\n'; 
    }
}
int main() {
    vector<MatchData> matches;
    // matches = FileReaderx();
    matches = FileReaderx();
    Printer(matches);
    // Initialize standings
    map<string, TeamStats> standings;
    
    return 0;
}
