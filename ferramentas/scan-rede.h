#ifndef SCAN_H_
#define SCAN_H_

#include "esp_err.h" // Necessário para reconhecer o tipo esp_err_t

// Definição do tamanho máximo da lista de redes (usado na sua Task)
#define DEFAULT_SCAN_LIST_SIZE 20

/**
 * @brief Inicializa todos os subsistemas de hardware e rede para o Wi-Fi.
 * Deve ser chamada no início da app_main.
 * * @return esp_err_t Retorna ESP_OK se tudo foi iniciado corretamente, 
 * ou o código de erro correspondente.
 */
esp_err_t inicializar_sistema_scan(void);

#endif /* SCAN_H_ */