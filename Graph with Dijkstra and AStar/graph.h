#pragma once

#include <cstdint>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <queue>
#include <optional>
#include <iostream>


using namespace std;

// Uwaga! Kod powinien być odporny na błędy i każda z metod jeżeli zachodzi niebezpieczeństwo wywołania z niepoprawnymi parametrami powinna zgłaszac odpowiednie wyjątki!
// V - dane przechowywane przez wierzcholki
// E - dane przechowywane przez krawedzie (etykiety)

template <typename V, typename E>
class Graph //oparty o macierz sąsiedztwa
{
public:
    class VerticesIterator : public std::iterator<std::input_iterator_tag, V>// iterator po wierzchołkach (rosnąco po id wierzchołków)
    {
    private:
        Graph<V, E> &graph_;
        int index;
    public:
        explicit VerticesIterator(Graph<V, E> &graph, size_t current_vertex_id = 0u) : graph_(graph), index(current_vertex_id) {}
        bool operator==(const VerticesIterator &vi2) const { return (index == vi2.index) ; }
        bool operator!=(const VerticesIterator &vi2) const { return (index != vi2.index) ; }
        explicit operator bool () const { return index < graph_.vertices_.size(); }
        VerticesIterator& operator++() { ++index; return *this; }
        VerticesIterator operator++(int) { VerticesIterator it(*this); ++(*this); return it; }
        V& operator*() const {return graph_.vertices_[index];}
        V* operator->() const { return &graph_.vertices_[index]; }

        std::size_t id() const { return index; } // zwraca id aktualnego wierzchołka
    };

    class EdgesIterator // iterator po istniejących krawędziach
    {
    private:
        std::size_t row_, column_;
        Graph<V, E> &graph_;
    public:
        EdgesIterator(Graph<V, E> &graph, std::size_t row, std::size_t col) : graph_(graph), row_(row), column_(col) {}
        bool operator==(const EdgesIterator &ei) const { return (row_ == ei.row_) && (column_ == ei.column_); }
        bool operator!=(const EdgesIterator &ei) const { return (row_ != ei.row_) && (column_ != ei.column_); }
        explicit operator bool() const {if(row_ < graph_.adjMatrix_.size() && column_ < graph_.adjMatrix_[graph_.adjMatrix_.size() - 1].size()) return true; else return false; }
        EdgesIterator& operator++();
        EdgesIterator operator++(int);
        E& operator*() const { return graph_.adjMatrix_[row_][column_].value(); }
        E* operator->() const { return &graph_.nbMatrix[row_][column_].value(); }

        std::size_t v1id() const { return row_; } // zwraca id wierzchołka startowego
        std::size_t v2id() const { return column_; } // zwraca id wierzchołka koncowego
    };



    // iterator po wierzchołkach w kolejności DFS
    class DFSIterator
    {
        explicit DFSIterator(Graph<V, E> &graph, std::size_t current_vertex_id = 0u);
        std::vector<bool> visited;
        Graph<V, E> & graph;
        mutable int vertexIndex;
        mutable std::stack<int> vertexIndexes;
    public:
        bool operator==(const DFSIterator& dfsi) const {return (vertexIndex==dfsi.vertexIndex);}
        bool operator!=(const DFSIterator& dfsi) const {return !(vertexIndex==dfsi.vertexIndex);}
        DFSIterator& operator++();
        DFSIterator operator++(int);
        V& operator*() const;
        V* operator->() const;
        operator bool() const;

        friend class Graph<V, E>;
    };

    // iterator po wierzchołkach w kolejności BFS
    class BFSIterator
    {
        explicit BFSIterator(Graph<V, E> &graph, std::size_t current_vertex_id = 0u);
        std::vector<bool> visited;
        Graph<V, E> & graph;
        mutable int vertexIndex;
        mutable std::queue<int> vertexIndexes;

    public:
        bool operator==(const BFSIterator& dfsi) const {return (vertexIndex == dfsi.vertexIndex);}
        bool operator!=(const BFSIterator& dfsi) const {return !(vertexIndex == dfsi.vertexIndex);}
        BFSIterator& operator++();
        BFSIterator operator++(int);
        V& operator*() const;
        V* operator->() const;
        operator bool() const;

