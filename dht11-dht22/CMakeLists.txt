idf_component_register(SRCS "example-dht11.cpp" "example-dht22.cpp" "dht.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES esp_driver_gpio esp_timer
                       )
