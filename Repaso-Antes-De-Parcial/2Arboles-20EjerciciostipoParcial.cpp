#include <iostream>
#include <queue>
#include <vector>
using namespace std;
/*
Notas por que estoy al borde del suicidio
1. Se usa un puntero simple CBinTreeNode : Solo cuando se necesita recorrer el arbol o acceder a los valores
de los nodos sin cambiar los enlaces entre ellos
ejm: Buscar un nodo, recolectar valores, como ancestros, hijos, imprimir nodos, procesar nodos sin modificar la estructura
como buscar k vecnos inferiores o knietos

en resumen te permite moverte por el arbol (acceder a los nodes[0], nodes[1] o value) sin alterar los enlaces entre nodos
es mas simple y menos propenso a errores, ya que no puedes cambiar accidentalmente la estructura del arbol

2. Se una un doble puntero CbinTreeNode** cuando
Necesitas modificar la estructura del arbol, como cambiar los enlaces entre nodos
por ejemplo asignar un nuevo nodo a nodes[0], nodes[1] o incluso a root
ejm: Inserar un nodo, eliminar un nodo, podar nodos, como en podar nuetos, ancestros
En resumen el doble puntero te da acceso al puntero que conecta un nodo con su padre, por ejemplo root, nodes[0][1], esto
permite modificar ese eblace como asignar un nuevo noodo o establecerlo a nullptr
Es necesario cuando quieres cambiar donde apunta un puntero del arbol por ejem desvincular un hijo o remplazar un nodo



*/
struct CBinTreeNode {
    CBinTreeNode(int v) {
        value = v;
        nodes[0] = nodes[1] = 0;
    }
    CBinTreeNode* nodes[2];
    int value;
};

class CBinTree {
public:
    CBinTree();
    void Print();
    bool Insert(int x);
    bool Remove(int x);
private:
    bool Find(int x, CBinTreeNode**& p);
    CBinTreeNode** Rep(CBinTreeNode** p);
    void InOrder(CBinTreeNode* n);
    void Levels(CBinTreeNode* n);
    CBinTreeNode* root;

    // === EJERCICIOS DE EXAMEN ===
public:
    // 1. Llenar un array con todos los ancestros de un nodo x (desde root hasta padre de x)
    /*FUNCIONA PERO CON ERRORES Y NO ES CORRECTO POR QUE MODIFCA EL ARBOL POR EL**
    void FillList_Ancestros(int x, int L[], int& size)
    {
        CBinTreeNode** p = &root;

        CBinTreeNode** n = &root;
        if (!Find(x, n)) return;
        while ((*p) != 0 && (*p)->value != x)
        {
            L[size++] = (*p)->value;
            if (x < (*p)->value)
            {
                (*p) = (*p)->nodes[0];
            }
            if (x > (*p)->value)
            {
                (*p) = (*p)->nodes[1];
            }
        }

    }
    */
    void FillList_Ancestros(int x, int L[], int& size)
    {
        CBinTreeNode* curr = root;
        if (!curr) return;
        

        while (curr != 0 && curr->value != x)
        {
            L[size++] = curr->value;
            if (x < curr->value)
            {
                curr = curr->nodes[0];
            }
            if (x > curr->value)
            {
                curr = curr->nodes[1];
            }
        }
    
    }
    // 2. Podar todos los nietos de un nodo x (eliminar hijos de sus hijos)
    void PodarNietos(int x) 
    {
        CBinTreeNode** p = &root;
        if (!Find(x, p)) return;
        
        CBinTreeNode* temp = *p; //--> se puede remplazar temp por (*p) en el codigo siempre y cunado no hagamos un *p = 0 o *p=new... por que cambiariamos el enlace del arbol y no queremo eso obvio
        if (!temp) return;

        queue<CBinTreeNode*> q;
       if(temp->nodes[0]) q.push(temp->nodes[0]);
       if(temp->nodes[1])q.push(temp->nodes[1]);

        while (!q.empty())
        {
            CBinTreeNode* n = q.front();
            q.pop();

            if (n->nodes[0])
            {
                delete n->nodes[0];
                n->nodes[0] = 0;
            }
            if(n->nodes[1])
            {
                delete n->nodes[1];
                n->nodes[1]=0;
            }
        }
   
    }

