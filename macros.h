// Copyright 2022 Dumitru Bianca Stefania 312CA
#ifndef MACROS_H_
#define MACROS_H_

// macros for string sizes
#define MAX_STRING_SIZE 64
#define SYMB_MAX 8
#define COMMAND_MAX 20
#define TOKENS_MAX 10

// macros for error outputs
#define DECK_INDEX_OUT_OF_BOUNDS \
printf("The provided index is out of bounds for the deck list.\n")

#define CARD_INDEX_OUT_OF_BOUNDS(x) \
printf("The provided index is out of bounds for deck %d.\n", x)

#define INVALID_CARD \
printf("The provided card is not a valid one.\n")

#define INVALID_COMMAND \
{printf("Invalid command. Please try again.\n"); continue;}
#endif  // MACROS_H_
