
run:
	make -C console run

acme:
	make -C ACME all

clean:
	make -C console clean

.PHONY: run clean
