#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

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
}
