# 🌡️ Sistema IoT de Monitoramento de Temperatura e Umidade com MQTT
Este projeto utiliza o ESP32, o sensor DHT11 e o protocolo MQTT para monitorar a temperatura e a umidade em tempo real. Os dados coletados são enviados para a plataforma Adafruit IO, onde podem ser visualizados por meio de gráficos e medidores interativos.

⚙️ Funcionalidades  
Monitoramento Local:  
- LED vermelho acende quando a temperatura excede 28°C.  
- LED verde acende quando a temperatura está abaixo de 28°C.  

Monitoramento Remoto:  
- Dados de temperatura e umidade são enviados via MQTT para a Adafruit IO.  
- Visualização em gráficos (line chart) e medidores (gauge) no dashboard do Adafruit.  

Conexão Automática:  
- Reconexão automática ao WiFi e ao broker MQTT em caso de desconexões.

🖥️ Hardware Utilizado  
- ESP32: Microcontrolador com WiFi integrado.  
- Sensor DHT11: Mede temperatura e umidade.  
- LEDs: Sinalizam o status da temperatura.  
- Protoboard e Fios Jumper: Para prototipagem.  

🛠️ Configuração  
1. Clone o Repositório  
```bash
git clone https://github.com/seu-usuario/seu-repositorio.git
cd seu-repositorio
```
2. Instale as bibliotecas necessárias  
  - Na Arduino IDE, instale as seguintes bibliotecas:
  - Adafruit MQTT Library
  - DHT Sensor Library
    
3. Altere as Credenciais
  - Substitua as credenciais no código:
    ```bash
    #define WLAN_SSID "NOME_DO_WIFI"
    #define WLAN_PASS "SENHA_DO_WIFI"
    #define MQTT_USERNAME "SEU_USUARIO_ADAFRUIT"
    #define MQTT_KEY "SUA_CHAVE_ADAFRUIT"
    ```
4. Carregue o Código
  - Conecte o ESP32 ao computador.
  - Na Arduino IDE, selecione:
    - Placa: "ESP32 Dev Module"
    - Porta correspondente ao ESP32.
  - Clique em Upload.

📊 Dashboard no Adafruit IO
Os dados coletados pelo sensor são enviados para o Adafruit IO e visualizados em:
1. Gráficos de linha (line charts):
  - Monitoram a variação de temperatura e umidade ao longo do tempo.
2. Medidores (gauges):
  - Exibem os valores instantâneos de temperatura e umidade.
Configuração do Dashboard
  - Crie dois feeds no Adafruit IO:
    - temperatura
    - umidade
  -Adicione os blocos (blocks) no dashboard:
    - Gauge: Para temperatura (0-50°C) e umidade (0-100%).
    - Line Chart: Para monitorar as leituras ao longo do tempo.

📜 Licença
Este projeto está licenciado sob a MIT License. Sinta-se à vontade para usar e modificar.
