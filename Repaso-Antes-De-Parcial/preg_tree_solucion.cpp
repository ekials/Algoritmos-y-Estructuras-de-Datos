#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    void Print();
    void kneighbors(int x, int k);
private:
    bool Find(int x, CBinNode**& p);
    void InOrder(CBinNode* n);
    CBinNode* m_root;
};

CBinTree::CBinTree()
{
    m_root = 0;
}

CBinTree::~CBinTree()
{}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);
    return 0;
}

void CBinTree::InOrder(CBinNode* n)
{
    if (!n) return;
    InOrder(n->nodes[0]);
    cout << n->value << " ";
    InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
    InOrder(m_root);
    cout << endl;
}

void CBinTree::kneighbors(int x, int k)
{
    std::cout << "\n(" << x << "," << k << ") => ";
    if (k <= 0) return;

    // Paso 1: recorrer el arbol y guardar todos los valores (in-order iterativo)
    CBinNode* stack[1000]; //almacena punteros a nodos
    int top = 0; //cima de la pila 
    CBinNode* curr = m_root; //para iniciar el recorrido

    int arr[50];  // arreglo donde guardaremos los valores
    int idx = 0;     // índice actual

    while (curr != 0 || top > 0)
    {
        while (curr != 0)  // bajar todo por la izquierda
        {
            stack[top++] = curr;
           // stack[top] = curr;
            //top = top + 1;
            
            curr = curr->nodes[0];
        }

        //simula un pop()
        curr = stack[--top];       // subimos un nodo
       
        arr[idx++] = curr->value;  // guardamos su valor (in-order)
      

        
        curr = curr->nodes[1];  // pasamos al subárbol derecho
    }

    int cont = idx; //total de nodos encontrados

    int distancias[1000];
    for (int i = 0; i < cont; i++)
    {
        int temp = x - arr[i];
        if (temp < 0) temp = -temp;  
        distancias[i] = temp;
    }

    for (int i = 0; i < cont - 1; i++)
    {
        for (int j = 0; j < cont - i - 1; j++)
        {
            if (distancias[j] > distancias[j + 1])
            {
                /*
                int tmpD = distancias[j];
                distancias[j] = distancias[j + 1];
                distancias[j + 1] = tmpD;

                int tmpV = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmpV;
                */
                std::swap(distancias[j], distancias[j + 1]);
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }

    for (int i = 0; i < k && i < cont; i++)
    {
        cout << arr[i] << " ";
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    CBinTree t;
    t.Insert(55); t.Insert(41); t.Insert(77);
    t.Insert(33); t.Insert(47); t.Insert(61);
    t.Insert(88); t.Insert(20); t.Insert(36);
    t.Insert(44); t.Insert(51); t.Insert(57);
    t.Insert(65); t.Insert(80); t.Insert(99);
    t.Print();

    t.kneighbors(33, 4);
    t.kneighbors(88, 3);
    t.kneighbors(76, 2);
    t.kneighbors(47, 5);
    t.kneighbors(61, 4);
    t.kneighbors(50, 3);
    t.kneighbors(81, 5);
    t.kneighbors(20, 7);
}
