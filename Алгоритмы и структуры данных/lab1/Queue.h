#pragma once
#include <vector>
template <typename ElType>
class Queue {
public:
	bool insert(ElType el) {
		if (isFull()) {
			return false;
		}
		elements[tail] = el;
		tail = (tail + 1) % maxElements;
		return true;
	}

	ElType* peek() {
		if (isEmpty()) {
			return nullptr;
		}
		return &elements[head];
	}

	bool dequeue() {
		if (isEmpty()) {
			return false;
		}
		head = (head + 1) % maxElements;
		return true;
	}

	bool isFull() {
		return (tail + 1) % maxElements == head;
	}

	bool isEmpty() {
		return head == tail;
	}

	void getQueue(std::vector<ElType> &arr) {
		for (int i = head; i != tail; i = (i + 1) % maxElements)
		{
			arr.push_back(elements[i]);
		}
	}
private:
	ElType elements[6];
	int maxElements = 6;
	int head = 0, tail = 0;
};