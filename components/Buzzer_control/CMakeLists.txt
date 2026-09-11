idf_component_register(SRCS "buzzer_driver.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_driver_ledc esp_driver_gpio)
