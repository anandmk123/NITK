#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 1000
#define MAX_CONNECTIONS 100

// Structure to represent a person (node)
typedef struct {
    int id;                       // ID of the person
    int neighbors[MAX_CONNECTIONS]; // List of neighbors (people they know)
    int neighborCount;            // Number of neighbors
} Node;

// Structure to represent the graph
typedef struct {
    int n;                        // Number of nodes (people)
    Node nodes[MAX_PEOPLE];       // Array of people
} Graph;

// Function prototypes
void initializeGraph(Graph *graph, int n);
void addEdge(Graph *graph, int person1, int person2);
void filterNodes(Graph *graph, bool invitees[MAX_PEOPLE]);
int countRelationships(Node *person, Graph *graph, bool invitees[MAX_PEOPLE], bool countKnows);

// Test case 1: Less than 10 people, none satisfy the conditions
void testCase1() {
    Graph graph;

    // Initialize graph with 9 nodes
    initializeGraph(&graph, 9);

    // Add edges (relationships)
    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 2);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 2, 4);
    addEdge(&graph, 3, 5);
    addEdge(&graph, 4, 6);
    addEdge(&graph, 5, 7);
    addEdge(&graph, 6, 8);

    // Initial invitee list (everyone is invited initially)
    bool invitees[MAX_PEOPLE];
    for (int i = 0; i < graph.n; i++) {
        invitees[i] = true;
    }

    // Filter the invitees based on constraints
    filterNodes(&graph, invitees);

    // Print the final invitee list
    printf("Test Case 1: Invitees:\n");
    bool found = false;
    for (int i = 0; i < graph.n; i++) {
        if (invitees[i]) {
            printf("%d ", i);
            found = true;
        }
    }
    if (!found) {
        printf("No one can be invited.\n");
    }
    printf("\n");
}

// Test case 2: More than 10 people, some know each other
void testCase2() {
    Graph graph;

    // Initialize graph with 12 nodes
    initializeGraph(&graph, 12);

    // Add edges (relationships)
    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 2);
    addEdge(&graph, 0, 3);
    addEdge(&graph, 1, 4);
    addEdge(&graph, 1, 5);
    addEdge(&graph, 2, 6);
    addEdge(&graph, 2, 7);
    addEdge(&graph, 3, 8);
    addEdge(&graph, 3, 9);
    addEdge(&graph, 4, 10);
    addEdge(&graph, 5, 11);
    addEdge(&graph, 6, 7);

    // Initial invitee list (everyone is invited initially)
    bool invitees[MAX_PEOPLE];
    for (int i = 0; i < graph.n; i++) {
        invitees[i] = true;
    }

    // Filter the invitees based on constraints
    filterNodes(&graph, invitees);

    // Print the final invitee list
    printf("Test Case 2: Invitees:\n");
    bool found = false;
    for (int i = 0; i < graph.n; i++) {
        if (invitees[i]) {
            printf("%d ", i);
            found = true;
        }
    }
    if (!found) {
        printf("No one can be invited.\n");
    }
    printf("\n");
}

// Test case 3: Three separate complete graphs of 6 people each (18 people in total)
void testCase3() {
    Graph graph;

    // Initialize graph with 18 nodes
    initializeGraph(&graph, 18);

    // Create three separate complete graphs of 6 people each
    // First complete graph: people 0 to 5
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            addEdge(&graph, i, j);
        }
    }

    // Second complete graph: people 6 to 11
    for (int i = 6; i < 12; i++) {
        for (int j = i + 1; j < 12; j++) {
            addEdge(&graph, i, j);
        }
    }

    // Third complete graph: people 12 to 17
    for (int i = 12; i < 18; i++) {
        for (int j = i + 1; j < 18; j++) {
            addEdge(&graph, i, j);
        }
    }

    // Initial invitee list (everyone is invited initially)
    bool invitees[MAX_PEOPLE];
    for (int i = 0; i < graph.n; i++) {
        invitees[i] = true;
    }

    // Filter the invitees based on constraints
    filterNodes(&graph, invitees);

    // Print the final invitee list
    printf("Test Case 3: Invitees:\n");
    bool found = false;
    for (int i = 0; i < graph.n; i++) {
        if (invitees[i]) {
            printf("%d ", i);
            found = true;
        }
    }
    if (!found) {
        printf("No one can be invited.\n");
    }
    printf("\n");
}

int main() {
    // Run each test case
    testCase1();
    testCase2();
    testCase3();

    return 0;
}

// Initialize the graph
void initializeGraph(Graph *graph, int n) {
    graph->n = n;
    for (int i = 0; i < n; i++) {
        graph->nodes[i].id = i;
        graph->nodes[i].neighborCount = 0;
    }
}

// Add an edge (relationship) between two people
void addEdge(Graph *graph, int person1, int person2) {
    // Add person2 to person1's neighbor list
    graph->nodes[person1].neighbors[graph->nodes[person1].neighborCount++] = person2;
    // Add person1 to person2's neighbor list
    graph->nodes[person2].neighbors[graph->nodes[person2].neighborCount++] = person1;
}

// Filter the invitees based on the constraints
void filterNodes(Graph *graph, bool invitees[MAX_PEOPLE]) {
    bool changed;
    do {
        changed = false;
        for (int i = 0; i < graph->n; i++) {
            if (!invitees[i]) continue;

            // Count neighbors and non-neighbors
            int neighbors = countRelationships(&graph->nodes[i], graph, invitees, true);
            int nonNeighbors = countRelationships(&graph->nodes[i], graph, invitees, false);

            // Remove person if they fail either condition
            if (neighbors < 5 || nonNeighbors < 5) {
                invitees[i] = false;
                changed = true;
            }
        }
    } while (changed);
}

// Count neighbors or non-neighbors for a given person
int countRelationships(Node *person, Graph *graph, bool invitees[MAX_PEOPLE], bool countKnows) {
    int count = 0;

    // Iterate through all people
    for (int i = 0; i < graph->n; i++) {
        if (i == person->id || !invitees[i]) continue;

        // Check if the person knows or does not know `i`
        bool knows = false;
        for (int j = 0; j < person->neighborCount; j++) {
            if (person->neighbors[j] == i) {
                knows = true;
                break;
            }
        }

        if ((countKnows && knows) || (!countKnows && !knows)) {
            count++;
        }
    }
    return count;
}
