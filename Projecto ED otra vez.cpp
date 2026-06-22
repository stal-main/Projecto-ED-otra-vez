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

int nodoTocado(const Graph& g, float mx, float my) {
    for (int i = 0; i < g.getNumNodes(); i++) {
        float distanciax = g.getX(i) - mx;
        float distanciay = g.getY(i) - my;
        if (distanciax * distanciax + distanciay * distanciay <= 12 * 12)
            return i;
    }
    return -1;
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

string nombreAlgoritmo(int alg) {
    switch (alg) {
    case 1:
        return "Busqueda en profundidad (DFS)";
    case 2:
        return "Busqueda en anchura (BFS)";
    case 3:
        return "Algoritmo de Prim";
    case 4:
        return "Algoritmo de Kruskal";
    case 5:
        return "Algoritmo de Dijkstra";
    default:
        return "Error, elija un numero entre 1 y 5";
    }
}

Graph* aplicarAlgoritmo(int alg, const Graph& g, int nodoInicio) {
    switch (alg) {
    case 1: 
        return dfs(g, nodoInicio);
    case 2: 
        return bfs(g, nodoInicio);
    case 3:
        return prim(g, nodoInicio);
    case 4: 
		return kruskal(g);
    case 5: 
		return dijkstra(g, nodoInicio, -1);
    default:
		return nullptr;
    }
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

    cout << "Ingrese el máximo de vecinos por nodo: ";
    if (!(cin >> maxVecinos) || maxVecinos <= 0) {
        cout << "Número inválido. Ingrese un número entero positivo: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> maxVecinos;
    }

    cout << "Ingrese la distancia de conexión (recomendado mayor a 100): ";
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
        cin >> algoritmo;
    }

    Graph g(numNodos, maxVecinos);
    g.generateRandom(distCon, 1500, 800);

    sf::RenderWindow window(sf::VideoMode({ 1500, 800 }), "Proyecto ED");
    window.setFramerateLimit(60);
    sf::Font fuente;
    if (!fuente.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        return -1;
    }

    sf::Text textoUI(fuente, nombreAlgoritmo(algoritmo), 18);
    textoUI.setFillColor(sf::Color::White);
    textoUI.setPosition({ 20.f, 15.f });

    int nodoSeleccionado = -1;
	Graph* arbol = nullptr;

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            
            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::R) {
                    delete arbol;
                    arbol = nullptr;
                    nodoSeleccionado = -1;
                    g.generateRandom(distCon, 1500, 800);
				}
            }

            if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {

                if (mouseEvent->button == sf::Mouse::Button::Left) {

                    int clicX = mouseEvent->position.x;

                    int clicY = mouseEvent->position.y;

                    nodoSeleccionado = nodoTocado(g, clicX, clicY);

                    if (nodoSeleccionado != -1) {

                        delete arbol;

                        arbol = aplicarAlgoritmo(algoritmo, g, nodoSeleccionado);
                    }
                }
            }
        }

        window.clear();

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

        if (arbol != nullptr) {
            for (int i = 0; i < arbol->getNumNodes(); i++) {
                for (int j = 0; j < arbol->getDegree(i); j++) {
                    int vecino = arbol->getNeighbor(i, j);
                    if (vecino > i) {
                        sf::Vertex line[] = {
                            sf::Vertex{sf::Vector2f(arbol->getX(i),  arbol->getY(i)),  sf::Color::Cyan},
                            sf::Vertex{sf::Vector2f(arbol->getX(vecino), arbol->getY(vecino)), sf::Color::Cyan}
                        };
                        window.draw(line, 2, sf::PrimitiveType::Lines);
                    }
                }
            }
        }

        for (int i = 0; i < g.getNumNodes(); i++) {
            sf::CircleShape circle(12);
			if (i == nodoSeleccionado) {
                circle.setFillColor(sf::Color::Red);
                circle.setOutlineColor(sf::Color::Red);
                circle.setOutlineThickness(1.5f);
                circle.setOrigin({ 12, 12 });
                circle.setPosition({ g.getX(i), g.getY(i) });
                window.draw(circle);
			}
            else {
                circle.setFillColor(sf::Color::White);
                circle.setOutlineColor(sf::Color::Green);
                circle.setOutlineThickness(1.5f);
                circle.setOrigin({ 12, 12 });
                circle.setPosition({ g.getX(i), g.getY(i) });
                window.draw(circle);
            }
        }

        window.draw(textoUI);
        window.display();
    }
	delete arbol;
}