        friend class Graph<V, E>;
    };





public:
    Graph() : edges_(0) {}
    Graph(const Graph<V, E> &source) = default;
    Graph(Graph<V, E> &&source) = default;
    Graph& operator=(const Graph<V, E> &source) = default;
    Graph& operator=(Graph<V, E> &&source) = default;
    ~Graph() = default;

// dodaje nowy wierzchołek z danymi przyjętymi w argumencie (wierzchołek powinien posiadać kopie danych) i zwraca "VerticesIterator" na nowo utworzony wierzchołek
    VerticesIterator insertVertex(const V &vertex_data);
// dodaje nową krawędź między wierzchołkami o id "vertex1_id" i "vertex2_id" i zwraca "EdgesIterator" na nowo dodaną krawędź, oraz informację o tym czy została dodana nowa krawędź, czy nie
// jeśli krawędź między podanymi wierzchołkami już istnieje to działanie funkcji zależy od ostatniego argumentu
// jeśli ostatni argument przyjmuje wartość "true" to krawędź zostaje zastąpiona, jeśli "false" to nie
    std::pair<EdgesIterator, bool> insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label = E(), bool replace = true);
// usuwa wierzchołek o podanym id i zwraca "VerticesIterator" na kolejny wierzchołek, lub to samo co "endVertices()" w przypadku usunięcia ostatniego wierzchołka, lub braku wierzchołka o podanym id
    VerticesIterator removeVertex(std::size_t vertex_id);
// usuwa krawedź między dwoma wierzchołkami o podanych id i zwraca "EdgesIterator" na kolejną krawędź, lub to samo co "endEdges()" w przypadku usunięcia ostatniej krawedzi, lub braku krawędzi między wierzchołkami o podanych id
    EdgesIterator removeEdge(std::size_t vertex1_id, std::size_t vertex2_id);
// zwraca true jeśli istnieje krawędź między wierzchołkami o podanych id, false w przeciwnym razie -
// O(1)
    bool edgeExist(std::size_t vertex1_id, std::size_t vertex2_id) const;
// zwraca ilość wierzchołków w grafie
// O(1)
    std::size_t nrOfVertices() const { return vertices_.size(); }
// zwraca ilość krawędzi w grafie
// O(1)
    std::size_t nrOfEdges() const { return edges_; }
// drukuje macierz sąsiedztwa na konsoli (debug)
    void printNeighborhoodMatrix() const;
// zwraca "VerticesIterator" do wierzchołka o podanym id, lub to samo co "endVertices()" w przypadku braku wierzchołka o podanym id
    VerticesIterator vertex(std::size_t vertex_id);
// zwraca referencję do danych wierzchołka o podanym id
    const V& vertexData(std::size_t vertex_id) const;
// zwraca referencję do danych wierzchołka o podanym id
    V& vertexData(std::size_t vertex_id);
// zwraca "EdgesIterator" do krawędzi pomiędzy wierzchołkami o podanych id, lub to samo co "endEdges()" w przypadku braku krawędzi między wierzchołkami o podanych id
    EdgesIterator edge(std::size_t vertex1_id, std::size_t vertex2_id);
// zwraca referencję do danych (etykiety) krawędzi pomiędzy wierzchołkami o podanych id
    const E& edgeLabel(std::size_t vertex1_id, std::size_t vertex2_id) const;
// zwraca referencję do danych (etykiety) krawędzi pomiędzy wierzchołkami o podanych id
    E& edgeLabel(std::size_t vertex1_id, std::size_t vertex2_id);
    VerticesIterator begin() { return beginVertices(); }
    VerticesIterator end() { return endVertices(); }
// zwraca "VerticesIterator" na pierwszy wierzchołek (o najmniejszym id)
    VerticesIterator beginVertices();
// zwraca "VerticesIterator" "za ostatni" wierzchołek
    VerticesIterator endVertices();
// zwraca "EdgesIterator" na pierwszą krawędz
    EdgesIterator beginEdges();
// zwraca "EdgesIterator" "za ostatnią" krawędz
    EdgesIterator endEdges();

    // zwraca "DFSIterator" na wierzcholek o podanym id
    DFSIterator beginDFS(std::size_t vertex_id = 0u);
// zwraca "DFSIterator" "za ostatni" wierzcholek
    DFSIterator endDFS();
// zwraca "BFSIterator" na wierzcholek o podanym id
    BFSIterator beginBFS(std::size_t vertex_id = 0u);
// zwraca "BFSIterator" "za ostatni" wierzcholek
    BFSIterator endBFS();

    vector<vector<optional<E>>>  adjMatrix_;
    vector<V> vertices_;
    int edges_;
};




template<typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::insertVertex(const V &vertex_data) {
    vertices_.push_back(vertex_data); //dodaje nowy element na końcu kontenera vector - O(1)
    for(int i = 0; i < adjMatrix_.size(); ++i) {
        adjMatrix_[i].resize(adjMatrix_[i].size() + 1);
    }
    adjMatrix_.push_back(vector<optional<E>>(adjMatrix_.size() + 1));
    return VerticesIterator(*this, vertices_.size() - 1);
}

