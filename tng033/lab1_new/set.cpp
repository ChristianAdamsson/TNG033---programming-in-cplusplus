
#include "set.h"
#include <algorithm>
//Default constructor
Set::Set ()
{
    head = new Node(0,nullptr);   //head pekar på en dummy node
}
//Constructor for creating a set from an int
Set::Set(int v)
{
    Node *newNode = new Node(v, nullptr); // ny node mead värdet v, pekar på null pointer
    head = new Node(0, newNode); // dummy node som pekar på första noden
}

//Constructor creating a set
//from n integers in a non-sorted array a
Set::Set (int a[], int n)
{
    sort(a,a+n, greater<int>()); // sorterar arrayen
    head = new Node(0, nullptr); // head pekar på dummy node
    for (int i = 0; i < n; ++i)  // n = storlek på array
    {
        head->next=new Node(a[i],head->next); // ny node skapas med värdet a[i]
    }
}

//copy constructor
Set::Set (const Set &source)
{
    head = new Node (0,nullptr); // temp pekar på null pointer
    Node *p2 = head; // p2 pekar på temp
    for (Node *p1 = source.head->next; p1 != nullptr; p1= p1->next) // så länge p1 inte pekar på null pointer, gå till nästa node
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

    while(p1 != nullptr && p1->next != nullptr)  // medans man inte är i slutet av ett set
    {
        p1 = p1->next; // flytta till nästa node
        counter ++; // addera till counter
    }
    return counter;
}

//Test if x is an element of the set
bool Set::member (int x) const
{
    Node* temp = head->next;

    while (temp) // medans värdet i en Node inte är lika med x
    {
        if (temp->value == x)
        {
            return true;
        }
        temp = temp->next; // gå till nästa node
    }
    return false;

}

bool Set:: operator<=(const Set& b) const
{
    Node *p1 = this->head->next;  // pekare till vänstra objektet
    Node *p2 = b.head->next; // pekare till högra objektet

    while (p1 && p2)
    {
        if( p1->value  >  p2->value)  // värdet i p1 strörre än värdet i p2
        {
            p2 = p2->next;  // peka på nästa nod i p2
        }
        else if (p1->value == p2->value) // värdena lika
        {
            // peka på nästa nod i p1 och p2
            p1 = p1->next;
            p2 = p2->next;

        }
        else  // p2->vlaue > p1->value.
        {
            return false; // de är sorterade och därmed kan p1 inte vara en delmängd
        }
    }
    while(p1) // p1 är längre än p2 (fortfarande noder kvar)
    {
        return false; // uppenbart
    }
    while(p2) // p2 är längre än p1
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
