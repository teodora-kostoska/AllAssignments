//Teodora Kostoska 0510085 Project 2 Part 3: my-zip

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	if(argc==1){//Check whether file to zip is given
		fprintf(stderr, "my-zip: file1 [file2 ...]\n"); //Error if not
		exit(1);
	}else{
		//First open the file
		int files = 1;//Keep track of files
		while(files < argc){//as long as there are files
			FILE *fp = fopen(argv[files], "r");//open file
	      		if(fp == NULL) {//if some issue with opening file throw error
         			fprintf(stderr,"error: cannot open file '%s'\n", argv[1]);
         			exit(1);
	     		}
	     		char* line_buffer = NULL; //Will contain the line
 			size_t line_buffer_size = 0; //Base unsigned integer for line
 			ssize_t line_size; //Number of chars
 		 	//go through file one line at a time
			while ((line_size = getline(&line_buffer, &line_buffer_size, fp)) != -1){
				size_t i = 0;//go through chars in line
				int count = 1;//how many times a letter is present consecutively
				while(line_buffer[i] != '\0') {//as long as the line is not over
    					if(i+1==line_size){//if i+1 is the same as line size, then we are at the end of the line
    						break;
    					}else if(line_buffer[i]==line_buffer[i+1]){//check if two consecutive letters are the same
    						count++;//if they are then the count will be grown by 1
    					}else{	
    						fwrite((const void*) &count,sizeof(int),1,stdout);//If they are not same then the count will be printed in 4 byte binary
    						fwrite(&line_buffer[i], sizeof(char),1, stdout);//The letter will also be printed
    						count = 1;//return count back to beginning in order to count next letter
    					}
    					i++;
				}
			}
			fclose(fp);//close file
			files++;
		}
	}
	exit(0);
}


//Sources:
//https://stackoverflow.com/questions/772118/problem-writing-int-to-binary-file-in-c
//https://en.cppreference.com/w/c/io/fwrite
//https://www.delftstack.com/howto/c/compare-char-in-c/
//https://riptutorial.com/c/example/6514/iterating-over-the-characters-in-a-string
//https://www.geeksforgeeks.org/printing-frequency-of-each-character-just-after-its-consecutive-occurrences/
