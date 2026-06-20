#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Graph.h"
#include "GraphAlgorithms.h"

using std::cin;
using std::cout;

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    int numNodos;
    int maxVecinos;
    float distanciaCone;

    cout << "Ingrese el numero de nodos: ";
    while (!(cin >> numNodos) || numNodos <= 0) {
		cout << "Número inválido. ingrese un número entero positivo: ";
        cin.clear();
        cin.ignore(10000, '\n');
		cin >> numNodos;
    }

    cout << "Ingrese el mximo de vecinos por nodo: ";
    if (!(cin >> maxVecinos) || maxVecinos <= 0) {
        cout << "Número inválido. Ingrese un número entero positivo: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> maxVecinos;
    }

    cout << "Ingrese la Distancia de conexión: ";
    if (!(cin >> distanciaCone) || distanciaCone <= 0.f) { 
        cout << "Número inválido. Ingrese un número entero positivo: ";
        cin.clear();
        cin.ignore(10000, '\n');
		cin >> distanciaCone;
    }

    sf::RenderWindow window(sf::VideoMode({ 1500, 800 }), "Proyecto ED");
    sf::CircleShape shape(15.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}