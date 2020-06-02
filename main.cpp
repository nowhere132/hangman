#include <time.h>
#include "handlers/handlers.h"
#include "helpers/helpers.h"
using namespace std;

int main() {
    srand(time(0));
    buildOurLib();  // get the data for our game

    int matchPlayed = 0, matchWon = 0;
    while (1) {
        int choice = askToPlay();
        if (choice == 0) break;
        matchPlayed++, matchWon += solve();

        // our stat about the player
        system("CLS");
        printf("Congratulation!\n");
        printf("You played %d games, and won %d games", matchPlayed, matchWon);
        PutNotice("", 3);
    }
}
