#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

/* EJERCICIO: Implementar métodos avanzados en BST

   Similar al ejercicio kneighbors del PDF pero con más variantes.

   MÉTODOS A IMPLEMENTAR:
   1. kneighbors(int x, int k) - Los k vecinos más cercanos a x
   2. range_query(int min, int max) - Elementos en rango [min, max]
   3. level_elements(int level) - Elementos en un nivel específico
   4. fill_list_left() - Llenar lista con borde izquierdo del árbol
   5. fill_list_right() - Llenar lista con borde derecho
   6. fill_list_leaves() - Llenar lista solo con hojas
   7. prune_to_height(int h) - Podar árbol para altura máxima h
   8. is_balanced() - Verificar si está balanceado
   9. balance_tree() - Balancear el árbol (convertir a AVL-like)
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

    // Funciones auxiliares
    void inorder_helper(Node* n, std::vector<int>& result);
    int height_helper(Node* n);
    bool is_balanced_helper(Node* n, int& height);
    void collect_inorder(Node* n, std::vector<int>& vals);
    Node* build_balanced(std::vector<int>& vals, int start, int end);

public:
    BST();
    ~BST();

    void insert(int x);
    void print();

    // IMPLEMENTAR ESTOS:
    void kneighbors(int x, int k);
    void range_query(int min, int max);
    void level_elements(int level);
    void fill_list_left();
    void fill_list_right();
    void fill_list_leaves();
    void prune_to_height(int h);
    bool is_balanced();
    void balance_tree();
    int height() { return height_helper(root); }
};

BST::BST() {
    root = 0;
}

BST::~BST() {
    // Implementación simple, no crítica para el examen
}

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

void BST::inorder_helper(Node* n, std::vector<int>& result) {
    if (!n) return;
    inorder_helper(n->left, result);
    result.push_back(n->value);
    inorder_helper(n->right, result);
}

void BST::print() {
    std::vector<int> result;
    inorder_helper(root, result);
    for (int v : result)
        std::cout << v << " ";
    std::cout << "\n";
}

int BST::height_helper(Node* n) {
    if (!n) return 0;
    int left_h = height_helper(n->left);
    int right_h = height_helper(n->right);
    return 1 + std::max(left_h, right_h);
}

// ========== IMPLEMENTA AQUÍ ==========

void BST::kneighbors(int x, int k) {
    std::cout << "(" << x << "," << k << ") => ";

    // Tu código aquí
    // Estrategia:
    // 1. Obtener todos los valores en inorder
    // 2. Encontrar los k más cercanos a x usando diferencia absoluta
    // 3. Ordenar por valor e imprimir


    std::cout << "\n";
}

void BST::range_query(int min, int max) {
    std::cout << "Range[" << min << "," << max << "]: ";

    // Tu código aquí
    // Recorrer inorder y recolectar valores en rango

    std::cout << "\n";
}

void BST::level_elements(int level) {
    std::cout << "Level " << level << ": ";

    // Tu código aquí
    // Recorrido por niveles o recursivo con contador de nivel

    std::cout << "\n";
}

void BST::fill_list_left() {
    std::cout << "Borde izquierdo: ";

    // Tu código aquí
    // Recorrer siempre por la izquierda

    std::cout << "\n";
}

void BST::fill_list_right() {
    std::cout << "Borde derecho: ";

    // Tu código aquí
    // Recorrer siempre por la derecha

    std::cout << "\n";
}

void BST::fill_list_leaves() {
    std::cout << "Hojas: ";

    // Tu código aquí
    // Recorrer y detectar hojas (sin hijos)

    std::cout << "\n";
}

void BST::prune_to_height(int h) {
    // Tu código aquí
    // Eliminar nodos que exceden la altura h
}

bool BST::is_balanced() {
    // Tu código aquí
    // Un árbol está balanceado si para cada nodo,
    // |height(left) - height(right)| <= 1
    return false;
}

bool BST::is_balanced_helper(Node* n, int& height) {
    // Tu código auxiliar
    return false;
}

void BST::balance_tree() {
    // Tu código aquí
    // Estrategia:
    // 1. Recolectar elementos en inorder (quedan ordenados)
    // 2. Reconstruir árbol balanceado desde array ordenado
}

void BST::collect_inorder(Node* n, std::vector<int>& vals) {
    // Tu código auxiliar
}

Node* BST::build_balanced(std::vector<int>& vals, int start, int end) {
    // Tu código auxiliar
    // Construir árbol balanceado recursivamente
    return 0;
}

// ========== TESTS ==========

int main() {
    BST tree;

    // Construir árbol del PDF
    tree.insert(55); tree.insert(41); tree.insert(77);
    tree.insert(33); tree.insert(47); tree.insert(61);
    tree.insert(88); tree.insert(20); tree.insert(36);
    tree.insert(44); tree.insert(51); tree.insert(57);
    tree.insert(65); tree.insert(80); tree.insert(99);

    std::cout << "=== ÁRBOL ORIGINAL ===\n";
    tree.print();
    std::cout << "Altura: " << tree.height() << "\n\n";

    std::cout << "=== TEST K-NEIGHBORS ===\n";
    tree.kneighbors(33, 4);
    tree.kneighbors(88, 3);
    tree.kneighbors(76, 2);
    tree.kneighbors(50, 5);

    std::cout << "\n=== TEST RANGE QUERY ===\n";
    tree.range_query(40, 60);
    tree.range_query(70, 90);

    std::cout << "\n=== TEST LEVEL ELEMENTS ===\n";
    tree.level_elements(0);
    tree.level_elements(1);
    tree.level_elements(2);
    tree.level_elements(3);

    std::cout << "\n=== TEST BORDERS ===\n";
    tree.fill_list_left();
    tree.fill_list_right();
    tree.fill_list_leaves();

    std::cout << "\n=== TEST IS BALANCED ===\n";
    std::cout << "Balanceado: " << (tree.is_balanced() ? "SI" : "NO") << "\n";

    std::cout << "\n=== TEST BALANCE TREE ===\n";
    tree.balance_tree();
    std::cout << "Después de balancear:\n";
    tree.print();
    std::cout << "Altura: " << tree.height() << "\n";
    std::cout << "Balanceado: " << (tree.is_balanced() ? "SI" : "NO") << "\n";

    std::cout << "\n=== TEST PRUNE ===\n";
    BST tree2;
    for (int i = 1; i <= 15; i++)
        tree2.insert(i);
    std::cout << "Antes de podar (altura=" << tree2.height() << "):\n";
    tree2.print();
    tree2.prune_to_height(3);
    std::cout << "Después de podar a altura 3:\n";
    tree2.print();

    return 0;
}

/* ========== SOLUCIONES ==========

void BST::kneighbors(int x, int k) {
    std::cout << "(" << x << "," << k << ") => ";

    std::vector<int> all_vals;
    inorder_helper(root, all_vals);

    // Calcular distancias
    std::vector<std::pair<int, int>> distances; // {distancia, valor}
    for (int val : all_vals) {
        distances.push_back({std::abs(val - x), val});
    }

    // Ordenar por distancia
    std::sort(distances.begin(), distances.end());

    // Tomar los k más cercanos
    std::vector<int> result;
    for (int i = 0; i < k && i < distances.size(); i++) {
        result.push_back(distances[i].second);
    }

    // Ordenar por valor
    std::sort(result.begin(), result.end());

    for (int val : result)
        std::cout << val << " ";
    std::cout << "\n";
}

void BST::range_query(int min, int max) {
    std::cout << "Range[" << min << "," << max << "]: ";

    std::vector<int> all_vals;
    inorder_helper(root, all_vals);

    for (int val : all_vals) {
        if (val >= min && val <= max)
            std::cout << val << " ";
    }
    std::cout << "\n";
}

void BST::level_elements(int level) {
    std::cout << "Level " << level << ": ";

    void level_helper(Node* n, int curr_level, int target) {
        if (!n) return;
        if (curr_level == target) {
            std::cout << n->value << " ";
            return;
        }
        level_helper(n->left, curr_level + 1, target);
        level_helper(n->right, curr_level + 1, target);
    };

    level_helper(root, 0, level);
    std::cout << "\n";
}

void BST::fill_list_left() {
    std::cout << "Borde izquierdo: ";
    Node* curr = root;
    while (curr) {
        std::cout << curr->value << " ";
        curr = curr->left;
    }
    std::cout << "\n";
}

void BST::fill_list_right() {
    std::cout << "Borde derecho: ";
    Node* curr = root;
    while (curr) {
        std::cout << curr->value << " ";
        curr = curr->right;
    }
    std::cout << "\n";
}

void BST::fill_list_leaves() {
    std::cout << "Hojas: ";

    void leaves_helper(Node* n) {
        if (!n) return;
        if (!n->left && !n->right) {
            std::cout << n->value << " ";
            return;
        }
        leaves_helper(n->left);
        leaves_helper(n->right);
    };

    leaves_helper(root);
    std::cout << "\n";
}

void BST::prune_to_height(int h) {
    void prune_helper(Node*& n, int curr_height) {
        if (!n) return;
        if (curr_height > h) {
            delete n;
            n = 0;
            return;
        }
        prune_helper(n->left, curr_height + 1);
        prune_helper(n->right, curr_height + 1);
    };

    prune_helper(root, 1);
}

bool BST::is_balanced() {
    int height = 0;
    return is_balanced_helper(root, height);
}

bool BST::is_balanced_helper(Node* n, int& height) {
    if (!n) {
        height = 0;
        return true;
    }

    int left_h = 0, right_h = 0;
    bool left_balanced = is_balanced_helper(n->left, left_h);
    bool right_balanced = is_balanced_helper(n->right, right_h);

    height = 1 + std::max(left_h, right_h);

    if (!left_balanced || !right_balanced)
        return false;

    return std::abs(left_h - right_h) <= 1;
}

void BST::balance_tree() {
    std::vector<int> vals;
    collect_inorder(root, vals);
    root = build_balanced(vals, 0, vals.size() - 1);
}

void BST::collect_inorder(Node* n, std::vector<int>& vals) {
    if (!n) return;
    collect_inorder(n->left, vals);
    vals.push_back(n->value);
    collect_inorder(n->right, vals);
}

Node* BST::build_balanced(std::vector<int>& vals, int start, int end) {
    if (start > end) return 0;

    int mid = start + (end - start) / 2;
    Node* n = new Node(vals[mid]);

    n->left = build_balanced(vals, start, mid - 1);
    n->right = build_balanced(vals, mid + 1, end);

    return n;
}

*/