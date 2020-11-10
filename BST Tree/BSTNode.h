#pragma once


template<typename T>
class BSTNode{
public:
    BSTNode* left;
    BSTNode* right;
    BSTNode* parent;
    T key;

    BSTNode() : parent(nullptr), left(nullptr), right(nullptr) {}
    BSTNode(T key) : key(key), right(nullptr), left(nullptr), parent(nullptr) {}
};




