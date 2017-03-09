#include <stdio.h>

#define ROWS 3
#define COLS 3
typedef char Board[ROWS][COLS];

void printBoard(Board board)
{
    puts("");
    for(int y = 0; y < ROWS; ++y)
    {
        for(int x = 0; x < COLS; ++x)
        {
            printf(" %c", board[y][x]);
            if(x < 2)
            {
                printf(" \u2502");
            }
        }
        puts("");
        if(y < 2)
        {
            printf("\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u253c\u2500\u2500\u2500\n");
        }
    }
    puts("");
}

int hasWinner(Board board)
{
    return ((board[0][0] == board[0][1] && board[0][0] == board[0][2]) ||
            (board[1][0] == board[1][1] && board[1][0] == board[1][2]) ||
            (board[2][0] == board[2][1] && board[2][0] == board[2][2]) ||
            (board[0][0] == board[1][0] && board[0][0] == board[2][0]) ||
            (board[0][1] == board[1][1] && board[0][1] == board[2][1]) ||
            (board[0][2] == board[1][2] && board[0][2] == board[2][2]) ||
            (board[0][0] == board[1][1] && board[0][0] == board[2][2]) ||
            (board[0][2] == board[1][1] && board[0][2] == board[2][0]));
}

int main()
{
	int winner = 0;
	int choice = 0;
	int row = 0;
	int column = 0;
	int i;

	Board board = {
		{'1','2','3'},
		{'4','5','6'},
		{'7','8','9'}
	};


	for (i = 0; i<9 && !winner; i++)
    {
		int player = i%2 + 1;
		printBoard(board);

		do
        {
			printf("\nJogador %d, introduza o numero do quadrado "
                   "onde quer colocar o seu %c: ",
                   player,(player==1)?'X':'O');
			scanf("%d", &choice);

			row = --choice/3;
			column = choice%3;
		} while(choice<0 || choice>9 || board [row][column]>'9');

		board[row][column] = (player == 1) ? 'X' : 'O';
		if (hasWinner(board))
        {
            winner = player;
        }
	}

	printBoard(board);

	if(!winner)
    {
		printf("Empate\n");
	}
    else
    {
		printf("O Jogador %d venceu\n", winner);
	}

	return 0;
}
