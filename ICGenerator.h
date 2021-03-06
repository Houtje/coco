/*
 * ICGenerator.h - Declaration of the ICGenerator class
 *
 * Part of the assignment of the Compiler Construction course
 * LIACS, Leiden University
 */

#ifndef _ICGENERATOR_H_
#define _ICGENERATOR_H_

#include "SyntaxTree.h"
#include "SymbolTable.h"
#include "IntermediateCode.h"


// This class handles the intermediate code generation. Extend it to your own
// needs.
class ICGenerator {
  public:
    // Constructor
    ICGenerator();

    // Destructor
    ~ICGenerator();

    // Preprocesses the syntax tree; this method is called before
    // GenerateIntermediateCode() if optimizations are enabled
    void Preprocess (SyntaxTree * tree, SymbolTable * symtab);
    
    // Takes a SyntaxTree and converts it into an IntermediateCode structure
    IntermediateCode * GenerateIntermediateCode (SyntaxTree * inputTree, SymbolTable * symtab);

    // Postprocesses the intermediate code; this method is called after
    // GenerateIntermediateCode() if optimizations are enabled
    void Postprocess (IntermediateCode * code, SymbolTable * symtab);
    
    IOperand *traverse_tree(Node *n, IntermediateCode *icode);

  private:
    // Generates a temporary symbol
    Symbol * GenerateTempVar(ReturnType type);
    
    // Generates a Symbol for a label
    Symbol * GenerateLabel();

    // ... your own private members and methods ...
    int tempCount;
    int labelCount;

};

#endif
