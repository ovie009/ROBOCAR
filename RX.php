<?php
    include_once "./database_connect.php";
    if (isset($_GET["id"])) {
        $id = $_GET['id'];
        $motion = $_GET['motion'];
        // sql query
        $sql = "SELECT `data`, `datetime`, `mode`, `servo_angle` FROM `robocar_datastream` WHERE `id` = 1;";
    
        // run query
        $result = mysqli_query($connect, $sql);
        $row = mysqli_fetch_assoc($result);
        $servoAngle = $row['servo_angle'];
        $data = $row['data'];
        $dateTime = $row['datetime'];
        $mode = $row['mode'];
        $dateTime = strtotime($dateTime);
        // $dateTime = strtotime($dateTime);
        $unixSeconds = date('U');
        $time = time();
        
        $timeElapsed = $unixSeconds - $dateTime;
        if ($timeElapsed > 2.5) {
            echo 'N/A#'.$mode.'@'.$servoAngle;
        } else {
            echo $data.'#'.$mode.'@'.$servoAngle;
        }
        
        $sql = "UPDATE `robocar_datastream` SET `motion_detected` = '".$motion."', `esp8266_timestamp` = CURRENT_TIMESTAMP WHERE `robocar_datastream`.`id` = 1;";
        mysqli_query($connect, $sql);
    } else {
        # code...
        echo 'invalid back door';
    }
?>    
