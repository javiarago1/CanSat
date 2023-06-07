let map;
let route = [];

let previousPosition;
let previousTime;
let lastPacketNumber=-1;

let previousTimeChart;

window.onload = setup



let chart;

let pressureChart;

let altitudeChart;

function setup(){
    setupChart()
    setupPressureChart()
    setupAltitudeChart()
}

function setupAltitudeChart(){
    let ctx = document.getElementById('altitude-chart').getContext('2d');
    altitudeChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: [],
            datasets: [
                {
                    label: 'Altitude',
                    data: [],
                    backgroundColor: [
                        'rgba(75, 192, 192, 0.2)'
                    ],
                    borderColor: [
                        'rgba(75, 192, 192, 1)'
                    ],
                    borderWidth: 1
                }
            ]
        },
        options: {
            responsive: true,

            tooltips: {
                callbacks: {
                    label: function (tooltipItem, data) {
                        let dataset = data.datasets[tooltipItem.datasetIndex];
                        let index = tooltipItem.index;
                        let y = dataset.data[index].y;
                        let date = dataset.data[index].date;
                        let packetNumber = dataset.data[index].packetNumber;
                        return `Packet number: ${packetNumber} Time stamp: ${date} Altitude: ' ${y} ' m`;
                    }
                }
            },
            scales: {
                xAxes: [{
                    type: 'linear',
                    scaleLabel: {
                        display: true,
                        labelString: 'Time (seconds)'
                    }, ticks: {
                        callback: function (value) {
                            return value + 's';
                        }
                    }
                }],
                yAxes: [{
                    scaleLabel: {
                        display: true,
                        labelString: 'Altitude (m)'
                    }, ticks: {
                        callback: function (value) {
                            return value + ' m';
                        }
                    }
                }]
            }
        }
    });
}


function setupPressureChart(){
    let ctx = document.getElementById('pressure-chart').getContext('2d');
    pressureChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: [],
            datasets: [
                {
                    label: 'Pressure',
                    data: [],
                    backgroundColor: [
                        'rgba(54, 162, 235, 0.2)'
                    ],
                    borderColor: [
                        'rgba(54, 162, 235, 1)'
                    ],
                    borderWidth: 1
                }
            ]
        },
        options: {
            responsive: true,

            tooltips: {
                callbacks: {
                    label: function (tooltipItem, data) {
                        let dataset = data.datasets[tooltipItem.datasetIndex];
                        let index = tooltipItem.index;
                        let y = dataset.data[index].y;
                        let date = dataset.data[index].date;
                        let packetNumber = dataset.data[index].packetNumber;
                        return `Packet number: ${packetNumber} Time stamp: ${date} Pressure: ' ${y} ' Pa`;
                    }
                }
            },
            scales: {
                xAxes: [{
                    type: 'linear',
                    scaleLabel: {
                        display: true,
                        labelString: 'Time (seconds)'
                    }, ticks: {
                        callback: function (value) {
                            return value + 's';
                        }
                    }
                }],
                yAxes: [{
                    scaleLabel: {
                        display: true,
                        labelString: 'Pressure (Pa)'
                    }, ticks: {
                        callback: function (value) {
                            return value + ' Pa';
                        }
                    }
                }]
            }
        }
    });
}

function setupChart(){
    let ctx = document.getElementById('temperature-chart').getContext('2d');
    chart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: [],
            datasets: [
                {
                    label: 'Temperature',
                    data: [],
                    backgroundColor: [
                        'rgba(255, 99, 132, 0.2)'
                    ],
                    borderColor: [
                        'rgba(255, 99, 132, 1)'
                    ],
                    borderWidth: 1
                }
            ]
        },
        options: {
            responsive: true,

            tooltips: {
                callbacks: {
                    label: function (tooltipItem, data) {
                        let dataset = data.datasets[tooltipItem.datasetIndex];
                        let index = tooltipItem.index;
                        let y = dataset.data[index].y;
                        let date = dataset.data[index].date;
                        let packetNumber = dataset.data[index].packetNumber;
                        return `Packet number: ${packetNumber} Time stamp: ${date} Temperature: ' ${y} '°C`;
                    }
                }
            },
            scales: {
                xAxes: [{
                    type: 'linear',
                    scaleLabel: {
                        display: true,
                        labelString: 'Time (seconds)'
                    }, ticks: {
                        callback: function (value) {
                            return value + 's';
                        }
                    }
                }],
                yAxes: [{
                    scaleLabel: {
                        display: true,
                        labelString: 'Temperature (°C)'
                    }, ticks: {
                        callback: function (value) {
                            return value + '°C';
                        }
                    }
                }]
            }
        }
    });
}

