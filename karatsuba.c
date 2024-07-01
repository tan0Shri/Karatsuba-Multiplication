#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Structure to store a number along with its length in byte
struct number{
	int len;
	unsigned char *num;
};

FILE *input_file;	//global file pointer for input
FILE *output_file;	//global file pointer for showing output

//File opening function
FILE * fileopen(const char *mode)
{
    FILE* file;
    char FileName[256];
    
    if(mode == "r") 
        printf("Enter your input file name: ");
    else 
        printf("Enter your output file name: ");
        
    scanf("%s",FileName);
    file = fopen(FileName,mode);
    
    if (file == NULL){
        printf("Error opening the file.\n");
        exit(1);
        }       
    
    return file;
}

// Function to create a dyamically allocated array to store a number
struct number makeInt(int SIZE){
    struct number a;
    a.num = (unsigned char*)malloc(SIZE);
    memset(a.num,0,SIZE);
    if (a.num == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    a.len = SIZE;
    return a;
}

// Function to convert a hexadecimal string to an array of unsigned char
int hextoint(char hex) {
	//Conversion of hex characters to decimal value 
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    } else if (hex >= 'a' && hex <= 'f') {
        return hex - 'a' + 10;
    } else if (hex >= 'A' && hex <= 'F') {
        return hex - 'A' + 10;
    }
    return -1; // Invalid hexadecimal character
}
struct number hexToInt(char* hex,int size){
	struct number binInt= makeInt(size);
	for (int i=1; i<= size; i++) // Ignore the first byte containing 0x
		binInt.num[i-1]= (hextoint(hex[2*i])<<4) + hextoint(hex[2*i+1]);
	
	return binInt;
}

//taking input into variable a
void readInt(struct number* num1, struct number* num2) {
    char ch;
    int size[2]={0,0}; // Store the length of two numbers temporarily
    int count =0;
    while (fscanf(input_file, "%*s %d", &size[count]) == 1){
    		count++;
    	}
		rewind(input_file);	
		char buf1[2*size[0]+2];
		fscanf(input_file,"%s %*d", buf1);
		char buf2[2*size[1]+2];
		fscanf(input_file,"%s %*d", buf2);
		*num1= hexToInt(buf1,size[0]);
		*num2= hexToInt(buf2,size[1]);		
}

// Function to write integers to a file
void writeInt(struct number integer) {
    int flag=0;
    for(int i=0; i<integer.len; ++i){
	        if(flag!=0 || integer.num[i]!=0){
	            fprintf(output_file,"%02x",integer.num[i]);
	            flag=1;
	        }
		}
		fprintf(output_file,"\n");
}

#include "add&sub.h"
#include "karatsuba.h"

int main(){
    //opening file for input    
    input_file = fileopen("r");
    
    //opening file for output
    output_file = fileopen("w");
      
    struct number num1, num2, result;
    
    
    readInt(&num1,&num2);
    fprintf(output_file, "Given two numbers are:\n");
    writeInt(num1);
    //fprintf(output_file,"\n"););
    writeInt(num2);
    
    
    //struct number result;
    result = karatsuba(&num1, &num2);
    fprintf(output_file, "\nMultiplication of above two number is: \n");
    writeInt(result);
    
	
    free(num1.num);
    free(num2.num);
    free(result.num);
	
    // Close the files
    fclose(input_file);
    fclose(output_file);
    return 0;
} 
