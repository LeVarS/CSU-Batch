compile:
			gcc process.c -o process
			gcc batch.c commandline_parser.c queue.c scheduling.c dispatching.c -o main
			clear
			./main

debug:
			gcc commandline_parser.c queue.c scheduling.c -g -o main
			lldb main
			
run: 
			./main