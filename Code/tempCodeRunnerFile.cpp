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
        if(fields[4] == "*")    continue;
        // cout << stoi(fields[0]) <<"\t\t\t" << fields[1] << "\t\t\t" << fields[2] <<"\t\t\t"<< fields[3] << "\t\t\t" << stoi(fields[4]) <<"\t\t\t"<< stoi(fields[5]) <<  "\t\t\t" << fields[6][0] << '\n';
    }