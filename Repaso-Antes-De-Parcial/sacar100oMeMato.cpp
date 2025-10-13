#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

/* ═══════════════════════════════════════════════════════════════════════
   🔴 NIVEL 1: FUNDAMENTOS CRÍTICOS
   ═══════════════════════════════════════════════════════════════════════ */

   // EJERCICIO 1A: Lista Simple - Destructor Correcto
struct NodeSimple {
    int data;
    NodeSimple* next;
    NodeSimple(int d) : data(d), next(0) {}
};

class ListaSimple_E1 {
private:
    NodeSimple* head;
public:
    ListaSimple_E1() : head(0) {}

    ~ListaSimple_E1() {
        NodeSimple* curr = head;
        while (curr) {
            NodeSimple* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = 0;
    }

    void push_back(int x) {
        if (!head) { head = new NodeSimple(x); return; }
        NodeSimple* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = new NodeSimple(x);
    }
};

// EJERCICIO 1B: Lista Doble - Destructor Correcto
struct NodeDoble {
    int data;
    NodeDoble* next, * prev;
    NodeDoble(int d) : data(d), next(0), prev(0) {}
};

class ListaDoble_E1 {
private:
    NodeDoble* head, * tail;
public:
    ListaDoble_E1() : head(0), tail(0) {}

