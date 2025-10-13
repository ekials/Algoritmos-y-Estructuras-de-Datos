#include <iostream>

/* EJERCICIO: Lista Circular con Operaciones Avanzadas

   Similar al ejercicio split_list del examen pero con lista circular.

   IMPLEMENTAR:
   1. split_circular(Node* pivot) - Reorganizar elementos menores a la
      izquierda del pivot, mayores a la derecha. La lista sigue circular.

   2. rotate_right(int k) - Rotar la lista k posiciones a la derecha
      Ejemplo: 1->2->3->4->5 con k=2 => 4->5->1->2->3

   3. rotate_left(int k) - Rotar k posiciones a la izquierda

   4. split_alternating(CircularList& other) - Dividir en dos listas
      alternando elementos: 1->2->3->4->5 => L1: 1->3->5, L2: 2->4

   5. josephus(int k) - Problema de Josephus: eliminar cada k-ésimo
      elemento hasta que quede uno solo. Retornar el valor del último.
*/

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(0) {}
};

class CircularList {
private:
    Node* head;
    int size;

public:
    CircularList();
    ~CircularList();

    void push_back(int x);
    void push_front(int x);
    Node* get_head() { return head; }

    // IMPLEMENTAR ESTOS:
    void split_circular(Node* pivot);
    void rotate_right(int k);
    void rotate_left(int k);
    void split_alternating(CircularList& other);
    int josephus(int k);

    void print(int max_iter = 20);
    Node* find(int x);
};

CircularList::CircularList() {
    head = 0;
    size = 0;
}

CircularList::~CircularList() {
    if (!head) return;
    Node* curr = head->next;
    while (curr != head) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete head;
}

void CircularList::push_back(int x) {
    Node* newNode = new Node(x);
    if (!head) {
        head = newNode;
        newNode->next = head;
    }
    else {
        Node* curr = head;
        while (curr->next != head)
            curr = curr->next;
        curr->next = newNode;
        newNode->next = head;
    }
    size++;
}

void CircularList::push_front(int x) {
    Node* newNode = new Node(x);
    if (!head) {
        head = newNode;
        newNode->next = head;
    }
    else {
        Node* curr = head;
        while (curr->next != head)
            curr = curr->next;
        newNode->next = head;
        curr->next = newNode;
        head = newNode;
    }
    size++;
}

void CircularList::print(int max_iter) {
    if (!head) {
        std::cout << "Empty\n";
        return;
    }
    Node* curr = head;
    int count = 0;
    do {
        std::cout << curr->data << " ";
        curr = curr->next;
        count++;
    } while (curr != head && count < max_iter);
    std::cout << "\n";
}

Node* CircularList::find(int x) {
    if (!head) return 0;
    Node* curr = head;
    do {
        if (curr->data == x) return curr;
        curr = curr->next;
    } while (curr != head);
    return 0;
}

// ========== IMPLEMENTA AQUÍ ==========

void CircularList::split_circular(Node* pivot) {
    // Tu código aquí
    // Reorganizar: menores al pivot van antes, mayores después
    // Mantener la estructura circular
}

void CircularList::rotate_right(int k) {
    if (!head || size <= 1) return;
    k = k % size;
    if (k == 0) return;

    // Encontrar el nuevo head (size - k pasos desde head)
    Node* curr = head;
    for (int i = 0; i < size - k - 1; i++)
        curr = curr->next;

    head = curr->next;
}

void CircularList::rotate_left(int k) {
    if (!head || size <= 1) return;
    k = k % size;
    if (k == 0) return;

    Node* curr = head;
    for (int i = 0; i < k - 1; i++)
        curr = curr->next;

    head = curr->next;
}

void CircularList::split_alternating(CircularList& other) {
    if (!head) return;

    Node* curr = head;
    Node* other_head = 0;
    Node* other_tail = 0;
    Node* this_tail = 0;

    bool take_this = true;
    int count = 0;

    do {
        Node* next = curr->next;

        if (!take_this) {
            curr->next = 0;
            if (!other_head) {
                other_head = other_tail = curr;
            }
            else {
                other_tail->next = curr;
                other_tail = curr;
            }
        }
        else {
            this_tail = curr;
        }

        take_this = !take_this;
        curr = next;
        count++;
    } while (count < size);

    // Cerrar círculos
    if (this_tail) this_tail->next = head;
    if (other_tail) {
        other_tail->next = other_head;
        other.head = other_head;
    }
}

