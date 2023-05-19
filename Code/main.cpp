#include <bits/stdc++.h>
#include <iomanip> // for setw()

#include "../Headers/FileReader.h"
const int N = 50;
#define ll long long
using namespace std;
string MeaningDate;    
vector<MatchData> matches;
unordered_map<int, string> Nodes;
unordered_map<string, int> NodesName;
int Visited[N];
int RoundNumber, Date;
vector<TeamStats> Standing(N);
vector<MatchDataForGraph> Graph[N];
void init(){
    Date = 0;
    RoundNumber = 0;
    for (int i = 0; i < N; i++){
        Standing[i].D = 0;
        Standing[i].goalsEncoded = 0;
        Standing[i].goalsScored = 0;
        Standing[i].L = 0;
        Standing[i].MatchPlayed = 0;
        Standing[i].points = 0;
        Standing[i].teamNode = i;
        Standing[i].W = 0;
    }
    memset(Visited, 0, sizeof(Visited));
}
bool sortBy(TeamStats &a, TeamStats &b){
    int diffGoalsA = (a.goalsScored - a.goalsEncoded), diffGoalsB = (b.goalsScored - b.goalsEncoded);
    if (a.points != b.points)
        return (a.points > b.points);
    else if (diffGoalsA != diffGoalsB)
        return (diffGoalsA > diffGoalsB);
    else if (a.goalsScored != b.goalsScored)
        return (a.goalsScored > b.goalsScored);
    else if (a.goalsEncoded != b.goalsEncoded)
        return (a.goalsEncoded < b.goalsEncoded);
    return (Nodes[a.teamNode] < Nodes[b.teamNode]);
}
int Converter(string date){
    stringstream ss(date);
    string SubStr;
    getline(ss, SubStr, '/'); 
    ll day = stoi(SubStr);
    getline(ss, SubStr, '/'); 
    ll month = stoi(SubStr);
    getline(ss, SubStr, '/'); 
    ll year = stoi(SubStr);
    ll dateIntFormat = (year * 10000) + (month * 100) + day;
    return dateIntFormat;
}
void Sorting(){   
    sort(Standing.begin(), Standing.end(), sortBy);
}
void MakeGraph(){
    for (MatchData i : matches){
        Graph[NodesName[i.homeTeam]].push_back({NodesName[i.awayTeam], Converter(i.date), i.roundNumber, i.homeGoals, i.awayGoals, i.result});
    }
}
void Stand(int winner, int loser, MatchDataForGraph Edge, char Result){
    if (Result == 'H' || Result == 'A'){
        Standing[winner].points += 3;
        Standing[winner].W++;
        Standing[loser].L++;
    }
    else{
        Standing[winner].points += 1;
        Standing[loser].points += 1;
        Standing[winner].D++;
        Standing[loser].D++;
    }
    Standing[winner].MatchPlayed++;
    Standing[loser].MatchPlayed++;
    if (Result == 'H'){
        Standing[winner].goalsScored += Edge.homeGoals;
        Standing[loser].goalsScored += Edge.awayGoals;
        Standing[winner].goalsEncoded += Edge.awayGoals;
        Standing[loser].goalsEncoded += Edge.homeGoals;
    }
    else{
        Standing[winner].goalsScored += Edge.awayGoals;
        Standing[loser].goalsScored += Edge.homeGoals;
        Standing[winner].goalsEncoded += Edge.homeGoals;
        Standing[loser].goalsEncoded += Edge.awayGoals;
    }
}
void PrintStanding(){
    cout << "Premier League Standings Untill ";
    if (Date)
        cout << MeaningDate;
    else
        cout << "Round " << RoundNumber << '\n';
    cout << "|**************************|***********|*****|*****|*****|*****|*****|*****|*****|\n";
    cout << "|Team                      |MatchPlayed|  W  |  D  |  L  | GF  | GA  | GD  | Pts |\n";
    cout << "|**************************|***********|*****|*****|*****|*****|*****|*****|*****|\n";
    for (TeamStats team : Standing){
        if (Nodes[team.teamNode].empty())
            continue;
        cout << '|' << left << setw(26) << Nodes[team.teamNode] << "|";
        cout << right << setw(11) << team.MatchPlayed << "|";
        cout << right << setw(5) << team.W << "|";
        cout << right << setw(5) << team.D << "|";
        cout << right << setw(5) << team.L << "|";
        cout << right << setw(5) << team.goalsScored << "|";
        cout << right << setw(5) << team.goalsEncoded << "|";
        cout << right << setw(5) << team.goalsScored - team.goalsEncoded << "|";
        cout << right << setw(5) << team.points << "|\n";
        cout << "|--------------------------|-----------|-----|-----|-----|-----|-----|-----|-----|\n";
    }
}
void BFS(int x, int condition){
    queue<int> q;
    Visited[x] = 1;
    q.push(x);
    if (condition == 1)
    {
        while (q.size())
        {
            int P = q.front();
            q.pop();
            for (MatchDataForGraph i : Graph[P])
            {
                if (i.roundNumber <= RoundNumber)
                {
                    if (i.result == 'H')
                        Stand(P, i.Awayteam, i, 'H');
                    else if (i.result == 'A')
                        Stand(i.Awayteam, P, i, 'A');
                    else
                        Stand(P, i.Awayteam, i, 'D');
                }
                if (!Visited[i.Awayteam])
                {
                    Visited[i.Awayteam] = 1;
                    q.push(i.Awayteam);
                }
            }
        }
    }
    else{
        while (q.size())
        {
            int P = q.front();
            q.pop();
            for (MatchDataForGraph i : Graph[P])
            {
                if (i.date <= Date)
                {
                    if (i.result == 'H')
                        Stand(P, i.Awayteam, i, 'H');
                    else if (i.result == 'A')
                        Stand(i.Awayteam, P, i, 'A');
                    else
                        Stand(P, i.Awayteam, i, 'D');
                }
                if (!Visited[i.Awayteam])
                {
                    Visited[i.Awayteam] = 1;
                    q.push(i.Awayteam);
                }
            }
        }
    }
}

void UpdateRounds(){
    int CurrentRound(1), CurrentNode(1);
    for (MatchData& i : matches){
        if (i.roundNumber < CurrentRound){
            i.roundNumber = CurrentRound;
        }else if (i.roundNumber > CurrentRound)
            CurrentRound = i.roundNumber;
        if (NodesName[i.homeTeam] == 0){
            NodesName[i.homeTeam] = CurrentNode;
            Nodes[CurrentNode] = i.homeTeam;
            CurrentNode++;
        }
        if (NodesName[i.awayTeam] == 0){
            NodesName[i.awayTeam] = CurrentNode;
            Nodes[CurrentNode] = i.awayTeam;
            CurrentNode++;
        }
    }
}
int main(){
    matches = FileReaderx();
    UpdateRounds();
    MakeGraph();
    int Condition;
    cout << "Round(1) or Date(2)? ";
    while (cin >> Condition){
        init();
        if (Condition == 1){
            cout << "Round# ";
            cin >> RoundNumber;
        }
        else if (Condition == 2){
            cout << "Date# ";
            cin >> MeaningDate;
            Date = Converter(MeaningDate);
        }
        else
            return 0;
        for (int i = 1; i <= 38; i++){
            if (!Visited[i])
                BFS(i, Condition);
        }
        Sorting();
        PrintStanding();
        cout << "Running.....\nRound(1) or Date(2)? ";
    }
    return 0;
}
