idf_component_register(SRCS "dht11_driver.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_driver_gpio esp_timer)
