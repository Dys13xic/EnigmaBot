#ifndef CONFIGURE_H
#define CONFIGURE_H

#define CHAR_LIMIT 301
#define ALPHA_LENGTH 26
#define ROTOR_AMOUNT 3
#define NUM_ROTOR_OPTIONS 5
#define PLUG_LIMIT 10
#define MAX_ARG_SEGMENTS 10
#define ARG_SEGMENT_LENGTH 3


int configureRotors(int rotors[], ROTOR rotorSet[]);

int validateRotors(char **args, int rotorSettings[], int size);

void swapChars(char *string, char x, char y);

int validatePlugboard(char **arg, char plugboardCipher[], int size);

char **splitArg(char *str, int *size);

int validateNumericSettings(char **arg, int numericSettings[], int size);

#endif