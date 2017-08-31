//// -------------- ////
//// PARSER LIBRARY ////
//// -------------- ////
#ifndef LIB_H
#define LIB_H

typedef int (*pCallback) (char*,char*,void*);

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);

#endif /* LIB_H */

