/*Teodora Kostoska 0510085, Project 1 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Create struct for linked list
typedef struct node {
    char* item;
    struct node * next;
};

//Adds new lines to the beginning of the linked list thus reversing the given lines.
void push(struct node **head, char* data, size_t lines){
	struct node *temp = (struct node *) malloc(sizeof(struct node)); //Create new node
	if(temp == NULL){
		fprintf(stderr, "malloc failed\n");
		exit(1);
	}
	temp->item = (char *) malloc(lines *sizeof(char)); //allocate memory to item
	if(temp->item == NULL){
		fprintf(stderr, "malloc failed\n");
		exit(1);
	}
	strcpy(temp->item, data); //copy data to node item
	temp->next = *head; //next will be previous head
	*head = temp; //new head is the new node
}


int main(int argc, char **argv){
	struct node *head = NULL; //Base the head node
	if(argc == 1){
	/* stdin what user writes */
	//lets create a loop so that user can input as many lines as wanted
		char *line_buffer = NULL;//Will contain the line
  		size_t line_buffer_size = 0;//Base unsigned integer for line
  		ssize_t line_size = 0;//Number of chars
  		printf("Empty line or only enter ends the loop.\n");
		while(1){
  			line_size = getline(&line_buffer, &line_buffer_size, stdin);
  			if(line_size == 1||line_size == -1){ //Check whether there is no line
  				break;
  			}
  			push(&head, line_buffer, line_size);	
  		}
  		struct node *temp = head; 
		while(temp != NULL){ //Go through the linked list until empty and print the values
			fprintf(stdout, "%s", temp->item);
			temp = temp->next;
		}
		free(line_buffer);
	
	}else if(argc == 2 || argc == 3){
	/*input file only if argc == 2, input and output file if argc == 3*/ 
		//This is needed for both cases, opening the input file, transfering the lines onto a linked list
		FILE *fp = fopen(argv[1], "r");
	      	if(fp == NULL) {
         		fprintf(stderr,"error: cannot open file '%s'\n", argv[1]);
         		exit(1);
	     	}
 		char* line_buffer = NULL; //Will contain the line
 		size_t line_buffer_size = 0; //Base unsigned integer for line
 		ssize_t line_size; //Number of chars
 		 
 		
 		//Loop through all the lines untill the file is empty and add all lines to linked list
		while ((line_size = getline(&line_buffer, &line_buffer_size, fp)) != -1){
			push(&head,line_buffer, line_size);
		}
		
		//Check whether output file is given
		if(argc == 2){//if no output file
			struct node *temp = head; 
			while(temp != NULL){ //Go through the linked list until empty and print the values
				fprintf(stdout,"%s", temp->item);
				temp = temp->next;
			}
		}else if(argc == 3){//if output file given
			if(strcmp(argv[1], argv[2]) == 0){ //Check whether output and input file are same
				fprintf(stderr,"Input and output file must differ.\n");
				exit(1);
			}
			FILE *fp_output = fopen(argv[2], "w");
			if(fp_output == NULL){
				fprintf(stderr,"error: cannot open file '%s'\n", argv[2]);
         			exit(1);
			}
			struct node *temp2 = head;
			while(temp2 != NULL){//Go through linked list and add the values to the output file.
				fprintf(fp_output, "%s", temp2->item);
				temp2 = temp2->next;
			}
			fclose(fp_output);
		}
		free(line_buffer);
		fclose(fp);
    		exit(0);
	}else{
	/*too many arguments*/
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}
}

//All of the sources:
//https://riptutorial.com/c/example/8274/get-lines-from-a-file-using-getline--
//https://pvs-studio.com/en/blog/posts/cpp/a0050/
//https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
//https://solarianprogrammer.com/2019/04/03/c-programming-read-file-lines-fgets-getline-implement-portable-getline/
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/getline.html
//https://www.learn-c.org/en/Linked_lists
//https://www.geeksforgeeks.org/reverse-a-linked-list/
//https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
//https://www.learn-c.org/en/Linked_lists
//https://dev-notes.eu/2019/07/Get-a-line-from-stdin-in-C/
//https://www.tutorialspoint.com/c-program-to-check-if-two-strings-are-same-or-not

