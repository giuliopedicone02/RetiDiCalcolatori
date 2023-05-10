# Chat UDP in C - Istruzioni per l'uso

**Attenzione:** L'ordine delle due porte deve essere invertito!

* **Visualizzazione indirizzo IP del Client/Server:**
    ```c
    ip a
    ```
## Client

* **Compilazione:**
    ```c
    gcc chat.c -o chat
    ```

* **Esecuzione:**
    ```c
    ./chat indirizzoIPServer porta1 porta2
    ```

* **Esempio:**
    ```c
    gcc chat.c -o chat
    ./chat 192.168.56.103 2222 3333 
    ```

## Server

* **Compilazione:**
    ```c
    gcc chat.c -o chat
    ```

* **Esecuzione:**
    ```c
    ./chat indirizzoIPClient porta2 porta1
    ```

* **Esempio:**
    ```c
    gcc chat.c -o chat
    ./chat 192.168.56.102 3333 2222
    ```

# Socket in TCP 

## Il metodo listen()

```c
int listen(int socket, int backlog)
```

La chiamata **listen()** abilita il socket a ricevere connessioni,rendendolo quindi un server socket.

* **backlog:** Massimo numero di richieste da eseguire contemporaneamente, 5 nell'[esempio](https://github.com/giuliopedicone02/RetiDiCalcolatori/tree/main/Lezioni/2023-05-10/Socket%20TCP/receiver.c) 

## Il metodo accept()

```c
int accept(int socket, struct sockaddr *addr, socklen_t *addrlen)
```

La chiamata **accept()** è bloccante. Non appena arriva una richiesta di connessione, crea un nuovo socket e ne restituisce il descrittore.

Il vecchio socket rimane aperto e non connesso. L’indirizzo restituito è quello di chi ha effettuato la connect().

## Il metodo connect()

```c
int connect(int socket, struct sockaddr* addr, int addrlen)
```

La chiamata **connect()** inizializza una connessione con un socketremoto. L’indirizzo che viene passato è relativo ad un host remoto

## Il metodo send()

```c
int send(int socket, void *buffer, size_t size, int flags)
```

Serve per la scrittura nei socket. Analogo alla **sendto()** di UDP.

* **flags:** Parametro impostato a 0

## Il metodo recv()

```c
int recv(int socket, void *buffer, size_t size, int flags)
```

Serve per la lettura nei socket. Analogo alla **recvfrom()** di UDP.

* **flags:** Parametro impostato a 0

# Socket TCP - Istruzioni per l'uso

## Client

* **Compilazione:**
    ```c
    gcc sender.c -o sender
    ```

* **Esecuzione:**
    ```c
    ./sender indirizzoIPServer porta
    ```

* **Visualizzazione indirizzo IP:**
    ```c
    ip a
    ```

* **Esempio:**
    ```c
    gcc sender.c -o sender
    ./sender 192.168.56.103 5050
    ```

## Server

* **Compilazione:**
    ```c
    gcc receiver.c -o receiver
    ```

* **Esecuzione:**
    ```c
    ./receiver porta
    ```

* **Esempio:**
    ```c
    gcc receiver.c -o receiver
    ./receiver 5050
    ```


