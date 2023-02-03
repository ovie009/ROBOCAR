<?php
    include_once "./database_connect.php";
    if (isset($_GET["IP"])) {
        $id = 1;
        $IP = $_GET['IP']; // get the IP address sent from the ESP32 CAM

        $sql = "UPDATE `ip` SET `address` = '".$IP."', `datetime` = CURRENT_TIMESTAMP WHERE `ip`.`id` = ".$id.";"; 
        // save the IP address in the database and the time it was sent
        
        mysqli_query($connect, $sql); 
        // run the query with the $connect variable established in database_connect.php

        // sql query
        $sql = "SELECT * FROM `robocar_datastream` WHERE id = ?;";
        // select the required data from the database the ESP32 CAM needs to function

        $stmt = mysqli_stmt_init($connect); // create prepared statement
        
        if (!mysqli_stmt_prepare($stmt, $sql)) { // run prepared statement
            echo 'Query Failed';
        } else {
            // Bind parameters to the placeholder
            mysqli_stmt_bind_param($stmt, "s", $id);
            // run parameters inside database
            mysqli_stmt_execute($stmt);
            $result = mysqli_stmt_get_result($stmt);
            while ($row = mysqli_fetch_assoc($result)) {
                # code...
                $mode = $row['mode']; // variable to indicate the mode of operation
                $flash = $row['flash']; // varable to control the flashlight during streaming
                $motionDetected = $row['motion_detected']; // varaible to store motion detected status
                $tolerance = $row['tolerance']; // variable to determine the tolerance level of the motion sensor
                $frame = $row['frame']; // variable to determine the tolerance level of the motion sensor
                echo $mode."#".$flash."&".$motionDetected.'@'.$tolerance.'%'.$frame; // send all these variables as a payload
            }
        }
    } else {
        echo 'invalid back door';
    }
    
?>
