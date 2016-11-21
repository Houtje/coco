/*
 * IntermediateCode.h - Declaration of the IntermediateCode abstract data structure
 *
 * Part of the assignment of the Compiler Construction course
 * LIACS, Leiden University
 *
 * Note that deleting an IntermediateCode object will also delete all
 * IStatement objects associated to it.
 */

#ifndef _INTERMEDIATECODE_H_
#define _INTERMEDIATECODE_H_

#include <cstdio>
#include <vector>
#include "IStatement.h"


using namespace std;

// This class stores a linear list of intermediate statements and provides
// operations to modify that list.
class IntermediateCode {
  public:
    // Constructor/destructor
    IntermediateCode();
    ~IntermediateCode();

    // Gets the program name
    string GetProgramName();

    // Sets the program name
    void SetProgramName(string name);

    // Returns the number of statements
    unsigned int GetStatementCount();

    // Gets the i-th statement
    IStatement *GetStatement(unsigned int i);

    // Appends a statement
    void AppendStatement(IStatement *stmt);

    // Inserts a statement before the i-th statement
    void InsertStatement(IStatement *stmt, unsigned int i);

    // Removes the i-th statement
    void RemoveStatement(unsigned int i);

    // Dump
    void Dump(FILE *file);

  private:
    string programName;
    vector<IStatement*> statements;
};

#endif
