from socket import *
import threading

HOST = "127.0.0.1"
PORT = 3000

def log(prefix: str, message: str):
    print(f"[{prefix}]\t\t{message}")

def run_client(client_id : int, message:str):
    clientSocket = socket(AF_INET, SOCK_STREAM)
    clientSocket.connect((HOST, PORT))

    log("INFO", f"Client {client_id} connected to server")
    log("INFO", f"Sending message {message}")
    clientSocket.sendall(message.encode())
    
    data:bytes = clientSocket.recv(1024)

    log("INFO", f"Message Received from server: {data.decode()}")
    clientSocket.close()


def main():
    messages = ["Hello from client 1", "Hello from client 2", "Hello from client 3", "Hello from client 4", "Hello from client 5"]

    for i in range(0, len(messages)):
        message = messages[i]
        client_thread = threading.Thread(target=run_client, args=(i+1, message))
        client_thread.start()



if __name__ == '__main__':
    main()