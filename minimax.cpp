#include <iostream>
using namespace std;

#define PLAYER_1 '1'
#define PLAYER_2 '2'
#define EMPTY_SPACE '0'
#define MIN -1000
#define MAX 1000
#define WIN 10
#define LOSS -10
#define COMMAND_SIZE 40

void deleteBoard(char** board, int n) {
        for (int i = 0; i < n; i++) delete[] board[i];
        delete[] board;
}

void printBoard(char** board, int n, int m) {
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        printf("%c ", board[i][j]);
                }
                printf("\n");
        }
}

bool isBoardFull(char** board, int n, int m) {
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        if (board[i][j] == EMPTY_SPACE) {
                                return false;
                        }
                }
        }
        return true;
}

bool vertical(char** board, char current, int y, int x, int n, int k, bool c) {
        int counter = 1;
        bool end1 = false;
        bool end2 = false;
        for (int i = y - 1; i >= 0; i--) {
                if (board[i][x] != current) {
                        if (board[i][x] == EMPTY_SPACE) end1 = true;
                        break;
                }
                else counter++;
        }
        for (int i = y + 1; i < n; i++) {
                if (board[i][x] != current) {
                        if (board[i][x] == EMPTY_SPACE) end2 = true;
                        break;
                }
                else counter++;
        }
        if (counter >= k) return true;
        else if (counter == k - 1 && end1 && end2 && c) return true;
        else return false;
}

bool horizontal(char** board, char current, int y, int x, int m, int k, bool c) {
        int counter = 1;
        bool end1 = false;
        bool end2 = false;
        for (int i = x - 1; i >= 0; i--) {
                if (board[y][i] != current) {
                        if (board[y][i] == EMPTY_SPACE) end1 = true;
                        break;
                }
                else counter++;
        }
        for (int i = x + 1; i < m; i++) {
                if (board[y][i] != current) {
                        if (board[y][i] == EMPTY_SPACE) end2 = true;
                        break;
                }
                else counter++;
        }
        if (counter >= k) return true;
        else if (counter == k - 1 && end1 && end2 && c) return true;
        else return false;
}

bool diagonalUpward(char** board, char current, int y, int x, int n, int m, int k, bool c) {
        int counter = 1;
        bool end1 = false;
        bool end2 = false;
        for (int i = y - 1, j = x + 1; i >= 0 && j < m; i--, j++) {
                if (board[i][j] != current) {
                        if (board[i][j] == EMPTY_SPACE) end1 = true;
                        break;
                }
                else counter++;
        }
        for (int i = y + 1, j = x - 1; i < n && j >= 0; i++, j--) {
                if (board[i][j] != current) {
                        if (board[i][j] == EMPTY_SPACE) end1 = true;
                        break;
                }
                else counter++;
        }
        if (counter >= k) return true;
        else if (counter == k - 1 && end1 && end2 && c) return true;
        else return false;
}

bool diagonalDownward(char** board, char current, int y, int x, int n, int m, int k, bool c) {
        int counter = 1;
        bool end1 = false;
        bool end2 = false;
        for (int i = y + 1, j = x + 1; i < n && j < m; i++, j++) {
                if (board[i][j] != current) {
                        if (board[i][j] == EMPTY_SPACE) end1 = true;
                        break;
                }
                else counter++;
        }
        for (int i = y - 1, j = x - 1; i >= 0 && j >= 0; i--, j--) {
                if (board[i][j] != current) {
                        if (board[i][j] == EMPTY_SPACE) end1 = true;
                        break;
                }
                else counter++;
        }
        if (counter >= k) return true;
        else if (counter == k - 1 && end1 && end2 && c) return true;
        else return false;
}

bool checkWin(char** board, int n, int m, int k, bool c) {
        for (int y = 0; y < n; y++) {
                for (int x = 0; x < m; x++) {
                        if (board[y][x] != EMPTY_SPACE) {
                                if (horizontal(board, board[y][x], y, x, m, k, c)) return true;
                                else if (vertical(board, board[y][x], y, x, n, k, c)) return true;
                                else if (diagonalUpward(board, board[y][x], y, x, n, m, k, c)) return true;
                                else if (diagonalDownward(board, board[y][x], y, x, n, m, k, c)) return true;
                        }
                }
        }
        return false;
}

