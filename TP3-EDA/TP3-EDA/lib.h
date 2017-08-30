<<<<<<< HEAD
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lib.h
 * Author: matias
 *
 * Created on August 29, 2017, 11:00 PM
 */

#ifndef LIB_H
#define LIB_H

typedef int (*pCallback) (char*,char*,void*);



int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);


#endif /* LIB_H */

=======
///////////////////////////////////////////
//// --------------------------------- ////
//// | LIBRERIA: Command line parser | ////
//// --------------------------------- ////
//// EDA - TP1 - Grupo 3               ////
////  - NOWIK, Ariel                   ////
////  - REGUEIRA, Marcelo              ////
////  - VIJANDE, Ezequiel              ////
///////////////////////////////////////////
#ifndef LIB_H
#define LIB_H

typedef int (*pCallback) (char*,char*,void*);

typedef struct{ /// parametro u opcion
    int type;
    char *key;
    char *value;
}t_action;

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);

#endif /* LIB_H */
>>>>>>> 4bdbf3251685d2946f8d85d509dc55566905a06d
