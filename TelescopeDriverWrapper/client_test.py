import socket

def main():
    host = 'localhost'
    port = 5502

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        print("Connected to server")

        # Send a message to the server
        while True:
            message = input("Enter message to send to server: ")
            s.sendall(message.encode('utf-8'))
            print(f"Sent: {message}")

            # Receive a response from the server
            data = s.recv(1024)
            print(f"Received: {data.decode('utf-8')}")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\nClient shutting down...")
    except ConnectionRefusedError:
        print("Connection refused. Is the server running?")
