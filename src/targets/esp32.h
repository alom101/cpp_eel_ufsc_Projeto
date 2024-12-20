#ifndef ESP32_H
#define ESP32_H

extern "C" {

#include <stdio.h>
#include "driver/i2c.h"
#include "esp_log.h"


#define I2C_MASTER_SCL_IO 19         // Pino SCL (alterado para 22)
#define I2C_MASTER_SDA_IO 18         // Pino SDA (alterado para 21)
#define I2C_MASTER_NUM I2C_NUM_0     // Porta I2C
#define I2C_MASTER_FREQ_HZ 100000    // Frequência I2C (100kHz)
#define MPU9250_ADDR 0x68            // Endereço padrão do MPU9250
#define MPU9250_WHO_AM_I 0x75        // Registro WHO_AM_I
#define MPU9250_PWR_MGMT_1 0x6B     // Registro de gerenciamento de energia
#define MPU9250_ACCEL_XOUT_H 0x3B   // Registro de dados do acelerômetro (X alto)

static const char *TAG = "MPU9250";

// Função para inicializar o I2C
static esp_err_t i2c_master_init(void) {
    i2c_config_t conf = {
    .mode = I2C_MODE_MASTER,              // Configurando o modo para mestre
    .sda_io_num = I2C_MASTER_SDA_IO,     // GPIO para SDA
    .scl_io_num = I2C_MASTER_SCL_IO,     // GPIO para SCL
    .sda_pullup_en = GPIO_PULLUP_ENABLE, // Habilitar pull-up interno para SDA
    .scl_pullup_en = GPIO_PULLUP_ENABLE, // Habilitar pull-up interno para SCL
    .master = {
        .clk_speed = I2C_MASTER_FREQ_HZ  // Configurando a frequência de clock do mestre
    },
    .clk_flags = 0                       // Configurando flags do clock como 0
	};

    ESP_LOGI(TAG, "Configurando I2C: SDA=%d, SCL=%d, Freq=%d Hz", 
        I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO, I2C_MASTER_FREQ_HZ);

    esp_err_t err = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Erro ao configurar I2C: %d", err);
        return err;
    }

    err = i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Erro ao instalar driver I2C: %d", err);
        return err;
    }

    return ESP_OK;
}


// Função para escrever no MPU9250
static esp_err_t mpu9250_write_byte(uint8_t reg_addr, uint8_t data) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MPU9250_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_write_byte(cmd, data, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

// Função para ler do MPU9250
static esp_err_t mpu9250_read_byte(uint8_t reg_addr, uint8_t *data) {
    esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    if (cmd == NULL) {
        ESP_LOGE(TAG, "Falha ao criar comando I2C");
        return ESP_FAIL;
    }

    // Enviar endereço do registro para leitura
    i2c_master_start(cmd);
    ret = i2c_master_write_byte(cmd, (MPU9250_ADDR << 1) | I2C_MASTER_WRITE, true);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Falha ao enviar endereço do dispositivo (WRITE). Erro: 0x%X", ret);
        i2c_cmd_link_delete(cmd);
        return ret;
    }

    ret = i2c_master_write_byte(cmd, reg_addr, true);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Falha ao enviar endereço do registro. Erro: 0x%X", ret);
        i2c_cmd_link_delete(cmd);
        return ret;
    }

    // Repetir start e iniciar leitura
    i2c_master_start(cmd);
    ret = i2c_master_write_byte(cmd, (MPU9250_ADDR << 1) | I2C_MASTER_READ, true);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Falha ao enviar endereço do dispositivo (READ). Erro: 0x%X", ret);
        i2c_cmd_link_delete(cmd);
        return ret;
    }

    // Ler o dado
    ret = i2c_master_read_byte(cmd, data, I2C_MASTER_NACK);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Falha ao ler dado do dispositivo. Erro: 0x%X", ret);
    }

    i2c_master_stop(cmd);
    esp_err_t cmd_ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 100 / portTICK_PERIOD_MS);
    if (cmd_ret != ESP_OK) {
        ESP_LOGE(TAG, "Falha ao enviar comando I2C. Erro: 0x%X", cmd_ret);
    }

    i2c_cmd_link_delete(cmd);
    return cmd_ret; // Retorna o resultado final da comunicação
}

// Função para inicializar o MPU9250
static esp_err_t mpu9250_init(void) {
    uint8_t who_am_i = 0;
    ESP_ERROR_CHECK(mpu9250_read_byte(MPU9250_WHO_AM_I, &who_am_i));
    if (who_am_i != 0x71) {
        ESP_LOGE(TAG, "MPU9250 não detectado! WHO_AM_I = 0x%02X", who_am_i);
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "MPU9250 detectado! WHO_AM_I = 0x%02X", who_am_i);

    // Sair do modo de suspensão
    return mpu9250_write_byte(MPU9250_PWR_MGMT_1, 0x00);
}

void configura(void){
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C inicializado com sucesso!");

    if (mpu9250_init() == ESP_OK) {
        ESP_LOGI(TAG, "MPU9250 inicializado com sucesso!");
    } else {
        ESP_LOGE(TAG, "Falha ao inicializar o MPU9250.");
        return;
    }
}

// Função principal
void loop_mpu(void) {
    uint8_t accel_x_h, accel_x_l;  // Declaração das variáveis

    // Ler valores do acelerômetro
    mpu9250_read_byte(MPU9250_ACCEL_XOUT_H, &accel_x_h);
    mpu9250_read_byte(MPU9250_ACCEL_XOUT_H + 1, &accel_x_l);

    // Combinar os dois bytes em um valor de 16 bits
    int16_t accel_x = (int16_t)((accel_x_h << 8) | accel_x_l);
    ESP_LOGI(TAG, "Acelerômetro X: %d", accel_x);

    //vTaskDelay(10 / portTICK_PERIOD_MS); // Delay de 500ms
}



} // extern "C"
#endif // !ESP32_H
