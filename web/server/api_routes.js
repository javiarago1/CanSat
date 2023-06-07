const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const mysql = require("mysql");
const LRU = require("lru-cache");
const axios = require('axios');
const Redis = require('ioredis');
const redis = new Redis();

const api_routes = express();

api_routes.use(cors());
api_routes.use(bodyParser.json());

const db = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'password',
    database: 'satelite',
    port: 3306
});

const sessions = [];

api_routes.post('/login', (req, res) => {
    const { username, password } = req.body;

    // Verificar si las credenciales son válidas
    if (username === 'admin' && password === 'admin') {
        // Generar un token de sesión
        const sessionToken = Math.random().toString(36).substring(2, 15) + Math.random().toString(36).substring(2, 15);

        const newSession = { token: sessionToken, username };
        sessions.push(newSession);

        res.status(200).json({ token: sessionToken });
    } else {
        res.status(401).json({ error: 'Credenciales inválidas' });
    }
});

api_routes.post('/reset-services', (req, res) => {
    const sessionToken = req.headers.authorization.split(' ')[1];
    const query = `DELETE FROM PacketData`;



    const session = sessions.find((session) => session.token === sessionToken);
    if (session) {
        res.status(200).json({ message: 'Servicios reiniciados' });
        redis.flushall()
            .then(() => {
                console.log('All data in Redis has been deleted.');
            })
            .catch((err) => {
                console.error(err);
            });
        db.query(query, (err) => {
            if (err) {
                console.error(err);
            } else {
                console.log('All data deleted from MySQL');
            }
        });
    } else {
        res.status(401).json({ error: 'Token de sesión inválido' });
    }
});

const cache = new LRU({ max: 500 });

api_routes.get('/api/pressure', async (req, res) => {
    try {
        const response = await axios.get('https://weather.visualcrossing.com/VisualCrossingWebServices/rest/services/timeline/madrid?unitGroup=metric&elements=pressure&include=fcst%2Ccurrent&key=RUYGNM558QPRY5NLNQX9NFHVS&options=nonulls&contentType=json');
        const data = response.data;
        res.send({ pressure: data.currentConditions.pressure });
    } catch (error) {
        console.error(error);
        res.status(500).send({ error: 'Error al obtener la información de presión atmosférica' });
    }
});

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
