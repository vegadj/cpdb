# cpdb
Pdb file parser library written in C

## What is Pdb file format ?
Pdb file format was created in 1970's and had been using for keeping 3D crystal structure of biological molecules. Besides there are newer generation formats Pdb format is still the commonly used one, since it the oldest and most humanly readable text based format.

## What is cpdb ?
cpdb is a library for parsing pdb files which is written in C language ( not C\+\+ ). Although there are good and reliable parsers in languages as C++, Python, Ruby etc, there are limited alternative to pure C language. This is the reason why `cpdb` born.

## Not a parser !
Since a good parser should parse all file without losing any information, `cpdb` is just focused on parsing `atoms` in pdb file. This is because me and most of other scientist are just dealing with topological studies. 

## Usage

### Quick Start
cpdb usage is stupidly easy with 4 steps.

1. include header into your own project `#include "cpdb.h"`
2. create a `pdb` type pointer and init `pdb *P = initPDB()`
3. parse pdb file from a path `parsePDB("foo/foo.pdb", P , "")`
4. release the pdb after your job is done `freePDB(P)`

### Basic Parsing Functions

#### pdb* initPDB()
for initialise pdb structure type. To work with `cpdb` all data is stored into one pdb structure type.

#### int parsePDB (char *pdbFilePath, pdb *P , char *options);
parsing pdb file from `pdbFilePath` path to `P` pdb type pointer. `options` is used for changing parser function behaviour.  

##### options
by default `parsePDB` function do not parse duplicated atoms and hydrogen atoms. This is common behaviour for many scientist. To parse these atoms 

* pass `h` for hydrogen
* pass `l` for alternate locations
* pass `a` for parsing all 

#### int writePDB (const char *filename, const pdb *P);
write pdb type to filepath given as `filename` with using pdb format. 

#### int writeFilePDB (FILE *F, const pdb *P);
write pdb type to file pointer given `F` For whom who needs to handle file opening by himself.

#### int printPDB (pdb *P);
prints pdb type as pdb format to screen

#### void freePDB (pdb *P);
free allocated pdb type

### Additional Creating functions

Here are some function for creating pdb type without existing file. For whom may want to use same structure without pdb file format.

void appendChaintoPdb (pdb *P, chain newChain);
void appendResiduetoChain (chain *C, residue newResidue);
void appendAtomtoResidue (residue *R, atom newAtom);

### Utils Functions

#### atom* getAtom (residue *resA, char *atomType);
returns desited `atomType` from residue type
	getAtom ( *Res, "CA" )

#### float distanceAtom (atom *A, atom*B);
calculate distance between two atoms


## Structure
This library has 5 types of custom structure. pdb, chain, residue, atom, v3. 
Here is these structure details. 

```
struct pdb {
    chain *chains;
    int size; // number of chains in pdb
    char name[32];
};

struct chain {
    char id;
    residue *residues;
    int size; // number of residues in chain
};
struct residue {
    int id;
    int idx;
    char type[5];
    atom *atoms;
    int size; // number of atoms in residue
    residue *next, *prev;
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

struct v3 {
    float x,y,z;
};
```

## TODO
### Checking pdb format
Sometimes, pdb format has some defects or there may be some missing residues or missing atoms in the crystal structure. Checking these defects should be added for both warning and correction level.

### Mutation Pdb
Add functions for delete and replace residues and atoms 

### Parse Secondary structure
Add parsing secondary structure info

### parse multiple model
add parsing multiple model for nmr 


## Warning
This library is still under development. It means that didn't passed my hardcore testing for scientific research yet. 
