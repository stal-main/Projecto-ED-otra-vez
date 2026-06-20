#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Graph.h"
#include "GraphAlgorithms.h"

using std::cin;
using std::cout;

void centerText(sf::Text& t, float cx) {
    sf::FloatRect b = t.getLocalBounds();
    t.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
    t.setPosition({ cx, t.getPosition().y });
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    srand(time(0));
    int numNodos;
    int maxVecinos;
    float distCon;

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
    if (!(cin >> distCon) || distCon <= 0.f) {
        cout << "Número inválido. Ingrese un número entero positivo: ";
        cin.clear();
        cin.ignore(10000, '\n');
		cin >> distCon;
    }

    Graph g(numNodos, maxVecinos);
    g.generateRandom(distCon, 1500);

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
            sf::CircleShape circle(15);
            circle.setFillColor(sf::Color::White);
            circle.setOutlineColor(sf::Color::Green);
            circle.setOrigin({ 15, 15 });
            circle.setPosition({ g.getX(i), g.getY(i) });
            window.draw(circle);
        }

        window.draw(textoUI);
        window.display();
    }
}