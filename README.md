
Configuração Inicial:

Define os pinos dos LEDs como saída.
Configura o botão como entrada com pull-up interno.
Define leds_ativos = false para indicar que o sistema está pronto para um novo acionamento.

Lógica do Botão:

Quando pressionado, acende todos os LEDs e ativa leds_ativos = true para impedir novas ativações.
Usa sleep_ms(50) para debounce.
Confirma a leitura do botão antes de acionar a sequência.

Sequência de Desligamento com add_alarm_in_ms():

Após 3s, desliga o LED verde e agenda o desligamento do vermelho.
Após mais 3s, desliga o LED vermelho e agenda o desligamento do azul.
Após mais 3s, desliga o LED azul e agenda o reset do estado.
Após mais 3s, libera o botão para um novo acionamento.

Componentes Utilizados:

1x Raspberry Pi Pico W
1x Botão (pushbutton)
3x LEDs (Azul, Vermelho e Verde)
3x Resistores de 330Ω

Esquema de Ligação:

Botão (Push):	GPIO 5
LED Azul:	GPIO 13
LED Vermelho:	GPIO 12
LED Verde: GPIO 11
