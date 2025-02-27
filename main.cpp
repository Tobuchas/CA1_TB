#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Lizard {
    string species;
    float length;
    string habitat;
    string diet;
    int age;
};

void display(const Lizard &liz)
{
    cout <<left
    << setw(30)<< liz.species
    <<setw(10) <<liz.length
    <<setw(15)<< liz.habitat
    <<setw(15)<<liz.diet
    <<setw(5)<<liz.age
    <<endl;

}

void displayAll(vector<Lizard> &liz) {
    cout <<" Species\t\t      Length\tHabitat\t       Diet\t      Age"<<endl;
    cout <<"_________________________________________________________________________"<<endl;
    for(int i = 0; i < liz.size(); i++) {
        display(liz[i]);
    }
}

void parseLine(string line,Lizard &liz)
{

    string temp;
    stringstream ss(line);
    getline(ss, liz.species, ',');
    getline(ss, temp, ',');
    liz.length = stod(temp);

    getline(ss, liz.habitat, ',');
    getline(ss, liz.diet, ',');
    getline(ss, temp, ',');
    liz.age = stoi(temp);

}

void load(const string &fname, vector<Lizard> &data)
{
    ifstream fin(fname);

    if(fin)
    {
        string line;
        getline(fin, line);

        while(getline(fin, line))
        {
            Lizard liz;
            parseLine(line, liz);
            data.push_back(liz);
        }
        fin.close();
    }
    else
    {
        cout << "Error opening file." <<endl;
    }
}

int find(vector<Lizard> &data, string target) {
    int index = -1;
    for(int i = 0; i < data.size(); i++) {
        if(data[i].species == target) {
            index = i;
        }
    }
    return index;
}


map<string,int> mapUniqueSpecies(vector<Lizard> &data) {
    map<string,int> map;
    map.insert(pair<string,int>(data[0].species,1));
    for(int i = 1; i < data.size(); i++) {
        if(map.find(data[i].species) != map.end()) {
            map[data[i].species] = map[data[i].species] + 1;
        }
        else {
            map.insert(pair<string,int>(data[i].species,1));
        }
    }
    return map;
}

map<float,int> mapUniqueLength(vector<Lizard> &data) {
        map<float,int> map;
        map.insert(pair<float,int>(data[0].length,1));
        for(int i = 1; i < data.size(); i++) {
            if(map.find(data[i].length) != map.end()) {
                map[data[i].length] = map[data[i].length] + 1;
            }
            else {
                map.insert(pair<float,int>(data[i].length,1));
            }
        }
        return map;
}

map<string,int> mapUniqueHabitat(vector<Lizard> &data) {
    map<string,int> map;
    map.insert(pair<string,int>(data[0].habitat,1));
    for(int i = 1; i < data.size(); i++) {
        if(map.find(data[i].habitat) != map.end()) {
            map[data[i].habitat] = map[data[i].habitat] + 1;
        }
        else {
            map.insert(pair<string,int>(data[i].habitat,1));
        }
    }
    return map;
}

map<string,int> mapUniqueDiet(vector<Lizard> &data) {
    map<string,int> map;
    map.insert(pair<string,int>(data[0].diet,1));
    for(int i = 1; i < data.size(); i++) {
        if(map.find(data[i].diet) != map.end()) {
            map[data[i].diet] = map[data[i].diet] + 1;
        }
        else {
            map.insert(pair<string,int>(data[i].diet,1));
        }
    }
    return map;
}

map<int,int> mapUniqueAge(vector<Lizard> &data) {
    map<int,int> map;
    map.insert(pair<int,int>(data[0].age,1));
    for(int i = 1; i < data.size(); i++) {
        if(map.find(data[i].age) != map.end()) {
            map[data[i].age] = map[data[i].age] + 1;
        }
        else {
            map.insert(pair<int,int>(data[i].age,1));
        }
    }
    return map;
}

void displaySpecificSpecies(vector<Lizard> &data, string spec) {
    bool found = false;
    for(int i = 0; i < data.size(); i++) {
        if(data[i].species == spec) {
            display(data[i]);
            found = true;
        }

    }
    if(!found) {
        cout << "Species not found:" <<endl;
    }
}

void displaySpecificHabitat(vector<Lizard> &data, string spec) {
    bool found = false;
    for(int i = 0; i < data.size(); i++) {
        if(data[i].habitat == spec) {
            display(data[i]);
            found = true;
        }

    }
    if(!found) {
        cout << "Habitat not found:" <<endl;
    }
}


int main() {
    // Lizard lizard;
    // lizard.species = "Crack";
    // lizard.length = 3;
    // lizard.habitat = "Canada";
    // lizard.diet = "Doodoo";
    // lizard.age = 20;
    // display(lizard);

    vector<Lizard> data;
    load("lizardsTable.csv", data);
    displayAll(data);
    cout << endl << endl << endl;
    map<string,int> map = mapUniqueHabitat(data);
    for (const auto& pair : map) {
        cout << pair.first << " => " << pair.second << endl;
    }
    cout << endl << endl << endl;


    string input;
    cout << "Please input the name of what habitat you want" << endl;
    getline(cin,input);
    displaySpecificHabitat(data, input);
}
