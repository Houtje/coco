/*
 * IStatement.h - Declaration of the IStatement abstract data structure
 *
 * Part of the assignment of the Compiler Construction course
 * LIACS, Leiden University
 *
 * Note that deleting an IStatement object will also delete the IOperand
 * objects associated to it.
 */

#ifndef _ISTATEMENT_H_
#define _ISTATEMENT_H_

#include <cstdio>
#include "IOperator.h"
#include "IOperand.h"

// A statement in the intermediate code (quadruple)
class IStatement {
  public:
    // Constructors/destructor
    IStatement();
    IStatement(IOperator op);
    IStatement(IOperator op, IOperand *opnd1, IOperand *opnd2, IOperand *res);
    ~IStatement();
    
    // Get operator
    IOperator GetOperator();
    
    // Set operator
    void SetOperator(IOperator op);
    
    // Get operand 1
    IOperand *GetOperand1();
    
    // Set operand 1
    void SetOperand1(IOperand *operand);
    
    // Get operand 2
    IOperand *GetOperand2();

    // Set operand 2
    void SetOperand2(IOperand *operand);
    
    // Get result operand
    IOperand *GetResult();

    // Set result operand
    void SetResult(IOperand *operand);
    
    // Dump
    void Dump(FILE *file, int indent);
    
  private:
    IOperator ioperator;
    IOperand *operand1;
    IOperand *operand2;
    IOperand *result;
};



#endif
