clean:
	rm -f statisticsConnector
	rm -f Queue
install-libs:
	@echo "installing library dependencies"
	@sudo apt satisfy -y -q 'libzmq3-dev, libboost-dev, gnuplot'

statisticsConnector: 
	g++ -g statisticsConnector.cpp -lzmq -o statisticsConnector
Queue:
	g++ -g Queue.cpp -lzmq -o Queue
monitorConnector:
	g++ -g monitorConnector.cpp -lzmq -o monitorConnector

run: statisticsConnector Queue monitorConnector
	./Queue &
	./statisticsConnector &
	./monitorConnector

killall:
	@echo "Killing Queue, statisticsConnector, and monitorConnector processes..."
	@lsof -i | grep -E 'Queue|statisticsConnector|monitorConnector' | awk '{print $$2}' | xargs -r kill -9



