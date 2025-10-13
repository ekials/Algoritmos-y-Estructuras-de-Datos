#include <iostream>
#include <queue> //para BFS
#include<stack> //para DFS
struct CBinNode {
    int value;
    CBinNode* nodes[2];

    CBinNode(int v) {
        value = v;
        nodes[0] = nullptr;
        nodes[1] = nullptr;
    }
};

//BFS
void BFS(CBinNode* p)
{
    //q es la cola bfs
    if (!p)return; //si el puntero es nulo indica que esta vacio

    //inicio de la cola
    std::queue<CBinNode*> q; //creamos la cola de CBinNode* para que funcione con orden FIFO
    q.push(p); //encolar la raiz, se inseta el nodo de inciio que es la raiz en la parte trasera de la cola
    while (!q.empty())
    {
        CBinNode* n = q.front(); // para mirar e nodo qee esta al frebtne de ka cika (el siguiente nodo en el orden de visita), este nodo se almacena temporanlmente en el puntero n
        q.pop(); //desencolamos el nodo que acba de mirar el frente de la cola
        std::cout << n->value << " ";

        if (n->nodes[0]) q.push(n->nodes[0]);
        if (n->nodes[1]) q.push(n->nodes[1]);
       
    }
}

void DFS_recursivo(CBinNode* p)
{
    if (!p) return;
    DFS_recursivo(p->nodes[0]);
    std::cout << p->value << " ";
    DFS_recursivo(p->nodes[1]);
}

void DFS_conStack(CBinNode* p)
{
    if (!p) return;
    std::stack <CBinNode*>s;
    s.push(p);

    while (!s.empty())
    {
        CBinNode* n = s.top();
        s.pop();
        std::cout << n->value << " "; //procesar nodo para preorden
        //apilar en orden inverso para simular inorder derecha izq
        if (n->nodes[1]) s.push(n->nodes[1]);
        if (n->nodes[0]) s.push(n->nodes[0]);
    }
    
}
//SIN LIBRERIAS

void BFS_SinLib(CBinNode* p)
{
    if (!p) return;
    CBinNode* q[100];
    int front = 0, rear = 0;
    q[rear++] = p;
    while (front < rear)
    {
        CBinNode* n = q[front++];
        std::cout << n->value << " ";
        if (n->nodes[0]) q[rear++] = n->nodes[0];
        if (n->nodes[1]) q[rear++] = n->nodes[1];
    }

}

void DFS_SinLib(CBinNode* p)
{
    if (!p) return;

    CBinNode* s[100];
    int top = -1;
    s[++top] = p;

    while (top >= 0)
    {
        CBinNode* n = s[top--];
        std::cout << n->value << " ";
        if (n->nodes[1]) s[++top] = n->nodes[1];
        if (n->nodes[0]) s[++top] = n->nodes[0];
    }
}

//int ShortesPathK(CBinNode¨* p)

int main()
{
    std::cout << "Hello World!\n";
}
