#include "enigma.h"
#include "configure.h"
#include "error.h"

#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>


int main(int argc, char *argv[]) {

    // For discord bot
    char programName[] = "!enigma";

    char input[CHAR_LIMIT];

    ROTOR rotorSet[ROTOR_AMOUNT];
    int flag, size, status, i;

    // default settings  
    int rotorSettings[ROTOR_AMOUNT] = {0,1,2};
    int positionSettings[ROTOR_AMOUNT] = {0,0,0};
    int ringSettings[ROTOR_AMOUNT] = {0,0,0};

    // copy alphabet string to plugcipher, null terminate
    char plugboardCipher[ALPHA_LENGTH + 1];
    strncpy(plugboardCipher, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", ALPHA_LENGTH);
    plugboardCipher[ALPHA_LENGTH] = '\0';

    // configure getopt_long options struct
    int long_index = 0;
    static struct option long_options[] = {
        {"help",        no_argument,        0,  'h' },
        {"ring",        required_argument,  0,  'o' },
        {"plugboard",   required_argument,  0,  'p' },
        {"rotor",       required_argument,  0,  'r' },
        {"start",       required_argument,  0,  's' },
        {0,             0,                  0,   0  }
    };

    // while there are arguments with options flags
    while ((flag = getopt_long(argc, argv, "ho:p:r:s:", long_options, &long_index)) != -1) {

        switch(flag) {

            case 'h': {
                printUsage(programName, false);
                exit(EXIT_SUCCESS);
                break;
            }

            case 'o': {
                char **splitRingArgument = splitArg(optarg, &size);
                status = validateNumericSettings(splitRingArgument, ringSettings, size);

                if (status != S_SUCCESS)
                    errorExit(status, "validateNumericSettings()", programName, true);
                break;
            }

            case 'p': {
                char **splitPlugboardArgument = splitArg(optarg, &size);
                status = validatePlugboard(splitPlugboardArgument, plugboardCipher, size);

                if (status != S_SUCCESS)
                    errorExit(status, "validatePlugboard()", programName, true);
                break;
            }

            case 'r': {
                char **splitRotorArgument = splitArg(optarg, &size);
                status = validateRotors(splitRotorArgument, rotorSettings, size);

                if (status != S_SUCCESS)
                    errorExit(status, "validateRotors()", programName, true);
                break;
            }

            case 's': {
                char **splitPositionArgument = splitArg(optarg, &size);
                status = validateNumericSettings(splitPositionArgument, positionSettings, size);

                if (status != S_SUCCESS);
                    errorExit(status, "validateRotors()", programName, true);
                break;
            }

            default:
                errorExit(S_INVALID_FLAG, "main()", programName, true);
        }
    }

    if (optind < argc) {                                  // if there is a non-flag argument
        strncpy(input, argv[optind], CHAR_LIMIT);      // copy argument to message buffer and null terminate
        input[CHAR_LIMIT - 1] = '\n';
    }

    else {
        printf("ERROR: missing message to convert. \n");
        printUsage(programName, true);
        exit(EXIT_FAILURE);
    }

    // return array of ROTOR object pointers
    configureRotors(rotorSettings, rotorSet);

    // set each ROTOR object's position to corresponding value in positionSettings array
    for (i = 0; i < ROTOR_AMOUNT; i++)
        rotorSet[i].position = positionSettings[i];                          

    // update ROTOR turnover and position according to corresponding ring setting;
    for (i = 0; i < ROTOR_AMOUNT; i++) {                                                                 
        rotorSet[i].turnover = moduloSubtract(rotorSet[i].turnover, ringSettings[i], ALPHA_LENGTH);
        rotorSet[i].position = moduloSubtract(rotorSet[i].position, ringSettings[i], ALPHA_LENGTH);
    }

    // convert input and print output
    char *output = convertMessage(rotorSet, plugboardCipher, input);

    if (output) {
        printf("%s\n", output);
        free(output);
        output = NULL;
    }

    return EXIT_SUCCESS;
}