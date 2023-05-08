# Socket UDP in C

## Introduzione 

Un socket è un oggetto software che permette l'invio e la ricezione di dati, tra host remoti (tramite una rete) o tra processi locali (Inter-Process Communication).

La chiamata **socket()** restituisce un identificatore di socket.

## Il metodo socket()

```c
int socket(int domain, int type, int protocol)
```
* **domain:** AF_INET, PF_INET, PF_INET6
* **type:** SOCK_DGRAM, SOCK_STREAM
* **protocol:** 0 (viene scelto il protocollo più adatto)

## Il metodo bind()

```c
int bind(int socket, struct sockaddr* addr, int addrlen)
```

Serve per inserire i dati locali (indirizzo e porta) nel socket. Restituisce 0 in caso di successo.

## Il metodo sendto()

```c
int sendto(int socket, void *buffer, size_t size, int flags, struct sockaddr* addr, size_t length)
```

Serve per la scrittura nei socket.
Bisogna specificare in 'addr' l'indirizzo di destinazione.

## Il metodo recvfrom()

```c
int recvfrom(int socket, void *buffer, size_t size, int flags, struct sockaddr* addr, size_t length)
```

Serve per la lettura nei socket.
Bisogna specificare in 'addr' l'indirizzo mittente.

## Il metodo close()

```c
int close(int socket)
```

Chiude un socket aperto.

# Socket non bloccanti

Un socket viene normalmente creato come **«bloccante»**; ciò significa che, a seguito di una chiamata alla funzione di attesa connessione, blocca il processo chiamante, fino all'arrivo di una richiesta di connessione.

Un socket **«non bloccante»**, invece, non provoca il blocco del processo chiamante in una attesa indefinita; se al momento dell'attesa di connessione non è presente alcuna richiesta, il processo continua la sua esecuzione e la funzione di attesa connessione fornisce un appropriato codice di errore.

# Istruzioni per l'uso

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


