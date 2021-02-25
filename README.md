# **EnigmaBot**

EnigmaBot brings the functionality of a Wehrmacht ENIGMA I cipher machine to your Discord server. Acting as a wrapper, EnigmaBot pipes all private messages it receives or public channel messages begining with a command prefix into the included Enigma executable.

## **Installation:**

---
### Requirements

* A Unix based operating system

### Procedure

1. Clone this repository to your machine

        $ git clone https://github.com/Dys13xic/EnigmaBot

2. Install GCC compiler

        $ sudo apt install gcc

3. Open a terminal within the repository folder, building using the make file

        $ make

2. [Install Python 3](https://www.python.org/downloads/)

        $ sudo apt install python3

3. [Install the discord.py library using pip](https://pypi.org/project/discord.py/)
4. [Create a Discord bot](https://discordpy.readthedocs.io/en/latest/discord.html)
5. Copy the token for your Discord bot into token.txt
6. Open a terminal within the repository folder, run the bot
            
        $ python3 bot.py
---

## **Usage Information:**

    ```
    Usage: !enigma [OPTION]... MESSAGE
    Convert MESSAGE by simulating Enigma I cipher machine.

    Required:
    MESSAGE: The input to be converted, must be enclosed in quotes if it contains spaces.
                (Example: "this is a message to convert")
    Options:
    -h, --help              Outputs usage and options information.

    -o, --ring              Ring settings for each rotor, range from 1-26 (inclusive).
                                    (Example: 13,1,26 - Default: 1,1,1)

    -p, --plugboard         Plugboard connects letters in pairs, swapping them (10 max), no duplicates.
                                    (Example: az,gh,lk - Default: empty)

    -r, --rotor             Rotor choices (I,II,III,IV,V) no duplicates.
                                    (Example: V,I,IV - Default: I,II,III)

    -s --start              Start position for each rotor, range from 1-26 (inclusive).
                                    (Example: 23,26,1 - Default: 1,1,1)
    ```