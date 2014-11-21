/*
Justin Canton, 1000017910
Samprit Raihan, 998138830
*/
#include "codegen.h"

void generateAssembly(node * ast){
	printf("Generating assembly.....\n");
	// Open the assembly file
	FILE *filePointer;	
	filePointer = fopen("./frag.txt", "w");
	
	/*
		From this point on, keep adding new instructions
		to the assembly file on a new line using 
		fprint(filePointer, <newline terminated string>)
	*/
	
	// Close the assembly file
	fclose(filePointer);
}