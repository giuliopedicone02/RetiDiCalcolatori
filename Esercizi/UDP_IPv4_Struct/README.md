# UDP IPv4 Struct
Esercizio inventato che permette di inviare al server le seguenti informazioni su un **Giocatore**

* Nome (array di char di 20 caratteri)
* Età (valore intero)
* Valutazione (valore intero)

Il **server** avrà il compito di visualizzare le informazioni ricevute e di mandare un messaggio di conferma al client del tipo:

```c
Ho ricevuto le informazioni sul giocatore: nomeGiocatore 
```

# Istruzioni per l'uso

## Client

* **Compilazione:**
    ```c
    gcc sender.c -o sender
    ```

* **Esecuzione:**
    ```c
    ./sender indirizzoIPServer
    ```

* **Esempio:**
    ```c
    gcc sender.c -o sender
    ./sender 192.168.56.103
    ```

## Server

* **Visualizzazione indirizzo IP:**
    ```c
    ip a
    ```

* **Compilazione:**
    ```c
    gcc receiver.c -o receiver
    ```

* **Esecuzione:**
    ```c
    ./receiver
    ```

* **Esempio:**
    ```c
    gcc receiver.c -o receiver
    ./receiver
    ```


