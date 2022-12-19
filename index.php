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
    <!-- Include VideoJS library -->
    <link href="https://vjs.zencdn.net/7.8.4/video-js.css" rel="stylesheet">
    <script src="https://vjs.zencdn.net/7.8.4/video.js"></script>
</head>
<body>
    <nav>
        Robocar 
    </nav>
    <div class="videostream">
        <p>
            <img alt="robocar video stram" id="stream" src="http://192.168.114.232/1024x768.jpg" >
            <!-- Create a video element to display the video stream -->
            <!-- <video id="my-video" class="video-js vjs-default-skin vjs-big-play-centered" controls preload="auto" width="640" height="480" data-setup='{}'>
            <source src="http://<ESP32-CAM IP address>:80/" type='video/mp4'>
            <p class="vjs-no-js">
                To view this video please enable JavaScript, and consider upgrading to a web browser that
                <a href="https://videojs.com/html5-video-support/" target="_blank">supports HTML5 video</a>
            </p>
            </video> -->
            <em>VIDEOSTREAM</em>
        </p>
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
</body>
</html>