install:
    # Atualizar pacotes e instalar SQLite
	sudo apt update && sudo apt upgrade -y
	sudo apt install sqlite3 -y
	sudo apt install libsqlite3-dev -y

compile:
    # Compilar os arquivos do projeto
	g++ main.cpp views/RoupaView.cpp views/ItemDiversoView.cpp views/ClienteView.cpp views/VendaView.cpp \
	models/Roupa.cpp models/Produto.cpp models/ItemDiverso.cpp models/Cliente.cpp models/Venda.cpp \
	dao/RoupaDAO.cpp dao/ItemDiversoDAO.cpp dao/ClienteDAO.cpp dao/VendaDAO.cpp \
	controllers/RoupaController.cpp controllers/ItemDiversoController.cpp controllers/ClienteController.cpp \
	controllers/VendaController.cpp -lsqlite3 -o a.out

run:
    # Executar o programa compilado
	./a.out

clean:
    # Remover o executável
	rm -f a.out

all:
    # Executar todas as etapas
	make install
	make compile
	make run
	make clean