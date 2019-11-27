/*
 * ICT1002 (C Language) Group Project, AY19 Trimester 1.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.i
 * kowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <dirent.h>
#include "chat1002.h"


/* knowledge base structure */
typedef struct node {
	char entity[MAX_ENTITY];
	char response[MAX_RESPONSE];
	struct node* next;
} KB_NODE;

KB_NODE* whatListHead = NULL;
KB_NODE* whoListHead = NULL;
KB_NODE* whereListHead = NULL;
KB_NODE* whenListHead = NULL;
KB_NODE* whyListHead = NULL;
KB_NODE* howListHead = NULL;





KB_NODE* create(char* entity, char* response)
{
	//make a new node
	KB_NODE* new_node = (KB_NODE*)malloc(sizeof(KB_NODE));
	//checks if the new node is make if not it be null
	if (new_node == NULL)
	{
		printf("Error creating a new node.\n");
		//to end the program if it fails to make a node
		exit(0);
	}
	//copy the entered string into the new node
	strcpy(new_node->entity, entity);
	//sets the node to point to the next one in this case Null
	strcpy(new_node->response, response);
	
	new_node->next = NULL;
	return new_node;
}

/* creates the head of the linked list */
KB_NODE* makefirst(KB_NODE* head, char* data, char* response)
{
	//make a node for the list
	KB_NODE* new_node = create(data, response);
	//set it as the head of the list
	head = new_node;
	return head;
}


/* for knowledge_read */
KB_NODE* append(KB_NODE* head, char* data, char* response)
{
	// create the head of the linklist if no head is found
	if (head == NULL) {
		head = makefirst(head, data, response);
		return head;
	}
	/* go to the last node */
	KB_NODE* currentNode = head;
	KB_NODE* found = NULL;
	while (currentNode != NULL) {
		if (compare_token(currentNode->entity, data) == 0) {
			strcpy(currentNode->response, response);
			found = currentNode;
			break;
		}
		currentNode = currentNode->next;
	}


	if (found == NULL) {
		KB_NODE* cursor = head;
		while (cursor->next != NULL)
			cursor = cursor->next;
		/* create a new node */
		KB_NODE* new_node = create(data, response);
		//sets the current node to point to the next one on the list
		cursor->next = new_node;
	}
	return head;
}


// find if there is a response for the given intent and entity
KB_NODE* findinlinkedlist(KB_NODE* listhead, const char* entity, int n)
{
	KB_NODE* temp = listhead;

	//check if list is empty
	if (temp == NULL)
	{
		return NULL;
	}
	else
	{
		while (temp->next != NULL)
		{
			// if the entity matches return the expected response
			if (compare_token(entity, temp->entity) == 0)
			{
				KB_NODE* returnvalue = (KB_NODE*)malloc(sizeof(KB_NODE));
				memcpy(returnvalue->entity, temp->entity, MAX_ENTITY);
				memcpy(returnvalue->response, temp->response, n);
				return returnvalue;

			}
			else
			{
				temp = temp->next;
			}

		}

		// check the last node
		if (temp->next == NULL)
		{
			if (compare_token(entity, temp->entity) == 0)
			{
				KB_NODE* returnvalue = (KB_NODE*)malloc(sizeof(KB_NODE));

				memcpy(returnvalue->entity, temp->entity, MAX_ENTITY);
				memcpy(returnvalue->response, temp->response, n);

				return returnvalue;
			}
			else
			{
				// if all of the above checks fail. Means the node is not found. Returns NULL.
				return NULL;
			}
		}
	}
}