    // 3. Imprimir los k valores más cercanos e inferiores a x
    void kVecinosInferiores(int x, int k)
    {
        CBinTreeNode* p = root;
 
        if (!p) return;
        queue<CBinTreeNode*> q;
        q.push(p);

        int total_inferiores = 0;
        vector<int> distancias;
        vector<int> valores_inferiores;
        std::vector<int> todos_los_valores;

        while (!q.empty())
        {
            CBinTreeNode* n = q.front();
            q.pop();

            todos_los_valores.push_back(n->value);
            if (n->nodes[0]) q.push(n->nodes[0]);
            if (n->nodes[1]) q.push(n->nodes[1]);


        }
        //int size_dist = q.size();

        for (int i = 0; i < todos_los_valores.size(); i++)
        {
            if (todos_los_valores[i] < x)
            {
                valores_inferiores.push_back(todos_los_valores[i]);
                distancias.push_back(x - todos_los_valores[i]);
                total_inferiores++;
            }
        }
        for (int i = 0; i < total_inferiores; i++)
        {
            for (int j = 0; j < total_inferiores-i-1; j++)
            {
                if (distancias[j] > distancias[j + 1])
                {
                    swap(distancias[j], distancias[j + 1]);
                    swap(valores_inferiores[j], valores_inferiores[j + 1]);

                }
            }
        }
        for (int i = 0; i < total_inferiores && i < k; i++)
        {
            if (distancias[i] > 0)
            {
                cout << valores_inferiores[i] << " ";
            }
        }
        std::cout << std::endl; 
     
    }

    // 4. Llenar un array con los hijos directos de un nodo x
    void FillList_Hijos(int x, int L[], int& size)
    {
        CBinTreeNode**p = &root;
        
        if (!Find(x, p)) return;

        CBinTreeNode* temp = *p;
        if (temp->nodes[0]) { L[size++] = temp->nodes[0]->value; }
       
        if (temp->nodes[1]) { L[size++] = temp->nodes[1]->value; }

    }

    // 5. Podar todos los ancestros de x (excepto el root)
    void PodarAncestros(int x) 
    {
        CBinTreeNode** p = &root;
        if (!Find(x, p)) return;
        CBinTreeNode* temp = *p;
        if (temp == root) return;
        *p = 0;
        if (x < root->value)
        {
            delete root->nodes[0];
            root->nodes[0] = temp;
        }
        else
        {
            delete root->nodes[1];
            root->nodes[1] = temp;
        }
    }

    // 6. Imprimir los k primeros nietos de x encontrados en BFS
    void kNietos(int x, int k) 
    {
        CBinTreeNode* curr = root;
        CBinTreeNode** p = &root;

        if (!curr) return;
        Find(x, p);
        curr = *p;
        queue<pair<CBinTreeNode*, int>> q;
        q.push({ curr,0 });
        int nieto = 2;
        vector <int> primeros_encontrados;
        while (!q.empty())
        {
            CBinTreeNode* n = q.front().first;
            int nivel = q.front().second;
            q.pop();

            if (nivel == nieto)
            {
                primeros_encontrados.push_back(n->value);
            }

            if (n->nodes[0]) q.push({ n->nodes[0], nivel + 1 });
            if (n->nodes[1]) q.push({ n->nodes[1], nivel + 1 });
        }
    
        for(int i = 0; i < k && i < primeros_encontrados.size();i++)
        { 
            cout << primeros_encontrados[i] << " ";
        }
    }

    // 7. Llenar un array con todos los nietos del root
    void FillList_Nietos(int L[], int& size) 
    {
        CBinTreeNode* curr = root;
        if (!curr) return;
        queue < pair<CBinTreeNode*, int>>q;
        q.push({curr, 0});
        int nieto = 2;

        while(!q.empty())
        { 
            CBinTreeNode* n = q.front().first;
            int nivel = q.front().second;
            q.pop();

            if (nivel == nieto)
            {
                L[size++] = n->value;
            }
            if (n->nodes[0]) q.push({ n->nodes[0], nivel + 1 });
            if (n->nodes[1]) q.push({ n->nodes[1], nivel + 1 });
        }

        
    }

    // 8. Podar los hermanos de x (otros hijos del mismo padre)
    void PodarHermanos(int x) {}

    // 9. Imprimir los k ancestros más cercanos a x
    void kAncestros(int x, int k) {}

