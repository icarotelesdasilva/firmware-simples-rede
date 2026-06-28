#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "ferramentas.h"

static const char *TAG = "SCAN_WIFI";

void wifi_scan_task(void *pvParameters) {
    ESP_LOGI(TAG, "Tarefa de scan iniciada!");
    
    while(1) {
        ESP_LOGI(TAG, "Escaneando redes...");
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
