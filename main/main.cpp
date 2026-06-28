#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_netif.h"

// Inclui o seu componente personalizado
#include "ferramentas.h" 

// 1. Definição do TAG de log (Corrige o erro de "TAG was not declared")
static const char *TAG = "MAIN_APP";

/**
 * @brief Inicializa todos os subsistemas de hardware e rede.
 * (Definida ANTES da app_main para o compilador achar)
 */
esp_err_t inicializar_sistema_scan(void) {
    ESP_LOGI(TAG, "Iniciando a inicializacao do sistema...");

    // Inicializa o armazenamento NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "NVS corrompido ou sem espaco. Apagando e reiniciando NVS...");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    if (ret != ESP_OK) return ret;

    // Inicializa o Loop de Eventos do Sistema
    ret = esp_event_loop_create_default();
    if (ret != ESP_OK) return ret;

    // Inicializa a pilha de rede TCP/IP e Wi-Fi
    ret = esp_netif_init();
    if (ret != ESP_OK) return ret;
    
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ret = esp_wifi_init(&cfg);
    if (ret != ESP_OK) return ret;

    ret = esp_wifi_set_mode(WIFI_MODE_STA);
    if (ret != ESP_OK) return ret;

    ret = esp_wifi_start();
    if (ret != ESP_OK) return ret;

    ESP_LOGI(TAG, "Hardware e drivers de Wi-Fi prontos!");
    return ESP_OK;
}

// ====================================================================
// PONTO DE ENTRADA DO PROGRAMA (MAIN)
// ====================================================================
extern "C" void app_main(void) {
    // 1. Chama a função de preparação
    if (inicializar_sistema_scan() != ESP_OK) {
        ESP_LOGE(TAG, "Falha critica na inicializacao! O sistema nao sera iniciado.");
        return; 
    }

    // 2. Cria a Task que roda em segundo plano vinda de ferramentas.h
    ESP_LOGI(TAG, "Disparando a tarefa de escaneamento continuo...");
    
    xTaskCreatePinnedToCore(
        wifi_scan_task,        
        "wifi_scan_task",      
        4096,                  
        NULL,                  
        2,                     
        NULL,                  
        0                      
    );
}
