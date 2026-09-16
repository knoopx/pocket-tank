# Waveshare 4B (ESP32-P4, P4-only): the BSP owns the MIPI-DSI display, the
# GT911 touch and the I2C bus; the board has no IMU or external RTC (the
# progression wall clock is the chip clock in tankcore's persist_port_esp.c).
set(SRCS main.c director.c brightness.c codec_port.c advisor_llm_esp.c
         display_port_st7703.c touch_port_gt911.c audio_port_es8311.c)
idf_component_register(
    SRCS ${SRCS}
    INCLUDE_DIRS "."
    REQUIRES tankcore llm esp32_p4_wifi6_touch_lcd_4b esp_partition nvs_flash
             esp_timer esp_driver_i2s esp_driver_gpio esp_driver_i2c
             esp_driver_usb_serial_jtag esp_lcd esp_app_format
    EMBED_FILES "tokenizer.bin" "../../assets/sounds/sounds.bin"
)
