import socket
import json
import random

questions = [ #первый вариант всегда правильный
    {
        'question': 'Сколько планет в солнечной системе?',
        'options': [
            '8', '6', '7', '9'
        ]
    },
    {
        'question': 'Какая планета в солнечной системе самая большая?',
        'options': [
            'Юпитер', 'Нептун', 'Земля', 'Солнце'
        ]
    },
    {
        'question': 'У какой планеты есть кольца?',
        'options': [
            'Сатурн', 'Венера', 'Юпитер', 'Земля'
        ]
    },
    {
        'question': 'Какая из планет самая тяжелая?',
        'options': [
            'Венера', 'Нептун', 'Юпитер', 'Земля'
        ]
    },
    {
        'question': 'За какой промежуток времени Земля совершает оборот вокруг Солнца?',
        'options': [
            'Год', 'День', 'Неделя', 'Месяц'
        ]
    },
]

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', 65432))
    server_socket.listen()
    print("Сервер запущен и ждет соединения...")

    conn, addr = server_socket.accept()
    print(f"Подключено к {addr}")
    handle_client(conn)
    server_socket.close()

def send_dict(conn, value):
    conn.sendall(json.dumps(value).encode())

alreadySent = 0
currQuestion = None
accuracy = 0

def get_current():
    global currQuestion
    return currQuestion

def get_question():
    global alreadySent
    global currQuestion
    if alreadySent == len(questions):
        return None
    alreadySent += 1
    currQuestion = questions[alreadySent - 1]
    return currQuestion

def handle_client(conn):
    global accuracy
    global questions
    random.shuffle(questions)
    try:
        while True:
            data = conn.recv(1024).decode()
            if not data:  # Если данных нет, клиент закрыл соединение
                print("Клиент закрыл соединение")
                break
            if data == 'getQuestion':
                send_dict(conn, get_question())
            if 'setOption:' in data:
                option = data[10:]
                print(option)
                if(option == get_current()['options'][0]):
                    print('true')
                    accuracy += 100/len(questions)
                else:
                    print('false')
            if data == 'getResult':
                conn.sendall(str(accuracy).encode())

    except ConnectionAbortedError:
        conn.close()
        print("Соединение закрыто.")

if __name__ == "__main__":
    start_server()
