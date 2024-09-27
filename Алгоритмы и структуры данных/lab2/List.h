#pragma once
#include <vector>
using namespace std;

template <typename T>
struct Node {
    T data;
    std::vector<Node<T>*> links;
    Node(T val) : data(val) {}
    Node(){}
};

template <typename T>
class ListDescriptor {
public:
    Node<T>* first = nullptr;
    Node<T>* last = nullptr;
    void clear() {
        first = nullptr;
        last = nullptr;
    }
};


template <typename T>
class List {
private:
    Node<T>* head = nullptr;
    std::vector<ListDescriptor<T>> descriptors;
public:
    List() {
        ListDescriptor<T> ls;
        descriptors.push_back(ls);
    }

    // Вставка значения в список
    Node<T>* insert(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (isEmpty()) {
            head = newNode;
            descriptors[0].first = newNode;
            descriptors[0].last = newNode;
            return newNode;
        }
        Node<T>* current = descriptors[0].last;
        current->links.push_back(newNode);
        descriptors[0].last = newNode;
        return newNode;
    }

    // enter desc
    void insertDescriptor() {
        ListDescriptor<T> desc;
        descriptors.push_back(desc);
    }

    // Вставка узла в конкретный подсписок
    bool insertByDescriptor(Node<T>* newNode, int descriptorIndex) {
        if (descriptorIndex >= descriptors.size()) {
            return false;
        }
        if (descriptors[descriptorIndex].first == nullptr) {
            descriptors[descriptorIndex].first = newNode;
            descriptors[descriptorIndex].last = newNode;
            return true;
        }
        Node<T>* last = descriptors[descriptorIndex].last;

        while (last->links.size() <= descriptorIndex) {
            last->links.push_back(nullptr);
        }
        last->links[descriptorIndex] = newNode;
        descriptors[descriptorIndex].last = newNode;
    }

    // Нужны комментарии?
    bool isEmpty() {
        return head == nullptr;
    }

    // Найти узел по значению key. Опционально - указатель на предыдущий узел и дескрпитор подсписка
    Node<T>* findNode(string key, Node<T>** prevNode = nullptr, int descriptorIndex = 0) {
        if (isEmpty()) { return nullptr; }
        Node<T>* tmp = descriptors[descriptorIndex].first;
        if (!tmp) { return nullptr; }
        while (tmp->links.size() >= descriptorIndex+1 && key != tmp->data.getKey())
        {
            if (prevNode) {
                *prevNode = tmp;
            }
            if (tmp->links[descriptorIndex] == nullptr) {
                break;
            }
            tmp = tmp->links[descriptorIndex];
        }
        if (tmp->data.getKey() == key) {
            return tmp;
        }
        return nullptr;
    }

    // Удалить по значению key из всех подсписков
    bool deleteNode(string key, int &cntr = 0) {
        bool success = false;
        for (int i = descriptors.size()-1; i >= 0 ; i--)
        {
            if (deleteNodeByDescriptor(key, i)) {
                success = true; // if any deleted
                cntr++;
            }
        }
        return success;
    }

    // Удалить по значению key из подсписка
    bool deleteNodeByDescriptor(string key, int descriptorIndex = 0) {
        Node<T>* prevNode = nullptr;
        Node<T>* node = findNode(key, &prevNode, descriptorIndex);
        if (!node) { return false; }

        if (prevNode) { // node is not first
            if (node->links.size() >= descriptorIndex + 1) { // node has links forward
                prevNode->links[descriptorIndex] = node->links[descriptorIndex];
            }
            if (prevNode->links[descriptorIndex] == nullptr) { // prevNode now last
                descriptors[descriptorIndex].last = prevNode;
            }
            
            node->links[descriptorIndex] = nullptr;
            while (node->links.size() > 0) // while last link is null -> delete it
            {
                if (node->links[node->links.size() - 1] != nullptr) { break; }
                node->links.pop_back();
            }

            if (descriptorIndex == 0) {// delete from main List
                delete node;
            }
            return true;
        }
        else { // node is first
            Node<T>* next = node->links[descriptorIndex];
            descriptors[descriptorIndex].first = next;
            if (descriptorIndex == 0) {
                delete node;
            }
            return true;
        }
        
    }

    // Получить вектор элементов подсписка
    vector<T> getAll(int descriptorIndex = 0) {
        vector<T> resp;
        Node<T>* tmp = descriptors[descriptorIndex].first;
        if (!tmp) { return {}; }
        while (tmp->links.size() >= descriptorIndex+1)
        {
            resp.push_back(tmp->data);
            if (tmp->links[descriptorIndex] == nullptr) {
                break;
            }
            tmp = tmp->links[descriptorIndex];
        }
        resp.push_back(tmp->data);
        return resp;
    }

    // Очистка
    void clear() {
        if (isEmpty()) { return; }
        while (head->links.size() > 0) {
            Node<T>* tmp = head->links[0];
            delete head;
            head = tmp;
        }
        delete head;
        head = nullptr;
        for (int i = 1; i < descriptors.size(); i++)
        {
            descriptors.pop_back();
        }
        descriptors[0].clear();
    }
};