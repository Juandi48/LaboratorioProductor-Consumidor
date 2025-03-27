# Nombre del compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -g

# Archivos fuente
PRODUCER_SRC = Productores.c reverse_string.c
CONSUMER_SRC = Consumidor.c

# Ejecutables
PRODUCER_BIN = productor
CONSUMER_BIN = consumidor

all: $(PRODUCER_BIN) $(CONSUMER_BIN)

# Compilar el productor (servidor)
$(PRODUCER_BIN): $(PRODUCER_SRC)
	$(CC) $(CFLAGS) -o $(PRODUCER_BIN) $(PRODUCER_SRC)

# Compilar el consumidor (cliente)
$(CONSUMER_BIN): $(CONSUMER_SRC)
	$(CC) $(CFLAGS) -o $(CONSUMER_BIN) $(CONSUMER_SRC)

# Limpiar archivos compilados
clean:
	rm -f $(PRODUCER_BIN) $(CONSUMER_BIN)
