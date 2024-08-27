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
        int start_row = row / 2;
        int start_col = (col - strlen(welcomeMsg)) / 2;
        mvprintw(start_row, start_col, "%s", welcomeMsg);
        start_row++;

        start_col = (col - strlen(modesMsg)) / 2;
        mvprintw(start_row, start_col, "%s", modesMsg);

        // -5 = strlen("10x10")
        start_col = (col - 5) / 2;

        for (const auto& mode : modes) {
            start_row++;
            mvprintw(start_row, start_col, "%s", mode.c_str());
        }

        mvprintw(start_row, start_col, "%s", modesMsg);

        refresh();
        
        while (1) {
            int c = getch();
            if (c == 44) {
                exit(0);
            }
        }

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