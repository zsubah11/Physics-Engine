//Zareen Subah
//zxs170630


#include "Node.h"


//default constructor that does nothing
Node::Node()
{

}

//overloaded constructor
Node::Node(double coeff, int exp)
{
    this->coefficient = coeff; //sets coefficient to coeff
    this->exponent = exp; //sets exponent to exp
}

//mutators
void Node::setCoefficient(double coeff)
{
    this->coefficient = coeff; //set coefficient to coeff
}

void Node::setExponent(int exp)
{
    this->exponent = exp; //sets exponent to exp
}

void Node::setNext(Node* nxt)
{
    this->next = nxt; //sets next to nxt
}


//accessors
double Node::getCoefficient()
{
    return this->coefficient; //returns the coefficient
}

int Node::getExponent()
{
    return this->exponent; //returns the exponent
}

Node *& Node::getNext()
{
    return this->next; //returns next
}

//destructor that does nothing
Node::~Node()
{

}
