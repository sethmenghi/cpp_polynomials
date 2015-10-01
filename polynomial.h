#ifndef COSC_POLYNOMIALS_H
#define COSC_POLYNOMIALS_H

#include <iostream>

/////////
/////////
/////////

using namespace std;


class Node
{
    public:
        Node();
        Node(float, int);
        Node(float, int, Node*);
        Node(Node*); //copy constructor w/o shallow copy

        float coefficient;
        int degree;
        Node* next;
};


class Polynomial
{
	public:
		//Constructors
		Polynomial(); //Intialize to 0
		//Read input to make Polynomial, defaults next to NULL
		Polynomial(Node*);
		Polynomial(float, int);
        Polynomial(const Polynomial &other); //copy constructor
        ~Polynomial();

    
        //Member functions
		void print(); //Print the polynomial
		double evaluate(double); // ????
		Polynomial exponent(int); //Multiply by itself n times
		Polynomial modulus(Polynomial); //Get Remainder
		void push(float, int);
        void clear();

		//Operators (CREATE NEW POLY OR REPLACE OLD ONES?)'
		Polynomial operator+(Polynomial&); // adds two polynomials
		Polynomial operator-(Polynomial&);
		Polynomial operator*(Polynomial&);
        const Polynomial& operator=(const Polynomial&);
		//Values
		Node* head;
};

#endif
