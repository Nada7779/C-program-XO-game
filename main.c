#include <stdio.h>
typedef unsigned char uint8_t;
uint8_t board_arr[] = { 49,50,51,52,53,54,55,56,57 };
uint8_t symbol[2];

void drawBoard(uint8_t* board);
void updateBoard(uint8_t* board, uint8_t position, uint8_t value);
uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t* symbol);
void setPlayerConfig(uint8_t* configArray);
void loadAndUpdate(uint8_t playerNumber);
void getGameState(uint8_t* board, uint8_t* gameState);

main() {
	uint8_t state;
	uint8_t playerNumber;
	uint8_t* gameState = &state;
	drawBoard(board_arr);
	setPlayerConfig(symbol);
	
	playerNumber = 2;
	while (1) {
		getGameState(board_arr, gameState);
		if (state == 2) {
			if (playerNumber == 2) playerNumber = 1;
			else if (playerNumber == 1) playerNumber = 2;
			loadAndUpdate(playerNumber);
			drawBoard(board_arr);
		}
		else if (state == 1) { printf("Game gone into draw case no winner"); return 0; }
		else if (state == 0) { printf("player %d is the winner", playerNumber); return 0; }
	}
}

void drawBoard(uint8_t* board) {
	printf("-\t-\t-\n");
	printf("%c\t%c\t%c\n", board[0], board[1], board[2]);
	printf("%c\t%c\t%c\n", board[3], board[4], board[5]);
	printf("%c\t%c\t%c\n-\t-\t-\n", board[6], board[7], board[8]);
}
void updateBoard(uint8_t* board, uint8_t position, uint8_t value) {
	board[position] = value;
}
uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t* symbol) {
	uint8_t check_symbol;
	printf("\nchoose your symbol x or o:");
	scanf(" %c", &check_symbol);
	if (check_symbol != 'x' && check_symbol != 'X' && check_symbol != 'O' && check_symbol != 'o') {
		printf("\nwrong choice please enter X or O\n");
		return 1;
	}
	else if (check_symbol == symbol[0] || check_symbol == symbol[1]) {
		printf("\nsymbol is already taken please enter another symbol\n");
		return 1;
	}
	else {
		uint8_t y = playerNumber-1;
		symbol[y] = check_symbol;
		return 0;
	}
}
void setPlayerConfig(uint8_t* configArray) {
	uint8_t playerNumber = 1;
	printf("\nplayer number (%d) : ",playerNumber);
	int x = getPlayerSymbol(playerNumber, configArray);
	switch (x) {
	case 1: getPlayerSymbol(playerNumber, configArray); break;
	case 0:
	default: printf("***next turn***\n");
	}
	playerNumber = 2;
	printf("\nplayer number (%d) : ", playerNumber);
	x = getPlayerSymbol(playerNumber, configArray);
	switch (x) {
	case 1: getPlayerSymbol(playerNumber, configArray); break;
	case 0:
	default: printf("***next turn***\n");}
}
void loadAndUpdate(uint8_t playerNumber) {
	int turn = playerNumber - 1;
	int position;
	printf("\n player %d enter your position:", playerNumber);
	scanf(" %d", &position);
	uint8_t playerSymbol = symbol[turn];
	board_arr[position - 1] = playerSymbol;
}
void getGameState(uint8_t* board, uint8_t* gameState) {
	int counter = 0;
	for (int i = 0; i < 9; i++) {
		if (board[i] != i + 49) counter += 1;
	}
	if (counter == 9) *gameState = 1;
	else if (board[0] == board[1] && board[1] == board[2]) *gameState = 0;
	else if (board[3] == board[4] && board[4] == board[5]) *gameState = 0;
	else if (board[6] == board[7] && board[7] == board[8]) *gameState = 0;
	else if (board[0] == board[3] && board[0] == board[6]) *gameState = 0;
	else if (board[1] == board[4] && board[4] == board[7]) *gameState = 0;
	else if (board[2] == board[5] && board[5] == board[8]) *gameState = 0;
	else if (board[0] == board[4] && board[4] == board[8]) *gameState = 0;
	else if (board[2] == board[4] && board[4] == board[6]) *gameState = 0;
	else *gameState = 2;
}
