// Dead Code - Graph Class
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct GraphNode {
    int vertex;
    int weight;
    struct GraphNode* next;
} GraphNode;

typedef struct {
    GraphNode* adjacency_list[MAX_VERTICES];
    int num_vertices;
    int is_directed;
} Graph;

Graph* graph_create(int num_vertices, int is_directed) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph) {
        graph->num_vertices = num_vertices > MAX_VERTICES ? MAX_VERTICES : num_vertices;
        graph->is_directed = is_directed;
        for (int i = 0; i < MAX_VERTICES; i++) {
            graph->adjacency_list[i] = NULL;
        }
    }
    return graph;
}

void graph_add_edge(Graph* graph, int from, int to, int weight) {
    if (graph && from >= 0 && from < graph->num_vertices && 
        to >= 0 && to < graph->num_vertices) {
        GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
        if (node) {
            node->vertex = to;
            node->weight = weight;
            node->next = graph->adjacency_list[from];
            graph->adjacency_list[from] = node;
            
            if (!graph->is_directed) {
                GraphNode* reverse_node = (GraphNode*)malloc(sizeof(GraphNode));
                if (reverse_node) {
                    reverse_node->vertex = from;
                    reverse_node->weight = weight;
                    reverse_node->next = graph->adjacency_list[to];
                    graph->adjacency_list[to] = reverse_node;
                }
            }
        }
    }
}

int graph_has_edge(Graph* graph, int from, int to) {
    if (graph && from >= 0 && from < graph->num_vertices && 
        to >= 0 && to < graph->num_vertices) {
        GraphNode* node = graph->adjacency_list[from];
        while (node != NULL) {
            if (node->vertex == to) {
                return 1;
            }
            node = node->next;
        }
    }
    return 0;
}

void graph_print(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->num_vertices; i++) {
            printf("Vertex %d: ", i);
            GraphNode* node = graph->adjacency_list[i];
            while (node != NULL) {
                printf("-> %d (w:%d) ", node->vertex, node->weight);
                node = node->next;
            }
            printf("\n");
        }
    }
}

int graph_get_degree(Graph* graph, int vertex) {
    if (graph && vertex >= 0 && vertex < graph->num_vertices) {
        int degree = 0;
        GraphNode* node = graph->adjacency_list[vertex];
        while (node != NULL) {
            degree++;
            node = node->next;
        }
        return degree;
    }
    return -1;
}

void graph_destroy(Graph* graph) {
    if (graph) {
        for (int i = 0; i < MAX_VERTICES; i++) {
            GraphNode* node = graph->adjacency_list[i];
            while (node != NULL) {
                GraphNode* next = node->next;
                free(node);
                node = next;
            }
        }
        free(graph);
    }
}

