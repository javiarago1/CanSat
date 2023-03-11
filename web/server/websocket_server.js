const WebSocket = require('ws');
const Redis = require('ioredis');

let db;

exports.setDb = (_db) => {
    db = _db;
};

exports.start = (server) => {
    const redis = new Redis();
    const wss = new WebSocket.Server({server});

    wss.on('connection', (ws) => {
        console.log('Client connected');

        ws.on('message', async (message) => {
            console.log(`Received message: ${message}`);
            let value = JSON.parse(message);
            const lastData = parseFloat(value.packetNumber);

            try {
                const resultRedis = await redis.zrangebyscore('PacketData', lastData + 1, '+inf');
                let resultRedisParsed = resultRedis.map(packet => JSON.parse(packet));
                let startData = lastData;
                if (resultRedisParsed.length > 0) {
                    startData = Math.max(...resultRedisParsed.map(packet => packet.packetNumber));
                }

                console.log(resultRedisParsed)

                const query = `SELECT *
                               FROM PacketData
                               WHERE packetNumber > ${startData}
                               ORDER BY packetNumber ASC`;

                const resultMySQL = await new Promise((resolve, reject) => {
                    db.query(query, (err, result) => {
                        if (err) return reject(err);
                        resolve(result);
                    });
                });

                for (let i = 0; i < resultMySQL.length; i++) {
                    await redis.zadd('PacketData', resultMySQL[i].packetNumber, JSON.stringify(resultMySQL[i]));
                }

                const result = resultRedisParsed.concat(resultMySQL);

                ws.send(JSON.stringify(result));
            } catch (err) {
                console.error(err);
            }
        });

        ws.on('close', () => {
            console.log('Client disconnected');
        });
    });
};