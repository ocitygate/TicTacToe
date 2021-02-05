#include <stdio.h>

VOID print_board(board)
char board[];
{
	printf(" %c | %c | %c     0 | 1 | 2 \n", board[0], board[1], board[2] );
	printf("---+---+---   ---+---+---\n");
	printf(" %c | %c | %c     3 | 4 | 5 \n", board[3], board[4], board[5] );
	printf("---+---+---   ---+---+---\n");
	printf(" %c | %c | %c     6 | 7 | 8  \n", board[6], board[7], board[8] );
	printf("\n");
}

int is_valid_move(board, move)
char board[];
int move;
{
	if (board[move] == ' ')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int get_move(board, player)
char board[];
char player;
{
	char ch;
	int move;
	while (1)
	{
		printf("Player %c move:\n", player);
		ch = getch();
		if (ch >= '0' && ch <= '8')
		{
			move = ch - 48;
			if (is_valid_move(board, move))
			{
				return move;
			}
		}
		printf("Invalid move!\n");
		printf("\n");
	}
}

VOID play_move(board, player, move)
char board[];
char player;
int move;
{
	board[move] = player;
}

VOID change_player(player)
char *player;
{
		if (*player == 'O')
	{
		*player = 'X';
	}
	else
	{
		*player = 'O';
	}
}

int gameover(board)
char board[];
{
	if (board[0] != ' ' && board[0] == board[1] && board[0] == board[2]) return 1;
	if (board[3] != ' ' && board[3] == board[4] && board[3] == board[5]) return 1;
	if (board[6] != ' ' && board[6] == board[7] && board[6] == board[8]) return 1;
	if (board[0] != ' ' && board[0] == board[3] && board[0] == board[6]) return 1;
	if (board[1] != ' ' && board[1] == board[4] && board[1] == board[7]) return 1;
	if (board[2] != ' ' && board[2] == board[5] && board[2] == board[8]) return 1;
	if (board[0] != ' ' && board[0] == board[4] && board[0] == board[8]) return 1;
	if (board[2] != ' ' && board[2] == board[4] && board[2] == board[6]) return 1;
	return 0;
}

int game_state(board)
char board[];
{
	if (gameover(board))
	{
		return 1;
	}
	else if (board[0] != ' ' && board[1] != ' ' && board[2] != ' ' && board[3] != ' ' && board[4] != ' ' && board[5] != ' ' && board[6] != ' ' && board[7] != ' ' && board[8] != ' ')
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

VOID copy(src_board, src_player, dst_board, dst_player)
char src_board[];
char src_player;
char dst_board[];
char *dst_player;
{
	dst_board[0] = src_board[0];
	dst_board[1] = src_board[1];
	dst_board[2] = src_board[2];
	dst_board[3] = src_board[3];
	dst_board[4] = src_board[4];
	dst_board[5] = src_board[5];
	dst_board[6] = src_board[6];
	dst_board[7] = src_board[7];
	dst_board[8] = src_board[8];

	*dst_player = src_player;
}

int get_computer_move(board, player, levels, result)
char board[];
char player;
int levels;
int* result;
{
	char temp_board[9];
	char temp_player;
	int move;
	int move_result;
	int temp_result;

	int best_move;
	int best_result = -99;

	for(move = 0; move < 9; move++)
	{
		if (is_valid_move(board, move))
		{
			copy(board, player, temp_board, &temp_player);
			play_move(temp_board, temp_player, move);

			switch (game_state(temp_board))
			{
				case 1:
					move_result = 1;
					break;
				case 0:
					move_result = 0;
					break;
				case -1:
					if (levels == 0)
					{
						move_result = 0;
					}
					else
					{
						change_player(&temp_player);
						get_computer_move(temp_board, temp_player, levels - 1, &temp_result);

						move_result = -temp_result;
						break;
					}
			}
			
			if (move_result > best_result)
			{
				best_move = move;
				best_result = move_result;
			}
		}
	}
	*result = best_result;
	return best_move;
}

VOID game(computerO, computerX)
int computerO;
int computerX;
{
	char board[9];
	char player   = 'O';
	int  move;
	int result;

	board[0] = ' ';
	board[1] = ' ';
	board[2] = ' ';
	board[3] = ' ';
	board[4] = ' ';
	board[5] = ' ';
	board[6] = ' ';
	board[7] = ' ';
	board[8] = ' ';
	
	print_board(board);

	while (1)
	{	
		if ((player == 'O' && computerO) || (player == 'X' && computerX))
		{
			printf("Computer %c thinking...\n", player;
			move = get_computer_move(board, player, 5, &result);
		}
		else
		{
			move = get_move(board, player);
		}
		play_move(board, player, move);
		print_board(board);
		switch (game_state(board))
		{
			case 1:
				if ((player == 'O' && computerO) || (player == 'X' && computerX))
				{
					printf("Computer %c wins!\n", player);
				}
				else
				{
					printf("Player %c wins!\n", player);
				}
				printf("\n");
				return;
			case 0:
				printf("Draw!\n", player);
				printf("\n");
				return;
		}
		change_player(&player);
	}
}

VOID menu()
{
	int select;
	char ch;
    while (1)
	{
		while (1)
		{
			printf("TicTacToe\n");
			printf("=========\n");
			printf("\n");
			printf("1. Player   O vs Player   X\n");
			printf("2. Player   O vs Computer X\n");
			printf("3. Computer O vs Player   X\n");
			printf("4. Computer O vs Computer X\n");
			printf("0. Exit\n");
			printf("\n");

			printf("Select:\n");
			ch = getch();
			select = ch - 48;
			
			printf("\n");

			switch (select)
			{
				case 1:
					game(0, 0);
					break;
				case 2:
					game(0, 1);
					break;
				case 3:
					game(1, 0);
					break;
				case 4:
					game(1, 1);
					break;
				case 0:
					return;
				default:
					printf("Invalid option!\n");
					printf("\n");
			}
		}
	}
}

main()
{
	menu();
}
