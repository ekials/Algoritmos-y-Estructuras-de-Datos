#include <iostream>
#include <queue>
#include <vector>

/* EJERCICIO: Impresión de Árbol por Niveles con Formatos

   Según mencionaste: "Imprimir un árbol por terminal con los niveles"

   MÉTODOS A IMPLEMENTAR:
   1. print_by_levels() - Cada nivel en una línea
   2. print_with_null() - Mostrar null para nodos faltantes
   3. print_tree_visual() - Vista jerárquica ASCII art
   4. print_zigzag() - Imprimir niveles alternando izq-der, der-izq
   5. level_sums() - Suma de cada nivel
   6. max_width() - Ancho máximo del árbol (más nodos en un nivel)
   7. vertical_order() - Impresión en orden vertical
*/

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int v) : value(v), left(0), right(0) {}
};

class BST {
private:
    Node* root;

    int height_helper(Node* n);
    void print_level_helper(Node* n, int level, int curr_level);

public:
    BST();
    ~BST();

    void insert(int x);
    int height() { return height_helper(root); }

    // IMPLEMENTAR ESTOS:
    void print_by_levels();
    void print_with_null();
    void print_tree_visual();
    void print_zigzag();
    void level_sums();
    int max_width();
    void vertical_order();
};

BST::BST() { root = 0; }
BST::~BST() {}

void BST::insert(int x) {
    Node** p = &root;
    while (*p && (*p)->value != x) {
        if ((*p)->value < x)
            p = &((*p)->right);
        else
            p = &((*p)->left);
    }
    if (!*p)
        *p = new Node(x);
}

int BST::height_helper(Node* n) {
    if (!n) return 0;
    int left_h = height_helper(n->left);
    int right_h = height_helper(n->right);
    return 1 + std::max(left_h, right_h);
}

// ========== IMPLEMENTA AQUÍ ==========

void BST::print_by_levels() {
    // Tu código aquí
    // Usar queue para BFS, imprimir cada nivel en una línea
    std::cout << "Árbol por niveles:\n";
}

void BST::print_with_null() {
    // Tu código aquí
    // Incluir "null" para espacios vacíos
    std::cout << "Árbol con nulls:\n";
}

void BST::print_tree_visual() {
    // Tu código aquí (DIFÍCIL - opcional pero impresionante)
    // Crear representación visual tipo:
    //       55
    //      /  \
    //    41    77
    //   /  \   / \
    //  33  47 61 88
    std::cout << "Árbol visual:\n";
}

void BST::print_zigzag() {
    // Tu código aquí
    // Nivel 0: izq->der, Nivel 1: der->izq, Nivel 2: izq->der, ...
    std::cout << "Zigzag:\n";
}

void BST::level_sums() {
    // Tu código aquí
    // Calcular suma de cada nivel
    std::cout << "Sumas por nivel:\n";
}

int BST::max_width() {
    // Tu código aquí
    // Retornar el máximo número de nodos en cualquier nivel
    return 0;
}

void BST::vertical_order() {
    // Tu código aquí (DIFÍCIL)
    // Columna vertical: todos los nodos en la misma "columna" horizontal
    std::cout << "Orden vertical:\n";
}

// ========== TESTS ==========

int main() {
    BST tree;

    // Árbol balanceado
    tree.insert(50);
    tree.insert(30); tree.insert(70);
    tree.insert(20); tree.insert(40);
    tree.insert(60); tree.insert(80);
    tree.insert(10); tree.insert(25);
    tree.insert(35); tree.insert(45);

    std::cout << "Altura: " << tree.height() << "\n\n";

    std::cout << "=== PRINT BY LEVELS ===\n";
    tree.print_by_levels();

    std::cout << "\n=== PRINT WITH NULL ===\n";
    tree.print_with_null();

    std::cout << "\n=== PRINT ZIGZAG ===\n";
    tree.print_zigzag();

    std::cout << "\n=== LEVEL SUMS ===\n";
    tree.level_sums();

    std::cout << "\n=== MAX WIDTH ===\n";
    std::cout << "Ancho máximo: " << tree.max_width() << "\n";

    std::cout << "\n=== VERTICAL ORDER ===\n";
    tree.vertical_order();
    return 0;
}