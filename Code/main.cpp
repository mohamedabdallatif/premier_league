#include <bits/stdc++.h>
#include "../Headers/FileReader.h"
const int N = 50;
using namespace std;
vector<MatchData> matches;
map<int, string> Nodes;
map<string, int> NodesName;
int RoundNumber, Visited[N];
struct TeamStats{
    int points;
    int goal_difference;    // -----------> Goals Scored - Goals Encoded.
    int goalsScored, goalsEncoded;
    int teamNode;
};
vector<TeamStats> Standing(N);
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
        cout << "\n\n\n";
    }
    
}
void DFS(int x){
    if(Visited[x] == 2)     return;
    Visited[x] = 1;
    for(auto i : Graph[x]){
        if(i.roundNumber <= RoundNumber){
            if (i.result == 'H')    Standing[x].points += 3;
            else if (i.result == 'A')   Standing[i.team].points += 3;
            else{
            Standing[x].points += 1;
            Standing[x].points += 1;
            if(Visited[i.team] == 0)     DFS(i.team);
        }

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
    // while (cin >> RoundNumber){
    //     if(RoundNumber < 1 || RoundNumber > 38)     return 0;
    //     for (int i = 1; i <= 38; i++){
    //         if(!Visited[i])     DFS(i);
    //     }   
    // }
        
    return 0;
}
