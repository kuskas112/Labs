class Book:
    ISBN = None
    title = None
    autors = []
    publisher = None
    year = None
    pageCount = None
    price = None

    def __init__(self, ISBN, title, autors, publisher, year, pageCount, price):
        self.ISBN = ISBN
        self.title = title
        self.autors = autors
        self.publisher = publisher
        self.year = year
        self.pageCount = pageCount
        self.price = price

    def __str__(self):
        output = '=' * 30 + '\n'
        output += 'ISBN: ' + self.ISBN + '\n'
        output += 'Название: ' + self.title + '\n'
        output += 'Авторы: ' + ''.join(x + ', ' for x in self.autors) + '\n'
        output += 'Издатель: ' + self.publisher + '\n'
        output += 'Год: ' + self.year + '\n'
        output += 'Количество страниц: ' + self.pageCount + '\n'
        output += 'Стоимость: ' + self.price + '\n'
        output += '=' * 30 + '\n'
        return output


books = []


def addBook():
    ISBN = input('Введите ISBN ')
    title = input('Введите название ')
    autors = []
    while True:
        autor = input('Введите автора (enter для продолжения) ')
        if autor == '':
            break
        autors.append(autor)
    publisher = input('Введите издателя ')
    year = input('Введите год ')
    pageCount = input('Введите количество страниц ')
    price = input('Введите цену ')
    books.append(Book(ISBN, title, autors, publisher, year, pageCount, price))


def deleteBook():
    index = input('Введите номер нужной книги начиная с нуля ')
    try:
        index = int(index)
        books.pop(index)
        print('Удаление успешно')
    except ValueError:
        print('Неправильный индекс')
    except IndexError:
        print('Индекс за пределами массива')


def printBooks(year='default'):
    for book in books:
        if year == book.year or year == 'default':
            print(book)

menu = "1. Добавить книгу\n" + \
       "2. Удалить книгу\n" + \
       "3. Вывести книги\n" + \
       "4. Вывести книги по году\n" + \
       "0. Выход"

def main():
    while True:
        print(menu)
        cmd = input()
        match cmd:
            case '0':
                exit()
            case '1':
                addBook()
            case '2':
                deleteBook()
            case '3':
                printBooks()
            case '4':
                year = input('Введите год')
                printBooks(year=year)
            case _:
                print('Неизвестная команда')

if __name__ == '__main__':
    main()
