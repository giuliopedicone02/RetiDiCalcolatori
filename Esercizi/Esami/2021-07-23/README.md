# Istruzioni per l'uso

* **Visualizzazione indirizzo IP del Server:**
    ```c
    ip a
    ```
## Client

* **Compilazione:**
    ```c
    gcc client.c -o client
    ```

* **Esecuzione:**
    ```c
    ./client indirizzoIPServer
    ```

* **Esempio:**
    ```c
    gcc client.c -o client
    ./chat 192.168.56.103 
    ```

## Server

* **Compilazione:**
    ```c
    gcc server.c -o server
    ```

* **Esecuzione:**
    ```c
    ./server
    ```

* **Esempio:**
    ```c
    gcc server.c -o server
    ./server
    ```

    **Attenzione!** Per il corretto funzionamento è necessario importare nella macchina virtuale del server anche i file "utenti.txt" e "files.txt".
