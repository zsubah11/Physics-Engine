//Zareen Subah
//zxs170630

#include "List.h" //include the headers for list
#include "Node.h" //include the header for Node
#include <cmath>


//default constructor
List::List()
{
    this->head = NULL; //set head to point to null
}

//overloaded constructor
List::List(Node *aHead)
{
        this->head = aHead; //sets head to the pointer
}

Node *& List::getHead()
{
    return this->head; //returns the head
}

//destructor
List::~List()
{
    delete this->head; //deletes the head
}

//this function adds node
void List::append(double coeff, int exp)
{

    Node* newNode = new Node(); //define a new node object dynamically and create a pointer to point to the Node class
    newNode->setCoefficient(coeff); //dereferences newNode and stores the value in coeff
    newNode->setExponent(exp); //dereferences newNode and stores the value in exp
    newNode->setNext(NULL); //dereferences newNode and stores null in next pointer

    if(!head) //if the list is empty
    {
        head = newNode; //assign new node to head
    }
    else //else if the list is not empty
    {
        newNode->setNext(head); //make new node point to the next node
        head = newNode; //set head to be the new node
    }
}

//this function prints the linked list
void List::printList(Node *curr, std::ofstream & output)
{
    if(!curr) //if there is no list then do nothing
        return;
    if(curr->getCoefficient()!= 1 ) //if the co efficient is not 1
        output<<' '<< fabs(curr->getCoefficient()); //then write the absolute value of the coefficient

    else if(curr->getCoefficient()==1 && curr->getExponent()== 0) //else if the coefficient is 1 and the exponent is zero
        output<<' '<< fabs(curr->getCoefficient()); //write the coefficient and store in the node
    else
        output<<' '; //else write a space to the file

    if(curr->getExponent()>1 && curr->getExponent() !=0) //if the coefficient is greater than 1
        output<<'x'<<'^'<<curr->getExponent(); //output x followed by a carat and the exponent number
    if(curr->getExponent()< 1 && curr->getExponent() !=0) //if the coefficient is less than 1
        output<<'x'<<'^'<<curr->getExponent(); //output x followed by a carat and the exponent number
    if(curr->getExponent()==1) //if the coefficient is 1, just output x
        output<<'x';


    if(curr->getNext()) //if there is a next node
    {
        if(curr->getNext()->getCoefficient()>=0) //if the coefficient is greater than 0
        {
            output<<" +"; //output a + operator
        }
        else
            output<<" -"; //else output a minus operator
    }

    printList(curr->getNext(), output); //print out the list recursively
}

//this function deletes the node
void List::deleteNode(Node *curr, Node *dNode)
{
    if(!curr) //if there is no list then do nothing
        return;

    if (curr->getNext() == dNode) //if the node is the node you need to delete
    {
        curr->setNext(dNode->getNext()); //then delete that node
        return;
    }
    else
        deleteNode(curr->getNext(), dNode); //else call the function recursively
}
