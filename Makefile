all:
	@cd ./client ; cmake . ; cd ..
	@make -C ./network
	@make -C ./client -j20
	@make -C ./server
	@mv ./client/Bomberman .
	@cp -r ./client/assets .
	@cp -r ./client/themes .
	@cp -r ./client/maps .
	@cp ./client/bomberman.properties .

bomber:
	@make -C ./client -j99
	@mv ./client/Bomberman ./

clean:
	@make -C ./client clean
	@make -C ./server fclean
	@make -C ./network fclean

re: all

fclean: clean
	rm -rf ./assets
	rm -rf ./themes
	rm -rf ./maps
	rm -rf ./bomberman.properties
	rm -rf ./Bomberman
