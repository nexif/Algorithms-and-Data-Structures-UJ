#pragma once

#include "BST.h"
#include <functional>
#include <iostream>
#include <stack>

template<typename T>
class Set{
public:

    class Iterator : public std::iterator<std::input_iterator_tag, const T>{

        typename BST<T>::Iterator iter;

    public:
        Iterator() : iter() {}
        explicit Iterator(const typename BST<T>::Iterator& source) : iter(source) {}
        bool operator==(const Iterator &it) const { return iter == it.iter; }
        bool operator!=(const Iterator &it) const { return iter != it.iter; }
        Iterator& operator++() { ++iter; return (*this); }
        Iterator operator++(int) { Iterator it(*this); ++(*this); return it; }
        const T& operator*() const { return *iter; }
        operator bool() const { return static_cast<bool>(iter); }
        bool isEmpty() { return bst_.isEmpty(); }
        friend class Set<T>;
    };

    Set();
    Set(const Set<T>& source);
    Set<T>& operator=(const Set<T>& source);
    Set(Set<T>&& source);
    Set<T>& operator=(Set<T>&& source);
    ~Set();
    std::size_t size() const;
    bool isEmpty() const;
    bool remove(const T& value);
    void inorder(std::function<void(const T&)> f) const;
    Iterator find(const T &value) const ;
    std::pair<Iterator, bool> insert(const T &value);
    Iterator begin() const;
    Iterator end() const;

private:
    BST<T> bst_;
};


template<typename T>
Set<T>::Set() : bst_(){
}

template<typename T>
Set<T>::Set(const Set<T>& source) : bst_(source.bst_){
}

template<typename T>
Set<T>& Set<T>::operator=(const Set<T>& source){
    if (this != &source)
        bst_ = source.bst_;
    return *this;
}

template<typename T>
Set<T>::Set(Set<T>&& source) : bst_(std::move(source.bst_)){
}

template<typename T>
Set<T>& Set<T>::operator=(Set<T>&& source){
    if (this != &source)
        bst_ = std::move(source.bst_);
    return *this;
}

template<typename T>
Set<T>::~Set(){
    bst_.clearTree();
}

template<typename T>
std::size_t Set<T>::size() const {
    return bst_.size();
}

template<typename T>
bool Set<T>::isEmpty() const{
    return bst_.isEmpty();
}

template<typename T>
void Set<T>::inorder(std::function<void(const T&)> f) const{
    bst_.inOrder(f);
}

template<typename T>
pair<typename Set<T>::Iterator, bool> Set<T>::insert(const T &value) {

    Set<T>::Iterator it = find(value);
    if(it) {
        return make_pair(it, false);
    }else {
        bst_.insert(value);
        Set<T>::Iterator tmp = find(value);
        return make_pair(tmp, true);
    }
}

template<typename T>
typename Set<T>::Iterator Set<T>::find(const T &value) const {
    BSTNode<T>* check = bst_.find_It_Helper(value);
    if(check != nullptr) {
        auto it = bst_.begin(check);
        Iterator it2(it);
        return it2;
    } else
        return Iterator();
}

template<typename T>
bool Set<T>::remove(const T &value) {
    if(bst_.find(value)){
        return bst_.remove(value);
    }else{
        return false;
    }
}

template<typename T>
typename Set<T>::Iterator Set<T>::begin() const{
    Set<T>::Iterator it(bst_.begin(bst_.getRoot()));
    return it;
}

template<typename T>
typename Set<T>::Iterator Set<T>::end() const{
    return Iterator();
}



