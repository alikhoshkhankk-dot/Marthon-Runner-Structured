
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_RUNNERS = 50;
const int NUM_DAYS = 7;

struct Runner
{
    string name;
    double miles[NUM_DAYS];
    double total;
    double average;
};

int readRunnerData(ifstream& file, Runner runners[]);
void calculateTotalsAndAverages(Runner runners[], int recordCount);
void displayResults(Runner runners[], int recordCount);

int main()
{
    Runner runners[MAX_RUNNERS];
    int recordCount;
    int numberOfRunners;
    int numberOfDays;

    ifstream file("runners.txt");

    if (!file)
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    file >> numberOfRunners >> numberOfDays;

    if (!file || numberOfDays != NUM_DAYS)
    {
        cout << "Invalid file header." << endl;
        file.close();
        return 1;
    }

    recordCount = readRunnerData(file, runners);

    file.close();

    calculateTotalsAndAverages(runners, recordCount);
    displayResults(runners, recordCount);

    return 0;
}

int readRunnerData(ifstream& file, Runner runners[])
{
    int recordCount = 0;

    while (recordCount < MAX_RUNNERS)
    {
        if (!(file >> runners[recordCount].name))
        {
            break;
        }

        bool complete = true;

        for (int day = 0; day < NUM_DAYS; day++)
        {
            if (!(file >> runners[recordCount].miles[day]))
            {
                complete = false;
                break;
            }
        }

        if (!complete)
        {
            break;
        }

        recordCount++;
    }

    return recordCount;
}

void calculateTotalsAndAverages(
    Runner runners[], int recordCount)
{
    for (int i = 0; i < recordCount; i++)
    {
        runners[i].total = 0;

        for (int day = 0; day < NUM_DAYS; day++)
        {
            runners[i].total += runners[i].miles[day];
        }

        runners[i].average =
            runners[i].total / NUM_DAYS;
    }
}

void displayResults(Runner runners[], int recordCount)
{
    cout << fixed << setprecision(2);

    cout << left << setw(15) << "Runner";

    for (int day = 1; day <= NUM_DAYS; day++)
    {
        cout << right << setw(8)
            << ("Day " + to_string(day));
    }

    cout << setw(10) << "Total";
    cout << setw(10) << "Average" << endl;

    for (int i = 0; i < recordCount; i++)
    {
        cout << left << setw(15) << runners[i].name;

        for (int day = 0; day < NUM_DAYS; day++)
        {
            cout << right << setw(8)
                << runners[i].miles[day];
        }

        cout << setw(10) << runners[i].total;
        cout << setw(10) << runners[i].average << endl;
    }

    cout << "\nNumber of runners read: "
        << recordCount << endl;
}