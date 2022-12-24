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
        $.ajax({
          type: 'POST',
          url: 'updatedb.php',
          data: { data: direction },
          success: function(data) {
            // code to handle the response from the server
          }
        });
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

// onclick the checkbox, show typed password
$(document).ready(function() {
  $('#show-password').change(function() {
    var input = $('#password-input');
    if(this.checked) {
      input.attr('type', 'text');
    } else {
      input.attr('type', 'password');
    }
  });
});

setInterval(function() {
  $.ajax({
    type: 'POST',
    url: 'check_new_login.php',
    data: { id: 1 },
    success: function(data) {
      // code to handle the response from the server
      // console.log(data);
      if (data === 'new user found!') {
        // if a new device has logged in with the same
        // login credentials more recently 
        // reload the page to log out the old user
        location.reload(true);
      }
    }
  });
}, 2500); // 5000 milliseconds = 5 seconds