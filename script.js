document.addEventListener('DOMContentLoaded', function () {
	// Replace the following with your MQTT broker details
	const brokerUrl = 'ws://192.168.27.201:9001';

	// Subscribe to multiple topics
	const topics = [
	  'sensor/BMP280/pressure', 
	  'sensor/BMP280/altitude',
	  'sensor/DHT11/humidity',
	  'sensor/DHT11/temperature',
	  'sensor/MQ135/air_quality'
	];

	const client = mqtt.connect(brokerUrl);

	client.on('connect', function () {
	  console.log('Connected to MQTT broker');

	  // Subscribe to each topic
	  topics.forEach(topic => {
		client.subscribe(topic, function (err) {
		  if (!err) {
			console.log(`Subscribed to ${topic}`);
		  }
		});
	  });
	});

	client.on('message', function (topic, message) {
console.log(`Received message on topic: ${topic}, message: ${message.toString()}`);
updateSensorData(topic, message);
});

function updateSensorData(topic, message) {
const temperatureElement = document.getElementById('temperatureDHT');
const humidityElement = document.getElementById('humidityDHT');
const pressureElement = document.getElementById('pressure');
const altitudeElement = document.getElementById('altitude');
const airqualityElement = document.getElementById('airQualityMQ135');

if (topic.includes('temperature') && message >= 35) {
  showNotification('Temperature exceeded threshold!');
}

if (topic.includes('humidity') && message >= 75) {
  showNotification('Humidity exceeded threshold!');
}

if (topic.includes('temperature') && temperatureElement) {
  temperatureElement.innerText = ` ${message} ${getSensorUnit('sensor/DHT11/temperature')}`;
}

if (topic.includes('humidity') && humidityElement) {
  humidityElement.innerText = `${message} ${getSensorUnit('sensor/DHT11/humidity')}`;
}

if (topic.includes('pressure') && pressureElement) {
  pressureElement.innerText = ` ${message} ${getSensorUnit('sensor/BMP280/pressure')}`;
}

if (topic.includes('altitude') && altitudeElement) {
  altitudeElement.innerText = ` ${message} ${getSensorUnit('sensor/BMP280/altitude')}`;
}

if (topic.includes('air_quality') && airqualityElement) {
  airqualityElement.innerText = `${message}`;
}
}
	function getSensorUnit(topic) {
	  // Add more cases for additional sensor units
	  if (topic.includes('temperature')) {
		return '°C';
	  } else if (topic.includes('humidity')) {
		return '%';
	  } else if (topic.includes('pressure')) {
		return 'Pa';
	  } else if (topic.includes('altitude')) {
		return 'm';
	  } else if (topic.includes('air_quality')) {
		return ''; // You may replace this with the appropriate unit for air quality
	  } else {
		return '';
	  }
	}
	function showNotification(message) {
	// Use the browser's native alert for simplicity
	// window.alert(message);
	Toastify({
		text: message,
		className: "info",
		style: {
		  background: "linear-gradient(to right, #F02929, #F57200)",
		}
	  }).showToast();
  }
 
  });