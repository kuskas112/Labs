#pragma once

#include <cstdlib>
#include <iostream>
#include <stack>
#include <utility> // ��� std::pair
using namespace std;

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int value) : data(value){}
};

class Tree {
public:
    Node* root = nullptr;

    void insert(int value) {
        root = insert(root, value);
    }

    void findUnbalancedNodes() {
        findUnbalancedNodes(root);
    }

    void findKthLeaf(int k) {
        int kValue = k;
        bool found = false;
        findKthLeaf(root, k, found);
        if (!found) {
            cout << "�-�� ���� �� ��� ������" << endl;
        }
    }

    void print() {
        print(root);
        cout << endl;
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    // ������� ��� ���������� ������ ������ (����������)
    int findHeight() {
        if (root == nullptr) return 0;

        stack<pair<Node*, int>> stk; // ���� ��� �������� ��� ���� � �������
        stk.push(make_pair(root, 1)); // �������� � ����� �� ������ 1
        int maxHeight = 0;

        while (!stk.empty()) {
            pair<Node*, int> top = stk.top();
            Node* node = top.first;
            int level = top.second;
            stk.pop();

            if (node != nullptr) {
                maxHeight = max(maxHeight, level); // ��������� ������������ ������
                // ��������� ������� �������
                stk.push(make_pair(node->right, level + 1));
                // ��������� ������ �������
                stk.push(make_pair(node->left, level + 1));
            }
        }
        return maxHeight;
    }

private:

    // ������� ���� � �������� ������ 
    Node* insert(Node* root, int value) {
        // ���� ������ ������, ������� ����� ����
        if (root == nullptr) {
            return new Node(value);
        }

        // ����������� ����� ����������� ����� ��� �������
        if (value < root->data) {
            root->left = insert(root->left, value);
        }
        else if (value > root->data) {
            root->right = insert(root->right, value);
        }

        return root; // ������� ������������� ����
    }

    // ����������� ����� ��� ������ ������ � �������� ���������� �������� == 1
    void findUnbalancedNodes(Node* root) {
        if (root == nullptr) {
            return;
        }

        findUnbalancedNodes(root->left);
        findUnbalancedNodes(root->right);

        int leftCount = countNodes(root->left);
        int rightCount = countNodes(root->right);

        if (abs(leftCount - rightCount) == 1) {
            cout << "������� � ������ �����: " << root->data
                << " ����� ������� � ��������: "
                << leftCount << " (����) � " << rightCount << " (�����)" << endl;
        }
    }

    // ������� ����� � ���������
    int countNodes(Node* root) {
        if (root == nullptr) {
            return 0;
        }
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    
    void findKthLeaf(Node* root, int& k, bool& found) {
        if (!root || found) {
            return;
        }

        // ������� ������������ ����� ���������
        findKthLeaf(root->left, k, found);

        // ���������, �������� �� ������� ���� ������
        if (!root->left && !root->right) {
            k--; // ��������� k ��� ������� ���������� �����
            if (k == 0) { // ���� �� ����� k-� ����
                cout << "K-� ����: " << root->data << endl;
                found = true; // ������������� ����, ��� ���� ������
                return;
            }
        }

        // ���� �� ����� � ����� ���������, ���������� � ������
        findKthLeaf(root->right, k, found);
    }

    void print(Node* root) {
        if (root == nullptr) { return; }
        print(root->left);
        cout << root->data << " ";
        print(root->right);
    }

    // �������� ���� �� ��������� key �� ��������� � ������ root
    Node* deleteNode(Node* root, int key) {
        if (!root) { return nullptr; }

        // ���������� ����� �� �����������
        if (key > root->data) {
            root->right = deleteNode(root->right, key);
        }
        else if (key < root->data) {
            root->left = deleteNode(root->left, key);
        }
        else { //key == root->data
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            else { // ��� �������� ���� != nullptr
                Node* minValueNode = root->right;
                while (minValueNode->left != nullptr) {
                    minValueNode = minValueNode->left;
                }
                // �������� �������� ���������� ����
                // �� ����������� �� ������� ���������
                root->data = minValueNode->data;

                // ������� �� ������� ��������� ���������� ���� �
                // ����������� ��������� �� ������� ���������
                root->right = deleteNode(root->right, minValueNode->data);
            }
        }

        return root;
    }

};