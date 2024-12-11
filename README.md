# **Interface de abstração para sensores**

Projeto realizado para a disciplina de `C++ para embarcados` do curso de `Engenharia Eletrônica` da `Universidade Federal de Santa Catarina` no semestre 2024.2

Feito por:

Arthur Leones Osorio Machado \- 19103415

Pedro Felipe Bender \- 20150153


# **Introdução**
## **Contextualização**
A programação embarcada é uma área da engenharia de software que se concentra no desenvolvimento de sistemas computacionais integrados a dispositivos físicos, como robôs, veículos autônomos, sistemas de automação industrial e dispositivos de consumo. Nesse contexto, o software é projetado para interagir diretamente com o hardware do dispositivo, controlando e monitorando suas funcionalidades.

No entanto, um dos principais desafios na programação embarcada é o problema de acoplamento entre software e hardware. O acoplamento refere-se à dependência excessiva entre os componentes de software e hardware, tornando difícil modificar ou substituir um componente sem afetar o outro.

## **Descrição do Projeto**
Com o objetivo de minimizar o acoplamento entre software e hardware na programação embarcada, este projeto visa criar uma interface genérica em C++ para a leitura de dados de sensores e envio dessas informações para um dispositivo de armazenamento. A solução será desenvolvida com base nos princípios da Programação Orientada a Objetos (POO), garantindo flexibilidade e modularidade do código. Isso permitirá que o sistema seja mais fácil de manter e escalável, reduzindo o acoplamento entre os componentes de software e hardware.

A arquitetura modular proposta permitirá a integração de diferentes tipos de sensores e métodos de armazenamento sem alterações significativas na base do código, tornando-a ideal para cenários onde é essencial integrar sensores e armazenar dados, como em sistemas IoT, automação industrial ou monitoramento ambiental. A utilização da POO facilitará a adição de novos tipos de sensores e formas de armazenar informações sem complicar o sistema, economizando tempo e esforço na manutenção e permitindo o reuso de partes do código em outros projetos. Além disso, a arquitetura proposta permitirá utilizar mais facilmente sensores disponíveis no mercado de forma simples e rápida, reduzindo o esforço necessário para integrar novos dispositivos e melhorando a portabilidade do sistema. Com isso, o projeto contribuirá para a criação de sistemas mais flexíveis, escaláveis e fáceis de manter, minimizando o problema de acoplamento entre software e hardware na programação embarcada.

![ideia_geral](https://github.com/alom101/cpp_eel_ufsc_Projeto/blob/main/docs/ideia_geral.png)

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
O código é feito para ser utilizando como biblioteca, para tal, basta incluir o header `sensorUFSC.h` e utilizar as classes lá definidas. Para testar o código, temos o arquivo `main_test.cpp` que será utilizado para demonstração e para os exemplos de compilação a seguir.

A compilação do código deve ser feita no compilador adequado para cada hardware. Alguns hardwares específicios já estão configurados no arquivo `makefile` para facil compilação. Abaixo está a descrição da compilação de cada hardware.

**Atenção**: em caso de erro, verifique o arquivo `config.h` e certifique-se que os defines TARGET_{...} se encontram comentados.


## Linux
Requisitos: `gcc`

Para compilar para Linux, basta utilizar o comando:
```bash
make
```

Saída: `linux.out`

## ATMEGA328P
Requisitos: `avr-gcc`

Para compilar para o microcontrolador ATMEGA328P, utilize o comando:

```bash
make atmega
```

Saída: `atmega.out` 

## ESP32
Requisitos: `Expressif-IDE`




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


