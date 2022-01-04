#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <string>
#include <sstream>

#include "stack.h"
#include "string.h"
#include "opnum.h"

using namespace std;
using namespace cop4530;

int main(int argc, char **argv)
{
   // Returns the precedence of an input
   int precedence(const char & inputChar);

   // Calculates current operation given two operands and the operator   
   float postfixCalc(const float & topFloat, const float & nextFloat, const string & tempChar);

   int retval = SYM_NULL;
   set_input(argc, argv);

   Stack<char> operators;          // Stores the operators for infix to postfix conversion
   Stack<float> operands;          // Stack to push and pop the operands for postfix evaluation

   string postfix;      // Stores the postfix expression as a string to be evauluated
   string tempInfix;    // Stores the infix expression to be printed if there is an error   

   // These are for error checking
   bool newLine;        // Flag for a new line, meaning the next expression.
   bool error;          // Keeps track if an error occurs
   bool typeError;      // Tracks if the expression uses an invalid operand type

   int matchingPar;    // Tracker for finding a matching '(' for ')'

   // These are for consecutive number tracking
   string consecNum;    // used to store and track consecutive numbers in the infix expression
   int numOfConsecNum;  // Used to know when to print the consecutive numbers
   string consecOp;     // used to store and track consecutive numbers in the infix expression
   int numOfConsecOp;   // Used to know when to print the consecutive operators

   // Loop for converting each expression to postfix and evaluating if possible.
   do{
      char * opnum;        // Stores the current opnum

      postfix = "";        // Resets the postfix expression tracker
      tempInfix = "";      // Resets the infix expression tracker

      operators.clear();   // Clears the operator stack
      operands.clear();    // Cleares the operand stack

      newLine = false;     // Flag to find the end of an expression
      error = false;       // Flag for errors
      typeError = false;   // Flag for invlaid operand types
      matchingPar = 0;     // Tracker for finding a matching '(' for ')'  

      consecNum = "";      // Resets consecutive number tracker
      numOfConsecNum = 0;
      consecOp = "";       // Resets consecutive operator tracker
      numOfConsecOp = 0;

      /* Converts a infix expression to a postfix expression and 
      stores it in a string. This also checks for errors, if there 
      is an error the error is printed and the conversion continues.
      Once the conversion is complete it will either continue to the 
      postfix evaluation or if there was an error the initial infix 
      expression is printed.*/
      while(newLine == false)
      {
         opnum = get_opnum(&retval);

         // Exit statment
         if(retval == SYM_NULL)
            break;

         // If not a new line, add to current infix expression.
         if(retval != SYM_NEWLINE && retval != SYM_INVAL)
         {
            tempInfix = tempInfix + opnum + " ";
         }

         // Prints the consecutive operands
         if(retval >= SYM_ADD && retval <= SYM_DIV || retval == SYM_NEWLINE)
         {
            // If this is an operator at the end of the expression
            if(numOfConsecOp == 1 && retval == SYM_NEWLINE)
               break;

            // If this is the second operator in a row there is an error
            if(consecOp != "")
            {
               error = true;
               consecOp = consecOp + opnum;
            }

            // Adds to the consecutive operator count
            numOfConsecOp++;

            if(numOfConsecNum > 1)
               cout << "Consecutive Numbers: " << consecNum << endl;      // Prints the consecutive numbers
            
            // Resets the consecutive number trackers
            consecNum = "";      
            numOfConsecNum = 0;
         }

         // Prints consecutive operators
         if(retval >= SYM_NAME && retval <= SYM_FLOAT || retval == SYM_NEWLINE)
         {

            // If this is the second number in a row there is an error
            if(consecNum != "")
            {
               error = true;
               consecNum = consecNum + opnum;
            }

            numOfConsecNum++;

            if(numOfConsecOp > 1)
               cout << "Consecutive Opcodes: " << consecOp << endl;        // Prints the consecutive operators

            // Resets the consecutive operator trackers
            consecOp = "";      
            numOfConsecOp = 0; 
         }

         if (retval) {
            switch (retval)
            {
               case SYM_NAME:
                  typeError = true;

                  // Checks for consecustive operands (already caught)
                  if(consecNum != "")
                     break;

                  consecNum = consecNum + opnum + " ";   // Adds new consecutive number to tracker
                  postfix = postfix + opnum + " ";       // If operand pass it to string

                  break;

               case SYM_INTEG:

                  // Checks for consecustive operands (already caught)
                  if(consecNum != "")
                     break;

                  consecNum = consecNum + opnum + " ";   // Adds new consecutive number to tracker
                  postfix = postfix + opnum + " ";       // If operand pass it to string

                  break;

               case SYM_FLOAT:

                  // Checks for consecustive operands (already caught)
                  if(consecNum != "")
                     break;
                  
                  consecNum = consecNum + opnum + " ";   // Adds new consecutive number to tracker
                  postfix = postfix + opnum + " ";       // If operand pass it to string

                  break;

               case SYM_ADD:
                  // Error if consecutive operators
                  if(consecOp != "")
                     break;

                  // If stack is not empty check the precedence and push/pop
                  // Else the stack is empty and you should push to stack.
                  if(operators.empty() == false)
                  {
                     while(precedence(*opnum) <= precedence(operators.top()))
                     {
                        postfix = postfix + operators.top() + " ";
                        operators.pop();
                     }
                  } 

                  operators.push(*opnum);    // Pushes operator onto stack
                  
                  consecOp = consecOp + opnum + " ";     // Adds new consecutive operator to tracker

                  break;

               case SYM_SUB:
                  // Error if consecutive operators
                  if(consecOp != "")
                     break;

                  // If stack is not empty check the precedence and push/pop
                  // Else the stack is empty and you should push to stack.
                  if(operators.empty() == false)
                  {
                     while(precedence(*opnum) <= precedence(operators.top()))
                     {
                        postfix = postfix + operators.top() + " ";
                        operators.pop();
                     }
                  } 

                  operators.push(*opnum);    // Pushes operator onto stack

                  consecOp = consecOp + opnum + " ";  // Adds new consecutive operator to tracker

                  break;

               case SYM_MUL:
                  // Error if consecutive operators
                  if(consecOp != "")
                     break;

                  // If stack is not empty check the precedence and push/pop
                  // Else the stack is empty and you should push to stack.
                  if(operators.empty() == false)
                  {
                     while(precedence(*opnum) <= precedence(operators.top()))
                     {
                        postfix = postfix + operators.top() + " ";
                        operators.pop();
                     }
                  } 

                  operators.push(*opnum);    // Pushes operator onto stack

                  consecOp = consecOp + opnum + " ";  // Adds new consecutive operator to tracker

                  break;

               case SYM_DIV:

                  if(consecOp != "")
                     break;

                  // If stack is not empty check the precedence and push/pop
                  // Else the stack is empty and you should push to stack.
                  if(operators.empty() == false)
                  {
                     while(precedence(*opnum) <= precedence(operators.top()))
                     {
                        postfix = postfix + operators.top() + " ";
                        operators.pop();
                     }
                  } 

                  operators.push(*opnum);    // Pushes operator onto stack

                  consecOp = consecOp + opnum + " ";  // Adds new consecutive operator to tracker

                  break;

               case SYM_OPEN:

                  matchingPar++; // Used to check for errors in case SYM_CLOSE

                  // If the last input was a operand, there is an error
                  if(consecNum != "")
                  { 
                     // If there is aready an error (  edge case ")("  )
                     if(error == true)
                     {
                        consecNum = "";
                        numOfConsecNum = 0;
                        break;
                     }

                     // Sets error to true and prints the error
                     error = true;
                     cout << "Number (: " << consecNum << "(" << endl;
                     consecNum = "";
                     numOfConsecNum = 0;

                     break;
                  }
                  else
                  {
                     // Resets tracker
                     consecOp = "";
                     numOfConsecOp = 0;
                  }

                  operators.push(*opnum);    // Pushes operator onto stack

                  break;

               case SYM_CLOSE:

                  // If there is not a matching '('
                  if(matchingPar == 0)
                  {
                     error = true;
                     cout << "Error: cannot find a matching (." << endl;
                     break;
                  }

                  // If the parentheses are empty or has a operator as the last argument
                  if(consecNum == "")
                  {
                     error = true;
                     cout << "Error: cannot have an opcode or ( before )." << endl;
                     break;
                  }

                  // If stack is not empty check the precedence and push/pop
                  // Else the stack is empty and you should push to stack.
                  if(operators.empty() == false)
                  {
                     while(precedence(*opnum) <= precedence(operators.top()))
                     {
                        // Checks for the opening parentheses to break
                        if(operators.top() == '(')
                        {
                           operators.pop();
                           break;
                        }

                        // Puts the top of the stack into a string and pops it from the stack
                        postfix = postfix + operators.top() + " ";
                        operators.pop();
                     }
                  }
                  
                  matchingPar--;

                  break;

               case SYM_INVAL:
                  // No longer a consecutive operator
                  consecOp = "";
                  numOfConsecOp = 0;

                  // Adds to the consecutive number string
                  consecNum = consecNum + opnum;

                  // Saves the '.' into the temp infix string
                  tempInfix = tempInfix + opnum;

                  break;

               case SYM_NEWLINE: 
                  newLine = true; // Used to check for the end of the expression  
                  break;

               default: break; 
            }   
         }
      }

      // Used to exit the program
      if(retval == SYM_NULL)
            break;

      // Checks if there is an opening parentheses still on the stack
      if(operators.top() == '(')
      {
         error = true;
         cout << "Error: failed conversion. Deck top=(" << endl;
      }

      // Prints the last operator on the stack if there is no error.
      if(error == false)
      {
         while(!(operators.empty()))
         {
         postfix = postfix + operators.top() + " ";
         operators.pop();
         }
      }

      // If the expression has invalid operands
      if(typeError == true && error == false)
      {
         cout << postfix << endl;
         continue;
      }

      // If there was an error print the input else, prints the value of the expression
      if(error == true)
      {
         cout << "Found in input:" << endl;
         cout << tempInfix << '\n' << endl;
         continue;
      }
      else
      {
         string tempChar;  // Used to store each operand

         // Creates a stream of the postfix expression
         stringstream tempStream(postfix);

         // Goes through each operator or operand seperated by a space
         while(tempStream >> tempChar)
         {
            // Checks if the current element is a operand or operator
            if(isdigit(tempChar[0]))
            {
               // If it is a digit, convert to float and store on operand stack
               float tempFloat = stof(tempChar);
               operands.push(tempFloat);
            }
            else
            {
               // Gets the first operand
               float topFloat = operands.top();
               operands.pop();

               /* If there are more operators than operands 
               report error and print current total*/
               if(operands.empty() == true)
               {
                  error = true;
                  cout << "Error operator [" << tempChar << "] has only one operand: " << topFloat << endl;
                  cout << "Found in input:" << endl;
                  cout << tempInfix << endl;
                  cout << endl;
                  break;
               }

               // Gets the second operand
               float nextFloat = operands.top();
               operands.pop();

               // Pushes the current calculation back on the stack.
               operands.push(postfixCalc(topFloat, nextFloat, tempChar));
            }
         }

         // If the postfix evaluation found no errors, print the top of the stack.(answer)
         if(error == false)
            cout << operands.top() << endl;
      }

   } while (retval > SYM_NULL);
}

