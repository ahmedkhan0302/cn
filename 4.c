#include <stdio.h>
#include <limits.h>

#define max 100

void print_path(int parent[], int dest) {
    int path[max], path_len = 0;
    while (dest != -1) {
        path[path_len++] = dest;
        dest = parent[dest];
    }

    // Print in reverse (source to destination)
    for (int i = path_len - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" -> ");
    }
}

void dijkstra(int graph[max][max], int v, int src) {
    int dist[max], visited[max] = {0}, parent[max];

    for (int i = 0; i < v; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < v - 1; count++) {
        int u = -1;

        for (int i = 0; i < v; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }

        visited[u] = 1;

        for (int w = 0; w < v; w++) {
            if (graph[u][w] && !visited[w] && dist[u] + graph[u][w] < dist[w]) {
                dist[w] = dist[u] + graph[u][w];
                parent[w] = u;
            }
        }
    }

    printf("\nShortest distances and paths from router %d:\n", src);
    for (int i = 0; i < v; i++) {
        printf("To %d: Distance = ", i);
        if (dist[i] == INT_MAX)
            printf("-1 | No path\n");
        else {
            printf("%d | Path: ", dist[i]);
            print_path(parent, i);
            printf("\n");
        }
    }
}

int main() {
    int graph[max][max] = {0}, V, E;
    printf("Enter number of routers and connections: ");
    scanf("%d %d", &V, &E);

    printf("Enter edges (from to cost):\n");
    for (int i = 0; i < E; i++) {
        int u, v, cost;
        scanf("%d %d %d", &u, &v, &cost);
        graph[u][v] = cost;
        graph[v][u] = cost;  // bidirectional
    }

    int src;
    printf("Enter source router: ");
    scanf("%d", &src);

    dijkstra(graph, V, src);
    return 0;
}