template<typename V, typename E>
pair<typename Graph<V, E>::EdgesIterator, bool> Graph<V, E>::insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label, bool replace) {
    if(vertex1_id < vertices_.size() && vertex2_id < vertices_.size() && replace) {
        if(!adjMatrix_[vertex1_id][vertex2_id]) {
            ++edges_;
        }
        adjMatrix_[vertex1_id][vertex2_id] = label;
        return make_pair(EdgesIterator(*this, vertex1_id, vertex2_id), true);
    } else {
        return make_pair(EdgesIterator(*this, vertex1_id, vertex2_id), false);
    }
}

template<typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::removeVertex(std::size_t vertex_id) {
    if(vertex_id < vertices_.size()) {
        vertices_.erase(vertices_.begin() + vertex_id);
        for(int i = 0; i < adjMatrix_.size(); ++i) {
            if(adjMatrix_[i][vertex_id]) {
                --edges_;
            }
            if(adjMatrix_[vertex_id][i] && i != vertex_id) {
                --edges_;
            }
            adjMatrix_[i].erase(adjMatrix_[i].begin() + vertex_id);
        }
        adjMatrix_.erase(adjMatrix_.begin() + vertex_id);
        return  VerticesIterator(*this, vertex_id);
    } else {
        return endVertices();
    }
}

template<typename V, typename E>
typename Graph<V, E>::EdgesIterator Graph<V, E>::removeEdge(std::size_t vertex1_id, std::size_t vertex2_id) {
    if (vertex1_id < vertices_.size() && vertex2_id < vertices_.size() && adjMatrix_[vertex1_id][vertex2_id]) {
        adjMatrix_[vertex1_id][vertex2_id].reset();
        --edges_;
        EdgesIterator tmp(*this, vertex1_id, vertex2_id+1);
        return tmp;
    } else {
        return endEdges();
    }
}

template<typename V, typename E>
bool Graph<V, E>::edgeExist(std::size_t vertex1_id, std::size_t vertex2_id) const {
    return vertex1_id < vertices_.size() && vertex2_id < vertices_.size() && adjMatrix_[vertex1_id][vertex2_id];
}

template<typename V, typename E>
void Graph<V, E>::printNeighborhoodMatrix() const {
    for (int i = 0; i < adjMatrix_.size(); ++i) {
        for (int j = 0; j < adjMatrix_[i].size(); ++j) {
            if (adjMatrix_[i][j]) {
                std::cout << adjMatrix_[i][j].value() << " ";
            } else { std::cout << "X "; }
        }
        std::cout << std::endl;
    }
}

template<typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::vertex(std::size_t vertex_id) {
    return Graph::VerticesIterator();
}

template<typename V, typename E>
const V &Graph<V, E>::vertexData(std::size_t vertex_id) const {
    if(vertex_id < vertices_.size()) {
        return vertices_[vertex_id];
    } else {
        throw invalid_argument("invalid vertex_id");
    }
}

template<typename V, typename E>
V &Graph<V, E>::vertexData(std::size_t vertex_id) {
    if(vertex_id < vertices_.size()) {
        return vertices_[vertex_id];
    } else {
        throw invalid_argument("invalid vertex_id");
    }
}

template<typename V, typename E>
typename Graph<V, E>::EdgesIterator Graph<V, E>::edge(std::size_t vertex1_id, std::size_t vertex2_id) {
    return EdgesIterator(*this, vertex1_id, vertex2_id);
}

template<typename V, typename E>
const E &Graph<V, E>::edgeLabel(std::size_t vertex1_id, std::size_t vertex2_id) const {
    EdgesIterator it(*this, vertex1_id, vertex2_id);
    return *it;
}

template<typename V, typename E>
E &Graph<V, E>::edgeLabel(std::size_t vertex1_id, std::size_t vertex2_id) {
    EdgesIterator it(*this, vertex1_id, vertex2_id);
    return *it;
}

template<typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::beginVertices() {
    return VerticesIterator(*this, 0);
}

template<typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::endVertices() {
    return VerticesIterator(*this, vertices_.size());
}

template<typename V, typename E>
typename Graph<V, E>::EdgesIterator Graph<V, E>::beginEdges() {
    for(int i = 0; i < adjMatrix_.size(); ++i) {
        for(int j = 0; j < adjMatrix_[i].size(); ++j) {
            if(adjMatrix_[i][j]) {
                return EdgesIterator(*this, i, j);
            }
        }
    }
    return EdgesIterator(*this, adjMatrix_.size(), adjMatrix_.size());
}

template<typename V, typename E>
typename Graph<V, E>::EdgesIterator Graph<V, E>::endEdges() {
    return Graph::EdgesIterator(*this, adjMatrix_.size(), adjMatrix_.size());
}

template<typename V, typename E>
typename Graph<V,E>::DFSIterator Graph<V, E>::beginDFS(std::size_t vertex_id) {
    return DFSIterator(*this, vertex_id);
}

