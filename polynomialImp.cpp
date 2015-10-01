#include "polynomial.h"

////////////////////////////////////////////////
//             Node Constructors              //
////////////////////////////////////////////////

Node::Node()
{
	coefficient = 0;
	degree = 0;
	next = NULL;
}


Node::Node(float coeff, int deg)
{
	coefficient = coeff;
	degree = deg;
    next = NULL;
}


Node::Node(float coeff, int deg, Node* nodey)
{
    coefficient = coeff;
    degree = deg;
    next = nodey;
}


Node::Node(Node* nodey)
{
    coefficient = nodey->coefficient;
    degree = nodey->degree;
    next = NULL;
}
////////////////////////////////////////////////
// Polynomial Constructors                    //
////////////////////////////////////////////////
Polynomial::Polynomial()
{
	head = NULL;
}


///////////////
//Takes Node pointer and makes 
Polynomial::Polynomial(Node* h)
{
	head = h;
}


////////////////
//Copy constructor
Polynomial::Polynomial(const Polynomial &other)
{
    if (other.head == NULL)
    {
        head = NULL;
    }
    else
    {
        Node* current = other.head;
        head = NULL;
        while(current != NULL)
        {
             push(current->coefficient, current->degree);
             current = current->next;
        }
    } //endifs
}

///////////////
//destructor
Polynomial::~Polynomial()
{
    clear();
}


////////////////////////////////////////////////
// Polynomial Member Functions                //
////////////////////////////////////////////////


void Polynomial::push(float coeff, int deg)
{
	Node* current;
	Node* temp;
	Node* new_node;

    //number would be zero anyway
    if (coeff == 0 && head == NULL)
    {
        deg = 0;
    }

	if (head == NULL)
	{
        current = new Node(coeff, deg);
		head = current;
		return;
	}

    current = head;
    temp = current;

	while(current != NULL)
	{
	    //if smaller than current degree
	    //move down the list
		if (current->degree > deg)
        {
            //add behind because hit end of list
            if (current->next == NULL)
            {
                new_node = new Node(coeff, deg);
                current->next = new_node;
                return;
            }
            //move down list, have temp follow one behind
            else
            {
                //cerr << current->degree << endl;
                temp = current; // keep temp one behind
                current = current->next;
                continue;
            }
        }
        else if (current->degree < deg)
        {
            //gets changed to current if not in right spot
            if (head == current)
            {
                //current has nothing before, so temp != anything
                new_node = new Node(coeff, deg, current);
                head = new_node;
                return;
            }

            new_node = new Node(coeff, deg, current);
            temp->next = new_node;
            return;
        }
        else if (current->degree == deg)
        {
            current->coefficient = current->coefficient + coeff;
            return;
        }
        else
        {
            cerr << "This shouldn't happen." << endl;
        }
	}
}



//////////////
//deallocates memory in Polynomial
//used in destructor
void Polynomial::clear()
{
    Node* current = head;
    Node* temp = NULL;
    
    while(current != NULL)
    {
        temp = current->next;
        delete current;
        current = head = temp;
    }
}


//////////////////
//prints out polynomial, + 0
//may happen if coeff = 0
void Polynomial::print()
{
	Node* current = head;
    if (head == NULL)
    {
        cout << "ERROR: No Polynomial to print()" << endl;
        return;
    }

	while (current != NULL)
	{
	    //degree zero should be at the end
	    if (current->degree == 0)
        {
            cout << current->coefficient << endl;
            break;
        }
		//don't want a + at the end of the polynomial
		if (current->next == NULL)
		{
		    if (current->degree == 1)
            {
                cout << current->coefficient << "x" << endl;
                break;
            }

			cout << current->coefficient << "x^" << current->degree << endl;
			break;
		}
        if (current->degree == 1)
        {
            cout << current->coefficient << "x" << " + ";
            current = current->next;
        }
        else
        {
            cout << current->coefficient << "x^" << current->degree << " + ";
            current = current->next;
        }
	}
}

