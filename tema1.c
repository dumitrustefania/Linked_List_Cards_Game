// Copyright 2022 Dumitru Bianca Stefania 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "macros.h"
#include "linked_list.h"
#include "auxiliary.h"
#include "functions.h"

int main()
{
	t_ll *deckList = create_list();

	while (1)
	{
		char command[COMMAND_MAX], tokens[TOKENS_MAX][COMMAND_MAX];
		int nr, deck_idx, card_idx, idx1, idx2, tokens_no;
		scanf("%s", command);
		tokens_no = read_tokens(tokens);

		if (strcmp(command, "ADD_DECK") == 0 && tokens_no == 1) {
			nr = atoi(tokens[0]);
			add_deck(deckList, nr);
			printf("The deck was successfully created with %d cards.\n", nr);
		} else if (strcmp(command, "DEL_DECK") == 0 && tokens_no == 1) {
			deck_idx = atoi(tokens[0]);
			if (deck_idx >= deckList->size || deck_idx < 0) {
				DECK_INDEX_OUT_OF_BOUNDS;
			} else {
				delete_deck(deckList, deck_idx);
				printf("The deck %d was successfully deleted.\n", deck_idx);
			}
		} else if (strcmp(command, "DEL_CARD") == 0 && tokens_no == 2) {
			deck_idx = atoi(tokens[0]);
			card_idx = atoi(tokens[1]);
			if (deck_idx >= deckList->size || deck_idx < 0)
				DECK_INDEX_OUT_OF_BOUNDS;
			else
				delete_card(deckList, deck_idx, card_idx);
		} else if (strcmp(command, "ADD_CARDS") == 0 && tokens_no == 2) {
			deck_idx = atoi(tokens[0]);
			nr = atoi(tokens[1]);
			if (deck_idx >= deckList->size || deck_idx < 0) {
				DECK_INDEX_OUT_OF_BOUNDS;
			} else {
				add_cards_to_deck(deckList, go_to_node(deckList, deck_idx), nr);
				printf("The cards were successfully added to deck %d.\n", deck_idx);
			}
		} else if (strcmp(command, "DECK_NUMBER") == 0 && tokens_no == 0) {
			printf("The number of decks is %d.\n", deckList->size);
		} else if (strcmp(command, "DECK_LEN") == 0 && tokens_no == 1) {
			deck_idx = atoi(tokens[0]);
			if (deck_idx >= deckList->size || deck_idx < 0)
				DECK_INDEX_OUT_OF_BOUNDS;
			else
				printf("The length of deck %d is %d.\n",
					   deck_idx, go_to_node(deckList, deck_idx)->size);
		} else if (strcmp(command, "SHUFFLE_DECK") == 0 && tokens_no == 1) {
			deck_idx = atoi(tokens[0]);
			if (deck_idx >= deckList->size || deck_idx < 0) {
				DECK_INDEX_OUT_OF_BOUNDS;
			} else {
				shuffle_deck(go_to_node(deckList, deck_idx));
				printf("The deck %d was successfully shuffled.\n", deck_idx);
			}
		} else if (strcmp(command, "MERGE_DECKS") == 0 && tokens_no == 2) {
			idx1 = atoi(tokens[0]);
			idx2 = atoi(tokens[1]);
			if (idx1 >= deckList->size || idx2 >= deckList->size ||
				idx1 < 0 || idx2 < 0) {
				DECK_INDEX_OUT_OF_BOUNDS;
			} else {
				merge_decks(deckList, idx1, idx2);
				printf("The deck %d and the deck %d were successfully merged.\n",
                idx1, idx2);
			}
		} else if (strcmp(command, "SPLIT_DECK") == 0 && tokens_no == 2) {
			deck_idx = atoi(tokens[0]);
			idx1 = atoi(tokens[1]);
			if (deck_idx >= deckList->size || deck_idx < 0) {
				DECK_INDEX_OUT_OF_BOUNDS;
			} else {
				split_deck(deckList, deck_idx, idx1);
			}
		} else if (strcmp(command, "REVERSE_DECK") == 0 && tokens_no == 1) {
			deck_idx = atoi(tokens[0]);
			if (deck_idx >= deckList->size || deck_idx < 0) {
				DECK_INDEX_OUT_OF_BOUNDS;
			} else {
				reverse_deck(deckList, deck_idx);
				printf("The deck %d was successfully reversed.\n", deck_idx);
			}
		} else if (strcmp(command, "SHOW_DECK") == 0 && tokens_no == 1) {
			deck_idx = atoi(tokens[0]);
			if (deck_idx >= deckList->size || deck_idx < 0)
				DECK_INDEX_OUT_OF_BOUNDS;
			else
				show_deck(deckList, deck_idx);
		} else if (strcmp(command, "SHOW_ALL") == 0 && tokens_no == 0) {
			show_all(deckList);
		} else if (strcmp(command, "SORT_DECK") == 0 && tokens_no == 1) {
			deck_idx = atoi(tokens[0]);
			if (deck_idx >= deckList->size || deck_idx < 0) {
				DECK_INDEX_OUT_OF_BOUNDS;
			} else {
				sort_deck(deckList, deck_idx);
				printf("The deck %d was successfully sorted.\n", deck_idx);
			}
		} else if (strcmp(command, "EXIT") == 0 && tokens_no == 0) {
			free_all(deckList);
			break;
		} else {
			INVALID_COMMAND
		}
	}
	return 0;
}
