$(document).ready(function() {
  // onclick the checkbox, show typed password
  $('#show-password').change(function() {
    var input = $('#password-input');
    if(this.checked) {
      input.attr('type', 'text');
    } else {
      input.attr('type', 'password');
    }
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
  }, 15000); // 5000 milliseconds = 5 seconds
    
  let intervalId;

  $('.car-buttons, #right, .camera-buttons, .reset-camera').on('mousedown touchstart', function () {
    let direction = $(this).data("direction");
    intervalId = setInterval(function() {
      // Do something on each iteration of the loop
      // let direction = this;
      console.log(direction);
      $.ajax({
        type: 'POST',
        url: 'updatedb.php',
        data: { data: direction },
        success: function(response) {
          // code to handle the response from the server
        }
      });
    }, 250);
  });

  $('.car-buttons, .camera-buttons, .reset-camera').on('mouseup touchend', function () {
    clearInterval(intervalId);
  });

  // function to check if a cookie exists
  function checkCookie(cookieName) {
    var name = cookieName + "=";
    var decodedCookie = decodeURIComponent(document.cookie);
    var ca = decodedCookie.split(';');
    for(var i = 0; i <ca.length; i++) {
      var c = ca[i];
      while (c.charAt(0) == ' ') {
        c = c.substring(1);
      }
      if (c.indexOf(name) == 0) {
        return true;
      }
    }
    return false;
  }

  // function to get the value of a cookie
  function getCookie(cookieName) {
    var name = cookieName + "=";
    var decodedCookie = decodeURIComponent(document.cookie);
    var ca = decodedCookie.split(';');
    for(var i = 0; i <ca.length; i++) {
      var c = ca[i];
      while (c.charAt(0) == ' ') {
        c = c.substring(1);
      }
      if (c.indexOf(name) == 0) {
        return c.substring(name.length, c.length);
      }
    }
    return "";
  }

  if (checkCookie("ngrokAddress")) {
    console.log("Cookie exists");
    $("#stream").attr("src", getCookie("ngrokAddress")+"/video");
  } else {
    console.log("Cookie does not exist");
  }
  
  // console.log(getCookie("myCookie"));
  
});
