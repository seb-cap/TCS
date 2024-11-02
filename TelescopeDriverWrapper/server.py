import asyncio
import socket

HEIMDALL = '72.233.250.82'

lock = asyncio.Lock()

async def handle_client(client):
    global driver

    print('Client connected')
    loop = asyncio.get_event_loop()
    request = None
    while request != 'exit':
        try:
            request = (await loop.sock_recv(client, 255))
        except (ConnectionResetError, ConnectionAbortedError) as e:
            print('Client disconnected')
            break
        if not request:
            print('Client disconnected')
            break
        async with lock:
            print(f"Sending request: {request.decode('utf8')}")
            driver.sendall(request)
            print('Request sent')
            try:
                response = driver.recv(255).decode('utf8')
            except socket.timeout:
                response = "Server timed out"
        print(f"Sending response: {response}")
        await loop.sock_sendall(client, response.encode("utf8"))
    print('Closing client')
    client.close()


async def run_server():
    # Connect to original TelescopeDriver server
    global driver
    driver = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    driver.connect((HEIMDALL, 5501))
    driver.settimeout(5)

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('localhost', 5502))
    server.listen(8)
    server.setblocking(False)

    loop = asyncio.get_event_loop()

    print("Listening on localhost:5502...")

    while True:
        client, _ = await loop.sock_accept(server)
        loop.create_task(handle_client(client))

try:
    asyncio.run(run_server())
except KeyboardInterrupt:
    print("Server shutting down...")
