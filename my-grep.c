

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	if(argc == 1){
	//No parameters given, even string
		fprintf(stderr,"my-grep: searchterm [file ...]\n");//Throws error
		exit(1);
	}else if(argc == 2){
	//No file given to search from, this is where we use user input
		char *line_buffer = NULL;//Will contain the line
  		size_t line_buffer_size = 0;//Base unsigned integer for line
  		ssize_t line_size = 0;//Number of chars
  		printf("Empty line or only enter ends the loop.\n");
		while(1){
  			line_size = getline(&line_buffer, &line_buffer_size, stdin); //get the standard input
  			if(line_size == 1||line_size == -1){ //Check whether there is no line
  				break;
  			}
  			if(strstr(line_buffer, argv[1]) != NULL){//compares the search term with the given lines and only prints the ones that contain the term
				printf("%s", line_buffer);
			}	
  		}
	
	}else{
	//File or files given
		int count = 2;//keep track of files
		while(count < argc){//as long as there are files
			FILE *fp = fopen(argv[count], "r");
			if(fp == NULL) {//check whether error with opening file
        			fprintf(stderr,"my-grep: cannot open file");//throws error
        			exit(1);
			}
			char* line_buffer = NULL; //Will contain the line
 			size_t line_buffer_size = 0; //Base unsigned integer for line
 			ssize_t line_size; //Number of chars	
 			//Loop through all the lines untill the file is empty and add all lines to linked list
			while ((line_size = getline(&line_buffer, &line_buffer_size, fp)) != -1){//go through all the lines in the file/s
				if(strstr(line_buffer, argv[1]) != NULL){//Check whether the line contains the given search term
					printf("%s", line_buffer);//prints if the line contains the term
				}
			}
   			fclose(fp);//close the file
   			free(line_buffer);//free the buffer
   			count++;//keep track of file num
   		}
   	}
   	exit(0);//successful exit
}

//References: 
//https://stackoverflow.com/questions/12784766/check-substring-exists-in-a-string-in-c/12784812
//https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm
//https://www.geeksforgeeks.org/strstr-in-ccpp/