void genAllPosMov(int n, int m, int k, char player) {
        int counter = 0;
        char** board = new char* [n];
        for (int i = 0; i < n; i++) board[i] = new char[m];
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        cin >> board[i][j];
                        if (board[i][j] == EMPTY_SPACE) counter++;
                }
        }
        if (checkWin(board, n, m, k, false) || isBoardFull(board, n, m)) {
                printf("0\n");
                deleteBoard(board, n);
                return;
        }
        printf("%d\n", counter);
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        if (board[i][j] == EMPTY_SPACE) {
                                board[i][j] = player;
                                printBoard(board, n, m);
                                board[i][j] = EMPTY_SPACE;
                        }
                }
        }
        deleteBoard(board, n);
}

void genAllPosCutIfGameOver(int n, int m, int k, char player) {
        int counter = 0;
        char** board = new char* [n];
        for (int i = 0; i < n; i++) board[i] = new char[m];
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        cin >> board[i][j];
                        if (board[i][j] == EMPTY_SPACE) counter++;
                }
        }
        if (checkWin(board, n, m, k, false) || isBoardFull(board, n, m)) {
                printf("0\n");
                deleteBoard(board, n);
                return;
        }
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        if (board[i][j] == EMPTY_SPACE) {
                                board[i][j] = player;
                                if (checkWin(board, n, m, k, false)) {
                                        printf("1\n");
                                        printBoard(board, n, m);
                                        deleteBoard(board, n);
                                        return;
                                }
                                board[i][j] = EMPTY_SPACE;
                        }
                }
        }
        printf("%d\n", counter);
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        if (board[i][j] == EMPTY_SPACE) {
                                board[i][j] = player;
                                printBoard(board, n, m);
                                board[i][j] = EMPTY_SPACE;
                        }
                }
        }
        deleteBoard(board, n);
}

int minimax(char** board, int depth, bool isMax, int n, int m, int k, int alpha, int beta) {
        if (checkWin(board, n, m, k, false)) {
                if (isMax) {
                        return LOSS;
                }
                else {
                        return WIN;
                }
        }
        if (isBoardFull(board, n, m)) return 0;
        if (isMax) {
                int best = MIN;
                int temp = 0;
                for (int i = 0; i < n; i++) {
                        for (int j = 0; j < m; j++) {
                                if (board[i][j] == EMPTY_SPACE) {
                                        board[i][j] = PLAYER_1;
                                        temp = minimax(board, depth + 1, !isMax, n, m, k, alpha, beta);
                                        board[i][j] = EMPTY_SPACE;
                                        if (temp > best) best = temp;
                                        if (best > alpha) alpha = best;
                                        if (beta <= alpha) break;
                                }
                        }
                }
                return best;
        }
        else {
                int best = MAX;
                int temp = 0;
                for (int i = 0; i < n; i++) {
                        for (int j = 0; j < m; j++) {
                                if (board[i][j] == EMPTY_SPACE) {
                                        board[i][j] = PLAYER_2;
                                        temp = minimax(board, depth + 1, !isMax, n, m, k, alpha, beta);
                                        board[i][j] = EMPTY_SPACE;
                                        if (temp < best) best = temp;
                                        if (best < beta) beta = best;
                                        if (beta <= alpha) break;
                                }
                        }
                }
                return best;
        }
}

void solve(int n, int m, int k, char player) {
        char** board = new char* [n];
        for (int i = 0; i < n; i++) board[i] = new char[m];
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        cin >> board[i][j];
                }
        }
        if (!checkWin(board, n, m, k, false) && isBoardFull(board, n, m)) {
                printf("BOTH_PLAYERS_TIE\n");
                deleteBoard(board, n);
                return;
        }
        int score;
        if (player == PLAYER_1) score = minimax(board, 0, true, n, m, k, MIN, MAX);
        else score = minimax(board, 0, false, n, m, k, MIN, MAX);

        if (score == WIN) printf("FIRST_PLAYER_WINS\n");
        else if (score == LOSS) printf("SECOND_PLAYER_WINS\n");
        else printf("BOTH_PLAYERS_TIE\n");
        deleteBoard(board, n);
}

int main() {
        int n, m, k;
        char player;
        char command[COMMAND_SIZE];

        while (cin >> command) {
                cin >> n >> m >> k >> player;
                if (!strcmp(command, "GEN_ALL_POS_MOV")) {
                        genAllPosMov(n, m, k, player);
                }
                if (!strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER")) {
                        genAllPosCutIfGameOver(n, m, k, player);
                }
                if (!strcmp(command, "SOLVE_GAME_STATE")) {
                        solve(n, m, k, player);
                }
        }

        return 0;
}