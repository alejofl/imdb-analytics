COMPILER=gcc
DEBUG_COMPILER=-g -DDEBUG=1
QUERY_FILES=./queries/*.c
BACKEND_FILES=utils.c
FRONTEND_FILES=main.c front.c
OUTPUT_FILE=main
OUTPUT_FILE_DEBUG=test
CSV_OUTPUT=query4.csv query1.csv query2.csv query3.csv

all: BACKEND_FILES+=$(QUERY_FILES)
all: clean
all: compile

compile:
	$(COMPILER) -o $(OUTPUT_FILE) $(FRONTEND_FILES) $(BACKEND_FILES)

clean:
	rm -r $(OUTPUT_FILE) *.o $(CSV_OUTPUT)

debug: 	COMPILER+=$(DEBUG_COMPILER)
		OUTPUT_FILE=$(OUTPUT_FILE_DEBUG)
debug: 	all

debugQ1: COMPILER+=$(DEBUG_COMPILER)
		BACKEND_FILES+=./queries/query1ADT.c
		OUTPUT_FILE=$(OUTPUT_FILE_DEBUG)
debugQ1: compile

debugQ2: COMPILER+=$(DEBUG_COMPILER)
		BACKEND_FILES+=./queries/query2ADT.c
		OUTPUT_FILE=$(OUTPUT_FILE_DEBUG)
debugQ2: compile

debugQ3: COMPILER+=$(DEBUG_COMPILER)
		BACKEND_FILES+=./queries/query3ADT.c
		OUTPUT_FILE=$(OUTPUT_FILE_DEBUG)
debugQ3: compile

debugQ4: COMPILER+=$(DEBUG_COMPILER)
		BACKEND_FILES+=./queries/query4ADT.c
		OUTPUT_FILE=$(OUTPUT_FILE_DEBUG)
debugQ4: compile

clean-debug:
	rm -r $(OUTPUT_FILE_DEBUG) *.o
