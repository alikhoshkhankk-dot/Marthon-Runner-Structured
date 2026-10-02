
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int NUM_RUNNERS = 5;
const int NUM_DAYS = 7;

struct Runner
{
    string name;
    double miles[NUM_DAYS];
    double total;
    double average;
};

void readData(ifstream& file, Runner runners[]);
void calculateData(Runner runners[]);
void displayData(Runner runners[]);

int main()
{
    Runner runners[NUM_RUNNERS];

    ifstream file("runners.txt");

    if (!file)
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    readData(file, runners);

    file.close();

    calculateData(runners);

    displayData(runners);

    return 0;
}

void readData(ifstream& file, Runner runners[])
{
    int numberOfRunners;
    int numberOfDays;

    file >> numberOfRunners >> numberOfDays;

    for (int i = 0; i < NUM_RUNNERS; i++)
    {
        file >> runners[i].name;

        for (int j = 0; j < NUM_DAYS; j++)
        {
            file >> runners[i].miles[j];
        }
    }
}

void calculateData(Runner runners[])
{
    for (int i = 0; i < NUM_RUNNERS; i++)
    {
        runners[i].total = 0;

        for (int j = 0; j < NUM_DAYS; j++)
        {
            runners[i].total += runners[i].miles[j];
        }

        runners[i].average =
            runners[i].total / NUM_DAYS;
    }
}

void displayData(Runner runners[])
{
    cout << fixed << setprecision(2);

    cout << left << setw(12) << "Runner";

    for (int i = 1; i <= NUM_DAYS; i++)
    {
        cout << right << setw(8)
            << ("Day " + to_string(i));
    }

    cout << setw(10) << "Total";
    cout << setw(10) << "Average" << endl;

    cout << string(96, '-') << endl;

    for (int i = 0; i < NUM_RUNNERS; i++)
    {
        cout << left << setw(12) << runners[i].name;

        for (int j = 0; j < NUM_DAYS; j++)
        {
            cout << right << setw(8)
                << runners[i].miles[j];
        }

        cout << setw(10) << runners[i].total;
        cout << setw(10) << runners[i].average << endl;
    }
}