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


/* function to create a new node for the linked list */
KB_NODE* create_node(char* entity, char* response)
{
	/* allocate memory for a new node */
	KB_NODE* new_node = (KB_NODE*)malloc(sizeof(KB_NODE));

	/* check for malloc failure */
	if (new_node == NULL)
	{
		printf("Error creating a new node.\n");
		//to end the program if it fails to make a node
		exit(0);
	}

	/* copy entity and response into the node */
	strcpy(new_node->entity, entity);
	strcpy(new_node->response, response);
	
	new_node->next = NULL;

	return new_node;
}


/* function to create the head of the linked list */
KB_NODE* create_head(KB_NODE* head, char* data, char* response)
{
	/* call function to create node */
	KB_NODE* new_node = create_node(data, response);

	head = new_node;

	return head;
}


/* function for knowledge_read */
KB_NODE* append(KB_NODE* head, char* data, char* response)
{
	/* if linked list is empty create head node and return */
	if (head == NULL) {
		head = create_head(head, data, response);

		return head;
	}

	/* temporary pointers */
	KB_NODE* currentNode = head;
	KB_NODE* found = NULL;

	/* loop through linked list to find existing entity, if found then overwrite reponse */
	while (currentNode != NULL) {
		if (compare_token(currentNode->entity, data) == 0) {
			strcpy(currentNode->response, response);
			found = currentNode;

			break;
		}

		currentNode = currentNode->next;
	}

	/* if no existing entity found then append to linked list */
	if (found == NULL) {
		KB_NODE* cursor = head;

		/* loop to the last node */
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}

		/* create a new node */
		KB_NODE* new_node = create_node(data, response);
		cursor->next = new_node;
	}

	return head;
}


