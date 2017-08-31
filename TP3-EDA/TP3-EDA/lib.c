#include <stdio.h>
#include "lib.h"

#define OPTION '-'
#define EOW '\0'
#define SPACE ' '

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData){

	int i = 1, ret; 
	int opt_and_params = 0;

	while(i < argc){
		if(*argv[i] == OPTION){ // Is option
			if((i+1 != argc)&&( *(argv[i]+1) != EOW)&&(*(argv[i]+1) != SPACE)){
				//printf("%s\n", argv[i]+1);
				//printf("%s\n\n", argv[i+1]);
				ret = p(argv[i]+1, argv[i+1], userData);
				i += 2;
			}
			else{
				ret = -1;
			}
		}
		else{ // Is parameter
			//printf("%s\n\n", argv[i]);
			ret = p(NULL, argv[i], userData);
			i++;
		}

		if((ret == -1)||(ret == 0)) // Any error
			return ret;
		else
			opt_and_params++; // Count options and parameters
	}

	return opt_and_params;
}
