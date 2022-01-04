#include <vector>
#include "stack.h"

using namespace cop4530;

// Constructor
template <typename T>
Stack<T>::Stack(int initSize): theSize{initSize}, totalCapacity{initSize}
{}

// Destructor
template <typename T>
Stack<T>::~Stack()
{   vec.clear();}

// Copy constructor
template <typename T>
Stack<T>::Stack(const Stack<T>& rhs): 
theSize{rhs.theSize}, totalCapacity{rhs.totalCapacity}, vec{rhs.vec}
{}

// Move constructor
template <typename T>
Stack<T>::Stack(Stack<T> && rhs):
theSize{rhs.theSize}, totalCapacity{rhs.totalCapacity}, vec{rhs.vec}
{
    // Null everything out for the move function
    rhs.theSize = 0;
    rhs.totalCapacity = 0;

    rhs.vec.clear();
}

// Copy assignment operator
template <typename T>
Stack<T> & Stack<T>::operator=(const Stack<T> & rhs)
{
    Stack tempStack = rhs;          // Makes a copy of rhs
    std::swap(*this, tempStack);    // Swaps the copy with the current

    return *this;
}

// Move assignment operator
template <typename T>
Stack<T> & Stack<T>::operator=(Stack<T> && rhs)
{
    // Swaps the member data
    std::swap(theSize, rhs.theSize);
    std::swap(totalCapacity, rhs.totalCapacity);

    std::swap(vec, rhs.vec);

    return *this;
}

// Checks if the stack is empty
template <typename T>
bool Stack<T>::empty() const
{   return size() == 0; }

// Deletes every element from the stack
template <typename T>
void Stack<T>::clear()
{
    // pops everything off the stack until its empty
    while(!empty())
        pop();
}

// Returns the number of ele-ments in the stack
template <typename T>
int Stack<T>::size() const
{   return theSize; }

// Pushes 'x' onto the stack
template <typename T>
void Stack<T>::push(const T& x)
{   
    // Pushes x onto the stack.
    vec.push_back(x); 
    ++theSize;
    ++totalCapacity;
}

// Moves 'x' onto the stack
template <typename T>
void Stack<T>::push(T && x)
{
    // Moves x to the stack.
    auto newX = std::move(x);
    vec.push_back(newX);
    ++theSize;
    ++totalCapacity;
}

// Pops the last element from the stack
template <typename T>
void Stack<T>::pop()
{   vec.pop_back();
    --theSize;
}

// Returns a reference to the element on the top of the stack
template <typename T>
T& Stack<T>::top()
{   return vec[theSize - 1];  }

// Returns the element on the top of the stack
template <typename T>
const T& Stack<T>::top() const
{   return vec[theSize - 1];   }

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const
{
    // Goes through each element and sends it to the ostream
    for(int i = 0; i < theSize; i++)
        os << vec[i] << ofc;
}

// Ostream for Stack objects.
template <typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& a)
{
    // Sends each element followed by a space to ostream
    a.print(os);

    return os;
}

// Checks if the two stacks are equal
template <typename T>
bool operator== (const Stack<T>& lhs, const Stack <T>& rhs)
{
    // If the sizes are different they are not equal
    if(lhs.size() != rhs.size())
        return false;
    
    // Temporary stacks to push/pop from
    Stack<T> tempLHS = lhs;
    Stack<T> tempRHS = rhs;
    
    while(tempLHS.empty() != true)
    {
        if(tempLHS.top() != tempRHS.top())
            return false;
        
        tempLHS.pop();
        tempRHS.pop();
    }
    
    return true;
}

template <typename T>
bool operator!= (const Stack<T>& lhs, const Stack <T>& rhs)
{
    // If the sizes are different they are not equal
    if (lhs.size() != rhs.size())
        return true;
    
    // Temporary stacks to push/pop from
    Stack<T> tempLHS = lhs;
    Stack<T> tempRHS = rhs;

    // Checks if each element is not equal to its corrosponding element.
    while(tempLHS.empty() != true)
    {
        if(tempLHS.top() != tempRHS.top())
            return true;
        
        tempLHS.pop();
        tempRHS.pop();
    }

    return false;
}

// Checks if the lhs is <= the rhs. (in size and elements)
template <typename T>
bool operator<= (const Stack<T>& lhs, const Stack <T>& rhs)
{   
    // Checks if the lhs or rhs has more elements to determing '<' or '>'
    if(lhs.size() > rhs.size())
        return false;

    // Temporary stacks to push/pop from
    Stack<T> tempLHS = lhs;
    Stack<T> tempRHS = rhs;

    // Checks if each element is not equal to its corrosponding element.
    while(tempLHS.empty() != true)
    {
        if(tempLHS.top() > tempRHS.top())
            return false;
        
        tempLHS.pop();
        tempRHS.pop();
    }
    
    return true;
}