    // 10. Llenar un array con los hermanos de x
    void FillList_Hermanos(int x, int L[], int& size)
    {
        if (!root || root->value == x)return;
        CBinTreeNode* padre = root;
        bool encontrado =false;

        while (padre && !encontrado)
        {
            if (padre->nodes[0] && padre->nodes[0]->value == x
                || padre->nodes[1] && padre->nodes[1]->value == x)
            {
                encontrado = true;
                break;
            }
            if (x < padre->value) padre = padre->nodes[0];
            else padre = padre->nodes[1];
        }

        if (!encontrado) return;

        if (padre->nodes[0] && padre->nodes[0]->value != x)
            L[size++] = padre->nodes[0]->value;
    
        if (padre->nodes[1] && padre->nodes[1]->value != x)
            L[size++] = padre->nodes[1]->value;
    }
   
    // 11. Podar todos los bisnietos del root
    void PodarBisnietos()
    {
        CBinTreeNode* curr = root;
        if (!curr) return;
        
        queue <CBinTreeNode*> q;

        if (curr->nodes[0]) q.push(curr->nodes[0]);
        if (curr->nodes[1]) q.push(curr->nodes[1]);

        int profundidad = 2; //1 = hijos, 2=nietos, 3 ==bisnietos
        int nivel = 1;
        int size_nivel = q.size();
        while (!q.empty() && nivel < profundidad)
        {
            size_nivel = q.size();
            for(int i = 0; i < size_nivel; i++)
            {
                CBinTreeNode* n = q.front();
                q.pop();

                if(nivel==1)
                {
                    if (n->nodes[0])
                    {
                        delete n->nodes[0];
                        n->nodes[0] = nullptr;
                    }
                    if (n->nodes[1])
                    {
                        delete n->nodes[1];
                        n->nodes[1] = nullptr;
                    }
                }
                else
                {
                    if (n->nodes[0]) q.push(n->nodes[0]);
                    if (n->nodes[1]) q.push(n->nodes[1]);
                }
            }
            nivel++;
        }
    
    }

    // 12. Imprimir los k primeros bisnietos del root
    void kBisnietos(int k) {}

    // 13. Llenar un array con todos los bisnietos del root
    void FillList_Bisnietos(int L[], int& size)
    {
        CBinTreeNode* curr = root;
        if (!curr) return;
        
        queue<pair<CBinTreeNode*,int>>q;
        q.push({ curr,0 });
        int bisnietos = 3;
        while (!q.empty())
        {
            CBinTreeNode* n = q.front().first;
            int nivel = q.front().second;
            q.pop();

            if(nivel == bisnietos )L[size++] = n->value;
            if (n->nodes[0]) q.push({ n->nodes[0], nivel + 1 });
            if (n->nodes[1]) q.push({ n->nodes[1], nivel + 1 });

        }
    
    }

    // 14. Podar los tatarabuelos de x (ancestros muy lejanos)
    void PodarTatarabuelos(int x) {}

    // 15. Imprimir los k tatarabuelos de x
    void kTatarabuelos(int x, int k) {}

    // 16. Llenar un array con todos los tatarabuelos de x
    void FillList_Tatarabuelos(int x, int L[], int& size) {}

    // 17. Podar los sobrinos de x (hijos de los hermanos)
    void PodarSobrinos(int x) {}

    // 18. Imprimir los k sobrinos de x
    void kSobrinos(int x, int k) {}

    // 19. Llenar un array con los sobrinos de x
    void FillList_Sobrinos(int x, int L[], int& size) {}

    // 20. Imprimir los k primos segundos de x (primos de los primos)
    void kPrimosSegundos(int x, int k) {}
};

CBinTree::CBinTree() { root = 0; }

bool CBinTree::Find(int x, CBinTreeNode**& p) {
    for (p = &root; *p && (*p)->value != x; p = &((*p)->nodes[x > (*p)->value]));
    return *p != 0;
}

bool CBinTree::Insert(int x) {
    CBinTreeNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinTreeNode(x);
    return 1;
}

void CBinTree::InOrder(CBinTreeNode* n) {
    if (!n) return;
    InOrder(n->nodes[0]);
    cout << n->value << " ";
    InOrder(n->nodes[1]);
}

