#pragma once

#include <utility>
#include <iterator>
#include <cstdint>
#include <array>
#include <bitset>



template<typename T, std::size_t UNIVERSE_SIZE>
class UniversalSet{ // klasa reprezentująca zbiór uniwersalny (uniwersum)
public:
    class Vector{ // klasa reprezetująca zbiór (wektor), który jest podzbiorem uniwersum
    public:
        class Iterator : public std::iterator<std::input_iterator_tag, const T>{ // iterator, który jest jednocześnie cost_iterator-em
        public:
            Iterator(const Iterator&) = default;
            Iterator& operator=(const Iterator&) = default;
            Iterator(Iterator&&) noexcept = default;
            Iterator& operator=(Iterator&&) noexcept = default;
            Iterator(const Vector *vector_ptr, std::size_t index);
            explicit Iterator(const Vector * vector_ptr);
            bool operator==(const Iterator& it) const;
            bool operator!=(const Iterator& it) const;
            Iterator& operator++();
            Iterator operator++(int);
            const T& operator*() const;
            const T* operator->() const;
            explicit operator bool() const;
            friend class Vector;
        private:
            const Vector* vector_ptr;
            std::size_t index;
        };


    public:
        explicit Vector(const UniversalSet *universe_ptr);
        Vector(const UniversalSet *universe_ptr, const std::bitset<UNIVERSE_SIZE> & bits);
        Vector(const Vector&) = default;
        Vector& operator=(const Vector &universe) = default;
        Vector(Vector &&universe) noexcept = default;
        Vector& operator=(Vector &&universe) noexcept = default;
        std::size_t count() const; // Zwraca liczbę elementów reprezentowanych przez "Vector"
        std::pair<Iterator, bool> insert(std::size_t index); // Jezeli element o indeksie "i" nie należy do "Vector" to dodaje ten element oraz zwraca "Iterator" do dodanego elementu i "true", w przeciwnym razie zwraca samo co "end()" i "false"
        bool isMember(std::size_t index) const; // Jezeli element o indeksie "i" należy do "Vector" to zwraca "true", w przeciwnym razie zwraca "false"
        Iterator elemIterator(std::size_t index) const; // Jeżeli element o indeksie "i" należy do "Vector" to zwraca "Iterator" do tego elementu, w przeciwnym razie zwraca to samo co "end()"
        bool remove(std::size_t index); // Jezeli element o indeksie "i" należy do "Vector" to usuwa ten element i zwraca "true", w przeciwnym razie zwraca "false"
        bool operator==(const Vector& v2) const; // Zwraca "true" jeżeli obiekt "v2" reprezentuje ten sam zestaw elementów z tego samego uniwersum, w przeciwnym razie zwraca "false"
        bool operator!=(const Vector& v2) const;
        Vector operator+(const Vector& v2) const; // Zwraca sumę zbiorow
        Vector operator-(const Vector& v2) const; // Zwraca różnicę zbiorów
        Vector operator*(const Vector& v2) const; // Zwraca część wspólną zbiorów
        Vector operator/(const Vector& v2) const; // Zwraca roznicę symetryczną zbiorów
        Iterator begin() const; // Zwraca "Iterator" na początek
        Iterator end() const; // Zwraca "Iterator" za koniec
        friend class Iterator;
    private:
        std::bitset<UNIVERSE_SIZE> bits;
        const UniversalSet<T, UNIVERSE_SIZE> *universe_ptr;
    };

public:
    explicit UniversalSet(const std::array<T, UNIVERSE_SIZE>& elements);
    UniversalSet(const UniversalSet&) = default;
    UniversalSet& operator=(const UniversalSet&) = default;
    UniversalSet(UniversalSet&&) noexcept = default;
    UniversalSet& operator=(UniversalSet&&) noexcept = default;
    constexpr std::size_t universeSize() const { return UNIVERSE_SIZE; }
    const T& elem(std::size_t index) const;
    const T& operator[](std::size_t index) const;
    Vector makeVector() const; // Zwraca pusty "Vector"
private:
    const std::array<T, UNIVERSE_SIZE> elements;
};




template<typename T, size_t UNIVERSE_SIZE>
UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::Iterator(const UniversalSet::Vector * vector_ptr) : vector_ptr(vector_ptr), index(0) {}

template<typename T, size_t UNIVERSE_SIZE>UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::Iterator(const UniversalSet::Vector *vector_ptr, std::size_t index) : vector_ptr(vector_ptr), index(index) {}

template<typename T, size_t UNIVERSE_SIZE>
bool UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::operator==(const UniversalSet::Vector::Iterator &it) const {
    return index == it.index;
}

template<typename T, size_t UNIVERSE_SIZE>
bool UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::operator!=(const UniversalSet::Vector::Iterator &it) const {
    return index != it.index;
}

template<typename T, size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator &UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::operator++() {
    do {
        ++index;
    } while (!vector_ptr->bits[index] && index < vector_ptr->bits.size());
    return *this;
}

