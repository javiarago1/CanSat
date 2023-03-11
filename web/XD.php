<?php

$data = array(
    "packetNumber" => 123,
    "data" => "Hello from PHP"
);

$payload = json_encode($data);

echo $payload;
$ch = curl_init();

curl_setopt($ch, CURLOPT_URL, "http://localhost:3000/api/insertData");
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_POSTFIELDS, $payload);
curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen($payload))
);

$response = curl_exec($ch);

curl_close($ch);

echo $response;

?>