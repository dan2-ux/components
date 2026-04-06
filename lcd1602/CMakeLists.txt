idf_component_register(SRCS "exmaple.cpp" "lcd1602.cpp" "lcd1602.c"
                       INCLUDE_DIRS "."
                       REQUIRES esp_timer esp_driver_gpio 
                       )
