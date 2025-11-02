
install-libs:
	@echo "installing library dependencies"
	@sudo apt satisfy -y -q 'libzmq3-dev, libboost-dev, gnuplot'

