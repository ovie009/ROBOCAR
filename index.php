<?php session_start(); ?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Robocar</title>
    <link rel="stylesheet" href="style.css">
    <link rel="shortcut icon" href="clutch.png" type="image/x-icon">
    <script src="./jquery-3.4.1.min.js"></script>
    <!-- <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script> -->
    <script src="./main.js"></script>
</head>
<body>
    <?php
        
        if (isset($_SESSION['user'])) {
            ?><div class="connected_notice">
                <!-- content would be loaded dynamically with javascript -->
            </div><?php
            if (!isset($_SESSION['ngrok_address'])) {
            # code...?>
                <div class="esp_now_modal">
                    <div class="esp_now_container">
                        <form action="./update_ngrok.php" method="POST" class="esp_now_form" >
                            <div class="ip_container">
                                <!-- content would be loaded dynamically with javascript -->
                            </div>
                            <label for="ngrok_address">Ngrok address:</label>
                            <input type="text" name="ngrok_address" id="ngrok_address" placeholder="ngrok port forward address">
                            <div class="esp_now_footer">
                                <!-- content would be loaded dynamically with javascript -->
                            </div>
                        </form>
                    </div>
                </div>
                <script>
                    function refreshInput() {
                        console.log("refreshing");
                        $.ajax({
                            url: 'ip_container.php',
                            success: function(data) {
                                $('.ip_container').html(data);
                            }
                        });
                    }

                    function refreshFooter() {
                        console.log("refreshing");
                        $.ajax({
                            url: 'esp_now_footer.php',
                            success: function(data) {
                                $('.esp_now_footer').html(data);
                            }
                        });
                    }
                    refreshInput();
                    refreshFooter();
                    setInterval(refreshInput, 10000);
                    setInterval(refreshFooter, 10000);
                </script>

                <?php 
            } ?>
            <nav>
                <form action="" class="flash_form">
                    <label for="flash">Flashlight</label>
                    <input type="checkbox" name="flash" id="flash">
                </form>
                <a class="home-link" href="./index.php">
                    Robocar
                </a>
                <a class="logout_button" href="./logout.php">logout</a>
            </nav>
            <div class="videostream">
                <img alt="robocar video stream" id="stream" src="./IMAGE/default-image.png">
                <!-- <img alt="robocar video stream" id="stream" src="ac8d-197-210-226-59.eu.ngrok.io/video"> -->
                <div class="camera_control">
                    <form class="camera_form">
                        <button data-direction="cam_left" id="camera-left" type="button" class="camera-buttons">
                            <span class="left_arrow"></span>
                        </button>
                    </form>
                    <form  class="camera_form">
                        <button data-direction="cam_right" id="camera-right" type="button" class="camera-buttons">
                            <span class="right_arrow"></span>
                        </button>
                    </form>
                </div>
            </div>
            <div class="car_control">              
                <form class="mode_form">
                    <label for="mode">Mode: </label>
                    <select name="mode" id="mode">
                        <!-- content would be loaded with javascript -->
                    </select>
                </form>

                <form class="tolerance_form">
                    <label for="tolerance">Tolerance: </label>
                    <select name="tolerance" id="tolerance">
                        <!-- content would be loaded with javascript -->
                    </select>
                </form>
                <div class="controller_center">
                    <form class="car_unassigned">
                        <button data-direction="reset" class="reset-camera" type="button">
                            C
                        </button>
                    </form>
        
                    <form class="car_forward">
                        <button data-direction="car_forward" id="forward" type="button" class="car-buttons">
                            <span class="up-arrow"></span>
                        </button>
                    </form>
                    
                    <form class="car_backward">
                        <button data-direction="car_backward" id="backward" type="button" class="car-buttons">
                            <span class="down-arrow"></span>
                        </button>
                    </form>
                    
                    <form class="car_right">
                        <button data-direction="car_right" id="right" type="button" class="car-buttons">
                            <span class="right-arrow"></span>
                        </button>
                    </form>
                    
                    <form class="car_left">
                        <button data-direction="car_left" id="left" type="button" class="car-buttons">
                            <span class="left-arrow"></span>
                        </button>
                    </form>
                    
                </div>
            </div>
            <div class="check_new_login" hidden>
            </div>
            <div class="captured_image_notice">
                <!-- content would be loaded with javascript -->
            </div>
            <?php
        } else {
            # code...?>
                <div class="login_modal_background">
                    <div class="modal_heading">
                        <strong>
                            R<img class="wheel left_w" src="./clutch.png" alt="car wheel icon"> B<img class="wheel right_w" src="./clutch.png" alt="car wheel icon"> CA <img class="camera_icon" src="./cctv-camera.png" alt="cctv-camera icon">
                        </strong>
                    </div>
                    <div class="error_notice invalidUser">
                        Invalid User!
                    </div>
                    <div class="error_notice incorrectPassword">
                        Incorrect Password!
                    </div>
                    <div class="login_modal">
                        <form action="loginHandler.php" method="post">
                            <h2 class="login_heading">Login Details</h2>
                            <input type="text" id="user" name="user" placeholder="username" required>
                            <input type="password" id="password-input" name="password" placeholder="password" required>
                            <div class="show_password_wrapper">
                                <input type="checkbox" name="showPassword" id="show-password" > <label for="show-password">show password</label>
                            </div>
                            <button type="button" class="login_submit">Login</button>
                        </form>
                    </div>
                </div>
            <?php
        }
    
    ?>
</body>
</html>