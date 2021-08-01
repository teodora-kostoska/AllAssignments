// Teodora Kostoska 0510085, Project 2 Part 1: my-cat
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	if(argc == 1){ //First checking whether there is any file given
		printf("No files given.\n"); //If not given prints this message and exits without error.
		exit(0);
	}else{
		int count = 1;//To keep track of all of the files given
		while(count < argc){ //As long as the count is smaller than everything given in command line argument
			FILE *fp = fopen(argv[count], "r");//opening file by using count to point the order
			if(fp == NULL) { //Check whether file opened successfully
         			fprintf(stderr, "my-cat: cannot open file. \n"); //Error if didn't open
         			perror("error");//more information on error
         			exit(1);
			}
			printf("Reading file: '%s'\n\n", argv[count]);//Which file is read
 			char string[300]; //buffer
			while(fgets(string, 300, fp)) {//read file
    				printf("%s", string);//print lines
			}		
			fclose(fp);//close file when ready
			count++;//add 1 to count for next file
		}
		exit(0);//Exit when program over. 
	}
}

//Sources: 
//https://www.tutorialspoint.com/c_standard_library/c_function_perror.htm
//https://www.geeksforgeeks.org/fgets-gets-c-language/
//https://www.educative.io/edpresso/how-to-use-the-fgets-function-in-c
