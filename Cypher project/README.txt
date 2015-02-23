Brett Carter
CS-260
Cypher program

Email: brett.carter@email.wsu.edu
--------------------------------------------------------------------------------
DESCRIPTION:

This program takes in two arguments from a user through stdin. the first being
either an "e" or a "d". The second argument need to be a string, some sort of
phrase to use and the encryption pad. It then encrypts a file using this pad,
and prints it out to stdout.

BUILD/EXECUTE:

(from command-line)
gcc -std=c99 cypher.c -o cypher              This will compile to code.

./cypher e 'encryption pad' < filename.txt   This will encrypt the file
./cypher d 'encryption pad' < filename.txt   This will decrypt the file

You can encrypt a file using a encryption phrase, and then decrypt the output
of that file with the same ecryption key to get the original back.

FILES IN ARCHIVE:

Cypher.c
README.txt