    ~ListaDoble_E1() {
        NodeDoble* curr = head;
        while (curr) {
            NodeDoble* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = tail = 0;
    }

    void push_back(int x) {
        NodeDoble* n = new NodeDoble(x);
        if (!tail) { head = tail = n; return; }
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
};

// EJERCICIO 1C: Árbol - Destructor Correcto (RECURSIVO)
struct TreeNode {
    int value;
    TreeNode* left, * right;
    TreeNode(int v) : value(v), left(0), right(0) {}
};

class BST_E1 {
private:
    TreeNode* root;

    void destroy(TreeNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST_E1() : root(0) {}

    ~BST_E1() {
        destroy(root);
        root = 0;
    }

    void insert(int x) {
        TreeNode** p = &root;
        while (*p && (*p)->value != x) {
            if ((*p)->value < x) p = &((*p)->right);
            else p = &((*p)->left);
        }
        if (!*p) *p = new TreeNode(x);
    }
};

/* ───────────────────────────────────────────────────────────────────────
   E2: PUNTEROS A PUNTEROS - TÉCNICA DEL PROFESOR
   ─────────────────────────────────────────────────────────────────────── */

class ListaOrdenada_E2 {
private:
    NodeSimple* head;

public:
    ListaOrdenada_E2() : head(0) {}

    bool find(int x, NodeSimple**& p) {
        for (p = &head; *p && (*p)->data < x; p = &((*p)->next));
        return *p && (*p)->data == x;
    }

    bool insert(int x) {
        NodeSimple** p;
        if (find(x, p)) return false;
        NodeSimple* n = new NodeSimple(x);
        n->next = *p;
        *p = n;
        return true;
    }

    bool remove(int x) {
        NodeSimple** p;
        if (!find(x, p)) return false;
        NodeSimple* temp = *p;
        *p = (*p)->next;
        delete temp;
        return true;
    }

    void print() {
        for (NodeSimple* t = head; t; t = t->next)
            cout << t->data << " ";
        cout << "\n";
    }
};

// Árbol con punteros a punteros
class BST_E2 {
private:
    TreeNode* root;

public:
    BST_E2() : root(0) {}

    bool find(int x, TreeNode**& p) {
        for (p = &root; *p && (*p)->value != x;
            p = &((*p)->value < x ? (*p)->right : (*p)->left));
        return *p && (*p)->value == x;
    }

    bool insert(int x) {
        TreeNode** p;
        if (find(x, p)) return false;
        *p = new TreeNode(x);
        return true;
    }

    bool remove(int x) {
        TreeNode** p;
        if (!find(x, p)) return false;
        TreeNode* t = *p;
        if (t->left && t->right) {
            TreeNode** q = &(t->right);
            while ((*q)->left) q = &((*q)->left);
            t->value = (*q)->value;
            t = *q;
            p = q;
        }
        *p = (t->left) ? t->left : t->right;
        delete t;
        return true;
    }
};

/* ───────────────────────────────────────────────────────────────────────
   E3: LISTA ENLAZADA ORDENADA SIN REPETICIÓN
   ─────────────────────────────────────────────────────────────────────── */

class CSortedList_E3 {
private:
    NodeSimple* head;

    bool find(int x, NodeSimple**& p) {
        for (p = &head; *p && (*p)->data < x; p = &((*p)->next));
        return *p && (*p)->data == x;
    }

public:
    CSortedList_E3() : head(0) {}

    ~CSortedList_E3() {
        NodeSimple* curr = head;
        while (curr) {
            NodeSimple* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = 0;
    }

    bool ins(int x) {
        NodeSimple** p;
        if (find(x, p)) return false;
        NodeSimple* n = new NodeSimple(x);
        n->next = *p;
        *p = n;
        return true;
    }

    bool rem(int x) {
        NodeSimple** p;
        if (!find(x, p)) return false;
        NodeSimple* t = *p;
        *p = (*p)->next;
        delete t;
        return true;
    }

    void print() {
        for (NodeSimple* t = head; t; t = t->next)
            cout << t->data << " ";
        cout << "\n";
    }
};

/* ───────────────────────────────────────────────────────────────────────
   E4: ADAPTADORES - Stack usando Lista Enlazada
   ─────────────────────────────────────────────────────────────────────── */

class CStack_E4 {
private:
    NodeSimple* top_node;

public:
    CStack_E4() : top_node(0) {}

    ~CStack_E4() {
        while (top_node) {
            NodeSimple* temp = top_node;
            top_node = top_node->next;
            delete temp;
        }
    }

    void push(int x) {
        NodeSimple* n = new NodeSimple(x);
        n->next = top_node;
        top_node = n;
    }

    void pop() {
        if (!top_node) return;
        NodeSimple* temp = top_node;
        top_node = top_node->next;
        delete temp;
    }

    int top() {
        if (!top_node) return -1;
        return top_node->data;
    }

    bool empty() { return top_node == 0; }
};

/* ───────────────────────────────────────────────────────────────────────
   E5: split_list() - Lista Doblemente Enlazada
   ─────────────────────────────────────────────────────────────────────── */

struct NodeDL {
    int data;
    NodeDL* next, * prev;
    NodeDL(int d) : data(d), next(0), prev(0) {}
};

class DoublyList_E10 {
private:
    NodeDL* head, * tail;
    int size;

public:
    DoublyList_E10() : head(0), tail(0), size(0) {}

    ~DoublyList_E10() {
        NodeDL* curr = head;
        while (curr) {
            NodeDL* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = tail = 0;
    }

    void push_front(int x) {
        NodeDL* n = new NodeDL(x);
        if (!head) head = tail = n;
        else {
            n->next = head;
            head->prev = n;
            head = n;
        }
        size++;
    }

    void push_back(int x) {
        NodeDL* n = new NodeDL(x);
        if (!head) head = tail = n;
        else {
            n->prev = tail;
            tail->next = n;
            tail = n;
        }
        size++;
    }

    void pop_front() {
        if (!head) return;
        NodeDL* temp = head;
        head = head->next;
        if (head) head->prev = 0;
        delete temp;
        size--;
    }

    void pop_back() {
        if (!tail) return;
        NodeDL* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = 0;
        delete temp;
        size--;
    }

    void insert_at(int pos, int x) {
        if (pos <= 0) { push_front(x); return; }
        if (pos >= size) { push_back(x); return; }

        NodeDL* n = new NodeDL(x);
        NodeDL* curr = head;
        for (int i = 0; i < pos; i++) curr = curr->next;

        n->next = curr;
        n->prev = curr->prev;
        curr->prev->next = n;
        curr->prev = n;
        size++;
    }

    void remove_at(int pos) {
        if (pos <= 0) { pop_front(); return; }
        if (pos >= size - 1) { pop_back(); return; }

        NodeDL* curr = head;
        for (int i = 0; i < pos; i++) curr = curr->next;

        NodeDL* before = curr->prev;
        NodeDL* after = curr->next;

        before->next = after;
        after->prev = before;
        delete curr;
        size--;
    }

    NodeDL* find(int x) {
        for (NodeDL* curr = head; curr; curr = curr->next)
            if (curr->data == x) return curr;
        return 0;
    }

    void reverse() {
        NodeDL* curr = head;
        NodeDL* temp = 0;
        while (curr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }
        if (temp) head = temp->prev;
    }

    void sort() {
        if (!head) return;
        bool swapped;
        do {
            swapped = false;
            NodeDL* curr = head;
            while (curr->next) {
                if (curr->data > curr->next->data) {
                    swap(curr->data, curr->next->data);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }

    void merge(DoublyList_E10& other) {
        NodeDL* a = head;
        NodeDL* b = other.head;
        NodeDL* result = 0, * tail_res = 0;

        while (a && b) {
            NodeDL*& minNode = (a->data < b->data) ? a : b;
            NodeDL* nextNode = minNode;
            minNode = minNode->next;

            nextNode->prev = tail_res;
            nextNode->next = 0;
            if (!result) result = nextNode;
            else tail_res->next = nextNode;
            tail_res = nextNode;
        }
        NodeDL* rest = a ? a : b;
        if (rest) {
            rest->prev = tail_res;
            if (tail_res) tail_res->next = rest;
            else result = rest;
        }

        head = result;
        tail = tail_res;
        other.head = other.tail = 0;
    }

    void print() {
        NodeDL* curr = head;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << "\n";
    }
};

/* ═══════════════════════════════════════════════════════════════════════
   🟡 NIVEL 4: ESTRUCTURAS HÍBRIDAS (con STL)
   ═══════════════════════════════════════════════════════════════════════ */

   /* ───────────────────────────────────────────────────────────────────────
      E11: STACK DE QUEUES

      PROBABILIDAD: 60% (mencionaste: "puede pedir de dos estructuras juntas")
      TIEMPO: 1 hora
      DIFICULTAD: ★★★☆☆

      Del chat: "en un parcial pasado vino crear una pila y que cada pila
      tenga un deque"
      ─────────────────────────────────────────────────────────────────────── */

struct StackNodeQ {
    queue<int> data;
    StackNodeQ* next;
    StackNodeQ() : next(0) {}
};

class StackOfQueues_E11 {
private:
    StackNodeQ* top;
    int stack_size;
public:
    StackOfQueues_E11() : top(0) {}

    ~StackOfQueues_E11() {
        while (top)
        {
            StackNodeQ* temp = top;
            top = top->next;
            delete temp;
        }
    }

    // TODO: push_queue - agregar un queue vacío al tope
    void push_queue() {
        StackNodeQ* n = new StackNodeQ();
        n->next = top;
        top = n;
        stack_size++;
    }

    // TODO: pop_queue - eliminar el queue del tope
    void pop_queue() {
        if (!top) return;
        StackNodeQ* temp = top;
        top = top->next;
        delete temp;
        stack_size--;

    }

    // TODO: enqueue_top - agregar x al queue del tope
    void enqueue_top(int x) {
        if (!top) { push_queue(); }
        top->data.push(x);
    }

    // TODO: dequeue_top - eliminar del frente del queue del tope
    int dequeue_top() {
        if (!top || top->data.empty()) {
            pop_queue(); return -1;
        }
        int val = top->data.front();
        top->data.pop();
        if (top->data.empty()) { pop_queue(); } //si el queue del tope quedo vacio, eliminar el nodo de la pila
        return val;
    }

    // TODO: transfer_to_next - mover todo del tope al siguiente queue
    void transfer_to_next() {
        // TU CÓDIGO AQUÍ
        if (!top || top->data.empty() )  return; 
        
        StackNodeQ* temp = top;
        while(!top->data.empty())
        {
            int val = top->data.front();
            top->next->data.push(val);
            top->data.pop();
        }
        top = top->next;
        delete temp;

    }

    // TODO: flatten - retornar todos los elementos en un solo queue
    queue<int> flatten() {
        queue<int> result;
        StackNodeQ* temp = top;
        while(temp)
        {
            while (!temp->data.empty())
            {
                int val = temp->data.front();
                result.push(val);
                temp->data.pop();
            }
            temp = temp->next;
        }

        return result;
    }

    void print_all() {
        if (!top) { cout << "Empty\n"; return; }
        StackNodeQ* curr = top;
        int level = 0;
        cout << "Stack (top->bottom):\n";
        while (curr) {
            cout << "  Queue[" << level << "]: ";
            queue<int> temp = curr->data;
            while (!temp.empty()) {
                cout << temp.front() << " ";
                temp.pop();
            }
            cout << "\n";
            curr = curr->next;
            level++;
        }
    }
};

/* ───────────────────────────────────────────────────────────────────────
   E12: DEQUE DE STACKS

   PROBABILIDAD: 60% (similar al anterior, pero inverso)
   TIEMPO: 1 hora
   DIFICULTAD: ★★★☆☆
   ─────────────────────────────────────────────────────────────────────── */

struct DequeNodeS {
    stack<int> data;
    DequeNodeS* next, * prev;
    DequeNodeS() : next(0), prev(0) {}
};

class DequeOfStacks_E12 {
private:
    DequeNodeS* head, * tail;
    int size;

public:
    DequeOfStacks_E12() : head(0), tail(0), size(0) {}

    ~DequeOfStacks_E12() {
        while (head)
        {
            DequeNodeS* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // TODO: Implementar todas estas operaciones
    void push_front_stack()
    {
        DequeNodeS* n = new DequeNodeS();
        if (!head) { head = tail = n; size++; return; }
        n->next = head;
        head->prev = n;
        size++;
    }
    void push_back_stack()
    {
        DequeNodeS* n = new DequeNodeS();
        if (!tail) { head = tail = n; size++; return; }
        n->prev = tail;
        tail->next = n;
        size++;
    
    }
    void pop_front_stack() 
    {
        if (!head) return;
        DequeNodeS* n = head;
        head = head->next;
        if (head) { head->prev = 0; }
        else { tail = 0; }
        delete n;
        size--;
    }
    
    void pop_back_stack() 
    { 
        if (!head) return;
        DequeNodeS* n = tail;
        tail = tail->prev;
        if (tail) { tail->next = 0; }
        else { head = 0; }
        delete n;
        size--;

    }
    void push_to_front_stack(int x) 
    {
        if (!head) { push_front_stack(); }
        head->data.push(x); 
    }
    void push_to_back_stack(int x) 
    {
        if (!head) { push_back_stack();  }
        tail->data.push(x);
    }
    int pop_from_front_stack() 
    {
        if (!head) return -1;
        if ( head->data.empty()) { pop_front_stack(); return -1; }
        int val = head->data.top();
        head->data.pop();
        if (head->data.empty()) { pop_front_stack(); }
        return val;
    
    }
    int pop_from_back_stack()

    {
        if (!tail || tail->data.empty()) { pop_back_stack(); return -1; }
        int val = tail->data.top();
        tail->data.pop();
        if (tail->data.empty()) pop_back_stack();
        return val;
    
    }
    // TODO: balance - redistribuir elementos para que todos los stacks
    // tengan aproximadamente el mismo tamaño
    void balance() {
        DequeNodeS* curr = head;
        stack<int> temp;
        int cont = 0;

        if (!head) return;
        while (curr)
        {
            cont += curr->data.size();
            curr = curr->next;
        }
        curr = head;
        int tam_ideal = cont / size;

        while (curr)
        {
            while (!curr->data.empty())
            {
                temp.push(curr->data.top());
                curr->data.pop();
            }
            curr = curr->next;
        }
        curr = head;
        while (curr)
        {
            for (int i = 0; i < tam_ideal && !temp.empty(); i++)
            {
                curr->data.push(temp.top());
                temp.pop();
            }
            curr = curr->next;
        }
        //si sobra
        curr = head;
        while (!temp.empty() && curr)
        {
            curr->data.push(temp.top());
            temp.pop();
            curr = curr->next;

        }
    }
};

/*void DequeOfStacks::balance() {
// Tu código: redistribuir elementos entre stacks
// para que tengan tamaños similares
if (!head)return;
int cont = 0;
DequeNode* n = head;
while (n)
{
    cont += n->data.size();
    n=n->next;
}
int temp_size = cont / deque_size;
if (head->data.size() == 0) return;

n = head;
while (n && n->next)
{
    while (n->data.size() < temp_size && n->next->data.empty())
    {
        int nro_temp = n->next->data.top();
        n->data.pop();
        n->data.push(nro_temp);
        //n = n->next;
    }

    while (n->data.size() > temp_size + 1)
    {
        int nro_temp = n->data.top();
        n->data.pop();
        head->next->data.push(nro_temp);
    }
    n = n->next;

}

}
*/
/* ═══════════════════════════════════════════════════════════════════════
   🟡 NIVEL 5: ÁRBOLES AVANZADOS
   ═══════════════════════════════════════════════════════════════════════ */

   /* ───────────────────────────────────────────────────────────────────────
      E13: fill_list - Llenar listas desde árbol

      PROBABILIDAD: 75% (del chat de clase que te pasaron)
      TIEMPO: 1 hora
      DIFICULTAD: ★★★☆☆

      Del chat: "FillList_a (lado izquierdo del arbol), FillList_c (lado
      derecho), FillList_b (hojas del árbol)"
      ─────────────────────────────────────────────────────────────────────── */

/*struct BinNode {
    int value;
    BinNode* left, * right;
    BinNode(int v) : value(v), left(0), right(0) {}
};*/

/*
Recursividad en arboles: 
la recursivdad es natural para los arboles porq 
cada subarbol es un arbol mas pequeño del mismo tipo
Eso significa que puedes aplicar la misma logica al nodo actual y sus hijos
es decir si sabes como resolver un problema para un arbol, sabes hacerlo para cada subarbol
ejm:
quiero imprimir los nodos
-> cada nodo tiene un hijo izquierdo y derecho (que son arboles tmb)
->entonces hago lo mismo: imprimir el actual y luego sus subarboles

-->patron basico de una funcion recursiva de una rbol:
void funcion(node* n)
{
    if(!n) return; //caso base el arbol es vacio o llegamos alf inal
    //accion del nodo actual, ejm cout << n->value;
    funcion(n->left); //lllamada recursiva para hijo izq
    funcion(n->right); // llmada recursiva para hijo  der
}
->Señales para usar recursividad:
1. ->tipo de ejercicio :Recorrer o imprimir todo el arbol ->señal: Recorrer, listar, mostrar, impirmir nodos ->que hacer: hacer recorrido preorden, inorder o postorden recursivo
2. ->tipo de ejercicio: Buscar una condicion en todo el arbol ->Señal o palabra clave:encontrar el valor mayor, buscar una hoja, ver si existe tal nodo ->que hacer: Recorrer recursivamente hasta hallarlo
3. ->tipo de ejercicio: Calcular algo de todos los nodos ->Señal o palabra clave:Suma de nodos, altura, nro de hojas, profundidad ->que hacer:combinar resultados de llamadas recursiva
4. ->tipo de ejercicio:Obtener solo una parte ->Señal o palabra clave: Borde izq/der, solo hojas, comino hasta un nodo->que hacer:aplicara la misma logica a subarboles y filtrar con if
5. ->tipo de ejercicio:estructuras anidadas ->Señal o palabra clave:nodo dentro de nodo, arbol dentro de arbol ->que hacer:usar recursion para procesar cada nvl
->recursion si o si 
preorden/inorder/postorden
borde izq/Der
hojas
altura/suma/contar nodos
->no recursion ndqvr
por niveles -> se hace con una cola no recursion


*/
class BST_E13 {
private:
    BinNode* root;
    vector<int> list_result;

    // TODO: Auxiliar para fill_list_left
    void collect_left_border(BinNode* n) {
        // TU CÓDIGO AQUÍ
        // Recorrer siempre por la izquierda
        if (!n) return;
        list_result.push_back(n->value);
        if (n->left) collect_left_border(n->left);
        if (n->right) collect_left_border(n->right);

    }

    // TODO: Auxiliar para fill_list_right
    void collect_right_border(BinNode* n) {
        // TU CÓDIGO AQUÍ
        // Recorrer siempre por la derecha
        if (!n) return;
        list_result.push_back(n->value);

        if (n->right) collect_right_border(n->right);
        if (n->left) collect_right_border(n->left);
    }

    // TODO: Auxiliar para fill_list_leaves
    void collect_leaves(BinNode* n) {
        // TU CÓDIGO AQUÍ
        // Detectar hojas (sin hijos) y agregarlas
        if (!n) return;
        if (!n->left && !n->right)
        {
            list_result.push_back(n->value);
            return;
        }
        collect_leaves(n->left);
        collect_leaves(n->right);
    }
public:
    BST_E13() : root(0) {}

    void insert(int x) {
        BinNode** p = &root;
        while (*p && (*p)->value != x) {
            if ((*p)->value < x) p = &((*p)->right);
            else p = &((*p)->left);
        }
        if (!*p) *p = new BinNode(x);
    }

    // TODO: fill_list_left - llenar lista con borde izquierdo
    void fill_list_left() {
        list_result.clear();
        collect_left_border(root);
        cout << "Borde izquierdo: ";
        // TU CÓDIGO AQUÍ
        for (int v : list_result) cout << v << " ";
        cout << "\n";
    }

    // TODO: fill_list_right - llenar lista con borde derecho
    void fill_list_right() {
        list_result.clear();
        cout << "Borde derecho: ";
        // TU CÓDIGO AQUÍ
        collect_right_border(root);
        for (int v : list_result) cout << v << " ";
        cout << "\n";
    }

    // TODO: fill_list_leaves - llenar lista con hojas
    void fill_list_leaves() {
        list_result.clear();
        cout << "Hojas: ";
        // TU CÓDIGO AQUÍ
        collect_leaves(root);
        for (int v : list_result) cout << v << " ";
        cout << "\n";
    }
};

/* ───────────────────────────────────────────────────────────────────────
   E14: PODAR ÁRBOL A ALTURA ESPECÍFICA

   PROBABILIDAD: 70% (del chat: "podar las hojas y ramas de tal forma que
   la altura en todos los subárboles sea la misma")
   TIEMPO: 45 minutos
   DIFICULTAD: ★★★☆☆
   ─────────────────────────────────────────────────────────────────────── */

class BST_E14 {
private:
    BinNode* root;

    int height_helper(BinNode* n) {
        if (!n) return 0;
        return 1 + max(height_helper(n->left), height_helper(n->right));
    }

    // TODO: Auxiliar para podar recursivamente
    void delete_subtree(BinNode* n)
    {
        if (!n) return;
        delete_subtree(n->left);//borra recursivamente todo el subarbolizq
        delete_subtree(n->right);//borra recursivamente todo el subarbol derecho
        delete n; //libera el nodo actual
    }
    void prune_helper(BinNode*& n, int curr_height, int max_height) {
        // TU CÓDIGO AQUÍ
        // Si curr_height > max_height, eliminar el nodo
        // Si no, seguir recursivamente con hijos
        
        
        if (!n) return;
        //si este nodo ya esta por debajo de la altura permitida
        //borrar todo el subarbol y dejar el puntero en 0
        if (curr_height > max_height)//si la altura actual del nodo supera el limite entonces este nodo y todo su subarbol se deben eliminar
        {
            delete_subtree(n); //borramos toda la estructura debajo de n
            n = 0; //nullptr, como n es BinNode*& (referencia a puntero), al asignar 0 (nullptr), estamos actualizando el puntwro en el padre para que deje de apuntar a memoria liberada 
            return;
        }
        //si todavia estamos dentro del limite, descendemos a los hijos
        //llamamos ants a los hijos para no perder referencias
        //sie curr_height > maax_height el nodo actual se conserva entonces debemos proceder a sus hijos
        prune_helper(n->left, curr_height+1, max_height); // se incrementa curr_height+1 al bajar un nvel
        prune_helper(n->right, curr_height+1, max_height);
    }

public:
    BST_E14() : root(0) {}

    void insert(int x) {
        BinNode** p = &root;
        while (*p && (*p)->value != x) {
            if ((*p)->value < x) p = &((*p)->right);
            else p = &((*p)->left);
        }
        if (!*p) *p = new BinNode(x);
    }

    // TODO: prune_to_height - podar árbol para que tenga altura máxima h
    void prune_to_height(int h) {
        // TU CÓDIGO AQUÍ
        cout << "Podando a altura " << h << "\n";
        if (h + 1)//caso especiall: no tiene sentido conservar la raiz si h < 1 (la raiz esta a altura 1 entonces eliminamos todo ela rbol)
        {
            delete_subtree(root);
            root = 0;
            return;
        }

        prune_helper(root, 1, h); //iniciamos la recursion en la raiz recorre el arbol y elimina subarboles por debajo de h
        
    }

    int height() { return height_helper(root); }
};

/* ───────────────────────────────────────────────────────────────────────
   E15: IMPRIMIR ÁRBOL POR NIVELES CON FORMATO

   PROBABILIDAD: 80% (del chat: "Imprimir un árbol por terminal con los
   niveles del árbol")
   TIEMPO: 1 hora
   DIFICULTAD: ★★★★☆
   ─────────────────────────────────────────────────────────────────────── */

class BST_E15 {
private:
    BinNode* root;

public:
    BST_E15() : root(0) {}

    void insert(int x) {
        BinNode** p = &root;
        while (*p && (*p)->value != x) {
            if ((*p)->value < x) p = &((*p)->right);
            else p = &((*p)->left);
        }
        if (!*p) *p = new BinNode(x);
    }

    // TODO: print_by_levels - cada nivel en una línea
    void print_by_levels() {
        if (!root) return;
        cout << "Árbol por niveles:\n";

        // TU CÓDIGO AQUÍ
        // Usa queue<BinNode*> para BFS
        // Cuenta elementos en cada nivel
    }

    // TODO: print_with_null - mostrar "null" para espacios vacíos
    void print_with_null() {
        if (!root) return;
        cout << "Con nulls:\n";

        // TU CÓDIGO AQUÍ
        // Agrega nulls a la queue para mantener estructura completa
    }

    // TODO: print_zigzag - niveles alternando izq-der, der-izq
    void print_zigzag() {
        if (!root) return;
        cout << "Zigzag:\n";

        // TU CÓDIGO AQUÍ
        // Usa un flag bool para alternar dirección
        // Guarda cada nivel en vector y invierte si es necesario
    }

    // TODO: level_sums - suma de cada nivel
    void level_sums() {
        if (!root) return;
        cout << "Sumas por nivel:\n";

        // TU CÓDIGO AQUÍ
    }

    // TODO: max_width - número máximo de nodos en cualquier nivel
    int max_width() {
        // TU CÓDIGO AQUÍ
        return 0;
    }
};

/* ═══════════════════════════════════════════════════════════════════════
   🟡 NIVEL 6: COMPLEJIDAD ALGORÍTMICA
   ═══════════════════════════════════════════════════════════════════════ */

   /* ───────────────────────────────────────────────────────────────────────
      E16: IDENTIFICAR Y OPTIMIZAR COMPLEJIDAD

      PROBABILIDAD: 70% (mencionaste: "puede pedir con algún tipo de orden")
      TIEMPO: 1 hora
      DIFICULTAD: ★★★☆☆
      ─────────────────────────────────────────────────────────────────────── */

class ComplejidadEjercicios_E16 {
public:

    // EJERCICIO A: Identifica la complejidad de estas funciones

    void funcionA(int n) {
        for (int i = 0; i < n; i++)
            cout << i << " ";
    }
    // Complejidad: _____ (escribe tu respuesta)

    void funcionB(int n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cout << i * j << " ";
    }
    // Complejidad: _____

    void funcionC(int n) {
        for (int i = 1; i < n; i *= 2)
            cout << i << " ";
    }
    // Complejidad: _____

    void funcionD(int n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++)
                cout << j << " ";
    }
    // Complejidad: _____

    int binary_search(vector<int>& arr, int x) {
        int left = 0, right = arr.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == x) return mid;
            if (arr[mid] < x) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
    // Complejidad: _____

    // EJERCICIO B: Optimiza esta función de O(n³) a O(n²)
    int sum_subarrays_slow(vector<int>& arr) {
        int n = arr.size();
        int total = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int subsum = 0;
                for (int k = i; k <= j; k++) {  // Este loop es innecesario
                    subsum += arr[k];
                }
                total += subsum;
            }
        }
        return total;
    }

    // TODO: Implementa versión O(n²)
    int sum_subarrays_fast(vector<int>& arr) {
        // TU CÓDIGO AQUÍ
        // HINT: Mantén suma acumulativa en el loop j
        return 0;
    }

    // EJERCICIO C: Implementa estos métodos con la complejidad indicada

    // TODO: Encontrar máximo en O(n)
    int find_max(vector<int>& arr) {
        // TU CÓDIGO AQUÍ
        return 0;
    }

    // TODO: Buscar en array ORDENADO en O(log n)
    bool binary_search_impl(vector<int>& arr, int x) {
        // TU CÓDIGO AQUÍ - implementa binary search
        return false;
    }

    // TODO: Verificar si hay duplicados en O(n²)
    bool has_duplicates(vector<int>& arr) {
        // TU CÓDIGO AQUÍ
        return false;
    }
};

/* ═══════════════════════════════════════════════════════════════════════
   🔴 SIMULACROS DE EXAMEN FINAL
   ═══════════════════════════════════════════════════════════════════════ */

   /* ───────────────────────────────────────────────────────────────────────
      SIMULACRO 1: EXAMEN TIPO A

      TIEMPO LÍMITE: 90 MINUTOS
      PROBLEMAS: 3
      PUNTOS: 100 (distribuidos: 30-35-35)

      INSTRUCCIONES:
      - Resuelve en orden
      - No mires las soluciones hasta terminar los 3
      - Simula presión de tiempo
      ─────────────────────────────────────────────────────────────────────── */

namespace SimulacroA {

    // PROBLEMA 1 (30 puntos): Lista enlazada - método partition
    struct Node {
        int data;
        Node* next;
        Node(int d) : data(d), next(0) {}
    };

    class Lista_S1 {
    private:
        Node* head;
    public:
        Lista_S1() : head(0) {}

        void push_back(int x) {
            if (!head) { head = new Node(x); return; }
            Node* curr = head;
            while (curr->next) curr = curr->next;
            curr->next = new Node(x);
        }

        // TODO: Implementar partition(int x)
        // Reorganizar: elementos < x a la izquierda, >= x a la derecha
        // Debe ser O(n) y mantener orden relativo
        void partition(int x) {
            // TU CÓDIGO AQUÍ (15 minutos máximo)
        }

        void print() {
            for (Node* p = head; p; p = p->next)
                cout << p->data << " ";
            cout << "\n";
        }
    };

    // PROBLEMA 2 (35 puntos): Priority Queue con dos stacks
    // Implementar una priority queue usando DOS std::stack
    class PriorityQueue_S1 {
    private:
        stack<int> s1;  // Stack principal
        stack<int> s2;  // Stack auxiliar

    public:
        // TODO: push - insertar elemento manteniendo orden (menor en tope)
        void push(int x) {
            // TU CÓDIGO AQUÍ (20 minutos máximo)
        }

        // TODO: pop - eliminar el menor elemento
        void pop() {
            // TU CÓDIGO AQUÍ
        }

        // TODO: top - ver el menor sin eliminar
        int top() {
            // TU CÓDIGO AQUÍ
            return 0;
        }

        bool empty() { return s1.empty(); }
    };

    // PROBLEMA 3 (35 puntos): Árbol - encontrar camino a nodo
    class BST_S1 {
    private:
        BinNode* root;

        // TODO: Auxiliar recursivo para encontrar camino
        bool find_path_helper(BinNode* n, int target, vector<int>& path) {
            // TU CÓDIGO AQUÍ
            return false;
        }

    public:
        BST_S1() : root(0) {}

        void insert(int x) {
            BinNode** p = &root;
            while (*p && (*p)->value != x) {
                if ((*p)->value < x) p = &((*p)->right);
                else p = &((*p)->left);
            }
            if (!*p) *p = new BinNode(x);
        }

        // TODO: find_path - retornar camino desde raíz hasta nodo con valor x
        // Ejemplo: árbol con raíz 50, buscar 20 => [50, 30, 20]
        vector<int> find_path(int x) {
            vector<int> path;
            // TU CÓDIGO AQUÍ (20 minutos máximo)
            return path;
        }
    };

} // namespace SimulacroA

/* ───────────────────────────────────────────────────────────────────────
   SIMULACRO 2: EXAMEN TIPO B

   TIEMPO LÍMITE: 90 MINUTOS
   PROBLEMAS: 3
   PUNTOS: 100 (distribuidos: 35-30-35)
   ─────────────────────────────────────────────────────────────────────── */

namespace SimulacroB {

    // PROBLEMA 1 (35 puntos): Deque con lista doble - rotate
    struct NodeDL2 {
        int data;
        NodeDL2* next, * prev;
        NodeDL2(int d) : data(d), next(0), prev(0) {}
    };

    class Deque_S2 {
    private:
        NodeDL2* head, * tail;
        int size;

    public:
        Deque_S2() : head(0), tail(0), size(0) {}

        void push_back(int x) {
            NodeDL2* n = new NodeDL2(x);
            if (!tail) { head = tail = n; }
            else { tail->next = n; n->prev = tail; tail = n; }
            size++;
        }

        // TODO: rotate_left(int k) - rotar k posiciones a la izquierda
        // Ejemplo: [1,2,3,4,5] rotate_left(2) => [3,4,5,1,2]
        void rotate_left(int k) {
            // TU CÓDIGO AQUÍ (20 minutos máximo)
        }

        // TODO: is_palindrome() - verificar si el deque es palíndromo
        bool is_palindrome() {
            // TU CÓDIGO AQUÍ (15 minutos máximo)
            return false;
        }

        void print() {
            NodeDL2* curr = head;
            while (curr) {
                cout << curr->data << " ";
                curr = curr->next;
            }
            cout << "\n";
        }
    };

    // PROBLEMA 2 (30 puntos): Merge K sorted lists
    class MergeLists_S2 {
    public:
        struct Node {
            int data;
            Node* next;
            Node(int d) : data(d), next(0) {}
        };

        // TODO: merge_k_lists - fusionar k listas ordenadas en una sola
        // Input: vector de k listas enlazadas ordenadas
        // Output: una lista ordenada con todos los elementos
        Node* merge_k_lists(vector<Node*>& lists) {
            // TU CÓDIGO AQUÍ (30 minutos máximo)
            // HINT: Usa una priority_queue o merge de a dos
            return 0;
        }
    };

    // PROBLEMA 3 (35 puntos): Árbol - nivel con suma máxima
    class BST_S2 {
    private:
        BinNode* root;

    public:
        BST_S2() : root(0) {}

        void insert(int x) {
            BinNode** p = &root;
            while (*p && (*p)->value != x) {
                if ((*p)->value < x) p = &((*p)->right);
                else p = &((*p)->left);
            }
            if (!*p) *p = new BinNode(x);
        }

        // TODO: max_sum_level - retornar el nivel con suma máxima
        // También imprimir la suma
        // Ejemplo: Nivel 0: suma=50, Nivel 1: suma=80, Nivel 2: suma=100
        // Retorna: 2 (e imprime "Nivel 2: 100")
        int max_sum_level() {
            // TU CÓDIGO AQUÍ (20 minutos máximo)
            return 0;
        }

        // TODO: count_nodes_at_level - contar nodos en nivel específico
        int count_nodes_at_level(int target_level) {
            // TU CÓDIGO AQUÍ (15 minutos máximo)
            return 0;
        }
    };

} // namespace SimulacroB

/* ═══════════════════════════════════════════════════════════════════════
   📊 PLAN DE ESTUDIO DETALLADO - CRONOGRAMA
   ═══════════════════════════════════════════════════════════════════════

   DÍA 1 - SÁBADO (10-12 HORAS)
   ────────────────────────────────────────────────────────────────────

   MAÑANA (08:00 - 13:00) - 5 HORAS
   ├─ 08:00-08:30 │ E1: Destructores (CRÍTICO) ★★★★★
   ├─ 08:30-10:00 │ E2: Punteros a punteros ★★★★★
   ├─ 10:00-10:45 │ E3: Lista ordenada sin repetición ★★★★☆
   ├─ 10:45-11:15 │ E4: Stack adapter ★★★☆☆
   └─ 11:15-13:00 │ E5: split_list() ★★★★★ EXAMEN ANTERIOR

   TARDE (15:00 - 20:00) - 5 HORAS
   ├─ 15:00-16:00 │ E6: CSortedQueue ★★★★★ EXAMEN ANTERIOR
   ├─ 16:00-17:00 │ E7: kneighbors() ★★★★★ EXAMEN ANTERIOR
   ├─ 17:00-18:30 │ E8: Lista circular ★★★★☆
   ├─ 18:30-20:00 │ E9: Deque en bloques ★★★★★

   NOCHE (20:30 - 22:00) - 1.5 HORAS
   └─ 20:30-22:00 │ E10: Lista doble completa (repaso) ★★★☆☆

   DÍA 2 - DOMINGO (8-10 HORAS)
   ────────────────────────────────────────────────────────────────────

   MAÑANA (08:00 - 13:00) - 5 HORAS
   ├─ 08:00-09:00 │ E11: Stack de queues ★★★☆☆
   ├─ 09:00-10:00 │ E12: Deque de stacks ★★★☆☆
   ├─ 10:00-11:00 │ E13: fill_list (left/right/leaves) ★★★☆☆
   ├─ 11:00-11:45 │ E14: Podar árbol ★★★☆☆
   └─ 11:45-13:00 │ E15: Imprimir por niveles ★★★★☆

   TARDE (15:00 - 19:00) - 4 HORAS
   ├─ 15:00-16:00 │ E16: Complejidad algorítmica ★★★☆☆
   ├─ 16:00-17:30 │ SIMULACRO A (90 min) ★★★★★
   └─ 17:30-19:00 │ SIMULACRO B (90 min) ★★★★★

   NOCHE (19:30 - 21:00) - 1.5 HORAS
   └─ 19:30-21:00 │ Revisar errores de simulacros
                   │ Repasar conceptos débiles
                   │ Dormir temprano para examen

   ═══════════════════════════════════════════════════════════════════════

   🎯 PROBABILIDADES DE QUE VENGA EN EL EXAMEN:

   100% SEGURO (haz esto SÍ o SÍ):
   ✓ E1: Destructores correctos
   ✓ E5: split_list() o similar
   ✓ E6: CSortedQueue o similar
   ✓ E7: kneighbors() o similar

   90-95% PROBABLE:
   ✓ E2: Punteros a punteros
   ✓ E10: Lista doble completa
   ✓ E15: Imprimir árbol por niveles

   70-80% PROBABLE:
   ✓ E3: Lista ordenada
   ✓ E8: Lista circular
   ✓ E13: fill_list variantes
   ✓ E14: Podar árbol
   ✓ E16: Complejidad

   60-70% POSIBLE:
   ✓ E9: Deque en bloques
   ✓ E11-E12: Estructuras híbridas

   ═══════════════════════════════════════════════════════════════════════

   💡 CONSEJOS FINALES PARA SACAR 100/100:

   1. GESTIÓN DE MEMORIA es lo MÁS IMPORTANTE
      - Destructor mal = -10 a -15 puntos automáticos
      - Siempre libera memoria con delete

   2. PUNTEROS A PUNTEROS
      - El profesor los usa en TODOS sus ejemplos
      - Practica hasta que sea natural

   3. NO REINVENTES LA RUEDA
      - Si el profesor usa una técnica, úsala igual
      - SLinkedList_E5 {
private:
    NodeDL *head, *tail;

public:
    DoublyLinkedList_E5() : head(0), tail(0) {}

    ~DoublyLinkedList_E5() {
        // TODO: Destructor correcto
    }

    void push_back(int x) {
        NodeDL* n = new NodeDL(x);
        if (!tail) { head = tail = n; return; }
        tail->next = n; n->prev = tail; tail = n;
    }

    NodeDL* get_head() { return head; }
    NodeDL* get_tail() { return tail; }

    // TODO: IMPLEMENTAR split_list (EL MÁS IMPORTANTE)
    void split_list(NodeDL* pivot) {
        if (!pivot || !head) return;

        // TU CÓDIGO AQUÍ
        // ESTRATEGIA:
        // 1. Crear tres grupos: menores, pivot, mayores
        // 2. Recorrer la lista y clasificar cada nodo
        // 3. Reconectar: menores -> pivot -> mayores
        // 4. Actualizar head y tail

        // PISTAS:
        // - Usa punteros less_head, less_tail, greater_head, greater_tail
        // - Desconecta el pivot de la lista original
        // - Recorre todos los nodos (except pivot)
        // - Clasifica cada nodo según: node->data < pivot->data
        // - Reconecta todo al final
    }

    void print() {
        NodeDL* curr = head;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << "\n";
    }
};

/* ───────────────────────────────────────────────────────────────────────
   E6: CSortedQueue - Cola Ordenada con UNA sola std::queue

   PROBABILIDAD: 100% (VINO EN EXAMEN ANTERIOR + es del tipo que le gusta)
   TIEMPO: 1 hora
   DIFICULTAD: ★★★★☆

   RESTRICCIONES CRÍTICAS (del PDF):
   - Solo UNA instancia de std::queue
   - NO otras estructuras (vector, list, etc.)
   - Puedes usar variables int y funciones auxiliares
   ─────────────────────────────────────────────────────────────────────── */

class CSortedQueue_E6 {
public:
    queue<int> q;  // SOLO esta queue permitida

    // TODO: pushx - insertar manteniendo orden O(n)
    void pushx(int x) {
        // TU CÓDIGO AQUÍ
        // ESTRATEGIA:
        // 1. Si vacía, solo push
        // 2. Sacar elementos menores que x
        // 3. Push de x
        // 4. Reinsertar elementos sacados
        // HINT: Usa q.size() como contador para no hacer loop infinito
    }

    // TODO: popx - eliminar el menor (frente)
    void popx() {
        // TU CÓDIGO AQUÍ
    }

    // TODO: frontx - retornar el menor
    int frontx() {
        // TU CÓDIGO AQUÍ
        return 0;
    }

    // TODO: remx - eliminar TODAS las ocurrencias de x
    void remx(int x) {
        // TU CÓDIGO AQUÍ
        // ESTRATEGIA:
        // 1. Guardar tamaño original
        // 2. Hacer size veces: sacar, si NO es x reinsertar
    }

    // TODO: printx - imprimir sin destruir la queue
    void printx() {
        // TU CÓDIGO AQUÍ
        // ESTRATEGIA:
        // Sacar cada elemento, imprimirlo, y reinsertarlo
    }
};

/* ───────────────────────────────────────────────────────────────────────
   E7: kneighbors() - K Vecinos Más Cercanos en BST

   PROBABILIDAD: 90% (VINO EN EXAMEN ANTERIOR)
   TIEMPO: 1 hora
   DIFICULTAD: ★★★★☆

   EJEMPLOS DEL PDF:
   (33,4) => 33 36 41 44
   (88,3) => 77 80 88 99
   (76,2) => 77 80
   ─────────────────────────────────────────────────────────────────────── */

struct BinNode {
    int value;
    BinNode* left, * right;
    BinNode(int v) : value(v), left(0), right(0) {}
};

class CBinTree_E7 {
private:
    BinNode* root;

    void inorder(BinNode* n, vector<int>& vals) {
        if (!n) return;
        inorder(n->left, vals);
        vals.push_back(n->value);
        inorder(n->right, vals);
    }

public:
    CBinTree_E7() : root(0) {}

    void Insert(int x) {
        BinNode** p = &root;
        while (*p && (*p)->value != x) {
            if ((*p)->value < x) p = &((*p)->right);
            else p = &((*p)->left);
        }
        if (!*p) *p = new BinNode(x);
    }

    // TODO: IMPLEMENTAR kneighbors
    void kneighbors(int x, int k) {
        cout << "(" << x << "," << k << ") => ";

        // TU CÓDIGO AQUÍ
        // ESTRATEGIA:
        // 1. Obtener todos los valores en inorder (quedan ordenados)
        // 2. Para cada valor, calcular distancia absoluta a x
        // 3. Guardar pares {distancia, valor}
        // 4. Ordenar por distancia
        // 5. Tomar los k primeros
        // 6. Ordenar esos k por valor
        // 7. Imprimir

        // HINT: Usa vector<pair<int,int>> para {distancia, valor}
        // HINT: abs(val - x) para calcular distancia

        cout << "\n";
    }

    void Print() {
        vector<int> vals;
        inorder(root, vals);
        for (int v : vals) cout << v << " ";
        cout << "\n";
    }
};

/* ═══════════════════════════════════════════════════════════════════════
   🟡 NIVEL 3: ESTRUCTURAS NO VISTAS EN CLASE
   ═══════════════════════════════════════════════════════════════════════ */

   /* ───────────────────────────────────────────────────────────────────────
      E8: LISTA CIRCULAR COMPLETA

      PROBABILIDAD: 75% (mencionaste que "solo explicó, no implementamos")
      TIEMPO: 1.5 horas
      DIFICULTAD: ★★★★☆

      El profesor puede pedir esto porque "no lo vieron" = perfecto para examen
      ─────────────────────────────────────────────────────────────────────── */

struct NodeCircular {
    int data;
    NodeCircular* next;
    NodeCircular(int d) : data(d), next(0) {}
};

class CircularList_E8 {
private:
    NodeCircular* head;
    int size;

public:
    CircularList_E8() : head(0), size(0) {}

    ~CircularList_E8() {
        // TODO: Destructor para lista circular (cuidado con loops infinitos!)
    }

    // TODO: push_back en lista circular
    void push_back(int x) {
        // TU CÓDIGO AQUÍ
        // PISTA: El último nodo debe apuntar a head
    }

    // TODO: push_front en lista circular
    void push_front(int x) {
        // TU CÓDIGO AQUÍ
    }

    // TODO: rotate_right - rotar k posiciones a la derecha
    // Ejemplo: 1->2->3->4->5 con k=2 => 4->5->1->2->3
    void rotate_right(int k) {
        // TU CÓDIGO AQUÍ
    }

    // TODO: split_by_value - dividir en dos listas circulares
    // menores que x en una lista, mayores en otra
    void split_by_value(int x, CircularList_E8& other) {
        // TU CÓDIGO AQUÍ
    }

    void print(int max_iter = 20) {
        if (!head) { cout << "Empty\n"; return; }
        NodeCircular* curr = head;
        int count = 0;
        do {
            cout << curr->data << " ";
            curr = curr->next;
            count++;
        } while (curr != head && count < max_iter);
        cout << "\n";
    }
};

/* ───────────────────────────────────────────────────────────────────────
   E9: DEQUE EN BLOQUES (como std::deque)

   PROBABILIDAD: 70% ("no implementamos en clase")
   TIEMPO: 2 horas
   DIFICULTAD: ★★★★★

   Esta es DIFÍCIL pero el profesor la tiene en el PDF.
   Si viene, vale muchos puntos.
   ─────────────────────────────────────────────────────────────────────── */

class CDeque_E9 {
private:
    static const int MAP_SIZE = 11;
    static const int BLOCK_SIZE = 11;

    int** mapa;
    int** M_INI;
    int** M_FIN;
    int* V_INI;
    int* V_FIN;

public:
    CDeque_E9() {
        mapa = new int* [MAP_SIZE];
        for (int i = 0; i < MAP_SIZE; i++) mapa[i] = 0;
        M_INI = mapa + MAP_SIZE / 2;
        M_FIN = M_INI;
        V_INI = V_FIN = 0;
    }

    ~CDeque_E9() {
        // TODO: Liberar todos los bloques
        for (int** p = M_INI; p <= M_FIN; p++) {
            if (*p) delete[] * p;
        }
        delete[] mapa;
    }

    // TODO: push_front - agregar al inicio
    void push_front(int n) {
        // TU CÓDIGO AQUÍ (ver PDF para implementación)
    }

    // TODO: push_back - agregar al final
    void push_back(int n) {
        // TU CÓDIGO AQUÍ
    }

    // TODO: pop_front - eliminar del inicio
    int pop_front() {
        // TU CÓDIGO AQUÍ
        return -1;
    }

    // TODO: pop_back - eliminar del final
    int pop_back() {
        // TU CÓDIGO AQUÍ
        return -1;
    }

    // TODO: operator[] - acceso aleatorio O(1)
    int& operator[](int idx) {
        // TU CÓDIGO AQUÍ
        // FÓRMULA: 
        // elem_antes = V_INI - *M_INI
        // pos_global = idx + elem_antes
        // bloque = pos_global / BLOCK_SIZE
        // pos = pos_global % BLOCK_SIZE
        // return *(*(M_INI + bloque) + pos)
        static int dummy = -1;
        return dummy;
    }

    // TODO: size() - calcular tamaño total
    int size() {
        // TU CÓDIGO AQUÍ
        return 0;
    }
};
/* ───────────────────────────────────────────────────────────────────────
   E10: LISTA DOBLEMENTE ENLAZADA COMPLETA (Repaso General)

   PROBABILIDAD: 85% (puede pedir crear desde cero)
   TIEMPO: 1 hora
   DIFICULTAD: ★★★☆☆
   ─────────────────────────────────────────────────────────────────────── */

class DoublyList_E10 {
private:
    NodeDL* head, * tail;
    int size;

public:
    DoublyList_E10() : head(0), tail(0), size(0) {}

    ~DoublyList_E10() {
        // TODO: Destructor correcto
        while (head) {
            NodeDL* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // TODO: Implementar TODOS estos métodos
    void push_front(int x) {
        NodeDL* n = new NodeDL(x);
        if (!head) {
            head = tail = n;
        }
        else {
            n->next = head;
            head->prev = n;
            head = n;
        }
        size++;
    }

    void push_back(int x) {
        NodeDL* n = new NodeDL(x);
        if (!tail) {
            head = tail = n;
        }
        else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        size++;
    }

    void pop_front() {
        if (!head) return;
        NodeDL* temp = head;
        head = head->next;
        if (head) head->prev = 0;
        else tail = 0;
        delete temp;
        size--;
    }

    void pop_back() {
        if (!tail) return;
        NodeDL* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = 0;
        else head = 0;
        delete temp;
        size--;
    }

    void insert_at(int pos, int x) {
        if (pos <= 0) { push_front(x); return; }
        if (pos >= size) { push_back(x); return; }

        NodeDL* curr = head;
        for (int i = 0; i < pos; i++)
            curr = curr->next;

        NodeDL* n = new NodeDL(x);
        n->prev = curr->prev;
        n->next = curr;
        curr->prev->next = n;
        curr->prev = n;
        size++;
    }

    void remove_at(int pos) {
        if (pos < 0 || pos >= size) return;
        if (pos == 0) { pop_front(); return; }
        if (pos == size - 1) { pop_back(); return; }

        NodeDL* curr = head;
        for (int i = 0; i < pos; i++)
            curr = curr->next;

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        size--;
    }

    NodeDL* find(int x) {
        NodeDL* curr = head;
        while (curr) {
            if (curr->data == x) return curr;
            curr = curr->next;
        }
        return 0;
    }

    void reverse() {
        if (!head || !head->next) return;
        NodeDL* left = head;
        NodeDL* right = tail;
        while (left != right && left->prev != right) {
            swap(left->data, right->data);
            left = left->next;
            right = right->prev;
        }
    }

    void sort() {
        if (!head || !head->next) return;
        for (int i = 0; i < size - 1; i++) {
            NodeDL* curr = head;
            for (int j = 0; j < size - i - 1; j++) {
                if (curr->data > curr->next->data)
                    swap(curr->data, curr->next->data);
                curr = curr->next;
            }
        }
    }

    // TODO: merge - fusionar con otra lista ordenada SIN crear nueva lista
    void merge(DoublyList_E10& other) {
        if (!other.head) return;

        NodeDL* p1 = head;
        NodeDL* p2 = other.head;
        NodeDL* newHead = 0;
        NodeDL* newTail = 0;

        while (p1 && p2) {
            NodeDL* toAdd;
            if (p1->data <= p2->data) {
                toAdd = p1;
                p1 = p1->next;
            }
            else {
                toAdd = p2;
                p2 = p2->next;
            }

            if (!newHead) {
                newHead = newTail = toAdd;
                toAdd->prev = 0;
            }
            else {
                newTail->next = toAdd;
                toAdd->prev = newTail;
                newTail = toAdd;
            }
        }

        if (p1) {
            newTail->next = p1;
            p1->prev = newTail;
            tail = this->tail;
        }
        if (p2) {
            newTail->next = p2;
            p2->prev = newTail;
            tail = other.tail;
        }

        head = newHead;
        size += other.size;
        other.head = other.tail = 0;
        other.size = 0;
    }

    void print() {
        NodeDL* curr = head;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << "\n";
    }
};

/* ═══════════════════════════════════════════════════════════════════════
   🟡 NIVEL 4: ESTRUCTURAS HÍBRIDAS (con STL)
   ═══════════════════════════════════════════════════════════════════════ */

   /* ───────────────────────────────────────────────────────────────────────
      E11: STACK DE QUEUES

      PROBABILIDAD: 60% (mencionaste: "puede pedir de dos estructuras juntas")
      TIEMPO: 1 hora
      DIFICULTAD: ★★★☆☆
      ─────────────────────────────────────────────────────────────────────── */

struct StackNodeQ {
    queue<int> data;
    StackNodeQ* next;
    StackNodeQ() : next(0) {}
};

class StackOfQueues_E11 {
private:
    StackNodeQ* top;

public:
    StackOfQueues_E11() : top(0) {}

    ~StackOfQueues_E11() {
        while (top) {
            StackNodeQ* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push_queue() {
        StackNodeQ* n = new StackNodeQ();
        n->next = top;
        top = n;
    }

    void pop_queue() {
        if (!top) return;
        StackNodeQ* temp = top;
        top = top->next;
        delete temp;
    }

    void enqueue_top(int x) {
        if (!top) push_queue();
        top->data.push(x);
    }

    int dequeue_top() {
        if (!top || top->data.empty()) return -1;
        int val = top->data.front();
        top->data.pop();
        return val;
    }

    void transfer_to_next() {
        if (!top || !top->next) return;
        while (!top->data.empty()) {
            top->next->data.push(top->data.front());
            top->data.pop();
        }
    }

    queue<int> flatten() {
        queue<int> result;
        StackNodeQ* curr = top;
        while (curr) {
            queue<int> temp = curr->data;
            while (!temp.empty()) {
                result.push(temp.front());
                temp.pop();
            }
            curr = curr->next;
        }
        return result;
    }

    void print_all() {
        if (!top) { cout << "Empty\n"; return; }
        StackNodeQ* curr = top;
        int level = 0;
        cout << "Stack (top->bottom):\n";
        while (curr) {
            cout << "  Queue[" << level << "]: ";
            queue<int> temp = curr->data;
            while (!temp.empty()) {
                cout << temp.front() << " ";
                temp.pop();
            }
            cout << "\n";
            curr = curr->next;
            level++;
        }
    }
};

/* ───────────────────────────────────────────────────────────────────────
   E12: DEQUE DE STACKS
   ─────────────────────────────────────────────────────────────────────── */

struct DequeNodeS {
    stack<int> data;
    DequeNodeS* next, * prev;
    DequeNodeS() : next(0), prev(0) {}
};

class DequeOfStacks_E12 {
private:
    DequeNodeS* head, * tail;

public:
    DequeOfStacks_E12() : head(0), tail(0) {}

    ~DequeOfStacks_E12() {
        while (head) {
            DequeNodeS* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_front_stack() {
        DequeNodeS* n = new DequeNodeS();
        if (!head) {
            head = tail = n;
        }
        else {
            n->next = head;
            head->prev = n;
            head = n;
        }
    }

    void push_back_stack() {
        DequeNodeS* n = new DequeNodeS();
        if (!tail) {
            head = tail = n;
        }
        else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }

    void push_to_front_stack(int x) {
        if (!head) push_front_stack();
        head->data.push(x);
    }

    void push_to_back_stack(int x) {
        if (!tail) push_back_stack();
        tail->data.push(x);
    }

    int pop_from_front_stack() {
        if (!head || head->data.empty()) return -1;
        int val = head->data.top();
        head->data.pop();
        return val;
    }

    int pop_from_back_stack() {
        if (!tail || tail->data.empty()) return -1;
        int val = tail->data.top();
        tail->data.pop();
        return val;
    }

    void balance() {
        // Redistribuir elementos
        int total = 0;
        int count = 0;

        DequeNodeS* curr = head;
        while (curr) {
            total += curr->data.size();
            count++;
            curr = curr->next;
        }

        if (count == 0) return;
        int target = total / count;

        // Extraer todos
        int* arr = new int[total];
        int idx = 0;
        curr = head;
        while (curr) {
            while (!curr->data.empty()) {
                arr[idx++] = curr->data.top();
                curr->data.pop();
            }
            curr = curr->next;
        }

        // Redistribuir
        idx = 0;
        curr = head;
        while (curr && idx < total) {
            int cnt = (curr->next) ? target : (total - idx);
            for (int i = 0; i < cnt && idx < total; i++) {
                curr->data.push(arr[idx++]);
            }
            curr = curr->next;
        }

        delete[] arr;
    }
};

/* ═══════════════════════════════════════════════════════════════════════
   🟡 NIVEL 5: ÁRBOLES AVANZADOS
   ═══════════════════════════════════════════════════════════════════════ */

   /* ───────────────────────────────────────────────────────────────────────
      E13: fill_list - Llenar listas desde árbol
      ─────────────────────────────────────────────────────────────────────── */

class BST_E13 {
private:
    BinNode* root;
    vector<int> list_result;

    void collect_left_border(BinNode* n) {
        if (!n) return;
        list_result.push_back(n->value);
        collect_left_border(n->left);
    }

    void collect_right_border(BinNode* n) {
        if (!n) return;
        list_result.push_back(n->value);
        collect_right_border(n->right);
    }

    void collect_leaves(BinNode* n) {
        if (!n) return;
        if (!n->left && !n->right) {
            list_result.push_back(n->value);
            return;
        }
        collect_leaves(n->left);
        collect_leaves(n->right);
    }

public:
    BST_E13() : root(0) {}

    void insert(int x) {
        BinNode** p = &root;
        while (*p && (*p)->value != x) {
            if ((*p)->value < x) p = &((*p)->right);
            else p = &((*p)->left);
        }
        if (!*p) *p = new BinNode(x);
    }

    void fill_list_left() {
        list_result.clear();
        cout << "Borde izquierdo: ";
        collect_left_border(root);
        for (int v : list_result) cout << v << " ";
        cout << "\n";
    }

    void fill_list_right() {
        list_result.clear();
        cout << "Borde derecho: ";
        collect_right_border(root);
        for (int v : list_result) cout << v << " ";
        cout << "\n";
    }

    void fill_list_leaves() {
        list_result.clear();
        cout << "Hojas: ";
        collect_leaves(root);
        for (int v : list_result) cout << v << " ";
        cout << "\n";
    }
};

/* ───────────────────────────────────────────────────────────────────────
   E14: PODAR ÁRBOL A ALTURA ESPECÍFICA
   ─────────────────────────────────────────────────────────────────────── */

class BST_E14 {
private:
    BinNode* root;

    int height_helper(BinNode* n) {
        if (!n) return 0;
        return 1 + max(height_helper(n->left), height_helper(n->right));
    }

    void prune_helper(BinNode*& n, int curr_height, int max_height) {
        if (!n) return;
        if (curr_height > max_height) {
            delete n;
            n = 0;
            return;
        }
        prune_helper(n->left, curr_height + 1, max_height);
        prune_helper(n->right, curr_height + 1, max_height);
    }

public:
    BST_E14() : root(0) {}

    void insert(int x) {
        BinNode** p = &root;
        while (*p && (*p)->value != x) {
            if ((*p)->value < x) p = &((*p)->right);
            else p = &((*p)->left);
        }
        if (!*p) *p = new BinNode(x);
    }

    void prune_to_height(int h) {
        cout << "Podando a altura " << h << "\n";
        prune_helper(root, 1, h);
    }

    int height() { return height_helper(root); }
};

/* ───────────────────────────────────────────────────────────────────────
   E15: IMPRIMIR ÁRBOL POR NIVELES CON FORMATO
   ─────────────────────────────────────────────────────────────────────── */

class BST_E15 {
private:
    BinNode* root;

public:
    BST_E15() : root(0) {}

    void insert(int x) {
        BinNode** p = &root;
        while (*p && (*p)->value != x) {
            if ((*p)->value < x) p = &((*p)->right);
            else p = &((*p)->left);
        }
        if (!*p) *p = new BinNode(x);
    }

    void print_by_levels() {
        if (!root) return;
        cout << "Árbol por niveles:\n";
        queue<BinNode*> q;
        q.push(root);
        int level = 0;

        while (!q.empty()) {
            int size = q.size();
            cout << "Nivel " << level << ": ";
            for (int i = 0; i < size; i++) {
                BinNode* curr = q.front();
                q.pop();
                cout << curr->value << " ";
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            cout << "\n";
            level++;
        }
    }

    void print_zigzag() {
        if (!root) return;
        cout << "Zigzag:\n";
        queue<BinNode*> q;
        q.push(root);
        bool left_to_right = true;
        int level = 0;

        while (!q.empty()) {
            int size = q.size();
            vector<int> level_vals;

            for (int i = 0; i < size; i++) {
                BinNode* curr = q.front();
                q.pop();
                level_vals.push_back(curr->value);
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }

            cout << "Nivel " << level << ": ";
            if (left_to_right) {
                for (int v : level_vals) cout << v << " ";
            }
            else {
                for (int i = level_vals.size() - 1; i >= 0; i--)
                    cout << level_vals[i] << " ";
            }
            cout << "\n";
            left_to_right = !left_to_right;
            level++;
        }
    }

    void level_sums() {
        if (!root) return;
        cout << "Sumas por nivel:\n";
        queue<BinNode*> q;
        q.push(root);
        int level = 0;

        while (!q.empty()) {
            int size = q.size();
            int sum = 0;
            for (int i = 0; i < size; i++) {
                BinNode* curr = q.front();
                q.pop();
                sum += curr->value;
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            cout << "Nivel " << level << ": " << sum << "\n";
            level++;
        }
    }

    int max_width() {
        if (!root) return 0;
        queue<BinNode*> q;
        q.push(root);
        int max_w = 0;

        while (!q.empty()) {
            int size = q.size();
            max_w = max(max_w, size);
            for (int i = 0; i < size; i++) {
                BinNode* curr = q.front();
                q.pop();
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
        return max_w;
    }
};

/* ═══════════════════════════════════════════════════════════════════════
   🟡 NIVEL 6: COMPLEJIDAD ALGORÍTMICA
   ═══════════════════════════════════════════════════════════════════════ */

class ComplejidadEjercicios_E16 {
public:
    // Complejidad: O(n)
    void funcionA(int n) {
        for (int i = 0; i < n; i++)
            cout << i << " ";
    }

    // Complejidad: O(n²)
    void funcionB(int n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cout << i * j << " ";
    }

    // Complejidad: O(log n)
    void funcionC(int n) {
        for (int i = 1; i < n; i *= 2)
            cout << i << " ";
    }

    // Complejidad: O(n²)
    void funcionD(int n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++)
                cout << j << " ";
    }

    int sum_subarrays_fast(vector<int>& arr) {
        int n = arr.size();
        int total = 0;
        for (int i = 0; i < n; i++) {
            int subsum = 0;
            for (int j = i; j < n; j++) {
                subsum += arr[j];
                total += subsum;
            }
        }
        return total;
    }

    int find_max(vector<int>& arr) {
        if (arr.empty()) return 0;
        int max_val = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] > max_val)
                max_val = arr[i];
        }
        return max_val;
    }

    bool has_duplicates(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            for (int j = i + 1; j < arr.size(); j++) {
                if (arr[i] == arr[j])
                    return true;
            }
        }
        return false;
    }
};