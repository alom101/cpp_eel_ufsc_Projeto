# **Interface de abstração para sensores **

Projeto realizado para a disciplina de *C++ para embarcados* do curso de *Engenharia Eletrônica* da *Universidade Federal de Santa Catarina* no semestre 2024.2

Feito por:

Arthur Leones Osorio Machado \- 19103415

Pedro Felipe Bender \- 20150153


# **Introdução**

Este projeto tem como objetivo criar uma interface genérica em C++ para a leitura de dados de sensores e envio dessas informações para um dispositivo de armazenamento. A solução será desenvolvida com base nos princípios da Programação Orientada a Objetos (POO), garantindo flexibilidade e modularidade do código. O foco será implementar uma arquitetura modular que permita a integração de diferentes tipos de sensores e métodos de armazenamento sem alterações significativas na base do código.  
A arquitetura deste projeto será pensada para cenários onde é essencial integrar sensores e armazenar dados, como em sistemas IoT, automação industrial ou monitoramento ambiental. Usar Programação Orientada a Objetos (POO) vai facilitar a adição de novos tipos de sensores e formas de armazenar informações sem complicar o sistema. Isso ajuda a economizar tempo e esforço na manutenção e ainda reaproveitar partes do código em outros projetos.	 Além de permitir utilizar mais facilmente sensores disponíveis no mercado de forma simples e rápida.


# **Requisitos Minimos**

Para utilizar o sistema por completo, é necessário:
* Sensor: Algum sensor deve ser configurado utilizando o mecanismo de herança da classe Sensor ou de alguma das classes filha;
* Microcontrolador: Algum microcontrolador deve ser configurado a partir da herança da classe HAL, implementando os métodos para interação, com o hardware;
* Saida de dados: Alguma saida de dados deve ser configurada a partir da herança da classe DataOutput, esta saida pode ser desde um ´printf´ a um banco de dados na rede.


# **Objetivos**

* [CONCLUIDO] Desenvolvimento de uma classe Sensor que abstraia os detalhes de cada sensor, permitindo que o software seja desenvolvido utilizando uma interface em comum para obtenção de dados;  
* [CONCLUIDO] Desenvolvimento de uma classe DataOutput que abstraia os dispositivos de armazenamento e servidores externos, permitindo sua substituição sem mudanças de código;  
* [NECESSITA VALIDAÇÃO] Desenvolvimento de um software independente do hardware, permitindo a utilização de diferentes microcontroladores (ESP32, ESP8266, Raspberry Pi Pico W) com minima modificação.  
* [EM PROGRESSO] Implementação de classes para sensores reais;
* [EM PROGRESSO] Implementação de classes para hardwares reais;
* [CONCLUIDO] Abstração da relação sensor-armazenamento utilizando classes abstratas;  
 

# **Compilação**

A compilação do cogido deve ser feita no compilador adequado para cada hardware. Alguns hardwares específicios já estão configurados no arquivo `makefile` para facil compilação. Abaixo está a descrição da compilação de cada hardware.

**Atenção**: em caso de erro, verifique o arquivo `config.h` e certifique-se que os defines TARGET_... se encontram comentados.


## Linux
Para compilar para Linux, basta utilizar o comando:
```bash
make
```

## ATMEGA328P


## ESP32





### **Componentes Utilizados :**

* **Microcontrolador**:  
  * *Raspberry Pi Pico*: Atua como unidade de controle para a coleta de dados.  
  * *STM32F411*: Alternativa ao Pico para um sistema mais genérico.  
  * *ESP32-S*: Gerencia a coleta de dados e envia as informações diretamente para a rede.  
  * *ESP8266*: Usado como módulo de conectividade sem fio, comunicando-se com os microcontroladores para envio de dados.  
* **Display LCD**:  
  * Um pequeno display LCD (por exemplo, 16x2 ou 20x4) exibe os dados coletados do sensor, incluindo o valor medido e a identificação do sensor ativo.  
* **Sensores**:  
  * Diversos sensores (temperatura, umidade, movimentação, etc.), cada um com uma identificação única para facilitar a rastreabilidade.

