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
    <script src="./main.js"></script>
    <!-- Include the JavaScript file -->
    <script src="stream.js"></script>
</head>
<body>
    <?php
        
        if (isset($_SESSION['user'])) {
            # code...?> 
            <nav>
                Robocar
                <a class="logout_button" href="./logout.php">logout</a>
            </nav>
            <div class="videostream">
                <!-- <img alt="robocar video stream" id="stream" src="./IMAGE/_jane.m_-20201013-0002.jpg" > -->
                <!-- <img alt="robocar video stream" id="stream" src="http://192.168.95.43:81/stream" crossorigin > -->
                <img alt="robocar video stream" id="stream" src="https://33cc-197-210-226-215.eu.ngrok.io/video">
                <div class="camera_control">
                    <form action="updateDb.php" method="POST" class="camera_form">
                        <button data-direction="cam_left" id="camera-left" type="button" class="camera-buttons">
                            <span class="left_arrow"></span>
                        </button>
                    </form>
                    <form action="updateDb.php" method="POST"  class="camera_form">
                        <button data-direction="cam_right" id="camera-right" type="button" class="camera-buttons">
                            <span class="right_arrow"></span>
                        </button>
                    </form>
                </div>
            </div>
            <div class="car_control">
                <div class="controller_center">
        
                    <form action="updateDb.php" method="POST" class="car_unassigned">
                        <button data-direction="reset" class="reset-camera" type="button">
                            C
                        </button>
                    </form>
        
                    <form action="updateDb.php" method="POST" class="car_forward">
                        <button data-direction="car_forward" id="forward" type="button" class="car-buttons">
                            <span class="up-arrow"></span>
                        </button>
                    </form>
                    
                    <form action="updateDb.php" method="POST" class="car_backward">
                        <button data-direction="car_backward" id="backward" type="button" class="car-buttons">
                            <span class="down-arrow"></span>
                        </button>
                    </form>
                    
                    <form action="updateDb.php" method="POST" class="car_right">
                        <button data-direction="car_right" id="right" type="button" class="car-buttons">
                            <span class="right-arrow"></span>
                        </button>
                    </form>
                    
                    <form action="updateDb.php" method="POST" class="car_left">
                        <button data-direction="car_left" id="left" type="button" class="car-buttons">
                            <span class="left-arrow"></span>
                        </button>
                    </form>
                    
                </div>
            </div>
            <div class="check_new_login" hidden>
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
                    <div class="login_modal">
                        <form action="loginHandler.php" method="post">
                            <h2 class="login_heading">Login Details</h2>
                            <input type="text" id="user" name="user" placeholder="username" required>
                            <input type="password" id="password-input" name="password" placeholder="password" required>
                            <div class="show_password_wrapper">
                                <input type="checkbox" name="showPassword" id="show-password" > <label for="show-password">show password</label>
                            </div>
                            <em class="error_notice">
                                <?php
                                    if (isset($_GET["incorrectPassword"])) {
                                        # code...
                                        echo 'Incorrect Password';
                                    }

                                    if (isset($_GET["invalidUsername"])) {
                                        # code...
                                        echo 'Invalid Username';
                                    }
                                ?>
                            </em>
                            <button type="submit" class="login_submit">Login</button>
                        </form>
                    </div>
                </div>
            <?php
        }
    
    ?>
</body>
</html>