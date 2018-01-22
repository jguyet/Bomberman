# Bomberman
Bomberman, c'est un classique du jeu video : aussi simple dans son gameplay que fun à jouer ! Vous allez ici profiter de sa simplicité pour faire votre premier gros projet de C++ de facture professionnelle. Vous allez recoder une version de Bomberman, en C++ et avec OpenGL, avec pour objectif de réaliser un jeu le plus abouti possible.

##### use :
Compilation command `make all`  
Recompilation command `make compile`
Clean build folder `make fclean`

##### developement :
create cpp files on `srcs` directory and add file_path on set(HEADER_FILES) CMakelist.txt  
create hpp headers on `includes` directory and add file_path on set(CLIENT_SRC) CMakelist.tx  

````
set(HEADER_FILES
  ./includes/Header.hpp
	)
set(CLIENT_SRC
	./srcs/Main.cpp
	)
````  

##### glfw documentation :
[http://www.glfw.org/](http://www.glfw.org/)

##### glm documentation :
[https://glm.g-truc.net/0.9.8/index.html](https://glm.g-truc.net/0.9.8/index.html)