# **Objetivos**

* Desenvolvimento de uma classe Sensor que abstraia os detalhes de cada sensor, permitindo que o software seja desenvolvido utilizando uma interface em comum para obtenção de dados;  
* Desenvolvimento de uma classe DataOutput que abstraia os dispositivos de armazenamento e servidores externos, permitindo sua substituição sem mudanças de código;  
* Desenvolvimento de um software independente do hardware, permitindo a utilização de diferentes microcontroladores (ESP32, ESP8266, Raspberry Pi Pico W) com minima modificação.  
* Definição de sensores utilizando herança, polimorfismo e sobrecarga;  
* Abstração da relação sensor-armazenamento utilizando classes abstratas;  
    
    
  


# **Descrição Funcional**

O funcionamento de sistemas de sensores como o **MPU9250**, **DS18B20**, **MPU6050** e **DHT11** baseia-se na interação entre o hardware do sensor, suas interfaces de comunicação e o microcontrolador responsável pelo processamento e envio dos dados. Cada sensor possui características únicas que permitem capturar informações específicas do ambiente ou do movimento, fornecendo dados para aplicações diversas.

### **Sensor MPU9250**

O **MPU9250** é um módulo combinado que integra um acelerômetro, giroscópio e magnetômetro em um único dispositivo. Ele opera medindo forças de aceleração, taxas angulares e campos magnéticos em três eixos, gerando dados úteis para aplicações de movimento e orientação.  
Internamente, o sensor possui circuitos MEMS (Micro-Electro-Mechanical Systems), que detectam variações de força e movimento. O MPU9250 se comunica com o microcontrolador por meio de interfaces I²C ou SPI, transmitindo os dados coletados em forma digital. Esses dados são então processados para determinar informações como inclinação, direção e velocidade angular.

### **Sensor DS18B20**

O **DS18B20** é um sensor de temperatura digital de alta precisão, ideal para medir temperaturas em um intervalo de \-55°C a \+125°C. Ele utiliza o protocolo **1-Wire**, que permite a comunicação com o microcontrolador por meio de um único pino de dados.  
Internamente, o sensor converte a temperatura ambiente em valores digitais utilizando um circuito integrado. O sensor armazena os dados em sua memória interna, permitindo que o microcontrolador faça a leitura quando necessário. Graças à sua simplicidade e precisão, o DS18B20 é amplamente utilizado em aplicações de monitoramento térmico.

### **Sensor MPU6050**

O **MPU6050** é um módulo que combina um acelerômetro e um giroscópio em um único chip. Ele mede aceleração e taxas angulares nos três eixos, sendo amplamente usado em aplicações de navegação, robótica e estabilização de sistemas.  
O sensor opera utilizando circuitos MEMS para detectar variações de movimento e envia os dados para o microcontrolador por meio de interfaces I²C. Ele também possui um Digital Motion Processor (DMP), que pode processar cálculos complexos diretamente no sensor, reduzindo a carga no microcontrolador.

### **Sensor de Umidade DHT11**

O **DHT11** é um sensor digital que mede temperatura e umidade relativa do ambiente. Ele utiliza um componente capacitivo para detectar mudanças na umidade e um termistor para medir a temperatura.  
O sensor converte as informações coletadas em sinais digitais e os transmite ao microcontrolador por meio de uma interface de comunicação proprietária. Embora tenha precisão limitada, o DHT11 é popular devido à sua simplicidade e baixo custo.

### **Sensor (Light Dependent Resistor)**

O **LDR** (Light Dependent Resistor), também conhecido como fotocélula, é um sensor de luz cuja resistência varia de acordo com a intensidade luminosa incidente. Esse comportamento é baseado nas propriedades de materiais semicondutores sensíveis à luz, como o sulfeto de cádmio (CdS), usados em sua construção.

Para seu funcionamento é necessário o microcontrolador realizar a conversão analógica-digital (ADC) da tensão fornecida pelo divisor. A variação do valor digital é proporcional à intensidade luminosa incidente no sensor.

---

### **Processo de Comunicação e Controle**

