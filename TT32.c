#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to store each question and its options
struct Question {
    char question[255];
    char options[4][50];
    int correctOption;
};

// Function to load questions from a file (admin only)
void loadQuestions(struct Question round[], int numQuestions, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    for (int i = 0; i < numQuestions; i++) {
        // Read question text
        fgets(round[i].question, sizeof(round[i].question), file);
        strtok(round[i].question, "\n"); // Remove the newline character

        // Read options
        for (int j = 0; j < 4; j++) {
            fgets(round[i].options[j], sizeof(round[i].options[j]), file);
            strtok(round[i].options[j], "\n"); // Remove the newline character
        }

        // Read the correct option
        fscanf(file, "%d", &round[i].correctOption);
        fgetc(file); // Consume the newline character after the correct option
    }

    fclose(file);
}

int main() {
    // Define the array of questions for each round
    struct Question round1Questions[5];
    struct Question round2Questions[5];
    struct Question round3Questions[5];

    // Load questions from a file for each round (assuming "questions.txt" is the file name)
    loadQuestions(round1Questions, 5, "questions_round1.txt");
    loadQuestions(round2Questions, 5, "questions_round2.txt");
    loadQuestions(round3Questions, 5, "questions_round3.txt");

    // Now, you have populated 'round' arrays with questions from the respective files.

    // ... (rest of the game logic)
    
    return 0;
}
