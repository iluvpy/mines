#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstring>


class MinesCLI {
public:
    MinesCLI() {
        initNCurses();
        setGameDifficulty();
    }

    void initNCurses() {
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, true);
    }

    void setGameDifficulty() {
        constexpr char* welcomeMsg = "Welcome to Mines!";
        constexpr char* modesMsg = "Chose a mode:";
        std::vector<std::string> modes = {};
        for (int i = 1; i < 6; i++) {
            std::string n = std::to_string(i*10);
            modes.push_back(n + "x" + n);
        }
        int row, col;
        getmaxyx(stdscr, row, col);
        int startRow = row / 2;
        int startCol = (col - strlen(welcomeMsg)) / 2;
        mvprintw(startRow, startCol, "%s", welcomeMsg);
        startRow++;

        startCol = (col - strlen(modesMsg)) / 2;
        mvprintw(startRow, startCol, "%s", modesMsg);

        refresh();
        int ch = 0;
        int highlightedIndex = 0;
        startCol = (col - 5) / 2; // -5 = strlen("10x10")
        do  {
            if (ch == KEY_UP) {
                highlightedIndex -= highlightedIndex > 0 ? 1 : 0;
            } else if (ch == KEY_DOWN) {
                highlightedIndex += highlightedIndex < modes.size() ? 1 : 0; 
            }
            if (ch == 10) { break;}
            int i = 0;
            // print possible choices
            for (const auto& mode : modes) {
                startRow++;
                if (i == highlightedIndex) {
                    attron(A_REVERSE);
                }
                mvprintw(startRow, startCol, "%s", mode.c_str());
                attroff(A_REVERSE);
                i++;
            }
            startRow -= modes.size();
            refresh();

        } while ((ch = getch()) != 'q');

        mvprintw(0, 0, "chose %s", modes[highlightedIndex].c_str());
        refresh();

        game();
    }

    void game() {
        getch();
    }

    ~MinesCLI() {
        endwin();
    }

private:

};


int main() {
    MinesCLI mines;
    return 0;
}