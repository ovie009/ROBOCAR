<?php 
    include_once "./database_connect.php";
    $data = "reset";
    $sql = "UPDATE `robocar_datastream` SET `data` = '".$data."' WHERE `robocar_datastream`.`id` = 1;";
    mysqli_query($connect, $sql);
?>
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
</head>
<body>
    <nav>
        <a class="home-link" href="./index.php">
            Robocar
        </a>
    </nav>
    <div class="videostream">
        <img alt="robocar video stream" id="captured" src="#">
        <!-- src would be added using javascript -->
    </div>
    <div class="car_control">
        <p>Image Captured from <strong>ESP32 CAM</strong> </p>
    </div>
    <script>
        $("#captured").attr("src", "./IMAGE/image.jpg?"+Math.random());
    </script>
</body>
</html>