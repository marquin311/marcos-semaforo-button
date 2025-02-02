
Configuração Inicial:

Define os pinos dos LEDs como saída.
Configura o botão como entrada com pull-up interno.
Define leds_ativos = false para indicar que o sistema está pronto para um novo acionamento.

Lógica do Botão:

Quando pressionado, acende todos os LEDs e ativa leds_ativos = true para impedir novas ativações.
Usa sleep_ms(50) para debounce.
Confirma a leitura do botão antes de acionar a sequência.

Sequência de Desligamento com add_alarm_in_ms():

Após 3s, desliga o LED vermelho e agenda o desligamento do verde.
Após mais 3s, desliga o LED verde e agenda o reset do estado.
Após mais 3s, libera o botão para um novo acionamento.
