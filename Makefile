all:
	cmake ./client
	make -C ./client -j20
	make -C ./server
	make -C ./network

bomber:
	make -C ./client -j99
	mv ./client/Bomberman ./

clean:
	make -C ./client clean
	make -C ./server fclean
	make -C ./network fclean