1. **Leitura dos Dados**:  
   Cada sensor é ligado e realiza a coleta de dados de forma contínua ou sob demanda, dependendo da configuração do sistema.  
2. **Transmissão de Dados**:  
   Os sensores utilizam interfaces específicas para enviar os dados ao microcontrolador:  
   * **MPU9250 e MPU6050**: I²C ou SPI.  
   * **DS18B20**: Protocolo 1-Wire.  
   * **DHT11**: Protocolo digital proprietário.  
3. **Processamento e Exibição**:  
   O microcontrolador interpreta os dados recebidos e os exibe em um display ou os transmite para outro sistema,  como o servidor influxdb, por meio de uma rede Wi-Fi ou armazena os dados em um cartão SD, para posteriormente transmitir via rede.  
4. **Aplicações dos Dados**:  
   As informações coletadas pelos sensores podem ser utilizadas em diversas aplicações, como:  
   * O **MPU9250** e o **MPU6050** são usados para estabilização de drones, sistemas de navegação ou detecção de movimentos.  
   * O **DS18B20** é empregado em sistemas de monitoramento de temperatura em casas inteligentes ou controle de processos industriais.  
   * O **DHT11** é amplamente utilizado em estações meteorológicas e sistemas de automação residencial.  
   * O **LDR** é normalmente utilizado na **Automação Residencial**: Controle de iluminação automática em função da luz ambiente e **Dispositivos Eletrônicos**: Ajuste automático de brilho em telas de smartphones ou outros displays.  
   


## **Diagrama de classes**

![Diagrama UML](https://github.com/alom101/cpp_eel_ufsc_Projeto/blob/main/docs/UML.png)

### **classe Sensor**

```cpp
// Proposta de uso
sensor = Sensor(); // alguma implementação concreta da classe
Measurement data = sensor.read();
```

### **classe DataOutput**

Esta classe será utilizada como interface de saida de dados, independentemente se estes dados irão para a memória local, um cartão SD ou um servidor.

```cpp
// Proposta de uso
dout = DataOutput(); // alguma implementação concreta da classe

Measurement data = sensor.read();
dout.save(data);
```

### **classe Measurement**

Esta classe irá encapsular as medidas. Ela agregará a medida, o timestamp e metadados, quando disponíveis.

```cpp
// Proposta de uso
Measurement data = sensor.read();

float valor = data.value();
time_t timestamp = data.timestamp();

// alguns metadados  
char sensor_type[20] = data.sensor_type(); // ex: DS18B20
chat sensor_name[20] = data.sensor_name(); // ex: Sensor de temperatura da sala
```

### **classe HAL**

Esta classe serve de interface para o hardware. Todas as interações com o hardware passarão por ela. Dessa forma, para portarmos o código para um microcontrolador diferente, basta herdar e implementar a classe HAL correta.

```cpp
// Proposta de uso

HAL hal = HAL();// alguma implementação concreta da classe

float value = hal.analog_read(5); // retorna a leitura analógica do pino 5

hal.i2c_write(0xAA);
int data = hal.i2c_read()
```

# **Plano de testes**

O plano de testes para o sistema de leitura de sensores e envio de dados para um servidor consistirá em duas etapas principais. A primeira etapa utilizará a classe FakeSensor para gerar medidas em uma sequência predefinida, permitindo o teste da saída de dados. Nesta etapa, será implementada a classe FakeOutput para imprimir os dados no terminal, simulando o comportamento da classe DataOutput. Esses testes permitirão verificar se os dados estão sendo coletados e processados corretamente pelo sistema.

A segunda etapa consistirá em testes em bancada, utilizando um servidor hospedado em um computador e um microcontrolador ESP32 para enviar leituras de um sensor para o sistema. Os principais pontos a serem testados incluem a armazenamento em LOG em caso de falha na comunicação com o servidor e o posterior envio de dados quando a conexão for restabelecida. Além disso, serão testados diferentes sensores para verificar a calibração e a taxa máxima de envio de dados sem perder a conexão ou quando o LOG estiver cheio. Esses testes garantirão a robustez e a eficiência do sistema em diferentes cenários.  


