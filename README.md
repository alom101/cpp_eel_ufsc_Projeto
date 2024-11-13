# Projeto de C++ para Embarcados: Leitura de Sensores e Envio de Dados para Servidor

Alunos:
Arthur Leones Osorio Machado - 19103415
Pedro Felipe Bender - 20150153

## Introdução

Este projeto visa desenvolver um software em C++ para um microcontrolador que leia dados de sensores e os envie para um servidor. Caso o servidor esteja fora de alcance, o software armazenará os dados localmente e os enviará posteriormente. O foco do projeto será no desenvolvimento do software, utilizando técnicas de programação orientada a objetos (POO) e abordando os seguintes tópicos:

*   Definição de sensores utilizando herança, polimorfismo e sobrecarga
*   Desenvolvimento de um software independente do hardware, permitindo a utilização de diferentes microcontroladores (ESP32 ou ESP8266)

## Objetivos

*   Desenvolver um software que leia dados de sensores e os envie para um dispositivo de saida de dados
*   Implementar a armazenagem local de dados caso o servidor esteja fora de alcance
*   Utilizar técnicas de POO para definir sensores
*   Desenvolver um software independente do hardware

## Requisitos

*   Microcontrolador ESP32 ou ESP8266
*   Sensores (a serem definidos)
*   Servidor para envio de dados

## Arquitetura do Software

O software será dividido em três módulos principais:

### Módulo de Sensores

*   Definição de uma classe base `Sensor` que contém métodos virtuais para leitura de dados
*   Criação de classes derivadas para cada tipo de sensor, utilizando herança e polimorfismo
*   Utilização de sobrecarga para permitir a leitura de dados de diferentes tipos

### Módulo de Comunicação

*   Implementação de uma classe `Comunicacao` que envia dados para o servidor
*   Utilização de bibliotecas de comunicação (WiFi, HTTP, etc.) para envio de dados
*   Implementação de um mecanismo de retry para caso o servidor esteja fora de alcance

### Módulo de Armazenamento

*   Implementação de uma classe `Armazenamento` que armazena dados localmente
*   Utilização de uma biblioteca de armazenamento (EEPROM, SPIFFS, etc.) para armazenar dados
*   Implementação de um mecanismo de gerenciamento de dados armazenados

## Implementação

A implementação será feita utilizando C++ e bibliotecas específicas para o microcontrolador escolhido (ESP32 ou ESP8266). O software será desenvolvido utilizando técnicas de POO e abordará os tópicos mencionados anteriormente.

## Resultados Esperados

*   Um software que leia dados de sensores e os envie para um servidor
*   Os dados sejam armazenados localmente caso o servidor esteja fora de alcance
*   Software permitindo a utilização de diferentes microcontroladores

