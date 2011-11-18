objects	=	html_parser.o	get_encoding.o
	
get_encoding	:	$(objects)
		cc -o get_encoding	$(objects) -lcurl -g

html_parser.o	:	html_parser.h html_parser.c
		cc -c -g html_parser.c
get_encoding.o	:	html_parser.h get_encoding.c utils.h
		cc -c -g get_encoding.c

.PHONY	:
	clean

clean	:
	rm get_encoding	$(objects)

