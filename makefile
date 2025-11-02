clean:
	rm -f statisticsConnector
install-libs:
	@echo "installing library dependencies"
	@sudo apt satisfy -y -q 'libzmq3-dev, libboost-dev, gnuplot'

statisticsConnector: 
	@g++ -g statisticsConnector.cpp -o statisticsConnector

run: statisticsConnector
	./statisticsConnector

