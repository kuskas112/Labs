from sqlalchemy import ForeignKey
from sqlalchemy import String
from sqlalchemy.orm import DeclarativeBase
from sqlalchemy.orm import Mapped
from sqlalchemy.orm import mapped_column
from sqlalchemy import Text
from sqlalchemy import create_engine


class Base(DeclarativeBase):
    pass


class Book(Base):
    __tablename__ = "book"
    id: Mapped[int] = mapped_column(primary_key=True)
    Title: Mapped[str] = mapped_column(String(30))
    Description: Mapped[str] = mapped_column(Text())
    PageCount: Mapped[str] = mapped_column(String(50))


class Author(Base):
    __tablename__ = "author"
    id: Mapped[int] = mapped_column(primary_key=True)
    Name: Mapped[str] = mapped_column(String(50))


class BookHasAuthor(Base):
    __tablename__ = "book_has_author"
    Book: Mapped[int] = mapped_column(ForeignKey("book.id"), primary_key=True)
    Author: Mapped[int] = mapped_column(ForeignKey("author.id"), primary_key=True)


engine = create_engine('sqlite:///myDatabase.db', echo=True)
Base.metadata.create_all(engine)