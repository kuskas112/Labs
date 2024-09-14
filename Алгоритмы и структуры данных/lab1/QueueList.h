#pragma once

#include <vector>
template <typename T>
struct Node {
	Node(T el) {
		this->data = el;
	}
	T data;
	Node<T>* next = nullptr;
};


template <typename ElType>
class Queue {
public:
	bool insert(ElType el) {
		Node<ElType>* newNode = new Node<ElType>(el);
		
		if (tail != nullptr) {
			tail->next = newNode;
		}
		else {
			head = newNode;
		}
		tail = newNode;
		return true;
	}

	ElType* peek() {
		if (isEmpty()) {
			return nullptr;
		}
		return &head->data;
	}

	bool dequeue() {
		if (isEmpty()) {
			return false;
		}
		Node<ElType>* oldHead = head;
		head = head->next;

		if (head == nullptr) {
			tail = nullptr;
		}
		
		delete oldHead;
		return true;
	}

	bool isEmpty() {
		return head == nullptr;
	}

	void getQueue(std::vector<ElType> &arr) {
		Node<ElType>* tmp = head;
		while (tmp != nullptr)
		{
			arr.push_back(tmp->data);
			tmp = tmp->next;
		}
	}
private:
	Node<ElType>* head = nullptr;
	Node<ElType>* tail = nullptr;
};

