//Teodora Kostoska 0510085, Assignment 2 Part 4: my-unzip

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 int main(int argc, char **argv){
 	if(argc == 1){ //Check whether file for unzipping given
 		fprintf(stderr, "my-unzip: file1 [file2 ...]\n"); //Print error if not
 		exit(1);
 	}else{
 		int files = 1; //Keep track of files given
 		while(files < argc){//go through all files given
 			FILE *fp = fopen(argv[files], "r");//open file
			if(fp == NULL) {//check whether open successful
        			fprintf(stderr,"error: cannot open file '%s'\n", argv[1]); //print error if failed
         			exit(1);
			}

			fseek(fp, 0L, SEEK_END);//Find ending of file
			long sz = ftell(fp);//get size of file in bytes
			rewind(fp);//back to beginning of file
 	
			int num;//keep track of the numbers in file
			ssize_t line_size;//save the result of fread
			int i = 0;//going through the bytes
	
			while(i < sz){//as long as i is smaller than the size of the file
				fseek(fp,i,SEEK_SET); //get the file at the i:th byte
				line_size = fread(&num,sizeof(int),1,fp);//read the binary number to int
				fseek(fp,i+4,SEEK_SET);//Then seek the char which is at the i+4:th space
				char letter[2] = "\0";//The char needs to be transformed into a string
				letter[0] = getc(fp);//Save tha char into the string array. Will look like: char\0
				for(int j = 0; j < num; j++){//The char needs to be printed out as many times as the binary num informed
					printf("%s",letter);
				}
				i = i+5;//Going through incraments of 5, as format is 4 byte binary int and 1 char
			}
			fclose(fp);//close file
			files++;//go to next file
		}
 	}
 	exit(0);
 }
 
 //Sources: 
 //https://stackoverflow.com/questions/22621952/convert-char-to-string-in-c/28015754
 //https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
 //https://www.educative.io/edpresso/c-reading-data-from-a-file-using-fread
 //https://overiq.com/c-programming-101/fread-function-in-c/
 //https://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm
 //https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