/* function to find reponse in linked list based on intent and entity */
KB_NODE* check_linkedlist(KB_NODE* listhead, const char* entity)
{
	KB_NODE* temp = listhead;

	/* check if linked list is empty */
	if (temp == NULL)
	{
		return NULL;
	}
	else
	{
		while (temp->next != NULL)
		{
			if (compare_token(entity, temp->entity) == 0)
			{
				KB_NODE* returnvalue = (KB_NODE*)malloc(sizeof(KB_NODE));

				memcpy(returnvalue->entity, temp->entity, MAX_ENTITY);
				memcpy(returnvalue->response, temp->response, MAX_RESPONSE);

				return returnvalue;
			}
			else
			{
				temp = temp->next;
			}

		}

		if (temp->next == NULL)
		{
			if (compare_token(entity, temp->entity) == 0)
			{
				KB_NODE* returnvalue = (KB_NODE*)malloc(sizeof(KB_NODE));

				memcpy(returnvalue->entity, temp->entity, MAX_ENTITY);
				memcpy(returnvalue->response, temp->response, MAX_RESPONSE);

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


/* function to link the node in the linked list */
KB_NODE* link_node(KB_NODE* listhead, KB_NODE* newnode)
{
	/* if no nodes inside list link node as head */
	if (listhead == NULL)
	{
		return newnode;
	}
	/* if head exists but 2nd node does not exist then link node after head */
	else if (listhead->next == NULL)
	{		
		listhead->next = newnode;
		newnode->next = NULL;

		return listhead;
	}
	/* if head and 2nd node exists, loop through linked list and link the node */
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

	if (compare_token(intent, "who") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			/* loop though linked list for 'who' intent */
			temp = check_linkedlist(whoListHead, entity);
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
			/* loop though linked list for 'what' intent */
			temp = check_linkedlist(whatListHead, entity);
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
			/* loop though linked list for 'when' intent */
			temp = check_linkedlist(whenListHead, entity);
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
			/* loop though linked list for 'where' intent */
			temp = check_linkedlist(whereListHead, entity);
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
			/* loop though linked list for 'why' intent */
			temp = check_linkedlist(whyListHead, entity);
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
			/* loop though linked list for 'how' intent */
			temp = check_linkedlist(howListHead, entity);
		}
	}
	else
	{
		return KB_INVALID;
	}

	/* answer not found in knowledge base if temp is NULL */
	if (temp == NULL)
	{
		return KB_NOTFOUND;
	}
	/* if answer is found print the response */
	else
	{
		char* buffer = strtok(temp->response, "\n");

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
	
	if (compare_token(intent, "who") == 0)
	{
		KB_NODE* newnode = create_node(entity, response);
		
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whoListHead = link_node(whoListHead, newnode);
			return KB_OK;
		}
	}
	else if (compare_token(intent, "what") == 0)
	{
		KB_NODE* newnode = create_node(entity, response);
		
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whatListHead = link_node(whatListHead, newnode);
			return KB_OK;
		}

	}
	else if (compare_token(intent, "when") == 0)
	{
		KB_NODE* newnode = create_node(entity, response);
		
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whenListHead = link_node(whenListHead, newnode);
			return KB_OK;
		}

	}
	else if (compare_token(intent, "where") == 0)
	{
		KB_NODE* newnode = create_node(entity, response);
		
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whereListHead = link_node(whereListHead, newnode);
			return KB_OK;
		}

	}
	else if (compare_token(intent, "why") == 0)
	{
		KB_NODE* newnode = create_node(entity, response);
		
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whyListHead = link_node(whyListHead, newnode);
			return KB_OK;
		}

	}
	else if (compare_token(intent, "how") == 0)
	{
		KB_NODE* newnode = create_node(entity, response);
		
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			howListHead = link_node(howListHead, newnode);
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
	int which_list = 0;
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
				which_list = 1;
			}
			else if (strstr(line, "what")) {
				which_list = 2;
			}
			else if (strstr(line, "when")) {
				which_list = 3;
			}
			else if (strstr(line, "where")) {
				which_list = 4;
			}
			else if (strstr(line, "why")) {
				which_list = 5;
			}
			else if (strstr(line, "how")) {
				which_list = 6;
			}
			else { 
				which_list = 0; 
			}

		}
		/* check for entity response lines */
		else if (which_list != 0 && strchr(line, '=') != NULL) 
		{
			/* seperate the entity and response from the line */
			char* entity = strtok(line, "=");
			char* response = strtok(NULL, "=");

			/* link node to linked list based on current intent section */
			switch(which_list)
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
	
	/* loop though all linked lists and free the memory to clear knowledge base */
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
	char newline[MAX_ENTITY + MAX_RESPONSE + 2];
	char entity[MAX_ENTITY];
	char response[MAX_RESPONSE];

	KB_NODE* printed = whoListHead;
	/* write "who" section header then loop through "who" linked list to write entities and responses */
	fprintf(f, "%s\n", "[who]");
	while (printed != NULL)
	{
		memcpy(entity, printed->entity, strlen(printed->entity) + 1);
		memcpy(response, printed->response, strlen(printed->response) + 1);
		fprintf(f, "%s%c%s", entity, '=', response);
		printed = printed->next;
	}

	printed = whatListHead;
	/* write "what" section header then loop through "what" linked list to write entities and responses */
	fprintf(f, "%s", "\n[what]\n");
	while (printed != NULL)
	{
		memcpy(entity, printed->entity, strlen(printed->entity) + 1);
		memcpy(response, printed->response, strlen(printed->response) + 1);
		fprintf(f, "%s%c%s", entity, '=', response);
		printed = printed->next;
	}

	printed = whenListHead;
	/* write "when" section header then loop through "when" linked list to write entities and responses */
	fprintf(f, "%s", "\n[when]\n");
	while (printed != NULL)
	{
		memcpy(entity, printed->entity, strlen(printed->entity) + 1);
		memcpy(response, printed->response, strlen(printed->response) + 1);
		fprintf(f, "%s%c%s", entity, '=', response);
		printed = printed->next;
	}

	printed = whereListHead;
	/* write "where" section header then loop through "where" linked list to write entities and responses */
	fprintf(f, "%s", "\n[where]\n");
	while (printed != NULL)
	{
		memcpy(entity, printed->entity, strlen(printed->entity) + 1);
		memcpy(response, printed->response, strlen(printed->response) + 1);
		fprintf(f, "%s%c%s", entity, '=', response);
		printed = printed->next;
	}
	
	printed = whyListHead;
	/* write "why" section header then loop through "why" linked list to write entities and responses */
	fprintf(f, "%s", "\n[why]\n");
	while (printed != NULL)
	{
		memcpy(entity, printed->entity, strlen(printed->entity) + 1);
		memcpy(response, printed->response, strlen(printed->response) + 1);
		fprintf(f, "%s%c%s", entity, '=', response);
		printed = printed->next;
	}

	printed = howListHead;
	/* write "how" section header then loop through "how" linked list to write entities and responses */
	fprintf(f, "%s", "\n[how]\n");
	while (printed != NULL)
	{
		memcpy(entity, printed->entity, strlen(printed->entity) + 1);
		memcpy(response, printed->response, strlen(printed->response) + 1);
		fprintf(f, "%s%c%s", entity, '=', response);
		printed = printed->next;
	}
	

	
}
