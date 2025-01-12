#include <bits/stdc++.h>

using namespace std;

#define dbg(x) cout << #x << " = " << x << endl

const int EMPTY = 2;
const int BLACK = 1;
const int WHITE = 0;

struct GameBoard {
	int board[8][8];
	bool turn; //
	int movesMade;

	GameBoard() {
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				board[i][j] = EMPTY;
			}
		}
		board[3][3] = board[4][4] = BLACK;
		board[4][3] = board[3][4] = WHITE;

		turn = 1;
		movesMade = 0;
	}

	void printBoard() {
		system("clear");
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				if (board[i][j] == EMPTY) cout << '*';
				if (board[i][j] == BLACK) cout << 'X';
				if (board[i][j] == WHITE) cout << 'O';
			}
			cout << '\n';
		}
	}

	bool inside(int row, int col) {
		return (0 <= row && row < 8 && 0 <= col && col < 8);
	}

	int tryMove(int row, int col, int player) {
		bool moveMade = 0;

		if (board[row][col] != EMPTY || player != turn || movesMade == 64) {
			return 0;
		}

		int brick = player;

		for(int dy = -1; dy <= 1; dy++) {
			for(int dx = -1; dx <= 1; dx++) {
				if (dx == 0 && dy == 0) continue;
				int y = row, x = col;
				while(inside(y + dy, x + dx) && (board[y+dy][x+dx] == (brick ^ 1))) {
					y += dy;	
					x += dx;
				}
				y += dy;
				x += dx;
				if (inside(y, x) && board[y][x] == brick) {
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
	int row, col, player;
	while(cin >> player) {
		cin >> row >> col;
		bool attempt = board.tryMove(row, col, player);
		if (!attempt) {
			cout << "not valid move\n";
		}
		else {
			board.printBoard();
			//board.AI();
			//sleep(2);
			//board.printBoard();
		}
	}
}

