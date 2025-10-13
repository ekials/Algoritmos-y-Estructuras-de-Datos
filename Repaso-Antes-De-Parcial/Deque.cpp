#include<iostream>
using namespace std;

struct Position //para la posicion en el mapa
{
	int blockIndex; // indice del bloque en el mapa, el bloque del array de punteros
	int elementIndex; //indice del elemnto dentro del bloque - celda

	Position(int block = 0, int element = 0)//posicion 0,0
	{
		blockIndex = block; //indc. del bloque
		elementIndex = element; //indc. del elemento
	}
};

class Deque
{
private:
	int** map; //arr de punteros, cada puntero apunta a un bloque de datos
	int mapCapacity; //el tam de map
	int blockSize;//tam fijo de cada bloque de datos

	Position frontPos; //donde empieza (bloque y celda)
	Position backPos; // donde termmina (bloque y celda)
	int totalElements; // cont de elem

};