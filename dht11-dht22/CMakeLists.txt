idf_component_register(SRCS "example-dht22.cpp" "dht.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES driver esp_timer
                       )
