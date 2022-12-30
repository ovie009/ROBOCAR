// Replace with the IP address of your ESP32
const wsUrl = "ws://192.168.1.100/";

// Create a WebSocket client
const ws = new WebSocket(wsUrl);

// Set up the canvas element
const canvas = document.getElementById("video");
const ctx = canvas.getContext("2d");

ws.onmessage = function(event) {
  // Parse the incoming JSON data
  const data = JSON.parse(event.data);

  // Decode the base64 image data
  const image = new Image();
  image.src = "data:image/jpeg;base64," + data.image;

  // Draw the image on the canvas
  ctx.drawImage(image, 0, 0, canvas.width, canvas.height);
};
