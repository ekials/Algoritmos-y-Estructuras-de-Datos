#include <iostream>
#include <stack>

/* EJERCICIO: Deque donde cada elemento es un Stack (similar a examen)

   Según dijiste: "puede pedir crear un deque y que cada elemento sea un queue"
   Aquí lo hacemos con stacks.

   Estructura:
   - Un Deque donde cada nodo contiene un Stack<int>
   - Implementar deque doblemente enlazado

   OPERACIONES A IMPLEMENTAR:
   1. push_front_stack() - Agregar stack vacío al frente
   2. push_back_stack() - Agregar stack vacío al final
   3. pop_front_stack() - Eliminar stack del frente
   4. pop_back_stack() - Eliminar stack del final
   5. push_to_front_stack(int x) - Push a stack del frente
   6. push_to_back_stack(int x) - Push a stack del final
   7. pop_from_front_stack() - Pop del stack del frente
   8. pop_from_back_stack() - Pop del stack del final
   9. balance() - Redistribuir elementos para que todos los stacks
                  tengan aprox. el mismo tamaño
   10. collect_tops() - Retornar vector con el tope de cada stack
   11. size_distribution() - Imprimir el tamaño de cada stack
   12. merge_adjacent() - Fusionar stacks adyacentes si su suma < threshold
*/

struct DequeNode {
    std::stack<int> data;
    DequeNode* next;
    DequeNode* prev;

    DequeNode() : next(0), prev(0) {}
};

class DequeOfStacks {
private:
    DequeNode* head;
    DequeNode* tail;
    int deque_size;

public:
    DequeOfStacks();
    ~DequeOfStacks();

    // IMPLEMENTAR:
    void push_front_stack();
    void push_back_stack();
    void pop_front_stack();
    void pop_back_stack();

    void push_to_front_stack(int x);
    void push_to_back_stack(int x);
    int pop_from_front_stack();
    int pop_from_back_stack();

    void balance();
    void collect_tops();
    void size_distribution();
    void merge_adjacent(int threshold);

    void print_all();
    bool empty() { return head == 0; }
};

DequeOfStacks::DequeOfStacks() {
    head = 0;
    tail = 0;
    deque_size = 0;
}

