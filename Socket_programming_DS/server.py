from socket import *
import threading


HOST: str = "127.0.0.1"
PORT: int = 3000

def log(prefix: str, message: str):
    print(f"[{prefix}]\t\t{message}")

def handle_client(clientSocket: socket):
    while True:
        data:bytes = clientSocket.recv(1024)
        if not data:
            break
        log("INFO", f"Message received from client : {data.decode()}")
        clientSocket.send(data)
    clientSocket.close()

def main() -> None:
    serverSocket = socket(AF_INET, SOCK_STREAM)
    serverSocket.bind((HOST, PORT))
    serverSocket.listen(10)
    log("INFO", f"Server Listening on {HOST}:{PORT}")
    while(True):
        try:
            clientSocket, client_addr = serverSocket.accept()
            log("INFO", f"Client Connected : {client_addr[0]}:{client_addr[1]}")
            client_thread = threading.Thread(target=handle_client, args=(clientSocket,))
            client_thread.start()

        except KeyboardInterrupt:
            log("LOG", "Server Shutting Down...")
            break
        except Exception as e:
            log("ERROR", "error occurred")
            print(e)
            break

    serverSocket.close()    


if __name__ == "__main__":
    main()