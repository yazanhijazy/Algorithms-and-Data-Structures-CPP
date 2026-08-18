#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

struct Edge {
    int source;
    int destination;
    int weight;
};

class DisjointSet {
public:
    explicit DisjointSet(int size) : parent_(size), rank_(size, 0) {
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int vertex) {
        if (parent_[vertex] != vertex) {
            parent_[vertex] = find(parent_[vertex]);
        }
        return parent_[vertex];
    }

    bool unite(int first, int second) {
        int rootFirst = find(first);
        int rootSecond = find(second);

        if (rootFirst == rootSecond) {
            return false;
        }

        if (rank_[rootFirst] < rank_[rootSecond]) {
            std::swap(rootFirst, rootSecond);
        }
        parent_[rootSecond] = rootFirst;

        if (rank_[rootFirst] == rank_[rootSecond]) {
            ++rank_[rootFirst];
        }
        return true;
    }

private:
    std::vector<int> parent_;
    std::vector<int> rank_;
};

std::vector<Edge> kruskalMST(int vertexCount, std::vector<Edge> edges) {
    std::sort(edges.begin(), edges.end(), [](const Edge& first, const Edge& second) {
        return first.weight < second.weight;
    });

    DisjointSet sets(vertexCount);
    std::vector<Edge> mst;

    for (const Edge& edge : edges) {
        if (sets.unite(edge.source, edge.destination)) {
            mst.push_back(edge);
            if (mst.size() == static_cast<std::size_t>(vertexCount - 1)) {
                break;
            }
        }
    }

    if (vertexCount > 0 && mst.size() != static_cast<std::size_t>(vertexCount - 1)) {
        throw std::runtime_error("The graph is disconnected; a spanning tree does not exist.");
    }
    return mst;
}

int main() {
    int vertexCount = 0;
    int edgeCount = 0;

    std::cout << "Enter number of vertices: ";
    if (!(std::cin >> vertexCount) || vertexCount <= 0) {
        std::cerr << "Invalid number of vertices.\n";
        return 1;
    }

    std::cout << "Enter number of edges: ";
    if (!(std::cin >> edgeCount) || edgeCount < 0) {
        std::cerr << "Invalid number of edges.\n";
        return 1;
    }

    std::vector<Edge> edges;
    edges.reserve(static_cast<std::size_t>(edgeCount));

    std::cout << "Enter each edge as: source destination weight (0-based vertices)\n";
    for (int i = 0; i < edgeCount; ++i) {
        Edge edge{};
        if (!(std::cin >> edge.source >> edge.destination >> edge.weight)) {
            std::cerr << "Invalid edge input.\n";
            return 1;
        }
        if (edge.source < 0 || edge.source >= vertexCount ||
            edge.destination < 0 || edge.destination >= vertexCount) {
            std::cerr << "Edge contains an invalid vertex index.\n";
            return 1;
        }
        edges.push_back(edge);
    }

    try {
        const auto mst = kruskalMST(vertexCount, edges);
        int totalWeight = 0;

        std::cout << "\nEdges in the Minimum Spanning Tree:\n";
        for (const Edge& edge : mst) {
            std::cout << edge.source << " - " << edge.destination
                      << " : " << edge.weight << '\n';
            totalWeight += edge.weight;
        }
        std::cout << "Total weight of MST: " << totalWeight << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
