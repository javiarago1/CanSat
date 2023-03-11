DROP DATABASE IF EXISTS satelite;
CREATE DATABASE satelite;

USE satelite;

CREATE TABLE PacketData (
    packetNumber INTEGER PRIMARY KEY,
    latitude FLOAT,
    longitude FLOAT,
    temperature FLOAT,
    pressure FLOAT,
    altitude FLOAT,
    timeStamp DATETIME(3)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;