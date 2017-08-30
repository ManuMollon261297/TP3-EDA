/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include "lib.h"

#define OPTION '-'
#define EOW '\0'
#define SPACE ' '

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData){

	int i = 1, ret; 
	int opt_and_params = 0;

	while(i < argc){
		if(*argv[i] == OPTION){ // is option
			if((i+1 != argc)&&( *(argv[i]+1) != EOW)&&(*(argv[i]+1) != SPACE)){
				
				ret = p(argv[i]+1, argv[i+1], userData);
				i += 2;
			}
			else{
				ret = -1;
			}
		}
		else{ // is parameter
			
			ret = p(NULL, argv[i], userData);
			i++;
		}

		if((ret == -1)||(ret == 0)) // any error
			return ret;
		else
			opt_and_params++; // count options and parameters
	}

	return opt_and_params;
} 

