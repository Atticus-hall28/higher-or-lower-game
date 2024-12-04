#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
//seed;
int past_card[100];
int rounds = 0 ;

void getcard(int *suit, int *rank ) {
    int rand_suit;
    int rand_rank;
     int card_num;
    cardstart:
    rand_suit = random() % 4;
    rand_rank = random() % 13;
    *suit = rand_suit + 1;
    *rank = rand_rank + 2;
    card_num = *suit * *rank;



    for(int i = 0; i < rounds; i++) {
        if (past_card[i] == card_num) {
            goto cardstart;
        }

    }



     past_card[rounds] = card_num;
     rounds++;


}


void stringifycard(int suit, int rank, char output[] ) {
    char suit_string[10];
    char rank_string[10];
  

    switch (suit) {
        case 1:
            strcpy(suit_string, "clubs");
            break;
        case 2:
            strcpy(suit_string, "diamonds");
            break;
        case 3:
            strcpy(suit_string, "hearts");
            break;
        case 4:
            strcpy(suit_string, "spades");
            break;
    }

    switch (rank) {
        case 11:
            strcpy(rank_string, "jack");
            break;
        case 12:
            strcpy(rank_string, "queen");
            break;
        case 13:
            strcpy(rank_string, "king");
            break;
        case 14:
            strcpy(rank_string, "ace");
            break;
        default:
             sprintf(rank_string, "%d",rank);
             break;

    
    }

    strcpy(output, rank_string);
    strcat(output, " of ");
    strcat(output, suit_string);

}


int main() {
    int suit,rank,next_suit,next_rank;
    char output[100];
    bool running = true;
    bool is_next_higher;
    char guess[100];
    size_t length; 
    unsigned int seed = time(0);
    srand(seed);
    char play_again;
    start:
    getcard(&suit, &rank);
    stringifycard(suit, rank, output);
            

        while(running) {
            getcard(&next_suit, &next_rank);
            printf("your card is the %s, is the next card higher or lower?\n",output);
            output[0] = '\0'; 
            fgets(guess, sizeof(guess), stdin);
            
             length = strlen(guess); 
             if (length > 0 && guess[length - 1] == '\n') {
                 guess[length - 1] = '\0'; }


            while (strcmp(guess,"higher")!=0 && strcmp(guess,"lower")!=0 ) {
                printf("invalid option, make sure you say either 'higher' or 'lower' \n");
                fgets(guess, sizeof(guess), stdin);
                length = strlen(guess); 
                if (length > 0 && guess[length - 1] == '\n') {
                     guess[length - 1] = '\0'; }
            
            }  

            if(next_rank < rank) {
                is_next_higher = false;
            } else if(next_rank > rank) {
                is_next_higher = true;
            } else { 
                    if(next_suit < suit) {
                        is_next_higher = false;
                     } else if(next_suit > suit) {
                        is_next_higher = true;
                     }
             }



                suit = next_suit;
                rank = next_rank;
                stringifycard(suit, rank, output);

            if(strcmp(guess,"higher")==0 && is_next_higher) {
                printf("you guessed correctly, ");

            } else if(strcmp(guess,"lower")==0 && !is_next_higher) {
                printf("you guessed correctly, ");
               
            } else {
                 stringifycard(suit, rank, output);
                printf("you guessed incorectly, the next card was the %s \nwould you like to play again [Y/n]? \n",output);
                running = false;
                play_again = getchar();
                getchar();

                if(play_again == 'y' || play_again == 'Y' ) {
                     memset(past_card, 0, sizeof(past_card));
                     rounds=0;
                     running = true; 
                     goto start;

                }
            }
           


            




        

        }
    /*
        getcard(&suit, &rank);
        stringifycard(suit, rank, output);
        printf("%s\n",output);

*/
}