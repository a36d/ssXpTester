#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

double CalculateReqXp(int level) {
    return (100 / 1.1) * (pow(1.1, level));
}

int main() {

    // Initialize Data <<
    const int base6x6 = 50;
    const int base9x9 = 150;

    const double minMulti = 0.5;
    const double maxMulti = 10.0;

    const double chaosMulti = 0.2;
    const double killerMulti = 0.5;

    const double easyMulti = -0.5;
    const double normalMulti = 0; const int normalLvlReq = 5;
    const double hardMulti = 0.5; const int hardLvlReq = 10;
    const double expertMulti = 2; const int expertLvlReq = 20;
    const double impossibleMulti = 5; const int impossibleLvlReq = 40;

    double baseMulti = 1.0;

    // Run a Test <<
    string iLevel, iFinalLevel;
    int level, finalLevel;
    double currentXp = 0.0;

    cout << "Enter starting level: ";
    getline(cin, iLevel);
    cout << "Enter final level: ";
    getline(cin, iFinalLevel);
    
    if(iLevel.empty()) {
        level = 1;
    } else {
        level = stoi(iLevel);
    }
    if(iFinalLevel.empty()) {
        finalLevel = 1;
    } else {
        finalLevel = stoi(iFinalLevel);
    }
    double reqXp = CalculateReqXp(level); 

    cout << fixed << setprecision(2) << "----------------------------------------\n\n";
    int runs = 1;
    while (level < finalLevel) {
        baseMulti = 1.0;
        cout << "Run #" << runs << "\n\n";

        string type, size, diff;
        cout << "Enter the desired board type (cl/ch/k; default cl): ";
        getline(cin, type);
        cout << "Enter the desired board size (6/9; default 9): ";
        getline(cin, size);;
        cout << "Enter the desired difficulty (e/n/h/e/i; default MAX): ";
        getline(cin, diff);

        string tString, sString, dString;
        
        if(type == "ch") {
            baseMulti += chaosMulti;
            tString = "Chaos";
        } else if(type == "k") {
            baseMulti += killerMulti;
            tString = "Killer";
        } else if(type == "") {
            tString = "Classic";
        } else {
            cout << "Invalid board type, terminating run...\n\n";
            continue;
        }

        int baseXpGain = 0;
        if(size == "6") {
            baseXpGain = base6x6;
            sString = "6x6";
        } else if(size == "9") {
            baseXpGain = base9x9;
            sString = "9x9";
        } else if(size == "") {
            baseXpGain = base9x9;
            sString = "9x9";
        } else {
            cout << "Invalid board size, terminating run...\n\n";
            continue;
        }

        if(diff == "e") {
            baseMulti += easyMulti;
            dString = "Easy";
        } else if(diff == "n") {
            baseMulti += normalMulti;
            dString = "Normal";
        } else if(diff == "h") {
            baseMulti += hardMulti;
            dString = "Hard";
        } else if(diff == "x") {
            baseMulti += expertMulti;
            dString = "Expert";
        } else if(diff == "i") {
            baseMulti += impossibleMulti;
            dString = "Impossible";
        } else if(diff == "") {
            if (level < normalLvlReq) {
                baseMulti += easyMulti;
                dString = "Easy";
            } else if (level < hardLvlReq) {
                baseMulti += normalMulti;
                dString = "Normal";
            } else if (level < expertLvlReq) {
                baseMulti += hardMulti;
                dString = "Hard";
            } else if (level < impossibleLvlReq) {
                baseMulti += expertMulti;
                dString = "Expert";
            } else {
                baseMulti += impossibleMulti;
                dString = "Impossible";
            }
        } else {
            cout << "Invalid difficulty, terminating run...\n\n";
            continue;
        }
        if(baseMulti < minMulti) {
            baseMulti = minMulti;
        } else if(baseMulti > maxMulti) {
            baseMulti = maxMulti;
        }

        cout << "\nSelected Board: " << dString << " " << tString << " " << sString << endl;
        cout << "XP Multiplier: " << baseMulti << "\n\n";
        cout << "Current Level: " << level << "\nXP: " << currentXp << "/" << reqXp << endl;
        cout << "[Enter] to continue...";
        cin.ignore();

        currentXp += (baseXpGain * baseMulti);
        cout << "\nXP Gain: " << (baseXpGain * baseMulti) << "\n";
        while(currentXp >= reqXp) {
            level++;
            currentXp -= reqXp;
            reqXp = CalculateReqXp(level);
        }
        cout << "Current Level: " << level << "\nXP: " << currentXp << "/" << reqXp << "\n\n";
        runs++;
        cout << "----------------------------------------\n\n";
    }
    cout << "Total Runs: " << runs << "\nLevel " << iLevel << " -> " << finalLevel << "\n\nLevel: " << level << "\nXP: " << currentXp << "/" << reqXp << endl;

    return 0;
}