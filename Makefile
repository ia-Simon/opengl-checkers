.PHONY: help
$(VERBOSE).SILENT:



# Self-Documented Makefile
# https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
help:
	@grep -E '^(\w|-)+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
.DEFAULT_GOAL := help

run-linux:
	tar -xzvf irrKlang.tar.gz irrKlang
	g++ src/main.cpp --std=c++17 -lGL -lGLU -lglut -I./irrKlang/include -L./irrKlang/bin/linux-gcc-64 -lIrrKlang -pthread -o checkers
	LD_LIBRARY_PATH=$$(pwd)/irrKlang/bin/linux-gcc-64 ./checkers
	rm checkers
	rm -rf irrKlang

run-macosx:
	tar -xzvf irrKlang.tar.gz irrKlang
	g++ src/main.cpp --std=c++17 -framework OpenGL -framework GLUT -I./irrKlang/include -L./irrKlang/bin/macosx-gcc -lirrklang -pthread -o checkers
	DYLD_LIBRARY_PATH=$$(pwd)/irrKlang/bin/macosx-gcc ./checkers
	rm checkers
	rm -rf irrKlang