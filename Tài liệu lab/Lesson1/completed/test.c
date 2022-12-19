#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Word{
    char character[50];
    int apperance;
    int start[50];
    int end[50];
    int type;
} Word;

typedef struct StopWord{
    char characters[50];
} StopWord;

int main()
{
    FILE* file1; 
    file1 = fopen("stopw.txt","r");
    if(file1 == NULL) {
        perror("Error! ");
        exit(0);
    }
    StopWord stopWord[1000];
    int numberOfStopWord = 0;
    char tempStopWord[50];
    memset(tempStopWord, 0, sizeof tempStopWord);
    while(fgets(tempStopWord, sizeof tempStopWord + 1, file1) != NULL){
        tempStopWord[strlen(tempStopWord) - 2] = '\0';
        memset(stopWord[numberOfStopWord].characters, 0, sizeof stopWord[numberOfStopWord].characters);
        strcpy(stopWord[numberOfStopWord++].characters, tempStopWord);
        // printf("%s Start: ", tempStopWord);
        // printf("%ld\n", strlen(tempStopWord));
        memset(tempStopWord, 0, sizeof tempStopWord);
    }
    // for(int i = 0; i < numberOfStopWord; i++){
    //     // stopWord[i].characters[strlen(stopWord[i].characters) - 2] = '\0';
    //     printf("%lu%s\n", strlen(stopWord[i].characters), stopWord[i].characters);
    // }
    FILE* file2; 
    file2 = fopen("vanban.txt","r");
    if(file2 == NULL) {
        perror("Error! ");
        exit(0);
    }
    Word words[2000];
    char allText[100000];
    memset(allText, 0, sizeof allText);
    int numberOfWord = 0;
    int start = 1;
    int currentPos = 0;
    int col = 1;
    char currentWord[50];
    char currentWordNormcase[50];
    memset(currentWord, 0, sizeof currentWord);
    memset(currentWordNormcase, 0, sizeof currentWordNormcase);
    int currentIndex = 0;
    char pointer;
    char pointerNorm;
    int type = 0;

    while((pointer = fgetc(file2)) != EOF){
        // printf("Check: %s - %ld\n", currentWord, strlen(currentWord));
        pointerNorm = pointer;
        allText[strlen(allText)] = pointerNorm;
        pointer = tolower(pointer);
        // printf("%c\n", pointer);
        // printf("Check: %s - %ld\n", currentWord, strlen(currentWord));
        currentPos++;
        if(pointer == ' ' || pointer == '\n' || pointer == '(' || pointer == ')' || pointer == ',' || pointer == '.' || (int)(pointer) == 13){
            // printf("x: %s - %ld\n", currentWord, strlen(currentWord));
            // printf("%d\n", pointer == '.');
            if(pointer == '.'){
                // printf("%c\n", allText[strlen(allText) - 2]);
                if(isdigit(allText[strlen(allText) - 2])){
                    // printf("Run here\n");
                    type = 3;
                    col = currentPos + 1;
                    currentWordNormcase[currentIndex] = pointerNorm;
                    currentWord[currentIndex++] = pointer;
                    continue;
                }
                if(allText[strlen(allText) - 2] == 'U'){
                    // printf("Run here2\n");
                    type = 1;
                    col = currentPos + 1;
                    currentWordNormcase[currentIndex] = pointerNorm;
                    // printf("%s", currentWordNormcase);
                    currentWord[currentIndex++] = pointer;
                    continue;
                }
            }
            if(strlen(currentWord) > 0){
                int stop = 0;
                // printf("1: %s - %ld\n", currentWord, strlen(currentWord));
                // printf("%c\n", pointer);
                // for(int x = 0; x < strlen(currentWord); x++){
                //     printf("%c\n", currentWord[x]);
                // }
                for(int i = 0; i < numberOfStopWord; i++){
                    // printf("2: %s\n", stopWord[i].characters);
                    // printf("3: %d\n", strcmp(currentWord, stopWord[i].characters));
                    // for(int x = 0; x < strlen(stopWord[i].characters); x++){
                    //     printf("%c\n", stopWord[i].characters[x]);
                    // }
                    if(strcmp(currentWord, stopWord[i].characters) == 0){
                        // printf("Check\n");
                        stop = 1;
                        break;
                    }
                }
                if(stop == 1){
                    memset(currentWord, 0, sizeof currentWord);
                    memset(currentWordNormcase, 0, sizeof currentWordNormcase);
                    currentIndex = 0;
                    col = currentPos  + 1;
                    if(pointer == '\n'){
                        start += 1;
                        currentPos = 0;
                        col = 1;
                    }
                    continue;
                }
                for(int i = 0; i < numberOfWord; i++){
                    if(strcmp(words[i].character, currentWord) == 0){
                        words[i].apperance += 1;
                        words[i].start[words[i].apperance] = start;
                        words[i].end[words[i].apperance] = col;
                        stop = 1;
                        break;
                    }
                }
                if(stop == 1){
                    memset(currentWord, 0, sizeof currentWord);
                    memset(currentWordNormcase, 0, sizeof currentWordNormcase);
                    currentIndex = 0;
                    col = currentPos  + 1;
                    if(pointer == '\n'){
                        start += 1;
                        currentPos = 0;
                        col = 1;
                    }
                    continue;
                } else {
                    for(int i = 0; i < numberOfWord; i++){
                        if(strcmp(words[i].character, currentWordNormcase) == 0){
                            words[i].apperance += 1;
                            words[i].start[words[i].apperance] = start;
                            words[i].end[words[i].apperance] = col;
                            stop = 1;
                            break;
                        }
                    }
                    if(stop == 1){
                        memset(currentWord, 0, sizeof currentWord);
                        memset(currentWordNormcase, 0, sizeof currentWordNormcase);
                        currentIndex = 0;
                        col = currentPos  + 1;
                        if(pointer == '\n'){
                            start += 1;
                            currentPos = 0;
                            col = 1;
                        }
                        continue;
                    }
                }
                
                if(isupper(currentWordNormcase[0])){
                    // printf("OK%sOK", currentWordNormcase);
                    int temp = strlen(allText) - 1;
                    for(int i = temp; i > 0; i--){
                        if(allText[i] == ' ' || allText[i] == '\n' || allText[i] == '(' || allText[i] == ')' || allText[i] == ',' || allText[i] == '.' || (int)(allText[i]) == 13){
                            continue;
                        } else {
                            // printf("%c", allText[i]);
                            temp = i;
                            break;
                        }
                    }
                    // printf("Temp: %d \n", temp);
                    temp -= strlen(currentWordNormcase);
                    // printf("%c", allText[temp]);
                    for(int i = temp; i > 0; i--){
                        // printf("%c", allText[i]);
                        // printf("-%d-", (int)(allText[i]));
                        if(allText[i] == ' ' || allText[i] == '\n' || allText[i] == '(' || allText[i] == ')' || (int)(allText[i]) == 13){
                            // printf("OK1");
                            continue;
                        } else if(allText[i] != '.'){
                            type = 1;
                            // printf("OK2");
                            // printf("%c", allText[i]);
                            // printf("-%d-", (int)(allText[i]));
                            break;
                        } else {
                            // printf("OK3");
                            break;
                        }
                    }
                }
                Word w;
                if(type == 1){
                    strcpy(w.character, currentWordNormcase);
                } else {
                    strcpy(w.character, currentWord);
                }
                w.apperance = 1;
                w.start[1] = start;
                w.end[1] = col;
                if(isdigit(w.character[0]) && type == 0){
                    type = 2;
                }
                w.type = type;
                words[numberOfWord++] = w;
                type = 0;
            }
            col = currentPos + 1;
            if(pointer == '\n'){
                start += 1;
                currentPos = 0;
                col = 1;
            }
            memset(currentWord, 0, sizeof currentWord);
            memset(currentWordNormcase, 0, sizeof currentWordNormcase);
            currentIndex = 0;
            // printf("This is currentWOrld:%s\n", currentWord);
            continue;
        }
        // printf("Comehere%c\nOK", pointer);
        // printf("%c\n", pointer);
        // printf("%d\n", pointer == '\n');
        // printf("XXX%d\n", (int)(pointer));
        // printf("%d\n", pointer == '\0');
        currentWordNormcase[currentIndex] = pointerNorm;
        currentWord[currentIndex++] = pointer;
    }

    for(int i = 0; i < numberOfWord - 1; i++){
        int temp = i;
        for(int j = i + 1; j < numberOfWord; j++){
            if(strcmp(words[temp].character, words[j].character) > 0){
                temp = j;
            }
        }
        Word temp2 = words[i];
        words[i] = words[temp];
        words[temp] = temp2;
    }

    for(int i = 0; i < numberOfWord; i++){
        printf("%s:%d  %d ", words[i].character, words[i].type, words[i].apperance);
        for(int j = 1; j <= words[i].apperance; j++){
            printf("(%d, %d) ", words[i].start[j], words[i].end[j]);
        }
        printf("\n");
    }

    fclose(file1);
    fclose(file2);

    return 0;
}
