#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>

namespace cop4530 {
    template <typename T>
    class Stack {
        public:
            // Zero argument constructor
            explicit Stack(int initSize = 0);

            ~Stack ();                                      // Destructor
            Stack (const Stack<T>& rhs);                    // Copy Constructor
            Stack(Stack<T> && rhs);                         // Move Constructor
            Stack<T>& operator= (const Stack <T>& rhs);     // Coppy assignment operator
            Stack<T> & operator=(Stack<T> && rhs);          // Move assignment operator

            bool empty() const;         // Returns true if the stack contains no elements
            void clear();               // Deletes every element from the stack 
            int size() const;           // Returns the number of elements in the stack

            void push(const T& x);      // Adds "x" onto the stack (copy version)
            void push(T && x);          // Adds "x" onto the stack (move version)
            void pop();                 // Removes the most recently added element from the stack
            T& top();                   // Returns the reference to the most recently added element
            const T& top() const;       // Returns the most recently added element of the stack

            // Prints elements of the stack to the ostream "os"
            void print(std::ostream& os, char ofc = ' ') const;

        private:
            int theSize;                // Number of elements
            int totalCapacity;          // Total capacity
            std::vector<T> vec;         // A vector of type 'T' elements
    };

    // Prints the stack
    template <typename T>
        std::ostream& operator<< (std::ostream& os, const Stack<T>& a);

    // Returns true if the two stacks have the same elements in the same order.
    template <typename T>
        bool operator== (const Stack<T>& lhs, const Stack <T>& rhs );

    /* Returns true if the two stacks are not in the 
    same order and/or do not have the same elements*/
    template <typename T>
        bool operator!= (const Stack<T>& lhs, const Stack <T>& rhs);

    // Returns true if every element in the stack 'a' is less than or equal to 'b'
    template <typename T>
        bool operator<= (const Stack<T>& lhs, const Stack <T>& rhs);

    #include "stack.hpp"

}

#endif
    