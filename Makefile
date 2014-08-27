.PHONY:clean

default_target: fuckyou

install: fuckyou
	install fuckyou /usr/local/bin
	rm -f *.o
	rm -f fuckyou

fuckyou: fuckyou.o
	g++ $(CFLAGS) -o $@ $+

%.o: %.cpp
	g++ $(CFLAGS) -c $+

clean:
	rm -f *.o
	rm -f fuckyou
