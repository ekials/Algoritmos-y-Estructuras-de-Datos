#include <iostream>

/* EJERCICIO: Implementar Deque en Bloques (similar al del PDF)

   Estructura:
   - Mapa de punteros a bloques
   - Cada bloque es un array de BLOCK_SIZE elementos
   - Punteros M_INI, M_FIN (inicio y fin en el mapa)
   - Punteros V_INI, V_FIN (inicio y fin en los bloques)

   IMPLEMENTAR:
   1. push_front(int x) - O(1) amortizado
   2. push_back(int x) - O(1) amortizado
   3. pop_front() - O(1) amortizado
   4. pop_back() - O(1) amortizado
   5. operator[](int idx) - O(1) acceso aleatorio

   6. size() - O(1)
   7. find_and_remove(int x) - Encontrar x y eliminarlo
   8. reverse() - Invertir el deque sin crear nuevos bloques
*/

class CDeque {
private:
    static const int MAP_SIZE = 11;
    static const int BLOCK_SIZE = 11;

    int** mapa;        // Mapa de punteros a bloques
    int** M_INI;       // Puntero al primer bloque usado
    int** M_FIN;       // Puntero al último bloque usado
    int* V_INI;        // Puntero al primer elemento
    int* V_FIN;        // Puntero al último elemento

public:
    CDeque();
    ~CDeque();

    void push_front(int n);
    void push_back(int n);
    int pop_front();
    int pop_back();
    int& operator[](int id);

    // NUEVOS MÉTODOS A IMPLEMENTAR:
    int size() const;
    bool empty() const;
    void print() const;
    bool find_and_remove(int x);
    void reverse();
    void clear();
};

CDeque::CDeque() {
    mapa = new int* [MAP_SIZE];
    for (int i = 0; i < MAP_SIZE; i++)
        mapa[i] = 0;

    M_INI = mapa + MAP_SIZE / 2;
    M_FIN = M_INI;
    V_INI = 0;
    V_FIN = 0;
}

CDeque::~CDeque() {
    clear();
    delete[] mapa;
}

void CDeque::push_front(int n) {
    if (!V_INI) {
        M_INI = mapa + MAP_SIZE / 2;
        M_FIN = M_INI;
        *M_INI = new int[BLOCK_SIZE];
        V_INI = *M_INI + BLOCK_SIZE / 2;
        V_FIN = V_INI;
        *V_INI = n;
    }
    else if (V_INI == *M_INI) {
        if (M_INI == mapa) {
            std::cout << "DEQUE LLENO (inicio)\n";
            return;
        }
        M_INI--;
        *M_INI = new int[BLOCK_SIZE];
        V_INI = *M_INI + (BLOCK_SIZE - 1);
        *V_INI = n;
    }
    else {
        V_INI--;
        *V_INI = n;
    }
}

void CDeque::push_back(int n) {
    if (!V_FIN) {
        M_INI = mapa + MAP_SIZE / 2;
        M_FIN = M_INI;
        *M_INI = new int[BLOCK_SIZE];
        V_INI = *M_INI + BLOCK_SIZE / 2;
        V_FIN = V_INI;
        *V_FIN = n;
    }
    else if (V_FIN == *M_FIN + (BLOCK_SIZE - 1)) {
        if (M_FIN == mapa + (MAP_SIZE - 1)) {
            std::cout << "DEQUE LLENO (final)\n";
            return;
        }
        M_FIN++;
        *M_FIN = new int[BLOCK_SIZE];
        V_FIN = *M_FIN;
        *V_FIN = n;
    }
    else {
        V_FIN++;
        *V_FIN = n;
    }
}

int CDeque::pop_front() {
    if (!V_INI) {
        std::cout << "DEQUE VACIO\n";
        return -1;
    }

    int retorno = *V_INI;

    if (V_INI == V_FIN) {
        delete[] * M_INI;
        *M_INI = 0;
        V_INI = V_FIN = 0;
    }
    else if (V_INI == *M_INI + (BLOCK_SIZE - 1)) {
        delete[] * M_INI;
        *M_INI = 0;
        M_INI++;
        V_INI = *M_INI;
    }
    else {
        V_INI++;
    }

    return retorno;
}

int CDeque::pop_back() {
    if (!V_FIN) {
        std::cout << "DEQUE VACIO\n";
        return -1;
    }

    int retorno = *V_FIN;

    if (V_INI == V_FIN) {
        delete[] * M_INI;
        *M_INI = 0;
        V_INI = V_FIN = 0;
    }
    else if (V_FIN == *M_FIN) {
        delete[] * M_FIN;
        *M_FIN = 0;
        M_FIN--;
        V_FIN = *M_FIN + (BLOCK_SIZE - 1);
    }
    else {
        V_FIN--;
    }

    return retorno;
}

int& CDeque::operator[](int id) {
    if (!V_INI) {
        static int dummy = -1;
        std::cout << "DEQUE VACIO\n";
        return dummy;
    }

    int elem_antes = V_INI - *M_INI;
    int pos_global = id + elem_antes;

    int bloque = pos_global / BLOCK_SIZE;
    int pos_en_bloque = pos_global % BLOCK_SIZE;

    return *(*(M_INI + bloque) + pos_en_bloque);
}

// ========== IMPLEMENTA AQUÍ ==========

