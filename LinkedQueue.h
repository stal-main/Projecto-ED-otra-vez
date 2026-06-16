#pragma once

#include <iostream>
#include <stdexcept>
#include "Node.h"
#include "Queue.h"

using std::cout;
using std::endl;
using std::runtime_error;

template <typename E>

class LinkedQueue : public Queue<E> {

private:

	Node<E>* front;

	Node<E>* back;

	int size;

public:

	LinkedQueue() {

		back = front = new Node<E>(nullptr);

		size = 0;

	}

	~LinkedQueue() {

		clear();

		delete front;
	}

	void Enqueue(E element) {

		back->next = new Node<E>(element, nullptr);

		back = back->next;

		size++;

	}

	E dequeue() {

		if (size == 0) {
			throw runtime_error("Queue is empty");
		}

		E result = front->next->element;

		Node<E>* temp = front->next;
		
		front->next = temp->next

		delete temp;

		if (size == 0) {
			back = front
		}

		size--;

		return result;
	}

	E frontValue() {
		if (size == 0) {
			throw runtime_error("Queue is empty");
		}

		return front->next->element;
	}

	void clear() {

		while (front->next != nullptr) {

			Node<E>* temp = front->next;

			front->next = temp->next;

			delete temp;
		}

		back = front;

		size = 0;

	}

	bool isEmpty() {

		return size == 0

	}

	int getSize() {

		return

	}

	void print() {

		cout << "[ ";

		Node<E>* temp = front->next;

		while (temp != nullptr) {

			cout << temp->element;

			if (temp->next != nullptr) {
				cout << ", ";
			}

			temp = temp->next;

		}

		cout << " ]" << endl;

	}

};

