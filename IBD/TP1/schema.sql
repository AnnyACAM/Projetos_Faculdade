DROP TABLE IF EXISTS ingressos;
DROP TABLE IF EXISTS clientes;
DROP TABLE IF EXISTS sessoes;
DROP TABLE IF EXISTS salas;
DROP TABLE IF EXISTS filmes;

CREATE TABLE filmes (
    id INTEGER PRIMARY KEY,
    titulo TEXT NOT NULL,
    genero TEXT NOT NULL,
    duracao INTEGER NOT NULL,
    classificacao_indicativa INTEGER NOT NULL
);

CREATE TABLE salas (
    id INTEGER PRIMARY KEY,
    nome TEXT NOT NULL,
    capacidade INTEGER NOT NULL
);

CREATE TABLE sessoes (
    id INTEGER PRIMARY KEY,
    filme_id INTEGER NOT NULL,
    sala_id INTEGER NOT NULL,
    data_hora TEXT NOT NULL,
    preco_ingresso REAL NOT NULL,
    FOREIGN KEY (filme_id) REFERENCES filmes(id),
    FOREIGN KEY (sala_id) REFERENCES salas(id)
);

CREATE TABLE clientes (
    id INTEGER PRIMARY KEY,
    nome TEXT NOT NULL,
    email TEXT NOT NULL,
    data_nascimento TEXT NOT NULL
);

CREATE TABLE ingressos (
    id INTEGER PRIMARY KEY,
    sessao_id INTEGER NOT NULL,
    cliente_id INTEGER NOT NULL,
    data_compra TEXT NOT NULL,
    FOREIGN KEY (sessao_id) REFERENCES sessoes(id),
    FOREIGN KEY (cliente_id) REFERENCES clientes(id)
);
