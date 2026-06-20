#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include "Graph.h"
#include "GraphAlgorithms.h"

using std::cin;
using std::cout;
using std::string;

void centerText(sf::Text& t, float cx) {
    sf::FloatRect b = t.getLocalBounds();
    t.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
    t.setPosition({ cx, t.getPosition().y });
}

string menu() {
	string res = "Elija el algoritmo que desea usar:\n";
	res += "1. Busqueda en profundidad (DFS)\n";
	res += "2. Busqueda en anchura (BFS)\n";
	res += "3. Algoritmo de Prim\n";
	res += "4. Algoritmo de Kruskal\n";
	res += "5. Algoritmo de Dijkstra\n";
    return res;
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    srand(time(0));
    int numNodos;
    int maxVecinos;
    float distCon;
    int algoritmo;

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

    cout << "Ingrese la distancia de conexión: ";
    if (!(cin >> distCon) || distCon <= 0.f) {
        cout << "Número inválido. Ingrese un número entero positivo: ";
        cin.clear();
        cin.ignore(10000, '\n');
		cin >> distCon;
    }

    cout << menu();
    if (!(cin >> algoritmo) || algoritmo <= 0.f) {
        cout << "Número inválido. Ingrese un número entero positivo: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> distCon;
    }

    Graph g(numNodos, maxVecinos);
    g.generateRandom(distCon, 1500, 800);

    sf::RenderWindow window(sf::VideoMode({ 1500, 800 }), "Proyecto ED");
    sf::Font fuente;
    if (!fuente.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        return -1;
    }

    std::string mensaje = "Hola Mundo";
    sf::Text textoUI(fuente, mensaje, 18);
    textoUI.setFillColor(sf::Color::White);
    textoUI.setPosition({ 20.f, 15.f });

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        for (int i = 0; i < g.getNumNodes(); i++) {
            sf::CircleShape circle(12);
            circle.setFillColor(sf::Color::White);
            circle.setOutlineColor(sf::Color::Green);
            circle.setOutlineThickness(1.5f);
            circle.setOrigin({ 12, 12 });
            circle.setPosition({ g.getX(i), g.getY(i)});
            window.draw(circle);
        }

        for (int i = 0; i < g.getNumNodes(); i++) {
            for (int j = 0; j < g.getDegree(i); j++) {
                int vecino = g.getNeighbor(i, j);
                if (vecino > i) {
                    sf::Vertex line[] = {
                        sf::Vertex{sf::Vector2f(g.getX(i),  g.getY(i)),  sf::Color(100, 100, 120)},
                        sf::Vertex{sf::Vector2f(g.getX(vecino), g.getY(vecino)), sf::Color(100, 100, 120)}
                    };
                    window.draw(line, 2, sf::PrimitiveType::Lines);
                }
            }
        }

        window.draw(textoUI);
        window.display();
    }
}