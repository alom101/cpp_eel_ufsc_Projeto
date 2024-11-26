# Projeto de C++ para Embarcados: Leitura de Sensores e Envio de Dados para Servidor

Alunos:

Arthur Leones Osorio Machado - 19103415

Pedro Felipe Bender - 20150153

## Introdução

Este projeto visa desenvolver uma interface genérica em C++ que leia dados de sensores e os envie para um servidor ou dispositivo de armazenamento utilizando técnicas de programação orientada a objetos (POO) e abordando os seguintes tópicos:

*   Definição de sensores utilizando herança, polimorfismo e sobrecarga;
*   Abstração da relação sensor-armazenamento utilizando classes abstratas;

## Objetivos

*   Desenvolvimento de uma classe Sensor que abstraia os detalhes de cada sensor, permitindo que o software seja desenvolvido utilizando uma interface em comum para obtenção de dados;
*   Desenvolvimento de uma classe DataOutput que abstraia os dispositivos de armazenamento e servidores externos, permitindo sua substituição sem mudanças de código;
*   Desenvolvimento de um software independente do hardware, permitindo a utilização de diferentes microcontroladores (ESP32, ESP8266, Raspberry Pi Pico W) com minima modificação.

## Requisitos

*   Microcontrolador;
*   Sensores;
*   Dispositivo para receber os dados



## Implementação

O software será dividido em três partes principais:

### SensorUFSC.h
---
Neste arquivo está todas as definições de interface necessárias para o uso do projeto. Ele foi pensado para ser o único #include necessário. Neste arquivo estarão as definições de:


#### classe Sensor
```cpp
// Proposta de uso
sensor = Sensor(); // alguma implementação concreta da classe
Measurement data = sensor.read();
```

#### classe DataOutput
Esta classe será utilizada como interface de saida de dados, independentemente se estes dados irão para a memória local, um cartão SD ou um servidor.

```cpp
// Proposta de uso
dout = DataOutput(); // alguma implementação concreta da classe

Measurement data = sensor.read();
dout.save(data);
```

#### classe Measurement
Esta classe irá encapsular as medidas. Ela agrupará a medida, o timestamp e metadados, quando disponíveis.

```cpp
// Proposta de uso
Measurement data = sensor.read();

float valor = data.value();
time_t timestamp = data.timestamp();

// alguns metadados
char sensor_type[20] = data.sensor_type(); // ex: DS18B20
chat sensor_name[20] = data.sensor_name(); // ex: Temperatura da sala
```




## Plano de testes

Para testes, implementaremos duas classes de testes: 
*   FakeSensor: Cria medidas em uma sequencia predefinida. Será utilizada para testar saidas de dados;
*   FakeOutput: Printa dados no terminal;


