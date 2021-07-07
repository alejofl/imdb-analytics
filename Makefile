COMPILER=gcc -pedantic -std=c99 -Wall -fsanitize=address 
DEBUG_COMPILER=-g -DDEBUG=1
QUERY_FILES=./queries/*.c
BACKEND_FILES=utils.c
FRONTEND_FILES=main.c front.c
OUTPUT_FILE=imdb
OUTPUT_FILE_DEBUG=test
CSV_OUTPUT=query4.csv query1.csv query2.csv query3.csv
TESTS=./tests/*.c

all: clean
all: compile

clean: 
	rm -rf $(OUTPUT_FILE) *.o $(CSV_OUTPUT)

debug: 	COMPILER+=$(DEBUG_COMPILER)
debug:  OUTPUT_FILE=$(OUTPUT_FILE_DEBUG)
debug:	BACKEND_FILES+=$(TESTS)
debug: 	all

clean-all: clean
clean-all: clean-debug

compile:
	$(COMPILER) -o $(OUTPUT_FILE) $(FRONTEND_FILES) $(BACKEND_FILES) $(QUERY_FILES)

clean-debug:
	rm -rf $(OUTPUT_FILE_DEBUG) *.o $(CSV_OUTPUT)
