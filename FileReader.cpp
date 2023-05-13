#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define TIME ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
const ll oo = 1e18, N = 1e9 + 1;
struct MatchData {
    int roundNumber;
    string date;
    string homeTeam;
    string awayTeam;
    int homeGoals;
    int awayGoals;
    char result;
};

int main() {
    // read match data from CSV file
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
        cout << stoi(fields[0]) <<"\t\t\t" << fields[1] << "\t\t\t" << fields[2] <<"\t\t\t"<< fields[3] << "\t\t\t" << stoi(fields[4]) <<"\t\t\t"<< stoi(fields[5]) <<  "\t\t\t" << fields[6][0] << '\n';
        MatchData match;

        match.roundNumber = stoi(fields[0]);
        match.date = fields[1];
        match.homeTeam = fields[2];
        match.awayTeam = fields[3];
        match.homeGoals = stoi(fields[4]);
        match.awayGoals = stoi(fields[5]);
        match.result = fields[6][0];
        // Extract match date (if needed)
    }

}