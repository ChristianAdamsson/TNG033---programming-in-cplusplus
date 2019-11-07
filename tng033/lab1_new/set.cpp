
#include "set.h"
#include <algorithm>
//Default constructor
Set::Set ()
{
    head = new Node(0,nullptr);   //head pekar p� en dummy node
}
//Constructor for creating a set from an int
Set::Set(int v)
{
    Node *newNode = new Node(v, nullptr); // ny node mead v�rdet v, pekar p� null pointer
    head = new Node(0, newNode); // dummy node som pekar p� f�rsta noden
}

//Constructor creating a set
//from n integers in a non-sorted array a
Set::Set (int a[], int n)
{
    sort(a,a+n, greater<int>()); // sorterar arrayen
    head = new Node(0, nullptr); // head pekar p� dummy node
    for (int i = 0; i < n; ++i)  // n = storlek p� array
    {
        head->next=new Node(a[i],head->next); // ny node skapas med v�rdet a[i]
    }
}

//copy constructor
Set::Set (const Set &source)
{
    head = new Node (0,nullptr); // temp pekar p� null pointer
    Node *p2 = head; // p2 pekar p� temp
    for (Node *p1 = source.head->next; p1 != nullptr; p1= p1->next) // s� l�nge p1 inte pekar p� null pointer, g� till n�sta node
    {
        Node *newNode = new Node(p1->value,nullptr); // newNode, en kopia
        // kopplar ihop listorna
        p2->next = newNode;
        p2 =newNode;
    }
}

//Destructor: deallocate all nodes
Set::~Set ()
{
    Node *node = head;
    while (node)
    {
        Node *temp = node;
        node = node->next;
        delete temp;
    }
}

//Test if set is empty
bool Set::empty () const
{
    return(!head->next);
}

//Return number of elements in the set
int Set::cardinality() const
{
    int counter = 0;
    Node *p1 = head;

    while(p1 != nullptr && p1->next != nullptr)  // medans man inte �r i slutet av ett set
    {
        p1 = p1->next; // flytta till n�sta node
        counter ++; // addera till counter
    }
    return counter;
}

//Test if x is an element of the set
bool Set::member (int x) const
{
    Node* temp = head->next;

    while (temp) // medans v�rdet i en Node inte �r lika med x
    {
        if (temp->value == x)
        {
            return true;
        }
        temp = temp->next; // g� till n�sta node
    }
    return false;

}

bool Set:: operator<=(const Set& b) const
{
    Node *p1 = this->head->next;  // pekare till v�nstra objektet
    Node *p2 = b.head->next; // pekare till h�gra objektet

    while (p1 && p2)
    {
        if( p1->value  >  p2->value)  // v�rdet i p1 str�rre �n v�rdet i p2
        {
            p2 = p2->next;  // peka p� n�sta nod i p2
        }
        else if (p1->value == p2->value) // v�rdena lika
        {
            // peka p� n�sta nod i p1 och p2
            p1 = p1->next;
            p2 = p2->next;

        }
        else  // p2->vlaue > p1->value.
        {
            return false; // de �r sorterade och d�rmed kan p1 inte vara en delm�ngd
        }
    }
    while(p1) // p1 �r l�ngre �n p2 (fortfarande noder kvar)
    {
        return false; // uppenbart
    }
    while(p2) // p2 �r l�ngre �n p1
    {
        return true;
    }
}


bool Set:: operator==(const Set& b) const
{
    return(*this <= b && b <= *this);
//    Node *p1 = this->head->next;
//    Node *p2 = b.head->next;
//
//     while (p1 && p2)
//     {
//        if(p1->value != p2->value)
//        {
//            return false;
//            p1 = p1->next;
//            p2 = p2->next;
//        }
//        while(p1)
//        {
//            return false;
//        }
//        while(p2)
//        {
//            return false;
//        }
//     }
//    return true;

}

bool Set:: operator<(const Set& b)  const
{
    if(*this <= b && !(b <= *this))
    {
        return true;
    }
    return false;
}

//Set union
//Repeated values are not allowed
Set Set::operator+ (const Set& b) const
{
    Set tempset;

    Node *p1 = tempset.head;
    Node *p2 = this->head->next ;
    Node *p3 = b.head->next;

    while(p3 && p2 ) // p2 != nullptr && p3 != nullptr
    {
        if (p2-> value > p3->value)
        {
            p1->next = new Node(p3->value, nullptr);
            p3 = p3->next;
            p1 = p1->next;
        }
        else if (p2->value < p3->value)
        {
            p1->next = new Node(p2->value, nullptr);
            p2 = p2->next;
            p1 = p1->next;

        }
        else //(p2 == p3)
        {
            p1->next= new Node(p2->value, nullptr);
            p2 = p2->next;
            p3 = p3->next;
            p1 = p1->next;
        }

    }
    while(p2)
    {
        p1->next = new Node(p2->value,nullptr);
        p2 = p2->next;
        p1 = p1->next;
    }
    while(p3)
    {
        p1->next= new Node(p3->value,nullptr);
        p3 = p3->next;
        p1 = p1->next;
    }


    return tempset; //to be deleted
}

//Set intersection
Set Set::operator* (const Set& b) const
{
    Set tempset;

    Node *p1 = tempset.head;
    Node *p2 = this->head->next ;
    Node *p3 = b.head->next;

    while (p2 && p3)
    {
        if (p2->value == p3->value)
        {
            p1->next = new Node(p2->value,nullptr);
            p1 = p1->next;
            p2 = p2->next;
            p3 = p3->next;
        }
        else
        {
            p2 = p2->next;
            p3 = p3->next;
        }
    }


    return tempset; //to be deleted
}

//Set difference
Set Set::operator- (const Set& b) const
{
    Set tempset;

    Node *p1 = tempset.head;
    Node *p2 = this->head->next ;
    Node *p3 = b.head->next;

    while (p2 && p3)
    {
        if(p2->value < p3->value)
        {
            p1->next = new Node(p2->value,nullptr);
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p3->value< p2->value )
        {
            p3 = p3->next;
        }
        else
        {
            p2 = p2->next;
            p3 = p3->next;
        }
    }
    while (p2)
    {
        p1->next = new Node(p2->value,nullptr);
        p2 = p2->next;
        p1 = p1->next;
    }
    while (p3)
    {
        p3 = p3->next;
    }

    return tempset;
}

//set union with set {x}
Set Set::operator+(int x) const
{
    Set newset(*this);
    Set tempset(x);

    newset = newset + tempset;

    return newset;

}

//set difference with set {x}
Set Set::operator-(int x) const
{

    Set tempset(x);


    return *this - tempset; //to be deleted
}

//Assignment operator
const Set& Set::operator=(const Set &s)
{
    Set temp(s);

    swap(head, temp.head);

    return *this; //to be deleted
}

ostream& operator<< (ostream& os, const Set& theSet)
{
    if (theSet.empty())
        os << "Set is empty!" << std::endl;
    else
    {
        Set::Node *temp = theSet.head->next;
        os << "{ ";

        while (temp)
        {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}" << endl;
    }

    return os;
}