template<typename V, typename E>
typename Graph<V,E>::DFSIterator Graph<V, E>::endDFS() {
    return DFSIterator(*this, this->vertices_.size());
}

template<typename V, typename E>
typename Graph<V,E>::BFSIterator Graph<V, E>::beginBFS(std::size_t vertex_id) {
    return BFSIterator(*this, vertex_id);
}

template<typename V, typename E>
typename Graph<V,E>::BFSIterator Graph<V, E>::endBFS() {
    return BFSIterator(*this, this->vertices_.size());
}

template<typename V, typename E>
typename Graph<V, E>::EdgesIterator &Graph<V, E>::EdgesIterator::operator++() {
    ++column_;
    for(int i = row_; i < graph_.adjMatrix_.size(); ++i) {
        for(int j = column_; j < graph_.adjMatrix_[i].size(); ++j) {
            if(graph_.adjMatrix_[i][j]) {
                row_ = i;
                column_ = j;
                return *this;
            }
        }
        column_ = 0;
    }
    row_ = graph_.vertices_.size();
    column_ = graph_.vertices_.size();
    return *this;
}

template<typename V, typename E>
typename Graph<V, E>::EdgesIterator Graph<V, E>::EdgesIterator::operator++(int) {
    EdgesIterator it(*this);
    ++(*this);
    return it;
}


template<typename V, typename E>
Graph<V, E>::DFSIterator::DFSIterator(Graph<V, E> &graph, size_t curr_id) : graph(graph), vertexIndex(curr_id) {
    for (int i = 0; i < graph.vertices_.size(); ++i) {
        visited.push_back(false);
    }
    vertexIndexes.push(vertexIndex);
    visited[vertexIndex] = true;
}


template<typename V, typename E>
typename Graph<V, E>::DFSIterator &Graph<V, E>::DFSIterator::operator++() {
    vertexIndexes.pop();
    for (int i = graph.vertices_.size()-1; i >= 0; --i) {
        if (!graph.adjMatrix_[vertexIndex][i] || visited[i]) {continue;}
        vertexIndexes.push(i);
        visited[i] = true;
    }
    if (vertexIndexes.empty()) {
        vertexIndex = graph.vertices_.size();
        return *this;
    }
    return *this;
}

template<typename V, typename E>
typename Graph<V, E>::DFSIterator Graph<V, E>::DFSIterator::operator++(int) {
    DFSIterator it(*this);
    ++(*this);
    return it;
}

template<typename V, typename E>
V &Graph<V, E>::DFSIterator::operator*() const {
    vertexIndex = vertexIndexes.top();
    return graph.vertices_[vertexIndex];
}

template<typename V, typename E>
V *Graph<V, E>::DFSIterator::operator->() const {
    vertexIndex = vertexIndexes.top();
    return &graph.vertices[vertexIndex];
}

template<typename V, typename E>
Graph<V, E>::DFSIterator::operator bool() const {
    if(vertexIndex<graph.vertices_.size()){
        return true;
    }else{
        return false;
    }
}

template<typename V, typename E>
Graph<V, E>::BFSIterator::operator bool() const {
    if(vertexIndex<graph.vertices_.size()){
        return true;
    }else{
        return false;
    }
}


template<typename V, typename E>
Graph<V, E>::BFSIterator::BFSIterator(Graph<V, E> &graph, size_t curr_id) : graph(graph), vertexIndex(curr_id) {
    for (int i = 0; i < graph.vertices_.size(); ++i) {
        visited.push_back(false);
    }
    vertexIndexes.push(vertexIndex);
    visited[vertexIndex] = true;
}

template<typename V, typename E>
typename Graph<V, E>::BFSIterator &Graph<V, E>::BFSIterator::operator++() {
    vertexIndexes.pop();
    for (int i = 0; i < graph.vertices_.size(); ++i) {
        if (!graph.adjMatrix_[vertexIndex][i] || visited[i]) {continue;}
        vertexIndexes.push(i);
        visited[i] = true;
    }
    if (vertexIndexes.empty()) {
        vertexIndex = graph.vertices_.size();
    }
    return *this;
}

template<typename V, typename E>
typename Graph<V, E>::BFSIterator Graph<V, E>::BFSIterator::operator++(int) {
    DFSIterator it(*this);
    ++(*this);
    return it;
}

template<typename V, typename E>
V &Graph<V, E>::BFSIterator::operator*() const {
    vertexIndex = vertexIndexes.front();
    return graph.vertices_[vertexIndex];
}

template<typename V, typename E>
V *Graph<V, E>::BFSIterator::operator->() const {
    vertexIndex = vertexIndexes.front();
    return &graph.vertices_[vertexIndex];
}




