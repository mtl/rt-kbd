
.PHONY: clean pristine

clean:
	find . -type f -name "*~" -exec rm {} \;
	find . -type f -name ".*.sw?" -exec rm {} \;

pristine: clean
	find . -type f -name "*.o" -exec rm {} \;
	find . -type f -name "*.lst" -exec rm {} \;

