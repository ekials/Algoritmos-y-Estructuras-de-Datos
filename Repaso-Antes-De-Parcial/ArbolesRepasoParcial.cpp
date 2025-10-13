#include <iostream>
#include <stack>
#include <queue>
using namespace std;

/* =======================================================
   🌱 NIVEL 1 – ÁRBOL BASE (Raíces del Ki)
   Objetivo: Entender punteros y estructura básica del árbol
   ======================================================= */

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(0), right(0) {}
};

class BinTree {
public:
    Node* root; //raiz de arbol
    BinTree() : root(0) {}

    // Inserta como BST normal
    void insert(int v) {
        Node** p = &root; //p inicia en la raiz
        while (*p) //mientras p!=nullptr
        {
            if (v < (*p)->val) p = &(*p)->left; //si v es menor a la data de p (una rama o raiz), p se ubica a la izzquierda
            else p = &(*p)->right; //pero si es mayor p se ubica a la derecha
        }
        *p = new Node(v); //y se inserta el valor y crea el nodo(hoja, raiz o rama)
    }

    void inorder(Node* n) {
        if (!n) return; //si es == nullptr, sale
        inorder(n->left); //recorre a la izquierda 
        cout << n->val << " ";//retorna el valor de forma recursiva
        inorder(n->right); //recorre a la derecha de forma recursiva
    }

    void print() {
        cout << "\nInorder: ";
        inorder(root); //para  imprimir
        cout << endl;
    }
};

/* =======================================================
   ⚡ NIVEL 2 – ÁRBOL DE STACKS (Aumentando el poder)
   Objetivo: Cada nodo contiene un stack de enteros
   ======================================================= */

struct StackNode {
    stack<int> data; //arbol de pilas
    StackNode* left; //nodes[0]
    StackNode* right; //nodes[1]
    StackNode() : left(0), right(0) {}
};

class StackTree {
public:
    StackNode* root; //raiz
    StackTree() : root(0) {}

    void insert_stack(int val) { //insertar en la pila
        StackNode** p = &root; //p apunta a la raiz
        while (*p) { //mientras p != 0
            p = &((*p)->right); //p va a la derecha
        }
        *p = new StackNode(); //se crea una pila
        (*p)->data.push(val); //se agrega el valor a la pila
    }

    void inorder(StackNode* n) {
        if (!n) return;
        inorder(n->left); //primero  recorre izquierda de forma recursiva
        if (!n->data.empty()) cout << "[" << n->data.top() << "] ";//si la pila no es vacia, se imprime el primer valor de la pila y asi con todos los otros valores
        inorder(n->right); //luego recorre derecha de forma recursiva
    }

    void print() {
        cout << "\nInorder (stack tree): ";
        inorder(root);
        cout << endl;
    }
};

/* =======================================================
   🔥 NIVEL 3 – ÁRBOL DE QUEUES (Entrenamiento del tiempo)
   Objetivo: Cada nodo contiene una queue
   ======================================================= */

struct QueueNode {
    queue<int> data;//arbol de queue
    QueueNode* left;
    QueueNode* right;
    QueueNode() : left(0), right(0) {}
};

class QueueTree {
public:
    QueueNode* root; //raiz
    QueueTree() : root(0) {}

    void insert_queue(int val) {
        QueueNode** p = &root;
        while (*p) {//mientras p != de 0
            p = &((*p)->left); // p avanza para la izquierda
        }
        *p = new QueueNode(); //se crea un queue
        (*p)->data.push(val); //se inserta el valor en el queue
    }

    void inorder(QueueNode* n) {
        if (!n) return; //si no hay sale
        inorder(n->left);
        if (!n->data.empty()) cout << "(" << n->data.front() << ") ";// mientras el queue no este vacio, imprime el queue
        inorder(n->right);
    }

    void print() {
        cout << "\nInorder (queue tree): ";
        inorder(root);
        cout << endl;
    }
};

/* =======================================================
   💫 NIVEL 4 – LISTA CIRCULAR DE ÁRBOLES (Fusión máxima)
   Objetivo: Combinar estructuras enlazadas con árboles
   ======================================================= */

