#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXT_LIMIT 65536

int main(void) {
    int key = 0;
    int input_valid = 0;
    char input_buffer[64];

    do { /* Read the key */
        printf("Input Caesar (1 to 26) key: "); /* Prompts the user on what to do */

        if(fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) { /* Reads input as one line */
            printf("Error reading input\n");
            continue;
        }

        input_buffer[strcspn(input_buffer, "\n")] = '\0'; /* Removes new line character if present */

        if(strlen(input_buffer) == 0) { /* Checks if the input is blank */
            printf("Empty input. Please enter an integer in a range of 1 to 26\n");
            continue;
        }

        char *conv; /* Converts the string into an integer */
        key = strtol(input_buffer, &conv, 10);

        if(*conv != '\0') { /* Check if the conversion is successfull */
            printf("Input \"%s\" is invalid. Please enter an integer in a range of 1 to 26\n", input_buffer);
        } else if(key >= 1 && key <= 26) { /* Checks if the inputted key is in a valid range */
            input_valid = 1;
        } else {
            printf("Input \"%s\" is invalid. Please enter an integer in a range of 1 to 26\n", input_buffer);
        }
    } while(input_valid != 1);

	FILE *ReadCaesar = fopen("Caesar26_Encrypted.txt", "r"); /* Open the encryped file */

	char encrypted_text[TEXT_LIMIT]; /* Reads the encryped file */
	fgets(encrypted_text, sizeof(encrypted_text), ReadCaesar);
	fclose(ReadCaesar);

	FILE *WriteCaesar = fopen("Caesar26_Decrypted.txt", "w"); /* Open decrypted file */

	char ascii_c;
	for(int i = 0; encrypted_text[i] != '\0'; i++) {
		if(islower(encrypted_text[i])) { /* Decrypting lowercase text */
			ascii_c = ((encrypted_text[i] - 'a' - key) % 26) + 'a';
		} else if(isupper(encrypted_text[i])) { /* Decrypting uppercase text */
			ascii_c = ((encrypted_text[i] - 'A' - key) % 26) + 'A';
		} else if(isdigit(encrypted_text[i])) { /* Decrypting arabic numeral */
			ascii_c = ((encrypted_text[i] - '0' - key) % 10) + '0';
		} else {
			ascii_c = encrypted_text[i];
		}
		fprintf(WriteCaesar, "%c", ascii_c); /* Writes in the opened text file */
	}
	fclose(WriteCaesar);  /* Closes the text file */
	printf("\nCaesar decryption saved to Caesar26_Decrypted.txt\n");

	return 0;
}
