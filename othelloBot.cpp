#include <bits/stdc++.h>

using namespace std;

#define dbg(x) cout << #x << " = " << x << endl

const int EMPTY = 2;
const int BLACK = 1;
const int WHITE = 0;

struct GameBoard {
	//int board[8][8];
	vector<vector<int>> board;
	bool turn; //
	int movesMade;

	GameBoard() {
		board.assign(8, vector<int>(8, EMPTY));
		board[3][3] = board[4][4] = BLACK;
		board[4][3] = board[3][4] = WHITE;

		turn = 1;
		movesMade = 0;
	}

	void printBoard() {
		system("clear");
		cout << "\033[32m";
		for(int i = 0; i < 8 * 3 + 1; i++) cout << '-';
		cout << '\n';
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				if (j == 0) cout << '|';
				if (board[i][j] == EMPTY) cout << "  |";
				if (board[i][j] == BLACK) cout << "\u26ab|";
				if (board[i][j] == WHITE) cout << "\u26aa|";
			}
			cout << '\n';
			for(int i = 0; i < 8 * 3 + 1; i++) cout << '-';
			cout << '\n';
		}
		cout << "\033[0m";
	}

	bool inside(int row, int col) {
		return (0 <= row && row < 8 && 0 <= col && col < 8);
	}

	bool gameOver() {
		return (int)(getMoves().size()) == 0; 
	}
	
	vector<pair<int, int>> getMoves() {
		vector<pair<int, int>> possibleMoves;
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				if (board[i][j] == EMPTY && movePossible(i, j)) {
					possibleMoves.push_back({i, j});
				}
			}
		}
		return possibleMoves;
	}

	bool movePossible(int row, int col) {
		if (board[row][col] != EMPTY || movesMade == 64) {
			return false;
		}

		int brick = turn;

		for(int dy = -1; dy <= 1; dy++) {
			for(int dx = -1; dx <= 1; dx++) {
				if (dx == 0 && dy == 0) continue;
				int y = row, x = col;
				bool wentInside = 0;
				while(inside(y + dy, x + dx) && (board[y+dy][x+dx] == (brick ^ 1))) {
					wentInside = 1;
					y += dy;	
					x += dx;
				}
				y += dy;
				x += dx;
				if (wentInside && inside(y, x) && board[y][x] == brick) {
					return true;
				}
			}
		}

		return false;
	}

	int evaluate() {
		int eval = 0;
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				if (board[i][j] == (int) turn) {
					eval++;	
				}
				else if (board[i][j] == (((int)turn) ^ 1)) eval--;
			}
		}
		return eval;
	}

	int search(int depth) {
		if (depth == 0) return evaluate();
		int minEval = 100000000;
		vector<pair<int, int>> moves = getMoves();	
		for(auto &mv: moves) {
			GameBoard curBoard;
			curBoard.board = board;
			curBoard.turn = turn;
			curBoard.movesMade = movesMade;
			curBoard.tryMove(mv.first, mv.second);
			minEval = min(curBoard.search(depth - 1), minEval);
		}
		return minEval;
	}

	void performBestMove(int depth) {
		vector<pair<int, int>> moves = getMoves();	
		int maxEval = -100000000;
		pair<int, int> bestMove;
		for(auto &mv: moves) {
			GameBoard curBoard;
			curBoard.board = board;
			curBoard.turn = turn;
			curBoard.movesMade = movesMade;
			curBoard.tryMove(mv.first, mv.second);
			int curEval = curBoard.search(2);
			if (curEval > maxEval) {
				maxEval = curEval;
				bestMove = mv;
			}
			maxEval = max(curBoard.search(depth), maxEval);
		}
		tryMove(bestMove.first, bestMove.second);
	}

	int tryMove(int row, int col) {
		bool moveMade = 0;

		if (board[row][col] != EMPTY || movesMade == 64) {
			return 0;
		}

		int brick = turn;


		for(int dy = -1; dy <= 1; dy++) {
			for(int dx = -1; dx <= 1; dx++) {
				if (dx == 0 && dy == 0) continue;
				int y = row, x = col;
				bool wentInside = 0;
				while(inside(y + dy, x + dx) && (board[y+dy][x+dx] == (brick ^ 1))) {
					wentInside = 1;
					y += dy;	
					x += dx;
				}
				y += dy;
				x += dx;
				if (wentInside && inside(y, x) && board[y][x] == brick) {
					moveMade = 1;
					y = row, x = col;
					while(inside(y + dy, x + dx) && (board[y+dy][x+dx] == (brick ^ 1))) {
						y += dy;	
						x += dx;
						board[y][x] = brick;
					}
				}
			}
		}

		if (moveMade) {
			board[row][col] = brick;
			movesMade++;
		}

		turn ^= moveMade;
		return moveMade;
	}

};

int main() {

	GameBoard board;
	board.printBoard();
	int row, col;
	while(cin >> row) {
		cin >> col;
		row--, col--;
		bool attempt = board.tryMove(row, col);
		if (!attempt) {
			cout << "not valid move\n";
		}
		else {
			board.printBoard();
			board.performBestMove(6);
			sleep(2);
			board.printBoard();
			if (board.gameOver()) {
				if (board.evaluate() > 0) {
					cout << "Black wins";
				}
				else cout << "White wins";
				break;
			}
		}
	}
}

