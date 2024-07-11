#include "esp_camera.h"
#include "esp_log.h"

#include "server_connection.h"
#include "led_control.h"


#define TAG "esp32-cam_img_sender"

// Configuração da câmera

extern int sock;

void send_image_to_server() {
    
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(TAG, "Failed to capture image");
        return;
    }

    int image_size = fb->len;
    write(sock, &image_size, sizeof(image_size)); //Envia o tamanho da imagem para que o server saiba o tamanho da mensagem que chegará
    write(sock, fb->buf, image_size);


    // while (bytes_written < fb->len) {
    //     ssize_t written = write(sock, fb->buf + bytes_written, fb->len - bytes_written);
    //     if (written < 0) {
    //         ESP_LOGE(TAG, "Failed to send image data");
    //         break;
    //     }
    //     bytes_written += written;
    // }

    esp_camera_fb_return(fb);
    // ESP_LOGI(TAG, "Image sent, waiting for finger count");
    // ESP_LOGI(TAG, "Image captured, size: %zu", fb->len);

    // Receber a quantidade de dedos levantados do servidor
    int finger_count;
    if (read(sock, &finger_count, sizeof(finger_count)) == sizeof(finger_count)) {
        //  ESP_LOGI(TAG, "Finger count received: %d", finger_count);
         set_leds(finger_count);
    } else {
         ESP_LOGE(TAG, "Failed to receive finger count");
    }

    
    // close(sock);
}

void take_picture() {
    // camera_fb_t *fb = esp_camera_fb_get();
    // if (!fb) {
    //     ESP_LOGE(TAG, "Failed to capture image");
    //     return;
    // }
    // ESP_LOGI(TAG, "Image captured, size: %zu", fb->len);
    // esp_camera_fb_return(fb);

    const char* message = "teste";
    // write(sock, m)
    int message_size = strlen(message);
    write(sock, &message_size, sizeof(message_size)); //enviar o tamanho da imagem
    write(sock, message, message_size);
        

}