struct TreeListNode {
    BinTree tree;
    TreeListNode* next; //solo avanza
    TreeListNode(int a, int b, int c) {
        tree.insert(a);
        tree.insert(b);
        tree.insert(c);
        next = 0;
    }
};

class CircularTreeList {
public:
    TreeListNode* head;//inicio
    CircularTreeList() : head(0) {}

    void push_back(int a, int b, int c) {
        TreeListNode* nuevo = new TreeListNode(a, b, c);//insertar 3 elementos
        if (!head) { //si head != 0
            head = nuevo; // nuevo se convierte en head
            head->next = head; //el siguiente de head se vuelve head (es circular)
        }
        else {
            TreeListNode* curr = head; //actual se vuelve head
            while (curr->next != head) //mientras curr avance pero sea diferente del inicio
                curr = curr->next; //avanzamos curr
            curr->next = nuevo; //el siguiente de curr se vuelve nuevo (conectamors curr con nuevo)
            nuevo->next = head; //conectamos nuevo con head(es circular)
            //nuevo le da la mano izqueirda a curr y la derecha a head
        }
    }

    void print() {
        if (!head) return;
        TreeListNode* curr = head;
        do {
            curr->tree.print();
            curr = curr->next;
        } while (curr != head);
    }
};

/* =======================================================
   🧠 NIVEL 5 – SAYAYIN LEGENDARIO
   Objetivo: Árbol de listas (cada nodo tiene su propia lista)
   ======================================================= */

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(0) {}
};

struct TreeList {
    ListNode* list;
    TreeList* left;
    TreeList* right;
    TreeList() : list(0), left(0), right(0) {}

    void add_list(int v) {
        ListNode** p = &list;
        while (*p) p = &((*p)->next);
        *p = new ListNode(v);
    }
};

class TreeOfLists {
public:
    TreeList* root;//raiz de arbol
    TreeOfLists() : root(0) {}

    void insert_node(int a, int b, int c) { //insertar 3 elementos de un nodo
        TreeList** p = &root; //puntero a la raiz
        while (*p) p = &((*p)->right); //mientras p exista, avazamos a la derecha con referencia?
        *p = new TreeList(); // creamos un nuevo TreeList pero vacio
        (*p)->add_list(a);//agregamos a la lista a, b y c(las otras dos lineas)
        (*p)->add_list(b);
        (*p)->add_list(c);
    }

    void print(TreeList* n) {
        if (!n) return;//si no existe sale (no hay que imprimir)
        print(n->left); //si si existe va para la izquierda
        ListNode* temp = n->list; // temp que entra al contenido de list
        cout << "[ ";
        while (temp) {
            cout << temp->val << " "; //esto es igual a n->list->val
            temp = temp->next; //n->list = n->list->next al siguiente de la lista
        }
        cout << "] ";
        print(n->right);//es recursivo para que imprima todo
    }

    void show() {
        cout << "\nÁrbol de listas:\n";
        print(root);
        cout << endl;
    }
};

/* =======================================================
   🧩 MAIN DE PRUEBA
   ======================================================= */
int main() {
    cout << "=== NIVEL 1: Árbol base ===\n";
    BinTree t;
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.print();

    cout << "\n=== NIVEL 2: Árbol de Stacks ===\n";
    StackTree st;
    st.insert_stack(10);
    st.insert_stack(20);
    st.print();

    cout << "\n=== NIVEL 3: Árbol de Queues ===\n";
    QueueTree qt;
    qt.insert_queue(1);
    qt.insert_queue(2);
    qt.insert_queue(3);
    qt.print();

    cout << "\n=== NIVEL 4: Lista Circular de Árboles ===\n";
    CircularTreeList ctl;
    ctl.push_back(4, 5, 6);
    ctl.push_back(7, 8, 9);
    ctl.print();

    cout << "\n=== NIVEL 5: Árbol de Listas ===\n";
    TreeOfLists tol;
    tol.insert_node(1, 2, 3);
    tol.insert_node(4, 5, 6);
    tol.show();
}
