CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY,
    username TEXT NOT NULL,
    password TEXT NOT NULL,
    role TEXT NOT NULL
);

INSERT INTO users (username, password, role) VALUES ('admin', 'admin', 'admin');
