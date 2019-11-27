/*
 * ICT1002 (C Language) Group Project, AY19 Trimester 1.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */

#include <stdio.h>
#include <string.h>
#include "chat1002.h"
#include <ctype.h>
#include <time.h>
#include <stdbool.h> 
#include <windows.h>
#include <winbase.h>

 /*
  * Get the name of the chatbot.
  *
  * Returns: the name of the chatbot as a null-terminated string
  */
const char* chatbot_botname() {

	/* edit to change bot name */
	return "Jamie";

}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char* chatbot_username() {

	/* edit to change user name */
	return "User";

}


/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char* inv[], char* response, int n) {

	/* check for empty input */
	if (inc < 1) {
		snprintf(response, n, "");
		return 0;
	}

	/* look for an intent and invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(inc, inv, response, n);
	else if (chatbot_is_smalltalk(inv[0]))
		return chatbot_do_smalltalk(inc, inv, response, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(inc, inv, response, n);
	else if (chatbot_is_question(inv[0]))
		return chatbot_do_question(inc, inv, response, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(inc, inv, response, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(inc, inv, response, n);
	else {
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 0;
	}

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char* intent) {

	/* chatbot_do_exit will invoke as long as one of the compare_token returns 0 */
	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0;

}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char* inv[], char* response, int n) {

	snprintf(response, n, "Goodbye!");

	return 1;

}


/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char* intent) {

	/* chatbot_do_load will invoke if compare_token returns 0 */
	return compare_token(intent, "load") == 0;

}


/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int inc, char* inv[], char* response, int n) {
	
	/* First check whether user has entered a filename */
	if (inv[1] == NULL) 
	{
		snprintf(response, n, "Please enter a filename.");

		return 0;
	}
	else 
	{
		/* Open file according to given file name, 2nd parameter of user input which is index 1 of inv */
		FILE* fp = fopen(inv[1], "r");

		if (fp != NULL)
		{
			/* variable to store number of lines read from file, knowledge_read returns it */
			int botintel = knowledge_read(fp);

			snprintf(response, n, "Read %d responses from %s.", botintel, inv[1]);

			fclose(fp);
		}
		else 
		{
			snprintf(response, n, "File not found, does your filename exist?");
		}

	}

	return 0;

}


/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char* intent) {

	/* check for who, what, when, where, why, how, do_question will invoke if any of the compare_token returns 0 */
	return 
		compare_token(intent, "what") == 0 ||
		compare_token(intent, "where") == 0 ||
		compare_token(intent, "who") == 0 ||
		compare_token(intent, "when") == 0 ||
		compare_token(intent, "why") == 0 ||
		compare_token(intent, "how") == 0;

}


/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int inc, char* inv[], char* response, int n) {

	/* first check if words in the question is bigger than 1, which is 2 onwards */
	if (inc > 1)
	{
		char input_buffer[MAX_INPUT];

		/* check first parameter for intent first */
		if (compare_token(inv[0], "what") == 0 || compare_token(inv[0], "where") == 0 || compare_token(inv[0], "who") == 0 || compare_token(inv[0], "when") == 0 || compare_token(inv[0], "why") == 0 || compare_token(inv[0], "how") == 0)
		{

			/* check second parameter for skipped words */
			if (compare_token(inv[1], "is") == 0 || compare_token(inv[1], "are") == 0 || compare_token(inv[1], "was") == 0 || compare_token(inv[1], "were") == 0)
			{
				/* third parameter onwards is considered entities */
				char join_buffer[MAX_ENTITY] = "";

				/* for loop to join multiple words entity */
				for (int i = 2; i < inc; i++)
				{
					if (strcmp(join_buffer, "") == 0)
					{
						strcpy(join_buffer, inv[i]);
					}
					else
					{
						strcat(join_buffer, " ");
						strcat(join_buffer, inv[i]);
					}
				}

				/*Search for entity in the relevant knowledge list and return the answer*/
				if (knowledge_get(inv[0], join_buffer, response, n) == KB_OK)
				{					
					return 0;
				}
				else if (knowledge_get(inv[0], join_buffer, response, n) == KB_NOTFOUND)
				{
					printf("%s: I dont know %s. %s is %s?\n", chatbot_botname(), join_buffer, inv[0], join_buffer);
					printf("%s:", chatbot_username());
					fgets(input_buffer, n, stdin);

					//check if the user pressed enter instead of replying a answer
					if (input_buffer[0] == '\n' || input_buffer[0] == ' ')
					{

						snprintf(response, n, "I do not understand your answer. Please try again!");
						return 0;
					}
					else
					{
						snprintf(response, n, "Thank you");
						return (knowledge_put(inv[0], join_buffer, input_buffer));
					}

				}
				else if (knowledge_get(inv[0], join_buffer, response, n) == KB_INVALID)
				{
					snprintf(response, n, "I dont see a question. Please ask again");

					return 0;
				}
			}

			else
			{
				snprintf(response, n, "Please ask a question in proper english.");
			}
			
		}
	}
	else
	{
		snprintf(response, n, "I do not understand your question");
	}


	return 0;
}


