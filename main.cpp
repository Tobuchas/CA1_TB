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

//Method to display the whole table
void displayAll(vector<Lizard> &liz) {
    cout <<" Species\t\t      Length\tHabitat\t       Diet\t      Age"<<endl;
    cout <<"_________________________________________________________________________"<<endl;
    for(int i = 0; i < liz.size(); i++) {
        display(liz[i]);
    }
}

//This method has been borrowed from proffesro Dermot Louge
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

//This method has been borrowed from proffesro Dermot Louge
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

//Find gives back an index of found species or -1 if not found
int find(vector<Lizard> &data, string target) {
    int index = -1;
    for(int i = 0; i < data.size(); i++) {
        if(data[i].species == target) {
            index = i;
        }
    }
    return index;
}

//Maps Unique Specie names to the counts of how many times they appear in the table
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

//Maps Unique Lengths to the counts of how many times they appear in the table

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

//Maps Unique Habitat names to the counts of how many times they appear in the table
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

//Maps Unique types of Diet to the counts of how many times they appear in the table
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

//Maps Unique Ages to the counts of how many times they appear in the table
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


//This is the Find method but instead of an index displays the actual Lizard
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

//Find method for the Habitat
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

//Displays the Highest Aged, Lowest Aged and the average of the Ages of lizards
void displayAgeValues(vector<Lizard> &data) {
    int highest = data[0].age;
    int highIndex = 0;
    int lowest = data[0].age;
    int lowIndex = 0;
    int total = data[0].age;
    double average;
    for(int i = 1; i < data.size(); i++) {
        if(data[i].age > highest) {
            highest = data[i].age;
            highIndex = i;
        }
        if(data[i].age < lowest) {
            lowest = data[i].age;
            lowIndex = i;
        }
        total += data[i].age;
    }
    average = total / data.size();
    cout << "Average:" <<endl;
    cout << average << endl;
    cout << "Highest:" <<endl;
    display(data[highIndex]);
    cout << "Lowest:" <<endl;
    display(data[lowIndex]);
}

//Find but it displays all results containing the input String
vector<string> findSpecies(vector<Lizard> &data,string input) {
    vector<string> result;
    string inputLowercase = input;
    transform(inputLowercase.begin(), inputLowercase.end(), inputLowercase.begin(), ::tolower);
    for (auto it = data.begin(); it != data.end(); it++) {
        string titleLowercase = it->species;
        transform(titleLowercase.begin(), titleLowercase.end(), titleLowercase.begin(), ::tolower);
        if (titleLowercase.find(inputLowercase) != string::npos) {
            result.push_back(titleLowercase);
        }
    }
    return result;
}

//Sorts the table by Length Descending and Displays
void displaySortedLength(vector<Lizard> &data) {
    sort(data.begin(), data.end(), [](const Lizard &a, const Lizard &b) {
        return a.length > b.length;
    });
    cout << "Sorted by Length:" <<endl;
    cout << endl;
    for(int i = 0; i < data.size(); i++) {
        display(data[i]);
    }
}

//The Main with the Menu
int main() {

    vector<Lizard> data;
    load("lizardsTable.csv", data);

    int menuOption;
    string input;

    //Menu containing the options needed for the questions
    do {
        cout << "_________________________________________________\n";
        cout << "#           Tomas's Database of Lizards         #\n";
        cout << "_________________________________________________\n";
        cout << "#              Select an option:                #\n";
        cout << "#           1. Display all Lizards              #\n";
        cout << "#           2. Find a specific lizard           #\n";
        cout << "#     3. Display Number of lizards per habitat  #\n";
        cout << "#         4. Search lizards by Habitat          #\n";
        cout << "#       5. Display interesting age info         #\n";
        cout << "#          6. Search species by name            #\n";
        cout << "#       7. Sort Lizards by Length - Desc        #\n";
        cout << "#                   8. Exit                     #\n";
        cout << "_________________________________________________\n";

        //Gets the input option
        cin >> menuOption;
        cin.ignore();  //Assures inputs go through as they should

        cout << endl;

        //The skeleton of the Menu
        switch(menuOption) {
            //1. Display all Lizards
            case 1:
                displayAll(data);
            break;

            //2. Find a specific lizard
            case 2:
                cout << "Enter the species of the lizard you want" << endl;
                getline(cin,input);

                if (find(data, input)>=0) {
                    display(data[find(data, input)]);
                }
                else {
                    cout << "Species not found!" <<endl;
                }
                break;

            //3. Display Number of lizards per habitat
            case 3: {
                map<string,int> map = mapUniqueHabitat(data);
                for (const auto& pair : map) {
                    cout << pair.first << " => " << pair.second << endl;
                }
            }
                break;

            //4. Search lizards by Habitat
            case 4: {
                cout << "Please input the name of what habitat you want" << endl;
                getline(cin,input);
                displaySpecificHabitat(data, input);
            }
                break;

            //5. Display interesting age info
            case 5:
                displayAgeValues(data);
                break;

            //6. Search species by name
            case 6: {
                cout << "Please input the name of what species you are searching for" << endl;
                cin >> input;
                cin.ignore();
                vector<string> searchResults = findSpecies(data, input);
                for(auto it = searchResults.begin(); it != searchResults.end(); it++) {
                    cout << *it << endl;
                }
            }
                break;

            //7. Sort Lizards by Length - Desc
            case 7:
                displaySortedLength(data);
                break;

            //8.Exit
            case 8:
                cout << "Exiting program... See you next time!" << endl;
                break;

            //Ensuring valid inputs
            default:
                cout << "Please input a valid option!" << endl;

        }

        //Stopping the menu to give the person time
        if(menuOption != 8) {
            cout << "Press ENTER to continue" << endl;
            cin.ignore();
        }
    }
    //Ending the whole loop
    while (menuOption != 8);


    /*displayAll(data);
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
    displayAgeValues(data);
    cout << endl << endl << endl;

    cout << "Please input the name of what species you are searching for" << endl;
    cin >> input;
    vector<string> searchResults = findSpecies(data, input);
    for(auto it = searchResults.begin(); it != searchResults.end(); it++) {
        cout << *it << endl;
    }

    cout << endl << endl << endl;
    displaySortedLength(data);
    */

    return 0;

}
