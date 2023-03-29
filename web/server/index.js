require('express');
const mysql = require('mysql');
const app = require('./api_routes');
const websocket = require('./websocket_server');

const db = mysql.createConnection({
    host: 'db-satelite-do-user-13771732-0.b.db.ondigitalocean.com',
    user: 'javier',
    password: 'AVNS_IoBshhllaHmSQ-5aiQQ',
    database: 'satelite',
    port: 25060
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
