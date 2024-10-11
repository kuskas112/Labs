from flask import Flask, render_template, request, make_response, jsonify, redirect, url_for
from sqlalchemy import create_engine, select, func
from sqlalchemy.orm import Session

from models import Book, Author, BookHasAuthor

engine = create_engine('sqlite:///myDatabase.db', echo=True)

app = Flask(__name__)


def validateBook(title, desc, pages):
    try:
        str(title)
        str(desc)
        return int(pages) > 0
    except ValueError:
        return False


@app.route('/')
def main():
    with Session(engine) as session:
        books = session.query(Book).all()
        authors = session.query(Author).all()

        return render_template('main-page.html', books=books, authors=authors)


@app.route('/add/<string:table>', methods=['GET', 'POST'])
def add(table):
    if request.method == 'POST' and table == 'Book':
        title = request.form['title']
        description = request.form['description']
        pageCount = request.form['pageCount']

        if (validateBook(title, description, pageCount)):
            with Session(engine) as session:
                newBook = Book(Title=title, Description=description, PageCount=pageCount)
                session.add(newBook)
                session.commit()
                return redirect('/')

    if request.method == 'POST' and table == 'Author':
        name = request.form['Name']
        if name != '':
            with Session(engine) as session:
                newAuthor = Author(Name=name)
                session.add(newAuthor)
                session.commit()
                return redirect('/')
    return render_template('add.html', tableName=table)

@app.route('/delete/<string:table>', methods=['GET', 'POST'])
def delete(table):
    if table == 'Book':
        if request.method == 'GET':
            with Session(engine) as session:
                books = session.query(Book).all()
                return render_template('delete.html', books=books)
        else:
            with Session(engine) as session:
                ids = request.form.keys()
                session.query(Book).filter(Book.id.in_(ids)).delete(synchronize_session=False)
                session.commit()
                return redirect('/')

    if table == 'Author':
        if request.method == 'GET':
            with Session(engine) as session:
                authors = session.query(Author).all()
                return render_template('delete.html', tableName=table, authors=authors)
        else:
            with Session(engine) as session:
                ids = request.form.keys()
                session.query(Author).filter(Author.id.in_(ids)).delete(synchronize_session=False)
                session.commit()
                return redirect('/')


if __name__ == '__main__':
    app.run(debug=True)