void CBinTree::Levels(CBinTreeNode* n) {
    if (!n) return;
    queue<pair<CBinTreeNode*, int>> q;
    q.push({ n, 0 });
    int l = 0;
    while (!q.empty()) {
        int last = l;
        pair<CBinTreeNode*, int> pp = q.front();
        CBinTreeNode* nn = pp.first;
        l = pp.second;
        if (nn->nodes[0]) q.push({ nn->nodes[0], l + 1 });
        if (nn->nodes[1]) q.push({ nn->nodes[1], l + 1 });
        if (last != l) cout << "\n";
        cout << nn->value << "(" << l << ") ";
        q.pop();
    }
}

void CBinTree::Print() {
    Levels(root);
    cout << "\n";
}

CBinTreeNode** CBinTree::Rep(CBinTreeNode** p) {
    return p;
}

bool CBinTree::Remove(int x) {
    return 0;
}

void VecInsert(CBinTree* t, int* v, int size) {
    for (int i = 0; i < size; i++) t->Insert(v[i]);
}

int main() {
    CBinTree t;

    // Árbol de prueba
    int values[] = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45 };
    for (int i = 0; i < 11; i++) t.Insert(values[i]);

    cout << "Árbol inicial:\n";
    t.Print();
    cout << "\n--- TESTEANDO EJERCICIOS ---\n";

    // Tests básicos - puedes comentar/descomentar para probar cada ejercicio
    int L[10]; int size;

    // Test ejercicio 1
    cout << "\n1. FillList_Ancestros(25): ";
    size = 0;
    t.FillList_Ancestros(25, L, size);
    for (int i = 0; i < size; i++) cout << L[i] << " ";

    // Test ejercicio 2: Podar nietos de 30
   /*
    cout << "\n\n2. Podar nietos de 30:\n";
    t.PodarNietos(30);

    cout << "Resultado despues de podar los nietos de 30:\n";
    t.Print();
    */
    cout << "\n--- TESTEANDO kVecinosInferiores ---\n";

    // Test 1: Buscar los 3 inferiores más cercanos a 47
    cout << "3. kVecinosInferiores(47, 3): ";
    t.kVecinosInferiores(47, 3);
    // Salida Esperada: 45 40 35 (Distancias: 2, 7, 12)

    // Test 2: Buscar los 2 inferiores más cercanos a 75
    cout << "3. kVecinosInferiores(75, 2): ";
    t.kVecinosInferiores(75, 2);
    // Salida Esperada: 70 60 (Distancias: 5, 15)

    // Test 3: k mayor que el número de elementos disponibles (debe ajustar k)
    cout << "3. kVecinosInferiores(21, 5): ";
    t.kVecinosInferiores(21, 5);
    // Salida Esperada: 20 10 (Solo hay 2 inferiores)
    cout << "6. kNietos(30, 2): ";
    t.kNietos(30, 2);



    // Test ejercicio 4  
    cout << "\n4. FillList_Hijos(30): ";
    size = 0;
    t.FillList_Hijos(30, L, size);
    for (int i = 0; i < size; i++) cout << L[i] << " ";


    // Test ejercicio 5: PodarAncestros
   // cout << "\n5. PodarAncestros(25):\n";
    //t.PodarAncestros(25); // Debería eliminar 30 y 20, conectar 25 a 50
    //t.Print();

    // Test 6 k nietos0
    //cout << "6(30, 2): ";
    //t.kNietos(30, 2);
    // Salida Esperada: 20 10 (Solo hay 2 inferiores)


    cout << "\n8. FillList_bisNietos(): ";
    size = 0;
    t.FillList_Bisnietos(L, size);
    for (int i = 0; i < size; i++) cout << L[i] << " ";

    cout << "\n9. Podar_bisNietos(): ";
    size = 0;
    t.PodarBisnietos();
    t.Print();

    // Test ejercicio 7
    cout << "\n7. FillList_Nietos(): ";
    size = 0;
    t.FillList_Nietos(L, size);
    for (int i = 0; i < size; i++) cout << L[i] << " ";
    // Test ejercicio 7
    
    // Test ejercicio 10
    cout << "\n10. FillList_Hermanos(30): ";
    size = 0;
    t.FillList_Hermanos(30, L, size);
    for (int i = 0; i < size; i++) cout << L[i] << " ";

    cout << "\n\n¡Implementa las funciones vacías!\n";

    return 0;
}