#include <bits/stdc++.h>
#include "../Headers/FileReader.h"
const int N = 50;
using namespace std;
vector<MatchData> matches;
map<int, string> Nodes;
map<string, int> NodesName;
struct TeamStats {
    int points;
    int goal_difference;    // -----------> Goals Scored - Goals Encoded.
    int goalsScored, goalsEncoded;
};
map<string, TeamStats> standings;
struct MatchData {
    int roundNumber;
    string date;
    string homeTeam;
    string awayTeam;
    int homeGoals;
    int awayGoals;
    char result;
};
struct MatchDataForGraph{
    int team, roundNumber, homeGoals, awayGoals;
    char result;
};
vector<MatchDataForGraph> Graph[N];

void MakeGraph(){
    for(MatchData i : matches){
        Graph[NodesName[i.homeTeam]].push_back({NodesName[i.awayTeam], i.roundNumber, i.homeGoals, i.awayGoals, i.result});
    }
}
void printGraph(){
    for (int i = 0; i <= 20; i++){
        cout << Nodes[i] << '\t';
        for(MatchDataForGraph x : Graph[i]){
            cout << Nodes[x.team] << ' ' << x.roundNumber << ' ' << x.homeGoals << ' ' << x.awayGoals << ' ' << x.result << '\n';
        }
    }
    
}

void MakeNodes(){
    int CurrentRound(1), CurrentNode(1);
    for(MatchData i : matches){
        // cout << CurrentRound << ' ' << i.roundNumber << '\t';
        if(i.roundNumber < CurrentRound)    i.roundNumber = CurrentRound;
        else if(i.roundNumber > CurrentRound)   CurrentRound = i.roundNumber;
        if(NodesName[i.homeTeam] == 0){
            NodesName[i.homeTeam] = CurrentNode;
            Nodes[CurrentNode] = i.homeTeam;
            CurrentNode++;
        }   
        if(NodesName[i.awayTeam] == 0){
            NodesName[i.awayTeam] = CurrentNode;
            Nodes[CurrentNode] = i.awayTeam;
            CurrentNode++;
        }   
    }
    // for(MatchData i : matches){
    //     cout << i.roundNumber << '\t' << i.date << '\t' << i.homeTeam << '\t' << i.awayTeam << '\t' << i.homeGoals << '\t' << i.homeGoals << '\t' << i.result << '\n'; 
    // }
    // for(auto i : Nodes){
    //     cout << i.first << ' ' << i.second << '\n';
    // }
}
int main() {
    // matches = FileReaderx();
    matches = FileReaderx();
    MakeNodes();
    MakeGraph();
    printGraph();
    // Initialize standings
    
    return 0;
}
