#ifndef FILEREADER
#define FILEREADER
using namespace std;

struct MatchData
{
    int Awayteam;
    int Date;
    int roundNumber;
    int homeGoals;
    int awayGoals;
    char result;
    string date;
    string homeTeam;
    string awayTeam;
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


vector<MatchData> FileReaderx();

#endif