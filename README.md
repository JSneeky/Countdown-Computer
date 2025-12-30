# Countdown Computer
A program that gives the best solutions to the UK Daytime TV show Countdown.

# C Implementation
par_countdown.c is a parallelised version of countdown.c and will reliably find up to 7 letter words within the 30 second time frame.
8 and 9 letter words will only be found in some circumstances in time. 

countdown.c will output the longest word found.
par_countdown.c will output a word for each length if possible.

Each file has two different modes:
- If called with the -l flag, e.g. ./countdown -l ..., the program will try to complete the letters game with the given letters.
- If called with the -n flag, e.g. ./countdown -n ..., the program will try to complete the numbers game with the given numbers.

# Currently In Devlopment
- A C program that computes the above for the letters and numbers game
- A Next.js based application that computes the above and provides solutions in a GUI.

## Dictionaries
The dictionaries were populated using the following grep command, replacing 'i' with the number of letters:
grep -E '^[a-z]{i}$' /usr/share/dict/words > i_words.txt
