# This is a makefile for our source files

SRC_DIR = Files_c
INCLUDE_DIR = Files_h 

#List of my source files here
SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/stm32_startup.c
# List all your include directories here
INCLUDES = \
	-I$(INCLUDE_DIR)