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
#include <windows.h>
#include <winbase.h>





//char *section[10] = {"Who", "What", "When", "Where", "Why", "How"};

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
int knowledge_get(const char* intent, const char* entity, char* response, int n) {

	
	///*intent not found*/
	//for (int i = 0; i < 6; i++)
	//{
	//	
	//}

	if (compare_token(intent, "who") == 0)
	{
		for (int i = 0; i < 255; i++) 
		{
			if (compare_token(who_knowledge_arr[i].entity, entity) == 0)
			{
				snprintf(response, n, who_knowledge_arr[i].response);
				return KB_OK;
			}
		}
	}
	else if (compare_token(intent, "what") == 0)
	{
		for (int i = 0; i < 255; i++)
		{
			if (compare_token(what_knowledge_arr[i].entity, entity) == 0)
			{
				snprintf(response, n, what_knowledge_arr[i].response);
				return KB_OK;
			}
		}
	}
	else if (compare_token(intent, "when") == 0)
	{
		for (int i = 0; i < 255; i++)
		{
			if (compare_token(when_knowledge_arr[i].entity, entity) == 0)
			{
				snprintf(response, n, when_knowledge_arr[i].response);
				return KB_OK;
			}
		}
	}
	else if (compare_token(intent, "where") == 0)
	{
		for (int i = 0; i < 255; i++)
		{
			if (compare_token(where_knowledge_arr[i].entity, entity) == 0)
			{
				snprintf(response, n, where_knowledge_arr[i].response);
				return KB_OK;
			}
		}
	}
	else if (compare_token(intent, "why") == 0)
	{
		for (int i = 0; i < 255; i++)
		{
			if (compare_token(why_knowledge_arr[i].entity, entity) == 0)
			{
				snprintf(response, n, why_knowledge_arr[i].response);
				return KB_OK;
			}
		}
	}
	else if (compare_token(intent, "how") == 0)
	{
		for (int i = 0; i < 255; i++)
		{
			if (compare_token(how_knowledge_arr[i].entity, entity) == 0)
			{
				snprintf(response, n, how_knowledge_arr[i].response);
				return KB_OK;
			}
		}
	}
	/* Based on this return input call KNOWLEDGE_PUT HERE */
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
int knowledge_put(const char* intent, const char* entity, const char* response) {

	/* to be implemented */
	int searchCount = 0;
	bool exist = false;
	response = strtok(response, "\n");

	if (compare_token(intent, "who") == 0)
	{
		for (searchCount = 0; who_knowledge_arr[searchCount].entity != NULL; searchCount++)
		{
			if (strcmp(who_knowledge_arr[searchCount].entity, entity) == 0)
			{
				exist = true;
				break;
			}

			if (strcmp(who_knowledge_arr[searchCount].entity, "") == 0)
			{
				strcpy(who_knowledge_arr[searchCount].entity, entity);
				strcpy(who_knowledge_arr[searchCount].response, response);
				
				return KB_OK;
			}
		}

		if (exist == true)
		{
			strcpy(who_knowledge_arr[searchCount].entity, entity);
			strcpy(who_knowledge_arr[searchCount].response, response);
			
			return KB_OK;
		}
	}
	else if (compare_token(intent, "what") == 0)
	{
		for (searchCount = 0; what_knowledge_arr[searchCount].entity != NULL; searchCount++)
		{
			if (strcmp(what_knowledge_arr[searchCount].entity, entity) == 0)
			{
				exist = true;
				break;
			}

			if (strcmp(what_knowledge_arr[searchCount].entity, "") == 0)
			{
				strcpy(what_knowledge_arr[searchCount].entity, entity);
				strcpy(what_knowledge_arr[searchCount].response, response);
				
				return KB_OK;
			}
		}

		if (exist == true)
		{
			strcpy(what_knowledge_arr[searchCount].entity, entity);
			strcpy(what_knowledge_arr[searchCount].response, response);
			
			return KB_OK;
		}
	}
	else if (compare_token(intent, "where") == 0)
	{
		for (searchCount = 0; where_knowledge_arr[searchCount].entity != NULL; searchCount++)
		{
			if (strcmp(where_knowledge_arr[searchCount].entity, entity) == 0)
			{
				exist = true;
				break;
			}

			if (strcmp(where_knowledge_arr[searchCount].entity, "") == 0)
			{
				strcpy(where_knowledge_arr[searchCount].entity, entity);
				strcpy(where_knowledge_arr[searchCount].response, response);
				
				return KB_OK;
			}
		}

		if (exist == true)
		{
			strcpy(where_knowledge_arr[searchCount].entity, entity);
			strcpy(where_knowledge_arr[searchCount].response, response);
			
			return KB_OK;
		}
	}
	else if (compare_token(intent, "when") == 0)
	{
		for (searchCount = 0; when_knowledge_arr[searchCount].entity != NULL; searchCount++)
		{
			if (strcmp(when_knowledge_arr[searchCount].entity, entity) == 0)
			{
				exist = true;
				break;
			}

			if (strcmp(when_knowledge_arr[searchCount].entity, "") == 0)
			{
				strcpy(when_knowledge_arr[searchCount].entity, entity);
				strcpy(when_knowledge_arr[searchCount].response, response);
				
				return KB_OK;
			}
		}

		if (exist == true)
		{
			strcpy(when_knowledge_arr[searchCount].entity, entity);
			strcpy(when_knowledge_arr[searchCount].response, response);
			
			return KB_OK;
		}
	}
	else if (compare_token(intent, "why") == 0)
	{
		for (searchCount = 0; why_knowledge_arr[searchCount].entity != NULL; searchCount++)
		{
			if (strcmp(why_knowledge_arr[searchCount].entity, entity) == 0)
			{
				exist = true;
				break;
			}

			if (strcmp(why_knowledge_arr[searchCount].entity, "") == 0)
			{
				strcpy(why_knowledge_arr[searchCount].entity, entity);
				strcpy(why_knowledge_arr[searchCount].response, response);
				
				return KB_OK;
			}
		}

		if (exist == true)
		{
			strcpy(why_knowledge_arr[searchCount].entity, entity);
			strcpy(why_knowledge_arr[searchCount].response, response);
			
			return KB_OK;
		}
	}
	else if (compare_token(intent, "how") == 0)
	{
		for (searchCount = 0; how_knowledge_arr[searchCount].entity != NULL; searchCount++)
		{
			if (strcmp(how_knowledge_arr[searchCount].entity, entity) == 0)
			{
				exist = true;
				break;
			}

			if (strcmp(how_knowledge_arr[searchCount].entity, "") == 0)
			{
				strcpy(how_knowledge_arr[searchCount].entity, entity);
				strcpy(how_knowledge_arr[searchCount].response, response);
				
				return KB_OK;
			}
		}

		if (exist == true)
		{
			strcpy(how_knowledge_arr[searchCount].entity, entity);
			strcpy(how_knowledge_arr[searchCount].response, response);
			
			return KB_OK;
		}
	}
	else
	{
		return KB_INVALID;
	}

	

}


/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE* f) {

	/* to be implemented */
	char buff[255];
	int intelligence = 0;
	char current_intent[MAX_INTENT];
	char current_entity[MAX_ENTITY];
	char current_response[MAX_RESPONSE];

	int cnt = 0;
	char* token;

	while (fgets(buff, 255, (FILE*)f) != NULL) {
		/* get true length of string */
		int len = strlen(buff) - 1;
		buff[len] = '\0';

		/* check for intent brackets -> [ ] */
		if (buff[0] == '[' && buff[len - 1] == ']')
		{
			//printf("%d ", strlen(buff));

			if (strcmp(buff, "[where]") == 0) {
				strcpy(current_intent, "where\0");
				printf("%s ", current_intent); // test print
				cnt = 0;
			}
			else if (strcmp(buff, "[what]") == 0) {
				strcpy(current_intent, "what\0");
				printf("%s ", current_intent); // test print
				cnt = 0;
			}
			else if (strcmp(buff, "[when]") == 0) {
				strcpy(current_intent, "when\0");
				printf("%s ", current_intent); // test print
				cnt = 0;
			}
			else if (strcmp(buff, "[who]") == 0) {
				strcpy(current_intent, "who\0");
				printf("%s ", current_intent); // test print
				cnt = 0;
			}
			else if (strcmp(buff, "[why]") == 0) {
				strcpy(current_intent, "why\0");
				printf("%s ", current_intent); // test print
				cnt = 0;
			}
			else if (strcmp(buff, "[how]") == 0) {
				strcpy(current_intent, "how\0");
				printf("%s ", current_intent); // test print
				cnt = 0;
			}

			printf("%s\n", buff);

		}
		//else if (isalpha(buff[0]))
		else if (strchr(buff, '=') != NULL)
		{
			//printf("%s\n%s\n", current_intent, buff);
			token = strtok(buff, "=");
			strcpy(current_entity, token);

			token = strtok(NULL, "=");
			strcpy(current_response, token);

			if (compare_token(current_intent, "who") == 0) {
				printf("I put in who");

				//who_knowledge_arr[cnt].entity = current_entity;
				//who_knowledge_arr[cnt].response = current_response;
				strcpy(who_knowledge_arr[cnt].entity, current_entity);
				strcpy(who_knowledge_arr[cnt].response, current_response);

			}
			else if (compare_token(current_intent, "what") == 0) {
				printf("I put in what");

				//what_knowledge_arr[cnt].entity = current_entity;
				//what_knowledge_arr[cnt].response = current_response;
				strcpy(what_knowledge_arr[cnt].entity, current_entity);
				strcpy(what_knowledge_arr[cnt].response, current_response);

			}
			else if (compare_token(current_intent, "when") == 0) {
				printf("I put in when");

				//when_knowledge_arr[cnt].entity = current_entity;
				//when_knowledge_arr[cnt].response = current_response;
				strcpy(when_knowledge_arr[cnt].entity, current_entity);
				strcpy(when_knowledge_arr[cnt].response, current_response);

			}
			else if (compare_token(current_intent, "where") == 0) {
				printf("I put in where");

				//where_knowledge_arr[cnt].entity = current_entity;
				//where_knowledge_arr[cnt].response = current_response;
				strcpy(where_knowledge_arr[cnt].entity, current_entity);
				strcpy(where_knowledge_arr[cnt].response, current_response);

			}
			else if (compare_token(current_intent, "why") == 0) {
				printf("I put in why");

				//why_knowledge_arr[cnt].entity = current_entity;
				//why_knowledge_arr[cnt].response = current_response;
				strcpy(why_knowledge_arr[cnt].entity, current_entity);
				strcpy(why_knowledge_arr[cnt].response, current_response);

			}
			else if (compare_token(current_intent, "how") == 0) {
				printf("I put in how");

				//how_knowledge_arr[cnt].entity = current_entity;
				//how_knowledge_arr[cnt].response = current_response;
				strcpy(how_knowledge_arr[cnt].entity, current_entity);
				strcpy(how_knowledge_arr[cnt].response, current_response);

			}

			printf("%s\t%s\n", who_knowledge_arr[intelligence].entity, who_knowledge_arr[intelligence].response);
			//printf("%s\n", current_intent);
			cnt++; // for file cnt
			intelligence++;
		}

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
void knowledge_write(FILE* f) {
	int i;
	
	if (what_knowledge_arr != NULL)
	{
		i = 0;
		fprintf(f, "[what]\n");	// print the header of what
		
		while (compare_token(what_knowledge_arr[i].entity, "") != 0)
		{
			fprintf(f, "%s=%s\n", what_knowledge_arr[i].entity, what_knowledge_arr[i].response);
			i++;
		}
		fprintf(f, "\n");
	}

	if (when_knowledge_arr != NULL)
	{
		i = 0;
		fprintf(f, "[where]\n");	// print the header of what
		while (compare_token(where_knowledge_arr[i].entity, "") != 0)
		{
			fprintf(f, "%s=%s\n", where_knowledge_arr[i].entity, where_knowledge_arr[i].response);
			i++;
		}

		fprintf(f, "\n");
	}

	if (who_knowledge_arr != NULL)
	{
		int i = 0;
		fprintf(f, "[who]\n");	// print the header of what
		while (compare_token(who_knowledge_arr[i].entity, "") != 0)
		{
			fprintf(f, "%s=%s\n", who_knowledge_arr[i].entity, who_knowledge_arr[i].response);
			i++;
		}

	}

	/* to be implemented */

}