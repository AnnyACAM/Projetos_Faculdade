CREATE TABLE IncrementoDesmatamento (
    ano INTEGER NOT NULL,                       -- year
    area_km2 DECIMAL(14,6),                 -- areakm
    municipio VARCHAR NOT NULL,             -- municipality
    cod_ibge INTEGER,                    -- geocode_ibge
    uf VARCHAR NOT NULL,                    -- state
    bioma VARCHAR NOT NULL,                 -- bioma
    PRIMARY KEY (ano, municipio, uf, bioma)
);