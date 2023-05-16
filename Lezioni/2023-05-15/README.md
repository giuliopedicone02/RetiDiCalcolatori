# Routing - Istruzioni per l'uso

* **Modificare il nome di una macchina virtuale**

    ```bash
    # Effettuare l'accesso come amministratore (root)

    cd /etc # Cartella con i file di configurazione di sistema

    nano hostname # Apre il file dove è inserito il nome della macchina virtuale

    # Modificare 'debian' con il nuovo nome della macchina virtuale
    
    # Salvare (CTRL+O)
    # Chiudere il file (CTRL+X)

    reboot # Serve a riavviare la macchina virtuale
    ```

* **Modificare l'indirizzo IP in modo non persistente**
    ```bash
    # --- Aggiungere un indirizzo IP --- #
    ip a add 'indirizzo' dev 'nomeSchedaRete'

    # Es: ip a add 192.168.1.1/24 dev enp0s3

    # --- Rimuovere un indirizzo IP --- #

    ip a del 'indirizzo' dev 'nomeSchedaRete'

    # Es: ip a del 192.168.1.1/24 dev enp0s3
    ```

* **Modifica persistente dell'indirizzo IP**
    ```bash
    # Effettuare l'accesso come amministratore (root)

    cd /etc/network # Cartella con i file di configurazione di rete

    nano interfaces 

    # Modificare 'iface enp0s3 inet dhcp' in 'iface enp0s3 inet static' ed aggiungere sotto quella riga le seguenti informazioni:

    address 192.168.1.1/24
    gateway 192.168.1.254

    # Salvare (CTRL+O)
    # Chiudere il file (CTRL+X)

    reboot # Serve a riavviare la macchina virtuale
    ```

* **Come abilitare le schede di rete:**
    ```bash
    ip link set dev 'nomeScheda' up

    # Es: ip link set dev enp0s3 up
    ```

# Esempio file di configurazione interfaces

```bash
# This file describes the network interfaces available on your system
# and how to activate them. For more information, see interfaces (5).

source /etc/network/interfaces.d/*

# The loopback network interface. 
auto lo
iface lo inet loopback

# The primary network interface
allow-hotplug enpos3 
iface enpos3 inet static 
address 192.168.1.1/24 
gateway 192.168.1.254

#
allow-hotplug enp0s8 
iface enpos8 inet static

#
allow-hotplug enpos9 
iface enpos9 inet static

#
allow-hotplug enp0s10 
iface enpos10 inet static
```