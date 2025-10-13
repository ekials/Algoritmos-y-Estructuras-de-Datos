#include <iostream>

struct Node {
    Node(int _v) { v = _v; next = 0; }
    int v;
    Node* next;
};

class CForwardList {
public:
    CForwardList();
    ~CForwardList();
    void push_front(int x);
    void push_back(int x);
    void print();

    // MÉTODOS A IMPLEMENTAR:

    // 1. Invertir la lista en O(n) sin crear nuevos nodos
    void reverse();

    // 2. Eliminar todos los nodos con valor x en O(n)
    void remove_all(int x);

    // 3. Insertar ordenadamente (asume lista ordenada)
    void insert_sorted(int x);

    // 4. Encontrar el k-ésimo elemento desde el final
    // Si k=1 retorna el último, k=2 el penúltimo, etc.
    int kth_from_end(int k);

    // 5. Detectar si hay un ciclo (retorna true si existe)
    bool has_cycle();

    // 6. Particionar la lista: menores a x a la izq, mayores a la der
    void partition(int x);

private:
    Node* head;
};

CForwardList::CForwardList() {
    head = 0;
}

CForwardList::~CForwardList() {
    Node* p = head;
    while (p) {
        Node* temp = p;
        p = p->next;
        delete temp;
    }
}

void CForwardList::push_front(int x) {
    Node* n = new Node(x);
    n->next = head;
    head = n;
}

void CForwardList::push_back(int x) {
    Node* n = new Node(x);
    Node** q;
    for (q = &head; *q != 0; q = &((*q)->next));
    *q = n;
}

void CForwardList::print() {
    for (Node* p = head; p != 0; p = p->next)
        std::cout << p->v << " ";
    std::cout << "\n";
}

// IMPLEMENTA AQUÍ:

void CForwardList::reverse() {
    // Tu código aquí
    // Pista: usa 3 punteros (prev, current, next)
}

void CForwardList::remove_all(int x) {
    // Tu código aquí
    // Pista: usa puntero a puntero
}

void CForwardList::insert_sorted(int x) {
    // Tu código aquí
    // Pista: encuentra la posición correcta con puntero a puntero
}

int CForwardList::kth_from_end(int k) {
    // Tu código aquí
    // Pista: técnica de dos punteros separados por k posiciones
    return -1;
}

bool CForwardList::has_cycle() {
    // Tu código aquí
    // Pista: algoritmo tortuga y liebre (Floyd's)
    return false;
}

void CForwardList::partition(int x) {
    // Tu código aquí
    // Similar al problema split_list del PDF
}

int main() {
    CForwardList l;

    // Test reverse
    std::cout << "=== TEST REVERSE ===\n";
    l.push_back(1); l.push_back(2); l.push_back(3);
    l.push_back(4); l.push_back(5);
    l.print();
    l.reverse();
    std::cout << "Reversed: "; l.print();

    // Test remove_all
    std::cout << "\n=== TEST REMOVE_ALL ===\n";
    CForwardList l2;
    l2.push_back(5); l2.push_back(3); l2.push_back(5);
    l2.push_back(7); l2.push_back(5); l2.push_back(9);
    l2.print();
    l2.remove_all(5);
    std::cout << "After removing 5: "; l2.print();

    // Test insert_sorted
    std::cout << "\n=== TEST INSERT_SORTED ===\n";
    CForwardList l3;
    l3.insert_sorted(5);
    l3.insert_sorted(2);
    l3.insert_sorted(8);
    l3.insert_sorted(3);
    l3.insert_sorted(7);
    std::cout << "Sorted list: "; l3.print();

    // Test kth_from_end
    std::cout << "\n=== TEST KTH_FROM_END ===\n";
    std::cout << "3rd from end: " << l3.kth_from_end(3) << "\n";
    std::cout << "1st from end: " << l3.kth_from_end(1) << "\n";

    // Test partition
    std::cout << "\n=== TEST PARTITION ===\n";
    CForwardList l4;
    l4.push_back(43); l4.push_back(67); l4.push_back(34);
    l4.push_back(20); l4.push_back(71); l4.push_back(12);
    l4.print();
    l4.partition(50);
    std::cout << "After partition by 50: "; l4.print();

    return 0;
}

/* SOLUCIONES:

void CForwardList::reverse() {
    Node* prev = 0;
    Node* curr = head;
    Node* next = 0;

    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

void CForwardList::remove_all(int x) {
    Node** p = &head;
    while (*p) {
        if ((*p)->v == x) {
            Node* temp = *p;
            *p = (*p)->next;
            delete temp;
        } else {
            p = &((*p)->next);
        }
    }
}

void CForwardList::insert_sorted(int x) {
    Node** p;
    for (p = &head; *p && (*p)->v < x; p = &((*p)->next));
    Node* n = new Node(x);
    n->next = *p;
    *p = n;
}

int CForwardList::kth_from_end(int k) {
    Node* fast = head;
    Node* slow = head;

    for (int i = 0; i < k; i++) {
        if (!fast) return -1;
        fast = fast->next;
    }

    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }

    return slow ? slow->v : -1;
}

bool CForwardList::has_cycle() {
    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

void CForwardList::partition(int x) {
    Node* less_head = 0;
    Node* less_tail = 0;
    Node* greater_head = 0;
    Node* greater_tail = 0;

    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        curr->next = 0;

        if (curr->v < x) {
            if (!less_head) {
                less_head = less_tail = curr;
            } else {
                less_tail->next = curr;
                less_tail = curr;
            }
        } else {
            if (!greater_head) {
                greater_head = greater_tail = curr;
            } else {
                greater_tail->next = curr;
                greater_tail = curr;
            }
        }
        curr = next;
    }

    if (less_tail) {
        less_tail->next = greater_head;
        head = less_head;
    } else {
        head = greater_head;
    }
}

*/