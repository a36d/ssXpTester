#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include <locale>

using namespace std;

string CommatizeNumber(double number) {
    int num = floor(number);
    stringstream ss;
    
    ss.imbue(locale("")); 
    
    ss << num;
    return ss.str();
}

double CalculateReqXp(int level) {
    double m = 1.2;
    return floor((100 / m) * (pow(m, level)));
}

int main() {

    // Initialize Data <<
    const int base6x6 = 50;
    const int base9x9 = 200;

    const double minMulti = 0.5;
    const double maxMulti = 50.0; // I either want to remove this or make it scale with your level

    // MULTIPLICATIVE
    const double chaosMulti = 1.25;
    const double killerMulti = 2;

    // ADDITIVE
    const double easyMulti = -0.5;
    const double normalMulti = 0; const int normalLvlReq = 5;
    const double hardMulti = 1; const int hardLvlReq = 10;
    const double expertMulti = 5; const int expertLvlReq = 20;
    const double impossibleMulti = 20; const int impossibleLvlReq = 40;

    // XP MULTIPLIER
    // Base Multi will always initially be equal to the player's level multi (1 + (level - 1) * 0.1)
    double baseMulti = 1.0;

    // Run a Test <<
    string testType;
    cout << "Select a test mode: Full Simulation or Linear Test (f/l; default l): ";
    getline(cin, testType);

    if(testType == "f") { // Full Simulation <<
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
            baseMulti = 1 + ((level - 1) * 0.1);
            cout << "Run #" << runs << "\n\n";

            string type, size, diff;
            cout << "Enter the desired board type (cl/ch/k; default k): ";
            getline(cin, type);
            cout << "Enter the desired board size (6/9; default 9): ";
            getline(cin, size);;
            cout << "Enter the desired difficulty (e/n/h/e/i; default MAX): ";
            getline(cin, diff);

            string tString, sString, dString;
            
            double typeMulti = 1.0;
            if(type == "ch") {
                typeMulti = chaosMulti;
                tString = "Chaos";
            } else if(type == "" || type == "k") {
                typeMulti = killerMulti;
                tString = "Killer";
            } else if(type == "cl") {
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
            baseMulti *= typeMulti;

            if(baseMulti < minMulti) {
                baseMulti = minMulti;
            } else if(baseMulti > maxMulti) {
                baseMulti = maxMulti;
            }

            cout << "\nSelected Board: " << dString << " " << tString << " " << sString << endl;
            cout << "XP Multiplier: " << baseMulti << "\n\n";
            cout << "Current Level: " << level << "\nXP: " << CommatizeNumber(currentXp) << " / " << CommatizeNumber(reqXp) << endl;
            cout << "[Enter] to continue...";
            cin.ignore();

            currentXp += (baseXpGain * baseMulti);
            cout << "\nXP Gain: " << CommatizeNumber(baseXpGain * baseMulti) << "\n";
            while(currentXp >= reqXp) {
                level++;
                currentXp -= reqXp;
                reqXp = CalculateReqXp(level);
            }
            cout << "Current Level: " << level << "\nXP: " << CommatizeNumber(currentXp) << " / " << CommatizeNumber(reqXp) << "\n\n";
            runs++;
            cout << "----------------------------------------\n\n";
        }
        cout << "Total Runs: " << runs << "\nLevel " << iLevel << " -> " << finalLevel << "\n\nLevel: " << level << "\nXP: " << CommatizeNumber(currentXp) << " / " << CommatizeNumber(reqXp) << endl;
    } else if(testType == "l" || testType == "") { // Linear Test <<
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

        string type, size, diff;
        cout << "Enter the fixed board type (cl/ch/k; default cl): ";
        getline(cin, type);
        cout << "Enter the fixed board size (6/9; default 9): ";
        getline(cin, size);

        string tString, sString, dString;

        double typeMulti = 1.0;
        if(type == "ch") {
            typeMulti = chaosMulti;
            tString = "Chaos";
        } else if(type == "k") {
            typeMulti = killerMulti;
            tString = "Killer";
        } else if(type == "") {
            tString = "Classic";
        } else {
            cout << "Invalid board type, terminating run...\n\n";
            exit(1);
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
            exit(1);
        }

        double diffMulti = 0.0;
        while(level < finalLevel) {
            if (level < normalLvlReq) {
                diffMulti = easyMulti;
                dString = "Easy";
            } else if (level < hardLvlReq) {
                diffMulti = normalMulti;
                dString = "Normal";
            } else if (level < expertLvlReq) {
                diffMulti = hardMulti;
                dString = "Hard";
            } else if (level < impossibleLvlReq) {
                diffMulti = expertMulti;
                dString = "Expert";
            } else {
                diffMulti = impossibleMulti;
                dString = "Impossible";
            }
            baseMulti += diffMulti;
            baseMulti *= typeMulti;

            if(baseMulti < minMulti) {
                baseMulti = minMulti;
            } else if(baseMulti > maxMulti) {
                baseMulti = maxMulti;
            }

            currentXp += (baseXpGain * baseMulti);
            while(currentXp >= reqXp) {
                level++;
                currentXp -= reqXp;
                reqXp = CalculateReqXp(level);
            }
            baseMulti = 1 + ((level - 1) * 0.1);

            runs++;
        }
        cout << "Total Runs: " << runs << "\nLevel " << iLevel << " -> " << finalLevel << "\n\nLevel: " << level << "\nXP: " << CommatizeNumber(currentXp) << " / " << CommatizeNumber(reqXp) << endl;
    } else {
        cout << "Invalid test mode, terminating program...";
    }
    return 0;
}