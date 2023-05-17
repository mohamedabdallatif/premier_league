#include <bits/stdc++.h>
#include "../Headers/FileReader.h"
const int N = 50;
using namespace std;
vector<MatchData> matches;
map<int, string> Nodes;
map<string, int> NodesName;
int Visited[N];
int RoundNumber, Date;
struct TeamStats{
    int points;
    int goal_difference;
    int goalsScored;
    int goalsEncoded;
    int teamNode;
    int MatchPlayed;
    int W;
    int D;
    int L;
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
    int Awayteam;
    int date;
    int roundNumber;
    int homeGoals;
    int awayGoals;
    char result;
};
vector<MatchDataForGraph> Graph[N];
void init(){
    Standing.clear();   
    memset(Visited, 0, sizeof Visited);
}
int Converter(string date){

}
void MakeGraph(){
    for(MatchData i : matches){
        Graph[NodesName[i.homeTeam]].push_back({NodesName[i.awayTeam], Converter(i.date), i.roundNumber, i.homeGoals, i.awayGoals, i.result});
    }
}
void Stand(int winner, int loser, MatchDataForGraph Edge, char Result){
    if(Result == 'H' || Result == 'A'){
        Standing[winner].points += 3;
        Standing[winner].W++;
        Standing[loser].L++;
    }
    else{
        Standing[winner].points += 1;
        Standing[loser].points += 1;
        Standing[loser].D++;
    }
    Standing[winner].MatchPlayed++;
    Standing[loser].MatchPlayed++;
    if(Result == 'H'){
        Standing[winner].goalsScored += Edge.homeGoals;
        Standing[loser].goalsScored+= Edge.awayGoals;
        Standing[winner].goalsEncoded += Edge.awayGoals;
        Standing[loser].goalsEncoded += Edge.homeGoals;
    }
    else{
        Standing[winner].goalsScored += Edge.Awayteam;
        Standing[loser].goalsScored+= Edge.homeGoals;
        Standing[winner].goalsEncoded += Edge.homeGoals;
        Standing[loser].goalsEncoded += Edge.awayGoals;
    }
}
void printGraph(){
    for (int i = 0; i <= 20; i++){
        cout << Nodes[i] << '\t';
        for(MatchDataForGraph x : Graph[i]){
            cout << Nodes[x.Awayteam] << ' ' << x.roundNumber << ' ' << x.homeGoals << ' ' << x.awayGoals << ' ' << x.result << '\n';
        }
        cout << "\n\n\n";
    }
    
}
void BFS(int x, int condition){
    if(condition == 1){   
        queue<int> q;
        Visited[x] = 1;
        while (q.size()){
            int P = q.front();
            q.pop();
            for(MatchDataForGraph i : Graph[P]){
                if(i.roundNumber < RoundNumber){
                    if (i.result == 'H')    Stand(P, i.Awayteam, i, 'H');
                    else if (i.result == 'A')   Stand(i.Awayteam, P, i, 'A');
                    else    Stand(P, i.Awayteam, i, 'D');
                }
                if(!Visited[i.Awayteam])    q.push(i.Awayteam); 
            }
        }
    }
    else{   
        queue<int> q;
        Visited[x] = 1;
        while (q.size()){
            int P = q.front();
            q.pop();
            for(MatchDataForGraph i : Graph[P]){
                if(i.date < Date){
                    if (i.result == 'H')    Stand(P, i.Awayteam, i, 'H');
                    else if (i.result == 'A')   Stand(i.Awayteam, P, i, 'A');
                    else    Stand(P, i.Awayteam, i, 'D');
                }
                if(!Visited[i.Awayteam])    q.push(i.Awayteam); 
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
    for (int i = 1; i < N; i++){
        Standing[i].teamNode = i;
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
    // printGraph();
    int Condition, What;
    cout << "Round(1) or Date(2)? ";
    while (cin >> Condition){
        init();
        if(Condition == 1)  cin >> RoundNumber;
        else if(Condition == 2)  cin >> Date;
        else    return 0;
        for (int i = 1; i <= 38; i++){
            if(!Visited[i])     BFS(i, Condition);
        }   
        // Sorting
        // Print Standing
        cout << "Round(1) or Date(2)? ";
    }
    return 0;
}

