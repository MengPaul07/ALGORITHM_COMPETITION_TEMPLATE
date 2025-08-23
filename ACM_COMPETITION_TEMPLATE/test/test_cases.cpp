#include <iostream>
#include <cassert>
#include "../src/algorithms/graph/shortest_path.cpp"
#include "../src/algorithms/math/number_theory.cpp"
#include "../src/algorithms/data_structures/segment_tree.cpp"

void testShortestPath() {
    // Test case for shortest path algorithm
    Graph g(5); // Create a graph with 5 vertices
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 1, 3);
    g.addEdge(2, 3, 9);
    g.addEdge(2, 4, 2);
    g.addEdge(3, 4, 4);
    g.addEdge(4, 3, 6);
    
    std::vector<int> distances = g.dijkstra(0);
    assert(distances[0] == 0);
    assert(distances[1] == 8);
    assert(distances[2] == 5);
    assert(distances[3] == 9);
    assert(distances[4] == 7);
}

void testNumberTheory() {
    // Test case for number theory functions
    assert(isPrime(2) == true);
    assert(isPrime(4) == false);
    assert(gcd(48, 18) == 6);
    assert(lcm(4, 5) == 20);
}

void testSegmentTree() {
    // Test case for segment tree
    int arr[] = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr, 6);
    assert(st.query(1, 3) == 15); // Sum from index 1 to 3
    st.update(1, 10); // Update index 1 to 10
    assert(st.query(1, 3) == 22); // Sum from index 1 to 3 after update
}

int main() {
    testShortestPath();
    testNumberTheory();
    testSegmentTree();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}