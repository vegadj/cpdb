//
//  cpdb.h
//  cpdb
//
//  Created by Gokhan SELAMET on 28/09/2016.
//  Copyright © 2016 Gokhan SELAMET. All rights reserved.
//

#ifndef cpdb_h
#define cpdb_h

#include <stdio.h>

#define VERSION_CPDB "$Id$"

typedef struct pdb pdb;
typedef struct chain chain;
typedef struct residue residue;
typedef struct atom atom;
typedef struct v3 v3;

pdb* initPDB();
int parsePDB (char *pdbFilePath, pdb *P , char *options);
/*
 by default, parsePDB function do not parse 'Hydrogene' atoms and 'Alternate Location' atoms.
 To parse these atoms you can pass `options` variable with these characters
 	h: for parsing hydrogen atoms
 	l: for parsing alternate locations
 	a: is equal to h and l both on
*/
int writePDB (const char *filename, const pdb *P);
int writeFilePDB (FILE *F, const pdb *P);
int printPDB (pdb *P);
void freePDB (pdb *P);

void appendChaintoPdb (pdb *P, chain newChain);
void appendResiduetoChain (chain *C, residue newResidue);
void appendAtomtoResidue (residue *R, atom newAtom);

struct v3 {
    float x,y,z;
};

struct atom {
    int id;
	int idx;
    char type[5];
    char element[3];
    v3 coor;
	float tfactor, occupancy;
	atom *next, *prev;
    residue *res;
};

struct residue {
    int id;
	int idx;
    char type[5];
    atom *atoms;
    int size;
    int __capacity;
    residue *next, *prev;
};

struct chain {
    char id;
    residue *residues;
    int size;
    int __capacity;
};

struct pdb {
    chain *chains;
    int size;
    int __capacity;
    char name[32];
};

#endif /* cpdb_h */
