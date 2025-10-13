#include <iostream>
using namespace std;

struct CBinNode {
    int value;
    CBinNode* nodes[2];

    CBinNode(int v) {
        value = v;
        nodes[0] = nullptr;
        nodes[1] = nullptr;
    }
};

class CBinTree {
private:
    CBinNode* m_root = nullptr;
    bool m_b = 0;
    bool find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void Inorder(CBinNode* p);
public:
    bool Insert(int x);
    bool Remove(int x);
    void Primos(int x);
    void print();
    void BFS_simple();
};

bool CBinTree::find(int x, CBinNode**& p) {
    for (p = &m_root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x) {
    CBinNode** p;
    if (find(x, p)) {
        return false;
    }
    *p = new CBinNode(x);
    return true;
}

CBinNode** CBinTree::Rep(CBinNode** p) {
    m_b = !m_b;
    p = &((*p)->nodes[!m_b]);
    while ((*p)->nodes[m_b]) {
        p = &((*p)->nodes[m_b]);
    }
    return p;
}

bool CBinTree::Remove(int x) {
    CBinNode** p;
    if (!find(x, p)) {
        return false;
    }


    if ((*p)->nodes[0] && (*p)->nodes[1]) {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }

    CBinNode* temp = *p;
    *p = (*p)->nodes[(*p)->nodes[0] == 0];
    delete temp;
    return true;
}

void CBinTree::Inorder(CBinNode* p) {
    if (!p) return;
    Inorder(p->nodes[0]);
    cout << p->value << " ";
    Inorder(p->nodes[1]);
}


void CBinTree::print() {
    Inorder(m_root);
    cout << endl;
}


void CBinTree::BFS_simple()
{
    CBinNode* cola[100];
    int frente = 0; //indice para sacar
    int final = 0; //indice para agtrgar

    cola[final++] = m_root; //encolar la raiz

    while (frente < final) //mientras la cola no este vacia
    {
        CBinNode* actual = cola[frente++]; //desencolar (sacar el primero)
        cout << actual->value << " ";
    
        //encolar los hijos
        if (actual->nodes[0])
        {
            cola[final++] = actual->nodes[0];
        }
        if (actual->nodes[1])
        {
            cola[final++] = actual->nodes[1];
        }
    
    } 
}
void CBinTree::Primos(int x) {
    CBinNode** pp;  // Para find
    if (!find(x, pp)) {
        cout << "El nodo no existe" << endl;
        return;
    }

    // Estructura para info en cola
    struct NodeInfo {
        CBinNode* node; //nodo actual
        CBinNode* parent; //padre del nodo
        int depth; //profundidad(nivel del nodo)
    };

    // PRIMER BFS: Encontrar depth_x y padre_x
    NodeInfo cola1[100];
    int frente1 = 0;
    int final1 = 0;
    cola1[final1++] = { m_root, nullptr, 0 };

    CBinNode* padre_x = nullptr;
    int depth_x = -1;

    while (frente1 < final1) {
        NodeInfo curr = cola1[frente1++];
        if (curr.node->value == x) {
            padre_x = curr.parent;
            depth_x = curr.depth;
            // No break, pero opcional: break; para parar temprano
        }
        if (curr.node->nodes[0]) {
            cola1[final1++] = { curr.node->nodes[0], curr.node, curr.depth + 1 };
        }
        if (curr.node->nodes[1]) {
            cola1[final1++] = { curr.node->nodes[1], curr.node, curr.depth + 1 };
        }
    }

    // SEGUNDO BFS: Recorrer todo el árbol y imprimir primos
    NodeInfo cola2[100];
    int frente2 = 0;
    int final2 = 0;
    cola2[final2++] = { m_root, nullptr, 0 };

    cout << "Primos de " << x << " :";

    while (frente2 < final2) {
        NodeInfo curr = cola2[frente2++];
        // Condición: mismo depth, no es x, padre diferente
        if (curr.depth == depth_x &&
            curr.node->value != x &&
            curr.parent != padre_x) {
            cout << " " << curr.node->value;
        }
        if (curr.node->nodes[0]) {
            cola2[final2++] = { curr.node->nodes[0], curr.node, curr.depth + 1 };
        }
        if (curr.node->nodes[1]) {
            cola2[final2++] = { curr.node->nodes[1], curr.node, curr.depth + 1 };
        }
    }

    cout << endl;
}

int main() {
    CBinTree t;
    t.Insert(50);
    t.Insert(30);
    t.Insert(70);
    t.Insert(10);
    t.Insert(40);
    t.Insert(60);
    t.Insert(80);
    t.Insert(5);
    t.Insert(15);
    t.Insert(35);
    t.Insert(45);

    t.print();
    t.Primos(30);
    t.Primos(50);
    t.Primos(10);
    t.Primos(15);
    t.Primos(35);
    t.Primos(900);
}
