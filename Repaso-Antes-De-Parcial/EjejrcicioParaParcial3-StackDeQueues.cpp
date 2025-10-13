#include <iostream>
#include <queue>

/* EJERCICIO: Stack donde cada elemento es un Queue (estructura híbrida)

   Similar a lo que mencionaste: "puede pedir creaciones de dos estructuras juntas"

   Estructura:
   - Un Stack donde cada elemento es un Queue<int>
   - NO usar std::stack, implementar con nodos

   OPERACIONES:
   1. push_queue() - Agregar un nuevo queue vacío al stack
   2. pop_queue() - Eliminar el queue del tope
   3. enqueue_top(int x) - Agregar x al queue del tope
   4. dequeue_top() - Eliminar del frente del queue del tope
   5. front_top() - Ver el frente del queue del tope
   6. size_top() - Tamaño del queue del tope
   7. transfer_to_next() - Pasar todos los elementos del queue del tope
                           al siguiente queue (si existe)
   8. flatten() - Retornar todos los elementos en un solo queue
                  (en orden: del tope al fondo, cada queue de frente a atrás)
   9. reverse_top_queue() - Invertir el queue del tope
   10. print_all() - Imprimir toda la estructura
*/

struct StackNode {
    std::queue<int> data;
    StackNode* next;

    StackNode() : next(0) {}
};

class StackOfQueues {
private:
    StackNode* top;
    int stack_size;

public:
    StackOfQueues();
    ~StackOfQueues();

    // IMPLEMENTAR ESTOS:
    void push_queue();
    void pop_queue();
    void enqueue_top(int x);
    int dequeue_top();
    int front_top();
    int size_top();
    void transfer_to_next();
    std::queue<int> flatten();
    void reverse_top_queue();
    void print_all();

    bool empty() { return top == 0; }
    int get_stack_size() { return stack_size; }
};

StackOfQueues::StackOfQueues() {
    top = 0;
    stack_size = 0;
}

StackOfQueues::~StackOfQueues() {
    while (top) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
}

// ========== IMPLEMENTA AQUÍ ==========

void StackOfQueues::push_queue() {
   StackNode* n =new StackNode();
   n->next = top;
   top = n;
   stack_size++;
}

void StackOfQueues::pop_queue() {
    if (!top)return;
    StackNode* n = top;
    top = top->next;
    delete n;
    stack_size--;

}

void StackOfQueues::enqueue_top(int x) {
    if (!top) push_queue();
    top->data.push(x);
}


int StackOfQueues::dequeue_top() {
    // Tu código: eliminar del frente del queue del tope
    if (!top || top->data.empty())return -1;
    
    int val = top->data.front();
    top->data.pop();
    return val;
}

int StackOfQueues::front_top() {
    // Tu código: ver el frente del queue del tope
    if(!top || top->data.empty())return -1;
    return top->data.front();
}

int StackOfQueues::size_top() {
    // Tu código: tamaño del queue del tope
    if (!top)return 0;
    return top->data.size();
}

void StackOfQueues::transfer_to_next() {
    // Tu código: mover elementos del tope al siguiente
    if (!top || top->next == 0) return;
    
    while (!top->data.empty())
    {
        top->next->data.push(top->data.front());
        top->data.pop();
    }
}

std::queue<int> StackOfQueues::flatten() {
    // Tu código: aplanar toda la estructura en un solo queue
    std::queue<int> result;
    StackNode* n = top;
    while (n)
    {
        std::queue<int> temp = n ->data;
        while (!temp.empty())
        {
            result.push(temp.front());
            temp.pop();
        }
        n = n->next;

    }
    return result;
}

void StackOfQueues::reverse_top_queue() {
    // Tu código: invertir el queue del tope (usa un stack auxiliar)
    if (!top)return;
    std::queue<int>aux;
    int size = top->data.size();
    int* arr = new int[size];

    for (int i = 0; i < size; i++)
    {
        arr[i] = top->data.front();
        top->data.pop();
    }
    for (int i = size - 1; i >= 0; i++)
    {
        top->data.push(arr[i]);
    }
    delete[] arr;

}

void StackOfQueues::print_all() {
    // Tu código: imprimir toda la estructura
    // Formato: Stack[Tope] -> Queue[1 2 3] -> Queue[4 5] -> ...
    if (!top) { std::cout << "vacio xd" << std::endl; }
    std::cout << "Stack" <<std::endl;
    
    for (StackNode* curr = top; curr; curr = curr->next)
    {
        if (curr->data.empty())
        {
            std::cout << "vacio";
        }
        else
        {
            std::queue<int> q = curr->data;
            while (!q.empty())
            {
                std::cout << q.front() << " ";
                q.pop();
            }
        }
        std::cout << std::endl;
    }
}