let acum=0;

async function nameOfFunction(event) {

    let polyline = new google.maps.Polyline({
        path: route,
        geodesic: true,
        strokeColor: '#FF0000',
        strokeOpacity: 1.0,
        strokeWeight: 2,
    });
    let data= JSON.parse(event.data)
    if (data.length > 0 ){
        lastPacketNumber = data[data.length-1].packetNumber;
    }
    const output = document.getElementById("output");
    let chartData = chart.data;
    let pressureCharData = pressureChart.data;
    let altitudeCharData = altitudeChart.data;

    for (let i=0;i<data.length;i++){

        let currentTimeChart = new Date(data[i].timeStamp);
        let temperature = data[i].temperature;
        let pressure = data[i].pressure;
        let altitude =  data[i].altitude;
        let timeDifferenceChart = previousTimeChart ? currentTimeChart - previousTimeChart : 0;
        acum += timeDifferenceChart / 1000

        chartData.datasets[0].data.push(
            {
                x: acum.toFixed(2),
                y: temperature,
                date: currentTimeChart.toLocaleString(),
                packetNumber: data[i].packetNumber
            });

        pressureCharData.datasets[0].data.push(
            {
                x: acum.toFixed(2),
                y: pressure,
                date: currentTimeChart.toLocaleString(),
                packetNumber: data[i].packetNumber
            });

        altitudeCharData.datasets[0].data.push(
            {
                x: acum.toFixed(2),
                y: altitude,
                date: currentTimeChart.toLocaleString(),
                packetNumber: data[i].packetNumber
            });

        previousTimeChart = currentTimeChart;


        if (data[i].latitude!==0 && data[i].longitude!==0) {
            output.innerHTML = '';
            const currentLat = parseFloat(data[i].latitude);
            const currentLng = parseFloat(data[i].longitude);

            let currentTime = data[i].timeStamp;
            currentTime = Date.parse(data[i].timeStamp);

            // Calculate the distance and speed if the previous position and time are defined
            if (previousPosition && previousTime && data.length <= 3) {

                // Calculate the distance between the previous position and the current position
                const distance = google.maps.geometry.spherical.computeDistanceBetween(
                    new google.maps.LatLng(previousPosition),
                    new google.maps.LatLng(currentLat, currentLng)
                );

                // Calculate the time elapsed between the previous time and the current time
                let timeElapsed = (currentTime - previousTime) / 1000.0; // convert from milliseconds to seconds

                // Calculate the speed in meters per second
                const speed = distance / timeElapsed;

                // Calculate the heading (direction)
                const heading = google.maps.geometry.spherical.computeHeading(
                    previousPosition,
                    new google.maps.LatLng(currentLat, currentLng)
                );


                // Add the distance, speed, and heading to the HTML output

                document.getElementById("latitude").innerText = `Latitude:  ${currentLat}`;
                document.getElementById("longitude").innerText = `Longitude: ${currentLng}`;
                document.getElementById("distance_traveled").innerText = `Distance traveled: ${distance.toFixed(2)} m`;
                document.getElementById("speed").innerText = `Speed : ${speed.toFixed(2)} m/s`;
                document.getElementById("heading").innerText = `Heading : ${heading.toFixed(2)} °`;

            }

            // Update the previous position and time
            previousPosition = new google.maps.LatLng(currentLat, currentLng);
            previousTime = currentTime;

            // Create a new LatLng object
            const latLng = new google.maps.LatLng(currentLat, currentLng);

            // Update the route
            route.push(latLng);

            // Center the map on the new LatLng object
            if (!map) {
                // Create the map if it doesn't exist yet
                map = new google.maps.Map(document.getElementById('map'), {
                    center: latLng,
                    zoom: 16,
                });
            } else {
                // Update the map center if it already exists
                map.setCenter(latLng);
            }

            // Add a marker to the map if the route is empty and the starting marker hasn't been added
            if (route.length === 1) {
                new google.maps.Marker({
                    position: latLng,
                    map,
                    icon: {
                        path: google.maps.SymbolPath.CIRCLE,
                        scale: 10,
                        fillColor: 'red',
                        fillOpacity: 1,
                        strokeWeight: 0,
                    },
                });
            }


            polyline.setMap(map);
            polyline.setPath(route);
        }


    }

    chart.update()

    pressureChart.update()

    altitudeChart.update()

}


// Load the Google Maps API
function initMap() {
    const socket = new WebSocket('ws://64.226.98.98:3000');
    socket.onmessage = nameOfFunction;
    setInterval(() => {
        socket.send(JSON.stringify({ packetNumber: lastPacketNumber }));
    }, 1000);
}