int precedence(const char & inputChar)
{
   int preced = 0;   // Stores return value

   // Sets a precedence for each value
   switch(inputChar)
   {
      case ')':   preced = 1; break;
      case '(':   preced = 2; break;
      case '+':   preced = 3; break;
      case '-':   preced = 3; break;
      case '*':   preced = 4; break;
      case '/':   preced = 4; break;
      default:break;
   }

   return preced;
}

float postfixCalc(const float & topFloat, const float & nextFloat, const string & tempChar)
{
   float combinedFloat = 0;

   // If both operands are a float, convert to int and preform operation
   // Else do the operation on the floats
   if(roundf(topFloat) == topFloat && roundf(nextFloat) == nextFloat)
   {
      int tempTop = static_cast<int>(topFloat);
      int tempNext = static_cast<int>(nextFloat);

   if(tempChar == "-")
      combinedFloat = tempNext - tempTop;

   if(tempChar == "+")
      combinedFloat = tempNext + tempTop;

   if(tempChar == "*")
      combinedFloat = tempNext * tempTop;

   if(tempChar == "/")
      combinedFloat = tempNext / tempTop;
   }
   else
   {
      if(tempChar == "-")
      combinedFloat = nextFloat - topFloat;

      if(tempChar == "+")
         combinedFloat = nextFloat + topFloat;

      if(tempChar == "*")
         combinedFloat = nextFloat * topFloat;

      if(tempChar == "/")
         combinedFloat = nextFloat / topFloat;
   }

   return combinedFloat;   
}
