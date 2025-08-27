# SERVERPOSTAL

Servidor e cliente para envio de mensagens em Java, suportando **TCP** e **UDP**. Este projeto serve como exemplo de comunicação de rede entre cliente e servidor.

---

## Funcionalidades

* Comunicação **TCP**:

  * Cliente envia mensagens para o servidor.
  * Servidor exibe mensagens recebidas.
  * Encerramento do cliente com a palavra `FIM`.
  * Servidor deve ser encerrado manualmente com `Ctrl + C`.

* Comunicação **UDP**:

  * Cliente envia pacotes de mensagens para o servidor.
  * Servidor exibe mensagens recebidas com o endereço do remetente.
  * Encerramento do cliente com a palavra `FIM`.
  * Servidor é encerrado manualmente com `Ctrl + C`.

---

## Requisitos

* **Java 8 ou superior**.
* IDE ou terminal para compilar e executar os arquivos `.java`.

---

## Como usar

### TCP

1. Compile os arquivos:

```bash
javac TCPServer.java TCPClient.java
```

2. Execute o servidor:

```bash
java TCPServer
```

3. Execute o cliente:

```bash
java TCPClient
```

4. No cliente, digite mensagens. Para encerrar, digite:

```
FIM
```

5. Para encerrar o servidor, pressione `Ctrl + C`.

---

### UDP

1. Compile os arquivos:

```bash
javac UDPServer.java UDPClient.java
```

2. Execute o servidor:

```bash
java UDPServer
```

3. Execute o cliente:

```bash
java UDPClient
```

4. No cliente, digite mensagens. Para encerrar, digite:

```
FIM
```

5. Para encerrar o servidor, pressione `Ctrl + C`.

---

## Estrutura dos arquivos

* `TCPServer.java` – Servidor TCP que recebe mensagens do cliente.
* `TCPClient.java` – Cliente TCP que envia mensagens para o servidor.
* `UDPServer.java` – Servidor UDP que recebe pacotes do cliente.
* `UDPClient.java` – Cliente UDP que envia pacotes para o servidor.

---

## Observações

* **TCP** garante entrega e ordem das mensagens.
* **UDP** é mais rápido, mas não garante entrega ou ordem das mensagens.
* Servidores não possuem encerramento automático via mensagem; use `Ctrl + C` para interrompê-los.