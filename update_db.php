<?php

    include_once "./database_connect.php";

    if (isset($_GET['data'])) {
        # code...
        $data = $_GET['data'];
        $sql = "SELECT `servo_angle` FROM `robocar_datastream` WHERE `id` = 1;";
        // run query
        $result = mysqli_query($connect, $sql);
        $row = mysqli_fetch_assoc($result);
        $servoAngle = $row['servo_angle'];

        echo 'servo angle from db: ';
        echo $servoAngle;
        echo '<br>';
        
        if ($data == "cam_left") {
            # code...
            // check if servo angle has reached its maximum value
            if ($servoAngle < 180) { $servoAngle += 5; }
            else { $servoAngle = 180; }
        } else if ($data == "cam_right") {
            # code...
            // check if servo angle has reached its minimum value
            if ($servoAngle > 0) { $servoAngle -= 5; }
            else { $servoAngle = 0; }
        } else if ($data == "reset") {
            # code...
            $servoAngle = 90;
        }
        
        $sql = "UPDATE `robocar_datastream` SET `data` = '".$data."', `servo_angle` = ".$servoAngle.", `datetime` = CURRENT_TIMESTAMP WHERE `robocar_datastream`.`id` = 1;";
        mysqli_query($connect, $sql);

        echo 'Car Direction: ';
        echo $data;
        echo '<br>';
        echo 'successful';
        
    } else{
        # code...
        header("location: index.php?successful");
    }
?>