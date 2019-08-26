//Zareen Subah
//zxs170630

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "Node.h"
#include "List.h"

using namespace std;

//function prototypes below
int getListSize(Node*);
Node* mergeNodes(Node *&, Node *&);
void mergeSort(Node *&);
void mergeSameExponent(List);
long double expressionSolution (List, double);


int main()
{

    char sign ='+'; //define the variable to hold the operator + or -
    double number=0, coefficient=1.0; //define the variables as doubles
    int exponent=0; //define the variable as a int
    ifstream file("poly.txt"); //open the input file
    ofstream output("answers.txt"); //open the output file


    while(file.peek()!= EOF) //while it is not the end of the file
    {
        List expression; //define the variable
        file.ignore(2); //ignore the next 2 characters
        file>>number; //get the number
        file.ignore(3); //ignore the next 3 characters
        while(file.peek()!='f' && file.peek()!=EOF) //while the character is not f and it is not the end of the file
        {
            file>>ws; //trim whitespace
            if(file.peek() == '+' || file.peek()== '-') //if the character is a plus or a minus
            {
                file>>sign; //store it as the sign/operator
            }
            file >> ws;//trim whitespace

            if(isdigit(file.peek())) //if the character is a digit
            {
                file >> coefficient; //store it as the coefficient

                if(sign=='-')
                    coefficient = coefficient * -1; //if the operator is negative store the coefficient times -1
            }
            if(file.peek()=='x') //if the character is x
            {
                file.ignore(1); //ignore next character
                if(file.peek()=='^')
                {
                    file.ignore(1); //if the character is a carat ignore that
                    file>>exponent; //and store the next number as the exponent
                }
                else
                {
                    exponent = 1; //else store the exponent as 1
                }
            }

            expression.append(coefficient, exponent); //call the append function
            sign='+'; //set the sign to +
            coefficient=1.0; //set the coefficient to 1
            exponent=0; //set the exponent to 0
            file>>ws; //trim whitespace or newline
        }

        mergeSort(expression.getHead()); //call the function
        mergeSameExponent(expression); //call the function
        output<<"f("<<number<<") ="; //write f followed by the value at which it will be evaluated in brackets
        expression.printList(expression.getHead(), output); //call the print function

        //set the precision to 3 decimal places and use default float so that the coefficients don't show decimals
        output<<" = "<<fixed<<setprecision(3)<<expressionSolution(expression, number)<<setprecision(6)<<defaultfloat;
        if(file.peek()!= EOF)
            output<<endl; //avoid newline at the end of the the file
    }
}


//get the size of the linked list
int getListSize(Node *head)
{
    int i=0;
    while(head) //while there is a pointer to a node, the linked list is not ending
    {
        i++; //increment the variable
        head=head->getNext(); //move to the next node
    }
    return i; //return the size of the linked list
}

//this function sorts and merges two halves of the pointer
Node* mergeNodes(Node *&leftHalf, Node *&rightHalf)
{
    Node* tempHead; //define a pointer to the node structure

    //Base case: return the other half if  one of them is NULL
    if(!leftHalf)
        return rightHalf;
    else if(!rightHalf)
        return leftHalf;



    if(leftHalf->getExponent() > rightHalf->getExponent()) //check if the left half has a smaller value than the right half
    {
        tempHead = leftHalf; //else if it is Roman numeral
        tempHead->setNext(mergeNodes(leftHalf->getNext(), rightHalf)); //recall the function to find the next Node
    }
    else //else if the right half has a smaller value than the left half
    {
        tempHead = rightHalf; //assign the tempHead to the Node has smaller value
        tempHead->setNext(mergeNodes(leftHalf, rightHalf->getNext())); //recall the function to find the next Node
    }

    return tempHead; //return the smaller value
}
//this function divides the linked list recursively into two half
void mergeSort(Node *&head)
{
    if(head->getNext()) //check the condition if this is the last Node, do nothing
    {
        Node* leftHalf;
        Node* rightHalf = head; //assign head to head 2. Head 2 will point to second half of the linked list
        int listSize = getListSize(head);
        for(int i=0; i<listSize/2; i++) //use for loop to increment the pointer 2 to the mid point in linked list
        {
            leftHalf = rightHalf; //assign leftHalf to any Node rightHalf point to,
            rightHalf = rightHalf->getNext(); //in order to put NULL terminate for the first half of the linked list
        }
        leftHalf->setNext(nullptr); //terminate first half of the linked list
        leftHalf = head; //reposition leftHalf to the beginning of linked list, also the first Node of the first half
        mergeSort(leftHalf); //recursive call
        mergeSort(rightHalf); //recursive call
        head = mergeNodes(leftHalf,rightHalf); //assign the value returned by the function to head
    }
}

//this function merges the terms if they have the same power
void mergeSameExponent(List expres)
{
    Node *head = expres.getHead();
    while(head->getNext()) //while there is a pointer to a node, the linked list is not ending
    {
        if(head->getExponent() == head->getNext()->getExponent()) //if the exponent and next exponent are the same
        {
            head->setCoefficient(head->getCoefficient()+head->getNext()->getCoefficient()); //add their coefficients
            Node *dNode = head->getNext(); //define a new pointer to Node class and initialize it with the next node
            head = head->getNext()->getNext(); //set head to the node after the next node
            expres.deleteNode(expres.getHead(), dNode); //delete the next node
        }
        else
        {
            head=head->getNext(); //else if they are not same, then move to the next node
        }

        if(!head) //if the list is empty
            return; //return nothing
    }
}


//this function calculates the solution
long double expressionSolution (List expres, double number)
{
    Node *head = expres.getHead(); //define a pointer to the Node class
    long double solution=0; //define and set the variable to 0
    while(head) //while there is a list
    {
        //multiply the coefficient with the number raised to the power of the exponent
        solution += (head->getCoefficient() * pow(number, head->getExponent()));
        head=head->getNext(); //move on to the next node
    }
  return solution; //return the solution
}
