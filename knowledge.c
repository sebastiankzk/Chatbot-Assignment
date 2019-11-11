/*
 * ICT1002 (C Language) Group Project, AY19 Trimester 1.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * kowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"

/* knowledge base of 5W 1H */
char* knowledge[255][3];

/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND, if no response could be found
 *   KB_INVALID, if 'intent' is not a recognised question word
 */
int knowledge_get(const char *intent, const char *entity, char *response, int n) {
	
	/* to be implemented */
	
	return KB_NOTFOUND;
	
}


/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_FOUND, if successful
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char *intent, const char *entity, const char *response) {
	
	/* to be implemented */
	
	return KB_INVALID;
	
}


/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE *f) {
	
	/* to be implemented */
	char buff[255];
	int intelligence = 0;

	while (fgets(buff, 255, (FILE*)f) != NULL) {

		/* get true length of string */
		int len = strlen(buff) - 1;
		buff[len] = '\0';
		

		/* check for intent brackets -> [ ] */
		if (buff[0] == '[' && buff[len-1] == ']')
		{
			printf("%d ", strlen(buff));
			if (strcmp(buff, "[who]") == 0) {
				printf("who "); // test print
			}
			else if (strcmp(buff, "[what]") == 0) {
				printf("what "); // test print
			}
			else if (strcmp(buff, "[when]") == 0) {
				printf("when "); // test print
			}
			else if (strcmp(buff, "[where]") == 0) {
				printf("where "); // test print
			}
			else if (strcmp(buff, "[why]") == 0) {
				printf("why "); // test print
			}
			else if (strcmp(buff, "[how]") == 0) {
				printf("how "); // test print
			}

			printf("%s\n", buff);

		}
		else if (isalpha(buff[0]))
		{
			printf("%d ", strlen(buff));
			printf("%s\n", buff);
			intelligence += 1;
		}
		//printf("%d\n", strcmp(buff, "[who]"));
	}

	return intelligence;

}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {
	
	/* to be implemented */
	
}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f) {
	
	/* to be implemented */
	
}