#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstring>
#include <ctime>
#include <random>

class BoardSquare {
public:
    bool m_isMine;
    bool m_isFlagged = false;
    bool m_isUncovered = false;
    BoardSquare(bool isMine) : m_isMine(isMine) {}
};

class MinesCLI {

private:
    std::vector<std::vector<BoardSquare>> m_board;

public:
    MinesCLI() {
        initNCurses();
        int difficulty = setGameDifficulty();
        generateBoard(difficulty);
        gameLoop();
    }

    void initNCurses() {
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, true);
    }

    float randomFloat(float min, float max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution dist(min, max);
        return dist(gen);
    }

    /*
        @brief prints out screen and lets player choose a game difficulty
        ie 10x10, 20x20, etc
        @returns difficulty (0 = 10x10, 1 = 20x..) 
    */
    int setGameDifficulty() {
        const std::string welcomeMsg = "Welcome to Mines!";
        const std::string modesMsg = "Chose a mode:";

        // 10x10, 20x20, 30x30
        std::vector<std::string> modes = {};
        for (int i = 1; i < 6; i++) { // 10x10, 20x20..50x50
            std::string n = std::to_string(i*10);
            modes.push_back(n + "x" + n);
        }

        // find center row, and column for welcome text and modes text and print them out
        int row, col;
        getmaxyx(stdscr, row, col);
        int startRow = row / 2;
        int startCol = (col - welcomeMsg.size()) / 2;
        mvprintw(startRow, startCol, "%s", welcomeMsg.c_str());
        startRow++;

        startCol = (col - modesMsg.size()) / 2;
        mvprintw(startRow, startCol, "%s", modesMsg.c_str());

        refresh(); // show printed 


        // loop that asks player 
        int ch = -1;
        int highlightedIndex = 0;
        startCol = (col - modes[0].size()) / 2;
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

        return highlightedIndex;
    }

    void generateBoard(int difficultyIndex) {
        int widthAndHeight = difficultyIndex * 10;
        for (int i = 0; i < widthAndHeight; i++) {
            std::vector<BoardSquare> row;
            for (int j = 0; j < widthAndHeight; j++) {
                row.push_back(BoardSquare(randomFloat(0.0f, 1.0f) >= 0.3f));
            }
            m_board.push_back(row);
        }
    }

    void gameLoop() {
        int ch = 0;
        do {
            updateBoard();
            printBoard();
            refresh();
        } while ((ch = getch() != 'q'));
    }

    // TODO
    void updateBoard() {

    }

    void printBoard() {
        for (int i = 0; i < m_board.size(); i++) {
            for (int j = 0; j < m_board[0].size(); i++) {
                if (!m_board[i][j].m_isUncovered) {
                    mvprintw(i, j, "O");
                }
            }
        }
    }

    ~MinesCLI() {
        endwin();
    }

};


int main() {
    MinesCLI mines;
    return 0;
}