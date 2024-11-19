CREATE TABLE new (
    id int NOT NULL,
    name char(50) NULL,
    age int NULL,

    PRIMARY KEY (id, name),
    FOREIGN KEY (name) REFERENCES name (name)
)