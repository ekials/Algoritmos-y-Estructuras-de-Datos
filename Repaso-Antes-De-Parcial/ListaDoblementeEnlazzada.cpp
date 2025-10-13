#include <iostream>
using namespace std;

struct Node
{
    int v;
    Node* prev; //* al nodo anterior
    Node* next; // * al nodo posterior
    Node(int x)
    {
        v = x;
        prev = 0;
        next = 0;
    }
};

class CDoublyList
{
public:
    CDoublyList();
    ~CDoublyList();
    void push_front(int x);
    void push_back(int x);


    void pop_front();
    void pop_back();

    void print_forward(); //print inicio a fin
    void print_backward(); //print fin a inicio
private:
        Node* head; //puntero al primer nodo
        Node* tail; //puntero al ultimo nodo
        int nelem;

};

CDoublyList::CDoublyList()
{
    head = 0;
    tail = 0;
    nelem = 0;
}


CDoublyList::~CDoublyList()
{
    Node* p = head; //comienza en el primer nodo 
    while (p) // mientras haya nodos
    { 
        Node* q = p; //guarda referencia al nodo actual
        p = p->next; // avanza al siguiente nodo
        delete q; // chau memoria de nodo actual
    }
}

void CDoublyList::push_front(int x)
{
    Node* n = new Node(x); //new nodo con x
    //c. nro 1
    if (!head) // si la lista esta vacia
    {
        head = tail = n; //head y tail apuntan al nuevo nodo
    }
    //c nro. 2 - con elementos en la lista
    else
    {
        n->next = head; //n tiene que estar antes de head (primer elemento)
        head->prev = n; // head (primer elemento) tiene que estar despues de n
        head = n; // El primer elemento (head) se convierte en n
    }
    nelem++;
}

void CDoublyList::push_back(int x)
{
    Node* n = new Node(x);

    if (!head)
    {
        head = tail = n;
    }

    else
    {
        n->prev = tail; // n tiene que estar despues de el ultimo nodo (tail)
        tail->next = n; // el ultimo nodo (tail) tiene que estar antes que n
        tail = n; // n se convierte en el ultimo nodo (tail) 
    }
    nelem++;
}

void CDoublyList::pop_front()
{
    if (!head) return;

    Node* n = head; // n guarda el valor de head (primer elemento) - nodo actual
    head = head->next; // el primer elemento (head) se convierte en el segundo elemento

    if (head) //si tenemos nodos uu
    { 
        head->prev = 0; // el elemento anterior de head se convierte en nullptr
    }
    else //si solo es un elemento
    {
        tail = 0;
    }
    delete n;
    nelem--;

}

void CDoublyList::pop_back()
{
    if (!tail) return;
    Node* n = tail;
    tail = tail-> prev; //el ultimo nodo (tail) se convierte en el penultimo nodo

    if (tail) //muchos nodos
    {
        tail->next = 0; // el elemento posterior a tail se convierte en 0
    }

    else
    {
        head = 0;
    }
    delete n;
    nelem--;
}

void CDoublyList::print_forward()
{
    for (Node* p = head; p; p = p->next)
    {
        cout << p->v << " ";
    }
    cout << "\n";
}
// p-> v es equivalente a (*p).v 
//lo que apunta a p, dame su valor v
void CDoublyList::print_backward()
{

    for (Node* p = tail; p; p = p->prev)
    {
        cout << (*p).v << " ";
    }
    cout << "\n";
}

int main() {
    CDoublyList dl;              // Crea lista vacía

    dl.push_front(10);           // Lista: 10
    dl.push_back(20);            // Lista: 10 ↔ 20
    dl.push_back(30);            // Lista: 10 ↔ 20 ↔ 30

    dl.print_forward();          // Imprime: 10 20 30
    dl.print_backward();         // Imprime: 30 20 10

    dl.pop_front();              // Elimina 10 → Lista: 20 ↔ 30
    dl.print_forward();          // Imprime: 20 30

    dl.pop_back();               // Elimina 30 → Lista: 20
    dl.print_forward();          // Imprime: 20

    return 0;
}