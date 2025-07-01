#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    int num1, num2, result;
    char op;

    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &op);  // Note the space before %c

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    write(client_socket, &num1, sizeof(num1));
    write(client_socket, &num2, sizeof(num2));
    write(client_socket, &op, sizeof(op));

    read(client_socket, &result, sizeof(result));

    if (op == '/' && num2 == 0)
        printf("Error: Division by zero\n");
    else
        printf("Result: %d %c %d = %d\n", num1, op, num2, result);

    close(client_socket);
    return 0;
}
/*#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i; // return index
    }
    return -1; // not found
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    int arr[10], key, index;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 1);
    client_socket = accept(server_socket, NULL, NULL);

    read(client_socket, arr, sizeof(arr));   // read 10 integers
    read(client_socket, &key, sizeof(key));  // read key to search

    index = linearSearch(arr, 10, key);

    write(client_socket, &index, sizeof(index)); // send result

    close(client_socket);
    close(server_socket);
    return 0;
}*/

//gcc echo_server.c -o server
//gcc echo_client.c -o client

//./server
//./client
