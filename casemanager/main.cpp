#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

const string dbfilename = "db.json";

void printMenu()
{
    cout << "Welcome to the case manager!" << endl;
    cout << "Commands are: " << endl;
    cout << "a - add case, rm - delete case, e - edit case" << endl;
    cout << "ls - list cases, sn - search cases by name, snum - search cases by number" << endl;
    cout << "s - save cases to file, l - load cases from file" << endl;
    cout << "q - exit" << endl;
}

int addCase(json &cases)
{
    string casenumber;
    string casename;
    cout << "Casenumber:" << endl;
    cin >> casenumber;
    cout << "Casename:" << endl;
    cin >> casename;
    json new_case = {{"casenumber", casenumber}, {"casename", casename}};
    cases.push_back(new_case);
    cout << "Case added" << endl;
    return 0;
}

int removeCase(json &cases)
{
    string casenumber;
    cout << "Casenumber:" << endl;
    cin >> casenumber;
    for (int i = 0; i < cases.size(); i++)
    {
        if (cases[i]["casenumber"] == casenumber)
        {
            cases.erase(cases.begin() + i);
            cout << "Case removed" << endl;
            return 0;
        }
    }
    cout << "Case not found" << endl;
    return 0;
}

int editCase(json &cases)
{
    string casenumber;
    cout << "Casenumber:" << endl;
    cin >> casenumber;
    for (int i = 0; i < cases.size(); i++)
    {
        if (cases[i]["casenumber"] == casenumber)
        {
            string casename;
            cout << "Casename:" << endl;
            cin >> casename;
            cases[i]["casename"] = casename;
            cout << "Case edited" << endl;
            return 0;
        }
    }
    cout << "Case not found" << endl;
    return 0;
}

int listCases(json &cases)
{
    cout << "Cases:" << endl;
    for (int i = 0; i < cases.size(); i++)
    {
        cout << cases[i]["casenumber"] << " - " << cases[i]["casename"] << endl;
    }
    return 0;
}

int searchCasesByName(json &cases)
{
    string casename;
    cout << "Casename:" << endl;
    cin >> casename;
    for (int i = 0; i < cases.size(); i++)
    {
        if (cases[i]["casename"] == casename)
        {
            cout << cases[i]["casenumber"] << " - " << cases[i]["casename"] << endl;
        }
    }
    return 0;
}

int searchCasesByNumber(json &cases)
{
    string casenumber;
    cout << "Casenumber:" << endl;
    cin >> casenumber;
    for (int i = 0; i < cases.size(); i++)
    {
        if (cases[i]["casenumber"] == casenumber)
        {
            cout << cases[i]["casenumber"] << " - " << cases[i]["casename"] << endl;
        }
    }
    return 0;
}

int saveCases(json &cases)
{
    ofstream file;
    file.open(dbfilename);
    if (file)
    {
        file << cases.dump(4); // pretty-print with 4-space indent
        file.close();
        cout << "Cases saved to: " << dbfilename << endl;
    }
    else
    {
        cerr << "Error: could not open " << dbfilename << " for writing." << endl;
    }
    return 0;
}

int loadCases(json &cases)
{
    ifstream file(dbfilename);

    if (!file)
    {
        cout << "Error: could not open " << dbfilename << " for reading." << endl;
        return 1;
    }
    try
    {
        file >> cases;
        if (cases.empty())
        {
            cout << "No cases in " << dbfilename << "." << endl;
            return 1;
        }
        else
        {
            cout << "Cases loaded from: " << dbfilename << endl;
            file.close();
        }
        return 0;
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}

int main()
{
    json cases = json::array();
    string input = "NULL";

    // Load cases on startup
    cout << "Do you want to load cases from a file? (y/n)" << endl;
    cin >> input;
    if (input == "y")
    {
        loadCases(cases);
    }

    // Menu
    printMenu();
    while (input != "q")
    {
        cin >> input;
        if (input == "a")
        {
            addCase(cases);
        }
        else if (input == "ls")
        {
            listCases(cases);
        }
        else if (input == "sn")
        {
            searchCasesByName(cases);
        }
        else if (input == "snum")
        {
            searchCasesByNumber(cases);
        }
    }

    // Quit program
    cout << "Do you want to save cases to a file? (y/n)" << endl;
    cin >> input;
    if (input == "y")
    {
        saveCases(cases);
    }
    return 0;
}