/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char* intent) {

	/* chatbot_do_reset will invoke if compare_token returns 0 */
	return compare_token(intent, "reset") == 0;

}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int inc, char* inv[], char* response, int n) {

	knowledge_reset();
	snprintf(response, n, "Chatbot reset.");

	return 0;

}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_save(const char* intent) {

	/* chatbot_do_save will invoke if compare_token returns 0 */
	return compare_token(intent, "save") == 0;

}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char* inv[], char* response, int n) {
	char filename[MAX_INPUT];
	FILE* fp;
	if (inc == 1)
	{
		snprintf(response, n, "Sorry. Please indicate a file name to save.");
		return 0;
	}

	if ((compare_token(inv[1], "as") == 0) || (compare_token(inv[1], "to") == 0))
	{
		strcpy(filename, inv[2]);
	}
	else
	{
		strcpy(filename, inv[1]);
	}
	fp = fopen(filename, "w");
	knowledge_write(fp);
	snprintf(response, n, "My knowledge has been saved to %s.", filename);
	fclose(fp);

	return 0;
}


/*
 * Determine which an intent is smalltalk.
 *
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is the first word of one of the smalltalk phrases
 *  0, otherwise
 */

int chatbot_is_smalltalk(const char* intent) {
	/* to be implemented */	
	if (compare_token(intent, "reset") == 0 || compare_token(intent, "save") || compare_token(intent, "load") || compare_token(intent, "who")
		|| compare_token(intent, "what") || compare_token(intent, "where"))
		return 0;
	else
		return 1;
}

struct smalltalklist {
	char input[64];
	char response[2][255];
	struct smalltalklist* next;
}*head;
typedef struct smalltalklist SMALLTALKLIST;
typedef SMALLTALKLIST* SMALLPTR;

/*
 * Respond to smalltalk.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop chatting (e.g. the smalltalk was "goodbye" etc.)
 */

int search(char input[64], SMALLPTR head) {
	SMALLTALKLIST* node;
	int index = 0;
	
	node = head;
	while (head != NULL && strcmp(head->input, input)!=0) {
		index++;
		head = head->next;
	}
	return (head != NULL) ? index : -1;
}

int chatbot_do_smalltalk(int inc, char* inv[], char* response, int n) {

	int index;
	SMALLPTR head;
	head = (SMALLPTR)calloc(3, sizeof(*head));
	SMALLTALKLIST st1 = { "morning", {"Good Morning, have a great day ahead.","Morning! Good weather today!"} };
	SMALLTALKLIST st2 = { "afternoon", {"Good Afternoon, remember to take a break once in awhile.", "Afternoon! What a great day!"} };
	SMALLTALKLIST st3 = { "evening", {"Good Evening, great work today.", "Evening! Have a great night ahead!" } };
	SMALLTALKLIST st4 = { "hello",{ "Hello!!!", "Hi mate!" } };
	SMALLTALKLIST st5 = { "bye", {"Goodbye!", "Ciao!" } };
	st1.next = &st2;
	st2.next = &st3;
	st3.next = &st4;
	st4.next = &st5;
	head = &st1;

	if (strcmp(inv[0], "hi") == 0) {
		inv[0] = "hello";
	}

	if (strcmp(inv[0], "good") == 0) {
		if (inv[1] == NULL) {
			inv[0] = inv[0];
		}
		else { inv[0] = inv[1]; }
	}

	index = search(inv[0], head);
	if (index >= 0) {
		srand(time(NULL));
		int random = rand() % 2;
		for(int i=0; i<index;i++){
			head = head->next;
		}
		if (strcmp(head->input, "bye") != 0) {
			snprintf(response, n, "%s", head->response[random]);
			return 0;
		}
		else {
			snprintf(response, n, "%s", head->response[random]);
			return 1;
		}
	}
	else {
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 0;
	}
}
