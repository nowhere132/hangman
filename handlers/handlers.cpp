#include <iostream>
#include <cstdlib>
#include <fstream>          // ifstream
#include <vector>
#include <string>
#include <algorithm>        // max, min ...
#include <ctime>            // clock
#include <conio.h>          // kbhit
#include "../helpers/helpers.h"
using namespace std;

vector<vector<string>> Easy, Hard;
string dataNames[] = { "animals_and_plants.txt", "city_and_transportation.txt", "computer_and_internet.txt", "education.txt", "family_and_relationships.txt", "food_and_drinks.txt", "health.txt", "ogden_picturable_200.txt", "sports_and_arts.txt", "weather_and_environment.txt", "data.txt" };
string igNames[] = { "Animals & Plants", "City & Transportation", "Computer & Internet", "Education", "Family & Relationships", "Food & Drinks", "Health", "Ogden Picturable", "Sports & Arts", "Weather & Environment", "Default mode"};

void buildOurLib() {
    Easy.resize(11), Hard.resize(11);
    for (int i = 0; i < 11; ++i) {
        ifstream inp("./datas/" + dataNames[i]);
        if (!inp.is_open()) {
            cout << "Unabled to open file " << igNames[i] << "\n";
            continue;
        }

        string str;
        while (inp >> str) {
            if (str.size() <= 5)
                Easy[i].push_back(str);
            else
                Hard[i].push_back(str);
        }
        // cout << Easy[i].size() << ' ' << Hard[i].size() << '\n';

        inp.close();
    }
}

int askToPlay() {
    cout << "Do u want to play our game ?\n";
    cout << "Press Y to play, otherwise N to quit\n";
    string str;
    cin >> str;
    if (str == "Y" || str == "y") {         // want to play the game
        system("CLS");
        return 1;
    }
    else if (str == "N" || str == "n") {    // want to quit
        system("CLS");
        return 0;
    }
    else {
        // PutNotice("You pressed wrong key sir! Just only Y or N");
        return askToPlay();
    }
}

int chooseMode() {
    cout << "Which mode do you want to play ?\n";
    for (int i = 0; i < 10; ++i) {
        cout << i << " . " << igNames[i] << '\n';
    }
    cout << "D . " << igNames[10] << '\n';

    char c; cin >> c;
    if ((c < '0' || c > '9') && (c != 'D' && c != 'd')) {
        PutNotice("");
        return chooseMode();
    }

    if ('0' <= c && c <= '9')
        return c - '0';
    else
        return 10;
}

string ourDeal(int idMode) {
    cout << "Which level do you want to play ?\n";
    cout << "You have 2 choices : Easy and Hard\n";
    cout << "Press E to play easy mode, otherwise H\n";

    string str;
    cin >> str;
    if (str == "E" || str == "e") {         // Easy mode
        system("CLS");
        int id = Rand(0, Easy[idMode].size() - 1);
        fixToLower(Easy[idMode][id]);
        return Easy[idMode][id];
    }
    else if (str == "H" || str == "h") {    // Hard mode
        system("CLS");
        int id = Rand(0, Hard[idMode].size() - 1);
        fixToLower(Hard[idMode][id]);
        return Hard[idMode][id];
    }
    else {
        PutNotice("");
        return ourDeal(idMode);
    }
}

void playGame(string &ans, string &our, string &vec, int &numSuggest) {
    system("CLS");
    cout << "Our answer is : " << our << '\n';
    cout << "Our mistakes : " << vec << '\n';
    cout << getHangPicture(vec.size()) << '\n';
    if (numSuggest) {
        cout << "You still have " << numSuggest << " suggestion" << (numSuggest > 1 ? "s" : "") << '\n';
        cout << "If you want to use it, press 1\n";
    }

    clock_t Start = clock(), curTime = Start;
    int len = 10;
    while (! _kbhit()) {
        if ((clock() - Start)/CLOCKS_PER_SEC >= 10) {
            while (vec.size() < 7)
                vec.push_back('#');
            return;
        }
        if ((clock() - curTime)/CLOCKS_PER_SEC == 1) {
            cout << "You still have " << --len << " seconds\n";
            curTime = clock();
        }
    }

    cout << "\n\nYour new guess is : ";
    char c;
    cin >> c;
    c = ToLowerChar(c);

    if (c == '1' && numSuggest) { // player need 1 suggestion
        numSuggest--;
        for (int i = 0; i < ans.size(); ++i)
            if (our[i] == '-') {
                cout << "Our suggestion is : " << ans[i] << '\n';
                c = ans[i];
                break;
            }
    }

    // check new guessed character
    int flag = 0;
    for (int i = 0; i < ans.size(); ++i)
        if (ans[i] == c && our[i] == '-') {
            flag = 1; break;
        }

    if (flag) {
        // update our guess word
        for (int i = 0; i < ans.size(); ++i)
            if (ans[i] == c && our[i] == '-')
                our[i] = c;
    }
    else {
        vec += c;
    }
}

int solve() {
    // get information for our game
    int idMode = chooseMode();
    string needToGuess = ourDeal(idMode);
    string ourGuess(needToGuess.size(), '-');
    string mistakes = "";
    int numSuggest = needToGuess.size()/3;

    // game process
    while (mistakes.size() < 7 && needToGuess != ourGuess) {
        playGame(needToGuess, ourGuess, mistakes, numSuggest);
    }

    // our ending
    if (mistakes.size() == 7) {
        renderDeath(needToGuess);
        return 0;
    }
    else {
        cout << "The correct answer is : " << needToGuess << '\n';
        PutNotice("Wow, u are so good", 3);
        return 1;
    }
}