int CircularList::josephus(int k) {
    if (!head) return -1;

    Node* curr = head;
    Node* prev = head;

    // Encontrar el último nodo
    while (prev->next != head)
        prev = prev->next;

    while (curr->next != curr) {
        // Contar k-1 pasos
        for (int i = 1; i < k; i++) {
            prev = curr;
            curr = curr->next;
        }

        // Eliminar curr
        prev->next = curr->next;
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }

    int result = curr->data;
    return result;
}

/*
// Tu código aquí
// Rotar k posiciones a la derecha


void CircularList::rotate_left(int k) {
    // Tu código aquí
}

void CircularList::split_alternating(CircularList& other) {
    // Tu código aquí
    // Dividir elementos alternados
}

int CircularList::josephus(int k) {
    // Tu código aquí
    // Simular el problema de Josephus
    return -1;
}
*/
// ========== TESTS ==========

int main() {
    std::cout << "=== TEST SPLIT_CIRCULAR ===\n";
    CircularList c1;
    c1.push_back(43); c1.push_back(67); c1.push_back(34);
    c1.push_back(20); c1.push_back(71); c1.push_back(12);
    c1.push_back(61); c1.push_back(77);
    std::cout << "Original: "; c1.print();

    Node* pivot = c1.find(43);
    c1.split_circular(pivot);
    std::cout << "After split by 43: "; c1.print();

    std::cout << "\n=== TEST ROTATE ===\n";
    CircularList c2;
    c2.push_back(1); c2.push_back(2); c2.push_back(3);
    c2.push_back(4); c2.push_back(5);
    std::cout << "Original: "; c2.print();
    c2.rotate_right(2);
    std::cout << "Rotate right 2: "; c2.print();
    c2.rotate_left(3);
    std::cout << "Rotate left 3: "; c2.print();

    std::cout << "\n=== TEST SPLIT_ALTERNATING ===\n";
    CircularList c3, c4;
    c3.push_back(1); c3.push_back(2); c3.push_back(3);
    c3.push_back(4); c3.push_back(5); c3.push_back(6);
    std::cout << "Original: "; c3.print();
    c3.split_alternating(c4);
    std::cout << "List 1: "; c3.print();
    std::cout << "List 2: "; c4.print();

    std::cout << "\n=== TEST JOSEPHUS ===\n";
    CircularList c5;
    for (int i = 1; i <= 7; i++) c5.push_back(i);
    std::cout << "N=7, k=3 => Survivor: " << c5.josephus(3) << "\n";

    CircularList c6;
    for (int i = 1; i <= 10; i++) c6.push_back(i);
    std::cout << "N=10, k=2 => Survivor: " << c6.josephus(2) << "\n";

    return 0;
}

/* ========== SOLUCIONES ==========

void CircularList::split_circular(Node* pivot) {
    if (!head || !pivot) return;

    Node* less_head = 0;
    Node* less_tail = 0;
    Node* greater_head = 0;
    Node* greater_tail = 0;

    Node* curr = head;
    bool first = true;

    do {
        Node* next = curr->next;

        if (curr == pivot) {
            // El pivot se maneja especial
        } else if (curr->data < pivot->data) {
            curr->next = 0;
            if (!less_head) {
                less_head = less_tail = curr;
            } else {
                less_tail->next = curr;
                less_tail = curr;
            }
        } else {
            curr->next = 0;
            if (!greater_head) {
                greater_head = greater_tail = curr;
            } else {
                greater_tail->next = curr;
                greater_tail = curr;
            }
        }

        if (first) first = false;
        curr = next;
    } while (curr != head);

    // Reconstruir: less -> pivot -> greater (circular)
    if (less_tail) {
        less_tail->next = pivot;
        head = less_head;
    } else {
        head = pivot;
    }

    pivot->next = greater_head ? greater_head : head;

    if (greater_tail) {
        greater_tail->next = head;
    } else {
        pivot->next = head;
    }
}

void CircularList::rotate_right(int k) {
*/