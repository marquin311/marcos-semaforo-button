#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#define LED_AZUL 13
#define LED_VERMELHO 12
#define LED_VERDE 11
#define BOTAO 5

volatile bool leds_ativos = false; // Indica se os LEDs estão em sequência

// Prototipação das funções de callback
int64_t desligar_led_azul(alarm_id_t id, void *user_data);
int64_t desligar_led_vermelho(alarm_id_t id, void *user_data);
int64_t desligar_led_verde(alarm_id_t id, void *user_data);
int64_t resetar_estado(alarm_id_t id, void *user_data);

// Callback para desligar o LED azul
int64_t desligar_led_azul(alarm_id_t id, void *user_data) {
    gpio_put(LED_AZUL, 0);
    add_alarm_in_ms(3000, desligar_led_vermelho, NULL, false); // Agenda o desligamento do verde
    return 0;
}

// Callback para desligar o LED vermelho
int64_t desligar_led_vermelho(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERMELHO, 0);
    add_alarm_in_ms(3000, desligar_led_verde, NULL, false); // Agenda o desligamento do verde
    return 0;
}

// Callback para desligar o LED verde
int64_t desligar_led_verde(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERDE, 0);
    add_alarm_in_ms(3000, resetar_estado, NULL, false); // Aguarda mais 3s antes de liberar o botão
    return 0;
}

// Callback para resetar o estado e permitir novo acionamento do botão
int64_t resetar_estado(alarm_id_t id, void *user_data) {
    leds_ativos = false; // Libera o botão para um novo acionamento
    return 0;
}

int main() {
    stdio_init_all();

    // Configuração dos LEDs como saída
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Configuração do botão como entrada com pull-up interno
    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);

    while (true) {
        // Verifica se o botão foi pressionado e se os LEDs não estão ativos
        if (gpio_get(BOTAO) == 0 && !leds_ativos) {
            sleep_ms(50); // Debounce

            if (gpio_get(BOTAO) == 0) { // Confirma a pressão do botão
                leds_ativos = true; // Impede novos acionamentos durante a sequência

                // Liga todos os LEDs
                gpio_put(LED_AZUL, 1);
                gpio_put(LED_VERMELHO, 1);
                gpio_put(LED_VERDE, 1);

                // Inicia a sequência de desligamento com 3 segundos de intervalo
                add_alarm_in_ms(3000, desligar_led_azul, NULL, false);
            }
        }
        sleep_ms(10); // Pequena pausa para evitar uso excessivo da CPU
    }

    return 0;
}
