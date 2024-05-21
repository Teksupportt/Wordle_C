#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void clearInputBuffer() {   //clear leftover input
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char* RandomWordGenerator(){    //pick a random word from file
    FILE* file = fopen("words.txt","r+");
    char tempwordbank[11514][6];
    char wordbank[5757][6];
    int i = 0;
    while(i < 11514 && fgets(tempwordbank[i], sizeof(tempwordbank[i]), file) != NULL){
        i++;
    }
    char* newline = strchr(tempwordbank[i], '\n');
    if (newline != NULL) {
        *newline = '\0';
    }
    for(int a = 0; a < 5757; a++){
        for(int b = 0; b < 5; b++){
            wordbank[a][b] = tempwordbank[a*2][b];  //file was being stupid so I hard coded all the empty spaces out
        }
    }
    fclose(file);
    
    srand(time(NULL));
    char* wordle = malloc(6 * sizeof(char));
    int r = rand() % 5758;
    strcpy(wordle, wordbank[r]);
    return wordle;
}

char* wordCheck(char* wordle, char* input, char* unused){   //compare input to word to guess and print output + legend + keyboard
    char output[5] = "_____";
    int count = 0;
    
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(wordle[i] == input[j] && i == j){
                output[i] = 'O';
            }else if(wordle[i] == input[j] && i != j && output[j] != 'O'){
                output[j] = 'X';
            }else{
                for(int x = 0; x < 26; x++){
                    if(input[i] == unused[x]){
                        unused[x] = '_';
                    }
                }
            }
        }
    }
    
    for(int i = 0; i < 5; i++){
        printf("%c", output[i]);
    }
    
    printf("\n\n");
    printf("\"O\" - correct placement\n");
    printf("\"X\" - incorrect placement\n");
    printf("\"_\" - Not part of the word\n");
    printf("\n");
    
    for(int i = 0; i < 10; i++){
        printf("%c ", unused[i]);
    }
    printf("\n");
    
    for(int i = 10; i < 19; i++){
        printf("%c ", unused[i]);
    }
    printf("\n");
    
    for(int i = 19; i < 26; i++){
        printf("%c ", unused[i]);
    }
    printf("\n\n");
    return unused;
}

void GAME(){    //main game function
    char* Wordle = RandomWordGenerator();
    char unused[27] = "qwertyuiopasdfghjklzxcvbnm";
    char input[6];
    int turn = 1;
    printf("Welcome to Wordle! Enter a 5 letter word as your first guess.\n");
    printf("TURN: %d\n", turn);
    scanf("%5s", input);
    input[5] = '\0';
    clearInputBuffer();
    strcpy(unused, wordCheck(Wordle, input, unused));
    turn++;
    while(turn <= 5){   //loop turns
        printf("TURN: %d\n", turn);
        if(turn == 5){
            printf("Last turn!\n");
        }
        printf("Enter your next guess.\n");
        scanf("%5s", input);
        input[5] = '\0';
        clearInputBuffer();
        strcpy(unused, wordCheck(Wordle, input, unused));
        turn++;
    }
    printf("You lost!\n");
    printf("The word was: %s", Wordle);
    return;
}

int main()
{
    GAME();
    return 0;
}