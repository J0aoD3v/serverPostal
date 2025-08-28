# SERVERPOSTAL

Servidor e cliente para envio de mensagens em **Java** e **C**, suportando **TCP** e **UDP**. Este projeto serve como exemplo de comunicação de rede entre cliente e servidor implementado em duas linguagens.

---

## Funcionalidades

- Comunicação **TCP**:

  - Cliente envia mensagens para o servidor.
  - Servidor exibe mensagens recebidas.
  - Encerramento do cliente com a palavra `FIM`.
  - Servidor deve ser encerrado manualmente com `Ctrl + C`.

- Comunicação **UDP**:
  - Cliente envia pacotes de mensagens para o servidor.
  - Servidor exibe mensagens recebidas com o endereço do remetente.
  - Encerramento do cliente com a palavra `FIM`.
  - Servidor é encerrado manualmente com `Ctrl + C`.

---

## Estrutura do Projeto

```
SERVERPOSTAL/
├── java/
│   ├── TCPServer.java
│   ├── TCPClient.java
│   ├── UDPServer.java
│   └── UDPClient.java
└── c/
    ├── TCPServer.c
    ├── TCPClient.c
    ├── UDPServer.c
    └── UDPClient.c
```

---

## Requisitos

### Para Java

- **Java 8 ou superior**.
- IDE ou terminal para compilar e executar os arquivos `.java`.

### Para C

- **GCC** ou outro compilador C.
- Sistema operacional compatível com POSIX (Linux, macOS, WSL no Windows).

---

## Como usar

## Versão Java

### TCP

1. Navegue até a pasta Java:

```bash
cd java/
```

2. Compile os arquivos:

```bash
javac TCPServer.java TCPClient.java
```

3. Execute o servidor:

```bash
java TCPServer
```

4. Execute o cliente (em outro terminal):

```bash
java TCPClient
```

5. No cliente, digite mensagens. Para encerrar, digite:

```
FIM
```

6. Para encerrar o servidor, pressione `Ctrl + C`.

---

### UDP

1. Navegue até a pasta Java:

```bash
cd java/
```

2. Compile os arquivos:

```bash
javac UDPServer.java UDPClient.java
```

3. Execute o servidor:

```bash
java UDPServer
```

4. Execute o cliente (em outro terminal):

```bash
java UDPClient
```

5. No cliente, digite mensagens. Para encerrar, digite:

```
FIM
```

6. Para encerrar o servidor, pressione `Ctrl + C`.

---

## Versão C

### TCP

1. Navegue até a pasta C:

```bash
cd c/
```

2. Compile os arquivos:

```bash
gcc -o tcp_server TCPServer.c
gcc -o tcp_client TCPClient.c
```

3. Execute o servidor:

```bash
./tcp_server
```

4. Execute o cliente (em outro terminal):

```bash
./tcp_client
```

5. No cliente, digite mensagens. Para encerrar, digite:

```
FIM
```

6. Para encerrar o servidor, pressione `Ctrl + C`.

---

### UDP

1. Navegue até a pasta C:

```bash
cd c/
```

2. Compile os arquivos:

```bash
gcc -o udp_server UDPServer.c
gcc -o udp_client UDPClient.c
```

3. Execute o servidor:

```bash
./udp_server
```

4. Execute o cliente (em outro terminal):

```bash
./udp_client
```

5. No cliente, digite mensagens. Para encerrar, digite:

```
FIM
```

6. Para encerrar o servidor, pressione `Ctrl + C`.

---

## Arquivos

### Pasta `java/`

- `TCPServer.java` – Servidor TCP que recebe mensagens do cliente.
- `TCPClient.java` – Cliente TCP que envia mensagens para o servidor.
- `UDPServer.java` – Servidor UDP que recebe pacotes do cliente.
- `UDPClient.java` – Cliente UDP que envia pacotes para o servidor.

### Pasta `c/`

- `TCPServer.c` – Servidor TCP implementado em C.
- `TCPClient.c` – Cliente TCP implementado em C.
- `UDPServer.c` – Servidor UDP implementado em C.
- `UDPClient.c` – Cliente UDP implementado em C.

---

## Observações

- **TCP** garante entrega e ordem das mensagens.
- **UDP** é mais rápido, mas não garante entrega ou ordem das mensagens.
- Servidores não possuem encerramento automático via mensagem; use `Ctrl + C` para interrompê-los.
- A porta padrão utilizada é **8089** em ambas as implementações.
- As implementações em Java e C são funcionalmente equivalentes e podem interoperar entre si.
