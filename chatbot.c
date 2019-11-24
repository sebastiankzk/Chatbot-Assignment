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

	/* chatbot_do_exit will invoke as long as one of the compare_token returns 0, (0 == 0 = 1), 1 OR 'anything' will be 1 */
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

	/* edit this to change chatbot response when you quit */
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

	/* to be implemented */

	/* chatbot_do_load will invoke if compare_token returns 0, (0 == 0) = 1 */
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

	/* to be implemented */
	int botintel = 0; // to store how many entity responses loaded from ini file

	//FILE* fp = fopen(inv[1], "r"); // supposed to be this
	FILE* fp = fopen("sample.ini", "r");// hard code first while testing, change name of user
	if (fp != NULL) {
		botintel = knowledge_read(fp);
		fclose(fp);
	}

	/* test ini file has 11 lines of entity responses */
	snprintf(response, n, "Read %d responses from %s.", botintel, inv[1]);

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

	// Retrieve all sections from INI file
	char INISection[256];
	GetPrivateProfileSectionNames(INISection, MAX_INPUT, INIAddress);

	// Loop through array to retrieve each section
	char* section = INISection;
	while (*section) {

		// Check if intent exists
		if (compare_token(intent, section) == 0)
		{
			return 1;
		}
		section = strchr(section, '\0');
		section++;
	}

	return 0;
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

	const char skippedwords[4][5] = { "is", "are", "was", "were" };
	//bool skip = 0;
	int intent = 0;
	int startentity = 1;

	// Check if 2nd word is a filler word
	for (int i = 0; i < inc; i++)
	{
		if (strcmp(skippedwords + i, inv[1]) == 0)
		{
			//skip = 1; 
			startentity = 2;
			break;
		}
	}

	// check if entity is more than 1 word and join them into a string
	int spacecnt = 0;
	char entity[MAX_INPUT];
	char test[MAX_INPUT] = " ";
	while (inv[startentity] != NULL)
	{
		if (startentity == 2)
		{
			strcpy(entity, inv[startentity]);
			spacecnt = 1;
		}
		else
		{
			strcat(test, inv[startentity]);
			strcat(entity, test);
		}
		startentity++;
	}

	// Get answer from knowledge
	int output = knowledge_get(inv[intent], entity, response, MAX_INPUT);

	if (output == 0)
	{

	}
	else
	{
		char buffer[MAX_INPUT];
		//snprintf(response, n, "I don't understand what you said");
		printf("%s: I don't know \"%s\".\n",chatbot_botname() ,inv[startentity]);
		printf("%s: ", chatbot_username());
		fgets(buffer, MAX_INPUT, stdin);
		if (strcmp(buffer, "\n") != 0)
		{
			knowledge_put(inv[intent], inv[startentity], buffer);
			snprintf(response, n, "Thank You.");
		}
		
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

	/* to be implemented */

	/* chatbot_do_reset will invoke if compare_token returns 0, (0 == 0) = 1 */
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

	/* to be implemented */
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

	/* to be implemented */
	
	


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
	return
		compare_token(intent, "hello") == 0 ||
		compare_token(intent, "hi") == 0 ||
		compare_token(intent, "good") == 0 ||
		compare_token(intent, "hey") == 0;

}


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
int chatbot_do_smalltalk(int inc, char* inv[], char* response, int n) {

	/* to be implemented */
	if (strcmp(inv[0], "hello") == 0)
	{
		snprintf(response, n, "Hello!!!");
		return 0;
	}

	else if (strcmp(inv[0], "good") == 0)
	{
		if (strcmp(inv[1], "morning") == 0)
		{
			snprintf(response, n, "Good Morning, have a great day ahead.");
			return 0;
		}
		else if (strcmp(inv[1], "afternoon") == 0)
		{
			snprintf(response, n, "Good Afternoon, remember to take a break once in awhile.");
			return 0;
		}
		else if (strcmp(inv[1], "evening") == 0)
		{
			snprintf(response, n, "Good Evening, great work today!");
			return 0;
		}
		return 0;
	}

	else if (strcmp(inv[0], "goodbye"))
	{
		snprintf(response, n, "All right, see you then.");
		return 1;
	}

	else
	{
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 1;
	}

}
  