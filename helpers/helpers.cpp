#include <iostream>
#include <vector>
#include <string>
#include <thread>           // this_thread
#include <chrono>           // system time control
#include <conio.h>          // keyboard hit
using namespace std;

string picture[] = {"",
"   ------------\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |          |\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",

};

const vector<string> HANGED = {
"   ------------\n"
"   |         /\n"
"   |        O\n"
"   |       /|\\\n"
"   |       / \\\n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |           \\\n"
"   |            O\n"
"   |           /|\\\n"
"   |           / \\\n"
"   |             \n"
"   |             \n"
"   |             \n"
"   |             \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        "
};

string getHangPicture(int n) {
    return picture[n];
}

void PutNotice(string str, int Time = 1) {
    cout << str << '\n';
    this_thread::sleep_for(chrono::seconds(Time));
    system("CLS");
}

int Rand(int l, int r) {
    long long t = RAND_MAX + 1;
    return l + (t*t*t*rand() + t*t*rand() + t*rand() + rand()) % (r - l + 1);
}

char ToLowerChar(char c) {
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    return c;
}

void fixToLower(string &s) {
    for (char &c : s) {
        c = ToLowerChar(c);
    }
}

void renderDeath(string answer) {
    int currentPic = 0;
    while (! kbhit()) {
        system("CLS");
        cout << "Sorry you lost :(\n";
        cout << "The correct answer is : " << answer << '\n';
        cout << HANGED[currentPic] << '\n';
        this_thread::sleep_for(chrono::milliseconds(100));
        currentPic = (currentPic + 1) % HANGED.size();
    }

    // remove this random keyboard hit from askToPlay()
    string s;
    cin >> s;
}
