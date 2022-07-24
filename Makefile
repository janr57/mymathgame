source:
	$(MAKE) -C src all

.PHONY: clean cleancsv

cleancsv:
	rm -f *.csv

clean:
	rm -f *.csv mathgame*
	$(MAKE) -C src clean


