#pragma once

#include <functional>
#include <vector>
#include <stack>
#include <queue>
#include "graph.h"

using namespace std;

template <typename V, typename E>
void DFS(const Graph<V, E> &g, std::size_t start_id, std::function<void(const V&)> f) {

    if (start_id < 0 || g.vertices_.size() <= 0) return;
    size_t index = start_id;
    vector<bool> visited(g.vertices_.size());
    stack<int> vertexStack;

    for(size_t i = 0; i < g.vertices_.size(); ++i) {
        visited.push_back(false);
    }
    vertexStack.push(index);
    visited[index] = true;

    do {
        index = vertexStack.top();
        vertexStack.pop();
        for (size_t i = 0; i < g.vertices_.size(); ++i) {
            if (g.adjMatrix_[index][i] && !visited[i]) {
                vertexStack.push(i);
                visited[i] = true;
            }
        }
        f(g.vertexData(index));
    } while (!vertexStack.empty());
}

template <typename V, typename E>
void BFS(const Graph<V, E> &g, std::size_t start_id, std::function<void(const V&)> f) {

    if (start_id < 0 || g.vertices_.size() <= 0) return;
    size_t index = start_id;
    vector<bool> visited(g.vertices_.size());
    queue<int> vertexQueue;
    for(size_t i = 0; i < g.vertices_.size(); ++i) {
        visited.push_back(false);
    }
    vertexQueue.push(index);
    visited[index] = true;
    do {
        index = vertexQueue.front();
        vertexQueue.pop();
        for (size_t i = 0; i < g.vertices_.size(); ++i) {
            if (g.adjMatrix_[index][i] && !visited[i]) {
                vertexQueue.push(i);
                visited[i] = true;
            }
        }
        f(g.vertexData(index));
    } while (!vertexQueue.empty());

}



template<typename V, typename E>
std::pair<double, std::vector<std::size_t>> dijkstra(Graph<V, E>& graph, std::size_t start_idx, std::size_t end_idx, std::function<double(const E&)> getEdgeLength = nullptr){
    std::vector<double > traversalCost(graph.vertices_.size());
    std::vector<bool>checkedVertices(graph.vertices_.size());
    std::vector<int>predecessors(graph.vertices_.size());
    std::fill(traversalCost.begin(), traversalCost.end(), std::numeric_limits<int>::max());
    std::fill(checkedVertices.begin(), checkedVertices.end(), false);
    std::fill(predecessors.begin(), predecessors.end(), -1);
    traversalCost[start_idx] = 0;

    while(!checkedVertices[end_idx]) {
        double minimalCost = std::numeric_limits<double>::max();
        int minimalIndex = -1;
        for (int j = 0; j < graph.vertices_.size(); ++j) {
            if (!checkedVertices[j] && traversalCost[j] < minimalCost) {
                minimalCost = traversalCost[j];
                minimalIndex = j;
            }
        }

        std::vector<std::size_t> path;
        if (minimalIndex == -1) {
            return std::make_pair(minimalIndex, path);
        }

        checkedVertices[minimalIndex] = true;
        for (int j = 0; j < graph.vertices_.size(); ++j) {
            if (graph.adjMatrix_[minimalIndex][j] && !checkedVertices[j]) {
                if (traversalCost[j] > (traversalCost[minimalIndex] + graph.adjMatrix_[minimalIndex][j].value()) ) {
                    if(getEdgeLength == nullptr){
                        traversalCost[j] = traversalCost[minimalIndex] + graph.adjMatrix_[minimalIndex][j].value();
                    }else{
                        traversalCost[j] = traversalCost[minimalIndex] + getEdgeLength(graph.adjMatrix_[minimalIndex][j].value());
                    }
                    predecessors[j] = minimalIndex;
                }
            }
        }
    }

    std::vector<std::size_t> path;
    path.push_back(end_idx);

    int temp = predecessors[end_idx];
    while (temp != -1) {
        path.push_back(temp);
        temp = predecessors[temp];
    }
    std::reverse(path.begin(), path.end());

    return std::make_pair(traversalCost[end_idx], path);
}




template<typename V, typename E>
std::pair<double, std::vector<std::size_t>> astar(const Graph<V, E> &graph, std::size_t start_idx, std::size_t end_idx,
        std::function<double(const Graph<V, E> &, size_t actual_vertex_id, size_t end_vertex_id)> heuristics,
        std::function<double (const E &)> getEdgeLenght = nullptr){

    std::vector<double> gCost(graph.vertices_.size());
    std::vector<double> fCost(graph.vertices_.size());
    std::vector<bool>costNotKnown(graph.vertices_.size());
    std::vector<bool>knownCost(graph.vertices_.size());
    std::vector<int>predecessors(graph.vertices_.size());

    std::fill(gCost.begin(), gCost.end(), numeric_limits<double>::max());
    std::fill(fCost.begin(), fCost.end(), numeric_limits<double>::max());
    std::fill(costNotKnown.begin(), costNotKnown.end(), true);
    std::fill(knownCost.begin(), knownCost.end(), false);
    std::fill(predecessors.begin(), predecessors.end(), -1);

    costNotKnown[start_idx] = true;
    gCost[start_idx] = 0;
    fCost[start_idx] = heuristics(graph, start_idx, end_idx);

    size_t curr_idx = 0;
    while(std::find(costNotKnown.begin(), costNotKnown.end(), true) != costNotKnown.end() && curr_idx != end_idx) {
        double minimalCost = std::numeric_limits<double>::max();
        int minimalIndex = -1;
        for (int j = 0; j < graph.vertices_.size(); ++j) {
            if (costNotKnown[j] && fCost[j] < minimalCost) {
                minimalCost = fCost[j];
                minimalIndex = j;
            }
        }
        costNotKnown[minimalIndex] = false;
        knownCost[minimalIndex] = true;
        curr_idx = minimalIndex;

        for (int j = 0; j < graph.vertices_.size(); ++j) {
            if (!knownCost[j] && graph.adjMatrix_[minimalIndex][j]) {
                double temp;
                if(getEdgeLenght == nullptr)
                    temp = gCost[minimalIndex] + graph.adjMatrix_[minimalIndex][j].value();
                else
                    temp = gCost[minimalIndex] + getEdgeLenght(graph.adjMatrix_[minimalIndex][j].value());
                if (!costNotKnown[j]) {
                    costNotKnown[j] = true;
                } else if (temp >= gCost[j]) {
                    continue;
                }
                predecessors[j] = minimalIndex;
                gCost[j] = temp;
                fCost[j] = gCost[j] + heuristics(graph, j, end_idx);
            }
        }
    }

    std::vector<std::size_t> path;
    if (fCost[end_idx] == std::numeric_limits<int>::max()) { return std::make_pair(-1, path); }

    path.push_back(end_idx);
    int temp = predecessors[end_idx];
    while (temp != -1) {
        path.push_back(temp);
        temp = predecessors[temp];
    }
    std::reverse(path.begin(), path.end());

    return std::make_pair(fCost[end_idx], path);
}
