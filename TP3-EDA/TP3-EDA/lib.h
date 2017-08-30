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

