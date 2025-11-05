clean:
	rm -f statisticsConnector
	rm -f Queue
install-libs:
	@echo "installing library dependencies"
	@sudo apt satisfy -y -q 'libzmq3-dev, libboost-dev, gnuplot'

statisticsConnector: 
	@g++ -g statisticsConnector.cpp -lzmq -o statisticsConnector
Queue:
	@g++ -g Queue.cpp -lzmq -o Queue

run: statisticsConnector Queue
	./Queue &
	./statisticsConnector

killall:
	@echo "Killing Queue and statisticsConnector processes..."
	@lsof -i | grep -E 'Queue|statisticsConnector' | awk '{print $$2}' | xargs -r kill -9



