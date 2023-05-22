#include <bits/stdc++.h>
#include "../Headers/FileReader.h"
const int N = 50;
#define ll long long
using namespace std;

string InDate;
int Visited[N], Rank;
int Roundnumber, Date, Condition;
vector<MatchData> matches;
unordered_map<int, string> Nodes;
unordered_map<string, int> NodesName;
vector<TeamStats> Standing(N);
vector<MatchData> Graph[N];

void init()                          // O(V)
{                               
    Date = 0;
    Roundnumber = 0;
    for (int i = 0; i < N; i++)
    {
        Standing[i].D = 0;
        Standing[i].L = 0;
        Standing[i].W = 0;
        Standing[i].points = 0;
        Standing[i].teamNode = i;
        Standing[i].goalsScored = 0;
        Standing[i].MatchPlayed = 0;
        Standing[i].goalsEncoded = 0;
    }
    memset(Visited, 0, sizeof(Visited));
    Rank = 1;
}


bool sortBy(TeamStats &a, TeamStats &b){                                                                    // O(V * log(V))
    int diffGoalsA = (a.goalsScored - a.goalsEncoded), diffGoalsB = (b.goalsScored - b.goalsEncoded);       // O(1)
    if (a.points != b.points)                                                                               // O(1)
        return (a.points > b.points);
    else if (diffGoalsA != diffGoalsB)                                                                      // O(1)
        return (diffGoalsA > diffGoalsB);
    else if (a.goalsScored != b.goalsScored)
        return (a.goalsScored > b.goalsScored);
    else if (a.goalsEncoded != b.goalsEncoded)
        return (a.goalsEncoded < b.goalsEncoded);
    return (Nodes[a.teamNode] < Nodes[b.teamNode]);
}


int Converter(string date){                                     // O(1)
    stringstream ss(date);                                      // used to extract substrings from a string stream (ss) using a delimiter ('/').
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


void Sorting(){                                                 // O(V * log(V))
    sort(Standing.begin(), Standing.end(), sortBy);
}


void MakeGraph(){                                               //  O(E)
    for (MatchData i : matches){                                //  O(E)
        Graph[NodesName[i.homeTeam]].push_back(
            {
                NodesName[i.awayTeam],
                Converter(i.date),
                i.roundNumber,
                i.homeGoals,
                i.awayGoals,
                i.result,
                "",
                "",
                ""
            }
        );
    }
}

void Stand(int winner, int loser, MatchData Edge, char Result)          // O(1)
{             
    if (Result == 'H' || Result == 'A')
    {
        Standing[winner].points += 3;
        Standing[winner].W++;
        Standing[loser].L++;
    }
    else
    {
        Standing[winner].points += 1;
        Standing[loser].points += 1;
        Standing[winner].D++;
        Standing[loser].D++;
    }
    Standing[winner].MatchPlayed++;
    Standing[loser].MatchPlayed++;
    if (Result == 'H')
    {
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
void PrintStanding(){                                                                                           // O(V)
    cout << "Premier League Standings Untill ";
    if (Date)
        cout << InDate << '\n';
    else
        cout << "Round " << Roundnumber << '\n';
    cout << "|****|**************************|***********|*****|*****|*****|*****|*****|*****|*****|\n";
    cout << "|Rank|Team                      |MatchPlayed|  W  |  D  |  L  | GF  | GA  | GD  | Pts |\n";
    cout << "|****|**************************|***********|*****|*****|*****|*****|*****|*****|*****|\n";
    for (TeamStats team : Standing){                                                                            // O(V)
        if (Nodes[team.teamNode].empty())
            continue;
        cout << '|' << left << setw(4) << Rank++ << "|";
        cout << left << setw(26) << Nodes[team.teamNode] << "|";
        cout << right << setw(11) << team.MatchPlayed << "|";
        cout << right << setw(5) << team.W << "|";
        cout << right << setw(5) << team.D << "|";
        cout << right << setw(5) << team.L << "|";
        cout << right << setw(5) << team.goalsScored << "|";
        cout << right << setw(5) << team.goalsEncoded << "|";
        cout << right << setw(5) << team.goalsScored - team.goalsEncoded << "|";
        cout << right << setw(5) << team.points << "|\n";
        cout << "|----|--------------------------|-----------|-----|-----|-----|-----|-----|-----|-----|\n";
    }
}

void BFS(int x, int condition)           // O(E + V)
{                                
    queue<int> q;
    Visited[x] = 1;
    q.push(x);
    if (condition == 1)
    {
        while (q.size())                                        // O(V)
        {
            int P = q.front();                                  // O(1)
            q.pop();                                            // O(1)
            for (MatchData i : Graph[P])                        // O(E)
            {
                if (i.roundNumber <= Roundnumber)
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
            for (MatchData i : Graph[P])
            {
                if (i.Date <= Date)
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
    for (MatchData& i : matches){                   // O(E)     --> E represents Rankber of matches.
        if (i.roundNumber < CurrentRound)           // O(1) 
            i.roundNumber = CurrentRound;
        else if (i.roundNumber > CurrentRound)     // O(1)
            CurrentRound = i.roundNumber;
        if (NodesName[i.homeTeam] == 0)            // O(1)
        {
            NodesName[i.homeTeam] = CurrentNode;
            Nodes[CurrentNode] = i.homeTeam;
            CurrentNode++;
        }                                           
        if (NodesName[i.awayTeam] == 0){            // O(1)
            NodesName[i.awayTeam] = CurrentNode;
            Nodes[CurrentNode] = i.awayTeam;
            CurrentNode++;
        }
    }
}

int main()
{
    matches = FileReaderx();                    // O(E)
    UpdateRounds();                             // O(E)
    MakeGraph();                                // O(E) 
    cout << "Round(1) or Date(2)? ";            // O(1)
    while (cin >> Condition){                   // O(E + V + V logV) --------> This graph is dense, so the complixity: O(V^2 + V * log(V)) = O(V^2)                  
        init();                                 // O(V)
        if (Condition == 1){                    // O(1)
            do
            {
                cout << "Enter Correct Round# ";
                cin >> Roundnumber;
            } while (Roundnumber < 1 || Roundnumber > 38);
        }
        else if (Condition == 2){               // O(1)
            do
            {
                cout << "Enter Correct Date : ";
                cin >> InDate;
            } while (InDate > "18/05/2023" || InDate < "05/08/2022");
            Date = Converter(InDate);      // O(1)  
        }
        else
            return 0;
        for (int i = 1; i <= N; i++)       // O(E + V)
        {
            if (!Visited[i])
            BFS(i, Condition);          // O(E + V)      
        }
        Sorting();                              // O(V * log(V)) 
        PrintStanding();                        // O(V)
        cout << "Running.....\nRound(1) or Date(2) ? ";          // O(1)
    }
    return 0;
}