template<typename T, size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::operator++(int) {
    Iterator it(*this);
    ++(*this);
    return it;
}

template<typename T, size_t UNIVERSE_SIZE>
const T & UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::operator*() const {
    return vector_ptr->universe_ptr->elements[index];
}

template<typename T, size_t UNIVERSE_SIZE>
const T* UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::operator->() const {
    return &vector_ptr->universe_ptr->elements[index];
}

template<typename T, size_t UNIVERSE_SIZE>
UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::operator bool() const {
    return index < UNIVERSE_SIZE;
}

template<typename T, size_t UNIVERSE_SIZE>
UniversalSet<T, UNIVERSE_SIZE>::Vector::Vector(const UniversalSet *universe_ptr) : universe_ptr(universe_ptr) {}

template<typename T, size_t UNIVERSE_SIZE>
UniversalSet<T, UNIVERSE_SIZE>::UniversalSet(const std::array<T, UNIVERSE_SIZE> & elements) : elements(elements) {}

template<typename T, size_t UNIVERSE_SIZE>
UniversalSet<T, UNIVERSE_SIZE>::Vector::Vector(const UniversalSet *universe_ptr, const std::bitset<UNIVERSE_SIZE> & bits) : universe_ptr(universe_ptr), bits(bits) {}

template<typename T, size_t UNIVERSE_SIZE>
std::size_t UniversalSet<T, UNIVERSE_SIZE>::Vector::count() const {
    return bits.count();
}

template<typename T, size_t UNIVERSE_SIZE>
std::pair<typename UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator, bool> UniversalSet<T, UNIVERSE_SIZE>::Vector::insert(std::size_t index) {
    if (bits.test(index)) {
        return std::make_pair(Iterator(this, bits.size()), false);
    }else {
        bits[index] = 1;
        return std::make_pair(Iterator(this, index), true);
    }
}

template<typename T, size_t UNIVERSE_SIZE>
bool UniversalSet<T, UNIVERSE_SIZE>::Vector::isMember(std::size_t index) const {
    return bits.test(index);
}

template<typename T, size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator
UniversalSet<T, UNIVERSE_SIZE>::Vector::elemIterator(std::size_t index) const {
    if (bits[index]){
        return Iterator(this, index);
    } else{
        return Iterator(this, bits.size());
    }
}

template<typename T, size_t UNIVERSE_SIZE>
bool UniversalSet<T, UNIVERSE_SIZE>::Vector::remove(std::size_t index) {
    if (bits.test(index)) {
        bits[index] = 0;
        return true;
    }else{
        return false;
    }
}

template<typename T, size_t UNIVERSE_SIZE>
bool UniversalSet<T, UNIVERSE_SIZE>::Vector::operator==(const UniversalSet::Vector &v2) const {
    return (bits == v2.bits) && (*universe_ptr == v2);
}

template<typename T, size_t UNIVERSE_SIZE>
bool UniversalSet<T, UNIVERSE_SIZE>::Vector::operator!=(const UniversalSet::Vector &v2) const {
    return bits != v2.bits && (*universe_ptr != v2);
}

template<typename T, size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector
UniversalSet<T, UNIVERSE_SIZE>::Vector::operator+(const UniversalSet::Vector &v2) const {
    std::bitset<UNIVERSE_SIZE> result(bits | v2.bits);
    return Vector(universe_ptr, result);
}

template<typename T, size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector
UniversalSet<T, UNIVERSE_SIZE>::Vector::operator-(const UniversalSet::Vector &v2) const {
    std::bitset<UNIVERSE_SIZE> result(bits & ~v2.bits);
    return Vector(universe_ptr, result);
}

template<typename T, size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector
UniversalSet<T, UNIVERSE_SIZE>::Vector::operator*(const UniversalSet::Vector &v2) const {
    std::bitset<UNIVERSE_SIZE> result(bits & v2.bits);
    return Vector(universe_ptr, result);
}

template<typename T, size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector
UniversalSet<T, UNIVERSE_SIZE>::Vector::operator/(const UniversalSet::Vector &v2) const {
    std::bitset<UNIVERSE_SIZE> result(bits ^ v2.bits);
    return Vector(universe_ptr, result);
}

template<typename T, size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator
UniversalSet<T, UNIVERSE_SIZE>::Vector::begin() const {
    int temp = 0;
    while (!bits[temp]) {
        ++temp;
    }
    return Iterator(this, temp);
}

template<typename T, size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator
UniversalSet<T, UNIVERSE_SIZE>::Vector::end() const {
    return Iterator(this, bits.size());
}

template<typename T, size_t UNIVERSE_SIZE>
const T &UniversalSet<T, UNIVERSE_SIZE>::elem(std::size_t i) const {
    return elements[i];
}

template<typename T, size_t UNIVERSE_SIZE>
const T &UniversalSet<T, UNIVERSE_SIZE>::operator[](std::size_t i) const {
    return elements[i];
}

template<typename T, size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector UniversalSet<T, UNIVERSE_SIZE>::makeVector()const {
    return Vector(this);
}






