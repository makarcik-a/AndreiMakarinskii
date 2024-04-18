#include <array>
#include <iostream>
#include <queue>

struct GraphNode
{
    int value;
    bool visited;
    std::array<GraphNode*, 2> neighbors;
};

GraphNode* createGraph() {
    GraphNode* n1 = new GraphNode{};
    n1->value = 1;
    n1->visited = false;

    GraphNode* n2 = new GraphNode{};
    n2->value = 2;
    n2->visited = false;

    GraphNode* n3 = new GraphNode{};
    n3->value = 3;
    n3->visited = false;

    GraphNode* n4 = new GraphNode{};
    n4->value = 4;
    n4->visited = false;

    GraphNode* n5 = new GraphNode{};
    n5->value = 5;
    n5->visited = false;

    GraphNode* n6 = new GraphNode{};
    n6->value = 6;
    n6->visited = false;

    n1->neighbors[0] = n4;
    n1->neighbors[1] = n5;

    n2->neighbors[0] = n1;
    n2->neighbors[1] = n6;

    n3->neighbors[0] = nullptr;
    n3->neighbors[1] = nullptr;

    n4->neighbors[0] = n1;
    n4->neighbors[1] = nullptr;

    n5->neighbors[0] = n2;
    n5->neighbors[1] = n3;

    n6->neighbors[0] = nullptr;
    n6->neighbors[1] = n4;

    return n1;
}

void printNeighborsValue(GraphNode* node) {
    if (node) {
        std::cout << "Neighbors of node with value " << node->value << " are: ";
        for (GraphNode* neighbor : node->neighbors) {
            if (neighbor) //check if node != nullptr
                std::cout << neighbor->value << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Invalid node!" << std::endl;
    }
}

int calculateSumOfNeighborsValue(GraphNode* node) {
    int sum = 0;
    
    if (node) {
        for (GraphNode* neighbor : node->neighbors) {
            if (neighbor) //check if node != nullptr
                sum += neighbor->value;
        }
    }

    return sum;
}

void DFS(GraphNode* node) {
    if (!node || node->visited)
        return;

    std::cout << "Visiting node with value " << node->value << std::endl;
    node->visited = true;

    for (GraphNode* neighbor : node->neighbors) {
        DFS(neighbor);
    }
}

void BFS(GraphNode* node) {
    if (!node)
        return;

    std::queue<GraphNode*> q;
    q.push(node);
    node->visited = true;

    while (!q.empty()) {
        GraphNode* current = q.front();
        q.pop();
        std::cout << "Visiting node with value " << current->value << std::endl;

        for (GraphNode* neighbor : current->neighbors) {
            if (neighbor && !neighbor->visited) {
                q.push(neighbor);
                neighbor->visited = true;
            }
        }
    }
}

int main() {
    
    GraphNode* graph = createGraph();

    GraphNode* n2 = graph->neighbors[1]->neighbors[0]; //Get pointer to node n2 (n1->n5->n2)

    printNeighborsValue(n2);
    std::cout << "Sum of Neighbors Values is: " << calculateSumOfNeighborsValue(n2) << std::endl;

    //BFS(graph);
    DFS(graph);

    return 0;
}