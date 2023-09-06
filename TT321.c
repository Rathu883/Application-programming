#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to store each question and its options
struct Question {
    char question[255];
    char options[4][50];
    int correctOption;
};

// Function to display a question and get the user's answer
int askQuestion(struct Question q) {
    int userAnswer;

    printf("%s\n", q.question);
    for (int i = 0; i < 4; i++) {
        printf("%d) %s\n", i + 1, q.options[i]);
    }
    printf("Your answer (1-4): ");
    scanf("%d", &userAnswer);

    return userAnswer;
}

// Function to load questions from a file (admin only)
void loadQuestions(struct Question round[], int numQuestions, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    for (int i = 0; i < numQuestions; i++) {
        // Read question text
        fscanf(file, " %[^\n]", round[i].question);

        // Read options
        for (int j = 0; j < 4; j++) {
            fscanf(file, " %[^\n]", round[i].options[j]);
        }

        // Read the correct option
        fscanf(file, "%d", &round[i].correctOption);
    }

    fclose(file);
}

int main() {
    // Define the array of questions for each round
    struct Question round1Questions[5];
    struct Question round2Questions[5];
    struct Question round3Questions[5];

    // Load questions from files for each round (assuming "roundX.txt" as file names, where X is the round number)
    loadQuestions(round1Questions, 5, "round1.txt");
    loadQuestions(round2Questions, 5, "round2.txt");
    loadQuestions(round3Questions, 5, "round3.txt");

    // Initialize player's name and score
    char playerName[50];
    int totalScore = 0;

    printf("Welcome to the Quiz Game!\n");
    printf("Enter your name: ");
    scanf("%s", playerName);

    // Play each round
    struct Question* currentRound;
    for (int round = 0; round < 3; round++) {
        if (round == 0) currentRound = round1Questions;
        else if (round == 1) currentRound = round2Questions;
        else currentRound = round3Questions;

        printf("\nRound %d:\n", round + 1);

        int roundScore = 0;
        for (int q = 0; q < 5; q++) {
            int userAnswer = askQuestion(currentRound[q]);
            if (userAnswer == currentRound[q].correctOption) {
                printf("Correct!\n");
                roundScore++;
            } else {
                printf("Wrong!\n");
            }
        }

        totalScore += roundScore;
        printf("Round %d Summary:\n", round + 1);
        printf("- Name: %s\n", playerName);
        printf("- Score: %d\n", roundScore);

        if (roundScore >= 3 && round < 2) {
            printf("\nCongratulations! You've qualified for the next round.\n");
        } else if (round < 2) {
            printf("\nUnfortunately, you did not qualify for the next round. Better luck next time!\n");
            break;
        }
    }

    printf("\nGame Over\n");
    printf("- Final Score: %d\n", totalScore);
    printf("Thank you for playing!\n");

    return 0;
}