// ========== TESTS ==========

int main() {
    StackOfQueues sq;

    std::cout << "=== TEST BASIC OPERATIONS ===\n";
    sq.push_queue();
    sq.enqueue_top(10);
    sq.enqueue_top(20);
    sq.enqueue_top(30);

    sq.push_queue();
    sq.enqueue_top(100);
    sq.enqueue_top(200);

    sq.push_queue();
    sq.enqueue_top(5);

    sq.print_all();

    std::cout << "\n=== TEST DEQUEUE ===\n";
    std::cout << "Dequeue from top: " << sq.dequeue_top() << "\n";
    sq.print_all();

    std::cout << "\n=== TEST TRANSFER ===\n";
    sq.transfer_to_next();
    std::cout << "After transfer to next:\n";
    sq.print_all();

    std::cout << "\n=== TEST REVERSE ===\n";
    sq.reverse_top_queue();
    std::cout << "After reversing top queue:\n";
    sq.print_all();

    std::cout << "\n=== TEST FLATTEN ===\n";
    std::queue<int> flat = sq.flatten();
    std::cout << "Flattened: ";
    while (!flat.empty()) {
        std::cout << flat.front() << " ";
        flat.pop();
    }
    std::cout << "\n";

    std::cout << "\n=== TEST POP QUEUE ===\n";
    sq.pop_queue();
    std::cout << "After popping top queue:\n";
    sq.print_all();

    return 0;
}

/* ========== SOLUCIONES ==========

void StackOfQueues::push_queue() {
    StackNode* newNode = new StackNode();
    newNode->next = top;
    top = newNode;
    stack_size++;
}

void StackOfQueues::pop_queue() {
    if (!top) {
        std::cout << "Stack vacío\n";
        return;
    }
    StackNode* temp = top;
    top = top->next;
    delete temp;
    stack_size--;
}

void StackOfQueues::enqueue_top(int x) {
    if (!top) {
        std::cout << "Stack vacío, creando queue...\n";
        push_queue();
    }
    top->data.push(x);
}

int StackOfQueues::dequeue_top() {
    if (!top || top->data.empty()) {
        std::cout << "Queue del tope vacío\n";
        return -1;
    }
    int val = top->data.front();
    top->data.pop();
    return val;
}

int StackOfQueues::front_top() {
    if (!top || top->data.empty()) {
        std::cout << "Queue del tope vacío\n";
        return -1;
    }
    return top->data.front();
}

int StackOfQueues::size_top() {
    if (!top) return 0;
    return top->data.size();
}

void StackOfQueues::transfer_to_next() {
    if (!top || !top->next) {
        std::cout << "No hay siguiente queue\n";
        return;
    }

    while (!top->data.empty()) {
        top->next->data.push(top->data.front());
        top->data.pop();
    }
}

std::queue<int> StackOfQueues::flatten() {
    std::queue<int> result;
    StackNode* curr = top;

    while (curr) {
        std::queue<int> temp = curr->data;
        while (!temp.empty()) {
            result.push(temp.front());
            temp.pop();
        }
        curr = curr->next;
    }

    return result;
}

void StackOfQueues::reverse_top_queue() {
    if (!top) return;

    std::queue<int> aux;
    int size = top->data.size();
    int* arr = new int[size];

    // Extraer a array
    for (int i = 0; i < size; i++) {
        arr[i] = top->data.front();
        top->data.pop();
    }

    // Reinsertar en orden inverso
    for (int i = size - 1; i >= 0; i--) {
        top->data.push(arr[i]);
    }

    delete[] arr;
}

void StackOfQueues::print_all() {
    if (!top) {
        std::cout << "Stack vacío\n";
        return;
    }

    StackNode* curr = top;
    int level = 0;

    std::cout << "Stack (tope->fondo):\n";
    while (curr) {
        std::cout << "  Queue[" << level << "]: ";

        std::queue<int> temp = curr->data;
        if (temp.empty()) {
            std::cout << "(vacío)";
        }
        while (!temp.empty()) {
            std::cout << temp.front() << " ";
            temp.pop();
        }
        std::cout << "\n";

        curr = curr->next;
        level++;
    }
}

*/