////////////////////
//multiply by itself deg times
Polynomial Polynomial::exponent(int deg)
{
    
    Node* temp = head;
    Polynomial temp_poly = Polynomial();
    while(temp != NULL)
    {
        temp_poly.push(temp->coefficient, temp->degree);
        temp = temp->next;
    }
    
    Polynomial poly = Polynomial();
    
    if (deg == 0)
    {
        Node* one = new Node(1,0);
        poly = Polynomial(one);
        return poly;
    }
    
    for(int i = 0; i < deg; i++)
    {
        if(i == 0)
        {
            //create a poly equal to current Poly
            //so not overwrite current one
            poly = Polynomial(*this);
        }
        else
        {
            //poly grows, temp_poly = *this constant
            poly = poly * temp_poly;
        }
    }
    return poly;
    
}


////////////////
//Evaluates polynomials at where x = double x
double Polynomial::evaluate(double x)
{
    if (head == NULL)
    {
        cout << "ERROR: polynomial is empty, returning 0..." << endl;
        return 0;
    }
    
    Node* current = head;
    double eval = 0; //answer
    float curr_coeff = 0; //coeff of current node
    int curr_deg = 0; //deg of current node
    float curr_term = 0; //current term with deg and coeff evaluated
    
    while(current != NULL)
    {
        curr_coeff = current->coefficient;
        curr_deg = current->degree;

        for (int i = 0; i < curr_deg; i++)
        {
            //exactly like exponent function
            if (i == 0)
            {
                //x is constant
                //multiplys by itself cur_deg times
                curr_term = x;
            }
            else
            {
                curr_term = curr_term * x;
            }
        }
        //after exponent is evaluated, evaluate * coeff...
        curr_term = curr_term * curr_coeff;
        eval = eval + curr_term; //eval is final term
        current = current->next; //move to next node
    }
    return eval; // return answer
}



//dividing this by parameter
Polynomial Polynomial::modulus(Polynomial divisor)
{
    Polynomial numerator = *this;
    Polynomial result = Polynomial(); //answer changes once is smaller
    Polynomial quotient = Polynomial(); //thing on top
    Polynomial sub = Polynomial();
    
    float temp_coeff = 0;
    int temp_deg = 0;
    
    //makes sure divisor is smaller
    if (head->degree >= divisor.head->degree)
    {
        while(numerator.head->degree >= divisor.head->degree)
        {
            
            //cout << numerator.head->degree << " >= " << node_divisor->degree << endl;
            // 1) *this coeff / divisor coeff = quotient coeff
            temp_coeff = numerator.head->coefficient / divisor.head->coefficient;
            
            // 2) *this degree - divisor degree = quotient degree
            temp_deg = numerator.head->degree - divisor.head->degree;
            quotient.push(temp_coeff, temp_deg);
        
            // 3) quotient * divisor = sub
            sub = quotient * divisor;
            
            // 4) numerator - sub = result
            result = numerator - sub;
            numerator = result; //assignment operator is weird
            //clear quotient so can always just use head...
            quotient.clear();

        }
    }
    else
    {
        return result;
    }
    return result;
}



////////////////////////////////////////////////
// Polynomial Overloaded Operators            //
////////////////////////////////////////////////


//Addition Operator
Polynomial Polynomial::operator+(Polynomial& poly2)
{
	//Gets polynomial before operator
	Node* poly1_ptr = head;
	Node* poly2_ptr = poly2.head;
    //new polynomial
	Polynomial* sum_poly = new Polynomial();

	//0+0=0
	if (poly1_ptr == NULL && poly2_ptr == NULL)
	{
        return *sum_poly;
	}
	// Adding this + 0 == this
	else if (poly1_ptr != NULL && poly2_ptr == NULL)
	{
		return *this;
	}
	// Adding 0 + poly2 == poly2
	else if (poly1_ptr == NULL && poly2_ptr != NULL)
	{
        *sum_poly = poly2;
        return *sum_poly;
	}

	while(poly1_ptr != NULL || poly2_ptr != NULL)
	{
	    if (poly1_ptr == NULL)
		{
			sum_poly->push(poly2_ptr->coefficient, poly2_ptr->degree);
			poly2_ptr = poly2_ptr->next;
		}
		else if (poly2_ptr == NULL)
		{

			//just add poly1_ptr to poly list
			sum_poly->push(poly1_ptr->coefficient, poly1_ptr->degree);
			poly1_ptr = poly1_ptr->next;
		}
		else if (poly1_ptr->degree > poly2_ptr->degree)
        {
            sum_poly->push(poly1_ptr->coefficient, poly1_ptr->degree);
			poly1_ptr = poly1_ptr->next;
        }
        else if (poly1_ptr->degree < poly2_ptr->degree)
        {
            sum_poly->push(poly2_ptr->coefficient, poly2_ptr->degree);
			poly2_ptr = poly2_ptr->next;
        }
		else if (poly1_ptr->degree == poly2_ptr->degree)
		{
			sum_poly->push(poly1_ptr->coefficient + poly2_ptr->coefficient, poly1_ptr->degree);
			poly1_ptr = poly1_ptr->next;
			poly2_ptr = poly2_ptr->next;
		}

	}
    return *sum_poly;
}


