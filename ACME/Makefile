CC := g++
INCLUDE = -I.

CSRCS := *.cpp
TRGT := Acme
CHDRS :=mainHeader.h resource.h stdafx.h

all: run

$(TRGT): $(CSRCS) $(CHDRS)
	$(CC) $(CFLAGS) $(CSRCS) -o $@

run: $(TRGT)
	./$(TRGT)
	cp injectionRange.txt ../console/injectionRange.txt

clean:
	@rm -f *# *~ $(TRGT)
	@rm -f injectionRange.txt synth_system.ebd

.PHONY: all run clean
