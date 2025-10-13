#include <iostream>
using namespace std;

struct CNode
{
    int v;
    CNode* next;
    CNode(int x)
    {
        v = x;
        next = 0;
    }

};

class CForwardList
{
public:
    CForwardList();
    ~CForwardList();

    void push_back(int x);
    void push_front(int x);

    void pop_back();
    void pop_front();

    int& operator[](int x); //cambiar un nro usando su posicion

    void print();

private:
    CNode* head;
    int nelem;

};
CForwardList::CForwardList()
{
    head = 0;
    nelem = 0;
}
CForwardList::~CForwardList()
{
    CNode* p = head; //empezamos a desarmar desde la cabeza(p es nuestro ayudante)
    while (p) //mientras quede algun p
    {
        p = p->next; //avanzamos p
        delete head; //borramos la cabeza
        head = p; //la cabeza ahora es p
    }
}

void CForwardList::push_back(int x)
{
    CNode* n = new CNode(x); //creamos un nuevo nodo
    if (!head) head = n;
    else
    {
        CNode* p = head;

        while (p->next)
        {
            p = p->next;
        }
        p->next = n;
        nelem++;
    }
}

void CForwardList::push_front(int x)
{
    CNode* n = new CNode(x);
    n->next = head;
    head = n;
    nelem++;
}

void CForwardList::pop_front()
{
    if (!head)return;
    CNode* n = head;
    head = head->next;
    delete n;
    nelem--;
}

void CForwardList::pop_back()
{
    CNode* n = head;
    if (!head) return;

    if (!head->next)
    {
        delete head;
        head = 0;
        nelem--;
        return;
    }
    CNode* prev = head;
    CNode* p = head->next;
    while (p->next != 0)
    {
        prev = p;
        p = p->next;
    }
    delete p;
    prev->next = 0;
    nelem--;

}
int& CForwardList::operator[](int i)
{
    // assert(i < nelem);
    CNode* p = head;
    for (int j = 0; j < i; j++)
        p = p->next;
    return p->v;
}
void CForwardList::print()
{
    for (CNode* p = head; p != 0; p = p->next)
        std::cout << p->v << " ";
    std::cout << "\n";
}


int main() {
    CForwardList fl;
    int opcion, valor, idx;

    do {
        cout << "\n===== MENU LISTA ENLAZADA =====\n";
        cout << "1. Insertar al frente\n";
        cout << "2. Insertar al final\n";
        cout << "3. Eliminar al frente\n";
        cout << "4. Eliminar al final\n";
        cout << "5. Modificar elemento por indice\n";
        cout << "6. Mostrar lista\n";
        cout << "0. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Valor a insertar: ";
            cin >> valor;
            fl.push_front(valor);
            break;
        case 2:
            cout << "Valor a insertar: ";
            cin >> valor;
            fl.push_back(valor);
            break;
        case 3:
            fl.pop_front();
            cout << "Elemento eliminado al frente.\n";
            break;
        case 4:
            fl.pop_back();
            cout << "Elemento eliminado al final.\n";
            break;
        case 5:
            cout << "Indice a modificar: ";
            cin >> idx;
            cout << "Nuevo valor: ";
            cin >> valor;
            fl[idx] = valor;
            break;
        case 6:
            fl.print();
            break;
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida!\n";
        }
    } while (opcion != 0);

    return 0;
}