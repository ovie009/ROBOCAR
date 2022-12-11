// Set up the mousedown and mouseup event listeners
document.addEventListener('mousedown', startLoop);
document.addEventListener('mouseup', stopLoop);
document.addEventListener('touchstart', startLoop);
document.addEventListener('touchend', stopLoop);

function startLoop(event) {
  // Check if the mousedown event occurred over the button element
  if (event.target.matches('.car-buttons, .camera-buttons, .reset-camera')) {
    // Start the loop
    var interval = setInterval(function() {
      // Do something on each iteration of the loop
      // console.log(event.target.dataset.direction);
      let direction = event.target.dataset.direction; // get the direction data
        // console.log(direction);
        $.post("updateDb.php", {
            data: direction
        })
    }, 250);

    // Save the interval ID so it can be canceled later
    event.target.dataset.interval = interval;
  }
}

function stopLoop(event) {
  // Check if the mouseup event occurred over the button element
  if (event.target.matches('.car-buttons, .camera-buttons, .reset-camera')) {
    // Stop the loop
    clearInterval(event.target.dataset.interval);
  }
}