/*
 * IOperand.h - Declaration of the IOperand abstract data structure
 *
 * Part of the assignment of the Compiler Construction course
 * LIACS, Leiden University
 *
 * This file provides three different objects:
 *   - IOperand_Int
 *   - IOperand_Real
 *   - IOperand_Symbol
 * You can instantiate these objects using a constructor, for example:
 *   IOperand * myOperand = new IOperand_Int(42);
 * This creates an IOperand_Int object containing the value 42.
 *
 * Note that deleting an IOperand_Symbol does not lead to a deletion of its
 * Symbol object.
 */

#ifndef _IOPERAND_H_
#define _IOPERAND_H_

#include "Symbol.h"

// The type of an operand
typedef enum __ioperandtype {
  OT_UNKNOWN,               // Unknown (yet)
  OT_INT,                   // Integer immediate
  OT_REAL,                  // Real immediate
  OT_SYMBOL                 // Symbol object
} IOperandType;



// Operand of an IStatement
class IOperand {
  public:
    // Constructor/destructor
    IOperand();
    virtual ~IOperand();
    virtual IOperand * Clone() =0;
    
    // Get operand type
    IOperandType GetOperandType();
    
    // Set operand type
    void SetOperandType(IOperandType type);
    
    // Empty virtuals
    virtual int GetIntValue();
    virtual void SetIntValue(int newvalue);
    virtual float GetRealValue();
    virtual void SetRealValue(float newvalue);
    virtual Symbol *GetSymbol();
    virtual void SetSymbol(Symbol *sym);
    
    // Dump
    virtual void Dump(FILE *file)               =0;
   
  private:
    IOperandType optype;
};


// Integer operand
class IOperand_Int: public IOperand {
  public:
    // Constructor/destructor
    IOperand_Int();
    IOperand_Int(int newvalue);
    ~IOperand_Int();
    
    // Clone
    virtual IOperand_Int * Clone();
    
    // Get the integer value
    int GetIntValue();
  
    // Set the integer value
    void SetIntValue(int newvalue);
    
    // Dump
    void Dump(FILE *file);
    
  private:
    int value;
};


// Real operand
class IOperand_Real: public IOperand {
  public:
    // Constructor/destructor
    IOperand_Real();
    IOperand_Real(float newvalue);
    ~IOperand_Real();
    
    // Clone
    virtual IOperand_Real * Clone();
    
    // Get the float value
    float GetRealValue();
  
    // Set the float value
    void SetRealValue(float newvalue);
    
    // Dump
    void Dump(FILE *file);
    
  private:
    float value;
};


// Symbol operand
class IOperand_Symbol: public IOperand {
  public:
    // Constructor/destructor
    IOperand_Symbol();
    IOperand_Symbol(Symbol * newsym);
    ~IOperand_Symbol();
    
    // Clone
    virtual IOperand_Symbol * Clone();
    
    // Get the Symbol object
    Symbol *GetSymbol();
  
    // Set the Symbol object
    void SetSymbol(Symbol *sym);
    
    // Dump
    void Dump(FILE *file);
    
  private:
    Symbol *symbol;
};


#endif
