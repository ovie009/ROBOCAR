<?php

    include_once "./database_connect.php";

    if (isset($_POST['car'])) {
        # code...
        $carDirection = $_POST['car'];
        $sql = "UPDATE `robocar_datastream` SET `car` = '".$carDirection."' WHERE `robocar_datastream`.`id` = 1;";
        mysqli_query($connect, $sql);
        echo 'Car Direction: ';
        echo $carDirection;
        echo '<br>';
        echo 'successful';
        
    } else if (isset($_POST['camera'])) {
        # code...
        $cameraDirection = $_POST['camera'];
        $sql = "UPDATE `robocar_datastream` SET `camera` = '".$cameraDirection."' WHERE `robocar_datastream`.`id` = 1;";
        mysqli_query($connect, $sql);
        echo 'Camera Direction: ';
        echo $cameraDirection;
        echo '<br>';
        echo 'successful';

    } else{
        # code...
        header("location: index.php?successful");
    }
    
    header("location: index.php?successful");


?>