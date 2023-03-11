require('express');
const mysql = require('mysql');
const app = require('./api_routes');
const websocket = require('./websocket_server');

const db = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '',
    database: 'satelite'
});



const server = app.listen(3000, () => {
    console.log('Server running on port 3000');
});

websocket.start(server);


db.connect((err) => {
    if (err) throw err;
    console.log('Connected to database');
});

websocket.setDb(db);
