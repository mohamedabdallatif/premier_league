#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define TIME ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
const ll oo = 1e18, N = 1e9 + 1;
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
        // cout << stoi(fields[0]) <<"\t\t\t" << fields[1] << "\t\t\t" << fields[2] <<"\t\t\t"<< fields[3] << "\t\t\t" << stoi(fields[4]) <<"\t\t\t"<< stoi(fields[5]) <<  "\t\t\t" << fields[6][0] << '\n';
    }
}