# Дополнительные библиотеки не для Mac, по умолчанию оставляем пустым, чтобы не портить сборку на Mac
LIBS_ADDITIONAL =

# Определяем ОС
ifeq ($(OS), Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif
# Настраиваем переменные в зависимости от ОС
ifeq ($(detected_OS), Linux)
	detected_Linux := $(shell cat /etc/issue | sed -n '1p' | awk '{print $$1}')
	ifeq ($(detected_Linux), Arch)
	LIBS_ADDITIONAL = -lm
	CMD_OPEN = xdg-open
	endif

	ifeq ($(detected_Linux), Ubuntu)
	LIBS_ADDITIONAL = -lm -pthread -lsubunit -lrt
	CMD_OPEN = xdg-open
	endif

	ifeq ($(detected_Linux), Debian)
	LIBS_ADDITIONAL = -lm -pthread -lsubunit -lrt
	CMD_OPEN = xdg-open
	endif
endif

# Набор цветов для красивостей
GREEN = \033[0;32m
RESET = \033[0m

# Компилятор / Линковщик
CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17

# Пути до используемых папок
TEST_MAIN=test_main.cc
TEST_SRCS=tests/*.cc
GCOV_OBJ_DIR = obj/gcov
TESTS_OBJ_DIR = obj/tests
REPORT_DIR = report
MODULES_STATIC_LIBRARY_GCOV = s21_containers_gcov.a

TESTS = test

# Пути к каталогам
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
COVERAGE_DIR = $(BUILD_DIR)/coverage

all: clean test

$(TESTS): clean
	@echo "Start compile..."
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(TEST_SRCS) $(TEST_MAIN) -lgtest --coverage -o $(BUILD_DIR)/test
	@echo "$(GREEN)************************************************************************************************$(RESET)\c"
	@echo "\n-------------------------------------------------------------------------------------------------\n"
	@mv $(BUILD_DIR)/test $(BIN_DIR)/
	@echo "Compile finish."
	@$(BIN_DIR)/test

gcov_report:
	@echo "Начало генерации отчета тестового покрытия..."
	@gcovr -r ./ --object-directory ./build --html --html-details -o build/coverage_report.html
	@echo "Генерация отчета тестового покрытия выполнена(build/coverage_report.html)."
	firefox --new-window build/coverage_report.html

clean:
	@rm -rf bin build
	@rm -rf *.gcno
	@rm -rf *.gcda

style:
	cp ../materials/linters/.clang-format ./
	find ./ -iname "*.h" -o -iname "*.cc" | xargs clang-format -n
	@echo "$(GREEN)style check complete"

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --leak-check=full ./build/bin/test

rebuild: clean all

.PHONY: all clean rebuild style