int CDeque::size() const {
    // Tu código
    // Calcular el número total de elementos
    return 0;
}

bool CDeque::empty() const {
    return V_INI == 0;
}

void CDeque::print() const {
    // Tu código
    // Imprimir todos los elementos
}

bool CDeque::find_and_remove(int x) {
    // Tu código
    // Encontrar x y eliminarlo (primera ocurrencia)
    // Retornar true si se encontró, false si no
    return false;
}

void CDeque::reverse() {
    // Tu código
    // Invertir el deque intercambiando elementos
    // NO crear nuevos bloques
}

void CDeque::clear() {
    // Tu código
    // Liberar todos los bloques
}

// ========== TESTS ==========

int main() {
    std::cout << "=== TEST BASIC OPERATIONS ===\n";
    CDeque dq;

    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.push_front(0);
    dq.push_front(-1);

    std::cout << "Size: " << dq.size() << "\n";
    dq.print();

    std::cout << "\n=== TEST OPERATOR[] ===\n";
    for (int i = 0; i < dq.size(); i++)
        std::cout << "dq[" << i << "] = " << dq[i] << "\n";

    std::cout << "\n=== TEST POP ===\n";
    std::cout << "Pop front: " << dq.pop_front() << "\n";
    std::cout << "Pop back: " << dq.pop_back() << "\n";
    dq.print();

    std::cout << "\n=== TEST FIND_AND_REMOVE ===\n";
    dq.push_back(99);
    dq.print();
    if (dq.find_and_remove(99))
        std::cout << "Removed 99\n";
    dq.print();

    std::cout << "\n=== TEST REVERSE ===\n";
    dq.print();
    dq.reverse();
    std::cout << "After reverse: ";
    dq.print();

    std::cout << "\n=== TEST LARGE DEQUE ===\n";
    CDeque dq2;
    for (int i = 0; i < 20; i++)
        dq2.push_back(i);
    dq2.print();
    std::cout << "Size: " << dq2.size() << "\n";

    return 0;
}

/* ========== SOLUCIONES ==========

int CDeque::size() const {
    if (!V_INI) return 0;

    int total = 0;

    // Contar elementos en el primer bloque
    int elem_primer_bloque = (*M_INI + BLOCK_SIZE) - V_INI;
    total += elem_primer_bloque;

    // Contar bloques intermedios completos
    for (int** p = M_INI + 1; p < M_FIN; p++)
        total += BLOCK_SIZE;

    // Contar elementos en el último bloque (si es diferente del primero)
    if (M_FIN != M_INI) {
        int elem_ultimo_bloque = V_FIN - *M_FIN + 1;
        total += elem_ultimo_bloque;
    } else {
        // Si es el mismo bloque, ajustar
        total = V_FIN - V_INI + 1;
    }

    return total;
}

void CDeque::print() const {
    if (!V_INI) {
        std::cout << "Empty\n";
        return;
    }

    int s = size();
    for (int i = 0; i < s; i++) {
        int elem_antes = V_INI - *M_INI;
        int pos_global = i + elem_antes;
        int bloque = pos_global / BLOCK_SIZE;
        int pos = pos_global % BLOCK_SIZE;
        std::cout << *(*(M_INI + bloque) + pos) << " ";
    }
    std::cout << "\n";
}

bool CDeque::find_and_remove(int x) {
    if (!V_INI) return false;

    int s = size();
    for (int i = 0; i < s; i++) {
        int elem_antes = V_INI - *M_INI;
        int pos_global = i + elem_antes;
        int bloque = pos_global / BLOCK_SIZE;
        int pos = pos_global % BLOCK_SIZE;

        if (*(*(M_INI + bloque) + pos) == x) {
            // Encontrado, shiftar elementos
            for (int j = i; j < s - 1; j++) {
                int curr_bloque = (j + elem_antes) / BLOCK_SIZE;
                int curr_pos = (j + elem_antes) % BLOCK_SIZE;
                int next_bloque = (j + 1 + elem_antes) / BLOCK_SIZE;
                int next_pos = (j + 1 + elem_antes) % BLOCK_SIZE;

                *(*(M_INI + curr_bloque) + curr_pos) =
                    *(*(M_INI + next_bloque) + next_pos);
            }
            pop_back();
            return true;
        }
    }
    return false;
}

void CDeque::reverse() {
    if (!V_INI) return;

    int s = size();
    for (int i = 0; i < s / 2; i++) {
        int elem_antes = V_INI - *M_INI;

        int left_bloque = (i + elem_antes) / BLOCK_SIZE;
        int left_pos = (i + elem_antes) % BLOCK_SIZE;

        int right_bloque = (s - 1 - i + elem_antes) / BLOCK_SIZE;
        int right_pos = (s - 1 - i + elem_antes) % BLOCK_SIZE;

        int temp = *(*(M_INI + left_bloque) + left_pos);
        *(*(M_INI + left_bloque) + left_pos) =
            *(*(M_INI + right_bloque) + right_pos);
        *(*(M_INI + right_bloque) + right_pos) = temp;
    }
}

void CDeque::clear() {
    if (!V_INI) return;

    for (int** p = M_INI; p <= M_FIN; p++) {
        if (*p) {
            delete[] *p;
            *p = 0;
        }
    }
    V_INI = V_FIN = 0;
}

*/