KB_NODE* insertnode(KB_NODE* listhead, KB_NODE* newnode)
{
	// check if first node empty
	if (listhead == NULL)
	{
		return newnode;
	}

	// check if theres a 2nd node
	else if (listhead->next == NULL)
	{
		// if the entities are the same replace head response with new response
		{
			listhead->next = newnode;
			newnode->next = NULL;
			return listhead;
		}
	}

	// if there is a 2nd node
	else if (listhead->next != NULL)
	{
		KB_NODE* temp = listhead;

		while (temp->next != NULL)
		{
			if (strcmp(temp->entity, newnode->entity) == 0)
			{
				strcpy(temp->response, newnode->response);
				return listhead;
			}
			else
			{
				newnode->next = listhead;
				return newnode;
			}
			temp = temp->next;
		}
	}
}



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
int knowledge_get(const char* intent, const char* entity, char* response, int n)
{

	KB_NODE* temp = NULL;

	// compare to check intent
	if (compare_token(intent, "who") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			//loop through what linked list
			temp = findinlinkedlist(whoListHead, entity, n);			
			//return KB_OK;
		}
	}
	else if (compare_token(intent, "what") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			//loop through where linked list
			temp = findinlinkedlist(whatListHead, entity, n);
		}
	}

	else if (compare_token(intent, "when") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			//loop through who linked list
			temp = findinlinkedlist(whenListHead, entity, n);
		}
	}

	else if (compare_token(intent, "where") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			//loop through who linked list
			temp = findinlinkedlist(whereListHead, entity, n);
		}
	}

	else if (compare_token(intent, "why") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			//loop through who linked list
			temp = findinlinkedlist(whyListHead, entity, n);
		}
	}

	else if (compare_token(intent, "how") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			//loop through who linked list
			temp = findinlinkedlist(howListHead, entity, n);
		}
	}
	else
	{
		// ans is invalid
		return KB_INVALID;
	}

	// if temp is still NULL after the checks, then it is not found in the knowledge List
	if (temp == NULL)
	{
		// ans is not found
		return KB_NOTFOUND;
	}
	else
	{
		//ans is found
		char* buffer;
		buffer = strtok(temp->response, "\n");
		snprintf(response, n, "%s", buffer);
		return KB_OK;
	}
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

	// compare to check intent
	if (compare_token(intent, "who") == 0)
	{

		KB_NODE* newnode = create(entity, response);
		// check if newnode is null then return error
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whoListHead = insertnode(whoListHead, newnode);
			return KB_OK;
		}
	}

	else if (compare_token(intent, "what") == 0)
	{
		KB_NODE* newnode = create(entity, response);
		// check if newnode is null then return error
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whatListHead = insertnode(whatListHead, newnode);
			return KB_OK;
		}

	}

	else if (compare_token(intent, "when") == 0)
	{
		KB_NODE* newnode = create(entity, response);
		// check if newnode is null then return error
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whenListHead = insertnode(whenListHead, newnode);
			return KB_OK;
		}

	}

	else if (compare_token(intent, "where") == 0)
	{
		KB_NODE* newnode = create(entity, response);
		// check if newnode is null then return error
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whereListHead = insertnode(whereListHead, newnode);
			return KB_OK;
		}

	}

	else if (compare_token(intent, "why") == 0)
	{
		KB_NODE* newnode = create(entity, response);
		// check if newnode is null then return error
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whyListHead = insertnode(whyListHead, newnode);
			return KB_OK;
		}

	}

	else if (compare_token(intent, "how") == 0)
	{
		KB_NODE* newnode = create(entity, response);
		// check if newnode is null then return error
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			howListHead = insertnode(howListHead, newnode);
			return KB_OK;
		}

	}
	else
	{
		// if what/where/who are not met, return invalid.
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
	int dict = 0;
	int count = 0;

	char line[2 + MAX_ENTITY + MAX_RESPONSE];

	while (fgets(line, 2 + MAX_ENTITY + MAX_RESPONSE, f) != NULL)
	{

		/* ignore blank lines */
		if (line[0] == '#' || line[0] == '\n') {
			continue;
		}

		/* check for bracket lines such as "[who]" */
		if (strchr(line, '[') != NULL && strchr(line, ']') != NULL) {

			if (strstr(line, "who")) {
				dict = 1;
			}
			else if (strstr(line, "what")) {
				dict = 2;
			}
			else if (strstr(line, "when")) {
				dict = 3;
			}
			else if (strstr(line, "where")) {
				dict = 4;
			}
			else if (strstr(line, "why")) {
				dict = 5;
			}
			else if (strstr(line, "how")) {
				dict = 6;
			}
			else { dict = 0; }
		}
		else if (dict != 0 && strchr(line, '=') != NULL) 
		{
			/* seperate the entity and response from the line */
			char* entity = strtok(line, "=");
			char* response = strtok(NULL, "=");

			//depending on dictionary it will put the LL_NODE in the linklist for the type of question
			switch(dict)
			{
				case 1:
					whoListHead = append(whoListHead, entity, response);
					break;

				case 2:
					whatListHead = append(whatListHead, entity, response);
					break;

				case 3:
					whenListHead = append(whenListHead, entity, response);
					break;

				case 4:
					whereListHead = append(whereListHead, entity, response);
					break;

				case 5:
					whyListHead = append(whyListHead, entity, response);
					break;

				case 6:
					howListHead = append(howListHead, entity, response);
					break;
			}


			/* count number of lines read */
			count++;
		}

	}

	return count;
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {
	KB_NODE* tmp;
	//emptys and free the list from memory
	while (whoListHead != NULL)
	{
		tmp = whoListHead->next;
		free(whoListHead);
		whoListHead = tmp;
	}
	while (whatListHead != NULL)
	{
		tmp = whatListHead->next;
		free(whatListHead);
		whatListHead = tmp;
	}

	while (whenListHead != NULL)
	{
		tmp = whenListHead->next;
		free(whenListHead);
		whenListHead = tmp;
	}

	while (whereListHead != NULL)
	{
		tmp = whereListHead->next;
		free(whereListHead);
		whereListHead = tmp;
	}
	
	while (whyListHead != NULL)
	{
		tmp = whyListHead->next;
		free(whyListHead);
		whyListHead = tmp;
	}
	while (howListHead != NULL)
	{
		tmp = howListHead->next;
		free(howListHead);
		howListHead = tmp;
	}

}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE* f) {
	KB_NODE* printed = whoListHead;
	char newline[MAX_ENTITY + MAX_RESPONSE + 2];
	char entity[MAX_ENTITY];
	char response[MAX_RESPONSE];
	//prints the who section
	fprintf(f, "%s\n", "[who]");
	while (printed != NULL)
	{
		memcpy(entity, printed->entity, strlen(printed->entity) + 1);
		memcpy(response, printed->response, strlen(printed->response) + 1);
		fprintf(f, "%s%c%s", entity, '=', response);
		printed = printed->next;
	}
	//prints the what section
	printed = whatListHead;
	fprintf(f, "%s", "\n[what]\n");
	while (printed != NULL)
	{
		memcpy(entity, printed->entity, strlen(printed->entity) + 1);
		memcpy(response, printed->response, strlen(printed->response) + 1);
		fprintf(f, "%s%c%s", entity, '=', response);
		printed = printed->next;
	}

	printed = whenListHead;
	fprintf(f, "%s", "\n[when]\n");
	while (printed != NULL)
	{
		memcpy(entity, printed->entity, strlen(printed->entity) + 1);
		memcpy(response, printed->response, strlen(printed->response) + 1);
		fprintf(f, "%s%c%s", entity, '=', response);
		printed = printed->next;
	}

	//prints the where section
	printed = whereListHead;
	fprintf(f, "%s", "\n[where]\n");
	while (printed != NULL)
	{
		memcpy(entity, printed->entity, strlen(printed->entity) + 1);
		memcpy(response, printed->response, strlen(printed->response) + 1);
		fprintf(f, "%s%c%s", entity, '=', response);
		printed = printed->next;
	}

	printed = whyListHead;
	fprintf(f, "%s", "\n[why]\n");
	while (printed != NULL)
	{
		memcpy(entity, printed->entity, strlen(printed->entity) + 1);
		memcpy(response, printed->response, strlen(printed->response) + 1);
		fprintf(f, "%s%c%s", entity, '=', response);
		printed = printed->next;
	}

	printed = howListHead;
	fprintf(f, "%s", "\n[how]\n");
	while (printed != NULL)
	{
		memcpy(entity, printed->entity, strlen(printed->entity) + 1);
		memcpy(response, printed->response, strlen(printed->response) + 1);
		fprintf(f, "%s%c%s", entity, '=', response);
		printed = printed->next;
	}
	

	
}
