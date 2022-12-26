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

  let imageUrl;
  setInterval(function() {
    imageUrl = "./stream/stream.jpg?"+Math.random();
    $("#stream").attr("src", imageUrl);
    // imageUrl = (imageUrl == "st.jpg") ? "image2.jpg" : "st.jpg";
  }, 250);
    
  // setInterval(function() {
  //   $.ajax({
  //     url: 'updateImage.php',
  //     success: function(data) {
  //       $('#stream_container').html(data);
  //     },
  //     error: function(xhr, status, error) {
  //       console.log(error);
  //     }
  //   });
  // }, 250);
});
