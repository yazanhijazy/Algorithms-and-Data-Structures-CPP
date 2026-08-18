#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>

class DirectedGraph {
public:
    explicit DirectedGraph(std::size_t vertexCount)
        : adjacencyMatrix_(vertexCount, std::vector<int>(vertexCount, 0)) {}

    void addEdge(std::size_t from, std::size_t to) {
        validateVertex(from);
        validateVertex(to);
        adjacencyMatrix_[from][to] = 1;
    }

    std::size_t edgeCount() const {
        std::size_t count = 0;
        for (const auto& row : adjacencyMatrix_) {
            for (const int value : row) {
                count += static_cast<std::size_t>(value != 0);
            }
        }
        return count;
    }

    std::size_t outDegree(std::size_t vertex) const {
        validateVertex(vertex);
        std::size_t count = 0;
        for (const int value : adjacencyMatrix_[vertex]) {
            count += static_cast<std::size_t>(value != 0);
        }
        return count;
    }

    std::size_t inDegree(std::size_t vertex) const {
        validateVertex(vertex);
        std::size_t count = 0;
        for (const auto& row : adjacencyMatrix_) {
            count += static_cast<std::size_t>(row[vertex] != 0);
        }
        return count;
    }

    bool hasEdge(std::size_t from, std::size_t to) const {
        validateVertex(from);
        validateVertex(to);
        return adjacencyMatrix_[from][to] != 0;
    }

    void print() const {
        std::cout << "Adjacency matrix:\n";
        for (const auto& row : adjacencyMatrix_) {
            for (const int value : row) {
                std::cout << value << ' ';
            }
            std::cout << '\n';
        }
    }

    std::vector<std::size_t> topologicalSort() const {
        const std::size_t n = adjacencyMatrix_.size();
        std::vector<std::size_t> indegrees(n, 0);
        std::queue<std::size_t> ready;

        for (std::size_t vertex = 0; vertex < n; ++vertex) {
            indegrees[vertex] = inDegree(vertex);
            if (indegrees[vertex] == 0) {
                ready.push(vertex);
            }
        }

        std::vector<std::size_t> order;
        while (!ready.empty()) {
            const std::size_t current = ready.front();
            ready.pop();
            order.push_back(current);

            for (std::size_t next = 0; next < n; ++next) {
                if (adjacencyMatrix_[current][next] != 0) {
                    --indegrees[next];
                    if (indegrees[next] == 0) {
                        ready.push(next);
                    }
                }
            }
        }

        if (order.size() != n) {
            throw std::runtime_error("Topological sort is impossible because the graph contains a cycle.");
        }
        return order;
    }

private:
    std::vector<std::vector<int>> adjacencyMatrix_;

    void validateVertex(std::size_t vertex) const {
        if (vertex >= adjacencyMatrix_.size()) {
            throw std::out_of_range("Vertex index is out of range.");
        }
    }
};

int main() {
    DirectedGraph graph(5);

    // Same directed graph used in the original coursework.
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 4);
    graph.addEdge(3, 1);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);

    graph.print();
    std::cout << "Number of edges: " << graph.edgeCount() << '\n';

    try {
        const auto order = graph.topologicalSort();
        std::cout << "Topological order: ";
        for (const std::size_t vertex : order) {
            std::cout << vertex << ' ';
        }
        std::cout << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
