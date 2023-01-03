<?php
    include_once "./database_connect.php";
    if (isset($_GET["id"])) {
        $id = $_GET['id'];
        $mode = $_GET['mode'];
        $motion = $_GET['motion'];
        // sql query
        $sql = "SELECT `data`, `datetime` FROM `robocar_datastream` WHERE `id` = 1;";
    
        // run query
        $result = mysqli_query($connect, $sql);
    
        while ($row = mysqli_fetch_assoc($result)) {
            # code...
            $data = $row['data'];
            $dateTime = $row['datetime'];
            $dateTime = strtotime($dateTime);
            $unixSeconds = date('U');
            $timeElapsed = $unixSeconds - $dateTime;
            // amount of seconds to elapse to disregard input 
            if ($timeElapsed > 5) {
                echo '#N/A@';
            } else {
                echo '#'.$data.'@';
            }
        }
        
        $sql = "UPDATE `robocar_datastream` SET `mode` = '".$mode."', `motion_detected` = '".$motion."' WHERE `robocar_datastream`.`id` = 1;";
        mysqli_query($connect, $sql);
    } else {
        # code...
        echo 'invalid back door';
    }
?>    
