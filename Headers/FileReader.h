#ifndef FILEREADER
#define FILEREADER
using namespace std;

struct MatchData
{
    int roundNumber;
    string date;
    string homeTeam;
    string awayTeam;
    int homeGoals;
    int awayGoals;
    char result;
};

struct TeamStats
{
    int points;
    int goalsScored;
    int goalsEncoded;
    int teamNode;
    int MatchPlayed;
    int W;
    int D;
    int L;
};

struct MatchDataForGraph
{
    int Awayteam;
    int date;
    int roundNumber;
    int homeGoals;
    int awayGoals;
    char result;
};

vector<MatchData> FileReaderx();

#endif