//Addition operator
Polynomial Polynomial::operator-(Polynomial& poly2)
{

	Node* poly1_ptr = this->head;
	Node* poly2_ptr = poly2.head;
    Node* zero = new Node(0,0);
	Polynomial* diff_poly = new Polynomial();
	Node* current;


	if (poly1_ptr == NULL && poly2_ptr == NULL)
	{
        *diff_poly = Polynomial(zero);
		return *diff_poly;
	}
	// Subtracting this - 0 == this
	else if (poly1_ptr != NULL && poly2_ptr == NULL)
	{
		return *this;
	}
	// Adding 0 - poly2 == - poly2
	else if (poly1_ptr == NULL && poly2_ptr != NULL)
	{
		current = new Node();
		diff_poly->head = current;
		//need to make everything negative
		while (poly2_ptr != NULL)
		{
			diff_poly->push(0 - poly2_ptr->coefficient, poly2_ptr->degree);
			poly2_ptr = poly2_ptr->next;
		}
        
		return *diff_poly;
	}

	current = new Node();
	diff_poly->head = current;

	while(poly1_ptr != NULL || poly2_ptr != NULL)
	{

        if (poly1_ptr == NULL)
		{
			diff_poly->push(0 - poly2_ptr->coefficient, poly2_ptr->degree);
			poly2_ptr = poly2_ptr->next;
		}
		else if (poly2_ptr == NULL)
		{
			//just add poly1_ptr to poly list
			diff_poly->push(poly1_ptr->coefficient, poly1_ptr->degree);
			poly1_ptr = poly1_ptr->next;
		}
		else if (poly1_ptr->degree == poly2_ptr->degree)
		{
			diff_poly->push(poly1_ptr->coefficient - poly2_ptr->coefficient, poly1_ptr->degree);
			poly1_ptr = poly1_ptr->next;
			poly2_ptr = poly2_ptr->next;
		}
		else if (poly1_ptr->degree > poly2_ptr->degree)
		{
			//just add poly1_ptr to poly list
			diff_poly->push(poly1_ptr->coefficient, poly1_ptr->degree);
			poly1_ptr = poly1_ptr->next;
		}
		else
		{
			//poly1_ptr < poly2_ptr degree, add poly2_ptr to poly list
			diff_poly->push(0 - poly2_ptr->coefficient, poly2_ptr->degree);
			poly2_ptr = poly2_ptr->next;
		}
	}
	return *diff_poly;
}

//Multiplication operator
Polynomial Polynomial::operator*(Polynomial& p2)
{
	Node* poly1 = this->head;
	Node* poly2 = p2.head;
	Polynomial* temp = new Polynomial();

    if (poly1 == NULL && poly2 == NULL)
    {
        return *temp;
    }
    else if (poly1 != NULL && poly2 == NULL)
    {
        return *this;
    }
    else if (poly1 == NULL && poly2 != NULL)
    {
        return p2;
    }
    else
    {
        float coeff = 0;
        int deg = 0;
        while(poly1 != NULL)
        {
            while(poly2 != NULL)
            {
                coeff = poly1->coefficient * poly2->coefficient;
                deg = poly1->degree + poly2->degree;
                temp->push(coeff, deg);
                poly2 = poly2->next;
            }
            poly2 = p2.head;
            poly1 = poly1->next;
        }
    }

	return *temp;
}


const Polynomial& Polynomial::operator=(const Polynomial& p2)
{
    if (&p2 == this)
    {
        cerr << "ERROR: Self-assignment! Returning itself..." << endl;
        return p2;
    }
    
    if(head != NULL)
    {
        clear();
    }
    
    Node* current = p2.head;
    while(current != NULL)
    {
        push(current->coefficient, current->degree);
        current = current->next;
    }
    
    return *this;
}






