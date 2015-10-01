//Driver program

#include <iostream>
#include <iomanip>
#include "polynomial.h"

using namespace std;

char get_menu();
Polynomial input_polys();
float input_coeff();
int input_deg();
Polynomial addition();
Polynomial subtraction();
Polynomial multiplication();
Polynomial modulo();
Polynomial exponent();
double evaluate();

int main()
{

    Polynomial poly1 = Polynomial();
    Polynomial poly2 = Polynomial();
    Polynomial result = Polynomial();
    bool done = 0;
    char selection = '0';
    double eval = 0;
    
    cout << "Polynomial Data Structure" << endl << endl;
    while(!done)
    {
        selection = get_menu();
        
        switch(selection)
        {
            case 'a':
            case 'A':
                //add polynomial function
                result = addition();
                break;
            case 's':
            case 'S':
                //subtract polynomials
                result = subtraction();
                break;
            case 'm':
            case 'M':
                result = multiplication();
                //multiply polynomials
                break;
            case 'd':
            case 'D':
                result = modulo();
                //modulo polynomials
                break;
            case 'e':
            case 'E':
                result = exponent();
                //exponent(int)
                break;
            case 'v':
            case 'V':
                eval = evaluate();
                //evalute a specific polynomial
                break;
            case 'x':
            case 'X':
                done = 1;
                break;
            default:
                cout << "Invalid Selection: Select an option from the menu." << endl;
        }
    }

    return 0;
}


char get_menu()
{
    char selection = '0';
    int w = 20;
    cout << left;
    cout << setw(w) << "Addition" << setw(5) << "(a/A)" << endl;
    cout << setw(w) << "Subtraction" << setw(5) << "(s/S)" << endl;
    cout << setw(w) << "Multiplication" << setw(5) << "(m/M)" << endl;
    cout << setw(w) << "Modulus" << setw(5) << "(d/D)" << endl;
    cout << setw(w) << "Exponent" << setw(5) << "(e/E)" << endl;
    cout << setw(w) << "Evaluate" << setw(5) << "(v/V)" << endl;
    cout << setw(w) << "Exit " << setw(5) << "(x/X)" << endl;
    cout << "Input Selection: ";
    cin >> selection;
    cout << endl;
    
    return selection;
}

float input_coeff()
{
    float coefficient = 0;
    cout << "Enter Polynomial Coefficient (x^coeff): ";
    cin >> coefficient;
    return coefficient;
}


int input_deg()
{
    int degree = 0;
    cout << "Enter Polynomial Degree (x^deg): ";
    cin >> degree;
    return degree;
}


Polynomial input_polys()
{
    bool done = 0;
    char selection = 'y';
    Polynomial poly = Polynomial();
    
    while(!done)
    {
        poly.push(input_coeff(), input_deg());
        cout << "Polynomial: ";
        poly.print();
        
        cout << "Enter another polynomial term for the "
             << "Polynomial? (y/n): ";
        cin >> selection;
        cout << endl;
        if (selection == 'n' || selection == 'N')
        {
            done = 1;
        }
    }
    return poly;
}

Polynomial addition()
{
    Polynomial poly1;
    Polynomial poly2;
    Polynomial result = Polynomial();
    
    cout << "POLYNOMIAL 1 INPUT" << endl;
    poly1 = input_polys();
    cout << endl;
    cout << "POLYNOMIAL 2 INPUT" << endl;
    poly2 = input_polys();
    
    cout << endl << "ADDITION" << endl;
    poly1.print();
    poly2.print();
    cout << "-------------------------" << endl;
    result = poly1 + poly2;
    result.print();
    
    return result;
}

Polynomial subtraction()
{
    Polynomial poly1;
    Polynomial poly2;
    Polynomial result = Polynomial();
    
    cout << "POLYNOMIAL 1 INPUT" << endl;
    poly1 = input_polys();
    cout << endl;
    cout << "POLYNOMIAL 2 INPUT" << endl;
    poly2 = input_polys();
    
    cout << endl << "SUBTRACTION" << endl;
    poly1.print();
    poly2.print();
    cout << "-------------------------" << endl;
    result = poly1 - poly2;
    result.print();
    
    return result;
}

Polynomial multiplication()
{
    Polynomial poly1;
    Polynomial poly2;
    Polynomial result = Polynomial();
    
    cout << "POLYNOMIAL 1 INPUT" << endl;
    poly1 = input_polys();
    cout << endl;
    cout << "POLYNOMIAL 2 INPUT" << endl;
    poly2 = input_polys();
    
    cout << endl << "MULTIPLICATION" << endl;
    poly1.print();
    poly2.print();
    cout << "-------------------------" << endl;
    result = poly1 * poly2;
    result.print();
    
    return result;
}

Polynomial modulo()
{
    Polynomial poly1;
    Polynomial poly2;
    Polynomial result = Polynomial();

    cout << "POLYNOMIAL 1 INPUT" << endl;
    poly1 = input_polys();
    cout << endl;
    cout << "POLYNOMIAL 2 INPUT" << endl;
    poly2 = input_polys();
    
    cout << endl << "MODULO" << endl;
    poly1.print();
    poly2.print();
    cout << "-------------------------" << endl;
    result = poly1.modulus(poly2);
    result.print();
    
    return result;
}
    
Polynomial exponent()
{
    Polynomial poly1;
    Polynomial result = Polynomial();
    int power = 0;
    
    cout << "POLYNOMIAL INPUT" << endl;
    poly1 = input_polys();
    cout << endl;
    
    cout << "Input exponent: ";
    cin >> power;
    
    poly1.print();
    cout << "-------------------------" << endl;
    result = poly1.exponent(power);
    result.print();
    
    return result;
}


double evaluate()
{
    Polynomial poly1;
    Polynomial result = Polynomial();
    double x;
    cout << "POLYNOMIAL INPUT" << endl;
    poly1 = input_polys();
  
    cout << "Input X to evaulate: ";
    cin >> x;
    cout << endl << "f(x= " << x << ")";
    poly1.print();
    cout << "-------------------------" << endl;
    x = poly1.evaluate(x);
    cout << x << endl;
    return x;
}






