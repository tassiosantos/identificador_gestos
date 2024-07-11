#include "esp_log.h"
#include <sys/socket.h>
#include "server_connection.h"

// IP do servidor e porta
#define SERVER_IP "192.168.1.101"
// #define SERVER_IP "192.168.0.130"
#define SERVER_PORT 1234

#define TAG "esp32-cam_server_connection"
int sock;

void server_connect(){
    
    int retries = 0;
    const int max_retries = 50;
    const int delay_between_retries = 1000; // 1 segundo em milissegundos

    do {
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
        if (sock < 0) {
            ESP_LOGE(TAG, "Failed to create socket");
            return;
        }

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr.s_addr);

        if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            ESP_LOGE(TAG, "Failed to connect to server, retrying...");
            close(sock);
            vTaskDelay(delay_between_retries / portTICK_PERIOD_MS);
            retries++;
        } else {
            ESP_LOGI(TAG, "Connected to server");
            break;
        }
    } while (retries < max_retries);

    if (retries >= max_retries) {
        ESP_LOGE(TAG, "Exceeded maximum retries, giving up");
        return;
    }

 
}
