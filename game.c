/*
 * game.c
 *
 *  Created on: Sep 10, 2023
 *      Author: anirudhjai
 */

/*
 * game.c
 *
 *  Created on: Sep 10, 2023
 *      Author: anirudhjai
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#define leaderboardSize 5

typedef struct{
	char name[25];
	int guesses;
} Player;

Player leaderboard[leaderboardSize];

int GetGuess(){
	int num;
	int isValid = 0;

	while(isValid == 0){
		if(scanf(" %d", &num)){
			isValid = 1;
		} else {
			printf("Invalid input, please try again. \n");

		}
	}
	return num;
}

int PlayGuessingGame(){
	srand(time(NULL));

	int randomNum = (rand() % 91) + 10;
	double squareRoot = sqrt(randomNum);
	int guess;

	printf("%.3f is the square root of what number?", squareRoot);

	int correct = 0;
	int numGuesses = 1;
	while(correct == 0){
		guess = GetGuess();
		if(guess > randomNum){
			printf("too high, guess again:\n");
			numGuesses++;
		} else if(guess < randomNum){
			printf("too low, guess again:\n");
			numGuesses++;
		} else {
			printf("You got it baby!\n");
			printf("You made %d guesses\n", numGuesses); // update here to count number of guesses and print and return them

			correct = 1;
		}
	}
	return numGuesses;
}


void loadLeaderboard(){ // loads leaderboard from file if available or fills with empty strings
	for (int i = 0; i < leaderboardSize; ++i) {
			    strcpy(leaderboard[i].name, ""); // set name to an empty string
			    leaderboard[i].guesses = INT_MAX;
	}
	FILE* file = fopen("leaderboard.txt", "r");
												//fill empty first, does not work properly with file read first
	if(file){
		for(int i = 0; i < leaderboardSize && fscanf(file, "%s %d",leaderboard[i].name, &leaderboard[i].guesses) == 2; i++);
		fclose(file);

	}
}

void saveLeaderboard(){ // saves leaderboard to txt file
	FILE* file = fopen("leaderboard.txt", "w");
	if (file) {
	        for (int i = 0; i < leaderboardSize; ++i) {
	                fprintf(file, "%s %d\n", leaderboard[i].name, leaderboard[i].guesses);
	        }
	        fclose(file);
	    } else {
	        printf("Error saving leaderboard to file!\n");
	    }
}

void updateLeaderboard(Player newPlayer){ // updates leaderboard by checking if new player has less guesses than others on leaderboard
	for(int i = 0; i < leaderboardSize; i++){
		if(newPlayer.guesses < leaderboard[i].guesses && newPlayer.guesses > 0){
			for(int j = leaderboardSize-1; j > i; j--){
				leaderboard[j] = leaderboard[j-1];
			}

			leaderboard[i] = newPlayer;
			break;
		}
	}
}
int main(){

	printf("Welcome! Press q to quit or any key to continue:\n");

	char input;
	scanf("%c", &input);
	loadLeaderboard();


	while(input != 'q'){
		Player newPlayer;
		printf("Please enter your name to start: ");
		scanf("%s", newPlayer.name);
		newPlayer.guesses = PlayGuessingGame(); // updated to return and store number of guesses for a player
		updateLeaderboard(newPlayer);
		printf("Here are the current leaders: \n"); // printing leaderboard
		for(int i = 0; i < leaderboardSize; i++){
		    if(leaderboard[i].guesses != INT_MAX){ // check if name is not an empty string
		        printf("%s made %d guesses\n", leaderboard[i].name, leaderboard[i].guesses);
		    }
		}

		printf("Press q to quit or any key to continue:\n");

		scanf(" %c", &input);

	}

	printf("Bye bye !");
	saveLeaderboard(); // saves leaderboard
	return 0;

}

