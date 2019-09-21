compile:
			gcc commandline_parser.c queue.c scheduling.c -o main
			clear
			./main

debug:
			gcc commandline_parser.c queue.c scheduling.c -g -o main
			lldb main
			
run: 
			./main