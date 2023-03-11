const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const mysql = require("mysql");
const LRU = require("lru-cache");

const api_routes = express();

api_routes.use(cors());
api_routes.use(bodyParser.json());

const db = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '',
    database: 'satelite'
});

const cache = new LRU({ max: 500 });

api_routes.post('/api/insertData', (req, res) => {


    const packetNumber = req.body.packetNumber;

    if (cache.has(packetNumber)) {
        console.log(req.connection.remoteAddress+":"+req.body.packetNumber+" esta ya" +
            " insertado");
        return res.send("Este paquete ya se ha registrado previamente.");
    }

    let sql = "INSERT INTO PacketData (packetNumber, latitude, longitude, "+
        "temperature, pressure, altitude, timeStamp) VALUES (?, ?, ?, ?, ?, ?," +
        " NOW(3))"
    let val = [req.body.packetNumber, req.body.latitude, req.body.longitude,
        req.body.temperature, req.body.pressure, req.body.altitude];

    try {
        db.query(sql, val, (err, result) => {
            if (err) {
                if (err.code === 'ER_DUP_ENTRY') {
                    console.log(req.connection.remoteAddress+":"+req.body.packetNumber+" esta ya" +
                        " insertado");
                    return res.send("Este paquete ya se ha registrado previamente.");
                }
                console.log("Error al insertar en la base de datos");
                return res.status(500).send("Error al insertar en la base de datos");
            }

            cache.set(packetNumber, true);

            console.log(req.connection.remoteAddress+":"+req.body.packetNumber+" se" +
                " acaba de insertar");
            res.send("Datos insertados correctamente");
        });
    } catch (e) {}
});

module.exports = api_routes;
