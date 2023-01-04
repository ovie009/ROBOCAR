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

  // function to copy text to clipboard
  function copyToClipboard(text) {
    navigator.clipboard.writeText(text).then(function() {
      console.log('Copying to clipboard was successful!');
    }, function(err) {
      console.error('Could not copy text: ', err);
    });
  }

  // onclick of copy button copy text to clipboard
  $(document).on('click', '#copy-button', function() {
    console.log("got here");
    let ipAddress = $("#ip_address").val();
    copyToClipboard('ngrok http '+ipAddress);
  });

  // get the flashlight status from the database
  $.ajax({
    type: 'GET',
    url: 'get_flash.php',
    data: { id: 1 },
    success: function(data) {
      if (data == 1) {
        $('#flash').prop('checked', true);
      }
    }
  });

  // checking if the same user has logged in from a different device
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
  // function to run on press and hold of a button
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

  // function to run on press and hold of a button
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

  // function to destroy Cookie
  function deleteCookie(name) {
    document.cookie = name + '=;expires=Thu, 01 Jan 1970 00:00:01 GMT;';
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

  // check if a cookie for the ngrok image has been created 
  if (checkCookie("ngrokAddress")) {
    console.log("Cookie exists");
    // if it has change the img link
    $("#stream").attr("src", getCookie("ngrokAddress")+"/video");
  } else {
    console.log("Cookie does not exist");
  }
  
  // if the img src in the stream isnt respomding, switch back to default image
  $('#stream').on('error', function() {
    // image could not be loaded
    deleteCookie("ngrokAddress");
    $("#stream").attr("src", "./IMAGE/default-image.png");
  });

  // function to handle login
  $('.login_submit').click(function() {
    let user = $("#user").val()
    let password = $("#password-input").val()
    // console.log(user);
    $.ajax({
      type: 'POST',
      url: 'login_handler.php',
      data: { user: user, password: password },
      success: function(data) {
        console.log(data);
        if (data === "successful") {
          location.reload(true);
        } else if (data === "incorrectPassword") {
          $("#password-input").addClass("input_error");
          $(".incorrectPassword").css({"opacity": 1, "transform": "translateY(-50px)"});
          setTimeout(() => {
            $(".incorrectPassword").css({"opacity": 0, "transform": "translateY(0px)"});
          }, 2000);
          
        } else if (data === "invalidUser") {
          $("#user").addClass("input_error");
          $(".invalidUser").css({"opacity": 1, "transform": "translateY(-50px)"});
          setTimeout(() => {
            $(".invalidUser").css({"opacity": 0, "transform": "translateY(0px)"});
          }, 2000);
        }
      }
    });
  });

  // function to remove error class in login input on keyup
  $("#password-input, #user").keyup(function() {
    $("#password-input, #user").removeClass("input_error");
  });

  
  let flashState;
  // function to make get request to update flash state in database
  $('#flash').click(function() {
    if ($(this).prop('checked')) {
      flashState = 1;
    } else {
      flashState = 0;
    }

    $.ajax({
      type: 'GET',
      url: 'update_flash.php',
      data: { flash: flashState },
      success: function(data) {
        // console.log(data);
      }
    });

  });


  
});
