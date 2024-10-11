import socket
import json

class client():
    def get_question(self):
        msg = 'getQuestion'
        self.client_socket.sendall(msg.encode())
        data = self.client_socket.recv(2046).decode()  # Получаем ответ
        return json.loads(data)

    def send_option(self, option):
        resp = 'setOption:' + option
        self.client_socket.sendall(resp.encode())
    
    def get_result(self):
        resp = 'getResult'
        self.client_socket.sendall(resp.encode())
        data = self.client_socket.recv(1024)
        print('acc = ' + data.decode())
        return data.decode()

    def __init__(self):
        host = '127.0.0.1'  # Адрес сервера
        port = 65432        # Порт сервера

        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((host, port))  # Подключаемся к серверу
