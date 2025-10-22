CREATE TABLE gestor (
    codigo_gestor TEXT PRIMARY KEY
);

CREATE TABLE bioma (
    bioma VARCHAR PRIMARY KEY
);

CREATE TABLE esfera_administrativa (
    esfera_administrativa VARCHAR PRIMARY KEY
);

CREATE TABLE uc (
    id_uc INTEGER UNIQUE NOT NULL,
    codigo_uc VARCHAR PRIMARY KEY,
    nome_uc TEXT NOT NULL,
    informacoes_gerais TEXT,
    esfera_administrativa VARCHAR REFERENCES esfera_administrativa(esfera_administrativa),
    categoria_manejo VARCHAR,
    categoria_iucn VARCHAR,
    uf CHAR(2),
    ano_criacao INTEGER,
    ano_ato_legal INTEGER,
    ato_legal_criacao TEXT,
    outros_atos_legais TEXT,
    plano_manejo INTEGER,
    conselho_gestor INTEGER,
    orgao_gestor VARCHAR REFERENCES gestor(codigo_gestor) ON DELETE SET NULL,
    fonte_area INTEGER,
    area_soma_biomas DECIMAL(14,6),
    area_soma_biomas_continental DECIMAL(14,6),
    area_ato_legal DECIMAL(14,6),
    bioma_area DECIMAL(14,6),
    percentual_alem_linha_costa DECIMAL(5,2),
    grupo VARCHAR,
    pi INTEGER,
    us INTEGER,
    recortes_ha DECIMAL(14,6),
    mar_territorial INTEGER,
    municipio_costeiro INTEGER,
    municipio_costeiro_area_marinha INTEGER,
    programa_projeto TEXT,
    sitios_patrimonio_mundial TEXT,
    sitios_ramsar TEXT,
    mosaico TEXT,
    reserva_biosfera TEXT,
    qualidade_dados_georreferenciados TEXT,
    codigo_wdpa VARCHAR,
    data_publicacao_cnuc TIMESTAMP,
    data_certificacao_gestor DATE
);


CREATE TABLE area_uc_bioma (
    codigo_uc VARCHAR NOT NULL REFERENCES uc(codigo_uc) ON DELETE CASCADE,
    bioma VARCHAR NOT NULL REFERENCES bioma(bioma) ON DELETE CASCADE,
    area_ha DECIMAL(14,6),
    PRIMARY KEY (codigo_uc, bioma)
);

CREATE TABLE municipio_bioma (
    municipio VARCHAR NOT NULL,
    uf VARCHAR NOT NULL,
    bioma VARCHAR NOT NULL REFERENCES bioma(bioma) ON DELETE CASCADE,
    PRIMARY KEY (municipio, uf, bioma)
);

CREATE TABLE desmatamento (
    ano INTEGER NOT NULL,
    area_km2 FLOAT,
    municipio VARCHAR NOT NULL,
    uf VARCHAR NOT NULL,
    cod_ibge INTEGER,
    bioma VARCHAR NOT NULL,
    PRIMARY KEY (ano, municipio, uf, bioma),
    FOREIGN KEY (municipio, uf, bioma) REFERENCES municipio_bioma(municipio, uf, bioma) ON DELETE CASCADE
);

CREATE TABLE municipios_abrangidos (
    codigo_uc VARCHAR NOT NULL REFERENCES uc(codigo_uc) ON DELETE CASCADE,
    municipio VARCHAR NOT NULL,
    uf VARCHAR NOT NULL,
    PRIMARY KEY (codigo_uc, municipio, uf)
);
