#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h" // ยังคงไว้เผื่อใช้ Log ในอนาคต

// --- กำหนด Pin ตามวงจร ---
#define LED_1_PIN    GPIO_NUM_17
#define SWITCH_1_PIN GPIO_NUM_15
#define LED_2_PIN    GPIO_NUM_18
#define SWITCH_2_PIN GPIO_NUM_16

// static const char *TAG = "SWITCH_APP"; // ปิด Log Tag ชั่วคราว

void app_main(void)
{
    // --- ตัวแปรเก็บสถานะ ---
    int SW1_Status = 0;
    int LED1_Status = 0;
    int SW2_Status = 0;
    int LED2_Status = 0;

    // --- ตั้งค่า Output Pins (LEDs) ---
    gpio_set_direction(LED_1_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_2_PIN, GPIO_MODE_OUTPUT);

    // --- ตั้งค่า Input Pins (Switches) ---
    gpio_set_direction(SWITCH_1_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(SWITCH_2_PIN, GPIO_MODE_INPUT);

    // --- เปิด Pull-up ภายในสำหรับ Switches ---
    gpio_set_pull_mode(SWITCH_1_PIN, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(SWITCH_2_PIN, GPIO_PULLUP_ONLY);

    // ESP_LOGI(TAG, "Setup complete. Entering main loop."); // ปิด Log ตอนเริ่ม

    while (1)
    {
        // --- อ่านค่าสถานะสวิตช์ ---
        SW1_Status = gpio_get_level(SWITCH_1_PIN);
        SW2_Status = gpio_get_level(SWITCH_2_PIN);

        // --- กลับค่า Logic (กด=ติด, ไม่กด=ดับ) ---
        LED1_Status = !SW1_Status;
        LED2_Status = !SW2_Status;

        // --- สั่งงาน LEDs ---
        gpio_set_level(LED_1_PIN, LED1_Status);
        gpio_set_level(LED_2_PIN, LED2_Status);

        // --- Delay สั้นๆ ---
        vTaskDelay(pdMS_TO_TICKS(50)); // Delay สำหรับ Debounce และลดภาระ CPU
    }
}