DequeOfStacks::~DequeOfStacks() {
    while (head) {
        DequeNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// ========== IMPLEMENTA AQUÍ ==========

void DequeOfStacks::push_front_stack() {
    DequeNode* n = new DequeNode();
    if (!head)head = tail = n;
    else
    {
        n->next = head;
        head->prev = n;
        head = n;
    }
    deque_size++;
}

void DequeOfStacks::push_back_stack() {
    DequeNode* n = new DequeNode();
    if (!head)head = tail = n;
    else
    {
        n->prev = tail;
        tail->next = n;
        tail = n;
    }
    deque_size++;
}

void DequeOfStacks::pop_front_stack() {
    if (!head) return;
    
    DequeNode* temp = head;
    head = head->next;
    if (head) head->prev = 0;
    
    else tail = 0;
    delete temp;
    deque_size--;
    

}

void DequeOfStacks::pop_back_stack() {
    if (!head) return;
    DequeNode* temp = tail;
    tail = tail->prev;
    if (tail) tail->next = 0;
    else head = 0;
    delete temp;
    deque_size--;
}

void DequeOfStacks::push_to_front_stack(int x) {
    if (!head )push_front_stack();
    head->data.push(x);
}

void DequeOfStacks::push_to_back_stack(int x) {
    if (!tail) push_back_stack();
    tail->data.push(x);
}

int DequeOfStacks::pop_from_front_stack() {
    if (!head || head->data.empty()) { pop_back_stack(); return -1; }
    int val = head->data.top();
    head->data.pop();
    return val;
}

int DequeOfStacks::pop_from_back_stack() {
    if (!tail) { pop_back_stack(); return -1; }
    int val = tail->data.top();
    tail->data.pop();
    return val;
}

void DequeOfStacks::balance() {
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

void DequeOfStacks::collect_tops() {
    // Tu código: imprimir el tope de cada stack
    if (!head) return;
    DequeNode* n = head;
    if (n && n->next)
    {
        for (int i = 0; i < deque_size; i++)
        {
            std::cout << n->data.top() <<" ";
            n = n->next;
        }
    }
}
/*
void DequeOfStacks::size_distribution() {
    // Tu código: imprimir tamaño de cada stack
    if (!head) return ;
    DequeNode* n = head;
    int temp = 0;
    int nro_deque = 0;
    while (nro_deque < deque_size);
    {
        for (int i = 0; i < n->data.size(); i++)
        {
            temp++;
        }
        
        nro_deque++;
        std::cout << "Tamaño " << temp << std::endl;
        n = n->next;
        temp = 0;
    }
    
}
*/
void DequeOfStacks::size_distribution() {
    if (!head) {
        std::cout << "Deque vacío\n";
        return;
    }

    std::cout << "Tamaños: ";
    DequeNode* curr = head;
    while (curr) {
        std::cout << curr->data.size() << " ";
        curr = curr->next;
    }
    std::cout << "\n";
}
void DequeOfStacks::merge_adjacent(int threshold) {
    // Tu código: fusionar stacks adyacentes si suma < threshold
}


void DequeOfStacks::print_all() {
    if (!head) {
        std::cout << "Deque vacío\n";
        return;
    }

    std::cout << "Deque (frente->atrás):\n";
    DequeNode* curr = head;
    int idx = 0;

    while (curr) {
        std::cout << "  Stack[" << idx << "]: ";

        std::stack<int> temp = curr->data;
        if (temp.empty()) {
            std::cout << "(vacío)";
        }

        // Imprimir de abajo hacia arriba
        int* arr = new int[temp.size()];
        int size = temp.size();
        for (int i = size - 1; i >= 0; i--) {
            arr[i] = temp.top();
            temp.pop();
        }
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        delete[] arr;

        std::cout << "(tope)\n";
        curr = curr->next;
        idx++;
    }
}
// ========== TESTS ==========

int main() {
    DequeOfStacks ds;

    std::cout << "=== TEST CREAR STACKS ===\n";
    ds.push_back_stack();
    ds.push_to_back_stack(10);
    ds.push_to_back_stack(20);
    ds.push_to_back_stack(30);

    ds.push_back_stack();
    ds.push_to_back_stack(100);
    ds.push_to_back_stack(200);

    ds.push_front_stack();
    ds.push_to_front_stack(5);
    ds.push_to_front_stack(15);

    ds.print_all();

    std::cout << "\n=== TEST SIZE DISTRIBUTION ===\n";
    ds.size_distribution();

    std::cout << "\n=== TEST COLLECT TOPS ===\n";
    ds.collect_tops();

    std::cout << "\n=== TEST POP FROM STACKS ===\n";
    std::cout << "Pop from front stack: " << ds.pop_from_front_stack() << "\n";
    std::cout << "Pop from back stack: " << ds.pop_from_back_stack() << "\n";
    ds.print_all();

    std::cout << "\n=== TEST BALANCE ===\n";
    DequeOfStacks ds2;
    ds2.push_back_stack();
    for (int i = 1; i <= 10; i++)
        ds2.push_to_back_stack(i);

    ds2.push_back_stack();
    ds2.push_to_back_stack(99);

    std::cout << "Antes del balance:\n";
    ds2.size_distribution();
    ds2.balance();
    std::cout << "Después del balance:\n";
    ds2.size_distribution();

    std::cout << "\n=== TEST MERGE ADJACENT ===\n";
    ds.merge_adjacent(5);
    std::cout << "After merging (threshold=5):\n";
    ds.print_all();

    return 0;
}

/* ========== SOLUCIONES ==========

void DequeOfStacks::push_front_stack() {
    DequeNode* newNode = new DequeNode();
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    deque_size++;
}

void DequeOfStacks::push_back_stack() {
    DequeNode* newNode = new DequeNode();
    if (!tail) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    deque_size++;
}

void DequeOfStacks::pop_front_stack() {
    if (!head) {
        std::cout << "Deque vacío\n";
        return;
    }
    DequeNode* temp = head;
    head = head->next;
    if (head) head->prev = 0;
    else tail = 0;
    delete temp;
    deque_size--;
}

void DequeOfStacks::pop_back_stack() {
    if (!tail) {
        std::cout << "Deque vacío\n";
        return;
    }
    DequeNode* temp = tail;
    tail = tail->prev;
    if (tail) tail->next = 0;
    else head = 0;
    delete temp;
    deque_size--;
}

void DequeOfStacks::push_to_front_stack(int x) {
    if (!head) {
        push_front_stack();
    }
    head->data.push(x);
}

void DequeOfStacks::push_to_back_stack(int x) {
    if (!tail) {
        push_back_stack();
    }
    tail->data.push(x);
}

int DequeOfStacks::pop_from_front_stack() {
    if (!head || head->data.empty()) {
        std::cout << "Stack del frente vacío\n";
        return -1;
    }
    int val = head->data.top();
    head->data.pop();
    return val;
}

int DequeOfStacks::pop_from_back_stack() {
    if (!tail || tail->data.empty()) {
        std::cout << "Stack del final vacío\n";
        return -1;
    }
    int val = tail->data.top();
    tail->data.pop();
    return val;
}

void DequeOfStacks::balance() {
    if (!head) return;

    // Contar elementos totales
    int total = 0;
    DequeNode* curr = head;
    while (curr) {
        total += curr->data.size();
        curr = curr->next;
    }

    if (deque_size == 0) return;
    int target = total / deque_size;

    // Extraer todos los elementos
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
        int count = (curr->next) ? target : (total - idx);
        for (int i = 0; i < count && idx < total; i++) {
            curr->data.push(arr[idx++]);
        }
        curr = curr->next;
    }

    delete[] arr;
}

void DequeOfStacks::collect_tops() {
    if (!head) {
        std::cout << "Deque vacío\n";
        return;
    }

    std::cout << "Tops: ";
    DequeNode* curr = head;
    while (curr) {
        if (!curr->data.empty()) {
            std::cout << curr->data.top() << " ";
        } else {
            std::cout << "(vacío) ";
        }
        curr = curr->next;
    }
    std::cout << "\n";
}

void DequeOfStacks::size_distribution() {
    if (!head) {
        std::cout << "Deque vacío\n";
        return;
    }

    std::cout << "Tamaños: ";
    DequeNode* curr = head;
    while (curr) {
        std::cout << curr->data.size() << " ";
        curr = curr->next;
    }
    std::cout << "\n";
}

void DequeOfStacks::merge_adjacent(int threshold) {
    if (!head || !head->next) return;

    DequeNode* curr = head;
    while (curr && curr->next) {
        int combined_size = curr->data.size() + curr->next->data.size();

        if (combined_size < threshold) {
            // Mover elementos del siguiente al actual
            std::stack<int> temp;
            while (!curr->next->data.empty()) {
                temp.push(curr->next->data.top());
                curr->next->data.pop();
            }
            while (!temp.empty()) {
                curr->data.push(temp.top());
                temp.pop();
            }

            // Eliminar el siguiente nodo
            DequeNode* toDelete = curr->next;
            curr->next = toDelete->next;
            if (toDelete->next) {
                toDelete->next->prev = curr;
            } else {
                tail = curr;
            }
            delete toDelete;
            deque_size--;
        } else {
            curr = curr->next;
        }
    }
}

void DequeOfStacks::print_all() {
    if (!head) {
        std::cout << "Deque vacío\n";
        return;
    }

    std::cout << "Deque (frente->atrás):\n";
    DequeNode* curr = head;
    int idx = 0;

    while (curr) {
        std::cout << "  Stack[" << idx << "]: ";

        std::stack<int> temp = curr->data;
        if (temp.empty()) {
            std::cout << "(vacío)";
        }

        // Imprimir de abajo hacia arriba
        int* arr = new int[temp.size()];
        int size = temp.size();
        for (int i = size - 1; i >= 0; i--) {
            arr[i] = temp.top();
            temp.pop();
        }
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        delete[] arr;

        std::cout << "(tope)\n";
        curr = curr->next;
        idx++;
    }
}

*/