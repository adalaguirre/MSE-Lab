# This is a makefile for our source files

SRC_DIR = Files_c
INCLUDE_DIR = Files_h 

#List of my source files here
SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/stm32_startup.c \
	$(SRC_DIR)/led.c \
	$(SRC_DIR)/timer.c \
	$(SRC_DIR)/pwm.c \
	$(SRC_DIR)/SRS_GPIO_DRIVER.c \
	$(SRC_DIR)/SRS_TIM_DRIVER.c \
	$(SRC_DIR)/system_stm32f4xx.c

# List all your include directories here
INCLUDES = \
	-I$(INCLUDE_DIR) \
	-I./CMSIS/STM32F4xx/Include \
	-I./CMSIS/Core/Include \
	-I./STM_files
