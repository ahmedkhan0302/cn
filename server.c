#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    int num1, num2, result;
    char op;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 1);
    client_socket = accept(server_socket, NULL, NULL);

    read(client_socket, &num1, sizeof(num1));
    read(client_socket, &num2, sizeof(num2));
    read(client_socket, &op, sizeof(op));

    switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = (num2 != 0) ? (num1 / num2) : 0; break;
        default: result = 0; break;
    }

    write(client_socket, &result, sizeof(result));

    close(client_socket);
    close(server_socket);
    return 0;
}
/*#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    int arr[10], key, index;

    printf("Enter 10 integers:\n");
    for (int i = 0; i < 10; i++)
        scanf("%d", &arr[i]);

    printf("Enter the number to search: ");
    scanf("%d", &key);

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    write(client_socket, arr, sizeof(arr));   // send array
    write(client_socket, &key, sizeof(key));  // send key

    read(client_socket, &index, sizeof(index)); // receive result

    if (index == -1)
        printf("Element not found in the array.\n");
    else
        printf("Element found at index: %d\n", index);

    close(client_socket);
    return 0;
}
*/
