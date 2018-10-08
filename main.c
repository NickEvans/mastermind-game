#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int read(char * input, int * check) {
	int i = 0, num, len;
	while (sscanf(input, "%1d%n", &num, &len) == 1) {
		check[i] = num;
		input += len;
		i++;
	}
	return 0;
}

void generate(int * sol) {
	srand(time(NULL));
	int i, n = 10, deck[10];
	for (i = 0; i < 10; i++) {
		deck[i] = i;
	}
	for (i = 0; i < n - 1; i++)
	{
		int j = i + rand() / (RAND_MAX / (n - i) + 1);
		int t = deck[j];
		deck[j] = deck[i];
		deck[i] = t;
	}
	for (i = 0; i < 4; i++) {
		sol[i] = deck[i];
	}
	return;
}

int compare(int * check, int * sol) {
	int white = 0, grey = 0, i, p;
	for (i = 0; i < 4; i++) {
		for (p = 0; p < 4; p++) {
			if (check[i] == sol[p]) {
				if (i == p)
					white++;
				else
					grey++;
				break;
			}
		}
	}
	for (i = 0; i < white; i++) {
		printf("X");
	}
	for (i = 0; i < grey; i++) {
		printf("O");
	}
	for (i = 0; i < (4 - white - grey); i++) {
		printf("-");
	}
	if (white == 4)
		return 1;
	else
		return 0;
}
int main()
{
	int i, lives, sol[4] = { 0 }, check[4], playing = 0;
	char input[4];

	printf("CODEBREAKER\n\nType \"help\" for rules!\n\n");

	do {

		generate(sol);
		lives = 8;

		printf("\nEnter your 4-digit guess!\n");

		while (lives >= 0) {
			scanf("%4s", input);

			if (strcmp(input, "help") == 0) {
				printf("\nTry to guess the code! The solution is four non-repeating digits.\nX: You have a correct number in a correct position.\nO: You have a correct number in the wrong position\n-: You have a number not in the solution\n\nEnter a guess:\n");
				continue;
			}

			read(input, check);

			if (compare(check, sol) == 1) {
				printf("\nYou cracked the code!\n");
				break;
			}
			if (lives == 0) {
				printf("\nYou lose!\n");
				printf("The solution was ");
				for (i = 0; i < 4; i++) {
					printf("%d", sol[i]);
				}
				break;
			}
			printf("\n%d remaining chances.\n\n", lives--);
		}
		printf("\nEnter 1 to play again or anything else to quit:\n");
		scanf("%d", &playing);
	} while (playing == 1);

	return 0;
}

